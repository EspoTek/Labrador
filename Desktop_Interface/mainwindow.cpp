#include "mainwindow.h"
#include "uartstyledecoder.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->psuDisplay->display("4.00");
    ui->bufferDisplay->refreshImage();

    ui->waveformSelect_CH1->readWaveformList();
    ui->waveformSelect_CH2->readWaveformList();

    labelPsu();

    ui->psuDisplay->display("4.50");

    ui->controller_iso->setDriver(new _PLATFORM_DEPENDENT_USB_OBJECT());
    ui->controller_iso->setAxes(ui->scopeAxes);

    ui->timeBaseSlider->setMaximum(10*log10(MAX_WINDOW_SIZE));

    ui->controller_iso->driver->setBufferPtr(ui->bufferDisplay);
    ui->cursorStatsLabel->hide();
    initialisePlot();
    menuSetup();
    readSettingsFile();

    ui->voltageInfoMaxDisplay_CH1->display(5312);
    ui->voltageInfoMinDisplay_CH1->display(0.01);
    ui->voltageInfoMeanDisplay_CH1->display(0.02);
    ui->voltageInfoRmsDisplay_CH1->display(6.00);
    connectDisplaySignals();

    ui->controller_iso->internalBuffer375_CH1->console1 = ui->console1;
    ui->controller_iso->internalBuffer375_CH1->console2 = ui->console2;

    ui->controller_iso->internalBuffer375_CH2->console1 = ui->console1;
    ui->controller_iso->internalBuffer375_CH2->console2 = ui->console2;
    initShortcuts();

    ui->debugButton1->setVisible(0);
    ui->debugButton2->setVisible(0);
    ui->debugButton3->setVisible(0);
    ui->debugConsole->setVisible(0);
#ifndef PLATFORM_ANDROID
    ui->console1->setVisible(0);
    ui->console2->setVisible(0);
#endif
    ui->timeBaseSlider->setVisible(0);

    //ui->pausedLabel_CH2->setVisible(0);
    ui->filterLabel_CH1->setVisible(0);
    ui->filterLabel_CH2->setVisible(0);

    //Reset the device to ensure Labrador_libusbk gets handle!!
    #ifdef PLATFORM_WINDOWS
        //ui->controller_iso->driver->usbSendControl(0x40, 0xa7, 0, 0, 0, NULL);
        //reinitUsb();
        ui->controller_iso->driver->killOnConnect = true;
    #endif
    #ifdef PLATFORM_LINUX
        reinitUsb();
    #endif
    #ifdef PLATFORM_MAC
        reinitUsb();
        /*
        //Reconnect the other objects.
        ui->controller_iso->driver->setBufferPtr(ui->bufferDisplay);
        connect(ui->debugButton1, SIGNAL(clicked()), ui->controller_iso->driver, SLOT(avrDebug()));
        connect(ui->debugButton3, SIGNAL(clicked()), ui->controller_iso->driver, SLOT(avrDebug()));
        connect(ui->psuSlider, SIGNAL(voltageChanged(double)), ui->controller_iso->driver, SLOT(setPsu(double)));
        connect(ui->controller_iso, SIGNAL(setGain(double)), ui->controller_iso->driver, SLOT(setGain(double)));
        connect(ui->controller_fg, SIGNAL(functionGenToUpdate(int,functionGenControl*)), ui->controller_iso->driver, SLOT(setFunctionGen(int,functionGenControl*)));
        connect(ui->bufferDisplay, SIGNAL(modeChange(int)), ui->controller_iso->driver, SLOT(setDeviceMode(int)));
        connect(ui->bufferDisplay, SIGNAL(updateDig(int)), ui->controller_iso->driver, SLOT(newDig(int)));

        //Set the settings again!
        connect(ui->controller_iso->driver, SIGNAL(gainBuffers(double)), ui->controller_iso, SLOT(gainBuffers(double)));
        connect(ui->controller_iso->driver, SIGNAL(disableWindow(bool)), this, SLOT(setEnabled(bool)));
        connect(ui->controller_iso->driver, SIGNAL(sendClearBuffer(bool,bool,bool)), ui->controller_iso, SLOT(clearBuffers(bool,bool,bool)));
        //connect(ui->controller_iso->driver, SIGNAL(startIsoTimer()), ui->controller_iso, SLOT(startTimer()));
        connect(ui->controller_iso->driver, SIGNAL(setVisible_CH2(bool)), ui->controller_iso, SLOT(setVisible_CH2(bool)));
        //connect(ui->controller_iso->driver, SIGNAL(enableMMTimer()), ui->controller_iso, SLOT(enableMM()));
        connect(ui->controller_iso->driver, SIGNAL(checkXY(bool)), ui->xyDisplayLabel, SLOT(setChecked(bool)));
        connect(ui->controller_iso->driver, SIGNAL(disableWindow(bool)), ui->deviceConnected, SLOT(connectedStatusChanged(bool)));
        connect(ui->controller_iso->driver, SIGNAL(upTick()), ui->controller_iso, SLOT(timerTick()));
        connect(ui->controller_iso->driver, SIGNAL(connectedStatus(bool)), ui->deviceConnected, SLOT(connectedStatusChanged(bool)));
        connect(ui->controller_iso->driver, SIGNAL(initialConnectComplete(void)), ui->deviceConnected, SLOT(resetUsbState(bool)));*/
    #endif
    #ifdef PLATFORM_ANDROID
        ui->actionAutomatically_Enable_Cursors->setVisible(false);
        //hide second pause label
        ui->pausedLabel_CH2->setVisible(false);
        //Capture pinches
        ui->scopeAxes->grabGesture(Qt::PinchGesture);
        ui->scopeAxes->installEventFilter(this);
        //Mutually exclude pinches/cursors
        connect(ui->scaleHoriCheck, SIGNAL(clicked(bool)),
                   this, SLOT(horiScaleEvent(bool)));
        connect(ui->scaleVertCheck, SIGNAL(clicked(bool)),
                   this, SLOT(vertScaleEvent(bool)));
        //Screen Rotation.  Thanks, Hamlet.  https://forum.qt.io/topic/66240/how-to-detect-rotate-on-android
        screenPtr = QGuiApplication::primaryScreen();
            connect(screenPtr, SIGNAL(orientationChanged(Qt::ScreenOrientation)),
                       this, SLOT(screenRotateEvent(Qt::ScreenOrientation)));

             screenPtr->setOrientationUpdateMask(
                        Qt::PortraitOrientation
                        | Qt::LandscapeOrientation
                        | Qt::InvertedPortraitOrientation
                        | Qt::InvertedLandscapeOrientation);

        //Hide the PSU page
        ui->stackedWidget->removeWidget(ui->page_5);

        //Reconnect the other objects.
        ui->controller_iso->driver->setBufferPtr(ui->bufferDisplay);
        connect(ui->debugButton1, SIGNAL(clicked()), ui->controller_iso->driver, SLOT(avrDebug()));
        connect(ui->psuSlider, SIGNAL(voltageChanged(double)), ui->controller_iso->driver, SLOT(setPsu(double)));
        connect(ui->controller_iso, SIGNAL(setGain(double)), ui->controller_iso->driver, SLOT(setGain(double)));
        connect(ui->controller_fg, SIGNAL(functionGenToUpdate(int,functionGenControl*)), ui->controller_iso->driver, SLOT(setFunctionGen(int,functionGenControl*)));
        connect(ui->bufferDisplay, SIGNAL(modeChange(int)), ui->controller_iso->driver, SLOT(setDeviceMode(int)));
        connect(ui->bufferDisplay, SIGNAL(updateDig(int)), ui->controller_iso->driver, SLOT(newDig(int)));

        //Set the settings again!
        connect(ui->controller_iso->driver, SIGNAL(gainBuffers(double)), ui->controller_iso, SLOT(gainBuffers(double)));
        connect(ui->controller_iso->driver, SIGNAL(disableWindow(bool)), this, SLOT(setEnabled(bool)));
        connect(ui->controller_iso->driver, SIGNAL(sendClearBuffer(bool,bool,bool)), ui->controller_iso, SLOT(clearBuffers(bool,bool,bool)));
        //connect(ui->controller_iso->driver, SIGNAL(startIsoTimer()), ui->controller_iso, SLOT(startTimer()));
        connect(ui->controller_iso->driver, SIGNAL(setVisible_CH2(bool)), ui->controller_iso, SLOT(setVisible_CH2(bool)));
        //connect(ui->controller_iso->driver, SIGNAL(enableMMTimer()), ui->controller_iso, SLOT(enableMM()));
        connect(ui->controller_iso->driver, SIGNAL(checkXY(bool)), ui->xyDisplayLabel, SLOT(setChecked(bool)));
        connect(ui->controller_iso->driver, SIGNAL(disableWindow(bool)), ui->deviceConnected, SLOT(connectedStatusChanged(bool)));
        connect(ui->controller_iso->driver, SIGNAL(upTick()), ui->controller_iso, SLOT(timerTick()));
        connect(ui->controller_iso->driver, SIGNAL(connectedStatus(bool)), ui->deviceConnected, SLOT(connectedStatusChanged(bool)));
    #endif

    connect(ui->controller_iso->driver, SIGNAL(killMe()), this, SLOT(reinitUsb()));
    //ui->console1->setMaximumBlockCount(MAX_CONSOLE_BLOCK_COUNT);
    //ui->console2->setMaximumBlockCount(MAX_CONSOLE_BLOCK_COUNT);
    //ui->frequencyValue_CH2->setValue(369);
    //ui->amplitudeValue_CH2->setValue(2);
    ui->controller_iso->doNotTouchGraph = false;

    calibrationMessages = new QMessageBox();
#ifndef PLATFORM_ANDROID
    ui->multimeterRLabel->setVisible(false);
    ui->multimeterRComboBox->setVisible(false);
#endif

    connect(ui->controller_iso, SIGNAL(multimeterREnabled(int)), this, SLOT(rSourceIndexChanged(int)));
    connect(ui->controller_iso, SIGNAL(multimeterRMS(double)), ui->multimeterRmsDisplay, SLOT(display(double)));
    connect(ui->controller_iso, SIGNAL(sendMultimeterLabel4(QString)), ui->multimeterRmsLabel, SLOT(setText(QString)));
    connect(ui->controller_iso, SIGNAL(sendVRMS_CH1(double)), ui->voltageInfoRmsDisplay_CH1, SLOT(display(double)));
    connect(ui->controller_iso, SIGNAL(sendVRMS_CH2(double)), ui->voltageInfoRmsDisplay_CH2, SLOT(display(double)));

    connect(ui->controller_iso, SIGNAL(mainWindowPleaseDisableSerial(int)), this, SLOT(serialEmergencyDisable(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialisePlot()
{
    ui->scopeAxes->addGraph();
    ui->scopeAxes->addGraph();
    ui->scopeAxes->addGraph();
    ui->scopeAxes->addGraph();
    ui->scopeAxes->addGraph();
    ui->scopeAxes->addGraph();

#if QCP_VER == 1
    textLabel = new QCPItemText(ui->scopeAxes);
    ui->scopeAxes->addItem(textLabel);
    textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignRight);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.99, 0); // place position at center/top of axis rect
    textLabel->setText("Cursor Label Here");
    textLabel->setFont(QFont("Courier New", 12));
    textLabel->setColor(Qt::white);
    textLabel->setPen(QPen(Qt::white));
    textLabel->setBrush(QBrush(Qt::black));

    textLabel->setVisible(0);
    ui->controller_iso->cursorTextPtr = textLabel;

    ui->scopeAxes->yAxis->setAutoTickCount(9);
    ui->scopeAxes->xAxis->setAutoTickCount(9);
#endif

#if QCP_VER == 2
    ui->scopeAxes->setOpenGl(true);
    QSharedPointer<QCPAxisTicker> xTicker(new QCPAxisTicker);
    xTicker->setTickCount(9);
    ui->scopeAxes->xAxis->setTicker(xTicker);

    QSharedPointer<QCPAxisTicker> yTicker(new QCPAxisTicker);
    yTicker->setTickCount(9);
    ui->scopeAxes->yAxis->setTicker(yTicker);
#endif

    QPen *dashPen = new QPen(Qt::white, 2);
    dashPen->setStyle(Qt::DashLine);

    ui->scopeAxes->graph(0)->setPen(QPen(Qt::yellow, 1));
    ui->scopeAxes->graph(1)->setPen(QPen(Qt::cyan, 1));
    ui->scopeAxes->graph(2)->setPen(QPen(Qt::white, 2));
    ui->scopeAxes->graph(3)->setPen(*(dashPen));
    ui->scopeAxes->graph(4)->setPen(QPen(Qt::white, 2));
    ui->scopeAxes->graph(5)->setPen(*(dashPen));


    ui->scopeAxes->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->scopeAxes->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->scopeAxes->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->scopeAxes->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->scopeAxes->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->scopeAxes->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->scopeAxes->xAxis->setTickLength(6);
    ui->scopeAxes->yAxis->setTickLength(6);
    ui->scopeAxes->xAxis->setSubTickLength(4);
    ui->scopeAxes->yAxis->setSubTickLength(4);
    ui->scopeAxes->xAxis->setTickLabelColor(Qt::white);
    ui->scopeAxes->yAxis->setTickLabelColor(Qt::white);

    ui->scopeAxes->setBackground(Qt::black);


    ui->scopeAxes->replot();
}

void MainWindow::labelPsu(){
    char tempString[4];
    int tempInt = ui->psuSlider->maximum();
    int tempCounter = 0;
    while(tempInt>90){
        sprintf(tempString, "%dV", tempInt/20);
        ui->psuSlider->setTickLabel(tempString, tempCounter);
        tempInt -= 20;
        tempCounter++;
    }
    ui->psuSlider->setTickLabel("4.5V", 11);
}

void MainWindow::resizeEvent(QResizeEvent *event){
    //ui->scopeAxes->yAxis->setAutoTickCount((ui->scopeAxes->height() + TICK_SEPARATION / 2) / TICK_SEPARATION);
    //ui->scopeAxes->xAxis->setAutoTickCount((ui->scopeAxes->width() + TICK_SEPARATION / 2) / TICK_SEPARATION);

    //ui->scopeAxes->resize(ui->scopeAxes->height(), ui->scopeAxes->height());
    //qDebug() << ui->scopeAxes->yAxis->autoTickCount() << ui->scopeAxes->xAxis->autoTickCount();

    if(forceSquare){
        int tempHeight = ui->scopeAxes->height();
        int tempWidth = ui->scopeAxes->width();
        int newDims = (tempHeight > tempWidth) ? tempWidth : tempHeight;
        ui->scopeAxes->resize(newDims, newDims);
        if(tempWidth > tempHeight){
            ui->scopeAxes->move(tempWidth-tempHeight, ui->scopeAxes->y());
        }else{
            ui->scopeAxes->move(ui->scopeAxes->x(), ui->scopeAxes->y() + (tempHeight - tempWidth) / 2);
        }
    }
}

void MainWindow::menuSetup(){
    gainGroup = new QActionGroup(this);
    gainGroup->addAction(ui->actionGainAuto);
    gainGroup->addAction(ui->actionGain0_5);
    gainGroup->addAction(ui->actionGain1);
    gainGroup->addAction(ui->actionGain2);
    gainGroup->addAction(ui->actionGain4);
    gainGroup->addAction(ui->actionGain8);
    gainGroup->addAction(ui->actionGain16);
    gainGroup->addAction(ui->actionGain32);
    gainGroup->addAction(ui->actionGain64);
    ui->actionGainAuto->setChecked(1);

    rangeGroupV = new QActionGroup(this);
    rangeGroupV->addAction(ui->actionAutoV);
    rangeGroupV->addAction(ui->actionMV);
    rangeGroupV->addAction(ui->actionV);

    rangeGroupI = new QActionGroup(this);
    rangeGroupI->addAction(ui->actionAutoI);
    rangeGroupI->addAction(ui->actionMA);
    rangeGroupI->addAction(ui->actionA);

    rangeGroupR = new QActionGroup(this);
    rangeGroupR->addAction(ui->actionAutoR);
    rangeGroupR->addAction(ui->actionKOhm);
    rangeGroupR->addAction(ui->actionOhm);

    rangeGroupC = new QActionGroup(this);
    rangeGroupC->addAction(ui->actionAutoC);
    rangeGroupC->addAction(ui->actionNF);
    rangeGroupC->addAction(ui->action_F);

    fpsGroup = new QActionGroup(this);
    fpsGroup->addAction(ui->action60FPS);
    fpsGroup->addAction(ui->action30FPS);
    fpsGroup->addAction(ui->action20FPS);
    fpsGroup->addAction(ui->action15FPS);
    fpsGroup->addAction(ui->action10FPS);
    fpsGroup->addAction(ui->action5FPS);


    connect(ui->actionAutoV, SIGNAL(toggled(bool)), ui->controller_iso, SLOT(setAutoMultimeterV(bool)));
    connect(ui->actionV, SIGNAL(toggled(bool)), ui->controller_iso, SLOT(setForceVolts(bool)));
    connect(ui->actionMV, SIGNAL(toggled(bool)), ui->controller_iso, SLOT(setForceMillivolts(bool)));
    connect(ui->actionAutoI, SIGNAL(toggled(bool)), ui->controller_iso, SLOT(setAutoMultimeterI(bool)));
    connect(ui->actionA, SIGNAL(toggled(bool)), ui->controller_iso, SLOT(setForceAmps(bool)));
    connect(ui->actionMA, SIGNAL(toggled(bool)), ui->controller_iso, SLOT(setForceMilliamps(bool)));
    connect(ui->actionAutoR, SIGNAL(toggled(bool)), ui->controller_iso, SLOT(setAutoMultimeterR(bool)));
    connect(ui->actionOhm, SIGNAL(toggled(bool)), ui->controller_iso, SLOT(setForceOhms(bool)));
    connect(ui->actionKOhm, SIGNAL(toggled(bool)), ui->controller_iso, SLOT(setForceKiloOhms(bool)));
    connect(ui->actionAutoC, SIGNAL(toggled(bool)), ui->controller_iso, SLOT(setAutoMultimeterC(bool)));
    connect(ui->actionNF, SIGNAL(toggled(bool)), ui->controller_iso, SLOT(setForceNFarads(bool)));
    connect(ui->action_F, SIGNAL(toggled(bool)), ui->controller_iso, SLOT(setForceUFarads(bool)));


    uartBaudGroup_CH1 = new QActionGroup(this);
    uartBaudGroup_CH1->addAction(ui->action300);
    uartBaudGroup_CH1->addAction(ui->action600);
    uartBaudGroup_CH1->addAction(ui->action1200);
    uartBaudGroup_CH1->addAction(ui->action2400);
    uartBaudGroup_CH1->addAction(ui->action4800);
    uartBaudGroup_CH1->addAction(ui->action9600);
    uartBaudGroup_CH1->addAction(ui->action14400);
    uartBaudGroup_CH1->addAction(ui->action19200);
    uartBaudGroup_CH1->addAction(ui->action28800);
    uartBaudGroup_CH1->addAction(ui->action38400);
    uartBaudGroup_CH1->addAction(ui->action57600);
    uartBaudGroup_CH1->addAction(ui->action115200);
    ui->action9600->setChecked(1);

    uartBaudGroup_CH2 = new QActionGroup(this);
    uartBaudGroup_CH2->addAction(ui->action300_2);
    uartBaudGroup_CH2->addAction(ui->action600_2);
    uartBaudGroup_CH2->addAction(ui->action1200_2);
    uartBaudGroup_CH2->addAction(ui->action2400_2);
    uartBaudGroup_CH2->addAction(ui->action4800_2);
    uartBaudGroup_CH2->addAction(ui->action9600_2);
    uartBaudGroup_CH2->addAction(ui->action14400_2);
    uartBaudGroup_CH2->addAction(ui->action19200_2);
    uartBaudGroup_CH2->addAction(ui->action28800_2);
    uartBaudGroup_CH2->addAction(ui->action38400_2);
    uartBaudGroup_CH2->addAction(ui->action57600_2);
    uartBaudGroup_CH2->addAction(ui->action115200_2);
    ui->action9600_2->setChecked(1);

    connectionTypeGroup = new QActionGroup(this);
    connectionTypeGroup->addAction(ui->actionLo_bw);
    connectionTypeGroup->addAction(ui->actionSingle_ep_msync);
    connectionTypeGroup->addAction(ui->actionSingle_ep_async);
    ui->actionLo_bw->setChecked(1);
    expected_variant = 1; //for default Lo_bw mode;

    ui->actionLo_bw->setVisible(false);
    ui->actionSingle_ep_msync->setVisible(false);
    ui->actionSingle_ep_async->setVisible(false);
    ui->menuConnection_Type->menuAction()->setVisible(false);

    //Hide unsupported option!!!
    ui->menuFrame_rate->menuAction()->setVisible(false);

}

void MainWindow::on_actionGain0_5_triggered()
{
    ui->controller_iso->driver->setGain(0.5);
    ui->controller_iso->setAutoGain(0);
}

void MainWindow::on_actionGain1_triggered()
{
    ui->controller_iso->driver->setGain(1);
    ui->controller_iso->setAutoGain(0);
}

void MainWindow::on_actionGain2_triggered()
{
    ui->controller_iso->driver->setGain(2);
    ui->controller_iso->setAutoGain(0);
}

void MainWindow::on_actionGain4_triggered()
{
    ui->controller_iso->driver->setGain(4);
    ui->controller_iso->setAutoGain(0);
}

void MainWindow::on_actionGain8_triggered()
{
    ui->controller_iso->driver->setGain(8);
    ui->controller_iso->setAutoGain(0);
}

void MainWindow::on_actionGain16_triggered()
{
    ui->controller_iso->driver->setGain(16);
    ui->controller_iso->setAutoGain(0);
}

void MainWindow::on_actionGain32_triggered()
{
    ui->controller_iso->driver->setGain(32);
    ui->controller_iso->setAutoGain(0);
}

void MainWindow::on_actionGain64_triggered()
{
    ui->controller_iso->driver->setGain(64);
    ui->controller_iso->setAutoGain(0);
}
void MainWindow::on_actionGainAuto_triggered()
{
    ui->controller_iso->setAutoGain(1);
}

void MainWindow::on_actionCursor_Stats_triggered(bool checked)
{
    ui->controller_iso->cursorStatsEnabled = checked;
}

void MainWindow::connectDisplaySignals(){
    connect(ui->actionMax, SIGNAL(toggled(bool)), ui->voltageInfoMaxLabel_CH1, SLOT(setVisible(bool)));
    connect(ui->actionMax, SIGNAL(toggled(bool)), ui->voltageInfoMaxDisplay_CH1, SLOT(setVisible(bool)));

    connect(ui->actionMin, SIGNAL(toggled(bool)), ui->voltageInfoMinLabel_CH1, SLOT(setVisible(bool)));
    connect(ui->actionMin, SIGNAL(toggled(bool)), ui->voltageInfoMinDisplay_CH1, SLOT(setVisible(bool)));

    connect(ui->actionMean, SIGNAL(toggled(bool)), ui->VoltageInfoMeanLabel_CH1, SLOT(setVisible(bool)));
    connect(ui->actionMean, SIGNAL(toggled(bool)), ui->voltageInfoMeanDisplay_CH1, SLOT(setVisible(bool)));

    connect(ui->actionRMS, SIGNAL(toggled(bool)), ui->voltageInfoRmsLabel_CH1, SLOT(setVisible(bool)));
    connect(ui->actionRMS, SIGNAL(toggled(bool)), ui->voltageInfoRmsDisplay_CH1, SLOT(setVisible(bool)));

    ui->voltageInfoMaxLabel_CH1->setVisible(0);
    ui->voltageInfoMaxDisplay_CH1->setVisible(0);
    ui->voltageInfoMinLabel_CH1->setVisible(0);
    ui->voltageInfoMinDisplay_CH1->setVisible(0);
    ui->VoltageInfoMeanLabel_CH1->setVisible(0);
    ui->voltageInfoMeanDisplay_CH1->setVisible(0);
    ui->voltageInfoRmsLabel_CH1->setVisible(0);
    ui->voltageInfoRmsDisplay_CH1->setVisible(0);

    connect(ui->actionMax_2, SIGNAL(toggled(bool)), ui->voltageInfoMaxLabel_CH2, SLOT(setVisible(bool)));
    connect(ui->actionMax_2, SIGNAL(toggled(bool)), ui->voltageInfoMaxDisplay_CH2, SLOT(setVisible(bool)));

    connect(ui->actionMin_2, SIGNAL(toggled(bool)), ui->voltageInfoMinLabel_CH2, SLOT(setVisible(bool)));
    connect(ui->actionMin_2, SIGNAL(toggled(bool)), ui->voltageInfoMinDisplay_CH2, SLOT(setVisible(bool)));

    connect(ui->actionMean_2, SIGNAL(toggled(bool)), ui->VoltageInfoMeanLabel_CH2, SLOT(setVisible(bool)));
    connect(ui->actionMean_2, SIGNAL(toggled(bool)), ui->voltageInfoMeanDisplay_CH2, SLOT(setVisible(bool)));

    connect(ui->actionRMS_2, SIGNAL(toggled(bool)), ui->voltageInfoRmsLabel_CH2, SLOT(setVisible(bool)));
    connect(ui->actionRMS_2, SIGNAL(toggled(bool)), ui->voltageInfoRmsDisplay_CH2, SLOT(setVisible(bool)));

    ui->voltageInfoMaxLabel_CH2->setVisible(0);
    ui->voltageInfoMaxDisplay_CH2->setVisible(0);
    ui->voltageInfoMinLabel_CH2->setVisible(0);
    ui->voltageInfoMinDisplay_CH2->setVisible(0);
    ui->VoltageInfoMeanLabel_CH2->setVisible(0);
    ui->voltageInfoMeanDisplay_CH2->setVisible(0);
    ui->voltageInfoRmsLabel_CH2->setVisible(0);
    ui->voltageInfoRmsDisplay_CH2->setVisible(0);
}



void MainWindow::on_action300_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH1 = 300;
    }
}

void MainWindow::on_action600_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH1 = 600;
    }
}

void MainWindow::on_action1200_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH1 = 1200;
    }
}

void MainWindow::on_action2400_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH1 = 2400;
    }
}

void MainWindow::on_action4800_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH1 = 4800;
    }
}

void MainWindow::on_action9600_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH1 = 9600;
    }
}

void MainWindow::on_action14400_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH1 = 14400;
    }
}

void MainWindow::on_action19200_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH1 = 19200;
    }
}

void MainWindow::on_action28800_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH1 = 28800;
    }
}

void MainWindow::on_action38400_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH1 = 38400;
    }
}

void MainWindow::on_action57600_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH1 = 57600;
    }
}

void MainWindow::on_action115200_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH1 = 115200;
    }
}

void MainWindow::on_action300_2_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH2 = 300;
    }
}

void MainWindow::on_action600_2_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH2 = 600;
    }
}

void MainWindow::on_action1200_2_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH2 = 1200;
    }
}

void MainWindow::on_action2400_2_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH2 = 2400;
    }
}

void MainWindow::on_action4800_2_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH2 = 4800;
    }
}

void MainWindow::on_action9600_2_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH2 = 9600;
    }
}

void MainWindow::on_action14400_2_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH2 = 14400;
    }
}

void MainWindow::on_action19200_2_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH2 = 19200;
    }
}

void MainWindow::on_action28800_2_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH2 = 28800;
    }
}

void MainWindow::on_action38400_2_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH2 = 38400;
    }
}

void MainWindow::on_action57600_2_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH2 = 57600;
    }
}

void MainWindow::on_action115200_2_toggled(bool arg1)
{
    if(arg1){
        ui->controller_iso->baudRate_CH2 = 115200;
    }
}

void MainWindow::cycleBaudRate_CH1(){
    QAction *currentAction = uartBaudGroup_CH1->checkedAction();
    qDebug() << currentAction;
    if(currentAction==ui->action300){
        ui->action600->setChecked(1);
        return;
        }
    if(currentAction==ui->action600){
        ui->action1200->setChecked(1);
        return;
        }
    if(currentAction==ui->action1200){
        ui->action2400->setChecked(1);
        return;
        }
    if(currentAction==ui->action2400){
        ui->action4800->setChecked(1);
        return;
        }
    if(currentAction==ui->action4800){
        ui->action9600->setChecked(1);
        return;
        }
    if(currentAction==ui->action9600){
        ui->action14400->setChecked(1);
        return;
        }
    if(currentAction==ui->action14400){
        ui->action19200->setChecked(1);
        return;
        }
    if(currentAction==ui->action19200){
        ui->action28800->setChecked(1);
        return;
        }
    if(currentAction==ui->action28800){
        ui->action38400->setChecked(1);
        return;
        }
    if(currentAction==ui->action38400){
        ui->action57600->setChecked(1);
        return;
        }
    if(currentAction==ui->action57600){
        ui->action115200->setChecked(1);
        return;
        }
    if(currentAction==ui->action115200){
        ui->action300->setChecked(1);
        return;
        }
    qFatal("Invalid state in MainWindow::cycleBaudRate_CH1()");
}

void MainWindow::cycleBaudRateBackwards_CH1(){
    QAction *currentAction = uartBaudGroup_CH1->checkedAction();
    qDebug() << currentAction;
    if(currentAction==ui->action1200){
        ui->action600->setChecked(1);
        return;
        }
    if(currentAction==ui->action2400){
        ui->action1200->setChecked(1);
        return;
        }
    if(currentAction==ui->action4800){
        ui->action2400->setChecked(1);
        return;
        }
    if(currentAction==ui->action9600){
        ui->action4800->setChecked(1);
        return;
        }
    if(currentAction==ui->action14400){
        ui->action9600->setChecked(1);
        return;
        }
    if(currentAction==ui->action19200){
        ui->action14400->setChecked(1);
        return;
        }
    if(currentAction==ui->action28800){
        ui->action19200->setChecked(1);
        return;
        }
    if(currentAction==ui->action38400){
        ui->action28800->setChecked(1);
        return;
        }
    if(currentAction==ui->action57600){
        ui->action38400->setChecked(1);
        return;
        }
    if(currentAction==ui->action115200){
        ui->action57600->setChecked(1);
        return;
        }
    if(currentAction==ui->action300){
        ui->action115200->setChecked(1);
        return;
        }
    if(currentAction==ui->action600){
        ui->action300->setChecked(1);
        return;
        }
    qFatal("Invalid state in MainWindow::cycleBaudRateBackwards_CH1()");
}

void MainWindow::cycleBaudRate_CH2(){
    QAction *currentAction = uartBaudGroup_CH2->checkedAction();
    qDebug() << currentAction;
    if(currentAction==ui->action300_2){
        ui->action600_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action600_2){
        ui->action1200_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action1200_2){
        ui->action2400_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action2400_2){
        ui->action4800_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action4800_2){
        ui->action9600_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action9600_2){
        ui->action14400_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action14400_2){
        ui->action19200_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action19200_2){
        ui->action28800_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action28800_2){
        ui->action38400_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action38400_2){
        ui->action57600_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action57600_2){
        ui->action115200_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action115200_2){
        ui->action300_2->setChecked(1);
        return;
        }
    qFatal("Invalid state in MainWindow::cycleBaudRate_CH2()");
}

void MainWindow::cycleBaudRateBackwards_CH2(){
    QAction *currentAction = uartBaudGroup_CH2->checkedAction();
    qDebug() << currentAction;
    if(currentAction==ui->action1200_2){
        ui->action600_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action2400_2){
        ui->action1200_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action4800_2){
        ui->action2400_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action9600_2){
        ui->action4800_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action14400_2){
        ui->action9600_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action19200_2){
        ui->action14400_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action28800_2){
        ui->action19200_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action38400_2){
        ui->action28800_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action57600_2){
        ui->action38400_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action115200_2){
        ui->action57600_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action300_2){
        ui->action115200_2->setChecked(1);
        return;
        }
    if(currentAction==ui->action600_2){
        ui->action300_2->setChecked(1);
        return;
        }
    qFatal("Invalid state in MainWindow::cycleBaudRateBackwards_CH2()");
}

void MainWindow::initShortcuts(){
    shortcut_cycleBaudRate_CH1 = new QShortcut(QKeySequence("Ctrl+B"), ui->menuBar);
    shortcut_cycleBaudRateBackwards_CH1 = new QShortcut(QKeySequence("Ctrl+Shift+B"), ui->menuBar);
    shortcut_cycleBaudRate_CH2 = new QShortcut(QKeySequence("Ctrl+Alt+B"), ui->menuBar);
    shortcut_cycleBaudRateBackwards_CH2 = new QShortcut(QKeySequence("Ctrl+Shift+Alt+B"), ui->menuBar);
    shortcut_snapScopeToCursors = new QShortcut(QKeySequence("Z"), ui->menuBar);
    shortcut_manualRange = new QShortcut(QKeySequence("M"), ui->menuBar);
    shortcut_snapshot_CH1 = new QShortcut(QKeySequence("c"), this);
    shortcut_snapshot_CH2 = new QShortcut(QKeySequence("v"), this);

    shortcut_ArrowUp = new QShortcut(QKeySequence("Up"), ui->menuBar);
    shortcut_ArrowDown = new QShortcut(QKeySequence("Down"), ui->menuBar);
    shortcut_CtrlArrowUp = new QShortcut(QKeySequence("Ctrl+Up"), ui->menuBar);
    shortcut_CtrlArrowDown = new QShortcut(QKeySequence("Ctrl+Down"), ui->menuBar);
    shortcut_w = new QShortcut(QKeySequence("w"), ui->menuBar);
    shortcut_s = new QShortcut(QKeySequence("s"), ui->menuBar);
    shortcut_ctrlW = new QShortcut(QKeySequence("Ctrl+w"), ui->menuBar);
    shortcut_ctrlS = new QShortcut(QKeySequence("Ctrl+s"), ui->menuBar);

    shortcut_a = new QShortcut(QKeySequence("a"), this);
    shortcut_d = new QShortcut(QKeySequence("d"), this);
    shortcut_ArrowLeft = new QShortcut(QKeySequence("Left"), this);
    shortcut_ArrowRight = new QShortcut(QKeySequence("Right"), this);
    shortcut_CtrlArrowLeft = new QShortcut(QKeySequence("Ctrl+Left"), this);
    shortcut_CtrlArrowRight = new QShortcut(QKeySequence("Ctrl+Right"), this);



    shortcut_Debug = new QShortcut(QKeySequence("Home"), this);
    shortcut_Esc = new QShortcut(QKeySequence("Esc"), this);


    connect(shortcut_cycleBaudRate_CH1, SIGNAL(activated()), this, SLOT(cycleBaudRate_CH1()));
    connect(shortcut_cycleBaudRateBackwards_CH1, SIGNAL(activated()), this, SLOT(cycleBaudRateBackwards_CH1()));
    connect(shortcut_cycleBaudRate_CH2, SIGNAL(activated()), this, SLOT(cycleBaudRate_CH2()));
    connect(shortcut_cycleBaudRateBackwards_CH2, SIGNAL(activated()), this, SLOT(cycleBaudRateBackwards_CH2()));
    connect(shortcut_snapshot_CH1, SIGNAL(activated()), this, SLOT(on_actionSnapshot_CH1_triggered()));
    connect(shortcut_snapshot_CH2, SIGNAL(activated()), this, SLOT(on_actionSnapshot_CH2_triggered()));

    connect(shortcut_ArrowUp, SIGNAL(activated()), this, SLOT(arrowUpTriggered()));
    connect(shortcut_ArrowDown, SIGNAL(activated()), this, SLOT(arrowDownTriggered()));
    connect(shortcut_CtrlArrowUp, SIGNAL(activated()), this, SLOT(ctrlArrowUpTriggered()));
    connect(shortcut_CtrlArrowDown, SIGNAL(activated()), this, SLOT(ctrlArrowDownTriggered()));
    connect(shortcut_w, SIGNAL(activated()), this, SLOT(arrowUpTriggered()));
    connect(shortcut_s, SIGNAL(activated()), this, SLOT(arrowDownTriggered()));
    connect(shortcut_ctrlW, SIGNAL(activated()), this, SLOT(ctrlArrowUpTriggered()));
    connect(shortcut_ctrlS, SIGNAL(activated()), this, SLOT(ctrlArrowDownTriggered()));

    connect(shortcut_a, SIGNAL(activated()), this, SLOT(cycleDelayLeft()));
    connect(shortcut_d, SIGNAL(activated()), this, SLOT(cycleDelayRight()));

    connect(shortcut_ArrowLeft, SIGNAL(activated()), this, SLOT(cycleDelayLeft()));
    connect(shortcut_ArrowRight, SIGNAL(activated()), this, SLOT(cycleDelayRight()));
    connect(shortcut_CtrlArrowLeft, SIGNAL(activated()), this, SLOT(cycleDelayLeft_large()));
    connect(shortcut_CtrlArrowRight, SIGNAL(activated()), this, SLOT(cycleDelayRight_large()));

    connect(shortcut_snapScopeToCursors, SIGNAL(activated()), this, SLOT(on_actionSnap_to_Cursors_triggered()));
    connect(shortcut_manualRange, SIGNAL(activated()), this, SLOT(on_actionEnter_Manually_triggered()));

    connect(shortcut_Debug, SIGNAL(activated()), this, SLOT(enableLabradorDebugging()));
    connect(shortcut_Esc, SIGNAL(activated()), this, SLOT(reinitUsb()));

}

void MainWindow::timeBaseNeedsChanging(bool positive){
    int tempVal = ui->timeBaseSlider->value();
    tempVal += positive ? 1 : -1;
    ui->timeBaseSlider->setValue(tempVal);
}

void MainWindow::on_actionForce_Square_triggered(bool checked)
{
    forceSquare = checked;
    //Force redraw!
    int tempHeight = this->height();
    int tempWidth = this->width();
    this->resize(tempWidth+1, tempHeight+1);
    this->resize(tempWidth, tempHeight);
}

void MainWindow::arrowUpTriggered(){
    qDebug() << "Boy UP!";
    if(!(ui->scopeAxes->underMouse())) return;

    QPoint point = ui->scopeAxes->mapFromGlobal(QCursor::pos());
    wheelEmu = new QWheelEvent(point, 120, 0, 0, Qt::Vertical);
    ui->controller_iso->setVoltageRange(wheelEmu);
}

void MainWindow::arrowDownTriggered(){
    qDebug() << "Boy DOWN!";
    if(!(ui->scopeAxes->underMouse())) return;

    QPoint point = ui->scopeAxes->mapFromGlobal(QCursor::pos());
    wheelEmu = new QWheelEvent(point, -120, 0, 0, Qt::Vertical);
    ui->controller_iso->setVoltageRange(wheelEmu);
}

void MainWindow::ctrlArrowUpTriggered(){
    qDebug() << "Boy (ctrl) UP!";
    if(!(ui->scopeAxes->underMouse())) return;

    QPoint point = ui->scopeAxes->mapFromGlobal(QCursor::pos());
    wheelEmu = new QWheelEvent(point, 120, 0, Qt::ControlModifier, Qt::Vertical);
    ui->controller_iso->setVoltageRange(wheelEmu);
}

void MainWindow::ctrlArrowDownTriggered(){
    qDebug() << "Boy (ctrl) DOWN!";
    if(!(ui->scopeAxes->underMouse())) return;

    QPoint point = ui->scopeAxes->mapFromGlobal(QCursor::pos());
    wheelEmu = new QWheelEvent(point, -120, 0, Qt::ControlModifier, Qt::Vertical);
    ui->controller_iso->setVoltageRange(wheelEmu);
}

void MainWindow::cycleDelayRight(){
    qDebug() << "RIGHT";
    ui->controller_iso->delay -= ui->controller_iso->window/10;
    if(ui->controller_iso->delay < 0) ui->controller_iso->delay = 0;
}

void MainWindow::cycleDelayLeft(){
    qDebug() << "LEFT";
    ui->controller_iso->delay += ui->controller_iso->window/10;
    if(ui->controller_iso->delay > (MAX_WINDOW_SIZE - ui->controller_iso->window)) ui->controller_iso->delay = (MAX_WINDOW_SIZE - ui->controller_iso->window);
}

void MainWindow::cycleDelayRight_large(){
    qDebug() << "RIGHT";
    ui->controller_iso->delay -= ui->controller_iso->window/2;
    if(ui->controller_iso->delay < 0) ui->controller_iso->delay = 0;
}

void MainWindow::cycleDelayLeft_large(){
    qDebug() << "LEFT";
    ui->controller_iso->delay += ui->controller_iso->window/2;
    if(ui->controller_iso->delay > (MAX_WINDOW_SIZE - ui->controller_iso->window)) ui->controller_iso->delay = (MAX_WINDOW_SIZE - ui->controller_iso->window);
}

void MainWindow::enableLabradorDebugging(){
    qDebug() << "DEBUG MODE ACTIVE";

    ui->debugButton1->setVisible(1);
    ui->debugButton2->setVisible(1);
    ui->debugButton3->setVisible(1);
    ui->debugConsole->setVisible(1);

    new Q_DebugStream(std::cout, ui->debugConsole); //Redirect Console output to QTextEdit
    Q_DebugStream::registerQDebugMessageHandler(); //Redirect qDebug() output to QTextEdit
    qDebug() << "DEBUG MODE ACTIVE";
}

void MainWindow::on_actionAutomatically_Enable_Cursors_toggled(bool enabled)
{
    ui->makeCursorsNicer->setTurnedOn(enabled);
}

void MainWindow::on_action60FPS_toggled(bool enabled)
{
    if(enabled){
        TIMER_PERIOD = 17;
        ui->controller_iso->startTimer();
    }
}
void MainWindow::on_action30FPS_toggled(bool enabled)
{
    if(enabled){
        TIMER_PERIOD = 33;
        ui->controller_iso->startTimer();
    }
}
void MainWindow::on_action20FPS_toggled(bool enabled)
{
    if(enabled){
        TIMER_PERIOD = 40;
        ui->controller_iso->startTimer();
    }
}
void MainWindow::on_action15FPS_toggled(bool enabled)
{
    if(enabled){
        TIMER_PERIOD = 67;
        ui->controller_iso->startTimer();
    }
}
void MainWindow::on_action10FPS_toggled(bool enabled)
{
    if(enabled){
        TIMER_PERIOD = 100;
        ui->controller_iso->startTimer();
    }
}
void MainWindow::on_action5FPS_toggled(bool enabled)
{
    qDebug() << "5FPS";
    if(enabled){
        qDebug() << "5FPS is enabled!";
        TIMER_PERIOD = 200;
        ui->controller_iso->startTimer();
    }
}


void MainWindow::on_actionAuto_Lock_toggled(bool arg1)
{
    ui->lockPsuCheckBox->enableTimer(arg1);
    ui->lockPsuCheckBox->timer->start(ui->lockPsuCheckBox->timerLength);
}

void MainWindow::on_actionSnap_to_Cursors_triggered()
{
    double xLeft, xRight, yBot, yTop;

    yTop = ui->controller_iso->y1 > ui->controller_iso->y0 ? ui->controller_iso->y1 : ui->controller_iso->y0;
    yBot = ui->controller_iso->y1 > ui->controller_iso->y0 ? ui->controller_iso->y0 : ui->controller_iso->y1;

    xRight = ui->controller_iso->x1 > ui->controller_iso->x0 ? ui->controller_iso->x1 : ui->controller_iso->x0;
    xLeft = ui->controller_iso->x1 > ui->controller_iso->x0 ? ui->controller_iso->x0 : ui->controller_iso->x1;

    if((yBot-yTop) != 0){
        ui->controller_iso->topRange = yTop;
        ui->controller_iso->botRange = yBot;
    }

    if((xLeft - xRight) != 0){
        ui->controller_iso->delay = - xRight;
        ui->controller_iso->window = xRight - xLeft;
    }
}

void MainWindow::on_actionEnter_Manually_triggered()
{
    ui->controller_iso->delay = 0;
    scopeRangeEnterDialog dialog(this, ui->controller_iso->topRange, ui->controller_iso->botRange, ui->controller_iso->window, ui->controller_iso->delay);
    dialog.setModal(true);
    connect(&dialog, SIGNAL(yTopUpdated(double)), ui->controller_iso, SLOT(setTopRange(double)));
    connect(&dialog, SIGNAL(yBotUpdated(double)), ui->controller_iso, SLOT(setBotRange(double)));
    connect(&dialog, SIGNAL(windowUpdated(double)), ui->controller_iso, SLOT(setTimeWindow(double)));
    connect(&dialog, SIGNAL(delayUpdated(double)), ui->controller_iso, SLOT(setDelay(double)));
    dialog.exec();
}

void MainWindow::helloWorld(){
    qDebug() << "Hello World!";
}

#define QSETTINGS_DEFAULT_RETURN 42069
void MainWindow::readSettingsFile(){
    settings = new QSettings("settings.ini", QSettings::IniFormat);
    int connectionType = settings->value("ConnectionType", QSETTINGS_DEFAULT_RETURN).toInt();
    double calibrate_vref_ch1 = settings->value("CalibrateVrefCH1", 1.65).toDouble();
    double calibrate_vref_ch2 = settings->value("CalibrateVrefCH2", 1.65).toDouble();
    double calibrate_gain_ch1 = settings->value("CalibrateGainCH1", R4/(R3+R4)).toDouble();
    double calibrate_gain_ch2 = settings->value("CalibrateGainCH2", R4/(R3+R4)).toDouble();

    //Change connection Type
    switch(connectionType){
    case 0:
        ui->actionLo_bw->setChecked(1);
        on_actionLo_bw_triggered();
        break;
    case 1:
        ui->actionSingle_ep_msync->setChecked(1);
        on_actionSingle_ep_msync_triggered();
        break;
    case 2:
        ui->actionSingle_ep_async->setChecked(1);
        on_actionSingle_ep_async_triggered();
        break;
    }

    //Fill in calibration data
    ui->controller_iso->ch1_ref = 3.3 - calibrate_vref_ch1;
    ui->controller_iso->ch2_ref = 3.3 - calibrate_vref_ch2;
    ui->controller_iso->frontendGain_CH1 = calibrate_gain_ch1;
    ui->controller_iso->frontendGain_CH2 = calibrate_gain_ch2;
    ui->controller_iso->internalBuffer375_CH1->voltage_ref = 3.3 - calibrate_vref_ch1;
    ui->controller_iso->internalBuffer750->voltage_ref = 3.3 - calibrate_vref_ch1;
    ui->controller_iso->internalBuffer375_CH2->voltage_ref = 3.3 - calibrate_vref_ch2;
    ui->controller_iso->internalBuffer375_CH1->frontendGain = calibrate_gain_ch1;
    ui->controller_iso->internalBuffer750->frontendGain = calibrate_gain_ch1;
    ui->controller_iso->internalBuffer375_CH2->frontendGain = calibrate_gain_ch2;
}

void MainWindow::on_actionRecord_triggered(bool checked)
{
    /*
    if(!checked){
        ui->controller_iso->internalBuffer375_CH1->disableFileIO();
        ui->controller_iso->internalBuffer375_CH2->disableFileIO();
        ui->controller_iso->internalBuffer750->disableFileIO();

        delete(output375_CH1);
        delete(output375_CH2);
        delete(output750);
        return;
    }
    QDateTime now = QDateTime::currentDateTime();
    QString dateString = now.toString("yyyyMMddhhmmsszzz");
    qDebug() << dateString;

    qDebug() << "QStandardPaths::DocumentsLocation" << QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    outputDir = new QDir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    outputDir->mkdir("EspoTek");
    outputDir->cd("EspoTek");
    outputDir->mkdir("recordings");
    outputDir->cd("recordings");
    outputDir->mkdir(dateString);
    outputDir->cd(dateString);

    qDebug() << outputDir->absolutePath();

    output375_CH1 = new QFile(outputDir->filePath("375_CH1.csv"));
    output375_CH2 = new QFile(outputDir->filePath("375_CH2.csv"));
    output750 = new QFile(outputDir->filePath("750.csv"));

    ui->controller_iso->internalBuffer375_CH1->enableFileIO(output375_CH1);
    ui->controller_iso->internalBuffer375_CH2->enableFileIO(output375_CH2);
    ui->controller_iso->internalBuffer750->enableFileIO(output750);

    delete(outputDir);
    return;
    */
}

void MainWindow::on_actionTake_Snapshot_triggered()
{
    /*
    QString fileName;
    showFileDialog(&fileName);
    qDebug() << fileName;
    int len = fileName.length();

    if(len==0) return; //User cancelled

    qDebug() << len;
    fileName.remove(len-4, 4);
    qDebug() << fileName;
    ui->controller_iso->takeSnapshot(&fileName);
    */
}

void MainWindow::reinitUsb(void){
    ui->controller_iso->doNotTouchGraph = true;
    ui->controller_iso->driver->saveState(&reinitdeviceMode, &reinitScopeGain, &reinitCurrentPsuVoltage, &reinitDigitalPinState);

#ifdef PLATFORM_WINDOWS
    reinitUsbStage2();
#else
    if(!(ui->controller_iso->driver->connected)){
        reinitUsbStage2();
    } else{
        ui->controller_iso->driver->shutdownProcedure();
        QTimer::singleShot(3500, this, SLOT(reinitUsbStage2()));
    }
#endif
    qDebug() << "ReinitUsb Stage 1 complete";
}

void MainWindow::reinitUsbStage2(void){
    qDebug() << "ReinitUsb entering stage 2";
    delete(ui->controller_iso->driver);
    qDebug() << "Reinitialising USB driver!";
    ui->controller_iso->driver = new _PLATFORM_DEPENDENT_USB_OBJECT();

    //Reconnect the other objects.
    ui->controller_iso->driver->setBufferPtr(ui->bufferDisplay);
    connect(ui->debugButton1, SIGNAL(clicked()), ui->controller_iso->driver, SLOT(avrDebug()));
    connect(ui->debugButton3, SIGNAL(clicked()), ui->controller_iso->driver, SLOT(bootloaderJump()));
    connect(ui->psuSlider, SIGNAL(voltageChanged(double)), ui->controller_iso->driver, SLOT(setPsu(double)));
    connect(ui->controller_iso, SIGNAL(setGain(double)), ui->controller_iso->driver, SLOT(setGain(double)));
    connect(ui->controller_fg, SIGNAL(functionGenToUpdate(int,functionGenControl*)), ui->controller_iso->driver, SLOT(setFunctionGen(int,functionGenControl*)));
    connect(ui->bufferDisplay, SIGNAL(modeChange(int)), ui->controller_iso->driver, SLOT(setDeviceMode(int)));
    connect(ui->bufferDisplay, SIGNAL(updateDig(int)), ui->controller_iso->driver, SLOT(newDig(int)));

    //Set the settings again!
    connect(ui->controller_iso->driver, SIGNAL(gainBuffers(double)), ui->controller_iso, SLOT(gainBuffers(double)));
    connect(ui->controller_iso->driver, SIGNAL(disableWindow(bool)), this, SLOT(setEnabled(bool)));
    connect(ui->controller_iso->driver, SIGNAL(sendClearBuffer(bool,bool,bool)), ui->controller_iso, SLOT(clearBuffers(bool,bool,bool)));
    //connect(ui->controller_iso->driver, SIGNAL(startIsoTimer()), ui->controller_iso, SLOT(startTimer()));
    connect(ui->controller_iso->driver, SIGNAL(setVisible_CH2(bool)), ui->controller_iso, SLOT(setVisible_CH2(bool)));
    //connect(ui->controller_iso->driver, SIGNAL(enableMMTimer()), ui->controller_iso, SLOT(enableMM()));
    connect(ui->controller_iso->driver, SIGNAL(checkXY(bool)), ui->xyDisplayLabel, SLOT(setChecked(bool)));
    connect(ui->controller_iso->driver, SIGNAL(disableWindow(bool)), ui->deviceConnected, SLOT(connectedStatusChanged(bool)));
    connect(ui->controller_iso->driver, SIGNAL(upTick()), ui->controller_iso, SLOT(timerTick()));
    connect(ui->controller_iso->driver, SIGNAL(killMe()), this, SLOT(reinitUsb()));
    connect(ui->controller_iso->driver, SIGNAL(connectedStatus(bool)), ui->deviceConnected, SLOT(connectedStatusChanged(bool)));
    connect(ui->controller_iso->driver, SIGNAL(initialConnectComplete()), this, SLOT(resetUsbState()));
    ui->controller_iso->driver->setGain(reinitScopeGain);

    readSettingsFile();

    qDebug() << "ReinitUsbStage2 is returning";
}

void MainWindow::resetUsbState(void){
    //ui->controller_iso->driver->setDeviceMode(deviceMode);
    //ui->controller_iso->driver->setPsu(currentPsuVoltage);
    ui->psuSlider->poke();
    //ui->controller_iso->driver->newDig(digitalPinState);
    ui->bufferDisplay->poke();
    ui->controller_iso->driver->setFunctionGen(0,ui->controller_fg);
    ui->controller_iso->driver->setFunctionGen(1,ui->controller_fg);

    ui->controller_iso->clearBuffers(1,1,1);
    ui->controller_iso->doNotTouchGraph = false;
}


#ifdef PLATFORM_ANDROID

void MainWindow::on_actionOld_Person_Mode_triggered(bool checked)
{
    qDebug() << "Old Person Mode" << checked;
    if(checked){
        QFont font = qApp->font();
        font.setPointSize(8);
        qApp->setFont(font);
        return;
    }else{
        QFont font = qApp->font();
        font.setPointSize(6);
        qApp->setFont(font);
    }
}

void MainWindow::screenRotateEvent(Qt::ScreenOrientation orientation)
{
    qDebug() << "Orientation:" << orientation;

    QWidget *oldCentralWidget = centralWidget();
    QLayout *oldLayout = oldCentralWidget->layout();
    oldLayout->removeWidget(ui->scopeAxes);
    oldLayout->removeWidget(ui->stackedWidget);
    oldLayout->removeWidget(ui->deviceConnected);

    QLayout *newLayout;
    if((orientation == Qt::LandscapeOrientation) || (orientation == Qt::InvertedLandscapeOrientation)){
      newLayout = new QHBoxLayout(this);
      ui->stackedWidget->setVisible(0);
    } else {
      newLayout = new QVBoxLayout(this);
      ui->stackedWidget->setVisible(1);
    }
    newLayout->addWidget(ui->scopeAxes);
    newLayout->addWidget(ui->stackedWidget);
    newLayout->addWidget(ui->deviceConnected);
    newLayout->setContentsMargins(0,0,0,0);
    newLayout->setSpacing(0);

    QWidget* newCentralWidget = new QWidget();
    newCentralWidget->setLayout(newLayout);
    setCentralWidget(newCentralWidget);
    delete(oldCentralWidget);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event){
    //qDebug() << event;
    if(event->type() == QEvent::Gesture){
        qDebug() << "gesture!!";
        return gestureFilter(static_cast<QGestureEvent*>(event));
    } else {
        return false;
    }


    //return QMainWindow::eventFilter(obj, event);
}

bool MainWindow::gestureFilter(QGestureEvent *event){
    QGesture *capturedGesture = event->gesture(Qt::PinchGesture);
    if(capturedGesture->gestureType() == Qt::PinchGesture){
        qDebug() << "pinch!";
        QPinchGesture *pinchGesture = static_cast<QPinchGesture *>(capturedGesture);
        qDebug() << "Last Centre Point" << pinchGesture->lastCenterPoint();
        qDebug() << "Last Scale Factor" << pinchGesture->lastScaleFactor();
        qDebug() << "Start Centre Point" << pinchGesture->startCenterPoint();
        qDebug() << "Total Scale Factor" << pinchGesture->totalScaleFactor();
        qDebug() << "Angle" << pinchGesture->rotationAngle();

        qreal totalScaleFactor = pinchGesture->totalScaleFactor();

        bool embiggen;
        if(totalScaleFactor >= ANDROID_SCALE_INSENSITIVITY){
            embiggen = true;
            pinchGesture->setTotalScaleFactor(totalScaleFactor/ANDROID_SCALE_INSENSITIVITY);
        } else if(totalScaleFactor < (1/ANDROID_SCALE_INSENSITIVITY)){
            embiggen = false;
            pinchGesture->setTotalScaleFactor(totalScaleFactor*ANDROID_SCALE_INSENSITIVITY);
        } else {
            return true;
        }

        QPoint point = pinchGesture->centerPoint().toPoint();
        qDebug() << point;
        if(scalingInTimeAxis){
            wheelEmu = new QWheelEvent(point, (embiggen ? 120 : -120), 0, Qt::ControlModifier, Qt::Vertical);
        } else{
            wheelEmu = new QWheelEvent(point, (embiggen ? 120 : -120), 0, 0, Qt::Vertical);
        }
        ui->controller_iso->setVoltageRange(wheelEmu);

        return true;
    } else {
        return false;
    }
}

void MainWindow::horiScaleEvent(bool enabled){
    if(enabled){
        ui->scaleHoriCheck->setChecked(true);
    }
    qDebug() << "Hori Scale";
    scalingInTimeAxis = true;
    ui->scaleVertCheck->setChecked(false);
}

void MainWindow::vertScaleEvent(bool enabled){
    if(enabled){
        ui->scaleVertCheck->setChecked(true);
    }
    qDebug() << "Vert Scale";
    scalingInTimeAxis = false;
    ui->scaleHoriCheck->setChecked(false);
}

#endif

void MainWindow::on_actionCalibrate_triggered()
{
    //Must be mode 4
    //Must be DC coupled
    //Voltage must be disconnected
    caibrateStage = 0;

    if(!ui->controller_iso->driver->connected){
        calibrationMessages->setText("You need to connect the board before calibrating it!");
        calibrationMessages->exec();
        return;
    }
    if(ui->controller_iso->driver->deviceMode!=4){
        calibrationMessages->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        calibrationMessages->setText("The calibration sequence requires all devices to be turned off, except for the oscilloscope CH1 and CH2.  Is it OK for me to change your workspace?");
        int choice = calibrationMessages->exec();
        calibrationMessages->setStandardButtons(QMessageBox::Ok);
        if(choice == QMessageBox::Ok){
            qDebug() << "Changing workspace...";
            ui->psuSlider->setValue(0);
            ui->busSifferGroup_CH1->setChecked(false);
            ui->busSnifferGroup_CH2->setChecked(false);
            ui->multimeterGroup->setChecked(false);
            ui->triggerGroup->setChecked(false);
            ui->scopeGroup_CH1->setChecked(true);
            ui->scopeGroup_CH2->setChecked(true);
            ui->pausedLabeL_CH1->setChecked(false);
            ui->pausedLabel_CH2->setChecked(false);
            ui->doubleSampleLabel->setChecked(false);
            ui->acCoupledLabel_CH1->setChecked(false);
            ui->acCoupledLabel_CH2->setChecked(false);
            ui->pause_LA->setChecked(false);
            ui->multimeterPauseCheckBox->setChecked(false);
        }
        else{
            return;
        }
    }

    //Throw out old calibration data in case of bad cali
    ui->controller_iso->ch1_ref = 1.65;
    ui->controller_iso->ch2_ref = 1.65;
    ui->controller_iso->frontendGain_CH1 = (R4/(R3+R4));
    ui->controller_iso->frontendGain_CH2 = (R4/(R3+R4));
    ui->controller_iso->internalBuffer375_CH1->voltage_ref = 1.65;
    ui->controller_iso->internalBuffer750->voltage_ref = 1.65;
    ui->controller_iso->internalBuffer375_CH2->voltage_ref = 1.65;
    ui->controller_iso->internalBuffer375_CH1->frontendGain = R4/(R3+R4);
    ui->controller_iso->internalBuffer750->frontendGain = R4/(R3+R4);
    ui->controller_iso->internalBuffer375_CH2->frontendGain = R4/(R3+R4);

    settings->setValue("CalibrateVrefCH1", 1.65);
    settings->setValue("CalibrateVrefCH2", 1.65);
    settings->setValue("CalibrateGainCH1", R4/(R3+R4));
    settings->setValue("CalibrateGainCH2", R4/(R3+R4));

    qDebug() << "Calibration routine beginning!";
    calibrationMessages->setText("Please disconnect all wires from your Labrador board then press OK to continue.");
    calibrationMessages->exec();

    ui->controller_iso->clearBuffers(1,1,1);
    QTimer::singleShot(1200, this, SLOT(calibrateStage2()));
}

void MainWindow::calibrateStage2(){
    double vref_CH1 = ui->controller_iso->meanVoltageLast(1, 1, 128);
    double vref_CH2 = ui->controller_iso->meanVoltageLast(1, 2, 128);
    qDebug() << "VRef (CH1) = " << vref_CH1;
    qDebug() << "VRef (CH2) = " << vref_CH2;

    if((vref_CH1 > 1.9) | (vref_CH1 < 1.4) | (vref_CH2 > 1.9) | (vref_CH2 < 1.4)){
        calibrationMessages->setText("Calibration has been abandoned due to out-of-range values.  Both channels should show approximately 1.6V.  Please disconnect all wires from your Labrador board and try again.");
        calibrationMessages->exec();
        return;
    }

    ui->controller_iso->ch1_ref = 3.3 - vref_CH1;
    ui->controller_iso->ch2_ref = 3.3 - vref_CH2;

    ui->controller_iso->internalBuffer375_CH1->voltage_ref = 3.3 - vref_CH1;
    ui->controller_iso->internalBuffer750->voltage_ref = 3.3 - vref_CH1;
    ui->controller_iso->internalBuffer375_CH2->voltage_ref = 3.3 - vref_CH2;

    settings->setValue("CalibrateVrefCH1", vref_CH1);
    settings->setValue("CalibrateVrefCH2", vref_CH2);

    calibrationMessages->setText("Please connect both oscilloscope channels to the outer shield of the USB connector then press OK to continue.");
    calibrationMessages->exec();

    ui->controller_iso->clearBuffers(1,1,1);
    QTimer::singleShot(1200, this, SLOT(calibrateStage3()));
}

void MainWindow::calibrateStage3(){
    double vMeasured_CH1 = ui->controller_iso->meanVoltageLast(1, 1, 128);
    double vMeasured_CH2 = ui->controller_iso->meanVoltageLast(1, 2, 128);

    qDebug() << "VMeasured (CH1) = " << vMeasured_CH1;
    qDebug() << "VMeasured (CH2) = " << vMeasured_CH2;

    if((vMeasured_CH1 > 0.3) | (vMeasured_CH1 < -0.3) | (vMeasured_CH2 > 0.3) | (vMeasured_CH2 < -0.3)){
        calibrationMessages->setText("Calibration has been abandoned due to out-of-range values.  Both channels should show approximately 0V.  Please try again.");
        calibrationMessages->exec();
        return;
    }

    double vref_CH1 = ui->controller_iso->ch1_ref;
    double vref_CH2 = ui->controller_iso->ch2_ref;

    //G^ <= G
    qDebug() << "Old gain (CH1) = " << ui->controller_iso->frontendGain_CH1;
    ui->controller_iso->frontendGain_CH1 = (vref_CH1 - vMeasured_CH1)*(ui->controller_iso->frontendGain_CH1)/vref_CH1;
    ui->controller_iso->frontendGain_CH2 = (vref_CH2 - vMeasured_CH2)*(ui->controller_iso->frontendGain_CH2)/vref_CH2;
    qDebug() << "New gain (CH1) = " << ui->controller_iso->frontendGain_CH1;

    ui->controller_iso->internalBuffer375_CH1->frontendGain = (vref_CH1 - vMeasured_CH1)*(ui->controller_iso->frontendGain_CH1)/vref_CH1;
    ui->controller_iso->internalBuffer750->frontendGain = (vref_CH1 - vMeasured_CH1)*(ui->controller_iso->frontendGain_CH1)/vref_CH1;
    ui->controller_iso->internalBuffer375_CH2->frontendGain = (vref_CH2 - vMeasured_CH2)*(ui->controller_iso->frontendGain_CH2)/vref_CH2;
    settings->setValue("CalibrateGainCH1", ui->controller_iso->frontendGain_CH1);
    settings->setValue("CalibrateGainCH2", ui->controller_iso->frontendGain_CH2);
    calibrationMessages->setText("Calibration complete.");
    calibrationMessages->exec();
}

void MainWindow::rSourceIndexChanged(int newSource){
    if(newSource == 0){
#ifndef PLATFORM_ANDROID
        ui->multimeterRLabel->setVisible(true);
        ui->multimeterRComboBox->setVisible(true);
#endif
        ui->signalGenGroup_CH2->setEnabled(false);
        ui->psuGroup->setEnabled(true);
        ui->waveformSelect_CH2->setCurrentText("DC");
        ui->dcOffsetValue_CH2->setValue(0);
        ui->amplitudeValue_CH2->setValue(3);
    }
    if(newSource == 1){
#ifndef PLATFORM_ANDROID
        ui->multimeterRLabel->setVisible(true);
        ui->multimeterRComboBox->setVisible(true);
#endif
        ui->psuGroup->setEnabled(false);
        ui->signalGenGroup_CH2->setEnabled(true);
        ui->psuSlider->setValue(100);
    }

    if(newSource == 254){
        ui->signalGenGroup_CH2->setEnabled(false);
        ui->psuGroup->setEnabled(true);
#ifndef PLATFORM_ANDROID
        ui->multimeterRLabel->setVisible(false);
        ui->multimeterRComboBox->setVisible(false);
#endif
        ui->waveformSelect_CH2->setCurrentText("Square");
        ui->frequencyValue_CH2->setValue(4);
        ui->dcOffsetValue_CH2->setValue(0);
        ui->amplitudeValue_CH2->setValue(3);
    }

    if(newSource == 255){
        ui->signalGenGroup_CH2->setEnabled(true);
        ui->psuGroup->setEnabled(true);
#ifndef PLATFORM_ANDROID
        ui->multimeterRLabel->setVisible(false);
        ui->multimeterRComboBox->setVisible(false);
#endif
    }
}

void MainWindow::multimeterStateChange(bool enabled){
    if(enabled){
        int cIdx = ui->multimeterModeSelect->currentIndex();
        ui->controller_iso->setMultimeterType(cIdx);
    } else rSourceIndexChanged(255);
}

void MainWindow::on_actionLo_bw_triggered()
{
    expected_variant = 1;
    settings->setValue("ConnectionType", 0);
    if(ui->controller_iso->driver->connected) reinitUsb();
}

void MainWindow::on_actionSingle_ep_msync_triggered()
{
    expected_variant = 2;
    settings->setValue("ConnectionType", 1);
    if(ui->controller_iso->driver->connected) reinitUsb();
}

void MainWindow::on_actionSingle_ep_async_triggered()
{
    expected_variant = 2;
    settings->setValue("ConnectionType", 2);
    if(ui->controller_iso->driver->connected) reinitUsb();
}

void MainWindow::showFileDialog(QString *fileName){
    QString filters("CSV files (*.csv)");
    QString defaultFilter("CSV files (*.csv)");

    /* Static method approach */
    QString temp = QFileDialog::getSaveFileName(0, "Save file", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
        filters, &defaultFilter);

    *(fileName) = temp;
}

void MainWindow::on_actionSnapshot_CH1_triggered()
{
  qDebug() << "on_actionSnapshot_CH1_triggered()";
  QString fileName;
  showFileDialog(&fileName);
  qDebug() << fileName;
  int len = fileName.length();

  if(len==0) return; //User cancelled

  ui->controller_iso->takeSnapshot(&fileName, 1);
}

void MainWindow::on_actionSnapshot_CH2_triggered()
{
  qDebug() << "on_actionSnapshot_CH2_triggered()";
  QString fileName;
  showFileDialog(&fileName);
  qDebug() << fileName;
  int len = fileName.length();

  if(len==0) return; //User cancelled
  ui->controller_iso->takeSnapshot(&fileName, 2);
}

void MainWindow::on_actionRecord_CH1_triggered(bool checked)
{
    qDebug() << "on_actionRecord_CH1_triggered(bool checked)";
    if(!checked){
        if(ui->controller_iso->driver->deviceMode!=6){
            ui->controller_iso->internalBuffer375_CH1->disableFileIO();
            delete(output375_CH1);
        } else {
            ui->controller_iso->internalBuffer750->disableFileIO();
            delete(output750);
        }
        ui->bufferDisplay->scopeDsrDisableOverride = false;
        ui->bufferDisplay->poke();
        return;
    }
    QString fileName;
    showFileDialog(&fileName);
    qDebug() << fileName;
    int len = fileName.length();

#ifndef PLATFORM_ANDROID
    if(len==0){
        ui->actionRecord_CH1->setChecked(0);
        return; //User cancelled
    }
#endif
    if(ui->controller_iso->driver->deviceMode!=6){
        output375_CH1 = new QFile(fileName);
        ui->controller_iso->internalBuffer375_CH1->enableFileIO(output375_CH1);
    } else {
        output750 = new QFile(fileName);
        ui->controller_iso->internalBuffer750->enableFileIO(output750);
    }
    ui->bufferDisplay->scopeDsrDisableOverride = true;
    ui->bufferDisplay->poke();
    return;
}

void MainWindow::on_actionRecord_CH2_triggered(bool checked)
{
    qDebug() << "on_actionRecord_CH2_triggered(bool checked)";
    if(!checked){
        ui->controller_iso->internalBuffer375_CH2->disableFileIO();
        delete(output375_CH2);
        return;
    }

    QString fileName;
    showFileDialog(&fileName);
    qDebug() << fileName;
    int len = fileName.length();

#ifndef PLATFORM_ANDROID
    if(len==0){
        ui->actionRecord_CH2->setChecked(0);
        return; //User cancelled
    }
#endif
    output375_CH2 = new QFile(outputDir->filePath("375_CH2.csv"));
    ui->controller_iso->internalBuffer375_CH2->enableFileIO(output375_CH2);
    return;
}

//Disable the serial, without wiping everything!
void MainWindow::serialEmergencyDisable(int channel){
    qDebug("MainWindow acknowledges disconnect from channel %d", channel);

    if(channel==1){
        //Disable the serial as if the user turned it off manually.
        ui->serialDecodingCheck_CH1->setChecked(false);

        //Bring back the lost text.
        ui->console1->setVisible(true);
        //Warn the user that the wire has been disconnected.
        QApplication::beep();
        ui->console1->appendPlainText("\n\n***Error:UART is not connected***\n***Serial Decoding has been disabled***");
        //Scroll to end of console.
        QTextCursor c =  ui->console1->textCursor();
        c.movePosition(QTextCursor::End);
        ui->console1->setTextCursor(c);
    }
    else{
        //Disable the serial as if the user turned it off manually.
        ui->serialDecodingCheck_CH2->setChecked(false);

        //Bring back the lost text.
        ui->console2->setVisible(true);
        //Warn the user that the wire has been disconnected.
        QApplication::beep();
        ui->console2->appendPlainText("\n\n***Error:UART is not connected***\n***Serial Decoding has been disabled***");
        //Scroll to end of console.
        QTextCursor c =  ui->console2->textCursor();
        c.movePosition(QTextCursor::End);
        ui->console2->setTextCursor(c);
    }

}
