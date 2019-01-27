#include "isobuffer.h"

#include <algorithm>

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
	constexpr auto fX0Comp = std::greater<int> {};
	constexpr auto fX1X2Comp = std::less<int> {};
	#else
	constexpr auto fX0Comp = std::less<int> {};
	constexpr auto fX1X2Comp = std::greater<int> {};
	#endif

	constexpr auto kTopMultimeter = 2048;
}

isoBuffer::isoBuffer(QWidget* parent, int bufferLen, isoDriver* caller, unsigned char channel_value)
	: QWidget(parent)
	, m_channel(channel_value)
	, m_buffer(std::make_unique<short[]>(bufferLen*2))
	, m_bufferEnd(bufferLen-1)
	, m_samplesPerSecond(bufferLen/21.0/375*VALID_DATA_PER_375)
	, m_sampleRate_bit(bufferLen/21.0/375*VALID_DATA_PER_375*8)
	, m_virtualParent(caller)
{
}

// NOTE: the length of half of the allocated buffer is m_bufferEnd+1
void isoBuffer::insertIntoBuffer(short item)
{
	m_buffer[m_back] = item;
	m_buffer[m_back+m_bufferEnd+1] = item;
	m_back++;
	m_insertedCount++;

	if (m_insertedCount > m_bufferEnd)
	{
		m_insertedCount = m_bufferEnd+1;
	}

	if (m_back > m_bufferEnd)
	{
		m_back = 0;
	}
}

short isoBuffer::bufferAt(int idx) const
{
	// NOTE: this is only correct if idx < m_insertedCount
	return m_buffer[m_back + (m_bufferEnd+1) - idx];
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
	for (int i = 0; i < numSamples && itr < m_insertedCount; i++)
	{
		readData[i] = bufferAt(int(itr));

		if (singleBit)
		{
			int subIdx = 8*(-itr-floor(-itr));
			readData[i] &= (1 << subIdx);
		}

		itr += timeBetweenSamples;
	}

	return readData;
}

void isoBuffer::clearBuffer()
{
	for (int i = 0; i < m_bufferEnd; i++)
	{
		m_buffer[i] = 0;
	}

	m_back = 0;
}

void isoBuffer::gainBuffer(int gain_log)
{
	qDebug() << "Buffer shifted by" << gain_log;
	for (int i = 0; i < m_bufferEnd; i++)
	{
		if (gain_log < 0)
			m_buffer[i] <<= -gain_log;
		else
			m_buffer[i] >>= gain_log;
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
	return;
}

double isoBuffer::sampleConvert(short sample, int TOP, bool AC) const
{
	double scope_gain = (double)(m_virtualParent->driver->scopeGain);

	double voltageLevel = (sample * (vcc/2)) / (m_frontendGain*scope_gain*TOP);
	if (m_virtualParent->driver->deviceMode != 7) voltageLevel += m_voltage_ref;
#ifdef INVERT_MM
	if (m_virtualParent->driver->deviceMode == 7) voltageLevel *= -1;
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
	if (m_virtualParent->driver->deviceMode == 7) voltageLevel *= -1;
#endif
	if (m_virtualParent->driver->deviceMode != 7) voltageLevel -= m_voltage_ref;

	// voltageLevel = (sample * (vcc/2)) / (frontendGain*scope_gain*TOP);
	short sample = (voltageLevel * (m_frontendGain*scope_gain*TOP))/(vcc/2);
	return sample;
}

// For capacitance measurement. x0, x1 and x2 are all various time points
// used to find the RC coefficient.
template<typename Function>
int isoBuffer::capSample(int offset, int target, double seconds, double value, Function comp)
{
	int samples = seconds * m_samplesPerSecond;

	if (m_back < samples + offset) return -1;

	short sample = inverseSampleConvert(value, 2048, 0);

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

void isoBuffer::serialManage(double baudRate, UartParity parity)
{
	if (m_decoder == NULL)
	{
		m_decoder = new uartStyleDecoder(this);

		connect(m_decoder, &uartStyleDecoder::wireDisconnected,
		        m_virtualParent, &isoDriver::serialNeedsDisabling);
	}
	if (!m_isDecoding)
	{
		m_decoder->updateTimer->start(CONSOLE_UPDATE_TIMER_PERIOD);
		m_isDecoding = true;
	}
	m_decoder->setParityMode(parity);
	m_decoder->serialDecode(baudRate);
}

