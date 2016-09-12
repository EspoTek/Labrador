#include "functiongencontrol.h"

functionGenControl::functionGenControl(QWidget *parent) : QLabel(parent)
{
    this->hide();
    samples_CH1 = (unsigned char *) malloc(0);
    samples_CH2 = (unsigned char *) malloc(0);

}

void functionGenControl::waveformName_CH1(QString newName)
{
    qDebug() << "newName = " << newName;
    newName.append(".tlw");

    QDir *dir = new QDir();
    QString directory = dir->currentPath();

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
    sscanf(lengthString, "%d", &length_CH1);

    char divisibilityString[5];
    fgets(divisibilityString, 5, fptr);
    sscanf(divisibilityString, "%d", &divisibility_CH1);

    qDebug() << "Length = " << length_CH1;
    qDebug() << "Divisibility = " << divisibility_CH1;

    free(samples_CH1);
    samples_CH1 = (unsigned char *) malloc(length_CH1);

    char *dataString = (char *) malloc(length_CH1*5+1);
    fgets(dataString, length_CH1*5+1, fptr);

    int dummy;
    char *dataStringCurrent = dataString;
    for (int i=0;i<length_CH1;i++){
        sscanf(dataStringCurrent, "%d", &dummy);
        dataStringCurrent += strcspn(dataStringCurrent, "\t") + 1;
        samples_CH1[i] = (unsigned char) dummy;
    }

    free(dataString);
    fclose(fptr);
    setMaxFreq_CH1(DAC_SPS/(length_CH1>>(divisibility_CH1-1)));
    setMinFreq_CH1((double) CLOCK_FREQ/1024/65535/length_CH1);
    functionGenToUpdate(0, this);
}

void functionGenControl::freqUpdate_CH1(double newFreq){
    qDebug() << "newFreq = " << newFreq;
    freq_CH1 = newFreq;
    functionGenToUpdate(0, this);
}

void functionGenControl::amplitudeUpdate_CH1(double newAmplitude){
    qDebug() << "newAmplitude = " << newAmplitude;
    amplitude_CH1 = newAmplitude;
    functionGenToUpdate(0, this);
}

void functionGenControl::offsetUpdate_CH1(double newOffset){
    qDebug() << "newOffset = " << newOffset;
    offset_CH1 = newOffset;
    functionGenToUpdate(0, this);
}

void functionGenControl::waveformName_CH2(QString newName)
{
    qDebug() << "newName = " << newName;
    newName.append(".tlw");

    QDir *dir = new QDir();
    QString directory = dir->currentPath();

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
    sscanf(lengthString, "%d", &length_CH2);

    char divisibilityString[5];
    fgets(divisibilityString, 5, fptr);
    sscanf(divisibilityString, "%d", &divisibility_CH2);

    qDebug() << "Length = " << length_CH2;
    qDebug() << "Divisibility = " << divisibility_CH2;

    free(samples_CH2);
    samples_CH2 = (unsigned char *) malloc(length_CH2);

    char *dataString = (char *) malloc(length_CH2*5+1);
    fgets(dataString, length_CH2*5+1, fptr);

    int dummy;
    char *dataStringCurrent = dataString;
    for (int i=0;i<length_CH2;i++){
        sscanf(dataStringCurrent, "%d", &dummy);
        dataStringCurrent += strcspn(dataStringCurrent, "\t") + 1;
        samples_CH2[i] = (unsigned char) dummy;
    }

    free(dataString);
    fclose(fptr);
    setMaxFreq_CH2(DAC_SPS/(length_CH2>>(divisibility_CH2-1)));
    setMinFreq_CH2((double) CLOCK_FREQ/1024/65535/length_CH2);
    functionGenToUpdate(1, this);
}

void functionGenControl::freqUpdate_CH2(double newFreq){
    qDebug() << "newFreq = " << newFreq;
    freq_CH2 = newFreq;
    functionGenToUpdate(1, this);
}

void functionGenControl::amplitudeUpdate_CH2(double newAmplitude){
    qDebug() << "newAmplitude = " << newAmplitude;
    amplitude_CH2 = newAmplitude;
    functionGenToUpdate(1, this);
}

void functionGenControl::offsetUpdate_CH2(double newOffset){
    qDebug() << "newOffset = " << newOffset;
    offset_CH2 = newOffset;
    functionGenToUpdate(1, this);
}
