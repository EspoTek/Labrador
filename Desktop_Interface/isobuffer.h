#ifndef ISOBUFFER_H
#define ISOBUFFER_H

// TODO: Make object macros constexprs or globals
// TODO: Move headers used only in implementation to isobuffer.cpp
#include <QWidget>
#include <QString>
#include <QByteArray>
#include <QDebug>
#include <QTimer>
#include <QPlainTextEdit>
#include <QDir>
#include <QFile>

#include "xmega.h"
#include "desktop_settings.h"
#include "genericusbdriver.h"

class isoDriver;
class uartStyleDecoder;
enum class UartParity : uint8_t;

// isoBuffer is a generic class that enables O(1) read times (!!!) on all
// read/write operations, while maintaining a huge buffer size.
// Imagine it as a circular buffer, but with access functions specifically
// designed for isochronous data from an Xmega.

constexpr auto CONSOLE_UPDATE_TIMER_PERIOD = ISO_PACKETS_PER_CTX * 4;

// TODO: Make private what should be private
// TODO: Add m_ prefix to member variables
// TODO: Change integer types to cstdint types
class isoBuffer : public QWidget
{
	Q_OBJECT
public:
	// TODO: Add consoles as constructor arguments
	isoBuffer(QWidget* parent = 0, int bufferLen = 0, isoDriver* caller = 0, unsigned char channel_value = 0);
	// TODO?: Add a destructor

//	Basic buffer operations
	short bufferAt(int idx) const;
	void insertIntoBuffer(short item);
	void clearBuffer();
	void gainBuffer(int gain_log);

// Advanced buffer operations
private:
	template<typename T, typename Function>
	void writeBuffer(T* data, int len, int TOP, Function transform);
public:
	void writeBuffer_char(char* data, int len);
	void writeBuffer_short(short* data, int len);

	// TODO: Change return value to unique_ptr
	short* readBuffer(double sampleWindow, int numSamples, bool singleBit, double delayOffset);

//	file I/O
	bool maybeOutputSampleToFile(double convertedSample);
	double sampleConvert(short sample, int TOP, bool AC) const;
	short inverseSampleConvert(double voltageLevel, int TOP, bool AC) const;

private:
	template<typename Function>
	int capSample(int offset, int target, double seconds, double value, Function comp);
public:
	int cap_x0fromLast(double seconds, double vbot);
	int cap_x1fromLast(double seconds, int x0, double vbot);
	int cap_x2fromLast(double seconds, int x1, double vtop);
	void serialManage(double baudRate, UartParity parity);

// ---- MEMBER VARIABLES ----

//	Presentantion?
// NOTE: it seems like these are never initialized but they are used as though they were...
	QPlainTextEdit* m_console1;
	QPlainTextEdit* m_console2;
	unsigned char m_channel = 255;
	bool m_serialAutoScroll = true;

// Conversion And Sampling
	double m_voltage_ref = 1.65;
	double m_frontendGain = (R4 / (R3 + R4));
	int m_samplesPerSecond;
	int m_sampleRate_bit;

//	Internal Storage
	int m_back = 0;
	int m_insertedCount = 0;
	int m_bufferEnd;
// TODO: Change buffer to be a unique_ptr
	short* m_buffer;
	short* m_readData = NULL;

//	UARTS decoding
	uartStyleDecoder* m_decoder = NULL;
	// TODO: change this to keepDecoding
	bool m_stopDecoding = false;
private:
//	File I/O
	bool m_fileIOEnabled = false;
	FILE* m_fptr = NULL;
	QFile* m_currentFile;
	int m_fileIO_maxIncrementedSampleValue;
	int m_fileIO_sampleCount;
	qulonglong m_fileIO_max_file_size;
	qulonglong m_fileIO_numBytesWritten;
	unsigned int m_currentColumn = 0;
	isoDriver* m_virtualParent;
	double m_average_sample_temp;
signals:
	void fileIOinternalDisable();
public slots:
	void enableFileIO(QFile* file, int samplesToAverage, qulonglong max_file_size);
	void disableFileIO();
};

#endif // ISOBUFFER_H
