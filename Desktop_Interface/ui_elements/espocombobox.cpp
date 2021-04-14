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
#ifdef PLATFORM_ANDROID
    QFile qt_list("assets:/waveforms/_list.wfl");
    bool success = qt_list.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!success){
        qFatal("Could not load _list.wfl");
    }

    char nameBuffer[255];
    QStringList *newNames = new QStringList();

    while (!qt_list.atEnd()) {
        QByteArray line = qt_list.readLine();
        strcpy(nameBuffer, line.data());
        strtok(nameBuffer, "\n\r");
        newNames->append(nameBuffer);
        qDebug() << nameBuffer;
    }
    this->addItems(*(newNames));
    delete newNames;
    qt_list.close();
#else
    QString dirString = QCoreApplication::applicationDirPath();
    dirString.append("/waveforms/_list.wfl");
    QByteArray array = dirString.toLocal8Bit();
    char* buffer = array.data();
    //qDebug() << buffer;

    qDebug() << "Attempting to open" << dirString;

    FILE *listPtr = fopen(buffer, "r");
    QStringList *newNames = new QStringList();
    char nameBuffer[255];

    if(listPtr == NULL){
        qWarning("Could not load _list.wfl");
        return;
    }

    while (fgets(nameBuffer,256,listPtr) !=NULL){
        qDebug() << "nameBuffer = " << nameBuffer;
        strtok(nameBuffer, "\n\r");
        newNames->append(nameBuffer);
    }
    this->addItems(*(newNames));
    delete newNames;

    fclose(listPtr);
#endif
    qDebug() << "List loaded!!";
}
