#include "isobuffer.h"
#include "isodriver.h"
#include "uartstyledecoder.h"

namespace {
	static char const * fileHeaderFormat =
		"EspoTek Labrador DAQ V1.0 Output File\n"
		"Averaging = %d\n"
		"Mode = %d\n";

	constexpr auto kSamplesSeekingCap = 20;
	constexpr auto kTopMultimeter = 2048;
}

isoBuffer::isoBuffer(QWidget* parent, int bufferLen, isoDriver* caller, unsigned char channel_value)
	: QWidget(parent)
	, buffer((short*)calloc(bufferLen*2, sizeof(short)))
	, bufferEnd(bufferLen-1)
	, samplesPerSecond(bufferLen/21.0/375*VALID_DATA_PER_375)
	, sampleRate_bit(bufferLen/21.0/375*VALID_DATA_PER_375*8)
	, virtualParent(caller)
	, channel(channel_value)
{
}

void isoBuffer::insertIntoBuffer(short item)
{
	buffer[back] = item;
	back++;
	insertedCount++;

	if (insertedCount > bufferEnd)
	{
		insertedCount = bufferEnd+1;
	}

	if (back > bufferEnd)
	{
		back = 0;
	}
}

short isoBuffer::bufferAt(int idx) const
{
	return buffer[back - idx];
}

bool isoBuffer::maybeOutputSampleToFile(double convertedSample)
{
	/*
	 * This function adds a sample to an accumulator and bumps the sample count.
	 * After the sample count hits some threshold, the accumulated sample is
	 * outputted to a file. If this 'saturates' the file, then fileIO is disabled.
	 */
	average_sample_temp += convertedSample;
	fileIO_sampleCount++;

	// Check to see if we can write a new sample to file
	if (fileIO_sampleCount == fileIO_maxIncrementedSampleValue)
	{
		char numStr[32];
		sprintf(numStr,"%7.5f, ", average_sample_temp/((double)fileIO_maxIncrementedSampleValue));
		currentFile->write(numStr);
		currentColumn++;
		if (currentColumn >= COLUMN_BREAK)
		{
			currentFile->write("\n");
			currentColumn = 0;
		}

		// Reset the average and sample count for next data point
		fileIO_sampleCount = 0;
		average_sample_temp = 0;

		// Check to see if we've reached the max file size.
		if (fileIO_max_file_size != 0) // value of 0 means "no limit"
		{
			fileIO_numBytesWritten += 9;  // 7 chars for the number, 1 for the comma and 1 for the space = 9 bytes per sample.
			if (fileIO_numBytesWritten >= fileIO_max_file_size)
			{
				fileIOEnabled = false; // Just in case signalling fails.
				fileIOinternalDisable();
				return false;
			}
		}
	}
	return true;
}

template<typename T, typename Function>
void isoBuffer::writeBuffer(T* data, int len, int TOP, Function transform)
{
	for (int i = 0; i < len; ++i)
	{
		insertIntoBuffer(transform(data[i]));
	}

	// Output to CSV
	if (fileIOEnabled)
	{
		bool isUsingAC = channel == 1
		                 ? virtualParent->AC_CH1
						 : virtualParent->AC_CH2;

		for (int i = 0; i < len; i++)
		{
			double convertedSample = sampleConvert(data[i], TOP, isUsingAC);

			bool keepOutputting = maybeOutputSampleToFile(convertedSample);

			if (!keepOutputting) break;
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

short* isoBuffer::readBuffer(double sampleWindow, int numSamples, bool singleBit, double delayOffset)
{
	/* Refactor Note:
	 *
	 * Refactoring this function took a few passes were i made some assumptions:
	 *  - round() should be replaced by floor() where it was used
	 *  - int(floor(x)) and int(x) are equivalent (since we are always positive)
	 *  - free(NULL) is a no-op. This is mandated by the C standard, and virtually all
	 * implementations comply. A few known exceptions are:
	 *    - PalmOS
	 *    - 3BSD
	 *    - UNIX 7
	 *   I do not know of any non-compliant somewhat modern implementations.
	 *
	 * The expected behavior is to cycle backwards over the buffer, taking into
	 * acount only the part of the buffer that has things stored, with a stride
	 * of timeBetweenSamples steps, and insert the touched elements into readData.
	 *
	 * ~Sebastian Mestre
	 */
	const double timeBetweenSamples = sampleWindow * samplesPerSecond / numSamples;
	const int delaySamples = delayOffset * samplesPerSecond;

	free(readData);

	if(delaySamples+1 > insertedCount)
	{
		return readData = nullptr;
	}

	readData = (short*) calloc(numSamples, sizeof(short));

	double itr = delaySamples + 1;
	for (int i = 0; i < numSamples; i++)
	{
		while (itr > insertedCount)
			itr -= insertedCount;

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
	for (int i=0; i<bufferEnd; i++)
	{
		buffer[i] = 0;
	}

	back = 0;
}

void isoBuffer::gainBuffer(int gain_log)
{
	qDebug() << "Buffer shifted by" << gain_log;
	for (int i=0; i<bufferEnd; i++)
	{
		if (gain_log == -1) buffer[i] *= 2;
		else buffer[i] /= 2;
	}
}

// NOTE: glitch insert is a no-op
void isoBuffer::glitchInsert(short type)
{
}

void isoBuffer::enableFileIO(QFile* file, int samplesToAverage, qulonglong max_file_size)
{

	// Open the file
	file->open(QIODevice::WriteOnly);
	currentFile = file;

	// Add the header
	char headerLine[256];
	sprintf(headerLine, "EspoTek Labrador DAQ V1.0 Output File\nAveraging = %d\nMode = %d\n", samplesToAverage, virtualParent->driver->deviceMode);
	currentFile->write(headerLine);

	// Set up the isoBuffer for DAQ
	fileIO_maxIncrementedSampleValue = samplesToAverage;
	fileIO_max_file_size = max_file_size;
	fileIO_sampleCount = 0;
	fileIO_numBytesWritten = 0;
	average_sample_temp = 0;

	// Enable DAQ
	fileIOEnabled = true;

	qDebug("File IO enabled, averaging %d samples, max file size %lluMB", samplesToAverage, max_file_size/1000000);
	qDebug() << max_file_size;
	return;
}

void isoBuffer::disableFileIO()
{
	fileIOEnabled = false;
	currentColumn = 0;
	currentFile->close();
	return;
}

double isoBuffer::sampleConvert(short sample, int TOP, bool AC) const
{

	double scope_gain = (double)(virtualParent->driver->scopeGain);
	double voltageLevel;

	voltageLevel = (sample * (vcc/2)) / (frontendGain*scope_gain*TOP);
	if (virtualParent->driver->deviceMode != 7) voltageLevel += voltage_ref;
#ifdef INVERT_MM
	if (virtualParent->driver->deviceMode == 7) voltageLevel *= -1;
#endif

	if (AC)
	{
		voltageLevel -= virtualParent->currentVmean; //This is old (1 frame in past) value and might not be good for signals with large variations in DC level (although the cap should filter that anyway)??
	}
	return voltageLevel;
}

short isoBuffer::inverseSampleConvert(double voltageLevel, int TOP, bool AC) const
{
	double scope_gain = (double)(virtualParent->driver->scopeGain);
	short sample;

	if (AC)
	{
		// This is old (1 frame in past) value and might not be good for signals with
		// large variations in DC level (although the cap should filter that anyway)??
		voltageLevel += virtualParent->currentVmean;
	}
#ifdef INVERT_MM
	if (virtualParent->driver->deviceMode == 7) voltageLevel *= -1;
#endif
	if (virtualParent->driver->deviceMode != 7) voltageLevel -= voltage_ref;

	//voltageLevel = (sample * (vcc/2)) / (frontendGain*scope_gain*TOP);
	sample = (voltageLevel * (frontendGain*scope_gain*TOP))/(vcc/2);
	return sample;
}

#ifdef INVERT_MM
constexpr auto X0_COMP_FTOR = std::greater<int> {};
constexpr auto X1_X2_COMP_FTOR = std::less<int> {};
#else
constexpr auto X0_COMP_FTOR = std::less<int> {};
constexpr auto X1_X2_COMP_FTOR = std::greater<int> {};
#endif

template<typename Function>
int isoBuffer::capSample(int offset, int target, double seconds, double value, Function comp)
{
	int samples = seconds * samplesPerSecond;

	if (back < samples + offset) return -1;

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

// For capacitance measurement. x0, x1 and x2 are all various time points used to find the RC coefficient.
int isoBuffer::cap_x0fromLast(double seconds, double vbot)
{
	return capSample(0, kSamplesSeekingCap, seconds, vbot, X0_COMP_FTOR);
}

int isoBuffer::cap_x1fromLast(double seconds, int x0, double vbot)
{
	return capSample(-x0, kSamplesSeekingCap, seconds, vbot, X1_X2_COMP_FTOR);
}

int isoBuffer::cap_x2fromLast(double seconds, int x1, double vtop)
{
	return capSample(-x1, kSamplesSeekingCap, seconds, vtop, X1_X2_COMP_FTOR);
}

// NOTE: type appears to be unused
void isoBuffer::serialManage(double baudRate, int type, UartParity parity)
{
	//Types:
	// 0 - standard UART, no parity
	// 1 - standard UART, with parity bit
	// 100 - I2C
	if (decoder == NULL)
	{
		decoder = new uartStyleDecoder(this);
		// TODO: Look into using the type safe version of connect.
		// NOTE: I believe Qt has a type-safe version of this, without the macros and the
		// explicit signature and stuff, i think it uses member-function pointers instead.
		connect(decoder, SIGNAL(wireDisconnected(int)), virtualParent, SLOT(serialNeedsDisabling(int)));
	}
	if (stopDecoding)
	{
		decoder->updateTimer->start(CONSOLE_UPDATE_TIMER_PERIOD);
		stopDecoding = false;
	}
	decoder->setParityMode(parity);
	decoder->serialDecode(baudRate);
}

