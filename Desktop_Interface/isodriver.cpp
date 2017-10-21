#include "isodriver.h"
#include "isobuffer.h"
#include "platformspecific.h"
#include <math.h>


isoDriver::isoDriver(QWidget *parent) : QLabel(parent)
{
    this->hide();
    internalBuffer375_CH1 = new isoBuffer(this, MAX_WINDOW_SIZE*ADC_SPS/20*21, this, 1);
    internalBuffer375_CH2 = new isoBuffer(this, MAX_WINDOW_SIZE*ADC_SPS/20*21, this, 1);
    internalBuffer750 = new isoBuffer(this, MAX_WINDOW_SIZE*ADC_SPS/10*21, this, 1);

    isoTemp = (char *) malloc(TIMER_PERIOD*ADC_SPF + 8); //8-byte header contains (unsigned long) length

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

    slowTimer = new QTimer;
    slowTimer->setTimerType(Qt::PreciseTimer);
    slowTimer->start(MULTIMETER_PERIOD);
    connect(slowTimer, SIGNAL(timeout()), this, SLOT(slowTimerTick()));
}

void isoDriver::setDriver(genericUsbDriver *newDriver){
    driver = newDriver;
    qDebug() << "driver = " << driver;
}

void isoDriver::setAxes(QCustomPlot *newAxes){
    axes = newAxes;
    qDebug() << "axes = " << axes;
}

void isoDriver::setWindow(int newWindow){
    window = pow( (double)10, ( (double)newWindow / 10) );
    windowAtPause = window;
    qDebug() << "window = " << window;
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

    if (length==0){
        //Zero length packet means something's gone wrong.  Probably a disconnect.
        qDebug() << "Zero length iso packet!";
        //driver->killMe();
        return;
    }

    switch(driver->deviceMode){
        case 0:
            frameActionGeneric(1,0);
            break;
        case 1:
            internalBuffer375_CH2->channel = 1;
            frameActionGeneric(1,2);
            if(serialDecodeEnabled_CH1){
                internalBuffer375_CH2->serialDecode(baudRate_CH1);
            }
            break;
        case 2:
            frameActionGeneric(1,1);
            break;
        case 3:
            frameActionGeneric(2,0);
            if(serialDecodeEnabled_CH1){
                internalBuffer375_CH1->serialDecode(baudRate_CH1);
            }
            break;
        case 4:
            internalBuffer375_CH2->channel = 2;
            frameActionGeneric(2,2);
            if(serialDecodeEnabled_CH1){
                internalBuffer375_CH1->serialDecode(baudRate_CH1);
            }
            if(serialDecodeEnabled_CH2){
                internalBuffer375_CH2->serialDecode(baudRate_CH2);
            }
            break;
        case 5:
            break;
        case 6:
            frameActionGeneric(-1,0);
            break;
        case 7:
            multimeterAction();
            break;
        default:
            qFatal("Error in isoDriver::timerTick.  Invalid device mode.");
    }
    //free(isoTemp);
}

void isoDriver::analogConvert(short *shortPtr, QVector<double> *doublePtr, int TOP, bool AC, int channel){

    double scope_gain = (double)(driver->scopeGain);
    double accumulated = 0;
    currentVmax = -20;
    currentVmin = 20;

    double ref = (channel == 1 ? ch1_ref : ch2_ref);
    double frontendGain = (channel == 1 ? frontendGain_CH1 : frontendGain_CH2);

    double *data = doublePtr->data();
    for (int i=0;i<GRAPH_SAMPLES;i++){
        data[i] = (shortPtr[i] * (vcc/2)) / (frontendGain*scope_gain*TOP);
        if (driver->deviceMode != 7) data[i] += ref;
        #ifdef INVERT_MM
            if(driver->deviceMode == 7) data[i] *= -1;
        #endif

        accumulated += data[i];
        if (data[i] > currentVmax) currentVmax = data[i];
        if (data[i] < currentVmin) currentVmin = data[i];
    }
    currentVmean  = accumulated / GRAPH_SAMPLES;
    if(AC){
        for (int i=0;i<GRAPH_SAMPLES;i++){
            data[i] -= currentVmean;
        }
    }
    //cool_waveform = cool_waveform - AC_offset;
}

void isoDriver::digitalConvert(short *shortPtr, QVector<double> *doublePtr){

    double *data = doublePtr->data();
    double top = topRange - (topRange - botRange)/10;
    double bot = botRange + (topRange - botRange)/10;
    for (int i=0;i<GRAPH_SAMPLES;i++){
        data[i] = shortPtr[i] ? top : bot;
    }
    //cool_waveform = cool_waveform - AC_offset;
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

void isoDriver::clearBuffers(bool ch3751, bool ch3752, bool ch750){
    if(ch3751) internalBuffer375_CH1->clearBuffer();
    if(ch3752) internalBuffer375_CH2->clearBuffer();
    if(ch750) internalBuffer750->clearBuffer();
}

void isoDriver::setVisible_CH2(bool visible){
    axes->graph(1)->setVisible(visible);
}

void isoDriver::setVoltageRange(QWheelEvent *event){
    if(doNotTouchGraph == true) return;

    if (!(event->modifiers() == Qt::ControlModifier)){
        double c = (topRange - botRange) / (double)400;

        QCPRange range = axes->yAxis->range();

        double pixPct = (double)100 - ((double)100 * (((double)axes->yAxis->pixelToCoord(event->y())-range.lower) / (double)(range.upper - range.lower)));
        if (pixPct<0) pixPct = 0;
        if (pixPct>100) pixPct = 100;


        qDebug() << "WHEEL @ " << pixPct << "%";
        qDebug() << range.upper;
        //qDebug() << event->delta();

        if (event->delta()==120){
            topRange -= c* ((double)pixPct);
            botRange += c* ((double)100 - (double)pixPct);
        }
        else{
            topRange += c* ((double)pixPct);
            botRange -= c* ((double)100 - (double)pixPct);
        }

        if (topRange > (double)20) topRange = (double)20;
        if (botRange <- (double)20) botRange = (double)-20;
        if (autoGainEnabled && !properlyPaused()) autoGain();
    }
    else if(properlyPaused()){
        double c = (window) / (double)200;
        QCPRange range = axes->xAxis->range();

        double pixPct = (double)100 * (((double)axes->xAxis->pixelToCoord(event->x())-range.lower) / (double)(range.upper - range.lower));
        if (pixPct<0) pixPct = 0;
        if (pixPct>100) pixPct = 100;

        qDebug() << "WHEEL @ " << pixPct << "%";
        qDebug() << event->delta();

        if (event->delta()==120){
            window -= c* ((double)pixPct);
            delay += c* ((double)100 - (double)pixPct) * pixPct/100;
        }
        else{
            window += c* ((double)pixPct);
            delay -= c* ((double)100 - (double)pixPct) * pixPct/100;
        }

        if (window > (double)MAX_WINDOW_SIZE) window = (double)MAX_WINDOW_SIZE;
        if ((window + delay) > MAX_WINDOW_SIZE) delay -= window + delay - (double)MAX_WINDOW_SIZE;
        if (delay < 0) delay = 0;
        qDebug() << window << delay;
    } else {
        qDebug() << "TIGGERED";
        double c = (window) / (double)200;
        QCPRange range = axes->xAxis->range();

        double pixPct = (double)100 * (((double)axes->xAxis->pixelToCoord(event->x())-range.lower) / (double)(window));
        if (pixPct<0) pixPct = 0;
        if (pixPct>100) pixPct = 100;

        qDebug() << "WHEEL @ " << pixPct << "%";
        qDebug() << event->delta();
        qDebug() << "upper = " << range.upper << "lower = " << range.lower;
        qDebug() << "triggerDelay = " << triggerDelay;
        qDebug() << "window = " << window;
        qDebug() << c* ((double)pixPct);
        qDebug() << c* ((double)100 - (double)pixPct) * pixPct/100;

        if (event->delta()==120){
            window -= c* ((double)pixPct);
            delay += c* ((double)100 - (double)pixPct) * pixPct/100;
        }
        else{
            window += c* ((double)pixPct);
            delay -= c* ((double)100 - (double)pixPct) * pixPct/100;
        }

        if (window > (double)MAX_WINDOW_SIZE) window = (double)MAX_WINDOW_SIZE;
        if ((window + delay) > MAX_WINDOW_SIZE) delay -= window + delay - (double)MAX_WINDOW_SIZE;
        if (delay < 0) delay = 0;
        windowAtPause = window;
        qDebug() << window << delay;
    }
    //changeTimeAxis(event->delta()==-120);
    //qDebug() << window;
}

bool isoDriver::properlyPaused(){
    if(paused_CH1 & paused_CH2){
        qDebug() << "Properly paused";
        return true;
    }
    if ((driver->deviceMode == 0) || (driver->deviceMode == 3) || (driver->deviceMode == 6)){
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
        delay = 0;
        if (autoGainEnabled) autoGain();
        //window = windowAtPause;
    }

    if(!enabled) clearBuffers(1,0,1);
    qDebug() << "pauseEnable_CH1" << enabled;
}


void isoDriver::pauseEnable_CH2(bool enabled){
    paused_CH2 = enabled;

    if(!properlyPaused()){
        delay = 0;
        if (autoGainEnabled) autoGain();
        //window = windowAtPause;
    }

    if(!enabled) clearBuffers(0,1,0);
}

void isoDriver::pauseEnable_multimeter(bool enabled){
    paused_multimeter = enabled;

    if(!properlyPaused()) {
        delay = 0;
        //window = windowAtPause;
    }

    if(!enabled) clearBuffers(1,0,0);
    qDebug() << "pauseEnable_multimeter" << enabled;
}


void isoDriver::autoGain(){
    double maxgain = vcc / (2 * ((double)topRange - vref) * R4/(R3+R4));
    double mingain = vcc / (2 * ((double)botRange - vref) * R4/(R3+R4));
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
    if (driver->deviceMode <5) internalBuffer375_CH1->gainBuffer(log2(multi));
    if ((driver->deviceMode == 1) | (driver->deviceMode == 2) | (driver->deviceMode == 4)) internalBuffer375_CH2->gainBuffer(log2(multi));
    if ((driver->deviceMode == 6) | (driver->deviceMode == 7)) internalBuffer750->gainBuffer(log2(multi));
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
        y0 = axes->yAxis->pixelToCoord(event->y());
#ifndef PLATFORM_ANDROID
    }else if(vertCursorEnabled && (event->button() == Qt::RightButton)){
#else
    }if(vertCursorEnabled){
#endif
        placingVertAxes = true;
        x0 = axes->xAxis->pixelToCoord(event->x());
    }
    qDebug() << "x0 =" << x0 << "x1 =" << x1 << "y0 =" << y0 << "y1 =" << y1;
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
    qDebug() << "x0 =" << x0 << "x1 =" << x1 << "y0 =" << y0 << "y1 =" << y1;
}

void isoDriver::graphMouseMove(QMouseEvent *event){
    if(horiCursorEnabled && placingHoriAxes){
        y1 = axes->yAxis->pixelToCoord(event->y());
#ifndef PLATFORM_ANDROID
    } else if(vertCursorEnabled && placingVertAxes){
#else
    } if(vertCursorEnabled && placingVertAxes){
#endif
        x1 = axes->xAxis->pixelToCoord(event->x());
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
#if QCP_VER == 1
        cursorTextPtr->setVisible(0);
#endif
        return;
    }

    QVector<double> vert0x(2), vert1x(2), hori0x(2), hori1x(2), vert0y(2), vert1y(2), hori0y(2), hori1y(2);

    vert0x[0] = x0;
    vert0x[1] = x0;
    vert0y[0] = botRange;
    vert0y[1] = topRange;

    vert1x[0] = x1;
    vert1x[1] = x1;
    vert1y[0] = botRange;
    vert1y[1] = topRange;

    hori0x[0] = -window - delay;
    hori0x[1] = -delay;
    hori0y[0] = y0;
    hori0y[1] = y0;

    hori1x[0] = -window - delay;
    hori1x[1] = -delay;
    hori1y[0] = y1;
    hori1y[1] = y1;

    if(vertCursorEnabled){
        axes->graph(2)->setData(vert0x, vert0y);
        axes->graph(3)->setData(vert1x, vert1y);
    }
    if(horiCursorEnabled){
        axes->graph(4)->setData(hori0x, hori0y);
        axes->graph(5)->setData(hori1x, hori1y);
    }
#if QCP_VER == 1
    cursorTextPtr->setVisible(cursorStatsEnabled);
#endif
    if (!cursorStatsEnabled) return;

    QString *cursorStatsString = new QString();

    v0->value = y0;
    v1->value = y1;
    dv->value = y0-y1;
    t0->value = x0;
    t1->value = x1;
    dt->value = fabs(x0-x1);
    f->value = 1/(x1-x0);

    char temp_hori[64];
    char temp_vert[64];
    char temp_separator[2];
    sprintf(temp_hori, "V0=%s,  V1=%s,  ΔV=%s", v0->printVal(), v1->printVal(), dv->printVal());
    sprintf(temp_vert, "t0=%s, t1=%s,  Δt=%s,  f=%s", t0->printVal(), t1->printVal(), dt->printVal(), f->printVal());
    sprintf(temp_separator, "\n");

    //sprintf(temp, "hello!");
    if(horiCursorEnabled) cursorStatsString->append(temp_hori);
    if(horiCursorEnabled && vertCursorEnabled) cursorStatsString->append(temp_separator);
    if(vertCursorEnabled) cursorStatsString->append(temp_vert);
    //qDebug() << temp;
#if QCP_VER == 1
    cursorTextPtr->setText(*(cursorStatsString));
#endif
    delete cursorStatsString;
}

int isoDriver::trigger(void){
    if(driver->deviceMode>2 && driver->deviceMode < 6){  //No scope
        return -2;
    }
    if(triggerType>1 && driver->deviceMode!=2){  //No CH2!
        return -1;
    }

    bool AC = (triggerType > 1) ? AC_CH2 : AC_CH1;
    double offsetMean = AC ? currentVmean : 0;

    short target = (triggerType%2) ? reverseFrontEnd(triggerLevel*1.1 + offsetMean) : reverseFrontEnd(triggerLevel + offsetMean);
    short lowThresh = (triggerType%2) ? reverseFrontEnd(triggerLevel + offsetMean) : reverseFrontEnd(triggerLevel*0.9 + offsetMean);

    int location = -1;

    if(driver->deviceMode == 7){
        for (unsigned int i=0;i<length/2;i++){
            if(i%750 >= VALID_DATA_PER_750) continue; //Not a valid sample

            //A bit of thresholding...
            //Gives DAT STABILITY

            //qDebug() << isoTemp_short[i+4];

            if(isoTemp_short[i] >= target){
                triggerCountSeeking = (triggerType % 2) ? 0 : triggerCountSeeking + 1;
                triggerCountNotSeeking = (triggerType % 2) ? triggerCountNotSeeking + 1 : 0;
            }
            else if (isoTemp_short[i] < lowThresh){
                triggerCountNotSeeking = (triggerType % 2) ? 0 : triggerCountNotSeeking + 1;
                triggerCountSeeking = (triggerType % 2) ? triggerCountSeeking + 1 : 0;
            }
            else{
                triggerCountSeeking = 0;
                triggerCountNotSeeking = 0;
            }

            //Check for found
            if(triggerSeeking && (triggerCountSeeking > TRIGGER_COUNT_THRESH)){
                    if(location == -1) location = i;
                    triggerSeeking = false;
            }

            //Check for lost
            if((!triggerSeeking) && (triggerCountNotSeeking > TRIGGER_COUNT_THRESH)){
                    triggerSeeking = true;
            }
        }
    }
    else{
        for (unsigned int i=0;i<length;i++){
            if(driver->deviceMode != 6){
                if(((i%750 > VALID_DATA_PER_375) && (triggerType<2)) || (((i%750 < 375) || (i%750 == VALID_DATA_PER_750)) && (triggerType>1))) continue; //Not a valid sample
            }

            //A bit of thresholding...
            //Gives DAT STABILITY

            if(isoTemp[i] >= target){
                triggerCountSeeking = (triggerType % 2) ? 0 : triggerCountSeeking + 1;
                triggerCountNotSeeking = (triggerType % 2) ? triggerCountNotSeeking + 1 : 0;
            }
            else if (isoTemp[i] < lowThresh){
                triggerCountNotSeeking = (triggerType % 2) ? 0 : triggerCountNotSeeking + 1;
                triggerCountSeeking = (triggerType % 2) ? triggerCountSeeking + 1 : 0;
            }
            else{
                triggerCountSeeking = 0;
                triggerCountNotSeeking = 0;
            }

            //Check for found
            if(triggerSeeking && (triggerCountSeeking > TRIGGER_COUNT_THRESH)){
                    if(location == -1) location = i;
                    triggerSeeking = false;
            }

            //Check for lost
            if((!triggerSeeking) && (triggerCountNotSeeking > TRIGGER_COUNT_THRESH)){
                    triggerSeeking = true;
            }
        }
    }

    if(singleShotEnabled && (location != -1)) {
        delay = triggerDelay;
        singleShotTriggered(1);
    }
    return location;
}

short isoDriver::reverseFrontEnd(double voltage){
    //qFatal("reverseFrontEnd driver mode 7");
    #ifdef INVERT_MM
        if(driver->deviceMode == 7) voltage *= -1;
    #endif


    double vn = vcc * (R2/(R1+R2));
    double vx = vn + (voltage - vn) * (R4 / (R3+R4));
    double TOP = (driver->deviceMode == 7) ? 2048 : 128;

    if (driver->deviceMode == 7){
        qDebug() << "SEEEKING";
        qDebug() <<  ((vx - vn)/vref * (double)driver->scopeGain * (double)TOP + (double)0.5);
        qDebug() << "SEEEKING";
        return ((vx - vn)/vref * (double)driver->scopeGain * (double)TOP + (double)0.5);
    }

    //qDebug() << "seeking" << voltage << "V";


    return ((vx - vn)/vref * (double)driver->scopeGain * (double)TOP + (double)0.5);
}

void isoDriver::setTriggerEnabled(bool enabled){
    triggerEnabled = enabled;
}

void isoDriver::setTriggerLevel(double level){
    triggerLevel = level;
}

void isoDriver::setSingleShotEnabled(bool enabled){
    singleShotEnabled = enabled;
}

void isoDriver::setTriggerMode(int newMode){
    triggerType = (triggerType_enum)newMode;
}

void isoDriver::frameActionGeneric(char CH1_mode, char CH2_mode)  //0 for off, 1 for ana, 2 for dig, -1 for ana750
{
    //qDebug() << "made it to frameActionGeneric";
    if(!paused_CH1 && CH1_mode == - 1){
        for (unsigned int i=0;i<(length/ADC_SPF);i++){
            internalBuffer750->writeBuffer_char(&isoTemp[ADC_SPF*i], VALID_DATA_PER_750);
        }
    }

    if(!paused_CH1 && CH1_mode > 0){
        for (unsigned int i=0;i<(length/ADC_SPF);i++){
            internalBuffer375_CH1->writeBuffer_char(&isoTemp[ADC_SPF*i], VALID_DATA_PER_375);
        }
    }

    if(!paused_CH2 && CH2_mode > 0){
        for (unsigned int i=0;i<(length/ADC_SPF);i++){
            internalBuffer375_CH2->writeBuffer_char(&isoTemp[ADC_SPF*i+ADC_SPF/2], VALID_DATA_PER_375);  //+375 to get the second half of the packet
        }
    }

    if(!paused_CH1){
        int offset = -2; //No trigger!
        if(triggerEnabled && (triggerWaiting == 0) ){
            offset = trigger();
        }
        if(offset == -1){ //Trigger is active but nothing found!
            return;
        }

        //qDebug() << "offset =" << offset;

        int backLength = length/750;
        backLength *= (CH1_mode == -1) ? VALID_DATA_PER_750 : VALID_DATA_PER_375;

        if(offset>0){
            int temp_offset = offset % 750;
            offset /= 750;
            offset *= (CH1_mode == -1) ? VALID_DATA_PER_750 : VALID_DATA_PER_375;
            offset += temp_offset;
        }

        //qDebug() << "Now offset = " << offset;

        if((!paused_CH1) && triggerEnabled && (triggerWaiting == 0)){
            triggerDelay = backLength - offset;
            triggerDelay /= (CH1_mode == -1) ? (VALID_DATA_PER_750 * 1000) : (VALID_DATA_PER_375*1000);
            triggerDelay += delay;
            triggerWaiting = (triggerDelay<(window/2)) * 2;
        }

        //qDebug() << "triggerDelay = " << triggerDelay;

        //qDebug() << "triggerWaiting =" << triggerWaiting;

        if(triggerWaiting == 1) triggerWaiting = 0;

        //qDebug() << "triggerWaiting =" << triggerWaiting;

        if(triggerEnabled && triggerWaiting){
            triggerDelay += (double)TIMER_PERIOD/(double)1000;
            triggerWaiting = (triggerDelay<(window/2)) + 1;
            return;
        }
    }

    readData375_CH1 = internalBuffer375_CH1->readBuffer(window,GRAPH_SAMPLES,CH1_mode==2, delay + ((triggerEnabled&&!paused_CH1) ? triggerDelay + window/2 : 0));
    if(CH2_mode) readData375_CH2 = internalBuffer375_CH2->readBuffer(window,GRAPH_SAMPLES,CH2_mode==2, delay + (triggerEnabled ? triggerDelay + window/2 : 0));
    if(CH1_mode == -1) readData750 = internalBuffer750->readBuffer(window,GRAPH_SAMPLES,false, delay + (triggerEnabled ? triggerDelay + window/2 : 0));


    //qDebug() << "Trigger Delay =" << triggerDelay;

    QVector<double> x(GRAPH_SAMPLES), CH1(GRAPH_SAMPLES), CH2(GRAPH_SAMPLES);


    if (CH1_mode == 1){
        analogConvert(readData375_CH1, &CH1, 128, AC_CH1, 1);
        xmin = (currentVmin < xmin) ? currentVmin : xmin;
        xmax = (currentVmax > xmax) ? currentVmax : xmax;
        broadcastStats(0);
    }
    if (CH1_mode == 2) digitalConvert(readData375_CH1, &CH1);

    if (CH2_mode == 1){
        analogConvert(readData375_CH2, &CH2, 128, AC_CH2, 2);
        ymin = (currentVmin < ymin) ? currentVmin : ymin;
        ymax = (currentVmax > ymax) ? currentVmax : ymax;
        broadcastStats(1);
    }
    if (CH2_mode == 2) digitalConvert(readData375_CH2, &CH2);

    if(CH1_mode == -1) {
        analogConvert(readData750, &CH1, 128, AC_CH1, 1);
        xmin = (currentVmin < xmin) ? currentVmin : xmin;
        xmax = (currentVmax > xmax) ? currentVmax : xmax;
        broadcastStats(0);
    }

    for (double i=0; i<GRAPH_SAMPLES; i++){
        x[i] = -(window*i)/((double)(GRAPH_SAMPLES-1)) - delay;
        if (x[i]>0) {
            CH1[i] = 0;
            CH2[i] = 0;
        }
    }

    udateCursors();

    if(XYmode){
        axes->graph(0)->setData(CH1,CH2);
        axes->xAxis->setRange(xmin, xmax);
        axes->yAxis->setRange(ymin, ymax);
    }else{
        axes->graph(0)->setData(x,CH1);
        if(CH2_mode) axes->graph(1)->setData(x,CH2);
        axes->xAxis->setRange(-window-delay,-delay);
        axes->yAxis->setRange(topRange, botRange);
    }

    if(snapshotEnabled){
        snapshotFile_CH1->open(QIODevice::WriteOnly);
        snapshotFile_CH1->write("t, v\n");

        snapshotFile_CH2->open(QIODevice::WriteOnly);
        snapshotFile_CH2->write("t, v\n");

        char tempchar[32];
        for(int i=0; i<GRAPH_SAMPLES; i++){
            sprintf(tempchar, "%f, %f\n", x.at(i), CH1.at(i));
            snapshotFile_CH1->write(tempchar);

            sprintf(tempchar, "%f, %f\n", x.at(i), CH2.at(i));
            snapshotFile_CH2->write(tempchar);
        }
        snapshotEnabled = false;
        snapshotFile_CH1->close();
        delete(snapshotFile_CH1);

        snapshotFile_CH2->close();
        delete(snapshotFile_CH2);

    }

    axes->replot();
}

void isoDriver::multimeterAction(){
    isoTemp_short = (short *)isoTemp;
    if(!paused_multimeter){
        for (unsigned int i=0;i<(length/ADC_SPF);i++){
            internalBuffer375_CH1->writeBuffer_short(&isoTemp_short[ADC_SPF/2*i], ADC_SPF/2-1);  //Offset because the first 8 bytes of the array contain the length (no samples!!)!
        }
    }

    if(!paused_multimeter){
        int offset = -2; //No trigger!
        if(triggerEnabled && (triggerWaiting == 0) ){
            offset = trigger();
        }
        if(offset == -1){ //Trigger is active but nothing found!
            return;
        }

        //qDebug() << "offset =" << offset;

        int backLength = length/750;
        backLength *= VALID_DATA_PER_375;

        if(offset>0){
            int temp_offset = offset % 750;
            offset /= 750;
            offset *= VALID_DATA_PER_375;
            offset += temp_offset;
        }

        //qDebug() << "Now offset = " << offset;

        if((!paused_CH1) && triggerEnabled && (triggerWaiting == 0)){
            triggerDelay = backLength - offset;
            triggerDelay /= (VALID_DATA_PER_375*1000);
            triggerDelay += delay;
            triggerWaiting = (triggerDelay<(window/2)) * 2;
        }

        //qDebug() << "triggerDelay = " << triggerDelay;

        //qDebug() << "triggerWaiting =" << triggerWaiting;

        if(triggerWaiting == 1) triggerWaiting = 0;

        //qDebug() << "triggerWaiting =" << triggerWaiting;

        if(triggerEnabled && triggerWaiting){
            triggerDelay += (double)TIMER_PERIOD/(double)1000;
            triggerWaiting = (triggerDelay<(window/2)) + 1;
            return;
        }
    }

    //qDebug() << triggerEnabled;
    //qDebug() << !paused_multimeter;
    //qDebug() << (triggerEnabled&&!paused_multimeter);

    //qDebug() << ((triggerEnabled&&!paused_multimeter) ? triggerDelay + window/2 : 0);

    readData375_CH1 = internalBuffer375_CH1->readBuffer(window,GRAPH_SAMPLES, false, delay + ((triggerEnabled&&!paused_multimeter) ? triggerDelay + window/2 : 0));

    QVector<double> x(GRAPH_SAMPLES), CH1(GRAPH_SAMPLES);
    analogConvert(readData375_CH1, &CH1, 2048, 0, 1);  //No AC coupling!

    for (double i=0; i<GRAPH_SAMPLES; i++){
        x[i] = -(window*i)/((double)(GRAPH_SAMPLES-1)) - delay;
        if (x[i]>0) {
            CH1[i] = 0;
        }
    }
    axes->graph(0)->setData(x,CH1);

    udateCursors();

    axes->xAxis->setRange(-window-delay,-delay);
    axes->yAxis->setRange(topRange, botRange);

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
    bool mvMax, mvMin, mvMean, mvRMS, maMax, maMin, maMean, maRMS, kOhms, uFarads;  //We'll let the compiler work out this one.

    if(autoMultimeterV){
        mvMax = currentVmax < 1;
        mvMin = currentVmin < 1;
        mvMean = currentVmean < 1;
        mvRMS = currentVRMS < 1;
    }
    if(autoMultimeterI){
        maMax = (currentVmax / seriesResistance) < 1;
        maMin = (currentVmin / seriesResistance) < 1;
        maMean = (currentVmean / seriesResistance) < 1;
        maRMS = (currentVRMS / seriesResistance) < 1;
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

        double dt = (double)(cap_x2-cap_x1)/internalBuffer375_CH1->samplesPerSecond;
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
    XYmode = enabled;
    if(!enabled){
        xmin = 20;
        xmax = -20;
        ymin = 20;
        ymax = -20;
    }
    axes->graph(1)->setVisible(!enabled);
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
        //sendVrms_CH2(currentVrms);
    } else{
        if(!update_CH1) return;
        update_CH1 = false;
        sendVmax_CH1(currentVmax);
        sendVmin_CH1(currentVmin);
        sendVmean_CH1(currentVmean);
        //sendVrms_CH1(currentVrms);
    }
}

void isoDriver::slowTimerTick(){
    update_CH1 = true;
    update_CH2 = true;
}

void isoDriver::setTopRange(double newTop){
    topRange = newTop;
}

void isoDriver::setBotRange(double newBot){
    botRange = newBot;
}

void isoDriver::setTimeWindow(double newWindow){
    window = newWindow;
    windowAtPause = window;
}

void isoDriver::takeSnapshot(){
    snapshotEnabled = true;

    QDateTime now = QDateTime::currentDateTime();
    QString fileName_CH1 = now.toString("yyyyMMddhhmmsszzz");
    fileName_CH1.append("_CH1.csv");

    QString fileName_CH2 = now.toString("yyyyMMddhhmmsszzz");
    fileName_CH2.append("_CH2.csv");

    QDir *dir = new QDir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    dir->mkdir("EspoTek");
    dir->cd("EspoTek");
    dir->mkdir("snapshots");
    dir->cd("snapshots");

    snapshotFile_CH1 = new QFile(dir->filePath(fileName_CH1));
    snapshotFile_CH2 = new QFile(dir->filePath(fileName_CH2));

    free(dir);
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

    short * tempBuffer = currentBuffer->readBuffer(seconds,1024, 0, 0);
    double sum = 0;
    double temp;
    for(int i = 0; i<1024; i++){
        temp = currentBuffer->sampleConvert(tempBuffer[i], TOP, 0);
        sum += temp;
    }
    return sum / 1024;
}

void isoDriver::rSourceChanged(int newSource){
    multimeterRsource = newSource;
}
