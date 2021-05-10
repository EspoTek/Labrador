// Copyright (C) 2017, 2018, 2019, 2020, 2021 Christopher Paul Esposito
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "functiongencontrol.h"
#include "platformspecific.h"

namespace functionGen {

ChannelData const& SingleChannelController::getData() const {
	return m_data;
}

void SingleChannelController::waveformName(QString newName)
{
    qDebug() << "newName = " << newName;
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

