#ifndef ISOBUFFER_H
#define ISOBUFFER_H

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

#define CONSOLE_UPDATE_TIMER_PERIOD (ISO_PACKETS_PER_CTX * 4)

// TODO: Make private what should be private
class isoBuffer : public QWidget
{
	Q_OBJECT
public:
	isoBuffer(QWidget *parent = 0, int bufferLen = 0, isoDriver *caller = 0, unsigned char channel_value = 0);
	// TODO?: Add a destructor

	//Generic Functions
	void openFile(QString newFile);

//	Basic buffer operations
	short bufferAt(int idx) const;
	void insertIntoBuffer(short item);
	void clearBuffer();
	void gainBuffer(int gain_log);
	void glitchInsert(short type); // NO-OP
	
// Advanced buffer operations
	void writeBuffer_char(char *data, int len);
	void writeBuffer_short(short *data, int len);

	short *readBuffer(double sampleWindow, int numSamples, bool singleBit, double delayOffset);
	
//	file I/O
	bool maybeOutputSampleToFile(double convertedSample);
	double sampleConvert(short sample, int TOP, bool AC) const;
	short inverseSampleConvert(double voltageLevel, int TOP, bool AC) const;

	int cap_x0fromLast(double seconds, double vbot);
	int cap_x1fromLast(double seconds, int x0, double vbot);
	int cap_x2fromLast(double seconds, int x1, double vtop);
	void serialManage(double baudRate, int type, UartParity parity);

// ---- MEMBER VARIABLES ----

//	Presentantion?
// NOTE: it seems like these are never initialized but they are used as though they were...
	QPlainTextEdit *console1, *console2;
	unsigned char channel = 255;
	bool serialAutoScroll = true;

// Conversion And Sampling
	double voltage_ref = 1.65;
	double frontendGain = (R4 / (R3 + R4));
	int samplesPerSecond;
	int sampleRate_bit;

//	Internal Storage
	int back = 0;
	int bufferEnd;
	short *buffer;
	short *readData = NULL;

//	UARTS decoding
	uartStyleDecoder *decoder = NULL;
	// TODO: change this to keepDecoding
	bool stopDecoding = false;
private:
//	File I/O
	bool fileIOEnabled = false;
	FILE* fptr = NULL;
	QFile *currentFile;
	int fileIO_maxIncrementedSampleValue;
	int fileIO_sampleCount;
	qulonglong fileIO_max_file_size;
	qulonglong fileIO_numBytesWritten;
	unsigned int currentColumn = 0;
	isoDriver *virtualParent;
	double average_sample_temp;
signals:
	void fileIOinternalDisable();
public slots:
	void enableFileIO(QFile *file, int samplesToAverage, qulonglong max_file_size);
	void disableFileIO();
};

#endif // ISOBUFFER_H
