#ifndef TIMEDTICKBOX_H
#define TIMEDTICKBOX_H

#include <QCheckBox>
#include <QTimer>
#include <QDebug>

//timedTickBox is used to re-lock the power supply after a few seconds.
//It's just a tickbox with a timer on it.

class timedTickBox : public QCheckBox
{
    Q_OBJECT
public:
    explicit timedTickBox(QWidget *parent = 0);
    bool timerEnabled = true;
    int timerLength = 7500;
    QTimer *timer = NULL;

signals:

public slots:
    void resetTimer();
    void timerTick();
    void enableTimer(bool enabled);
};

#endif // TIMEDTICKBOX_H
