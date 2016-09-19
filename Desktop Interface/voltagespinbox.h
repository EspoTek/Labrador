#ifndef VOLTAGESPINBOX_H
#define VOLTAGESPINBOX_H

#include <QWidget>
#include <QSpinBox>

class voltageSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit voltageSpinBox(QWidget *parent = 0);
    bool min = false;
signals:

public slots:
    void setMax(double newMax);
    void setMin(double newMin);
};

#endif // VOLTAGESPINBOX_H
