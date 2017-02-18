#include "voltagespinbox.h"

voltageSpinBox::voltageSpinBox(QWidget *parent) : QDoubleSpinBox(parent)
{

}

void voltageSpinBox::setMax(double newMax){
    this->setMaximum(newMax);
}

void voltageSpinBox::setMin(double newMin){
    this->setMinimum(newMin);
}
