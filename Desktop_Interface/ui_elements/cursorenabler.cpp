#include "cursorenabler.h"
#include "platformspecific.h"

cursorEnabler::cursorEnabler(QWidget *parent) : QLabel(parent)
{
    this->setVisible(false);
#ifdef PLATFORM_ANDROID
    this->m_turnedOn = false;
#endif
}

void cursorEnabler::setTurnedOn(bool enabled){
    m_turnedOn = enabled;
    #ifdef PLATFORM_ANDROID
        this->m_turnedOn = false;
    #endif
}

void cursorEnabler::clickDetected(QMouseEvent* event){
    if(m_turnedOn){
        if (event->button() == Qt::LeftButton)
        {
            tickHori(true);
        }
        else if (event->button() == Qt::RightButton)
        {
            tickVert(true);
        }
    }
    passOnSignal(event);
}
