#include "functiongencontrol.h"
#include "platformspecific.h"


functionGenControl::functionGenControl(QWidget *parent) : QLabel(parent)
{
    this->hide();
}

void functionGenControl::waveformName_CH1(QString newName)
{
	waveformName(ChannelID::CH1, newName);
}

void functionGenControl::freqUpdate_CH1(double newFreq)
{
	freqUpdate(ChannelID::CH1, newFreq);
}

void functionGenControl::amplitudeUpdate_CH1(double newAmplitude)
{
	amplitudeUpdate(ChannelID::CH1, newAmplitude);
}

void functionGenControl::offsetUpdate_CH1(double newOffset)
{
	offsetUpdate(ChannelID::CH1, newOffset);
}


void functionGenControl::waveformName_CH2(QString newName)
{
	waveformName(ChannelID::CH2, newName);
}

void functionGenControl::freqUpdate_CH2(double newFreq)
{
	freqUpdate(ChannelID::CH2, newFreq);
}

void functionGenControl::amplitudeUpdate_CH2(double newAmplitude)
{
	amplitudeUpdate(ChannelID::CH2, newAmplitude);
}

void functionGenControl::offsetUpdate_CH2(double newOffset)
{
	offsetUpdate(ChannelID::CH2, newOffset);
}


functionGenControl::ChannelData& functionGenControl::getChannelData(ChannelID channelID)
{
	return channels[static_cast<int>(channelID)];
}

void functionGenControl::waveformName(ChannelID channelID, QString newName)
{
	ChannelData& channel = getChannelData(channelID);

    qDebug() << "newName = " << newName;
    newName.append(".tlw");

	int length;

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
    sscanf(lengthString, "%d", &length);
    qDebug() << "lengthString" << lengthString;

    line = fptr.readLine();
    strcpy(divisibilityString, line.data());
    sscanf(divisibilityString, "%d", &channel.divisibility);
    qDebug() << "divisibilityString" << divisibilityString;

    qDebug() << "Length = " << length;
    qDebug() << "Divisibility = " << channel.divisibility;

    QByteArray remainingData = fptr.readAll();
    char *dataString = remainingData.data();

	channel.samples.resize(length);

    int dummy;
    char *dataStringCurrent = dataString;
    for (int i = 0; i < length; i++)
	{
        sscanf(dataStringCurrent, "%d", &dummy);
        dataStringCurrent += strcspn(dataStringCurrent, "\t") + 1;
        channel.samples[i] = static_cast<uint8_t>(dummy);
    }

#else

    QByteArray filePath = QCoreApplication::applicationDirPath()
		.append("/waveforms/").append(newName).toLocal8Bit();

    qDebug() << "opening" << filePath;

    FILE *fptr = fopen(filePath.constData(), "r");
    if (fptr == NULL)
        qFatal("%s could not be opened!", filePath.constData());

    char lengthString[16];
    fgets(lengthString, 5, fptr);
    sscanf(lengthString, "%d", &length);

    char divisibilityString[16];
    //Bit of bullshit to deal with CRLF line endings on Mac.
    do
	{
		fgets(divisibilityString, 5, fptr);
	}
	while ((divisibilityString[0] == '\r') || (divisibilityString[0] == '\n'));

    sscanf(divisibilityString, "%d", &channel.divisibility);

    qDebug() << "Length = " << length;
    qDebug() << "Divisibility = " << channel.divisibility;

	channel.samples.resize(length);

    char *dataString = (char *) malloc(length*5+1);
    fgets(dataString, length*5+1, fptr);

    int dummy;
    char *dataStringCurrent = dataString;
    for (int i = 0; i < length; i++)
	{
        sscanf(dataStringCurrent, "%d", &dummy);
        dataStringCurrent += strcspn(dataStringCurrent, "\t") + 1;
        channel.samples[i] = static_cast<uint8_t>(dummy);
    }

    free(dataString);
    fclose(fptr);
#endif

	double newMaxFreq = DAC_SPS / (length >> (channel.divisibility - 1));
	double newMinFreq = double(CLOCK_FREQ) / 1024.0 / 65535.0 / length;

	// NOTE: Not very clean... Not sure what to do about it.
	// I guess the "right thing" would be to have a Channel QObject class with its
	// own signals and slots, or have a single setMaxFreq signal with channelID as
	// an argument. Either solution would require changes in other places in the
	// codebase so this will have to do for now.
	switch (channelID)
	{
	case ChannelID::CH1:
		setMaxFreq_CH1(newMaxFreq);
		setMinFreq_CH1(newMinFreq);
		break;
	case ChannelID::CH2:
		setMaxFreq_CH2(newMaxFreq);
		setMinFreq_CH2(newMinFreq);
		break;
	}

    functionGenToUpdate(channelID, this);
}

void functionGenControl::freqUpdate(ChannelID channelID, double newFreq)
{
	qDebug() << "newFreq" << int(channelID) << " = " << newFreq;
	getChannelData(channelID).freq = newFreq;
	functionGenToUpdate(channelID, this);
}

void functionGenControl::amplitudeUpdate(ChannelID channelID, double newAmplitude)
{
	qDebug() << "newAmplitude" << int(channelID) << " = " << newAmplitude;
	getChannelData(channelID).amplitude = newAmplitude;
	functionGenToUpdate(channelID, this);
}

void functionGenControl::offsetUpdate(ChannelID channelID, double newOffset)
{
	qDebug() << "newOffset" << int(channelID) << " = " << newOffset;
	getChannelData(channelID).offset = newOffset;
	functionGenToUpdate(channelID, this);
}

