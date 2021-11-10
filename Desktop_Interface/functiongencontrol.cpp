#include "functiongencontrol.h"
#include "platformspecific.h"
#include <QStandardPaths>

namespace functionGen {

ChannelData const& SingleChannelController::getData() const {
    return m_data;
}

void SingleChannelController::waveformName(QString newName)
{
#if defined(PLATFORM_ANDROID)
    QString path("assets:/waveforms/");
    QFile file(path.append(newName).append(".tlw"));
#elif defined(PLATFORM_LINUX)
    QString path("waveforms/");
    path.append(newName).append(".tlw");
    QFile file(QStandardPaths::locate(QStandardPaths::AppDataLocation, path));
#else
    QString path = QCoreApplication::applicationDirPath();
    QFile file(path.append("/waveforms/").append(newName).append(".tlw"));
#endif

    qDebug() << "opening" << file.fileName();
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qFatal("could not open %s", qUtf8Printable(file.fileName()));

    int length = file.readLine().toInt();
    m_data.divisibility = file.readLine().toInt();
    QByteArray data = file.readLine().trimmed();
    file.close();

    qDebug() << "Length = " << length;
    qDebug() << "Divisibility = " << m_data.divisibility;

    // Length is redundant, could be derived from the sample list.
    if (length != data.count('\t') + 1)
        qFatal("%s: sample count mismatch", qUtf8Printable(file.fileName()));
    m_data.samples.resize(length);

    data.replace('\t', '\0');
    const char *dataString = data.constData();
    QByteArray dataElem;
    for (auto &sample : m_data.samples) {
        dataElem.setRawData(dataString, strlen(dataString));
        sample = static_cast<uint8_t>(dataElem.toInt());
        dataString += dataElem.size() + 1;
    }

    double newMaxFreq = DAC_SPS / (length >> (m_data.divisibility - 1));
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
    getChannelController(channelID)->waveformName(newName);
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
    waveformName(ChannelID::CH1, newName);
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
    waveformName(ChannelID::CH2, newName);
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
