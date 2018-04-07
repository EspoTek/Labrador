#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "librador.h"
#include "QDebug"
#include <QVector>

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

    QVector<double> yaxis = QVector<double>::fromStdVector(*(librador_get_iso_data(75000, 1, 1500, 0)));

    qDebug() << yaxis;

    QVector<double> xaxis;
    for (int i=0; i<yaxis.length(); i++){
        xaxis.append(i);
    }

    qDebug() << yaxis.length();
    qDebug() << xaxis.length();

    ui->widget->yAxis->setRange(0, 255);
    ui->widget->xAxis->setRange(0, yaxis.length());

    ui->widget->graph(0)->setData(xaxis, yaxis);
    ui->widget->replot();
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
