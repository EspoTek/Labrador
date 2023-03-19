#include "espospinbox.h"

espoSpinBox::espoSpinBox(QWidget *parent) : QDoubleSpinBox(parent)
{
    setKeyboardTracking(false);
    //connect(this, SIGNAL(valueChanged(double)), this, SLOT(changeStepping(double)));
}

QString espoSpinBox::textFromValue(double value) const{
    QString windowText;

    double approximatelyZero = pow(10, -1 * (decimals() + 1));

    if (abs(value) <= approximatelyZero){
        QTextStream(&windowText) << 0;
        lastValidValue = 0;
        return windowText;
    }
    if (abs(value) >= 1000000){
        QTextStream(&windowText) << value/1000000 << "M";
        lastValidValue = value;
        return windowText;
    }
    if (abs(value) >= 1000){
        QTextStream(&windowText) << value/1000 << "k";
        lastValidValue = value;
        return windowText;
    }
    if (abs(value) >= 1){
        QTextStream(&windowText) << value;
        lastValidValue = value;
        return windowText;
    }
    if (abs(value) >= 1/1000){
        QTextStream(&windowText) << value * 1000 << "m";
        lastValidValue = value;
        return windowText;
    }
    if (abs(value) >= 1/1000000){
        QTextStream(&windowText) << value * 1000000 << "u";
        lastValidValue = value;
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
    double roundval = pow(10.0, floor(log10(abs(value))));  //http://stackoverflow.com/questions/22491505/how-to-round-down-to-the-nearest-power-of-10
    double minimumStepSize = pow(10, -1 * decimals());
    setSingleStep(std::max(minimumStepSize, roundval/10));
}

QValidator::State espoSpinBox::validate(QString& text, int& pos) const
{
    return QValidator::State::Acceptable;
}

double espoSpinBox::valueFromText(const QString &text) const
{
    double ret;
    bool isValid;

    uint32_t prefixLength = text.length() - suffix().length();

    qDebug() << text.mid(0, prefixLength - 1) << text.at(prefixLength - 1).toLatin1();

    switch (text.at(prefixLength - 1).toLatin1())
    {
        case 'M':
            ret = text.mid(0, prefixLength - 1).toDouble(&isValid) * 1000000;
            break;

        case 'k':
            ret = text.mid(0, prefixLength - 1).toDouble(&isValid) * 1000;
            break;

        case 'm':
            ret = text.mid(0, prefixLength - 1).toDouble(&isValid) / 1000;
            break;

        case 'u':
            ret = text.mid(0, prefixLength - 1).toDouble(&isValid) / 1000000;
            break;

        default:
            ret = text.mid(0, prefixLength).toDouble(&isValid);
    }

    if (isValid)
    {
        return ret;
    }
    else
    {
        qDebug() << "espoSpinBox: warning: invalid text input." << "Defaulting to last known good value of" << lastValidValue;
        return lastValidValue;
    }
}
