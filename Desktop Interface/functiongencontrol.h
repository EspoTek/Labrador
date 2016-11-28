#ifndef FUNCTIONGENCONTROL_H
#define FUNCTIONGENCONTROL_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QDir>
#include <QFile>
#include "xmega.h"

//functionGenControl is a centralised object to control all of the high-level function gen commands for both channels.

class functionGenControl : public QLabel
{
    Q_OBJECT
public:
    explicit functionGenControl(QWidget *parent = 0);
    unsigned char *samples_CH1, *samples_CH2;
    int length_CH1, divisibility_CH1, length_CH2, divisibility_CH2;
    double freq_CH1 = 1000, amplitude_CH1 = 0, offset_CH1 = 0, freq_CH2 = 1000, amplitude_CH2 = 0, offset_CH2 = 0;
signals:
    void functionGenToUpdate(int channel, functionGenControl *fGenControl);
    void setMaxFreq_CH1(double maxFreq);
    void setMinFreq_CH1(double minFreq);
    void setMaxFreq_CH2(double maxFreq);
    void setMinFreq_CH2(double minFreq);
public slots:
    void waveformName_CH1(QString newName);
    void freqUpdate_CH1(double newFreq);
    void amplitudeUpdate_CH1(double newAmplitude);
    void offsetUpdate_CH1(double newOffset);
    void waveformName_CH2(QString newName);
    void freqUpdate_CH2(double newFreq);
    void amplitudeUpdate_CH2(double newAmplitude);
    void offsetUpdate_CH2(double newOffset);
};

#endif // FUNCTIONGENCONTROL_H
