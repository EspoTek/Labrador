#include "isodriver.h"
#include "isobuffer.h"
#include "isobuffer_file.h"
#include "platformspecific.h"
#include <math.h>
#include "daqloadprompt.h"


isoDriver::isoDriver(QWidget *parent) : QLabel(parent)
{
    this->hide();
    internalBuffer375_CH1 = new isoBuffer(this, MAX_WINDOW_SIZE*ADC_SPS/20*21, this, 1);
    internalBuffer375_CH2 = new isoBuffer(this, MAX_WINDOW_SIZE*ADC_SPS/20*21, this, 2);
    internalBuffer750 = new isoBuffer(this, MAX_WINDOW_SIZE*ADC_SPS/10*21, this, 1);

    // use malloc, it gives us aligned data
    isoTemp.reset((char *) malloc(TIMER_PERIOD*ADC_SPF + 8), free); //8-byte header contains (unsigned long) length

    char volts[2] = "V";
    char seconds[2] = "s";
    char hertz[3] = "Hz";

    v0 = new siprint(volts, 1234);
    v1 = new siprint(volts, 0);
    dv = new siprint(volts, 0);
    t0 = new siprint(seconds, 0);
    t1 = new siprint(seconds, 0);
    dt = new siprint(seconds, 0);
    f = new siprint(hertz, 0);

    startTimer();

    slowTimer = new QTimer(this);
    slowTimer->setTimerType(Qt::PreciseTimer);
    slowTimer->start(MULTIMETER_PERIOD);
    connect(slowTimer, &QTimer::timeout, this, &isoDriver::slowTimerTick);

    connect(&display, &DisplayControl::delayUpdated, this, &isoDriver::delayUpdated);
    connect(&display, &DisplayControl::timeWindowUpdated, this, &isoDriver::timeWindowUpdated);
    connect(&display, &DisplayControl::topRangeUpdated, this, &isoDriver::topRangeUpdated);
    connect(&display, &DisplayControl::botRangeUpdated, this, &isoDriver::botRangeUpdated);
}

isoDriver::~isoDriver()
{
    delete v0;
    delete v1;
    delete dv;

    delete t0;
    delete t1;
    delete dt;

    delete f;
}

void isoDriver::setDriver(genericUsbDriver *newDriver){
    if (driver) {
        driver->deleteLater();
    }
    driver = newDriver;
    qDebug() << "driver = " << driver;
}

void isoDriver::setAxes(QCustomPlot *newAxes){
    axes = newAxes;
    qDebug() << "axes = " << axes;
}

void isoDriver::timerTick(void){
    //qDebug() << "isoDriver SEZ Tick!";
    if(firstFrame){
        autoGain();
        firstFrame = false;
    }

    isoTemp = driver->isoRead(&length);
    //qDebug() << length << "read in!!";
    total_read += length;

    if(fileModeEnabled){
        qDebug() << "File mode is active.  Abort live refresh";
        return;
    }

    if (length==0){
        //Zero length packet means something's gone wrong.  Probably a disconnect.
        qDebug() << "Zero length iso packet!";
        //driver->killMe();
        return;
    }

    // TODO: Do we need to invalidate state when the device is reconnected?
    bool invalidateTwoWireState = true;
    switch(driver->deviceMode){
        case DeviceCH1Analog:
            if (deviceMode_prev != DeviceCH1Analog && deviceMode_prev != DeviceCH1AnalogCH2Digital && deviceMode_prev != DeviceCH1AnalogCH2Analog) {
                clearBuffers(Channel3751);
            }

            frameActionGeneric(ChannelMode::Analog, ChannelMode::Off);
            break;
        case DeviceCH1AnalogCH2Digital:
            if (deviceMode_prev != DeviceCH1Analog && deviceMode_prev != 1 && deviceMode_prev != DeviceCH1AnalogCH2Analog) {
                clearBuffers(Channel3751);
            }

            if (deviceMode_prev != DeviceCH1AnalogCH2Digital) {
                clearBuffers(Channel3752);
            }

            internalBuffer375_CH2->m_channel = 1;
            frameActionGeneric(ChannelMode::Analog, ChannelMode::Digital);
            if(serialDecodeEnabled_CH1 && serialType == 0){
                internalBuffer375_CH2->serialManage(baudRate_CH1, parity_CH1, hexDisplay_CH1);
            }
            break;
        case DeviceCH1AnalogCH2Analog:
            if (deviceMode_prev != DeviceCH1Analog  && deviceMode_prev != DeviceCH1AnalogCH2Digital  && deviceMode_prev != DeviceCH1AnalogCH2Analog) {
                clearBuffers(Channel3751);
            }
            if (deviceMode_prev != DeviceCH1AnalogCH2Analog) {
                clearBuffers(Channel3752);
            }

            frameActionGeneric(ChannelMode::Analog, ChannelMode::Analog);
            break;
        case DeviceCH1Digital:
            if (deviceMode_prev != DeviceCH1Digital  && deviceMode_prev != DeviceCH1DigitalCH2Digital) {
                clearBuffers(Channel3751);
            }

            frameActionGeneric(ChannelMode::Digital, ChannelMode::Off);
            if(serialDecodeEnabled_CH1 && serialType == 0){
                internalBuffer375_CH1->serialManage(baudRate_CH1, parity_CH1, hexDisplay_CH1);
            }
            break;
        case DeviceCH1DigitalCH2Digital:
            if (deviceMode_prev != DeviceCH1Digital && deviceMode_prev != DeviceCH1DigitalCH2Digital) {
                clearBuffers(Channel3751);
            }
            if (deviceMode_prev != DeviceCH1DigitalCH2Digital) {
                clearBuffers(Channel3752);
            }

            internalBuffer375_CH2->m_channel = 2;
            frameActionGeneric(ChannelMode::Digital, ChannelMode::Digital);
            if(serialDecodeEnabled_CH1 && serialType == 0){
                internalBuffer375_CH1->serialManage(baudRate_CH1, parity_CH1, hexDisplay_CH1);
            }
            if(serialDecodeEnabled_CH2 && serialType == 0){
                internalBuffer375_CH2->serialManage(baudRate_CH2, parity_CH2, hexDisplay_CH2);
            }
            if (serialDecodeEnabled_CH1 && serialType == 1)
            {
                if (twoWireStateInvalid)
                    twoWire->reset();
                try
                {
                    twoWire->run();
                }
                catch(...)
                {
                    qDebug() << "Resetting I2C";
                    twoWire->reset();
                }
                invalidateTwoWireState = false;
                twoWireStateInvalid = false;
            }
            break;
        case 5:
            break;
        case DeviceCH1Analog750:
            if (deviceMode_prev != DeviceCH1Analog750) {
                clearBuffers(Channel750);
            }
            frameActionGeneric(ChannelMode::Analog750, ChannelMode::Off);
            break;
        case DeviceMultimeter:
            if (deviceMode_prev != DeviceMultimeter) {
                clearBuffers(Channel3751);
            }
            multimeterAction();
            break;
        default:
            qFatal("Error in isoDriver::timerTick.  Invalid device mode.");
    }
    if (invalidateTwoWireState)
        twoWireStateInvalid = true;

    deviceMode_prev = driver->deviceMode;
    //free(isoTemp);
}

void isoDriver::analogConvert(short *shortPtr, QVector<double> *doublePtr, int TOP, bool AC, int channel){

    double scope_gain = (double)(driver->scopeGain);
    double accumulated = 0;
    double accumulated_square = 0;
    currentVmax = -20;
    currentVmin = 20;

    double ref = (channel == 1 ? ch1_ref : ch2_ref);
    double frontendGain = (channel == 1 ? frontendGain_CH1 : frontendGain_CH2);

    double *data = doublePtr->data();
    for (int i=0;i<GRAPH_SAMPLES;i++){
        data[i] = (shortPtr[i] * (vcc/2)) / (frontendGain*scope_gain*TOP);
        if (driver->deviceMode != DeviceMultimeter) data[i] += ref;
        #ifdef INVERT_MM
            if(driver->deviceMode == DeviceMultimeter) data[i] *= -1;
        #endif

        accumulated += data[i];
        accumulated_square += data[i] * data[i];
        if (data[i] > currentVmax) currentVmax = data[i];
        if (data[i] < currentVmin) currentVmin = data[i];
    }
    currentVmean  = accumulated / GRAPH_SAMPLES;
    currentVRMS = sqrt(accumulated_square / GRAPH_SAMPLES);
    if(AC){
        //Previous measurments are wrong, edit and redo.
        accumulated = 0;
        accumulated_square = 0;
        currentVmax = -20;
        currentVmin = 20;

        for (int i=0;i<GRAPH_SAMPLES;i++){
            data[i] -= currentVmean;

            accumulated += data[i];
            accumulated_square += (data[i] * data[i]);
            if (data[i] > currentVmax) currentVmax = data[i];
            if (data[i] < currentVmin) currentVmin = data[i];
        }
        currentVmean  = accumulated / GRAPH_SAMPLES;
        currentVRMS = sqrt(accumulated_square / GRAPH_SAMPLES);
    }
    //cool_waveform = cool_waveform - AC_offset;
}

void isoDriver::digitalConvert(short *shortPtr, QVector<double> *doublePtr){

    double *data = doublePtr->data();
    double top = display.topRange - (display.topRange - display.botRange) / 10;
    double bot = display.botRange + (display.topRange - display.botRange) / 10;
    for (int i=0;i<GRAPH_SAMPLES;i++){
        data[i] = shortPtr[i] ? top : bot;
    }
    //cool_waveform = cool_waveform - AC_offset;
}

void isoDriver::fileStreamConvert(float *floatPtr, QVector<double> *doublePtr){
    double *data = doublePtr->data();
    for (int i=0;i<GRAPH_SAMPLES;i++){
        data[i] = floatPtr[i];
    }
}


void isoDriver::startTimer(){
    /*if (isoTimer!=NULL){
        delete isoTimer;
        isoTimer = NULL;
    }
    isoTimer = new QTimer();
    isoTimer->setTimerType(Qt::PreciseTimer);
    isoTimer->start(TIMER_PERIOD);
    connect(isoTimer, SIGNAL(timeout()), this, SLOT(timerTick()));
    //qFatal("ISO TIMER STARTED");*/
}

void isoDriver::clearChannelBuffers(bool ch3751, bool ch3752, bool ch750){
    if(ch3751) internalBuffer375_CH1->clearBuffer();
    if(ch3752) internalBuffer375_CH2->clearBuffer();
    if(ch750) internalBuffer750->clearBuffer();
    total_read = 0;
}

void isoDriver::clearBuffers(const Channels channels)
{
    if (channels & Channel3751) {
        internalBuffer375_CH1->clearBuffer();
    }
    if (channels & Channel3752) {
        internalBuffer375_CH2->clearBuffer();
    }
    if (channels & Channel750) {
        internalBuffer750->clearBuffer();
    }

    total_read = 0;
}

void isoDriver::setVisible_CH2(bool visible){
    axes->graph(1)->setVisible(visible);
}

void isoDriver::onWheelEvent(QWheelEvent* event)
{
    if(doNotTouchGraph && !fileModeEnabled) return;

    bool isProperlyPaused = properlyPaused();
    double maxWindowSize = fileModeEnabled ? daq_maxWindowSize : ((double)MAX_WINDOW_SIZE);

    display.setVoltageRange(event->position(), event->angleDelta(), event->modifiers(), isProperlyPaused, maxWindowSize, axes);

    if (!(event->modifiers() == Qt::ControlModifier))
        if (autoGainEnabled && !isProperlyPaused)
            autoGain();
}

bool isoDriver::properlyPaused(){
    if(paused_CH1 & paused_CH2){
        qDebug() << "Properly paused";
        return true;
    }
    if ((driver->deviceMode == DeviceCH1Analog) || (driver->deviceMode == DeviceCH1Digital) || (driver->deviceMode == DeviceCH1Analog750)){
        if(paused_CH1) qDebug() << "Properly paused"; else qDebug() << "Not properly paused";
        return paused_CH1;
    }
    if(paused_multimeter){
        qDebug() << "Properly paused";
        return true;
    }
    qDebug() << "Not properly paused";
    return false;
}

void isoDriver::pauseEnable_CH1(bool enabled){
    paused_CH1 = enabled;

    if(!properlyPaused()) {
        display.delay = 0;
        emit delayUpdated(display.delay);
        if (autoGainEnabled) autoGain();
    }

    if (!enabled) {
        clearBuffers(Channel3751 | Channel750);
    }
    qDebug() << "pauseEnable_CH1" << enabled;
}


void isoDriver::pauseEnable_CH2(bool enabled){
    paused_CH2 = enabled;

    if(!properlyPaused()){
        display.delay = 0;
        emit delayUpdated(display.delay);
        if (autoGainEnabled) autoGain();
    }

    if (!enabled) {
        clearBuffers(Channel3752);
    }
    qDebug() << "pauseEnable_CH2" << enabled;
}

void isoDriver::pauseEnable_multimeter(bool enabled){
    paused_multimeter = enabled;

    if(!properlyPaused()) {
        display.delay = 0;
        emit delayUpdated(display.delay);
    }

    if (!enabled) {
        clearBuffers(Channel3751);
    }
    qDebug() << "pauseEnable_multimeter" << enabled;
}


void isoDriver::autoGain(){
    double maxgain = vcc / (2 * ((double)display.topRange - vref) * R4/(R3+R4));
    double mingain = vcc / (2 * ((double)display.botRange - vref) * R4/(R3+R4));
    maxgain = fmin(fabs(mingain) * 0.98, fabs(maxgain) * 0.98);

    double snap[8] = {64, 32, 16, 8, 4, 2, 1, 0.5};

    for (int i=0;i<8;i++){
        if (maxgain>snap[i]){
            setGain(snap[i]);
            return;
        }
    }
}

void isoDriver::gainBuffers(double multiplier){
    multi = multiplier;
    QTimer::singleShot(TIMER_PERIOD*4, this, SLOT(gainTick()));
}

void isoDriver::gainTick(void){
#ifdef PLATFORM_ANDROID
#warning: "gainTick does nothing on Android!!"
#else
    qDebug() << "Multiplying by " << multi;
    if (driver->deviceMode <= DeviceCH1DigitalCH2Digital) {
        internalBuffer375_CH1->gainBuffer(log2(multi));
    }

    switch(driver->deviceMode) {
    case DeviceCH1AnalogCH2Digital:
    case DeviceCH1AnalogCH2Analog:
    case DeviceCH1DigitalCH2Digital:
        internalBuffer375_CH2->gainBuffer(log2(multi));
        break;
    case DeviceCH1Analog750:
    case DeviceMultimeter:
        internalBuffer750->gainBuffer(log2(multi));
        break;
    default:
        qWarning() << "Invalid device mode" << driver->deviceMode;
        break;
    }
#endif
}

void isoDriver::setAutoGain(bool enabled){
    autoGainEnabled = enabled;
    if(enabled){
        autoGain();
    }
}

void isoDriver::graphMousePress(QMouseEvent *event){
    qDebug() << event->button();
    if (horiCursorEnabled && (event->button() == Qt::LeftButton)){
        placingHoriAxes = true;
        display.y0 = axes->yAxis->pixelToCoord(event->y());
#ifndef PLATFORM_ANDROID
    }else if(vertCursorEnabled && (event->button() == Qt::RightButton)){
#else
    }if(vertCursorEnabled){
#endif
        placingVertAxes = true;
        display.x0 = axes->xAxis->pixelToCoord(event->x());
    }
    qDebug() << "x0 =" << display.x0 << "x1 =" << display.x1 << "y0 =" << display.y0 << "y1 =" << display.y1;
}

void isoDriver::graphMouseRelease(QMouseEvent *event){
    if(horiCursorEnabled && placingHoriAxes && (event->button() == Qt::LeftButton)){
        placingHoriAxes = false;
#ifndef PLATFORM_ANDROID
    } else if (vertCursorEnabled && placingVertAxes && (event->button() == Qt::RightButton)){
#else
    } if (vertCursorEnabled && placingVertAxes){
#endif
        placingVertAxes = false;
    }
    qDebug() << "x0 =" << display.x0 << "x1 =" << display.x1 << "y0 =" << display.y0 << "y1 =" << display.y1;
}

void isoDriver::graphMouseMove(QMouseEvent *event){
    if(horiCursorEnabled && placingHoriAxes){
        display.y1 = axes->yAxis->pixelToCoord(event->y());
#ifndef PLATFORM_ANDROID
    } else if(vertCursorEnabled && placingVertAxes){
#else
    } if(vertCursorEnabled && placingVertAxes){
#endif
        display.x1 = axes->xAxis->pixelToCoord(event->x());
    }
}

void isoDriver::cursorEnableHori(bool enabled){
    horiCursorEnabled = enabled;
    axes->graph(4)->setVisible(enabled);
    axes->graph(5)->setVisible(enabled);
}

void isoDriver::cursorEnableVert(bool enabled){
    vertCursorEnabled = enabled;
    axes->graph(2)->setVisible(enabled);
    axes->graph(3)->setVisible(enabled);
}

void isoDriver::udateCursors(void){
    if(!(vertCursorEnabled || horiCursorEnabled)){
        cursorTextPtr->setVisible(false);
        return;
    }

    QVector<double> vert0x(2), vert1x(2), hori0x(2), hori1x(2), vert0y(2), vert1y(2), hori0y(2), hori1y(2);

    vert0x[0] = display.x0;
    vert0x[1] = display.x0;
    vert0y[0] = display.botRange;
    vert0y[1] = display.topRange;

    vert1x[0] = display.x1;
    vert1x[1] = display.x1;
    vert1y[0] = display.botRange;
    vert1y[1] = display.topRange;

    hori0x[0] = -display.window - display.delay;
    hori0x[1] = -display.delay;
    hori0y[0] = display.y0;
    hori0y[1] = display.y0;

    hori1x[0] = -display.window - display.delay;
    hori1x[1] = -display.delay;
    hori1y[0] = display.y1;
    hori1y[1] = display.y1;

    if(vertCursorEnabled){
        axes->graph(2)->setData(vert0x, vert0y);
        axes->graph(3)->setData(vert1x, vert1y);
    }
    if(horiCursorEnabled){
        axes->graph(4)->setData(hori0x, hori0y);
        axes->graph(5)->setData(hori1x, hori1y);
    }

    cursorTextPtr->setVisible(cursorStatsEnabled);

    if (!cursorStatsEnabled) return;

    QString cursorStatsString;

    v0->value = display.y0;
    v1->value = display.y1;
    dv->value = display.y0-display.y1;
    t0->value = display.x0;
    t1->value = display.x1;
    dt->value = fabs(display.x0 - display.x1);
    f->value = display.x1 != display.x0 ? 1 / (display.x1 - display.x0) : 0.;

    const QString temp_hori = QString::asprintf("V0=%s,  V1=%s,  ΔV=%s", v0->printVal(), v1->printVal(), dv->printVal());
    const QString temp_vert = QString::asprintf("t0=%s, t1=%s,  Δt=%s,  f=%s", t0->printVal(), t1->printVal(), dt->printVal(), f->printVal());

    if(horiCursorEnabled) cursorStatsString.append(temp_hori);
    if(horiCursorEnabled && vertCursorEnabled) cursorStatsString.append("\n");
    if(vertCursorEnabled) cursorStatsString.append(temp_vert);
    cursorTextPtr->setText(cursorStatsString);
}

short isoDriver::reverseFrontEnd(double voltage){
    //qFatal("reverseFrontEnd driver mode 7");
    #ifdef INVERT_MM
        if(driver->deviceMode == DeviceMultimeter) voltage *= -1;
    #endif


    double vn = vcc * (R2/(R1+R2));
    double vx = vn + (voltage - vn) * (R4 / (R3+R4));
    double TOP = (driver->deviceMode == DeviceMultimeter) ? 2048 : 128;

    if (driver->deviceMode == DeviceMultimeter){
        qDebug() << "SEEEKING";
        qDebug() <<  ((vx - vn)/vref * (double)driver->scopeGain * (double)TOP + (double)0.5);
        qDebug() << "SEEEKING";
        return ((vx - vn)/vref * (double)driver->scopeGain * (double)TOP + (double)0.5);
    }

    //qDebug() << "seeking" << voltage << "V";


    return ((vx - vn)/vref * (double)driver->scopeGain * (double)TOP + (double)0.5);
}

void isoDriver::setTriggerEnabled(bool enabled)
{
    triggerEnabled = enabled;
    triggerStateChanged();
}

void isoDriver::setTriggerLevel(double level)
{
    internalBuffer375_CH1->setTriggerLevel(level, (driver->deviceMode == DeviceMultimeter ? 2048 : 128), AC_CH1);
    internalBuffer375_CH2->setTriggerLevel(level, 128, AC_CH2);
    internalBuffer750->setTriggerLevel(level, 128, AC_CH1);
    triggerStateChanged();
}

void isoDriver::setSingleShotEnabled(bool enabled)
{
    singleShotEnabled = enabled;
    triggerStateChanged();
}

void isoDriver::setTriggerMode(int newMode)
{
    triggerMode = newMode;
    triggerStateChanged();
}

//0 for off, 1 for ana, 2 for dig, -1 for ana750, -2 for file
void isoDriver::frameActionGeneric(const ChannelMode CH1_mode, const ChannelMode CH2_mode)
{
    //qDebug() << "made it to frameActionGeneric";
    if(!paused_CH1 && CH1_mode == ChannelMode::Analog750) {
        for (unsigned int i=0;i<(length/ADC_SPF);i++){
            internalBuffer750->writeBuffer_char(&isoTemp[ADC_SPF*i], VALID_DATA_PER_750);
        }
    }

    if(!paused_CH1 && (CH1_mode == ChannelMode::Analog || CH1_mode == ChannelMode::Digital)){
        for (unsigned int i=0;i<(length/ADC_SPF);i++){
            internalBuffer375_CH1->writeBuffer_char(&isoTemp[ADC_SPF*i], VALID_DATA_PER_375);
        }
    }

    if(!paused_CH2 && (CH2_mode == ChannelMode::Analog || CH2_mode == ChannelMode::Digital)){
        for (unsigned int i=0;i<(length/ADC_SPF);i++){
            internalBuffer375_CH2->writeBuffer_char(&isoTemp[ADC_SPF*i+ADC_SPF/2], VALID_DATA_PER_375);  //+375 to get the second half of the packet
        }
    }

    double triggerDelay = 0;
    if (triggerEnabled)
    {
        isoBuffer* internalBuffer_CH1 = (CH1_mode == ChannelMode::Analog750) ? internalBuffer750 : internalBuffer375_CH1;
        triggerDelay = (triggerMode < 2) ? internalBuffer_CH1->getDelayedTriggerPoint(display.window) - display.window : internalBuffer375_CH2->getDelayedTriggerPoint(display.window) - display.window;

        if (triggerDelay < 0)
            triggerDelay = 0;
    }

    if(singleShotEnabled && (triggerDelay != 0))
        singleShotTriggered(true);

    readData375_CH1 = internalBuffer375_CH1->readBuffer(display.window,GRAPH_SAMPLES,CH1_mode==ChannelMode::Digital, display.delay + triggerDelay);
    if(CH2_mode != ChannelMode::Off) readData375_CH2 = internalBuffer375_CH2->readBuffer(display.window,GRAPH_SAMPLES, CH2_mode==ChannelMode::Digital, display.delay + triggerDelay);
    if(CH1_mode == ChannelMode::Analog750) readData750 = internalBuffer750->readBuffer(display.window,GRAPH_SAMPLES,false, display.delay + triggerDelay);
    if(CH1_mode == ChannelMode::File) readDataFile = internalBufferFile->readBuffer(display.window,GRAPH_SAMPLES,false, display.delay);

    QVector<double> x(GRAPH_SAMPLES), CH1(GRAPH_SAMPLES), CH2(GRAPH_SAMPLES);

    if (CH1_mode == ChannelMode::Analog){
        analogConvert(readData375_CH1.get(), &CH1, 128, AC_CH1, 1);
        for (int i=0; i < GRAPH_SAMPLES; i++)
        {
            CH1[i] /= m_attenuation_CH1;
            CH1[i] += m_offset_CH1;
        }
        xmin = (currentVmin < xmin) ? currentVmin : xmin;
        xmax = (currentVmax > xmax) ? currentVmax : xmax;
        broadcastStats(false);
    }
    if (CH1_mode == ChannelMode::Digital) digitalConvert(readData375_CH1.get(), &CH1);

    if (CH2_mode == ChannelMode::Analog){
        analogConvert(readData375_CH2.get(), &CH2, 128, AC_CH2, 2);
        for (int i=0; i < GRAPH_SAMPLES; i++)
        {
            CH2[i] /= m_attenuation_CH2;
            CH2[i] += m_offset_CH2;
        }
        ymin = (currentVmin < ymin) ? currentVmin : ymin;
        ymax = (currentVmax > ymax) ? currentVmax : ymax;
        broadcastStats(true);
    }
    if (CH2_mode == ChannelMode::Digital) digitalConvert(readData375_CH2.get(), &CH2);

    if(CH1_mode == ChannelMode::Analog750) {
        analogConvert(readData750.get(), &CH1, 128, AC_CH1, 1);
        xmin = (currentVmin < xmin) ? currentVmin : xmin;
        xmax = (currentVmax > xmax) ? currentVmax : xmax;
        broadcastStats(false);
    }

    if(CH1_mode == ChannelMode::File) {
        fileStreamConvert(readDataFile, &CH1);
    }


    for (int i=0; i<GRAPH_SAMPLES; i++){
        x[i] = -(display.window*i)/((double)(GRAPH_SAMPLES-1)) - display.delay;
        if (x[i]>0) {
            CH1[i] = 0;
            CH2[i] = 0;
        }
    }

    udateCursors();

    if(XYmode){
        QCPCurve* curve = reinterpret_cast<QCPCurve*>(axes->plottable(0));
        curve->setData(CH1, CH2);
        axes->xAxis->setRange(xmin, xmax);
        axes->yAxis->setRange(ymin, ymax);
    }else{
        axes->graph(0)->setData(x,CH1);
        if(CH2_mode != ChannelMode::Off) axes->graph(1)->setData(x,CH2);
        axes->xAxis->setRange(-display.window - display.delay, -display.delay);
        axes->yAxis->setRange(display.topRange, display.botRange);
    }

    if(snapshotEnabled_CH1){
        snapshotFile_CH1->open(QIODevice::WriteOnly);
        snapshotFile_CH1->write("t, v\n");

        char tempchar[32];
        for(int i=0; i<GRAPH_SAMPLES; i++){
            sprintf(tempchar, "%f, %f\n", x.at(i), CH1.at(i));
            snapshotFile_CH1->write(tempchar);
        }
        snapshotEnabled_CH1 = false;
        snapshotFile_CH1->close();
        delete(snapshotFile_CH1);
    }

    if(snapshotEnabled_CH2){
        snapshotFile_CH2->open(QIODevice::WriteOnly);
        snapshotFile_CH2->write("t, v\n");

        char tempchar[32];
        for(int i=0; i<GRAPH_SAMPLES; i++){
            sprintf(tempchar, "%f, %f\n", x.at(i), CH2.at(i));
            snapshotFile_CH2->write(tempchar);
        }
        snapshotEnabled_CH2 = false;
        snapshotFile_CH2->close();
        delete(snapshotFile_CH2);
    }

    axes->replot();
}

void isoDriver::multimeterAction(){
    isoTemp_short = (short *)isoTemp.get();
    if(!paused_multimeter){
        for (unsigned int i=0;i<(length/ADC_SPF);i++){
            internalBuffer375_CH1->writeBuffer_short(&isoTemp_short[ADC_SPF/2*i], ADC_SPF/2-1);  //Offset because the first 8 bytes of the array contain the length (no samples!!)!
        }
    }

    double triggerDelay = 0;
    if (triggerEnabled)
    {
        triggerDelay = internalBuffer375_CH1->getDelayedTriggerPoint(display.window) - display.window;

        if (triggerDelay < 0)
            triggerDelay = 0;
    }

    if(singleShotEnabled && (triggerDelay != 0)) {
        singleShotTriggered(true);
    }
    
	readData375_CH1 = internalBuffer375_CH1->readBuffer(display.window,GRAPH_SAMPLES, false, display.delay + triggerDelay);

    QVector<double> x(GRAPH_SAMPLES), CH1(GRAPH_SAMPLES);
    analogConvert(readData375_CH1.get(), &CH1, 2048, false, 1);  //No AC coupling!

    for (int i=0; i<GRAPH_SAMPLES; i++){
        x[i] = -(display.window*i)/((double)(GRAPH_SAMPLES-1)) - display.delay;
        if (x[i]>0) {
            CH1[i] = 0;
        }
    }
    axes->graph(0)->setData(x,CH1);

    udateCursors();

    axes->xAxis->setRange(-display.window - display.delay, -display.delay);
    axes->yAxis->setRange(display.topRange, display.botRange);

    axes->replot();
    multimeterStats();
}

void isoDriver::setAC_CH1(bool enabled){
    AC_CH1 = enabled;
}

void isoDriver::setAC_CH2(bool enabled){
    AC_CH2 = enabled;
}

void isoDriver::setMultimeterType(int type){
    multimeterType = (multimeterType_enum) type;
    switch (type){

    case R:
        multimeterREnabled(multimeterRsource);
        break;
    case C:
        multimeterREnabled(254);
        break;
    default:
        multimeterREnabled(255);
    }

    qDebug() << "multimeterType = " << multimeterType;
}

void isoDriver::setSeriesResistance(double resistance){
    seriesResistance = resistance;
    qDebug() << "seriesResistance = " << seriesResistance;
}

void isoDriver::multimeterStats(){
    //qDebug() << "Entering isoDriver::multimeterStats()";
    if (!multimeterShow) return;

    QTimer::singleShot(MULTIMETER_PERIOD, this, SLOT(enableMM()));

    multimeterShow = false;
    bool mvMax = false;
    bool mvMin = false;
    bool mvMean = false;
    bool mvRMS = false;
    bool maMax = false;
    bool maMin = false;
    bool maMean = false;
    bool maRMS = false;
    bool kOhms = false;
    bool uFarads = false;  //We'll let the compiler work out this one.

    if(autoMultimeterV){
        mvMax = abs(currentVmax) < 1.;
        mvMin = abs(currentVmin) < 1.;
        mvMean = abs(currentVmean) < 1.;
        mvRMS = abs(currentVRMS) < 1.;
    }
    if(autoMultimeterI){
        maMax = abs(currentVmax / seriesResistance) < 1.;
        maMin = abs(currentVmin / seriesResistance) < 1.;
        maMean = abs(currentVmean / seriesResistance) < 1.;
        maRMS = abs(currentVRMS / seriesResistance) < 1.;
    }

    if(forceMillivolts){
        mvMax = true;
        mvMin = true;
        mvMean = true;
        mvRMS = true;
    }
    if(forceMilliamps){
        maMax = true;
        maMin = true;
        maMean = true;
        maRMS = true;
    }
    if(forceKiloOhms){
        kOhms = true;
    }
    if(forceUFarads){
        uFarads = true;
    }

    if(forceVolts){
        mvMax = false;
        mvMin = false;
        mvMean = false;
        mvRMS = false;
    }
    if(forceAmps){
        maMax = false;
        maMin = false;
        maMean = false;
        maRMS = false;
    }
    if(forceOhms){
        kOhms = false;
    }
    if(forceNFarads){
        uFarads = false;
    }

    if(multimeterType == V){
        if(mvMax){
            currentVmax *= 1000;
            sendMultimeterLabel1("Max (mV)");
        }else sendMultimeterLabel1("Max (V)");

        if(mvMin){
            currentVmin *= 1000;
            sendMultimeterLabel2("Min (mV)");
        }else sendMultimeterLabel2("Min (V)");

        if(mvMean){
            currentVmean *= 1000;
            sendMultimeterLabel3("Mean (mV)");
        }else sendMultimeterLabel3("Mean (V)");

        if(mvRMS){
            currentVRMS *= 1000;
            sendMultimeterLabel4("RMS (mV)");
        }else sendMultimeterLabel4("RMS (V)");

        multimeterMax(currentVmax);
        multimeterMin(currentVmin);
        multimeterMean(currentVmean);
        multimeterRMS(currentVRMS);
        return;
    }

    if(multimeterType == I){
        if(maMax){
            currentVmax *= 1000;
            sendMultimeterLabel1("Max (mA)");
        }else sendMultimeterLabel1("Max (A)");

        if(maMin){
            currentVmin *= 1000;
            sendMultimeterLabel2("Min (mA)");
        }else sendMultimeterLabel2("Min (A)");

        if(maMean){
            currentVmean *= 1000;
            sendMultimeterLabel3("Mean (mA)");
        }else sendMultimeterLabel3("Mean (A)");

        if(maRMS){
            currentVRMS *= 1000;
            sendMultimeterLabel4("RMS (mA)");
        }else sendMultimeterLabel4("RMS (A)");


        multimeterMax(currentVmax / seriesResistance);
        multimeterMin(currentVmin / seriesResistance);
        multimeterMean(currentVmean / seriesResistance);
        multimeterRMS(currentVRMS / seriesResistance);
        return;
    }

    if(multimeterType == R){
        if(estimated_resistance!=estimated_resistance){
            estimated_resistance = 0; //Reset resistance if it's NaN
        }
        double Vm = meanVoltageLast((double)MULTIMETER_PERIOD/(double)1000, 1, 2048);
        double rtest_para_r = 1/(1/seriesResistance + 1/estimated_resistance);
        double perturbation = ch2_ref * (rtest_para_r / (R3 + R4 + rtest_para_r));
        Vm = Vm - perturbation;
        double Vin = (multimeterRsource * 2) + 3;
        double Vrat = (Vin-Vm)/Vin;
        double Rp = 1/(1/seriesResistance + 1/(R3+R4));
        estimated_resistance = ((1-Vrat)/Vrat) * Rp; //Perturbation term on V2 ignored.  V1 = Vin.  V2 = Vin(Rp/(R+Rp)) + Vn(Rtest||R / (R34 + (Rtest||R34));
        //qDebug() << "Vm = " << Vm;
        //qDebug() << "Vin = " << Vin;
        //qDebug() << "perturbation = " << perturbation;
        //qDebug() << "Vrat = " << Vrat;
        //qDebug() << "Rp = " << Rp;
        //qDebug() << "estimated_resistance = " << estimated_resistance;
        multimeterMax(0);
        multimeterMin(0);
        multimeterMean(0);

        if(autoMultimeterR){
            kOhms = (estimated_resistance) > 1000;
        }

        if(kOhms){
            estimated_resistance /= 1000;
            sendMultimeterLabel4("Resistance (kΩ)");
        }else sendMultimeterLabel4("Resistance (Ω)");
        multimeterRMS(estimated_resistance);
    }
    if(multimeterType == C){
        double cap_vbot = 0.8;
        double cap_vtop = 2.5;

        int cap_x0 = internalBuffer375_CH1->cap_x0fromLast(1, cap_vbot);
        if(cap_x0 == -1){
            qDebug() << "cap_x0 == -1";
            return;
        }
        int cap_x1 = internalBuffer375_CH1->cap_x1fromLast(1, cap_x0, cap_vbot);
        if(cap_x1 == -1){
            qDebug() << "cap_x1 == -1";
            return;
        }
        int cap_x2 = internalBuffer375_CH1->cap_x2fromLast(1, cap_x1, cap_vtop);
        if(cap_x2 == -1){
            qDebug() << "cap_x2 == -1";
            return;
        }
        qDebug() << "x0 = " << cap_x0;
        qDebug() << "x1 = " << cap_x1;
        qDebug() << "x2 = " << cap_x2;
        qDebug() << "dt = " << cap_x2-cap_x1;

        double dt = (double)(cap_x2-cap_x1)/internalBuffer375_CH1->m_samplesPerSecond;
        double Cm = -dt/(seriesResistance * log((vcc-cap_vtop)/(vcc-cap_vbot)));
        qDebug() << "Cm = " << Cm;

        if(autoMultimeterC){
            uFarads = (Cm) > 1e-6;
        }

        if(uFarads){
            sendMultimeterLabel4("Capacitance (μF)");
            Cm = Cm*1000000;
        } else {
            sendMultimeterLabel4("Capacitance (nF)");
            Cm = Cm*1000000000;
        }
        multimeterRMS(Cm);
    }

}

void isoDriver::enableMM(){
    multimeterShow = true;
}


void isoDriver::setAutoMultimeterV(bool enabled){
    autoMultimeterV = enabled;
}

void isoDriver::setAutoMultimeterI(bool enabled){
    autoMultimeterI = enabled;
}

void isoDriver::setAutoMultimeterR(bool enabled){
    autoMultimeterR = enabled;
}

void isoDriver::setAutoMultimeterC(bool enabled){
    autoMultimeterC = enabled;
}

void isoDriver::setForceMillivolts(bool enabled){
    forceMillivolts = enabled;
}

void isoDriver::setForceMilliamps(bool enabled){
    forceMilliamps = enabled;
}

void isoDriver::setForceKiloOhms(bool enabled){
    forceKiloOhms = enabled;
}

void isoDriver::setForceUFarads(bool enabled){
    forceUFarads = enabled;
}

void isoDriver::setForceVolts(bool enabled){
    forceVolts = enabled;
}

void isoDriver::setForceAmps(bool enabled){
    forceAmps = enabled;
}

void isoDriver::setForceOhms(bool enabled){
    forceOhms = enabled;
}

void isoDriver::setForceNFarads(bool enabled){
    forceNFarads = enabled;
}

void isoDriver::setSerialDecodeEnabled_CH1(bool enabled){
    serialDecodeEnabled_CH1 = enabled;
}

void isoDriver::setSerialDecodeEnabled_CH2(bool enabled){
    serialDecodeEnabled_CH2 = enabled;
}

void isoDriver::setXYmode(bool enabled){
    int graphCount = axes->graphCount();
    static QVector<bool> graphState;
    graphState.resize(graphCount);

    if(enabled)  // Hide graphs - we only want the X-Y plot to appear
    {
        xmin = 20;
        xmax = -20;
        ymin = 20;
        ymax = -20;

        for (int i=0; i < graphCount; i++)
        {
            qDebug() << "isVisible" << axes->graph(i)->visible();
            graphState[i] = axes->graph(i)->visible();
            axes->graph(i)->setVisible(false);
        }
    }
    else  // Restore State
    {
        for (int i=0; i < graphCount; i++)
        {
            qDebug() << "graphState" << graphState[i];
            axes->graph(i)->setVisible(graphState[i]);
        }
    }
    
    QCPCurve* curve = reinterpret_cast<QCPCurve*>(axes->plottable(0));
    curve->setVisible(enabled);
    emit enableCursorGroup(!enabled);
    XYmode = enabled;
}

void isoDriver::triggerGroupStateChange(bool enabled){
    if(enabled) sendTriggerValue((currentVmax-currentVmin)*0.85 + currentVmin);
}

void isoDriver::broadcastStats(bool CH2){
    if(CH2){
        if(!update_CH2) return;
        update_CH2 = false;
        sendVmax_CH2(currentVmax);
        sendVmin_CH2(currentVmin);
        sendVmean_CH2(currentVmean);
        sendVRMS_CH2(currentVRMS);
    } else{
        if(!update_CH1) return;
        update_CH1 = false;
        sendVmax_CH1(currentVmax);
        sendVmin_CH1(currentVmin);
        sendVmean_CH1(currentVmean);
        sendVRMS_CH1(currentVRMS);
    }
}

void isoDriver::slowTimerTick(){
    update_CH1 = true;
    update_CH2 = true;
}

void isoDriver::setTopRange(double newTop)
{
    // NOTE: Should this be clamped to 20?
    display.topRange = newTop;
    emit topRangeUpdated(display.topRange);
}

void isoDriver::setBotRange(double newBot)
{
    // NOTE: Should this be clamped to 20?
    display.botRange = newBot;
    emit botRangeUpdated(display.botRange);
}

void isoDriver::setTimeWindow(double newWindow){
    display.window = newWindow;
    emit timeWindowUpdated(display.window);
}

void isoDriver::setDelay(double newDelay){
    display.delay = newDelay;
    emit delayUpdated(display.delay);
}

void isoDriver::takeSnapshot(QString *fileName, unsigned char channel){
    if(channel==1){
        snapshotEnabled_CH1 = true;
        QString fname_CH1 = *(fileName);
        snapshotFile_CH1 = new QFile(fname_CH1);
        qDebug() << fname_CH1;
    } else if(channel==2){
        snapshotEnabled_CH2 = true;
        QString fname_CH2 = *(fileName);
        snapshotFile_CH2 = new QFile(fname_CH2);
        qDebug() << fname_CH2;
    }
}

double isoDriver::meanVoltageLast(double seconds, unsigned char channel, int TOP){
    isoBuffer *currentBuffer;
    switch (channel){
    case 1:
        currentBuffer = internalBuffer375_CH1;
        break;
    case 2:
        currentBuffer = internalBuffer375_CH2;
        break;
    case 3:
        currentBuffer = internalBuffer750;
        break;
    }

	std::unique_ptr<short[]> tempBuffer = currentBuffer->readBuffer(seconds, 1024, false, 0);
    double sum = 0;
    double temp;
    for(int i = 0; i<1024; i++){
        temp = currentBuffer->sampleConvert(tempBuffer[i], TOP, false);
        sum += temp;
    }
    return sum / 1024;
}

void isoDriver::rSourceChanged(int newSource){
    multimeterRsource = newSource;
}

void isoDriver::serialNeedsDisabling(int channel){
    qDebug("isoDriver acknowledges disconnect from channel %d", channel);
    mainWindowPleaseDisableSerial(channel);
}

//Thank you https://stackoverflow.com/questions/27318631/parsing-through-a-csv-file-in-qt
void isoDriver::loadFileBuffer(QFile *fileToLoad){
    //Delete the current buffer if it exists

    disableFileMode();

    delete internalBufferFile;

    //Load the file
    if (!fileToLoad->open(QIODevice::ReadOnly)) {
        qDebug() << fileToLoad->errorString();
        return;
    }
    QByteArray currentLine;
    QList<QByteArray> tempList;
    //First Header line
    currentLine = fileToLoad->readLine();
    qDebug() << currentLine;

    //Averaging line
    currentLine = fileToLoad->readLine();
    qDebug() << currentLine;
    tempList.append(currentLine.split('\n'));
    tempList.append(currentLine.split('\r'));
    tempList.append(tempList.first().split(' '));
    qDebug() << tempList;
    int averages = tempList.back().toInt();
    qDebug() << averages;

    //Mode line
    tempList.clear();
    currentLine = fileToLoad->readLine();
    qDebug() << currentLine;
    tempList.append(currentLine.split('\n'));
    tempList.append(currentLine.split('\r'));
    tempList.append(tempList.first().split(' '));
    qDebug() << tempList;
    int mode = tempList.back().toInt();
    qDebug() << mode;

    tempList.clear();
    //Count the number of elements
    qulonglong numel = 0;
    while (!fileToLoad->atEnd()) {
        currentLine = fileToLoad->readLine();
        tempList.append(currentLine.split(','));
        numel += tempList.count() - 1;
        tempList.clear();
    }

    qDebug("There are %llu elements!", numel);

    //Prompt user for start and end times
    double defaultSampleRate = 375000;
    if(mode == 6){
        defaultSampleRate = 750000;
    }
    double minTime = ((double)averages) / defaultSampleRate;
    double maxTime = numel * ((double)averages) / defaultSampleRate;
    qDebug() << "maxTime =" << maxTime;

    daqLoadPrompt dlp(this, minTime, maxTime);
    connect(&dlp, &daqLoadPrompt::startTime, this, &isoDriver::daqLoad_startChanged);
    connect(&dlp, &daqLoadPrompt::endTime, this, &isoDriver::daqLoad_endChanged);

    //Defaults
    daqLoad_startTime = minTime;
    daqLoad_endTime = maxTime;

    dlp.exec();

    //Initialise the (modified) isoBuffer.
    int bufferLen = (int)(((daqLoad_endTime - daqLoad_startTime)/minTime) * 1.1) + 1; //Add a bit on to account for rounding error.  Int conversion rounds down, so we add 1.
    qDebug() << "daqLoad_endTime" << daqLoad_endTime;
    qDebug() << "daqLoad_startTime" << daqLoad_startTime;
    qDebug() << "minTime" << minTime;
    qDebug() << "bufferLen" << bufferLen;
    double sampleRate_Hz = defaultSampleRate/averages;
    internalBufferFile = new isoBuffer_file(this, bufferLen, sampleRate_Hz);

    //Go to start of data section
    fileToLoad->seek(0);//Return to start
    currentLine = fileToLoad->readLine();  //Chew up header
    qDebug() << currentLine;
    currentLine = fileToLoad->readLine();  //Chew up averages line
    qDebug() << currentLine;
    currentLine = fileToLoad->readLine();  //Chew up mode line
    qDebug() << currentLine;
    tempList.clear();

    //Copy the data into the (modified) isoBuffer
    float tempArray[COLUMN_BREAK + 1];  //751 elements per row with the old files; this just avoids a possible crash;
    int temp_len;

    qulonglong sampleCount = 0;
    qulonglong minCount = (daqLoad_startTime / minTime);
    qulonglong maxCount = (daqLoad_endTime / minTime);

    qDebug() << "minCount" << minCount;
    qDebug() << "maxCount" << maxCount;

    int min_i;
    int tempCount;
    qDebug() << "Loading data into isoBuffer_file";
    while (!fileToLoad->atEnd()) {
        currentLine = fileToLoad->readLine();
        tempList.append(currentLine.split(','));
        tempList.removeLast();  //Last element is a "\n", not a number.
        temp_len = 0;
        tempCount = tempList.count();
        min_i = 2000000000; //Arbitrary big number.
        for (int i=0; i<tempCount; i++){
            if((sampleCount > minCount) && (sampleCount < maxCount)){
                if(i < min_i){
                    min_i = i;
                }
                tempArray[i] = tempList.at(i).toFloat();
                temp_len++;
            }
            sampleCount++;
        }
        internalBufferFile->writeBuffer_float(&tempArray[min_i], temp_len);
        tempList.clear();
    }

    fileToLoad->close();

    qDebug() << "Initialising timer";
    //Initialise the file timer.
    delete fileTimer;
    fileTimer = new QTimer();
    fileTimer->setTimerType(Qt::PreciseTimer);
    fileTimer->start(TIMER_PERIOD);
    connect(fileTimer, &QTimer::timeout, this, &isoDriver::fileTimerTick);
    qDebug() << "File Buffer loaded!";
    enableFileMode();
    qDebug() << "File Mode Enabled";
}

void isoDriver::daqLoad_startChanged(double newStart){
    qDebug() << "isoDriver::daqLoad_startChanged" << newStart;
    daqLoad_startTime = newStart;
}

void isoDriver::daqLoad_endChanged(double newEnd){
    qDebug() << "isoDriver::daqLoad_endChanged" << newEnd;
    daqLoad_endTime = newEnd;
}

void isoDriver::fileTimerTick(){
    //qDebug() << "isoDriver::fileTimerTick()";
    frameActionGeneric(ChannelMode::File, ChannelMode::Off);
}

void isoDriver::enableFileMode(){
    fileModeEnabled = true;
    daq_maxWindowSize = daqLoad_endTime - daqLoad_startTime;
    emit showRealtimeButton(true);
}

void isoDriver::disableFileMode(){
    fileModeEnabled = false;
    emit showRealtimeButton(false);
    if(fileTimer != NULL){
        fileTimer->stop();
    }

    //Shrink screen back, if necessary.
    double mws = fileModeEnabled ? daq_maxWindowSize : ((double)MAX_WINDOW_SIZE);
    if (display.window > mws)
    {
        display.window = mws;
        emit timeWindowUpdated(display.window);
    }
    if ((display.window + display.delay) > mws)
    {
        display.delay -= display.window + display.delay - mws;
        emit delayUpdated(display.delay);
    }
    if (display.delay < 0)
    {
        display.delay = 0;
        emit delayUpdated(display.delay);
    }
}

void isoDriver::setSerialType(unsigned char type)
{
    serialType = type;
    qDebug() << "Serial Type changed to" << serialType;

    if(serialType == 1)
    {
        if (twoWire)
            delete twoWire;
        twoWire = new i2c::i2cDecoder(internalBuffer375_CH1, internalBuffer375_CH2, internalBuffer375_CH1->m_console1);
    }
}

void isoDriver::hideCH1(bool enable)
{
	axes->graph(0)->setVisible(!enable);
}

void isoDriver::hideCH2(bool enable)
{
	axes->graph(1)->setVisible(!enable);
}

void isoDriver::triggerStateChanged()
{
    qDebug() << "triggerStateChanged()";
    switch(triggerMode)
    {
        case 0:
        {
            internalBuffer375_CH1->setTriggerType(TriggerType::Rising);
            internalBuffer375_CH2->setTriggerType(TriggerType::Disabled);
            internalBuffer750->setTriggerType(TriggerType::Rising);
            break;
        }
        case 1:
        {
            internalBuffer375_CH1->setTriggerType(TriggerType::Falling);
            internalBuffer375_CH2->setTriggerType(TriggerType::Disabled);
            internalBuffer750->setTriggerType(TriggerType::Falling);
            break;
        }
        case 2:
        {
            internalBuffer375_CH1->setTriggerType(TriggerType::Disabled);
            internalBuffer375_CH2->setTriggerType(TriggerType::Rising);
            internalBuffer750->setTriggerType(TriggerType::Disabled);
            break;

        }
        case 3:
        {
            internalBuffer375_CH1->setTriggerType(TriggerType::Disabled);
            internalBuffer375_CH2->setTriggerType(TriggerType::Falling);
            internalBuffer750->setTriggerType(TriggerType::Disabled);
            break;
        }
    }
}

void isoDriver::offsetChanged_CH1(double newOffset)
{
    m_offset_CH1 = newOffset;
}

void isoDriver::offsetChanged_CH2(double newOffset)
{
    m_offset_CH2 = newOffset;
}

void isoDriver::attenuationChanged_CH1(int attenuationIndex)
{
    switch(attenuationIndex)
    {
        case 0:
            m_attenuation_CH1 = 1;
            break;
        case 1:
            m_attenuation_CH1 = 5;
            break;
        case 2:
            m_attenuation_CH1 = 10;
            break;
        default:
            throw std::runtime_error("Unknown attenuation index for CH1");
    }
}

void isoDriver::attenuationChanged_CH2(int attenuationIndex)
{
    switch(attenuationIndex)
    {
        case 0:
            m_attenuation_CH2 = 1;
            break;
        case 1:
            m_attenuation_CH2 = 5;
            break;
        case 2:
            m_attenuation_CH2 = 10;
            break;
        default:
            throw std::runtime_error("Unknown attenuation index for CH2");
    }
}

void isoDriver::setHexDisplay_CH1(bool enabled)
{
    hexDisplay_CH1 = enabled;
}

void isoDriver::setHexDisplay_CH2(bool enabled)
{
    hexDisplay_CH2 = enabled;
}

void isoDriver::setDownsampleMethod(const DownsamplingMethod method)
{
    internalBuffer375_CH1->setDownsampleMethod(method);
    internalBuffer375_CH2->setDownsampleMethod(method);
    internalBuffer750->setDownsampleMethod(method);
}
