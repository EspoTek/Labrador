#ifndef USBDRIVER_H
#define USBDRIVER_H

#include <QWidget>
#include <QLabel>

class usbDriver : public QLabel
{
    Q_OBJECT
public:
    explicit usbDriver(QLabel *parent = 0);

signals:

public slots:
};

#endif // USBDRIVER_H
