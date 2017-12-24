#include "daqform.h"
#include "ui_daqform.h"

daqForm::daqForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::daqForm)
{
    ui->setupUi(this);
}

daqForm::~daqForm()
{
    delete ui;
}
