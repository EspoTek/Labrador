#include "functiongencontrol.h"

#include <utility>
#include "platformspecific.h"

#include <QRegularExpression>

namespace functionGen {

ChannelData const& SingleChannelController::getData() const {
	return m_data;
}

void SingleChannelController::waveformName(QString newName)
{
    qDebug() << "newName = " << newName;
    newName.append(".tlw");

	int length;

    const QStringList potentialDirs = {
#ifdef PLATFORM_ANDROID
        "assets:",
#else
       QCoreApplication::applicationDirPath(),
#endif
       ":", // fall back to builtin
    };

    QString filename;
    for (const QString &dir : potentialDirs) {
        const QString potential = dir + "/waveforms/" + newName;
        if (QFileInfo::exists(potential)) {
            filename = potential;
            break;
        }
    }

    QString waveformFilePath(filename);

    QFile fptr(waveformFilePath);
    if (!fptr.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open" << newName;
        return;
    }

    QByteArray line;

    line = fptr.readLine().trimmed();
    bool ok;
    length = line.toInt(&ok);
    if (!ok) {
        qWarning() << "Invalid length line" << line << "in" << filename;
        return;
    }
    if (length == 0) {
        qWarning() << "No samples in" << filename;
        return;
    }

    line = fptr.readLine().trimmed();
    m_data.divisibility = line.toInt(&ok);
    if (!ok) {
        qWarning() << "Invalid divisibility line" << line << "in" << filename;
        return;
    }


    qDebug() << "Length = " << length;
    qDebug() << "Divisibility = " << m_data.divisibility;

    QString remainingData = QString::fromLatin1(fptr.readAll().simplified());

	m_data.samples.resize(length);

    // Should use tabs for separating, but we support any kind of whitespace
    const QStringList values = remainingData.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    if (values.count() != length) {
        qWarning() << "Invalid amount of values" << values.count() << "in" << filename << "expected" << length;
        m_data.samples.resize(values.count());
    }
    for (int i=0; i<values.count(); i++) {
        ushort sample = values[i].toUShort(&ok);
        if (!ok || sample > 255) {
            qWarning() << "Invalid sample value" << values[i];
        }
        m_data.samples[i] = uint8_t(sample);
    }


    const unsigned divisor = length >> (m_data.divisibility - 1);
    if (divisor == 0) {
        qWarning() << "Invalid divisor" << divisor;
        return;
    }
    double newMaxFreq = DAC_SPS / divisor;
	double newMinFreq = double(CLOCK_FREQ) / 1024.0 / 65535.0 / static_cast<double>(length);

	setMaxFreq(newMaxFreq);
	setMinFreq(newMinFreq);

    notifyUpdate(this);
}

void SingleChannelController::freqUpdate(double newFreq)
{
	qDebug() << "newFreq = " << newFreq;
	m_data.freq = newFreq;
	notifyUpdate(this);
}

void SingleChannelController::amplitudeUpdate(double newAmplitude)
{
	qDebug() << "newAmplitude = " << newAmplitude;
	m_data.amplitude = newAmplitude;
	notifyUpdate(this);
}

void SingleChannelController::offsetUpdate(double newOffset)
{
	qDebug() << "newOffset = " << newOffset;
	m_data.offset = newOffset;
	notifyUpdate(this);
}


DualChannelController::DualChannelController(QWidget *parent) : QLabel(parent)
{
	// A bunch of plumbing to forward the SingleChannelController's signals

	SingleChannelController* controller1 = getChannelController(ChannelID::CH1);
	SingleChannelController* controller2 = getChannelController(ChannelID::CH2);

	connect(controller1, &SingleChannelController::notifyUpdate,
	        this, [=](SingleChannelController* ptr){ this->functionGenToUpdate(ChannelID::CH1, ptr); });

	connect(controller1, &SingleChannelController::setMaxFreq,
	        this, &DualChannelController::setMaxFreq_CH1);

	connect(controller1, &SingleChannelController::setMinFreq,
	        this, &DualChannelController::setMinFreq_CH1);


	connect(controller2, &SingleChannelController::notifyUpdate,
	        this, [=](SingleChannelController* ptr){ this->functionGenToUpdate(ChannelID::CH2, ptr); });

	connect(controller1, &SingleChannelController::setMaxFreq,
	        this, &DualChannelController::setMaxFreq_CH2);

	connect(controller1, &SingleChannelController::setMinFreq,
	        this, &DualChannelController::setMinFreq_CH2);

    this->hide();
}


SingleChannelController* DualChannelController::getChannelController(ChannelID channelID)
{
	return &m_channels[(int)channelID];
}

// The rest of this file is just plumbing to forward slot calls to SingleChannelController's
// Hopefuly it can be mostly removed eventually
void DualChannelController::waveformName(ChannelID channelID, QString newName)
{
	getChannelController(channelID)->waveformName(std::move(newName));
}

void DualChannelController::freqUpdate(ChannelID channelID, double newFreq)
{
	getChannelController(channelID)->freqUpdate(newFreq);
}

void DualChannelController::amplitudeUpdate(ChannelID channelID, double newAmplitude)
{
	getChannelController(channelID)->amplitudeUpdate(newAmplitude);
}

void DualChannelController::offsetUpdate(ChannelID channelID, double newOffset)
{
	getChannelController(channelID)->offsetUpdate(newOffset);
}


void DualChannelController::waveformName_CH1(QString newName)
{
	waveformName(ChannelID::CH1, std::move(newName));
}

void DualChannelController::freqUpdate_CH1(double newFreq)
{
	freqUpdate(ChannelID::CH1, newFreq);
}

void DualChannelController::amplitudeUpdate_CH1(double newAmplitude)
{
	amplitudeUpdate(ChannelID::CH1, newAmplitude);
}

void DualChannelController::offsetUpdate_CH1(double newOffset)
{
	offsetUpdate(ChannelID::CH1, newOffset);
}


void DualChannelController::waveformName_CH2(QString newName)
{
	waveformName(ChannelID::CH2, std::move(newName));
}

void DualChannelController::freqUpdate_CH2(double newFreq)
{
	freqUpdate(ChannelID::CH2, newFreq);
}

void DualChannelController::amplitudeUpdate_CH2(double newAmplitude)
{
	amplitudeUpdate(ChannelID::CH2, newAmplitude);
}

void DualChannelController::offsetUpdate_CH2(double newOffset)
{
	offsetUpdate(ChannelID::CH2, newOffset);
}

}

