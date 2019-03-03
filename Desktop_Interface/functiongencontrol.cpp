#include "functiongencontrol.h"
#include "platformspecific.h"


functionGenControl::functionGenControl(QWidget *parent) : QLabel(parent)
{
    this->hide();
}

void functionGenControl::waveformName_CH1(QString newName)
{
	waveformName<6>(newName, CH1, 0, [](QString const& str){return str.toLocal8Bit(); });
}

void functionGenControl::freqUpdate_CH1(double newFreq){
    qDebug() << "newFreq = " << newFreq;
	CH1.freq = newFreq;
    functionGenToUpdate(0, this);
}

void functionGenControl::amplitudeUpdate_CH1(double newAmplitude){
    qDebug() << "newAmplitude = " << newAmplitude;
	CH1.amplitude = newAmplitude;
    functionGenToUpdate(0, this);
}

void functionGenControl::offsetUpdate_CH1(double newOffset){
    qDebug() << "newOffset = " << newOffset;
	CH1.offset = newOffset;
    functionGenToUpdate(0, this);
}

void functionGenControl::waveformName_CH2(QString newName)
{
	waveformName<5>(newName, CH2, 1, [](QString const& str){ return str.toLatin1(); });
}

void functionGenControl::freqUpdate_CH2(double newFreq){
    qDebug() << "newFreq2 = " << newFreq;
	CH2.freq = newFreq;
    functionGenToUpdate(1, this);
}

void functionGenControl::amplitudeUpdate_CH2(double newAmplitude){
    qDebug() << "newAmplitude2 = " << newAmplitude;
	CH2.amplitude = newAmplitude;
    functionGenToUpdate(1, this);
}

void functionGenControl::offsetUpdate_CH2(double newOffset){
    qDebug() << "newOffset2 = " << newOffset;
	CH2.offset = newOffset;
    functionGenToUpdate(1, this);
}

template<int LengthStringSize, typename Lambda>
void functionGenControl::waveformName(QString newName, ChannelData& channel, int channelID, Lambda encode)
{
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
    for (int i=0;i<channel.length;i++){
        sscanf(dataStringCurrent, "%d", &dummy);
        dataStringCurrent += strcspn(dataStringCurrent, "\t") + 1;
        channel.samples[i] = uint8_t(dummy);
    }

#else
    QString directory = QCoreApplication::applicationDirPath();

    directory.append("/waveforms/");
    directory.append(newName);
    QByteArray temp = encode(directory);
    char *fileName = temp.data();

    qDebug() << "opening" << fileName;
    FILE *fptr = fopen(fileName, "r");
        if (fptr==NULL){
            qFatal("%s could not be opened!", fileName);
        }

    char lengthString[LengthStringSize];
    fgets(lengthString, 5, fptr);
    sscanf(lengthString, "%d", &channel.length);

    char divisibilityString[LengthStringSize];
    //Bit of bullshit to deal with CRLF line endings on Mac.
    do fgets(divisibilityString, 5, fptr);
    while ((divisibilityString[0] == '\r') || (divisibilityString[0] == '\n'));
    sscanf(divisibilityString, "%d", &channel.divisibility);

    qDebug() << "Length = " << channel.length;
    qDebug() << "Divisibility = " << channel.divisibility;

	channel.samples.resize(channel.length);

    char *dataString = (char *) malloc(channel.length*5+1);
    fgets(dataString, channel.length*5+1, fptr);

    int dummy;
    char *dataStringCurrent = dataString;
    for (int i=0;i<channel.length;i++){
        sscanf(dataStringCurrent, "%d", &dummy);
        dataStringCurrent += strcspn(dataStringCurrent, "\t") + 1;
        channel.samples[i] = uint8_t(dummy);
    }

    free(dataString);
    fclose(fptr);
#endif

    setMaxFreq_CH1(DAC_SPS/(channel.length>>(channel.divisibility-1)));
    setMinFreq_CH1((double) CLOCK_FREQ/1024/65535/channel.length);
    functionGenToUpdate(channelID, this);
}


