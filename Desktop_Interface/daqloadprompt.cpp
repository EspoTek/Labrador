#include "daqloadprompt.h"
#include "ui_daqloadprompt.h"
#include <QDebug>

daqLoadPrompt::daqLoadPrompt(QWidget *parent, double minTime, double maxTime) :
    QDialog(parent),
    ui(new Ui::daqLoadPrompt)
{
    ui->setupUi(this);

    min_interval = minTime;
    ui->startTimeDoubleSpinBox->setMinimum(minTime);
    ui->endTimeDoubleSpinBox->setMinimum(minTime);
    ui->startTimeDoubleSpinBox->setMaximum(maxTime);
    ui->endTimeDoubleSpinBox->setMaximum(maxTime);

    //Internal signals
    connect(ui->startTimeDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(valueChange()));
    connect(ui->endTimeDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(valueChange()));

}

daqLoadPrompt::~daqLoadPrompt()
{
    delete ui;
}

void daqLoadPrompt::valueChange(){
    ui->startTimeDoubleSpinBox->setMaximum(ui->endTimeDoubleSpinBox->value() - min_interval);
    ui->endTimeDoubleSpinBox->setMinimum(ui->startTimeDoubleSpinBox->value() + min_interval);

    startTime(ui->startTimeDoubleSpinBox->value());
    endTime(ui->endTimeDoubleSpinBox->value());
}
