#include "timedtickbox.h"

timedTickBox::timedTickBox(QWidget *parent) : QCheckBox(parent)
{
    timer = new QTimer();
    timer->setTimerType(Qt::PreciseTimer);
    timer->start(timerLength);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()));

}

void timedTickBox::resetTimer(){
    timer->stop();
    if(timerEnabled) timer->start(timerLength);
}

void timedTickBox::timerTick(){
    this->setChecked(true);
    timer->stop();
}

void timedTickBox::enableTimer(bool enabled){
    timerEnabled = enabled;
}
