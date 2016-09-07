#include "espocombobox.h"

espoComboBox::espoComboBox(QWidget *parent) : QComboBox(parent)
{

}


void espoComboBox::readWaveformList(void)
{
    FILE *listPtr = fopen("C:/kfvcc/waveforms/_list.wfl", "r");
    QStringList *newNames = new QStringList();
    char nameBuffer[255];

    if(listPtr == NULL){
        qFatal("Could not load _list.wfl");
    }

    while (fgets(nameBuffer,256,listPtr) !=NULL){
        qDebug() << "nameBuffer = " << nameBuffer;
        strtok(nameBuffer, "\n");
        newNames->append(nameBuffer);
    }
    this->addItems(*(newNames));
    delete newNames;
    fclose(listPtr);
}
