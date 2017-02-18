#include "deviceconnecteddisplay.h"

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
}
