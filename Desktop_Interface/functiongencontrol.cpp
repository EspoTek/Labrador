#include "functiongencontrol.h"
#include "platformspecific.h"

namespace functionGen {

ChannelData const& SingleChannelController::getData() const {
	return m_data;
}

void SingleChannelController::waveformName(QString newName)
{
    qDebug() << "newName = " << newName;
    m_data.waveform = newName;
    newName.append(".tlw");

	int length;

#ifdef PLATFORM_ANDROID
    QString waveformFilePath("assets:/waveforms/");
    waveformFilePath.append(newName);

    QFile fptr(waveformFilePath);
    bool success = fptr.open(QIODevice::ReadOnly);

    QByteArray line;
    char lengthString[16];
    char divisibilityString[16];

    line = fptr.readLine();
    strcpy(lengthString, line.data());
    sscanf(lengthString, "%d", &length);
    qDebug() << "lengthString" << lengthString;

    line = fptr.readLine();
    strcpy(divisibilityString, line.data());
    sscanf(divisibilityString, "%d", &m_data.divisibility);
    qDebug() << "divisibilityString" << divisibilityString;

    qDebug() << "Length = " << length;
    qDebug() << "Divisibility = " << m_data.divisibility;

    QByteArray remainingData = fptr.readAll();
    char *dataString = remainingData.data();

	m_data.samples.resize(length);

    int dummy;
    char *dataStringCurrent = dataString;
    for (int i = 0; i < length; i++)
	{
        sscanf(dataStringCurrent, "%d", &dummy);
        dataStringCurrent += strcspn(dataStringCurrent, "\t") + 1;
        m_data.samples[i] = static_cast<uint8_t>(dummy);
    }

#else

    QByteArray filePath = QCoreApplication::applicationDirPath()
		.append("/waveforms/").append(newName).toLocal8Bit();

    qDebug() << "opening" << filePath;

    FILE *fptr = fopen(filePath.constData(), "r");
    if (fptr == NULL)
        qFatal("%s could not be opened!", filePath.constData());

    char lengthString[16];
    fgets(lengthString, 5, fptr);
    sscanf(lengthString, "%d", &length);

    char divisibilityString[16];
    //Bit of bullshit to deal with CRLF line endings on Mac.
    do
	{
		fgets(divisibilityString, 5, fptr);
	}
	while ((divisibilityString[0] == '\r') || (divisibilityString[0] == '\n'));

    sscanf(divisibilityString, "%d", &m_data.divisibility);

    qDebug() << "Length = " << length;
    qDebug() << "Divisibility = " << m_data.divisibility;

	m_data.samples.resize(length);

    char *dataString = (char *) malloc(length*5+1);
    fgets(dataString, length*5+1, fptr);

    int dummy;
    char *dataStringCurrent = dataString;
    for (int i = 0; i < length; i++)
	{
        sscanf(dataStringCurrent, "%d", &dummy);
        dataStringCurrent += strcspn(dataStringCurrent, "\t") + 1;
        m_data.samples[i] = static_cast<uint8_t>(dummy);
    }
    m_data.repeat_forever = true;

    free(dataString);
    fclose(fptr);
#endif

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
	m_data.repeat_forever = true;
	notifyUpdate(this);
}

void SingleChannelController::amplitudeUpdate(double newAmplitude)
{
	qDebug() << "newAmplitude = " << newAmplitude;
	m_data.amplitude = newAmplitude;
	m_data.repeat_forever = true;
	notifyUpdate(this);
}

void SingleChannelController::offsetUpdate(double newOffset)
{
	qDebug() << "newOffset = " << newOffset;
	m_data.offset = newOffset;
	m_data.repeat_forever = true;
	notifyUpdate(this);
}

void SingleChannelController::dutyCycleUpdate(double newDutyCycle)
{
	qDebug() << "newDutyCycle = " << newDutyCycle;
	m_data.dutyCycle = newDutyCycle;
	m_data.repeat_forever = true;
	notifyUpdate(this);
}

void SingleChannelController::txuartUpdate(int baudRate, std::vector<uint8_t> samples)
{
	// Update txUart data
	int length = samples.size();
	m_data.samples.resize(length);
	m_data.samples = samples;
	m_data.freq = baudRate/length;
	m_data.repeat_forever = false;

	notifyUpdate(this);
}

void SingleChannelController::backup_waveform()
{
	m_data.freq2 = m_data.freq;
}

void SingleChannelController::restore_waveform()
{
	m_data.freq = m_data.freq2;
	waveformName(m_data.waveform);
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

void DualChannelController::dutyCycleUpdate(ChannelID channelID, double newDutyCycle)
{
	getChannelController(channelID)->dutyCycleUpdate(newDutyCycle);
}

void DualChannelController::txuartUpdate(ChannelID channelID, int baudRate, std::vector<uint8_t> samples)
{
	getChannelController(channelID)->txuartUpdate(baudRate, samples);
}

void DualChannelController::backup_waveform(ChannelID channelID)
{
	getChannelController(channelID)->backup_waveform();
}

void DualChannelController::restore_waveform(ChannelID channelID)
{
	getChannelController(channelID)->restore_waveform();
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

void DualChannelController::dutyCycleUpdate_CH1(double newDutyCycle)
{
	dutyCycleUpdate(ChannelID::CH1, newDutyCycle);
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

void DualChannelController::dutyCycleUpdate_CH2(double newDutyCycle)
{
    dutyCycleUpdate(ChannelID::CH2, newDutyCycle);
}

}

