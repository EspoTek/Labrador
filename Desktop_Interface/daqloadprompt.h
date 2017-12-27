#ifndef DAQLOADPROMPT_H
#define DAQLOADPROMPT_H

#include <QDialog>

namespace Ui {
class daqLoadPrompt;
}

class daqLoadPrompt : public QDialog
{
    Q_OBJECT

public:
    explicit daqLoadPrompt(QWidget *parent, double minTime, double maxTime);
    ~daqLoadPrompt();

private:
    double min_interval;
    Ui::daqLoadPrompt *ui;
signals:
    void startTime(double);
    void endTime(double);

public slots:
    void valueChange(void);
};

#endif // DAQLOADPROMPT_H
