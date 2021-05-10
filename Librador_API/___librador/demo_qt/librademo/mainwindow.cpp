// Copyright (C) 2018 Christopher Paul Esposito
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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "librador.h"
#include "QDebug"
#include <QVector>
#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setbuf(stdout, 0);
    setbuf(stderr, 0);
    initialisePlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialisePlot()
{
    ui->widget->addGraph();
    ui->widget->addGraph();

    ui->widget->yAxis->setAutoTickCount(9);
    ui->widget->xAxis->setAutoTickCount(9);

    ui->widget->graph(0)->setPen(QPen(Qt::yellow, 1));
    ui->widget->graph(1)->setPen(QPen(Qt::cyan, 1));

    ui->widget->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->widget->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->widget->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->widget->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->widget->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->widget->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->widget->xAxis->setTickLength(6);
    ui->widget->yAxis->setTickLength(6);
    ui->widget->xAxis->setSubTickLength(4);
    ui->widget->yAxis->setSubTickLength(4);
    ui->widget->xAxis->setTickLabelColor(Qt::white);
    ui->widget->yAxis->setTickLabelColor(Qt::white);

    ui->widget->setBackground(Qt::black);


    ui->widget->replot();
}


void MainWindow::on_pushButton_clicked()
{
    qDebug() << librador_init();
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << librador_exit();
}

void MainWindow::on_pushButton_3_clicked()
{
    qDebug() << librador_setup_usb();
}

void MainWindow::on_pushButton_4_clicked()
{
    qDebug() << librador_avr_debug();
}

void MainWindow::on_pushButton_5_clicked()
{
    double sampleRate = 375000;
    if((current_channel == 1) || (current_channel == 2)){
        std::vector<double> *from_librador = (librador_get_analog_data(current_channel, 1, sampleRate, 0.1, 0));
        plot_from_librador(from_librador, sampleRate, ui->widget->graph(0));
    } else {
        std::vector<double> *from_librador_ch1 = (librador_get_analog_data(1, 1, sampleRate, 0.1, 0));
        std::vector<double> *from_librador_ch2 = (librador_get_analog_data(2, 1, sampleRate, 0.1, 0));
        plot_from_librador(from_librador_ch1, sampleRate, ui->widget->graph(0));
        plot_from_librador(from_librador_ch2, sampleRate, ui->widget->graph(1));
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    qDebug() << librador_reset_usb();
}

void MainWindow::on_pushButton_7_clicked()
{
    qDebug() << librador_get_device_firmware_version();
}

void MainWindow::on_pushButton_8_clicked()
{
    qDebug() << librador_get_device_firmware_variant();
}

void MainWindow::on_pushButton_9_clicked()
{
    qDebug() << librador_set_power_supply_voltage(ui->powerSupplySpinBox->value());
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    qDebug() << librador_set_digital_out(1, arg1);
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    qDebug() << librador_set_digital_out(2, arg1);
}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    qDebug() << librador_set_digital_out(3, arg1);
}

void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    qDebug() << librador_set_digital_out(4, arg1);
}

void MainWindow::on_comboBox_activated(int index)
{
    double gainValues[8] = {0.5, 1, 2 , 4, 8, 16, 32, 64};
    qDebug() << index;

    double newGain = gainValues[index];
    ymax = 1.65 + (11/newGain);
    ymin = 1.65 - (14/newGain);
    qDebug() << librador_set_oscilloscope_gain(newGain);
}

void MainWindow::on_pushButton_10_clicked()
{
    qDebug() << librador_reset_device();
}

void MainWindow::on_pushButton_11_clicked()
{
    qDebug() << librador_jump_to_bootloader();
}

void MainWindow::on_comboBox_2_activated(int index)
{
    qDebug() << librador_set_device_mode(index);
}

void MainWindow::on_comboBox_3_activated(int index)
{
    current_channel = index + 1;
}

void MainWindow::signal_gen_convenience(int channel)
{
    double frequency_hz = ui->doubleSpinBox_frequency->value();
    double amplitude_v = ui->doubleSpinBox_amplitude->value();
    double offset_v = ui->doubleSpinBox_offset->value();

    switch(ui->comboBox_signal_gen_type->currentIndex()){
    case 0:
        librador_send_sin_wave(channel, frequency_hz, amplitude_v, offset_v);
        break;
    case 1:
        librador_send_square_wave(channel, frequency_hz, amplitude_v, offset_v);
        break;
    case 2:
        librador_send_triangle_wave(channel, frequency_hz, amplitude_v, offset_v);
        break;
    case 3:
        librador_send_sawtooth_wave(channel, frequency_hz, amplitude_v, offset_v);
        break;
    default:
        qDebug() << "INVALID WAVEFORM";
    }

}

void MainWindow::on_pushButton_12_clicked()
{
    signal_gen_convenience(1);
}

void MainWindow::on_pushButton_13_clicked()
{
    signal_gen_convenience(2);
}

void MainWindow::on_pushButton_14_clicked()
{
    double sampleRate = 375000;
    if((current_channel == 1) || (current_channel == 2)){
        std::vector<double> *from_librador = (librador_get_analog_data_sincelast(current_channel, 10, sampleRate, 0.1, 0));
        plot_from_librador(from_librador, sampleRate, ui->widget->graph(0));
    } else {
        std::vector<double> *from_librador_ch1 = (librador_get_analog_data_sincelast(1, 10, sampleRate, 0.1, 0));
        std::vector<double> *from_librador_ch2 = (librador_get_analog_data_sincelast(2, 10, sampleRate, 0.1, 0));
        plot_from_librador(from_librador_ch1, sampleRate, ui->widget->graph(0));
        plot_from_librador(from_librador_ch2, sampleRate, ui->widget->graph(1));
    }
}

void MainWindow::plot_from_librador(std::vector<double> *from_librador, double sampleRate, QCPGraph *graph)
{
    qDebug() << "check1";

    if(from_librador == NULL){
        qDebug() << "from_librador NULL!";
        return;
    }

    QVector<double> yaxis = QVector<double>::fromStdVector(*from_librador);

    if(yaxis.length() == 0){
        qDebug() << "NO DATA RETURNED!";
        return;
    }

    //qDebug() << yaxis;

    QVector<double> xaxis;
    for (int i=0; i<yaxis.length(); i++){
        xaxis.append(-i/sampleRate);
    }

    qDebug() << yaxis.length();
    qDebug() << xaxis.length();

    ui->widget->yAxis->setRange(ymin, ymax);
    ui->widget->xAxis->setRange(-yaxis.length()/sampleRate, 0);

    graph->setData(xaxis, yaxis);
    ui->widget->replot();
}

void MainWindow::on_pushButton_15_clicked()
{
    double sampleRate = 3000000;
    if((current_channel == 1) || (current_channel == 2)){
        std::vector<uint8_t> *from_librador_uint8 = (librador_get_digital_data(current_channel, 1, sampleRate, 0.1));
        if(from_librador_uint8 != NULL){
            std::vector<double> from_librador(from_librador_uint8->begin(), from_librador_uint8->end());
            plot_from_librador(&from_librador, sampleRate, ui->widget->graph(0));
        }
    } else {
        std::vector<uint8_t> *from_librador_ch1_uint8 = (librador_get_digital_data(1, 1, sampleRate, 0.1));
        std::vector<uint8_t> *from_librador_ch2_uint8 = (librador_get_digital_data(2, 1, sampleRate, 0.1));
        if(from_librador_ch1_uint8 != NULL){
            std::vector<double> from_librador_ch1(from_librador_ch1_uint8->begin(), from_librador_ch1_uint8->end());
            plot_from_librador(&from_librador_ch1, sampleRate, ui->widget->graph(0));
        }
        if(from_librador_ch2_uint8 != NULL){
            std::vector<double> from_librador_ch2(from_librador_ch2_uint8->begin(), from_librador_ch2_uint8->end());
            plot_from_librador(&from_librador_ch2, sampleRate, ui->widget->graph(1));
        }
    }
}
