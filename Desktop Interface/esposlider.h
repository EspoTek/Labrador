#ifndef ESPOSLIDER_H
#define ESPOSLIDER_H

#include <QSlider>
#include <QString>
//#include <QDebug>
#include <QLabel>
#include <QLayout>
#include <QString>

class espoSlider : public QSlider
{
    Q_OBJECT
public:
    explicit espoSlider(QWidget *parent = 0);
    bool setTickLabel(QString label, int position);
    void resizeEvent(QResizeEvent *event);
    void moveEvent(QMoveEvent *event);
    void setTickInterval(int ti);
    int maxTick();
    int maxTick(int ti);
private:
    int debug_var = 0;
    void rearrange();
    std::vector<QLabel*> addressBook;
    QWidget* windowPointer;
    int labelMargin;
signals:
    void lcdOut(QString values);
    void voltageChanged(double newVoltage);
public slots:
    void selfMoved(int newval);
};

#endif // ESPOSLIDER_H
