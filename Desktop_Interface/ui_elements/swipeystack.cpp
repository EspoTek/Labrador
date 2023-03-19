#include "swipeystack.h"

swipeyStack::swipeyStack(QWidget *parent) : QStackedWidget(parent)
{
}

void swipeyStack::mousePressEvent(QMouseEvent *event){
    initial_x = event->globalX();
    initial_y = event->globalY();
    initial_epochTime = QDateTime::currentMSecsSinceEpoch();
    return;
}

void swipeyStack::mouseReleaseEvent(QMouseEvent *event){
        qint64 msecsPassed = QDateTime::currentMSecsSinceEpoch() - initial_epochTime;
        int x = event->globalX();
        int y = event->globalY();

        int deltaX = x - initial_x;
        int deltaY = y - initial_y;

        qDebug("TouchPoint moved [%d, %d] in %lldms", deltaX, deltaY, msecsPassed);

        if((msecsPassed < SWIPEYSTACK_MAX_DRAG_TIME) && (qAbs(deltaX) > SWIPEYSTACK_MIN_DELTAX)){
            if((qreal)deltaX/(qreal)msecsPassed > 1){
                qDebug() << "SWIPE RIGHT";
                cycleStack(-1);
            }
            if((qreal)deltaX/(qreal)msecsPassed < -1){
                qDebug() << "SWIPE LEFT";
                cycleStack(1);
            }
        }
        return;
    }

void swipeyStack::cycleStack(int delta){
    int idx = currentIndex();
    int cnt = count();
    if(!wrapEnabled){
        if((delta > 0) && ((idx + delta) > (cnt-1))){
            setCurrentIndex(cnt-1);
            return;
        }
        if((delta < 0) && ((idx + delta) < 0)){
            setCurrentIndex(0);
            return;
        }
    }
    if(idx == 0){
        idx = cnt;
    }
    setCurrentIndex((idx + delta) % cnt);
    return;
}

void swipeyStack::enableWrapping(bool enabled){
    wrapEnabled = enabled;
}
