#include "scoperangeenterdialog.h"
#include "ui_scoperangeenterdialog.h"

scopeRangeEnterDialog::scopeRangeEnterDialog(QWidget *parent, double yTop, double yBot, double window, double delay) :
    QDialog(parent),
    ui(new Ui::scopeRangeEnterDialog)
{
    ui->setupUi(this);

    ui->vMaxBox->setMinimum(yBot);
    ui->vMinBox->setMaximum(yTop);

    ui->vMaxBox->setValue(yTop);
    ui->vMinBox->setValue(yBot);
    ui->timeWindowBox->setValue(window);
}

scopeRangeEnterDialog::~scopeRangeEnterDialog()
{
    delete ui;
}

void scopeRangeEnterDialog::toUpdateYTop(double val){
    qDebug() << val;
    yTopUpdated(val);
}

void scopeRangeEnterDialog::toUpdateYBot(double val){
    qDebug() << val;
    yBotUpdated(val);
}

void scopeRangeEnterDialog::toUpdateWindow(double val){
    qDebug() << val;
    windowUpdated(val);
}

