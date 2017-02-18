#include "espocombobox.h"

espoComboBox::espoComboBox(QWidget *parent) : QComboBox(parent)
{

}


void espoComboBox::readWaveformList(void)
{
    //This code gets the name of the current directory, regardless of platform.
    //This is so the interface knows where to find the waveform data
    //QDir *dir = new QDir();
    //qDebug() << dir->currentPath();
    QString dirString = QCoreApplication::applicationDirPath();
    dirString.append("/waveforms/_list.wfl");
    QByteArray array = dirString.toLocal8Bit();
    char* buffer = array.data();
    //qDebug() << buffer;

    FILE *listPtr = fopen(buffer, "r");
    QStringList *newNames = new QStringList();
    char nameBuffer[255];

    if(listPtr == NULL){
        qFatal("Could not load _list.wfl");
    }

    while (fgets(nameBuffer,256,listPtr) !=NULL){
        qDebug() << "nameBuffer = " << nameBuffer;
        strtok(nameBuffer, "\n\r");
        newNames->append(nameBuffer);
    }
    this->addItems(*(newNames));
    delete newNames;
    fclose(listPtr);
}
