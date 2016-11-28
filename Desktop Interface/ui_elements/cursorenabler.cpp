#include "cursorenabler.h"

cursorEnabler::cursorEnabler(QWidget *parent) : QLabel(parent)
{
    this->setVisible(0);
}

void cursorEnabler::setTurnedOn(bool enabled){
    turnedOn = enabled;
}

void cursorEnabler::clickDetected(QMouseEvent* event){
    if(turnedOn){
        if (event->button() == Qt::LeftButton){
            tickHori(1);
        }
        if (event->button() == Qt::RightButton){
            tickVert(1);
        }
    }
    passOnSignal(event);
}
