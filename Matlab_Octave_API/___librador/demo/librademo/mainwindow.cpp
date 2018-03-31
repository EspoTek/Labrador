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

    QVector<double> yaxis = QVector<double>::fromStdVector(*(librador_get_iso_data(75000, 1, 750000, 0)));

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

