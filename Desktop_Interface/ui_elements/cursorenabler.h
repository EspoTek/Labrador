#ifndef CURSORENABLER_H
#define CURSORENABLER_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

//cursorEnabler intercepts click events from the chart and allows automatic cursor drops to take place.

class cursorEnabler : public QLabel
{
    Q_OBJECT
public:
    explicit cursorEnabler(QWidget *parent = 0);
private:
    bool turnedOn = true;
signals:
    void tickHori(bool);
    void tickVert(bool);
    void passOnSignal(QMouseEvent* event);
public slots:
    void setTurnedOn(bool enabled);
    void clickDetected(QMouseEvent* event);
};

#endif // CURSORENABLER_H
