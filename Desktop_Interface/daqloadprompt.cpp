// Copyright (C) 2017, 2018, 2019, 2020, 2021 Christopher Paul Esposito
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
    connect(ui->startTimeDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(valueChange()));
    connect(ui->endTimeDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(valueChange()));

    valueChange();
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

    char units[2] = "B";
    double contig_ram_required = ((ui->endTimeDoubleSpinBox->value() - ui->startTimeDoubleSpinBox->value()) / min_interval) * 4 + 512;  //4 bytes per sample (float), each sample is stored only once.  512 is just a bullshit value to represent the overhead required to store the other variables in the buffer object
    siprint cotig_print(&units[0],contig_ram_required);

    ui->contigRamLabel_Value->setText(cotig_print.printVal());


}
