#include "espospinbox.h"

espoSpinBox::espoSpinBox(QWidget *parent) : QDoubleSpinBox(parent)
{
    //connect(this, SIGNAL(valueChanged(double)), this, SLOT(changeStepping(double)));
}

QString espoSpinBox::textFromValue(double value) const{
    QString windowText;
    if (value == 0){
        QTextStream(&windowText) << value;
        return windowText;
    }
    if (value >= 1000000){
        QTextStream(&windowText) << value/1000000 << "M";
        return windowText;
    }
    if (value >= 1000){
        QTextStream(&windowText) << value/1000 << "k";
        return windowText;
    }
    if (value >= 1){
        QTextStream(&windowText) << value;
        return windowText;
    }
    if (value >= 1/1000){
        QTextStream(&windowText) << value * 1000 << "m";
        return windowText;
    }
    if (value >= 1/1000000){
        QTextStream(&windowText) << value * 1000000 << "u";
        return windowText;
    }
    return "invalid";
}

void espoSpinBox::maximumChanged(double linked){
    this->setMaximum(9.6-linked);
}

void espoSpinBox::setMax(double newMax){
    this->setMaximum(newMax);
}

void espoSpinBox::setMin(double newMin){
    this->setMinimum(newMin);
}

void espoSpinBox::changeStepping(double value){
    double roundval = pow(10.0, floor(log10(value)));  //http://stackoverflow.com/questions/22491505/how-to-round-down-to-the-nearest-power-of-10
    roundval = (roundval == 0) ? 0.1 : roundval/10;
    setSingleStep(roundval);
}
