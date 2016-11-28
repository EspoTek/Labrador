#ifndef ESPOSPINBOX_H
#define ESPOSPINBOX_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <math.h>

//espoSpinBox is a subclass of QSpinbox.  It can talk to other espoSpinBoxes and change their min/max values.

class espoSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit espoSpinBox(QWidget *parent = 0);
private:
    QString textFromValue(double value) const;
signals:

public slots:
    void maximumChanged(double linked);
    void setMax(double newMax);
    void setMin(double newMin);
    void changeStepping(double value);
};

#endif // ESPOSPINBOX_H
