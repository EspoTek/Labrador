#ifndef FUNCTIONGENCONTROL_H
#define FUNCTIONGENCONTROL_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QDir>
#include <QFile>
#include "xmega.h"
#include <QCoreApplication>

//functionGenControl is a centralised object to control all of the high-level function gen commands for both channels.

class functionGenControl : public QLabel
{
    Q_OBJECT
public:
	struct ChannelData
	{
		unsigned char* samples;
		int length;
		int divisibility;
		double freq = 1000.0;
		double amplitude = 0.0;
		double offset = 0.0;
	};
public:
    explicit functionGenControl(QWidget *parent = 0);

	ChannelData CH1;
	ChannelData CH2;

	__attribute__ ((deprecated)) unsigned char *samples_CH1;
	__attribute__ ((deprecated)) unsigned char *samples_CH2;
	__attribute__ ((deprecated)) int length_CH1;
	__attribute__ ((deprecated)) int divisibility_CH1;
	__attribute__ ((deprecated)) int length_CH2;
	__attribute__ ((deprecated)) int divisibility_CH2;
	__attribute__ ((deprecated)) double freq_CH1 = 1000;
	__attribute__ ((deprecated)) double amplitude_CH1 = 0;
	__attribute__ ((deprecated)) double offset_CH1 = 0;
	__attribute__ ((deprecated)) double freq_CH2 = 1000;
	__attribute__ ((deprecated)) double amplitude_CH2 = 0;
	__attribute__ ((deprecated)) double offset_CH2 = 0;
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
