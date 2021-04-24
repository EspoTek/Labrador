#ifndef ISODRIVER_H
#define ISODRIVER_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QVector>
#include "qcustomplot.h"
#include "genericusbdriver.h"
#include "desktop_settings.h"
#include "siprint.h"
#include "i2cdecoder.h"
#include "uartstyledecoder.h"

class isoBuffer;
class isoBuffer_file;

// isoDriver is a huge class.  It handles everything related to the
// isochronous IN stream - and perhaps that constraint was applied
// a bit too loosely (spot the C programmer...).

// Too much stuff is handled in this class, and it's too heavily
// entangled with the (generic/win/unix)UsbDriver classes.

// That is one of the things I plan on fixing, and in fact
// the reason why I began the commenting!

class DisplayControl : public QObject
{
    Q_OBJECT
public:

    double delay = 0;
    double window = 0.01;
    double y0 = 0;
    double y1 = 0;
    double x0 = 0;
    double x1 = 0;
    double topRange = 2.5;
    double botRange = -0.5;

    void setVoltageRange (QWheelEvent* event, bool isProperlyPaused, double maxWindowSize, QCustomPlot* axes);

signals:
    void topRangeUpdated(double);
    void botRangeUpdated(double);
    void timeWindowUpdated(double);
    void delayUpdated(double);
};

class isoDriver : public QLabel
{
    Q_OBJECT
public:
    enum Channel {
        Channel3751 = 1 << 0,
        Channel3752 = 1 << 1,
        Channel750 =  1 << 2,
    };
    Q_DECLARE_FLAGS(Channels, Channel);
    Q_FLAG(Channel);

    enum class ChannelMode {
        Off = 0,
        Analog = 1,
        Digital = 2,
        Analog750 = -1,
        File = -2
    };
    Q_ENUM(ChannelMode);

    enum DeviceMode {
        DeviceCH1Analog = 0,
        DeviceCH1AnalogCH2Digital = 1,
        DeviceCH1AnalogCH2Analog = 2,
        DeviceCH1Digital = 3,
        DeviceCH1DigitalCH2Digital = 4,
        DeviceCH1Analog750 = 6,
        DeviceMultimeter = 7
    };
    Q_ENUM(DeviceMode);

    explicit isoDriver(QWidget *parent = 0);
    ~isoDriver();

    void autoGain(void);
    //Generic Vars
    isoBuffer *internalBuffer375_CH1;
    isoBuffer *internalBuffer375_CH2;
    isoBuffer *internalBuffer750;
    isoBuffer_file *internalBufferFile = NULL;
#if QCP_VER == 1
    QCPItemText *cursorTextPtr;
#endif
    QPointer<genericUsbDriver> driver;
    bool doNotTouchGraph = true;
    double ch1_ref = 1.65;
    double ch2_ref = 1.65;
    double frontendGain_CH1 = (R4/(R3+R4));
    double frontendGain_CH2 = (R4/(R3+R4));
    UartParity parity_CH1 = UartParity::None;
    UartParity parity_CH2 = UartParity::None;
    //State Vars
    bool AC_CH1 = false;
    bool AC_CH2 = false;
    bool cursorStatsEnabled = true;
    int baudRate_CH1 = 9600;
    int baudRate_CH2 = 9600;
    double currentVmean;
    //Display Control Vars (Variables that control how the buffers are displayed)
    DisplayControl display;
    //Generic Functions
    void setDriver(genericUsbDriver *newDriver);
    void setAxes(QCustomPlot *newAxes);
    double meanVoltageLast(double seconds, unsigned char channel, int TOP);
    void loadFileBuffer(QFile *fileToLoad);
    void setSerialType(unsigned char type);
    //DAQ
    bool fileModeEnabled = false;
    double daq_maxWindowSize;

    double vMax() const { return qMax(xmax, ymax); }
    double vMin() const { return qMin(xmin, ymin); }
    long numSamples() const { return total_read; }

private:
    //Those bloody bools that just Enable/Disable a single property
    bool paused_CH1 = false;
    bool paused_CH2 = false;
    bool paused_multimeter = false;
    bool autoGainEnabled = true;
    bool placingHoriAxes = false; // TODO: move into DisplayControl
    bool placingVertAxes = false; // TODO: move into DisplayControl
    bool horiCursorEnabled = false; // TODO: move into DisplayControl
    bool vertCursorEnabled = false; // TODO: move into DisplayControl
    bool triggerEnabled = false;
    bool singleShotEnabled = false;
    bool multimeterShow = true;
    bool autoMultimeterV = true;
    bool autoMultimeterI = true;
    bool autoMultimeterR = true;
    bool autoMultimeterC = true;
    bool forceMillivolts = false;
    bool forceMilliamps = false;
    bool forceKiloOhms = false;
    bool forceUFarads = false;
    bool forceVolts = false;
    bool forceAmps = false;
    bool forceOhms = false;
    bool forceNFarads = false;
    bool serialDecodeEnabled_CH1 = false;
    bool serialDecodeEnabled_CH2 = false;
    bool XYmode = false;
    bool update_CH1 = true;
    bool update_CH2 = true;
    bool snapshotEnabled_CH1 = false;
    bool snapshotEnabled_CH2 = false;
    bool firstFrame = true;
    bool hexDisplay_CH1 = false;
    bool hexDisplay_CH2 = false;
    //Generic Functions
    void analogConvert(short *shortPtr, QVector<double> *doublePtr, int TOP, bool AC, int channel);
    void digitalConvert(short *shortPtr, QVector<double> *doublePtr);
    void fileStreamConvert(float *floatPtr, QVector<double> *doublePtr);
    bool properlyPaused();
    void udateCursors(void);
    short reverseFrontEnd(double voltage);
    void multimeterAction();
    void broadcastStats(bool CH2);
    void frameActionGeneric(const ChannelMode CH1_mode, const ChannelMode CH2_mode);
    void triggerStateChanged();
    //Variables that are just pointers to other classes/vars
    QPointer<QCustomPlot> axes; // TODO: move into DisplayControl
	std::unique_ptr<short[]> readData375_CH1;
	std::unique_ptr<short[]> readData375_CH2;
	std::unique_ptr<short[]> readData750;
    float *readDataFile;
    std::shared_ptr<char[]> isoTemp;
    short *isoTemp_short = nullptr;
    siprint *v0;
    siprint *v1;
    siprint *dv;
    siprint *t0;
    siprint *t1;
    siprint *dt;
    siprint *f;
    //Scope/MM++ related variables
    double currentVmax;
    double currentVmin;
    double currentVRMS;
    double multi = 0;
    double xmin = 20;
    double xmax = -20;
    double ymin = 20;
    double ymax = -20;
    double estimated_resistance = 0;
    int multimeterRsource = 0;
    int triggerMode = 0;
    double m_offset_CH1 = 0;
    double m_offset_CH2 = 0;
    double m_attenuation_CH1 = 1;
    double m_attenuation_CH2 = 1;
    //Pure MM++ related variables
    enum multimeterType_enum {V = 0, I = 1, R = 2, C = 3};
    multimeterType_enum multimeterType = V;
    double seriesResistance = 0;
    // Logic Analyser
    unsigned char serialType = 0;
    i2c::i2cDecoder* twoWire = nullptr;
    bool twoWireStateInvalid = true;
    //Generic Vars
    QTimer* isoTimer = NULL;
    QTimer *slowTimer = NULL;
    QTimer *fileTimer = NULL;
    long total_read = 0;
    unsigned int length;
    QFile *snapshotFile_CH1;
    QFile *snapshotFile_CH2;
    uint8_t deviceMode_prev;
    //DAQ
    double daqLoad_startTime, daqLoad_endTime;

signals:
    void setGain(double newGain);
    void disableWindow(bool enabled);
    void setCursorStatsVisible(bool enabled);
    void sendCursorStatsText(QString text);
    void singleShotTriggered(bool triggered);
    void multimeterMax(double);
    void multimeterMin(double);
    void multimeterMean(double);
    void multimeterRMS(double);
    void sendMultimeterLabel1(QString);
    void sendMultimeterLabel2(QString);
    void sendMultimeterLabel3(QString);
    void sendMultimeterLabel4(QString);
    void sendTriggerValue(double);
    void sendVmax_CH1(double);
    void sendVmin_CH1(double);
    void sendVmean_CH1(double);
    void sendVRMS_CH1(double);
    void sendVmax_CH2(double);
    void sendVmin_CH2(double);
    void sendVmean_CH2(double);
    void sendVRMS_CH2(double);
    void multimeterREnabled(int source);
    void mainWindowPleaseDisableSerial(int);
    void showRealtimeButton(bool visible);
    void topRangeUpdated(double);
    void botRangeUpdated(double);
    void timeWindowUpdated(double);
    void delayUpdated(double);
    void enableCursorGroup(bool);
public slots:
    void setVoltageRange(QWheelEvent *event);
    void timerTick(void);
    void pauseEnable_CH1(bool enabled);
    void pauseEnable_CH2(bool enabled);
    void pauseEnable_multimeter(bool enabled);
    void startTimer();
    void clearBuffers(const isoDriver::Channels channels);
    void setVisible_CH2(bool visible);
    void gainBuffers(double multiplier);
    void gainTick(void);
    void setAutoGain(bool enabled);
    void graphMousePress(QMouseEvent *event);
    void graphMouseRelease(QMouseEvent *event);
    void graphMouseMove(QMouseEvent *event);
    void cursorEnableHori(bool enabled);
    void cursorEnableVert(bool enabled);
    void setTriggerEnabled(bool enabled);
    void setTriggerLevel(double level);
    void setSingleShotEnabled(bool enabled);
    void setTriggerMode(int newMode);
    void setAC_CH1(bool enabled);
    void setAC_CH2(bool enabled);
    void setMultimeterType(int type);
    void setSeriesResistance(double resistance);
    void multimeterStats();
    void enableMM();
    void setAutoMultimeterV(bool enabled);
    void setAutoMultimeterI(bool enabled);
    void setAutoMultimeterR(bool enabled);
    void setAutoMultimeterC(bool enabled);
    void setForceMillivolts(bool enabled);
    void setForceMilliamps(bool enabled);
    void setForceKiloOhms(bool enabled);
    void setForceUFarads(bool enabled);
    void setForceVolts(bool enabled);
    void setForceAmps(bool enabled);
    void setForceOhms(bool enabled);
    void setForceNFarads(bool enabled);
    void setSerialDecodeEnabled_CH1(bool enabled);
    void setSerialDecodeEnabled_CH2(bool enabled);
    void setXYmode(bool enabled);
    void triggerGroupStateChange(bool enabled);
    void slowTimerTick();
    void setTopRange(double newTop);
    void setBotRange(double newBot);
    void setTimeWindow(double newWindow);
    void setDelay(double newDelay);
    void takeSnapshot(QString *fileName, unsigned char channel);
    void rSourceChanged(int newSource);
    void serialNeedsDisabling(int channel);
    void daqLoad_startChanged(double newStart);
    void daqLoad_endChanged(double newEnd);
    void fileTimerTick();
    void enableFileMode();
    void disableFileMode();
	void hideCH1(bool enable);
	void hideCH2(bool enable);
    void offsetChanged_CH1(double newOffset);
    void offsetChanged_CH2(double newOffset);
    void attenuationChanged_CH1(int attenuationIndex);
    void attenuationChanged_CH2(int attenuationIndex);
    void setHexDisplay_CH1(bool enabled);
    void setHexDisplay_CH2(bool enabled);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(isoDriver::Channels);

#endif // ISODRIVER_H
