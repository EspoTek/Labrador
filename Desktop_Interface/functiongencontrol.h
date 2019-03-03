#ifndef FUNCTIONGENCONTROL_H
#define FUNCTIONGENCONTROL_H

#include <vector>

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
		std::vector<uint8_t> samples;
		// TODO: get rid of length member. samples:std::vector already has this information
		int length;
		int divisibility;
		double freq = 1000.0;
		double amplitude = 0.0;
		double offset = 0.0;
	};

    explicit functionGenControl(QWidget *parent = 0);

	ChannelData channels[2];

private:

	// NOTE: An enum instead of a plain int would probably be better here
    void waveformName(QString newName, int channelID);
    void freqUpdate(double newFreq, int channelID);
    void amplitudeUpdate(double newAmplitude, int channelID);
    void offsetUpdate(double newOffset, int channelID);

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
