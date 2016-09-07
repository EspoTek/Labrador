#ifndef DEVICECONNECTEDDISPLAY_H
#define DEVICECONNECTEDDISPLAY_H

#include <QWidget>
#include <QLabel>
#include <QDebug>

class deviceConnectedDisplay : public QLabel
{
    Q_OBJECT
public:
    explicit deviceConnectedDisplay(QWidget *parent = 0);

signals:

public slots:
    void connectedStatusChanged(bool status);
};

#endif // DEVICECONNECTEDDISPLAY_H
