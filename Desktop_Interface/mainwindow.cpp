#include "mainwindow.h"
#include "uartstyledecoder.h"
#include "daqform.h"
#include <QDesktopServices>
#include "espospinbox.h"

namespace
{
   constexpr uint32_t MAX_CONSOLE_BLOCK_COUNT = 512;
   constexpr char kDocumentationUrl[] = "https://github.com/EspoTek/Labrador/wiki";
   constexpr char kPinoutUrl[] = "https://github.com/EspoTek/Labrador/wiki/Pinout";
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    calibrationMessages = new QMessageBox();
    ui->psuDisplay->display("4.00");
    ui->bufferDisplay->refreshImage();

    ui->waveformSelect_CH1->readWaveformList();
    ui->waveformSelect_CH2->readWaveformList();

    labelPsu();

    ui->psuDisplay->display("4.50");

    ui->controller_iso->setDriver(new _PLATFORM_DEPENDENT_USB_OBJECT());
    ui->controller_iso->setAxes(ui->scopeAxes);

    ui->timeBaseSlider->setMaximum(10*log10(MAX_WINDOW_SIZE));

    //ui->controller_iso->driver->setBufferPtr(ui->bufferDisplay);
    ui->cursorStatsLabel->hide();
    initialisePlot();
    menuSetup();
    readSettingsFile();

    ui->voltageInfoMaxDisplay_CH1->display(5312);
    ui->voltageInfoMinDisplay_CH1->display(0.01);
    ui->voltageInfoMeanDisplay_CH1->display(0.02);
    ui->voltageInfoRmsDisplay_CH1->display(6.00);
    connectDisplaySignals();

    ui->controller_iso->internalBuffer375_CH1->m_console1 = ui->console1;
    ui->controller_iso->internalBuffer375_CH1->m_console2 = ui->console2;

    ui->controller_iso->internalBuffer375_CH2->m_console1 = ui->console1;
    ui->controller_iso->internalBuffer375_CH2->m_console2 = ui->console2;
    initShortcuts();

    ui->debugButton1->setVisible(0);
    ui->debugButton2->setVisible(0);
    ui->debugButton3->setVisible(0);
    ui->debugConsole->setVisible(0);

//    // Set the consoles to be resizeable
//    for (const auto & console : {ui->console1, ui->console2})
//    {
//        console->setWindowFlags(Qt::SubWindow);
//        QSizeGrip* sizeGrip = new QSizeGrip(console);
//        QGridLayout* layout = new QGridLayout(console);
//        layout->addWidget(sizeGrip, 0,0,1,1,Qt::AlignBottom | Qt::AlignLeft);
//    }

    for (const auto & console : {ui->console1, ui->console2})
    {
        QFont font("Monospace");
        font.setStyleHint(QFont::Monospace);
        console->setFont(font);
    }

#ifndef PLATFORM_ANDROID
    ui->kickstartIsoButton->setVisible(0);
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
        //ui->controller_iso->driver->setBufferPtr(ui->bufferDisplay);
        connect(ui->debugButton1, SIGNAL(clicked()), ui->controller_iso->driver, SLOT(avrDebug()));
        connect(ui->psuSlider, SIGNAL(voltageChanged(double)), ui->controller_iso->driver, SLOT(setPsu(double)));
        connect(ui->controller_iso, SIGNAL(setGain(double)), ui->controller_iso->driver, SLOT(setGain(double)));
        connect(ui->controller_fg, &functionGenControl::functionGenToUpdate, ui->controller_iso->driver, &genericUsbDriver::setFunctionGen);
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
        connect(ui->controller_iso->driver, SIGNAL(signalFirmwareFlash(void)), ui->deviceConnected, SLOT(flashingFirmware(void)));

        ui->serialDecodingModeSelect_CH1->setVisible(false);
        ui->serialDecodingModeSelect_CH2->setVisible(false);

        QTimer::singleShot(30, this, SLOT(dpiAutoScaling()));

        ui->androidMenuButton->setVisible(false);


        ui->menuAndroid_Special->menuAction()->setVisible(false);
    #endif

    connect(ui->controller_iso->driver, SIGNAL(killMe()), this, SLOT(reinitUsb()));
    ui->console1->setMaximumBlockCount(MAX_CONSOLE_BLOCK_COUNT);
    ui->console2->setMaximumBlockCount(MAX_CONSOLE_BLOCK_COUNT);
    //ui->frequencyValue_CH2->setValue(369);
    //ui->amplitudeValue_CH2->setValue(2);
    ui->controller_iso->doNotTouchGraph = false;

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

    connect(ui->controller_iso->driver, SIGNAL(signalFirmwareFlash(void)), ui->deviceConnected, SLOT(flashingFirmware(void)));
    connect(ui->controller_iso->internalBuffer375_CH1, SIGNAL(fileIOinternalDisable()), this, SLOT(fileLimitReached_CH1()));
    connect(ui->controller_iso->internalBuffer750, SIGNAL(fileIOinternalDisable()), this, SLOT(fileLimitReached_CH1()));
    connect(ui->controller_iso->internalBuffer375_CH2, SIGNAL(fileIOinternalDisable()), this, SLOT(fileLimitReached_CH2()));

    connect(ui->controller_iso, SIGNAL(showRealtimeButton(bool)), ui->realTimeButton, SLOT(setVisible(bool)));
    connect(ui->realTimeButton, SIGNAL(pressed()), ui->controller_iso, SLOT(disableFileMode()));


	
    connect(ui->pausedLabeL_CH1, SIGNAL(toggled(bool)), this, SLOT(paused(bool)));
    connect(ui->pausedLabel_CH2, SIGNAL(toggled(bool)), this, SLOT(paused(bool)));
    connect(ui->pause_LA, SIGNAL(toggled(bool)), this, SLOT(paused(bool)));
    connect(ui->multimeterPauseCheckBox, SIGNAL(toggled(bool)), this, SLOT(paused(bool)));

    connect(ui->hideCH1Box, SIGNAL(toggled(bool)), ui->controller_iso, SLOT(hideCH1(bool)));
    connect(ui->hideCH2Box, SIGNAL(toggled(bool)), ui->controller_iso, SLOT(hideCH2(bool)));

	ui->hideCH1Box->setVisible(false);
	ui->hideCH2Box->setVisible(false);

    ui->realTimeButton->setVisible(false);

    if ((QApplication::desktop()->availableGeometry().width() >= 1920) || (QApplication::desktop()->availableGeometry().height() >= 1080))
    {
        this->setGeometry(64, 64, 1920, 1080);
    }
    else if ((QApplication::desktop()->availableGeometry().width() < 1440) || (QApplication::desktop()->availableGeometry().height() < 900))
    {
        qDebug() << "Low resolution detected:" << QApplication::desktop()->availableGeometry().width() << "x" << QApplication::desktop()->availableGeometry().height();
        this->setGeometry(64, 64, 800, 600);
    }
    else
    {
        this->setGeometry(64, 64, 1440, 880);
    }

    connect(ui->offsetSpinBox_CH1, SIGNAL(valueChanged(double)), ui->controller_iso, SLOT(offsetChanged_CH1(double)));
    connect(ui->offsetSpinBox_CH2, SIGNAL(valueChanged(double)), ui->controller_iso, SLOT(offsetChanged_CH2(double)));
    connect(ui->attenuationComboBox_CH1, SIGNAL(currentIndexChanged(int)), ui->controller_iso, SLOT(attenuationChanged_CH1(int)));
    connect(ui->attenuationComboBox_CH2, SIGNAL(currentIndexChanged(int)), ui->controller_iso, SLOT(attenuationChanged_CH2(int)));
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
    textLabel->setFont(QFont("Courier New", 16));
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

    if(forceSquare)
    {
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

    // This prevents the multimeter LCD labels from being differently-sized
    QRect mmGeometry = ui->gridLayout->geometry();
    int spacing = ui->gridLayout->spacing();
    int mmHeight = mmGeometry.height();
    mmGeometry.setHeight(mmHeight - ((mmHeight - (3 * spacing)) % 4));
    ui->gridLayout->setGeometry(mmGeometry);
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
    ui->actionGainAuto->setChecked(true);

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

    serialProtocolGroup = new QActionGroup(this);
    serialProtocolGroup->addAction(ui->actionSerial);
    serialProtocolGroup->addAction(ui->actionI2C);


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
    ui->action9600->setChecked(true);

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
    ui->action9600_2->setChecked(true);

    uartParityGroup_CH1 = new QActionGroup(this);
    uartParityGroup_CH1->addAction(ui->actionNone);
    uartParityGroup_CH1->addAction(ui->actionEven);
    uartParityGroup_CH1->addAction(ui->actionOdd);
    ui->actionNone->setChecked(true);

    uartParityGroup_CH2 = new QActionGroup(this);
    uartParityGroup_CH2->addAction(ui->actionNone_2);
    uartParityGroup_CH2->addAction(ui->actionEven_2);
    uartParityGroup_CH2->addAction(ui->actionOdd_2);
    ui->actionNone_2->setChecked(true);

    connectionTypeGroup = new QActionGroup(this);
    connectionTypeGroup->addAction(ui->actionLo_bw);
    connectionTypeGroup->addAction(ui->actionSingle_ep_msync);
    connectionTypeGroup->addAction(ui->actionSingle_ep_async);
    ui->actionLo_bw->setChecked(true);
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
        ui->action600->setChecked(true);
        return;
        }
    if(currentAction==ui->action600){
        ui->action1200->setChecked(true);
        return;
        }
    if(currentAction==ui->action1200){
        ui->action2400->setChecked(true);
        return;
        }
    if(currentAction==ui->action2400){
        ui->action4800->setChecked(true);
        return;
        }
    if(currentAction==ui->action4800){
        ui->action9600->setChecked(true);
        return;
        }
    if(currentAction==ui->action9600){
        ui->action14400->setChecked(true);
        return;
        }
    if(currentAction==ui->action14400){
        ui->action19200->setChecked(true);
        return;
        }
    if(currentAction==ui->action19200){
        ui->action28800->setChecked(true);
        return;
        }
    if(currentAction==ui->action28800){
        ui->action38400->setChecked(true);
        return;
        }
    if(currentAction==ui->action38400){
        ui->action57600->setChecked(true);
        return;
        }
    if(currentAction==ui->action57600){
        ui->action115200->setChecked(true);
        return;
        }
    if(currentAction==ui->action115200){
        ui->action300->setChecked(true);
        return;
        }
    qFatal("Invalid state in MainWindow::cycleBaudRate_CH1()");
}

void MainWindow::cycleBaudRateBackwards_CH1(){
    QAction *currentAction = uartBaudGroup_CH1->checkedAction();
    qDebug() << currentAction;
    if(currentAction==ui->action1200){
        ui->action600->setChecked(true);
        return;
        }
    if(currentAction==ui->action2400){
        ui->action1200->setChecked(true);
        return;
        }
    if(currentAction==ui->action4800){
        ui->action2400->setChecked(true);
        return;
        }
    if(currentAction==ui->action9600){
        ui->action4800->setChecked(true);
        return;
        }
    if(currentAction==ui->action14400){
        ui->action9600->setChecked(true);
        return;
        }
    if(currentAction==ui->action19200){
        ui->action14400->setChecked(true);
        return;
        }
    if(currentAction==ui->action28800){
        ui->action19200->setChecked(true);
        return;
        }
    if(currentAction==ui->action38400){
        ui->action28800->setChecked(true);
        return;
        }
    if(currentAction==ui->action57600){
        ui->action38400->setChecked(true);
        return;
        }
    if(currentAction==ui->action115200){
        ui->action57600->setChecked(true);
        return;
        }
    if(currentAction==ui->action300){
        ui->action115200->setChecked(true);
        return;
        }
    if(currentAction==ui->action600){
        ui->action300->setChecked(true);
        return;
        }
    qFatal("Invalid state in MainWindow::cycleBaudRateBackwards_CH1()");
}

void MainWindow::cycleBaudRate_CH2(){
    QAction *currentAction = uartBaudGroup_CH2->checkedAction();
    qDebug() << currentAction;
    if(currentAction==ui->action300_2){
        ui->action600_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action600_2){
        ui->action1200_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action1200_2){
        ui->action2400_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action2400_2){
        ui->action4800_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action4800_2){
        ui->action9600_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action9600_2){
        ui->action14400_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action14400_2){
        ui->action19200_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action19200_2){
        ui->action28800_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action28800_2){
        ui->action38400_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action38400_2){
        ui->action57600_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action57600_2){
        ui->action115200_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action115200_2){
        ui->action300_2->setChecked(true);
        return;
        }
    qFatal("Invalid state in MainWindow::cycleBaudRate_CH2()");
}

void MainWindow::cycleBaudRateBackwards_CH2(){
    QAction *currentAction = uartBaudGroup_CH2->checkedAction();
    qDebug() << currentAction;
    if(currentAction==ui->action1200_2){
        ui->action600_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action2400_2){
        ui->action1200_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action4800_2){
        ui->action2400_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action9600_2){
        ui->action4800_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action14400_2){
        ui->action9600_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action19200_2){
        ui->action14400_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action28800_2){
        ui->action19200_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action38400_2){
        ui->action28800_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action57600_2){
        ui->action38400_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action115200_2){
        ui->action57600_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action300_2){
        ui->action115200_2->setChecked(true);
        return;
        }
    if(currentAction==ui->action600_2){
        ui->action300_2->setChecked(true);
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
    ui->controller_iso->delayUpdated(ui->controller_iso->delay);
}

void MainWindow::cycleDelayLeft(){
    qDebug() << "LEFT";
    double mws = ui->controller_iso->fileModeEnabled ? ui->controller_iso->daq_maxWindowSize : ((double)MAX_WINDOW_SIZE);
    ui->controller_iso->delay += ui->controller_iso->window/10;
    if(ui->controller_iso->delay > (mws - ui->controller_iso->window)) ui->controller_iso->delay = (mws - ui->controller_iso->window);
    ui->controller_iso->delayUpdated(ui->controller_iso->delay);
}

void MainWindow::cycleDelayRight_large(){
    qDebug() << "RIGHT";
    ui->controller_iso->delay -= ui->controller_iso->window/2;
    if(ui->controller_iso->delay < 0) ui->controller_iso->delay = 0;
    ui->controller_iso->delayUpdated(ui->controller_iso->delay);
}

void MainWindow::cycleDelayLeft_large(){
    qDebug() << "LEFT";
    double mws = ui->controller_iso->fileModeEnabled ? ui->controller_iso->daq_maxWindowSize : ((double)MAX_WINDOW_SIZE);
    ui->controller_iso->delay += ui->controller_iso->window/2;
    if(ui->controller_iso->delay > (mws - ui->controller_iso->window)) ui->controller_iso->delay = (mws - ui->controller_iso->window);
    ui->controller_iso->delayUpdated(ui->controller_iso->delay);
}

void MainWindow::enableLabradorDebugging(){
    qDebug() << "DEBUG MODE ACTIVE";

    ui->debugButton1->setVisible(1);
    ui->debugButton2->setVisible(1);
    ui->debugButton3->setVisible(1);
#ifndef PLATFORM_ANDROID
    ui->kickstartIsoButton->setVisible(1);
#endif
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
    psu_voltage_calibration_offset = settings->value("CalibratePsu", 0).toDouble();

    daq_num_to_average = settings->value("daq_defaultAverage", 1).toInt();
    daq_max_file_size = settings->value("daq_defaultFileSize", 2048000000).toULongLong();

    //Change connection Type
    switch(connectionType){
    case 0:
        ui->actionLo_bw->setChecked(true);
        on_actionLo_bw_triggered();
        break;
    case 1:
        ui->actionSingle_ep_msync->setChecked(true);
        on_actionSingle_ep_msync_triggered();
        break;
    case 2:
        ui->actionSingle_ep_async->setChecked(true);
        on_actionSingle_ep_async_triggered();
        break;
    }

    //Fill in calibration data
    ui->controller_iso->ch1_ref = 3.3 - calibrate_vref_ch1;
    ui->controller_iso->ch2_ref = 3.3 - calibrate_vref_ch2;
    ui->controller_iso->frontendGain_CH1 = calibrate_gain_ch1;
    ui->controller_iso->frontendGain_CH2 = calibrate_gain_ch2;
    ui->controller_iso->internalBuffer375_CH1->m_voltage_ref = 3.3 - calibrate_vref_ch1;
    ui->controller_iso->internalBuffer750->m_voltage_ref = 3.3 - calibrate_vref_ch1;
    ui->controller_iso->internalBuffer375_CH2->m_voltage_ref = 3.3 - calibrate_vref_ch2;
    ui->controller_iso->internalBuffer375_CH1->m_frontendGain = calibrate_gain_ch1;
    ui->controller_iso->internalBuffer750->m_frontendGain = calibrate_gain_ch1;
    ui->controller_iso->internalBuffer375_CH2->m_frontendGain = calibrate_gain_ch2;

    if(!dt_AlreadyAskedAboutCalibration && ((calibrate_vref_ch1 == 1.65) || (calibrate_vref_ch2 == 1.65) || (calibrate_gain_ch1 == R4/(R3+R4)) || (calibrate_gain_ch2 == R4/(R3+R4)))){
        //Prompt user to calibrate if no calibration data found.
        QApplication::processEvents();
        calibrationMessages->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        calibrationMessages->setText("No calibration data detected!\nWould you like to run calibration once connected?");
        dt_userWantsToCalibrate = calibrationMessages->exec();
        qDebug() << "dt_userWantsToCalibrate" << dt_userWantsToCalibrate;
        dt_AlreadyAskedAboutCalibration = true;
    }
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
        QTimer::singleShot(1000, this, SLOT(reinitUsbStage2()));
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
    //ui->controller_iso->driver->setBufferPtr(ui->bufferDisplay);
    connect(ui->debugButton1, SIGNAL(clicked()), ui->controller_iso->driver, SLOT(avrDebug()));
    connect(ui->debugButton3, SIGNAL(clicked()), ui->controller_iso->driver, SLOT(bootloaderJump()));
    connect(ui->psuSlider, SIGNAL(voltageChanged(double)), ui->controller_iso->driver, SLOT(setPsu(double)));
    connect(ui->controller_iso, SIGNAL(setGain(double)), ui->controller_iso->driver, SLOT(setGain(double)));
    connect(ui->controller_fg, &functionGenControl::functionGenToUpdate, ui->controller_iso->driver, &genericUsbDriver::setFunctionGen);
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
    connect(ui->controller_iso->driver, SIGNAL(signalFirmwareFlash(void)), ui->deviceConnected, SLOT(flashingFirmware(void)));
    connect(ui->controller_iso->driver, SIGNAL(initialConnectComplete()), this, SLOT(resetUsbState()));
    ui->controller_iso->driver->setGain(reinitScopeGain);
    ui->controller_iso->driver->psu_offset = psu_voltage_calibration_offset;

    readSettingsFile();

    ui->controller_iso->driver->calibrateOnConnect = (dt_userWantsToCalibrate == 16384); //Yes/No are 16384/65536 for some reason.  I think 0/1 are reserved for OK/Cancel.
    connect(ui->controller_iso->driver, SIGNAL(calibrateMe()), this, SLOT(on_actionCalibrate_triggered()));
    qDebug() << "ReinitUsbStage2 is returning";
}

void MainWindow::resetUsbState(void){
	using functionGen::ChannelID;
    //ui->controller_iso->driver->setDeviceMode(deviceMode);
    //ui->controller_iso->driver->setPsu(currentPsuVoltage);
    ui->psuSlider->poke();
    //ui->controller_iso->driver->newDig(digitalPinState);
    ui->bufferDisplay->poke();
    ui->controller_iso->driver->setFunctionGen(ChannelID::CH1, ui->controller_fg->getChannelController(ChannelID::CH1));
    ui->controller_iso->driver->setFunctionGen(ChannelID::CH2, ui->controller_fg->getChannelController(ChannelID::CH2));

    ui->controller_iso->clearBuffers(1,1,1);
    ui->controller_iso->doNotTouchGraph = false;
}


#ifdef PLATFORM_ANDROID
//Should be called "High Resolution mode".  This function has been comandeered for Android devices with 1080p or higher resolutions.
void MainWindow::on_actionOld_Person_Mode_triggered(bool checked)
{
    //Scope Page
    ui->scopeGroup_CH1->setFlat(true);
    ui->scopeGroup_CH2->setFlat(true);
    ui->triggerGroup->setFlat(true);
    ui->cursorGroup->setFlat(true);


    //Signal Gen Page
    ui->signalGenGroup_CH1->setFlat(true);
    ui->signalGenGroup_CH2->setFlat(true);

    //Multimeter Page
    ui->multimeterGroup->setFlat(true);

    //Logic Analyzer Page
    ui->digitalOutputGroup->setFlat(true);
    ui->busSifferGroup_CH1->setFlat(true);
    ui->busSnifferGroup_CH2->setFlat(true);
    ui->serialDecodingCheck_CH1->setFlat(true);
    ui->serialDecodingCheck_CH2->setFlat(true);




    for (int i=1;i<100;i++){
        qDebug() << "High Resolution Mode" << checked;
    }
    if(checked){
        //Embiggen the fonts
        QFont font_scope1 = ui->scopeGroup_CH1->font();
        font_scope1.setPointSize(16);
        font_scope1.setBold(true);
        ui->scopeGroup_CH1->setFont(font_scope1);

        QFont font_scope2 = ui->scopeGroup_CH2->font();
        font_scope2.setPointSize(16);
        font_scope2.setBold(true);
        ui->scopeGroup_CH2->setFont(font_scope2);

        QFont font_scope_trigger = ui->triggerGroup->font();
        font_scope_trigger.setPointSize(16);
        font_scope_trigger.setBold(true);
        ui->triggerGroup->setFont(font_scope_trigger);

        QFont font_cursor_scaling = ui->cursorGroup->font();
        font_cursor_scaling.setPointSize(16);
        font_cursor_scaling.setBold(true);
        ui->cursorGroup->setFont(font_cursor_scaling);

        QFont font_scope_pause = ui->pausedLabeL_CH1->font();
        font_scope_pause.setPointSize(16);
        font_scope_pause.setBold(true);
        ui->pausedLabeL_CH1->setFont(font_scope_pause);

        QFont font_sg1 = ui->signalGenGroup_CH1->font();
        font_sg1.setPointSize(16);
        font_sg1.setBold(true);
        ui->signalGenGroup_CH1->setFont(font_sg1);

        QFont font_sg2 = ui->signalGenGroup_CH2->font();
        font_sg2.setPointSize(16);
        font_sg2.setBold(true);
        ui->signalGenGroup_CH2->setFont(font_sg2);

        QFont font_3 = ui->page_3->font();
        font_3.setPointSize(16);
        font_3.setBold(true);
        ui->page_3->setFont(font_3);

        QFont font_4 = ui->page_4->font();
        font_4.setPointSize(16);
        font_4.setBold(true);
        ui->page_4->setFont(font_4);

        QFont font_5 = ui->page_5->font();
        font_5.setPointSize(16);
        font_5.setBold(true);
        ui->page_5->setFont(font_5);

        QFont font_realtime = ui->realTimeButton->font();
        font_realtime.setPointSize(16);
        font_realtime.setBold(true);
        ui->realTimeButton->setFont(font_realtime);

        QFont font_android_menu = ui->androidMenuButton->font();
        font_android_menu.setPointSize(16);
        font_android_menu.setBold(true);
        ui->androidMenuButton->setFont(font_android_menu);


        //Embiggen the serial consoles.
        ui->console1->setMinimumHeight(128);
        ui->console1->setMaximumHeight(256);
        ui->console2->setMinimumHeight(128);
        ui->console2->setMaximumHeight(256);

        //Increase the size of the swiped stack
        ui->stackedWidget->setMaximumHeight(720);
        ui->stackedWidget->setMinimumHeight(480);

        //Grow Pause buttons
        ui->pausedLabeL_CH1->setMaximumHeight(80);
        ui->pausedLabel_CH2->setMaximumHeight(80);
        ui->pause_LA->setMaximumHeight(80);
        ui->multimeterPauseCheckBox->setMaximumHeight(80);

        //Show the "single shot" button
        ui->singleShotCheckBox->setVisible(true);


    }else{
        //Shrink the fonts
        QFont font_scope1 = ui->scopeGroup_CH1->font();
        font_scope1.setPointSize(11);
        font_scope1.setBold(true);
        ui->scopeGroup_CH1->setFont(font_scope1);

        QFont font_scope2 = ui->scopeGroup_CH2->font();
        font_scope2.setPointSize(11);
        font_scope2.setBold(true);
        ui->scopeGroup_CH2->setFont(font_scope2);

        QFont font_scope_trigger = ui->triggerGroup->font();
        font_scope_trigger.setPointSize(11);
        font_scope_trigger.setBold(true);
        ui->triggerGroup->setFont(font_scope_trigger);

        QFont font_cursor_scaling = ui->cursorGroup->font();
        font_cursor_scaling.setPointSize(11);
        font_cursor_scaling.setBold(true);
        ui->cursorGroup->setFont(font_cursor_scaling);

        QFont font_scope_pause = ui->pausedLabeL_CH1->font();
        font_scope_pause.setPointSize(11);
        font_scope_pause.setBold(true);
        ui->pausedLabeL_CH1->setFont(font_scope_pause);

        QFont font_sg1 = ui->signalGenGroup_CH1->font();
        font_sg1.setPointSize(11);
        font_sg1.setBold(true);
        ui->signalGenGroup_CH1->setFont(font_sg1);

        QFont font_sg2 = ui->signalGenGroup_CH2->font();
        font_sg2.setPointSize(11);
        font_sg2.setBold(true);
        ui->signalGenGroup_CH2->setFont(font_sg2);

        QFont font_3 = ui->page_3->font();
        font_3.setPointSize(11);
        font_3.setBold(true);
        ui->page_3->setFont(font_3);

        QFont font_4 = ui->page_4->font();
        font_4.setPointSize(11);
        font_4.setBold(true);
        ui->page_4->setFont(font_4);

        QFont font_5 = ui->page_5->font();
        font_5.setPointSize(11);
        font_5.setBold(true);
        ui->page_5->setFont(font_5);

        QFont font_realtime = ui->realTimeButton->font();
        font_realtime.setPointSize(11);
        font_realtime.setBold(true);
        ui->realTimeButton->setFont(font_realtime);

        QFont font_android_menu = ui->androidMenuButton->font();
        font_android_menu.setPointSize(11);
        font_android_menu.setBold(true);
        ui->androidMenuButton->setFont(font_android_menu);

        //Shrink the serial consoles.
        ui->console1->setMinimumHeight(0);
        ui->console1->setMaximumHeight(96);
        ui->console2->setMinimumHeight(0);
        ui->console2->setMaximumHeight(96);

        //Increase the size of the swiped stack
        ui->stackedWidget->setMaximumHeight(480);
        ui->stackedWidget->setMinimumHeight(400);

        //Shrink Pause buttons
        ui->pausedLabeL_CH1->setMaximumHeight(40);
        ui->pausedLabel_CH2->setMaximumHeight(40);
        ui->pause_LA->setMaximumHeight(40);
        ui->multimeterPauseCheckBox->setMaximumHeight(40);

        //Hide the "single shot" button
        ui->singleShotCheckBox->setVisible(false);

    }
    return;

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
        calibrationMessages->setStandardButtons(QMessageBox::Ok);
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
    ui->controller_iso->internalBuffer375_CH1->m_voltage_ref = 1.65;
    ui->controller_iso->internalBuffer750->m_voltage_ref = 1.65;
    ui->controller_iso->internalBuffer375_CH2->m_voltage_ref = 1.65;
    ui->controller_iso->internalBuffer375_CH1->m_frontendGain = R4/(R3+R4);
    ui->controller_iso->internalBuffer750->m_frontendGain = R4/(R3+R4);
    ui->controller_iso->internalBuffer375_CH2->m_frontendGain = R4/(R3+R4);

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

    if((vref_CH1 > 2.1) | (vref_CH1 < 1.1) | (vref_CH2 > 2.1) | (vref_CH2 < 1.1)){
        calibrationMessages->setText("Calibration has been abandoned due to out-of-range values.  Both channels should show approximately 1.6V.  Please disconnect all wires from your Labrador board and try again.");
        calibrationMessages->exec();
        return;
    }

    ui->controller_iso->ch1_ref = 3.3 - vref_CH1;
    ui->controller_iso->ch2_ref = 3.3 - vref_CH2;

    ui->controller_iso->internalBuffer375_CH1->m_voltage_ref = 3.3 - vref_CH1;
    ui->controller_iso->internalBuffer750->m_voltage_ref = 3.3 - vref_CH1;
    ui->controller_iso->internalBuffer375_CH2->m_voltage_ref = 3.3 - vref_CH2;

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

    ui->controller_iso->internalBuffer375_CH1->m_frontendGain = (vref_CH1 - vMeasured_CH1)*(ui->controller_iso->frontendGain_CH1)/vref_CH1;
    ui->controller_iso->internalBuffer750->m_frontendGain = (vref_CH1 - vMeasured_CH1)*(ui->controller_iso->frontendGain_CH1)/vref_CH1;
    ui->controller_iso->internalBuffer375_CH2->m_frontendGain = (vref_CH2 - vMeasured_CH2)*(ui->controller_iso->frontendGain_CH2)/vref_CH2;
    settings->setValue("CalibrateGainCH1", ui->controller_iso->frontendGain_CH1);
    settings->setValue("CalibrateGainCH2", ui->controller_iso->frontendGain_CH2);
    calibrationMessages->setText("Oscilloscope Calibration complete.");
    calibrationMessages->exec();

    if (dt_userWantsToCalibrate)
        on_actionCalibrate_2_triggered();
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
    QFileDialog dialog;

    dialog.setDefaultSuffix("csv");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setDirectory(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("CSV files (*.csv);;All Files (*)");

    int retVal = dialog.exec();

    if(!retVal){
        return; //User did not select a file!
    }

    QStringList tempList = dialog.selectedFiles();
    QString temp = tempList.first();
    *(fileName) = temp;
}

void MainWindow::openFileDialog(QString *fileName){
    QFileDialog dialog;

    dialog.setDefaultSuffix("csv");
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setDirectory(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("CSV files (*.csv);;All Files (*)");

    int retVal = dialog.exec();

    if(!retVal){
        return; //User did not select a file!
    }

    QStringList tempList = dialog.selectedFiles();
    QString temp = tempList.first();
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
    qDebug() << daq_max_file_size;
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
        ui->actionRecord_CH1->setChecked(false);
        return; //User cancelled
    }
#endif
    if(ui->controller_iso->driver->deviceMode!=6){
        output375_CH1 = new QFile(fileName);
        ui->controller_iso->internalBuffer375_CH1->enableFileIO(output375_CH1, daq_num_to_average, daq_max_file_size);
    } else {
        output750 = new QFile(fileName);
        ui->controller_iso->internalBuffer750->enableFileIO(output750, daq_num_to_average, daq_max_file_size);
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
        ui->actionRecord_CH2->setChecked(false);
        return; //User cancelled
    }
#endif
    output375_CH2 = new QFile(outputDir->filePath("375_CH2.csv"));
    ui->controller_iso->internalBuffer375_CH2->enableFileIO(output375_CH2, daq_num_to_average, daq_max_file_size);
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

void MainWindow::on_actionFirmware_Recovery_triggered()
{
    qDebug() << "on_actionFirmware_Recovery_triggered";
    ui->controller_iso->driver->manualFirmwareRecovery();
}

void MainWindow::on_actionShow_Debug_Console_triggered()
{
    enableLabradorDebugging();
}

void MainWindow::on_actionDAQ_Settings_triggered()
{
    qDebug() << "on_actionDAQ_Settings_triggered()";
    daqForm df(this, daq_num_to_average, daq_max_file_size);
    df.setModal(true);
    connect(&df, SIGNAL(updatedAveraging(int)), this, SLOT(daq_updatedAveraging(int)));
    connect(&df, SIGNAL(updatedMaxFileSize(qulonglong)), this, SLOT(daq_updatedMaxFileSize(qulonglong)));
    connect(&df, SIGNAL(saveButtonPressed()), this, SLOT(daq_saveButtonPressed()));

    df.exec();
}

void MainWindow::fileLimitReached_CH1(void){
    ui->actionRecord_CH1->setChecked(false);

    QMessageBox recordingStoppedMessageBox;
    char recordingStoppedMessage[256];
    sprintf(recordingStoppedMessage, "Maximum file size limit of %uMB reached.  Data Acquisition Stopped.", daq_max_file_size/1000000);
    recordingStoppedMessageBox.setText(recordingStoppedMessage);
    recordingStoppedMessageBox.exec();
}

void MainWindow::fileLimitReached_CH2(void){
    ui->actionRecord_CH2->setChecked(false);

    QMessageBox recordingStoppedMessageBox;
    char recordingStoppedMessage[256];
    sprintf(recordingStoppedMessage, "Maximum file size limit of %uMB reached.  Data Acquisition Stopped.", daq_max_file_size/1000000);
    recordingStoppedMessageBox.setText(recordingStoppedMessage);
    recordingStoppedMessageBox.exec();
}

void MainWindow::daq_updatedAveraging(int newVal){
    qDebug() << "MainWindow::daq_updatedAveraging" << newVal;
    daq_num_to_average = newVal;
}

void MainWindow::daq_updatedMaxFileSize(qulonglong newVal){
    qDebug() << "MainWindow::daq_updatedMaxFileSize" << newVal;
    daq_max_file_size = newVal;
}

void MainWindow::daq_saveButtonPressed(){
    qDebug() << "MainWindow::daq_saveButtonPressed";
    settings->setValue("daq_defaultAverage", daq_num_to_average);
    settings->setValue("daq_defaultFileSize", daq_max_file_size);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About EspoTek Labrador", "EspoTek Labrador, Christmas Edition 2017.\nWebsite: http://espotek.com\nContact Email: admin@espotek.com");
}

void MainWindow::on_actionOpen_DAQ_File_triggered()
{
    qDebug() << "on_actionOpen_DAQ_File_triggered";
    //Prompt user for file name
    QString fileName;
    openFileDialog(&fileName);
    qDebug() << fileName;
    int len = fileName.length();

    if(len==0) return; //User cancelled

    QFile *inputFile = new QFile(fileName);
    ui->controller_iso->loadFileBuffer(inputFile);
}

#ifdef PLATFORM_ANDROID

void MainWindow::dpiAutoScaling(){
    this->update();
    this->updateGeometry();
    this->repaint();
    QSize size = this->size();
    int numPixels = size.height() * size.width();

    for(int i=0;i<100;i++){
        qDebug() << size.height();
        qDebug() << size.width();
        qDebug() << numPixels;
    }

    if(numPixels > (1280 * 720 * 1.5)){
        on_actionOld_Person_Mode_triggered(true);
    } else on_actionOld_Person_Mode_triggered(false);
}


void MainWindow::on_androidMenuButton_clicked()
{
    //ui->menuBar->actions();
    ui->menuBar->show();
    dpiAutoScaling();
}

#endif

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_kickstartIsoButton_clicked()
{
    ui->controller_iso->driver->kickstartIso();
}

void MainWindow::on_actionCalibrate_2_triggered()
{
    qDebug() << "Calibrating PSU!";

    //Abort if Scope is uncalibrated
    if ((ui->controller_iso->ch1_ref == 1.65) && (ui->controller_iso->ch2_ref == 1.65) && (ui->controller_iso->frontendGain_CH1 ==  R4/(R3+R4)) && (ui->controller_iso->frontendGain_CH2 == R4/(R3+R4)))\
    {
        calibrationMessages->setStandardButtons(QMessageBox::Ok);
        calibrationMessages->setText("You need to calibrate the oscilloscope before the power supply!");
        calibrationMessages->exec();
        return;
    }

    calibrationMessages->setStandardButtons(QMessageBox::Ok);
    calibrationMessages->setText("Power Supply calibration requires me to control your power supply temporarily.  \n\nTO PREVENT BLUE SMOKE DAMAGE, DISCONNECT ANY CIRCUIT ATTACHED TO YOUR POWER SUPPLY NOW.");
    calibrationMessages->exec();

    qDebug() << "Beginning PSU calibration!";

    //Must be mode 0
    //Must be DC coupled
    //CH1 must be shorted to PSU out
    //Gain must be 1x
    qDebug() << "Changing workspace...";
    ui->psuSlider->setValue(0);
    ui->busSifferGroup_CH1->setChecked(false);
    ui->busSnifferGroup_CH2->setChecked(false);
    ui->multimeterGroup->setChecked(false);
    ui->triggerGroup->setChecked(false);
    ui->scopeGroup_CH1->setChecked(true);
    ui->scopeGroup_CH2->setChecked(false);
    ui->pausedLabeL_CH1->setChecked(false);
    ui->pausedLabel_CH2->setChecked(false);
    ui->doubleSampleLabel->setChecked(false);
    ui->acCoupledLabel_CH1->setChecked(false);
    ui->acCoupledLabel_CH2->setChecked(false);
    ui->pause_LA->setChecked(false);
    ui->multimeterPauseCheckBox->setChecked(false);

    ui->controller_iso->setAutoGain(false);
    ui->controller_iso->setGain(4);

    //Remove the offset before setting it again; don't want them to stack!
    ui->controller_iso->driver->psu_offset = 0;

    qDebug() << "PSU Calibration routine beginning!";
    calibrationMessages->setStandardButtons(QMessageBox::Ok);
    calibrationMessages->setText("Please connect your Labrador's Oscilloscope CH1 (DC) pin to the Power Supply Output (positive) then press OK to continue.");
    calibrationMessages->exec();

    ui->controller_iso->driver->setPsu(5);
    ui->controller_iso->clearBuffers(1,1,1);
    QTimer::singleShot(1800, this, SLOT(calibrate_psu_stage2()));
}

void MainWindow::calibrate_psu_stage2()
{
    PSU5 = ui->controller_iso->meanVoltageLast(1, 1, 128);
    qDebug() << "PSU5 =" << PSU5;
    if((PSU5 > 6) | (PSU5 < 4) ){
        ui->controller_iso->driver->setPsu(4.5);
        ui->psuSlider->setValue(0);
        ui->controller_iso->clearBuffers(1,1,1);
        ui->controller_iso->setAutoGain(true);
        ui->controller_iso->autoGain();
        calibrationMessages->setText("Calibration has been abandoned due to out-of-range values.  The oscilloscope should show approximately 5V.  Please check all wires on your Labrador board and try again.");
        calibrationMessages->exec();
        return;
    }
    ui->controller_iso->setGain(1);
    ui->controller_iso->driver->setPsu(10);
    ui->controller_iso->clearBuffers(1,1,1);
    QTimer::singleShot(1800, this, SLOT(calibrate_psu_stage3()));
}

void MainWindow::calibrate_psu_stage3()
{
    PSU10 = ui->controller_iso->meanVoltageLast(1, 1, 128);
    qDebug() << "PSU10 =" << PSU10;
    ui->controller_iso->driver->setPsu(4.5);
    ui->psuSlider->setValue(0);
    ui->controller_iso->clearBuffers(1,1,1);
    ui->controller_iso->setAutoGain(true);
    ui->controller_iso->autoGain();


    if((PSU10 > 11) | (PSU10 < 9) ){
        calibrationMessages->setText("Calibration has been abandoned due to out-of-range values.  The oscilloscope should show approximately 10V.  Please check all wires on your Labrador board and try again.");
        calibrationMessages->exec();
        return;
    }

    psu_voltage_calibration_offset = ((PSU5 - 5) + (PSU10 - 10)) / 2.0;
    settings->setValue("CalibratePsu", psu_voltage_calibration_offset);
    ui->controller_iso->driver->psu_offset = psu_voltage_calibration_offset;

    calibrationMessages->setStandardButtons(QMessageBox::Ok);
    calibrationMessages->setText("PSU calibration complete.");
    calibrationMessages->exec();

    qDebug() << "PSU Calibration complete!  Offset =" << psu_voltage_calibration_offset;
}

void MainWindow::on_actionSerial_triggered(bool checked)
{
    ui->controller_iso->setSerialType(0);
}

void MainWindow::on_actionI2C_triggered(bool checked)
{
    ui->controller_iso->setSerialType(1);
}

void MainWindow::on_actionShow_Range_Dialog_on_Main_Page_triggered(bool checked)
{
    qDebug() << "on_actionShow_Range_Dialog_on_Main_Page_triggered" << checked;
    if (checked)
    {
        scopeRangeSwitch = new scopeRangeEnterDialog(nullptr, false, ui->controller_iso->topRange, ui->controller_iso->botRange, ui->controller_iso->window, ui->controller_iso->delay);
        scopeRangeSwitch->setWindowFlags(Qt::Widget);
        ui->verticalLayout_5->insertWidget(2, scopeRangeSwitch);
        connect(scopeRangeSwitch, SIGNAL(yTopUpdated(double)), ui->controller_iso, SLOT(setTopRange(double)));
        connect(scopeRangeSwitch, SIGNAL(yBotUpdated(double)), ui->controller_iso, SLOT(setBotRange(double)));
        connect(scopeRangeSwitch, SIGNAL(windowUpdated(double)), ui->controller_iso, SLOT(setTimeWindow(double)));
        connect(scopeRangeSwitch, SIGNAL(delayUpdated(double)), ui->controller_iso, SLOT(setDelay(double)));

        connect(ui->controller_iso, SIGNAL(topRangeUpdated(double)), scopeRangeSwitch, SLOT(yTopChanged(double)));
        connect(ui->controller_iso, SIGNAL(botRangeUpdated(double)), scopeRangeSwitch, SLOT(yBotChanged(double)));
        connect(ui->controller_iso, SIGNAL(timeWindowUpdated(double)), scopeRangeSwitch, SLOT(windowChanged(double)));
        connect(ui->controller_iso, SIGNAL(delayUpdated(double)), scopeRangeSwitch, SLOT(delayChanged(double)));
    }
    else
    {
        delete scopeRangeSwitch;
        scopeRangeSwitch = nullptr;
    }
}

void MainWindow::paused(bool enabled)
{
	qDebug() << "MainWindow::paused(" << enabled << ")";
	ui->hideCH1Box->setVisible(enabled);
	ui->hideCH2Box->setVisible(enabled);
	
	if (! enabled)
	{
		ui->hideCH1Box->setChecked(false);
		ui->hideCH2Box->setChecked(false);
	}
}

void MainWindow::on_actionNone_triggered()
{
    ui->controller_iso->parity_CH1 = UartParity::None;
}

void MainWindow::on_actionEven_triggered()
{
    ui->controller_iso->parity_CH1 = UartParity::Even;
}

void MainWindow::on_actionOdd_triggered()
{
    ui->controller_iso->parity_CH1 = UartParity::Odd;
}

void MainWindow::on_actionNone_2_triggered()
{
    ui->controller_iso->parity_CH2 = UartParity::None;
}

void MainWindow::on_actionEven_2_triggered()
{
    ui->controller_iso->parity_CH2 = UartParity::Even;
}

void MainWindow::on_actionOdd_2_triggered()
{
    ui->controller_iso->parity_CH2 = UartParity::Odd;
}

void MainWindow::on_actionDocumentation_triggered()
{
    QDesktopServices::openUrl(QUrl(kDocumentationUrl, QUrl::TolerantMode));
}

void MainWindow::on_actionPinout_triggered()
{
    QDesktopServices::openUrl(QUrl(kPinoutUrl, QUrl::TolerantMode));
}
