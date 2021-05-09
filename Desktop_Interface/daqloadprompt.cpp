#include "daqloadprompt.h"
#include "ui_daqloadprompt.h"
#include <QDebug>
#include "siprint.h"

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
    ui->startTimeDoubleSpinBox->setValue(minTime);
    ui->endTimeDoubleSpinBox->setValue(maxTime);

    //Internal signals
    connect(ui->startTimeDoubleSpinBox, &QDoubleSpinBox::textChanged, this, &daqLoadPrompt::valueChange);
    connect(ui->endTimeDoubleSpinBox, &QDoubleSpinBox::textChanged, this, &daqLoadPrompt::valueChange);

    valueChange();
}

daqLoadPrompt::~daqLoadPrompt()
{
    delete ui;
}

void daqLoadPrompt::valueChange(){
    ui->startTimeDoubleSpinBox->setMaximum(ui->endTimeDoubleSpinBox->value() - min_interval);
    ui->endTimeDoubleSpinBox->setMinimum(ui->startTimeDoubleSpinBox->value() + min_interval);

    emit startTime(ui->startTimeDoubleSpinBox->value());
    emit endTime(ui->endTimeDoubleSpinBox->value());

    char units[2] = "B";
    double contig_ram_required = ((ui->endTimeDoubleSpinBox->value() - ui->startTimeDoubleSpinBox->value()) / min_interval) * 4 + 512;  //4 bytes per sample (float), each sample is stored only once.  512 is just a bullshit value to represent the overhead required to store the other variables in the buffer object
    siprint cotig_print(&units[0],contig_ram_required);

    ui->contigRamLabel_Value->setText(cotig_print.printVal());


}
