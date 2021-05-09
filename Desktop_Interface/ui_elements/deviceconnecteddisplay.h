#ifndef DEVICECONNECTEDDISPLAY_H
#define DEVICECONNECTEDDISPLAY_H

#include <QWidget>
#include <QLabel>
#include <QDebug>

//deviceConnectedDisplay simply displays the "device connected" message.

class deviceConnectedDisplay : public QLabel
{
    Q_OBJECT
public:
    explicit deviceConnectedDisplay(QWidget *parent = nullptr);
signals:
public slots:
    void connectedStatusChanged(bool status);
    void flashingFirmware(void);
};

#endif // DEVICECONNECTEDDISPLAY_H
