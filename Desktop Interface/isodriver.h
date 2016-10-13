#ifndef ISODRIVER_H
#define ISODRIVER_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QVector>
#include "qcustomplot.h"
#include "winusbdriver.h"
#include "desktop_settings.h"
#include "siprint.h"

class isoBuffer;

class isoDriver : public QLabel
{
    Q_OBJECT
public:
    explicit isoDriver(QWidget *parent = 0);
    void setDriver(winUsbDriver *newDriver);
    void setAxes(QCustomPlot *newAxes);
    bool cursorStatsEnabled = true;
    isoBuffer *internalBuffer375_CH1, *internalBuffer375_CH2, *internalBuffer750;
    int baudRate_CH1 = 9600, baudRate_CH2 = 9600;
    double delay = 0, window = 0.01;
    QCPItemText *cursorTextPtr;
    double y0=0, y1=0, x0=0, x1=0;
    double topRange=2.5, botRange=-0.5;
    bool AC_CH1 = false, AC_CH2 = false;
    winUsbDriver *driver;
    double currentVmean;
private:
    QCustomPlot *axes;
    double windowAtPause = 0.01;
    QTimer* isoTimer = NULL, *recoveryTimer = NULL, *slowTimer = NULL;
    short *readData375_CH1, *readData375_CH2, *readData750;
    long total_read = 0;
    void analogConvert(short *shortPtr, QVector<double> *doublePtr, int TOP, bool AC);
    void digitalConvert(short *shortPtr, QVector<double> *doublePtr);
    bool paused_CH1 = false, paused_CH2 = false, paused_multimeter = false;
    void frameActionGeneric(char CH1_mode, char CH2_mode);
    char *isoTemp = NULL;
    short *isoTemp_short = NULL;
    bool properlyPaused();
    void autoGain(void);
    double multi = 0;
    bool autoGainEnabled = true;
    bool placingHoriAxes = false, placingVertAxes = false, horiCursorEnabled = false, vertCursorEnabled = false;
    void udateCursors(void);
    short reverseFrontEnd(double voltage);
    int trigger(void);
    bool triggerSeeking = true;
    bool triggerEnabled = false;
    double triggerLevel = 0;
    enum triggerType_enum {rising_ch1 = 0, falling_ch1 = 1, rising_ch2 = 2, falling_ch2 = 3};
    triggerType_enum triggerType = rising_ch1;
    int length;
    siprint *v0, *v1, *dv, *t0, *t1, *dt, *f;
    bool singleShotEnabled = false;
    double triggerDelay;
    int triggerCountSeeking = 0, triggerCountNotSeeking = 0;
    unsigned char triggerWaiting = 0;
    bool firstFrame = true;
    void multimeterAction();
    double currentVmax, currentVmin;
    enum multimeterType_enum {V = 0, I = 1, R = 2, C = 3};
    multimeterType_enum multimeterType = V;
    double seriesResistance = 0;
    bool multimeterShow = false;
    bool autoMultimeterV = true;
    bool autoMultimeterI = true;
    bool forceMillivolts = false;
    bool forceMilliamps = false;
    bool forceVolts = false;
    bool forceAmps = false;
    bool serialDecodeEnabled_CH1 = false, serialDecodeEnabled_CH2 = false;
    bool XYmode = false;
    double xmin = 20, xmax = -20, ymin = 20, ymax = -20;
    bool update_CH1 = true, update_CH2 = true;
    void broadcastStats(bool CH2);
    bool snapshotEnabled = false;
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
    void sendMultimeterLabel1(QString);
    void sendMultimeterLabel2(QString);
    void sendMultimeterLabel3(QString);
    void changeTimeAxis(bool positive);
    void sendTriggerValue(double);
    void sendVmax_CH1(double);
    void sendVmin_CH1(double);
    void sendVmean_CH1(double);
    void sendVmax_CH2(double);
    void sendVmin_CH2(double);
    void sendVmean_CH2(double);

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
    void setForceMillivolts(bool enabled);
    void setForceMilliamps(bool enabled);
    void setForceVolts(bool enabled);
    void setForceAmps(bool enabled);
    void setSerialDecodeEnabled_CH1(bool enabled);
    void setSerialDecodeEnabled_CH2(bool enabled);
    void setXYmode(bool enabled);
    void triggerGroupStateChange(bool enabled);
    void slowTimerTick();
    void setTopRange(double newTop);
    void setBotRange(double newBot);
    void setTimeWindow(double newWindow);
    void takeSnapshot();
};

#endif // ISODRIVER_H
