#ifndef DAQFORM_H
#define DAQFORM_H

#include <QDialog>

namespace Ui {
class daqForm;
}

class daqForm : public QDialog
{
    Q_OBJECT

public:
    explicit daqForm(QWidget *parent = 0);
    ~daqForm();

private:
    Ui::daqForm *ui;
};

#endif // DAQFORM_H
