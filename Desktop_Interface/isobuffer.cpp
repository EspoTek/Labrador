#include "isobuffer.h"

#include <algorithm>
#include <cassert>
#include <limits>

#include "isodriver.h"
#include "uartstyledecoder.h"

namespace
{
constexpr char const* fileHeaderFormat =
    "EspoTek Labrador DAQ V1.0 Output File\n"
    "Averaging = %d\n"
    "Mode = %d\n";

constexpr auto kSamplesSeekingCap = 20;

#ifdef INVERT_MM
constexpr auto fX0Comp = std::greater<> {};
constexpr auto fX1X2Comp = std::less<> {};
#else
constexpr auto fX0Comp = std::less<> {};
constexpr auto fX1X2Comp = std::greater<> {};
#endif

constexpr double kTriggerSensitivityMultiplier = 4;
}

isoBuffer::isoBuffer(QWidget* parent, int bufferLen, isoDriver* caller, unsigned char channel_value)
    : QWidget(parent)
    , m_channel(channel_value)
    , m_bufferPtr(std::make_unique<short[]>(bufferLen*2))
    , m_bufferLen(bufferLen)
    , m_samplesPerSecond(bufferLen/21.0/375*VALID_DATA_PER_375)
    , m_sampleRate_bit(bufferLen/21.0/375*VALID_DATA_PER_375*8)
    , m_virtualParent(caller)
{
    m_buffer = m_bufferPtr.get();
}

void isoBuffer::insertIntoBuffer(short item)
{
    m_buffer[m_back] = item;
    m_buffer[m_back+m_bufferLen] = item;
    m_back++;
    m_insertedCount++;

    if (m_insertedCount > m_bufferLen)
    {
        m_insertedCount = m_bufferLen;
    }

    if (m_back == m_bufferLen)
    {
        m_back = 0;
    }

    checkTriggered();
}

short isoBuffer::bufferAt(uint32_t idx) const
{
    if (idx > m_insertedCount)
        qFatal("isoBuffer::bufferAt: invalid query, idx = %u, m_insertedCount = %u", idx, m_insertedCount);

    return m_buffer[(m_back-1) + m_bufferLen - idx];
}

template<typename T, typename Function>
void isoBuffer::writeBuffer(T* data, int len, int TOP, Function transform)
{
    for (int i = 0; i < len; ++i)
    {
        insertIntoBuffer(transform(data[i]));
    }

    // Output to CSV
    if (m_fileIOEnabled)
    {
        bool isUsingAC = m_channel == 1
                         ? m_virtualParent->AC_CH1
                         : m_virtualParent->AC_CH2;

        for (int i = 0; i < len && m_fileIOEnabled; i++)
        {
            double convertedSample = sampleConvert(data[i], TOP, isUsingAC);

            maybeOutputSampleToFile(convertedSample);
        }
    }
}

void isoBuffer::writeBuffer_char(char* data, int len)
{
    writeBuffer(data, len, 128, [](char item) -> short {return item;});
}

void isoBuffer::writeBuffer_short(short* data, int len)
{
    writeBuffer(data, len, 2048, [](short item) -> short {return item >> 4;});
}

std::unique_ptr<short[]> isoBuffer::readBuffer(double sampleWindow, int numSamples, bool singleBit, double delayOffset)
{
    /*
     * The expected behavior is to run backwards over the buffer with a stride
     * of timeBetweenSamples steps, and push the touched elements into readData.
     * If more elements are requested than how many are stored (1), the buffer
     * will be populated only partially. Modifying this function to return null
     * or a zero-filled buffer instead should be simple enough.
     *
     * (1) m_insertedCount < (delayOffset + sampleWindow) * m_samplesPerSecond
     */
    const double timeBetweenSamples = sampleWindow * m_samplesPerSecond / numSamples;
    const int delaySamples = delayOffset * m_samplesPerSecond;

    std::unique_ptr<short[]> readData = std::make_unique<short[]>(numSamples);

    std::fill (readData.get(), readData.get() + numSamples, short(0));

    double itr = delaySamples;
    short *data = &m_buffer[(m_back-1) + m_bufferLen];
    for (int pos = 0; pos < numSamples && itr < m_insertedCount; pos++)
    {
        if (int(itr) < 0 || ((m_back-1) + m_bufferLen - itr) >= m_bufferLen * 2) {
            qWarning() << "itr out of range" << itr << numSamples << m_insertedCount << pos << timeBetweenSamples;
            break;
        }
        assert(int(itr) >= 0);

        // What we do: We loop over the bytes we would skip, and count the number of negative and positive values.
        // If there are more negative than positive we select the lowest we found, otherwise we pick the highest.
        // It's not perfect, but eliminates some of the worst artifacts.
        // An average would be easier, but you miss the peaks, which are the interesting parts of the data.

        // TODO: to optimize:
        // - reverse the loop (I thought the prefetching would be smart enough, but maybe not)
        // - Split loop into blocks with constant length, to avoid the pshuflw and whatnot
        if (timeBetweenSamples > 1) {
            int numPositive = 0;
            int numNegative = 0;
            short minimum = std::numeric_limits<short>::max();
            short maximum = std::numeric_limits<short>::min();
            const int end = qMin<int>(m_insertedCount, itr + timeBetweenSamples);
            for (int i=itr; i<end; i++) {
                // 29,94 │       movq      (%rdx,%rdi,2),%xmm4
                //  7,46 │       pshuflw   $0x1b,%xmm4,%xmm4
                const short val = data[-i];

                // 8,65 │       pminsw    %xmm4,%xmm1
                minimum = (val < minimum) ? val : minimum;

                // 4,00 │       pmaxsw    %xmm4,%xmm0
                maximum = (maximum < val) ? val : maximum;

                // 8,13 │       psrlw     $0xf,%xmm4
                // 4,12 │       movdqa    %xmm4,%xmm5
                // 4,43 │       punpcklwd %xmm6,%xmm5
                // 7,56 │       paddd     %xmm5,%xmm2
                numNegative += val < 0;

                // 4,78 │       pxor      %xmm11,%xmm4
                // 4,34 │       punpcklwd %xmm6,%xmm4
                // 5,98 │       paddd     %xmm4,%xmm3
                numPositive += val >= 0;
            }
            readData[pos] = maximum;
//            readData[pos] = (minimum < 0 && qAbs(minimum)) > qAbs(maximum) ? minimum: maximum;// numPositive > numNegative ? maximum: minimum;
//            readData[pos] = numPositive > numNegative ? maximum: minimum;
        } else {
            readData[pos] = bufferAt(int(itr));
        }

        if (singleBit)
        {
            int subIdx = 8*(-itr-floor(-itr));
            readData[pos] &= (1 << subIdx);
        }

        itr += timeBetweenSamples;
    }

    return readData;
}

void isoBuffer::clearBuffer()
{
    for (uint32_t i = 0; i < m_bufferLen; i++)
    {
        m_buffer[i] = 0;
        m_buffer[i + m_bufferLen] = 0;
    }

    m_back = 0;
    m_insertedCount = 0;
}

void isoBuffer::gainBuffer(int gain_log)
{
    qDebug() << "Buffer shifted by" << gain_log;
    for (uint32_t i = 0; i < m_bufferLen; i++)
    {
        if (gain_log < 0)
        {
            m_buffer[i] <<= -gain_log;
            m_buffer[i+m_bufferLen] <<= -gain_log;
        }
        else
        {
            m_buffer[i] >>= gain_log;
            m_buffer[i+m_bufferLen] >>= gain_log;
        }
    }
}


void isoBuffer::outputSampleToFile(double averageSample)
{
    char numStr[32];
    sprintf(numStr,"%7.5f, ", averageSample);

    m_currentFile->write(numStr);
    m_currentColumn++;

    if (m_currentColumn == COLUMN_BREAK)
    {
        m_currentFile->write("\n");
        m_currentColumn = 0;
    }
}

void isoBuffer::maybeOutputSampleToFile(double convertedSample)
{
    /*
     * This function adds a sample to an accumulator and bumps a sample count.
     * After the sample count hits some threshold the samples are averaged
     * and the average is written to a file.
     * If this makes us hit the max. file size, then fileIO is disabled.
     */

    m_fileIO_sampleAccumulator += convertedSample;
    m_fileIO_sampleCount++;

    if (m_fileIO_sampleCount == m_fileIO_sampleCountPerWrite)
    {
        double averageSample = m_fileIO_sampleAccumulator / m_fileIO_sampleCount;
        outputSampleToFile(averageSample);

        // Reset the accumulator and sample count for next data point.
        m_fileIO_sampleAccumulator = 0;
        m_fileIO_sampleCount = 0;

        // value of 0 means "no limit", meaning we must skip the check by returning.
        if (m_fileIO_maxFileSize == 0)
            return;

        // 7 chars(number) + 1 char(comma) + 1 char(space) = 9 bytes/sample.
        m_fileIO_numBytesWritten += 9;
        if (m_fileIO_numBytesWritten >= m_fileIO_maxFileSize)
        {
            m_fileIOEnabled = false; // Just in case signalling fails.
            fileIOinternalDisable();
        }
    }
}

void isoBuffer::enableFileIO(QFile* file, int samplesToAverage, qulonglong max_file_size)
{

    // Open the file
    file->open(QIODevice::WriteOnly);
    m_currentFile = file;

    // Add the header
    char headerLine[256];
    sprintf(headerLine, fileHeaderFormat, samplesToAverage, m_virtualParent->driver->deviceMode);
    m_currentFile->write(headerLine);

    // Set up the isoBuffer for DAQ
    m_fileIO_maxFileSize = max_file_size;
    m_fileIO_sampleCountPerWrite = samplesToAverage;
    m_fileIO_sampleCount = 0;
    m_fileIO_sampleAccumulator = 0;
    m_fileIO_numBytesWritten = 0;

    // Enable DAQ
    m_fileIOEnabled = true;

    qDebug("File IO enabled, averaging %d samples, max file size %lluMB", samplesToAverage, max_file_size/1000000);
    qDebug() << max_file_size;
}

void isoBuffer::disableFileIO()
{
    m_fileIOEnabled = false;
    m_currentColumn = 0;
    m_currentFile->close();
}


double isoBuffer::sampleConvert(short sample, int TOP, bool AC) const
{
    double scope_gain = (double)(m_virtualParent->driver->scopeGain);

    double voltageLevel = (sample * (vcc/2)) / (m_frontendGain*scope_gain*TOP);
    if (m_virtualParent->driver->deviceMode != DeviceMultimeter) voltageLevel += m_voltage_ref;
#ifdef INVERT_MM
    if (m_virtualParent->driver->deviceMode == DeviceMultimeter) voltageLevel *= -1;
#endif

    if (AC)
    {
        // This is old (1 frame in past) value and might not be good for signals with
        // large variations in DC level (although the cap should filter that anyway)??
        voltageLevel -= m_virtualParent->currentVmean;
    }
    return voltageLevel;
}

short isoBuffer::inverseSampleConvert(double voltageLevel, int TOP, bool AC) const
{
    double scope_gain = m_virtualParent->driver->scopeGain;

    if (AC)
    {
        // This is old (1 frame in past) value and might not be good for signals with
        // large variations in DC level (although the cap should filter that anyway)??
        voltageLevel += m_virtualParent->currentVmean;
    }

#ifdef INVERT_MM
    if (m_virtualParent->driver->deviceMode == DeviceMultimeter) voltageLevel *= -1;
#endif
    if (m_virtualParent->driver->deviceMode != DeviceMultimeter) voltageLevel -= m_voltage_ref;

    // voltageLevel = (sample * (vcc/2)) / (frontendGain*scope_gain*TOP);
    short sample = (voltageLevel * (m_frontendGain*scope_gain*TOP))/(vcc/2);
    return sample;
}

// For capacitance measurement.
// x0, x1 and x2 are all various time points used to find the RC coefficient.
template<typename Function>
int isoBuffer::capSample(int offset, int target, double seconds, double value, Function comp)
{
    int samples = seconds * m_samplesPerSecond;

    if (static_cast<int32_t>(m_back) < (samples + offset))
        return -1;

    short sample = inverseSampleConvert(value, 2048, false);

    int found = 0;
    for (int i = samples + offset; i--;)
    {
        short currentSample = bufferAt(i);
        if (comp(currentSample, sample))
            found = found + 1;
        else
            found = std::max(0, found-1);

        if (found > target)
            return samples - i;
    }

    return -1;
}

int isoBuffer::cap_x0fromLast(double seconds, double vbot)
{
    return capSample(0, kSamplesSeekingCap, seconds, vbot, fX0Comp);
}

int isoBuffer::cap_x1fromLast(double seconds, int x0, double vbot)
{
    return capSample(-x0, kSamplesSeekingCap, seconds, vbot, fX1X2Comp);
}

int isoBuffer::cap_x2fromLast(double seconds, int x1, double vtop)
{
    return capSample(-x1, kSamplesSeekingCap, seconds, vtop, fX1X2Comp);
}

void isoBuffer::serialManage(double baudRate, UartParity parity, bool hexDisplay)
{
    if (m_decoder == NULL)
    {
        m_decoder = new uartStyleDecoder(baudRate, this);
    }
    if (!m_isDecoding)
    {
        m_decoder->m_updateTimer.start(CONSOLE_UPDATE_TIMER_PERIOD);
        m_isDecoding = true;
    }

	m_decoder->m_baudRate = baudRate;
    m_decoder->setParityMode(parity);
    m_decoder->setHexDisplay(hexDisplay);
    m_decoder->serialDecode();
}

void isoBuffer::setTriggerType(TriggerType newType)
{
    qDebug() << "Trigger Type: " << (uint8_t)newType;
    m_triggerType = newType;
}

void isoBuffer::setTriggerLevel(double voltageLevel, uint16_t top, bool acCoupled)
{
    m_triggerLevel = inverseSampleConvert(voltageLevel, top, acCoupled);
    m_triggerSensitivity = static_cast<short>(1 + abs(voltageLevel * kTriggerSensitivityMultiplier * static_cast<double>(top) / 128.));
    qDebug() << "Trigger Level: " << m_triggerLevel;
    qDebug() << "Trigger sensitivity:" << m_triggerSensitivity;
}

// TODO: Clear trigger
// FIXME: AC changes will not be reflected here
void isoBuffer::checkTriggered()
{
    if (m_triggerType == TriggerType::Disabled)
        return;

    if ((bufferAt(0) >= (m_triggerLevel + m_triggerSensitivity)) && (m_triggerSeekState == TriggerSeekState::BelowTriggerLevel))
    {
        // Rising Edge
        m_triggerSeekState = TriggerSeekState::AboveTriggerLevel;
        if (m_triggerType == TriggerType::Rising)
            m_triggerPositionList.push_back(m_back - 1);
    }
    else if ((bufferAt(0) < (m_triggerLevel - m_triggerSensitivity)) && (m_triggerSeekState == TriggerSeekState::AboveTriggerLevel))
    {
        // Falling Edge
        m_triggerSeekState = TriggerSeekState::BelowTriggerLevel;
        if (m_triggerType == TriggerType::Falling)
            m_triggerPositionList.push_back(m_back - 1);
    }
}

double isoBuffer::getDelayedTriggerPoint(double delay)
{
    if (m_triggerPositionList.isEmpty()) {
        return 0;
    }
	
    // Holy fuck the STL APIs suck,
    // TODO: port to something sane that is readable

    const uint32_t delaySamples = delay * m_samplesPerSecond;

    QVector<uint32_t>::reverse_iterator it = std::find_if(m_triggerPositionList.rbegin(), m_triggerPositionList.rend(), [=](uint32_t index)
    {
        if (m_back > delaySamples) {
            return (index < m_back - delaySamples) || (index >= m_back);
        }

        return (index < m_bufferLen + m_back - delaySamples) && (index >= m_back);
    });

    if (it != m_triggerPositionList.rend())
    {
        // NOTE: vector::erase does not remove the element pointed to by the second iterator.
        m_triggerPositionList.erase(m_triggerPositionList.begin(), std::prev(it.base()));
        const uint32_t index = m_triggerPositionList[0];

        if (m_back > index) {
            return (m_back - index) / double(m_samplesPerSecond);
        }

        return (m_bufferLen + (m_back-1) - index) / double(m_samplesPerSecond);
    }

    return 0;
}
