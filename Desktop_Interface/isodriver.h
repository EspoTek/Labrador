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

class isoBuffer;

//isoDriver is a huge class.  It handles everything related to the isochronous IN stream - and perhaps that constraint was applied a bit too loosely (spot the C programmer...).
//Too much stuff is handled in this class, and it's too heavily entangled with the (generic/win/unix)UsbDriver classes.
//That is one of the things I plan on fixing, and in fact the reason why I began the commenting!

class isoDriver : public QLabel
{
    Q_OBJECT
public:
    explicit isoDriver(QWidget *parent = 0);
    //Generic Vars
    isoBuffer *internalBuffer375_CH1, *internalBuffer375_CH2, *internalBuffer750;
#if QCP_VER == 1
    QCPItemText *cursorTextPtr;
#endif
    genericUsbDriver *driver;
    bool doNotTouchGraph = true;
    double ch1_ref = 1.65, ch2_ref = 1.65;
    double frontendGain_CH1 = (R4/(R3+R4)), frontendGain_CH2 = (R4/(R3+R4));
    //State Vars
    bool AC_CH1 = false, AC_CH2 = false;
    bool cursorStatsEnabled = true;
    int baudRate_CH1 = 9600, baudRate_CH2 = 9600;
    double currentVmean;
    //Display Control Vars     (Variables that control how the buffers are displayed)
    double delay = 0, window = 0.01;
    double y0=0, y1=0, x0=0, x1=0;
    double topRange=2.5, botRange=-0.5;
    //Generic Functions
    void setDriver(genericUsbDriver *newDriver);
    void setAxes(QCustomPlot *newAxes);
    double meanVoltageLast(double seconds, unsigned char channel, int TOP);
private:
    //Those bloody bools that just Enable/Disable a single property
    bool paused_CH1 = false, paused_CH2 = false, paused_multimeter = false;
    bool autoGainEnabled = true;
    bool placingHoriAxes = false, placingVertAxes = false, horiCursorEnabled = false, vertCursorEnabled = false;
    bool triggerSeeking = true;
    bool triggerEnabled = false;
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
    bool serialDecodeEnabled_CH1 = false, serialDecodeEnabled_CH2 = false;
    bool XYmode = false;
    bool update_CH1 = true, update_CH2 = true;
    bool snapshotEnabled = false;
    bool firstFrame = true;
    double triggerDelay;
    bool singleShotEnabled = false;
    //Generic Functions
    void analogConvert(short *shortPtr, QVector<double> *doublePtr, int TOP, bool AC, int channel);
    void digitalConvert(short *shortPtr, QVector<double> *doublePtr);
    bool properlyPaused();
    void autoGain(void);
    void udateCursors(void);
    short reverseFrontEnd(double voltage);
    int trigger(void);
    void multimeterAction();
    void broadcastStats(bool CH2);
    void frameActionGeneric(char CH1_mode, char CH2_mode);
    //Variables that are just pointers to other classes/vars
    QCustomPlot *axes;
    short *readData375_CH1, *readData375_CH2, *readData750;
    char *isoTemp = NULL;
    short *isoTemp_short = NULL;
    siprint *v0, *v1, *dv, *t0, *t1, *dt, *f;
    //Scope/MM++ related variables
    double currentVmax, currentVmin, currentVRMS;
    double triggerLevel = 0;
    enum triggerType_enum {rising_ch1 = 0, falling_ch1 = 1, rising_ch2 = 2, falling_ch2 = 3};
    triggerType_enum triggerType = rising_ch1;
    double multi = 0;
    int triggerCountSeeking = 0, triggerCountNotSeeking = 0;
    unsigned char triggerWaiting = 0;
    double xmin = 20, xmax = -20, ymin = 20, ymax = -20;
    double estimated_resistance = 0;
    int multimeterRsource = 0;
    //Pure MM++ related variables
    enum multimeterType_enum {V = 0, I = 1, R = 2, C = 3};
    multimeterType_enum multimeterType = V;
    double seriesResistance = 0;
    //Generic Vars
    double windowAtPause = 0.01;
    QTimer* isoTimer = NULL, *slowTimer = NULL;
    long total_read = 0;
    unsigned int length;
    QFile *snapshotFile_CH1;
    QFile *snapshotFile_CH2;

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
    void changeTimeAxis(bool positive);
    void sendTriggerValue(double);
    void sendVmax_CH1(double);
    void sendVmin_CH1(double);
    void sendVmean_CH1(double);
    void sendVmax_CH2(double);
    void sendVmin_CH2(double);
    void sendVmean_CH2(double);
    void multimeterREnabled(int source);
public slots:
    void setWindow(int newWindow);
    void setVoltageRange(QWheelEvent *event);
    void timerTick(void);
    void pauseEnable_CH1(bool enabled);
    void pauseEnable_CH2(bool enabled);
    void pauseEnable_multimeter(bool enabled);
    void startTimer();
    void clearBuffers(bool ch3751, bool ch3752, bool ch750);
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
    void takeSnapshot();
    void rSourceChanged(int newSource);
};

#endif // ISODRIVER_H
