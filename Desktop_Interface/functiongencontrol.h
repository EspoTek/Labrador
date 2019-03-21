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

namespace functionGen {

enum class ChannelID
{
	CH1 = 0,
	CH2 = 1
};

struct ChannelData
{
	std::vector<uint8_t> samples;
	int divisibility;
	double freq = 1000.0;
	double amplitude = 0.0;
	double offset = 0.0;
};

class SingleChannelController : public QObject
{
	Q_OBJECT

public:
	ChannelData const& getData() const;

signals:
    void notifyUpdate(SingleChannelController* controller);
	void setMaxFreq(double maxFreq);
    void setMinFreq(double minFreq);

public slots:
    void waveformName(QString newName);
    void freqUpdate(double newFreq);
    void amplitudeUpdate(double newAmplitude);
    void offsetUpdate(double newOffset);

private:
	ChannelData m_data;
};

class DualChannelController : public QLabel
{
    Q_OBJECT
public:
    explicit DualChannelController(QWidget *parent = 0);

public:
	SingleChannelController* getChannelController(ChannelID channelID);

signals:
    void functionGenToUpdate(ChannelID channel, SingleChannelController* fGenControl);
    void setMaxFreq_CH1(double maxFreq);
    void setMinFreq_CH1(double minFreq);
    void setMaxFreq_CH2(double maxFreq);
    void setMinFreq_CH2(double minFreq);

public slots:
    void waveformName(ChannelID channelID, QString newName);
    void freqUpdate(ChannelID channelID, double newFreq);
    void amplitudeUpdate(ChannelID channelID, double newAmplitude);
    void offsetUpdate(ChannelID channelID, double newOffset);

    void waveformName_CH1(QString newName);
    void freqUpdate_CH1(double newFreq);
    void amplitudeUpdate_CH1(double newAmplitude);
    void offsetUpdate_CH1(double newOffset);

    void waveformName_CH2(QString newName);
    void freqUpdate_CH2(double newFreq);
    void amplitudeUpdate_CH2(double newAmplitude);
    void offsetUpdate_CH2(double newOffset);

private:
	SingleChannelController m_channels[2];
};

}

using functionGenControl = functionGen::DualChannelController;

#endif // FUNCTIONGENCONTROL_H
