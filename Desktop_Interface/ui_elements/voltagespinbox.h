#ifndef VOLTAGESPINBOX_H
#define VOLTAGESPINBOX_H

#include <QWidget>
#include <QSpinBox>

//Wrapper for the spinboxes on the "Enter Scope Range" dialog (Oscilloscope->Range->Enter Manually; shortcut is "M").
//It needs to exist in order to map the setMaximum() and setMinimum() functions for QDOubleSpinbox to slots.

class voltageSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit voltageSpinBox(QWidget *parent = nullptr);
    bool min = false;
signals:

public slots:
    void setMax(double newMax);
    void setMin(double newMin);
};

#endif // VOLTAGESPINBOX_H
