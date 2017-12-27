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
    explicit daqForm(QWidget *parent, int initialAverage, qulonglong initialMaxFileSize);
    ~daqForm();
signals:
    void updatedAveraging(int);
    void updatedMaxFileSize(qulonglong);
    void saveButtonPressed();
private:
    Ui::daqForm *ui;
private slots:
    void updateLabels();
    void updateValues();
    void trigger_saveButtonPressed();
};

#endif // DAQFORM_H
