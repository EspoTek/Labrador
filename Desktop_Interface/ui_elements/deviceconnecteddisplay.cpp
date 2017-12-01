#include "deviceconnecteddisplay.h"
#include "platformspecific.h"

deviceConnectedDisplay::deviceConnectedDisplay(QWidget *parent) : QLabel(parent)
{
    this->setText("Device Not Connected!");
    this->setStyleSheet("QLabel { color:red; }");
}

void deviceConnectedDisplay::connectedStatusChanged(bool status){
    qDebug() << "deviceConnectedDisplay::connectedStatusChanged running!";
    if(status){
        this->setText("Device Connected");
        this->setStyleSheet("QLabel { color:black; }");
    }
    else{
        this->setText("Device Not Connected!");
        this->setStyleSheet("QLabel { color:red; }");
    }
    #ifdef PLATFORM_ANDROID
        this->setVisible(!status);
    #endif
}

void deviceConnectedDisplay::flashingFirmware(void){
    qDebug() << "deviceConnectedDisplay::flashingFirmware";
    this->setText("Flashing Device Firmware");
    this->setStyleSheet("QLabel { color:green; }");
}
