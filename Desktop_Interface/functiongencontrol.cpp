#include "functiongencontrol.h"
#include "platformspecific.h"


functionGenControl::functionGenControl(QWidget *parent) : QLabel(parent)
{
    this->hide();
}

void functionGenControl::waveformName_CH1(QString newName)
{
	waveformName(newName, 0);
}

void functionGenControl::freqUpdate_CH1(double newFreq)
{
	freqUpdate(newFreq, 0);
}

void functionGenControl::amplitudeUpdate_CH1(double newAmplitude)
{
	amplitudeUpdate(newAmplitude, 0);
}

void functionGenControl::offsetUpdate_CH1(double newOffset)
{
	offsetUpdate(newOffset, 0);
}


void functionGenControl::waveformName_CH2(QString newName)
{
	waveformName(newName, 1);
}

void functionGenControl::freqUpdate_CH2(double newFreq)
{
	freqUpdate(newFreq, 1);
}

void functionGenControl::amplitudeUpdate_CH2(double newAmplitude)
{
	amplitudeUpdate(newAmplitude, 1);
}

void functionGenControl::offsetUpdate_CH2(double newOffset)
{
	offsetUpdate(newOffset, 1);
}


void functionGenControl::waveformName(QString newName, int channelID)
{
	ChannelData& channel = channels[channelID];

    qDebug() << "newName = " << newName;
    newName.append(".tlw");

#ifdef PLATFORM_ANDROID
    QString waveformFilePath("assets:/waveforms/");
    waveformFilePath.append(newName);

    QFile fptr(waveformFilePath);
    bool success = fptr.open(QIODevice::ReadOnly);

    QByteArray line;
    char lengthString[16];
    char divisibilityString[16];

    line = fptr.readLine();
    strcpy(lengthString, line.data());
    sscanf(lengthString, "%d", &channel.length);
    qDebug() << "lengthString" << lengthString;

    line = fptr.readLine();
    strcpy(divisibilityString, line.data());
    sscanf(divisibilityString, "%d", &channel.divisibility);
    qDebug() << "divisibilityString" << divisibilityString;

    qDebug() << "Length = " << channel.length;
    qDebug() << "Divisibility = " << channel.divisibility;

    QByteArray remainingData = fptr.readAll();
    char *dataString = remainingData.data();

	channel.samples.resize(channel.length);

    int dummy;
    char *dataStringCurrent = dataString;
    for (int i = 0; i < channel.length; i++)
	{
        sscanf(dataStringCurrent, "%d", &dummy);
        dataStringCurrent += strcspn(dataStringCurrent, "\t") + 1;
        channel.samples[i] = uint8_t(dummy);
    }

#else

    QByteArray filePath = QCoreApplication::applicationDirPath()
		.append("/waveforms/").append(newName).toUtf8();

    qDebug() << "opening" << filePath;

    FILE *fptr = fopen(filePath.constData(), "r");
    if (fptr == NULL)
        qFatal("%s could not be opened!", filePath.constData());

    char lengthString[16];
    fgets(lengthString, 5, fptr);
    sscanf(lengthString, "%d", &channel.length);

    char divisibilityString[16];
    //Bit of bullshit to deal with CRLF line endings on Mac.
    do
	{
		fgets(divisibilityString, 5, fptr);
	}
	while ((divisibilityString[0] == '\r') || (divisibilityString[0] == '\n'));

    sscanf(divisibilityString, "%d", &channel.divisibility);

    qDebug() << "Length = " << channel.length;
    qDebug() << "Divisibility = " << channel.divisibility;

	channel.samples.resize(channel.length);

    char *dataString = (char *) malloc(channel.length*5+1);
    fgets(dataString, channel.length*5+1, fptr);

    int dummy;
    char *dataStringCurrent = dataString;
    for (int i = 0; i < channel.length; i++)
	{
        sscanf(dataStringCurrent, "%d", &dummy);
        dataStringCurrent += strcspn(dataStringCurrent, "\t") + 1;
        channel.samples[i] = uint8_t(dummy);
    }

    free(dataString);
    fclose(fptr);
#endif

	double newMaxFreq = DAC_SPS / (channel.length >> (channel.divisibility - 1));
	double newMinFreq = double(CLOCK_FREQ) / 1024.0 / 65535.0 / channel.length;

	// NOTE: Not very clean... Not sure what to do about it.
	// I guess the "right thing" would be to have a Channel QObject class with its
	// own signals and slots, or have a single setMaxFreq signal with channelID as
	// an argument. Either solution would require changes in other places in the
	// codebase so this will have to do for now.
	if (channelID == 0)
	{
	    setMaxFreq_CH1(newMaxFreq);
	    setMinFreq_CH1(newMinFreq);
	}
	else
	{
	    setMaxFreq_CH2(newMaxFreq);
	    setMinFreq_CH2(newMinFreq);
	}

    functionGenToUpdate(channelID, this);
}

void functionGenControl::freqUpdate(double newFreq, int channelID)
{
	qDebug() << "newFreq" << channelID << " = " << newFreq;
	channels[channelID].freq = newFreq;
	functionGenToUpdate(channelID, this);
}

void functionGenControl::amplitudeUpdate(double newAmplitude, int channelID)
{
	qDebug() << "newAmplitude" << channelID << " = " << newAmplitude;
	channels[channelID].amplitude = newAmplitude;
	functionGenToUpdate(channelID, this);
}

void functionGenControl::offsetUpdate(double newOffset, int channelID)
{
	qDebug() << "newOffset" << channelID << " = " << newOffset;
	channels[channelID].offset = newOffset;
	functionGenToUpdate(channelID, this);
}

