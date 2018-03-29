#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "librador.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setbuf(stdout, 0);
    setbuf(stderr, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
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
