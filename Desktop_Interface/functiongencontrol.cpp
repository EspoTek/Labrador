#include "functiongencontrol.h"
#include "platformspecific.h"


functionGenControl::functionGenControl(QWidget *parent) : QLabel(parent)
{
    this->hide();
}

void functionGenControl::waveformName_CH1(QString newName)
{
    qDebug() << "newName = " << newName;
    newName.append(".tlw");

    //QDir *dir = new QDir();
    //QString directory = dir->currentPath();

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
    sscanf(lengthString, "%d", &CH1.length);
    qDebug() << "lengthString" << lengthString;

    line = fptr.readLine();
    strcpy(divisibilityString, line.data());
    sscanf(divisibilityString, "%d", &CH1.divisibility);
    qDebug() << "divisibilityString" << divisibilityString;

    qDebug() << "Length = " << CH1.length;
    qDebug() << "Divisibility = " << CH1.divisibility;

    QByteArray remainingData = fptr.readAll();
    char *dataString = remainingData.data();

    free(CH1.samples);
    CH1.samples = (unsigned char *) malloc(CH1.length);

    int dummy;
    char *dataStringCurrent = dataString;
    for (int i=0;i<CH1.length;i++){
        sscanf(dataStringCurrent, "%d", &dummy);
        dataStringCurrent += strcspn(dataStringCurrent, "\t") + 1;
        CH1.samples[i] = (unsigned char) dummy;
    }

#else
    QString directory = QCoreApplication::applicationDirPath();

    directory.append("/waveforms/");
    directory.append(newName);
    QByteArray temp = directory.toLocal8Bit();
    char *fileName = temp.data();

    qDebug() << "opening" << fileName;
    FILE *fptr = fopen(fileName, "r");
        if (fptr==NULL){
            qFatal("%s could not be opened!", fileName);
        }

    char lengthString[6];
    fgets(lengthString, 5, fptr);
    qDebug() << lengthString;
    sscanf(lengthString, "%d", &CH1.length);

    char divisibilityString[6];
    //Bit of bullshit to deal with CRLF line endings on Mac.
    do fgets(divisibilityString, 5, fptr);
    while ((divisibilityString[0] == '\r') || (divisibilityString[0] == '\n'));
    sscanf(divisibilityString, "%d", &CH1.divisibility);

    qDebug() << "Length = " << CH1.length;
    qDebug() << "Divisibility = " << CH1.divisibility;

    free(CH1.samples);
    CH1.samples = (unsigned char *) malloc(CH1.length);

    char *dataString = (char *) malloc(CH1.length*5+1);
    fgets(dataString, CH1.length*5+1, fptr);

    int dummy;
    char *dataStringCurrent = dataString;
    for (int i=0;i<CH1.length;i++){
        sscanf(dataStringCurrent, "%d", &dummy);
        dataStringCurrent += strcspn(dataStringCurrent, "\t") + 1;
        CH1.samples[i] = (unsigned char) dummy;
    }

    free(dataString);
    fclose(fptr);
#endif

    setMaxFreq_CH1(DAC_SPS/(CH1.length>>(CH1.divisibility-1)));
    setMinFreq_CH1((double) CLOCK_FREQ/1024/65535/CH1.length);
    functionGenToUpdate(0, this);
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
    sscanf(lengthString, "%d", &CH2.length);
    qDebug() << "lengthString" << lengthString;

    line = fptr.readLine();
    strcpy(divisibilityString, line.data());
    sscanf(divisibilityString, "%d", &CH2.divisibility);
    qDebug() << "divisibilityString" << divisibilityString;

    qDebug() << "Length = " << CH2.length;
    qDebug() << "Divisibility = " << CH2.divisibility;

    QByteArray remainingData = fptr.readAll();
    char *dataString = remainingData.data();

    free(CH2.samples);
    CH2.samples = (unsigned char *) malloc(CH2.length);

    int dummy;
    char *dataStringCurrent = dataString;
    for (int i=0;i<CH2.length;i++){
        sscanf(dataStringCurrent, "%d", &dummy);
        dataStringCurrent += strcspn(dataStringCurrent, "\t") + 1;
        CH2.samples[i] = (unsigned char) dummy;
    }
#else
    QString directory = QCoreApplication::applicationDirPath();

    directory.append("/waveforms/");
    directory.append(newName);
    QByteArray temp = directory.toLatin1();
    char *fileName = temp.data();

    qDebug() << "opening" << fileName;
    FILE *fptr = fopen(fileName, "r");
        if (fptr==NULL){
            qFatal("%s could not be opened!", fileName);
        }

    char lengthString[5];
    fgets(lengthString, 5, fptr);
    sscanf(lengthString, "%d", &CH2.length);

    char divisibilityString[5];
    //Bit of bullshit to deal with CRLF line endings on Mac.
    do fgets(divisibilityString, 5, fptr);
    while ((divisibilityString[0] == '\r') || (divisibilityString[0] == '\n'));
    sscanf(divisibilityString, "%d", &CH2.divisibility);

    qDebug() << "Length = " << CH2.length;
    qDebug() << "Divisibility = " << CH2.divisibility;

    free(CH2.samples);
    CH2.samples = (unsigned char *) malloc(CH2.length);

    char *dataString = (char *) malloc(CH2.length*5+1);
    fgets(dataString, CH2.length*5+1, fptr);

    int dummy;
    char *dataStringCurrent = dataString;
    for (int i=0;i<CH2.length;i++){
        sscanf(dataStringCurrent, "%d", &dummy);
        dataStringCurrent += strcspn(dataStringCurrent, "\t") + 1;
        CH2.samples[i] = (unsigned char) dummy;
    }

    free(dataString);
    fclose(fptr);
#endif

    setMaxFreq_CH2(DAC_SPS/(CH2.length>>(CH2.divisibility-1)));
    setMinFreq_CH2((double) CLOCK_FREQ/1024/65535/CH2.length);
    functionGenToUpdate(1, this);
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

