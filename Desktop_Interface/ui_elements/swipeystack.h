#ifndef SWIPEYSTACK_H
#define SWIPEYSTACK_H

#include <QStackedWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QDateTime>

#define SWIPEYSTACK_MIN_DELTAX 20
#define SWIPEYSTACK_MAX_DRAG_TIME 500


class swipeyStack : public QStackedWidget
{
    Q_OBJECT
public:
    explicit swipeyStack(QWidget *parent = 0);
private:
    int initial_x;
    int initial_y;
    qint64 initial_epochTime;
    bool wrapEnabled = true;
signals:

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enableWrapping(bool enabled);
    void cycleStack(int delta);
};

#endif // SWIPEYSTACK_H
