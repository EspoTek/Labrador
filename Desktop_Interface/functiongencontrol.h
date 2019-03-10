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

enum class ChannelID
{
	CH1 = 0,
	CH2 = 1
};

class functionGenControl : public QLabel
{
    Q_OBJECT
public:
	struct ChannelData
	{
		std::vector<uint8_t> samples;
		int divisibility;
		double freq = 1000.0;
		double amplitude = 0.0;
		double offset = 0.0;
	};


    explicit functionGenControl(QWidget *parent = 0);

	ChannelData channels[2];

public:

	ChannelData& getChannelData(ChannelID channelID);

signals:
    void functionGenToUpdate(ChannelID channel, functionGenControl *fGenControl);
    void setMaxFreq_CH1(double maxFreq);
    void setMinFreq_CH1(double minFreq);
    void setMaxFreq_CH2(double maxFreq);
    void setMinFreq_CH2(double minFreq);

public slots:
    void waveformName(ChannelID channelId, QString newName);
    void freqUpdate(ChannelID channelId, double newFreq);
    void amplitudeUpdate(ChannelID channelId, double newAmplitude);
    void offsetUpdate(ChannelID channelId, double newOffset);

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
