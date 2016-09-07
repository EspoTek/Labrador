#include "deviceconnecteddisplay.h"

deviceConnectedDisplay::deviceConnectedDisplay(QWidget *parent) : QLabel(parent)
{

}

void deviceConnectedDisplay::connectedStatusChanged(bool status){
    qDebug() << "deviceConnectedDisplay::connectedStatusChanged running!";
    if(status){
        this->setText("Device Connected");
        this->setStyleSheet("QLabel { color:black; }");
    }
    else{
        this->setText("Device Not Detected!");
        this->setStyleSheet("QLabel { color:red; }");
    }
}
