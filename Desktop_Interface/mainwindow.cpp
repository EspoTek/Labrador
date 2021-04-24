#include "mainwindow.h"
#include "uartstyledecoder.h"
#include "daqform.h"
#include "pinoutDialog.h"
#include <QDesktopServices>
#include "espospinbox.h"


#include <algorithm>

#define DO_QUOTE(X) #X
#define QUOTE(X) DO_QUOTE(X)

#ifndef GIT_HASH_SHORT
#define GIT_HASH_SHORT 0000000
#endif

namespace
{
   constexpr uint32_t MAX_CONSOLE_BLOCK_COUNT = 512;
   constexpr char kDocumentationUrl[] = "https://github.com/EspoTek/Labrador/wiki";
   constexpr char kAboutString[] = "<h4>EspoTek Labrador</h4>"
                                   "Continuous Release<br>"\
                                   "Git hash: <a href='https://github.com/EspoTek/Labrador/commits/" QUOTE(GIT_HASH_SHORT) "'>" QUOTE(GIT_HASH_SHORT) "</a><br>"\
                                   "Website: <a href='http://espotek.com'>https://espotek.com</a><br>"\
                                   "Contact email: <a href='mailto:admin@espotek.com'>admin@espotek.com</a>";
   constexpr char kOrganisationName[] = "EspoTek";
   constexpr char kApplicationName[] = "Labrador";
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QCoreApplication::setOrganizationName(kOrganisationName);
    QCoreApplication::setApplicationName(kApplicationName);

    ui->setupUi(this);

    ui->actionQuit->setShortcut(Qt::CTRL + Qt::Key_Q); // on macOS CTRL is automaticall translated to the command key
    ui->actionPinout->setShortcut(Qt::Key_F1);

    calibrationMessages = new QMessageBox();
    ui->psuDisplay->display("4.00");
    ui->bufferDisplay->refreshImage();

    ui->waveformSelect_CH1->readWaveformList();
    ui->waveformSelect_CH2->readWaveformList();

    labelPsu();

    ui->psuDisplay->display("4.50");

    ui->controller_iso->setDriver(new _PLATFORM_DEPENDENT_USB_OBJECT(this));
    ui->controller_iso->setAxes(ui->scopeAxes);

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

    ui->debugButton1->setVisible(false);
    ui->debugButton2->setVisible(false);
    ui->debugButton3->setVisible(false);
    ui->debugConsole->setVisible(false);

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
    ui->kickstartIsoButton->setVisible(false);
    ui->console1->setVisible(false);
    ui->console2->setVisible(false);
#endif

    //ui->pausedLabel_CH2->setVisible(0);
    ui->filterLabel_CH1->setVisible(false);
    ui->filterLabel_CH2->setVisible(false);

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
		connect(ui->bufferDisplay, &bufferControl::modeChange, this, [this](){
			// Force a trigger refresh
			ui->controller_iso->setTriggerLevel(ui->triggerLevelValue->value());	
		});
        connect(ui->bufferDisplay, SIGNAL(updateDig(int)), ui->controller_iso->driver, SLOT(newDig(int)));

        //Set the settings again!
        connect(ui->controller_iso->driver, SIGNAL(gainBuffers(double)), ui->controller_iso, SLOT(gainBuffers(double)));
        connect(ui->controller_iso->driver, SIGNAL(disableWindow(bool)), this, SLOT(setEnabled(bool)));
        connect(ui->controller_iso->driver, SIGNAL(sendClearBuffer(bool,bool,bool)), ui->controller_iso, SLOT(clearChannelBuffers(bool,bool,bool)));
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

    connect(ui->controller_iso->driver.data(), &genericUsbDriver::killMe, this, &MainWindow::reinitUsb);
    ui->console1->setMaximumBlockCount(MAX_CONSOLE_BLOCK_COUNT);
    ui->console2->setMaximumBlockCount(MAX_CONSOLE_BLOCK_COUNT);
    //ui->frequencyValue_CH2->setValue(369);
    //ui->amplitudeValue_CH2->setValue(2);
    ui->controller_iso->doNotTouchGraph = false;

#ifndef PLATFORM_ANDROID
    ui->multimeterRLabel->setVisible(false);
    ui->multimeterRComboBox->setVisible(false);
#endif

    connect(ui->controller_iso, &isoDriver::multimeterREnabled, this, &MainWindow::rSourceIndexChanged);
    connect(ui->controller_iso, &isoDriver::multimeterRMS, ui->multimeterRmsDisplay, qOverload<double>(&QLCDNumber::display));
    connect(ui->controller_iso, &isoDriver::sendMultimeterLabel4, ui->multimeterRmsLabel, &QLabel::setText);
    connect(ui->controller_iso, &isoDriver::sendVRMS_CH1, ui->voltageInfoRmsDisplay_CH1, qOverload<double>(&QLCDNumber::display));
    connect(ui->controller_iso, &isoDriver::sendVRMS_CH2, ui->voltageInfoRmsDisplay_CH2, qOverload<double>(&QLCDNumber::display));

    connect(ui->controller_iso, &isoDriver::mainWindowPleaseDisableSerial, this, &MainWindow::serialEmergencyDisable);

    connect(ui->controller_iso->driver.data(), &genericUsbDriver::signalFirmwareFlash, ui->deviceConnected, &deviceConnectedDisplay::flashingFirmware);
    connect(ui->controller_iso->internalBuffer375_CH1, &isoBuffer::fileIOinternalDisable, this, &MainWindow::fileLimitReached_CH1);
    connect(ui->controller_iso->internalBuffer750, &isoBuffer::fileIOinternalDisable, this, &MainWindow::fileLimitReached_CH1);
    connect(ui->controller_iso->internalBuffer375_CH2, &isoBuffer::fileIOinternalDisable, this, &MainWindow::fileLimitReached_CH2);

    connect(ui->controller_iso, &isoDriver::showRealtimeButton, ui->realTimeButton, &QWidget::setVisible);
    connect(ui->realTimeButton, &QAbstractButton::pressed, ui->controller_iso, &isoDriver::disableFileMode);


	
    connect(ui->pausedLabeL_CH1, &QAbstractButton::toggled, this, &MainWindow::paused);
    connect(ui->pausedLabel_CH2, &QAbstractButton::toggled, this, &MainWindow::paused);
    connect(ui->pause_LA, &QAbstractButton::toggled, this, &MainWindow::paused);
    connect(ui->multimeterPauseCheckBox, &QAbstractButton::toggled, this, &MainWindow::paused);

#ifndef PLATFORM_ANDROID
    connect(ui->hideCH1Box, &QAbstractButton::toggled, ui->controller_iso, &isoDriver::hideCH1);
    connect(ui->hideCH2Box, &QAbstractButton::toggled, ui->controller_iso, &isoDriver::hideCH2);

    connect(ui->actionHexDisplay, &QAction::toggled, ui->controller_iso, &isoDriver::setHexDisplay_CH1);
    connect(ui->actionHexDisplay_2, &QAction::toggled, ui->controller_iso, &isoDriver::setHexDisplay_CH2);

	ui->hideCH1Box->setVisible(false);
	ui->hideCH2Box->setVisible(false);
#endif
    ui->realTimeButton->setVisible(false);

    if ((screen()->availableGeometry().width() < 1520) || (screen()->availableGeometry().height() < 800))
    {
        qDebug() << "Low resolution detected:" << screen()->availableGeometry().width() << "x" << screen()->availableGeometry().height();
        this->setMinimumSize(1280, 700);
        this->resize(1280, 700);
    }
    else
    {
        this->setMinimumSize(1520, 800);
        this->resize(1520, 800);
    }

#ifndef PLATFORM_ANDROID
    connect(ui->offsetSpinBox_CH1, qOverload<double>(&QDoubleSpinBox::valueChanged), ui->controller_iso, &isoDriver::offsetChanged_CH1);
    connect(ui->offsetSpinBox_CH2, qOverload<double>(&QDoubleSpinBox::valueChanged), ui->controller_iso, &isoDriver::offsetChanged_CH2);
    connect(ui->attenuationComboBox_CH1, qOverload<int>(&QComboBox::currentIndexChanged), ui->controller_iso, &isoDriver::attenuationChanged_CH1);
    connect(ui->attenuationComboBox_CH2, qOverload<int>(&QComboBox::currentIndexChanged), ui->controller_iso, &isoDriver::attenuationChanged_CH2);
#endif
    connect(ui->controller_iso, &isoDriver::enableCursorGroup, this, &MainWindow::cursorGroupEnabled);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialisePlot()
{
    QCPCurve *xyCurve = new QCPCurve(ui->scopeAxes->xAxis, ui->scopeAxes->yAxis);
    xyCurve->setPen(QPen(Qt::yellow, 1));

#if QCP_VER == 1
    ui->scopeAxes->addPlottable(xyCurve);
#endif

    ui->scopeAxes->addGraph();
    ui->scopeAxes->addGraph();
    ui->scopeAxes->addGraph();
    ui->scopeAxes->addGraph();
    ui->scopeAxes->addGraph();
    ui->scopeAxes->addGraph();

    textLabel = new QCPItemText(ui->scopeAxes);
#if QCP_VER == 1
    ui->scopeAxes->addItem(textLabel);
#endif

    textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignRight);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.99, 0); // place position at center/top of axis rect
    textLabel->setText("Cursor Label Here");
    textLabel->setFont(QFont("Courier New", 16));
    textLabel->setColor(Qt::white);
    textLabel->setPen(QPen(Qt::white));
    textLabel->setBrush(QBrush(Qt::black));

    textLabel->setVisible(false);
    ui->controller_iso->cursorTextPtr = textLabel;

#if QCP_VER == 1
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

    QPen dashPen(Qt::white, 2);
    dashPen.setStyle(Qt::DashLine);

    ui->scopeAxes->graph(0)->setPen(QPen(Qt::yellow, 1));
    ui->scopeAxes->graph(1)->setPen(QPen(Qt::cyan, 1));
    ui->scopeAxes->graph(2)->setPen(QPen(Qt::white, 2));
    ui->scopeAxes->graph(3)->setPen(dashPen);
    ui->scopeAxes->graph(4)->setPen(QPen(Qt::white, 2));
    ui->scopeAxes->graph(5)->setPen(dashPen);


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
    Q_UNUSED(event);

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
#ifndef PLATFORM_ANDROID
    serialProtocolGroup->addAction(ui->actionSerial);
    serialProtocolGroup->addAction(ui->actionI2C);
#endif


    connect(ui->actionAutoV, &QAction::toggled, ui->controller_iso, &isoDriver::setAutoMultimeterV);
    connect(ui->actionV, &QAction::toggled, ui->controller_iso, &isoDriver::setForceVolts);
    connect(ui->actionMV, &QAction::toggled, ui->controller_iso, &isoDriver::setForceMillivolts);
    connect(ui->actionAutoI, &QAction::toggled, ui->controller_iso, &isoDriver::setAutoMultimeterI);
    connect(ui->actionA, &QAction::toggled, ui->controller_iso, &isoDriver::setForceAmps);
    connect(ui->actionMA, &QAction::toggled, ui->controller_iso, &isoDriver::setForceMilliamps);
    connect(ui->actionAutoR, &QAction::toggled, ui->controller_iso, &isoDriver::setAutoMultimeterR);
    connect(ui->actionOhm, &QAction::toggled, ui->controller_iso, &isoDriver::setForceOhms);
    connect(ui->actionKOhm, &QAction::toggled, ui->controller_iso, &isoDriver::setForceKiloOhms);
    connect(ui->actionAutoC, &QAction::toggled, ui->controller_iso, &isoDriver::setAutoMultimeterC);
    connect(ui->actionNF, &QAction::toggled, ui->controller_iso, &isoDriver::setForceNFarads);
    connect(ui->action_F, &QAction::toggled, ui->controller_iso, &isoDriver::setForceUFarads);


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
#ifndef PLATFORM_ANDROID
    uartParityGroup_CH1->addAction(ui->actionEven);
    uartParityGroup_CH1->addAction(ui->actionOdd);
#endif
    ui->actionNone->setChecked(true);

    uartParityGroup_CH2 = new QActionGroup(this);
    uartParityGroup_CH2->addAction(ui->actionNone_2);
#ifndef PLATFORM_ANDROID
    uartParityGroup_CH2->addAction(ui->actionEven_2);
    uartParityGroup_CH2->addAction(ui->actionOdd_2);
    ui->actionNone_2->setChecked(true);
#endif

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
    ui->controller_iso->setAutoGain(false);
}

void MainWindow::on_actionGain1_triggered()
{
    ui->controller_iso->driver->setGain(1);
    ui->controller_iso->setAutoGain(false);
}

void MainWindow::on_actionGain2_triggered()
{
    ui->controller_iso->driver->setGain(2);
    ui->controller_iso->setAutoGain(false);
}

void MainWindow::on_actionGain4_triggered()
{
    ui->controller_iso->driver->setGain(4);
    ui->controller_iso->setAutoGain(false);
}

void MainWindow::on_actionGain8_triggered()
{
    ui->controller_iso->driver->setGain(8);
    ui->controller_iso->setAutoGain(false);
}

void MainWindow::on_actionGain16_triggered()
{
    ui->controller_iso->driver->setGain(16);
    ui->controller_iso->setAutoGain(false);
}

void MainWindow::on_actionGain32_triggered()
{
    ui->controller_iso->driver->setGain(32);
    ui->controller_iso->setAutoGain(false);
}

void MainWindow::on_actionGain64_triggered()
{
    ui->controller_iso->driver->setGain(64);
    ui->controller_iso->setAutoGain(false);
}
void MainWindow::on_actionGainAuto_triggered()
{
    ui->controller_iso->setAutoGain(true);
}

void MainWindow::on_actionCursor_Stats_triggered(bool checked)
{
    ui->controller_iso->cursorStatsEnabled = checked;
}

void MainWindow::connectDisplaySignals(){
    connect(ui->actionMax, &QAction::toggled, ui->voltageInfoMaxLabel_CH1, &QWidget::setVisible);
    connect(ui->actionMax, &QAction::toggled, ui->voltageInfoMaxDisplay_CH1, &QWidget::setVisible);

    connect(ui->actionMin, &QAction::toggled, ui->voltageInfoMinLabel_CH1, &QWidget::setVisible);
    connect(ui->actionMin, &QAction::toggled, ui->voltageInfoMinDisplay_CH1, &QWidget::setVisible);

    connect(ui->actionMean, &QAction::toggled, ui->VoltageInfoMeanLabel_CH1, &QWidget::setVisible);
    connect(ui->actionMean, &QAction::toggled, ui->voltageInfoMeanDisplay_CH1, &QWidget::setVisible);

    connect(ui->actionRMS, &QAction::toggled, ui->voltageInfoRmsLabel_CH1, &QWidget::setVisible);
    connect(ui->actionRMS, &QAction::toggled, ui->voltageInfoRmsDisplay_CH1, &QWidget::setVisible);

    ui->voltageInfoMaxLabel_CH1->setVisible(false);
    ui->voltageInfoMaxDisplay_CH1->setVisible(false);
    ui->voltageInfoMinLabel_CH1->setVisible(false);
    ui->voltageInfoMinDisplay_CH1->setVisible(false);
    ui->VoltageInfoMeanLabel_CH1->setVisible(false);
    ui->voltageInfoMeanDisplay_CH1->setVisible(false);
    ui->voltageInfoRmsLabel_CH1->setVisible(false);
    ui->voltageInfoRmsDisplay_CH1->setVisible(false);

    connect(ui->actionMax_2, &QAction::toggled, ui->voltageInfoMaxLabel_CH2, &QWidget::setVisible);
    connect(ui->actionMax_2, &QAction::toggled, ui->voltageInfoMaxDisplay_CH2, &QWidget::setVisible);

    connect(ui->actionMin_2, &QAction::toggled, ui->voltageInfoMinLabel_CH2, &QWidget::setVisible);
    connect(ui->actionMin_2, &QAction::toggled, ui->voltageInfoMinDisplay_CH2, &QWidget::setVisible);

    connect(ui->actionMean_2, &QAction::toggled, ui->VoltageInfoMeanLabel_CH2, &QWidget::setVisible);
    connect(ui->actionMean_2, &QAction::toggled, ui->voltageInfoMeanDisplay_CH2, &QWidget::setVisible);

    connect(ui->actionRMS_2, &QAction::toggled, ui->voltageInfoRmsLabel_CH2, &QWidget::setVisible);
    connect(ui->actionRMS_2, &QAction::toggled, ui->voltageInfoRmsDisplay_CH2, &QWidget::setVisible);

    ui->voltageInfoMaxLabel_CH2->setVisible(false);
    ui->voltageInfoMaxDisplay_CH2->setVisible(false);
    ui->voltageInfoMinLabel_CH2->setVisible(false);
    ui->voltageInfoMinDisplay_CH2->setVisible(false);
    ui->VoltageInfoMeanLabel_CH2->setVisible(false);
    ui->voltageInfoMeanDisplay_CH2->setVisible(false);
    ui->voltageInfoRmsLabel_CH2->setVisible(false);
    ui->voltageInfoRmsDisplay_CH2->setVisible(false);
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


    connect(shortcut_cycleBaudRate_CH1, &QShortcut::activated, this, &MainWindow::cycleBaudRate_CH1);
    connect(shortcut_cycleBaudRateBackwards_CH1, &QShortcut::activated, this, &MainWindow::cycleBaudRateBackwards_CH1);
    connect(shortcut_cycleBaudRate_CH2, &QShortcut::activated, this, &MainWindow::cycleBaudRate_CH2);
    connect(shortcut_cycleBaudRateBackwards_CH2, &QShortcut::activated, this, &MainWindow::cycleBaudRateBackwards_CH2);
    connect(shortcut_snapshot_CH1, &QShortcut::activated, this, &MainWindow::on_actionSnapshot_CH1_triggered);
    connect(shortcut_snapshot_CH2, &QShortcut::activated, this, &MainWindow::on_actionSnapshot_CH2_triggered);

    connect(shortcut_w, &QShortcut::activated, this, &MainWindow::arrowUpTriggered);
    connect(shortcut_s, &QShortcut::activated, this, &MainWindow::arrowDownTriggered);
    connect(shortcut_ctrlW, &QShortcut::activated, this, &MainWindow::ctrlArrowUpTriggered);
    connect(shortcut_ctrlS, &QShortcut::activated, this, &MainWindow::ctrlArrowDownTriggered);

    connect(shortcut_a, &QShortcut::activated, this, &MainWindow::cycleDelayLeft);
    connect(shortcut_d, &QShortcut::activated, this, &MainWindow::cycleDelayRight);

    connect(shortcut_ArrowLeft, &QShortcut::activated, this, &MainWindow::cycleDelayLeft);
    connect(shortcut_ArrowRight, &QShortcut::activated, this, &MainWindow::cycleDelayRight);
    connect(shortcut_CtrlArrowLeft, &QShortcut::activated, this, &MainWindow::cycleDelayLeft_large);
    connect(shortcut_CtrlArrowRight, &QShortcut::activated, this, &MainWindow::cycleDelayRight_large);

    connect(shortcut_snapScopeToCursors, &QShortcut::activated, this, &MainWindow::on_actionSnap_to_Cursors_triggered);
    connect(shortcut_manualRange, &QShortcut::activated, this, &MainWindow::on_actionEnter_Manually_triggered);

    connect(shortcut_Debug, &QShortcut::activated, this, &MainWindow::enableLabradorDebugging);
    connect(shortcut_Esc, &QShortcut::activated, this, &MainWindow::reinitUsb);

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

// In Qt 6 they have gone insane
static QWheelEvent createWheelEvent(const bool negative, const QPoint &point, const Qt::KeyboardModifier modifier = Qt::NoModifier)
{
    return QWheelEvent(point, // pos
                           QCursor::pos(), // globalpos
                           QPoint(negative ? -0 : 0, 0), // pixelDelta
                           QPoint(negative ? -120 : 120, 0), // angleDelta
                           Qt::NoButton, // buttons
                           modifier, // keyboard modifiers
                           Qt::NoScrollPhase, // scroll phase
                           false // inverted
        );
}

void MainWindow::arrowUpTriggered(){
    qDebug() << "Boy UP!";
    if(!(ui->scopeAxes->underMouse())) return;

    QPoint point = ui->scopeAxes->mapFromGlobal(QCursor::pos());

    QWheelEvent wheelEmu = createWheelEvent(false, point);
    qApp->sendEvent(ui->scopeAxes, &wheelEmu);
}

void MainWindow::arrowDownTriggered(){
    qDebug() << "Boy DOWN!";
    if(!(ui->scopeAxes->underMouse())){
        qDebug() << "Not under mouse";
        return;
    }

    QPoint point = ui->scopeAxes->mapFromGlobal(QCursor::pos());
    QWheelEvent wheelEmu = createWheelEvent(true, point);
    qApp->sendEvent(ui->scopeAxes, &wheelEmu);
}

void MainWindow::ctrlArrowUpTriggered(){
    qDebug() << "Boy (ctrl) UP!";
    if(!(ui->scopeAxes->underMouse())) return;

    QPoint point = ui->scopeAxes->mapFromGlobal(QCursor::pos());
    QWheelEvent wheelEmu = createWheelEvent(false, point, Qt::ControlModifier);
    qApp->sendEvent(ui->scopeAxes, &wheelEmu);
}

void MainWindow::ctrlArrowDownTriggered(){
    qDebug() << "Boy (ctrl) DOWN!";
    if(!(ui->scopeAxes->underMouse())) return;

    QPoint point = ui->scopeAxes->mapFromGlobal(QCursor::pos());
    QWheelEvent wheelEmu = createWheelEvent(true, point, Qt::ControlModifier);
    qApp->sendEvent(ui->scopeAxes, &wheelEmu);
}

void MainWindow::cycleDelayRight(){
    qDebug() << "RIGHT";
    ui->controller_iso->display.delay -= ui->controller_iso->display.window/10;
    if(ui->controller_iso->display.delay < 0) ui->controller_iso->display.delay = 0;
    emit ui->controller_iso->delayUpdated(ui->controller_iso->display.delay);
}

void MainWindow::cycleDelayLeft(){
    qDebug() << "LEFT";
    double mws = ui->controller_iso->fileModeEnabled ? ui->controller_iso->daq_maxWindowSize : ((double)MAX_WINDOW_SIZE);
    ui->controller_iso->display.delay += ui->controller_iso->display.window/10;
    if(ui->controller_iso->display.delay > (mws - ui->controller_iso->display.window)) ui->controller_iso->display.delay = (mws - ui->controller_iso->display.window);
    emit ui->controller_iso->delayUpdated(ui->controller_iso->display.delay);
}

void MainWindow::cycleDelayRight_large(){
    qDebug() << "RIGHT";
    ui->controller_iso->display.delay -= ui->controller_iso->display.window/2;
    if(ui->controller_iso->display.delay < 0) ui->controller_iso->display.delay = 0;
    emit ui->controller_iso->delayUpdated(ui->controller_iso->display.delay);
}

void MainWindow::cycleDelayLeft_large(){
    qDebug() << "LEFT";
    double mws = ui->controller_iso->fileModeEnabled ? ui->controller_iso->daq_maxWindowSize : ((double)MAX_WINDOW_SIZE);
    ui->controller_iso->display.delay += ui->controller_iso->display.window/2;
    if(ui->controller_iso->display.delay > (mws - ui->controller_iso->display.window)) ui->controller_iso->display.delay = (mws - ui->controller_iso->display.window);
    emit ui->controller_iso->delayUpdated(ui->controller_iso->display.delay);
}

void MainWindow::enableLabradorDebugging(){
    qDebug() << "DEBUG MODE ACTIVE";

    ui->debugButton1->setVisible(true);
    ui->debugButton2->setVisible(true);
    ui->debugButton3->setVisible(true);
#ifndef PLATFORM_ANDROID
    ui->kickstartIsoButton->setVisible(true);
#endif
    ui->debugConsole->setVisible(true);

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

    yTop = std::max(ui->controller_iso->display.y1, ui->controller_iso->display.y0);
    yBot = std::min(ui->controller_iso->display.y1, ui->controller_iso->display.y0);

    xRight = std::max(ui->controller_iso->display.x1, ui->controller_iso->display.x0);
    xLeft = std::min(ui->controller_iso->display.x1, ui->controller_iso->display.x0);

    if((yBot-yTop) != 0){
        ui->controller_iso->display.topRange = yTop;
        ui->controller_iso->display.botRange = yBot;
    }

    if((xLeft - xRight) != 0){
        ui->controller_iso->display.delay = - xRight;
        ui->controller_iso->display.window = xRight - xLeft;
    }
}

void MainWindow::on_actionEnter_Manually_triggered()
{
    ui->controller_iso->display.delay = 0;
    scopeRangeEnterDialog dialog(this, ui->controller_iso->display.topRange, ui->controller_iso->display.botRange, ui->controller_iso->display.window, ui->controller_iso->display.delay);
    dialog.setModal(true);
    connect(&dialog, &scopeRangeEnterDialog::yTopUpdated, ui->controller_iso, &isoDriver::setTopRange);
    connect(&dialog, &scopeRangeEnterDialog::yBotUpdated, ui->controller_iso, &isoDriver::setBotRange);
    connect(&dialog, &scopeRangeEnterDialog::windowUpdated, ui->controller_iso, &isoDriver::setTimeWindow);
    connect(&dialog, &scopeRangeEnterDialog::delayUpdated, ui->controller_iso, &isoDriver::setDelay);
    dialog.exec();
}

void MainWindow::helloWorld(){
    qDebug() << "Hello World!";
}

#define QSETTINGS_DEFAULT_RETURN 42069
void MainWindow::readSettingsFile(){
    settings = new QSettings(this);
    int connectionType = settings->value("ConnectionType", QSETTINGS_DEFAULT_RETURN).toInt();
    double calibrate_vref_ch1 = settings->value("CalibrateVrefCH1", 1.65).toDouble();
    double calibrate_vref_ch2 = settings->value("CalibrateVrefCH2", 1.65).toDouble();
    double calibrate_gain_ch1 = settings->value("CalibrateGainCH1", R4/(R3+R4)).toDouble();
    double calibrate_gain_ch2 = settings->value("CalibrateGainCH2", R4/(R3+R4)).toDouble();
    psu_voltage_calibration_offset = settings->value("CalibratePsu", 0).toDouble();
#ifndef PLATFORM_ANDROID
    if (settings->value("ShowRangeDialog").toBool())
    {
        qDebug() << "ShowRangeDialog setting true";
        ui->actionShow_Range_Dialog_on_Main_Page->setChecked(true);
        on_actionShow_Range_Dialog_on_Main_Page_triggered(true);
    }
#endif

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
    ui->controller_iso->setDriver(new _PLATFORM_DEPENDENT_USB_OBJECT(this));

    //Reconnect the other objects.
    //ui->controller_iso->driver->setBufferPtr(ui->bufferDisplay);
    connect(ui->debugButton1, &QAbstractButton::clicked, ui->controller_iso->driver.data(), &genericUsbDriver::avrDebug);
    connect(ui->debugButton3, &QAbstractButton::clicked, ui->controller_iso->driver.data(), &genericUsbDriver::bootloaderJump);
    connect(ui->psuSlider, &espoSlider::voltageChanged, ui->controller_iso->driver.data(), &genericUsbDriver::setPsu);
    connect(ui->controller_iso, &isoDriver::setGain, ui->controller_iso->driver.data(), &genericUsbDriver::setGain);
    connect(ui->controller_fg, &functionGenControl::functionGenToUpdate, ui->controller_iso->driver, &genericUsbDriver::setFunctionGen);
    connect(ui->bufferDisplay, &bufferControl::modeChange, ui->controller_iso->driver.data(), &genericUsbDriver::setDeviceMode);
	connect(ui->bufferDisplay, &bufferControl::modeChange, this, [this](){
		// Force a trigger refresh
		ui->controller_iso->setTriggerLevel(ui->triggerLevelValue->value());	
	});
    connect(ui->bufferDisplay, &bufferControl::updateDig, ui->controller_iso->driver.data(), &genericUsbDriver::newDig);

    //Set the settings again!
    connect(ui->controller_iso->driver.data(), &genericUsbDriver::gainBuffers, ui->controller_iso, &isoDriver::gainBuffers);
    connect(ui->controller_iso->driver.data(), &genericUsbDriver::disableWindow, this, &QWidget::setEnabled);
    connect(ui->controller_iso->driver.data(), &genericUsbDriver::sendClearBuffer, ui->controller_iso, &isoDriver::clearChannelBuffers);
    //connect(ui->controller_iso->driver, SIGNAL(startIsoTimer()), ui->controller_iso, SLOT(startTimer()));
    connect(ui->controller_iso->driver.data(), &genericUsbDriver::setVisible_CH2, ui->controller_iso, &isoDriver::setVisible_CH2);
    //connect(ui->controller_iso->driver, SIGNAL(enableMMTimer()), ui->controller_iso, SLOT(enableMM()));
    connect(ui->controller_iso->driver.data(), &genericUsbDriver::checkXY, ui->xyDisplayLabel, &QAbstractButton::setChecked);
    connect(ui->controller_iso->driver.data(), &genericUsbDriver::disableWindow, ui->deviceConnected, &deviceConnectedDisplay::connectedStatusChanged);
    connect(ui->controller_iso->driver.data(), &genericUsbDriver::upTick, ui->controller_iso, &isoDriver::timerTick);
    connect(ui->controller_iso->driver.data(), &genericUsbDriver::killMe, this, &MainWindow::reinitUsb);
    connect(ui->controller_iso->driver.data(), &genericUsbDriver::connectedStatus, ui->deviceConnected, &deviceConnectedDisplay::connectedStatusChanged);
    connect(ui->controller_iso->driver.data(), &genericUsbDriver::signalFirmwareFlash, ui->deviceConnected, &deviceConnectedDisplay::flashingFirmware);
    connect(ui->controller_iso->driver.data(), &genericUsbDriver::initialConnectComplete, this, &MainWindow::resetUsbState);
    ui->controller_iso->driver->setGain(reinitScopeGain);
    ui->controller_iso->driver->psu_offset = psu_voltage_calibration_offset;

    readSettingsFile();

    ui->controller_iso->driver->calibrateOnConnect = (dt_userWantsToCalibrate == 16384); //Yes/No are 16384/65536 for some reason.  I think 0/1 are reserved for OK/Cancel.
    connect(ui->controller_iso->driver.data(), &genericUsbDriver::calibrateMe, this, &MainWindow::on_actionCalibrate_triggered);
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

    ui->controller_iso->clearBuffers(isoDriver::Channel3751 | isoDriver::Channel3752 | isoDriver::Channel750);
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
        ui->controller_iso->onWheelEvent(wheelEmu);

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
    if(ui->controller_iso->driver->deviceMode != DeviceCH1DigitalCH2Digital){
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

    ui->controller_iso->clearBuffers(isoDriver::Channel3751 | isoDriver::Channel3752 | isoDriver::Channel750);
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

    ui->controller_iso->clearBuffers(isoDriver::Channel3751 | isoDriver::Channel3752 | isoDriver::Channel750);
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

void MainWindow::on_actionExportImage_triggered()
{
    qDebug() << "on_actionExportImage_triggered()";

    QFileDialog dialog;

    dialog.setDefaultSuffix("pdf");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setDirectory(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("PDF files (*.pdf);;JPEG files (*.jpg);;PNG files (*.png);;BMP files (*.bmp)");

    int retVal = dialog.exec();

    if(!retVal){
        return; //User did not select a file!
    }

    QStringList tempList = dialog.selectedFiles();
    qDebug() << tempList.first();

    // Avoiding an if () cascade
    switch (dialog.nameFilters().indexOf( dialog.selectedNameFilter() ) )
    {
        case 0:
            ui->scopeAxes->savePdf(tempList.first());
            break;
        case 1:
            ui->scopeAxes->saveJpg(tempList.first());
            break;
        case 2:
            ui->scopeAxes->savePng(tempList.first());
            break;
        case 3:
            ui->scopeAxes->saveBmp(tempList.first());
            break;
        default:
            qDebug() << "Wrong file type for exporting image to";
    }
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
        if(ui->controller_iso->driver->deviceMode != DeviceCH1Analog750) {
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
    if(ui->controller_iso->driver->deviceMode != DeviceCH1Analog750) {
        output375_CH1 = new QFile(fileName);
        ui->controller_iso->internalBuffer375_CH1->enableFileIO(output375_CH1, daq_num_to_average, daq_max_file_size);
    } else {
        output750 = new QFile(fileName);
        ui->controller_iso->internalBuffer750->enableFileIO(output750, daq_num_to_average, daq_max_file_size);
    }
    ui->bufferDisplay->scopeDsrDisableOverride = true;
    ui->bufferDisplay->poke();
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
    output375_CH2 = new QFile(fileName);
    ui->controller_iso->internalBuffer375_CH2->enableFileIO(output375_CH2, daq_num_to_average, daq_max_file_size);

    if((checked) && (ui->controller_iso->driver->deviceMode != DeviceCH1DigitalCH2Digital))
        QMessageBox::warning(nullptr, "Warning", "CH2 is disabled.  The DAQ will NOT RECORD any data from from CH2 until it has been enabled!");
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
    connect(&df, &daqForm::updatedAveraging, this, &MainWindow::daq_updatedAveraging);
    connect(&df, &daqForm::updatedMaxFileSize, this, &MainWindow::daq_updatedMaxFileSize);
    connect(&df, &daqForm::saveButtonPressed, this, &MainWindow::daq_saveButtonPressed);

    df.exec();
}

void MainWindow::fileLimitReached_CH1(void){
    ui->actionRecord_CH1->setChecked(false);

    QMessageBox recordingStoppedMessageBox;
    char recordingStoppedMessage[256];
    sprintf(recordingStoppedMessage, "Maximum file size limit of %lluMB reached.  Data Acquisition Stopped.", daq_max_file_size/1000000);
    recordingStoppedMessageBox.setText(recordingStoppedMessage);
    recordingStoppedMessageBox.exec();
}

void MainWindow::fileLimitReached_CH2(void){
    ui->actionRecord_CH2->setChecked(false);

    QMessageBox recordingStoppedMessageBox;
    char recordingStoppedMessage[256];
    sprintf(recordingStoppedMessage, "Maximum file size limit of %lluMB reached.  Data Acquisition Stopped.", daq_max_file_size/1000000);
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
    QMessageBox aboutDialog(this);
    aboutDialog.setWindowTitle("About EspoTek Labrador");
    aboutDialog.setTextFormat(Qt::RichText);
    aboutDialog.setText(kAboutString);
    aboutDialog.exec();
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

    if (!ui->controller_iso->driver->connected) {
        calibrationMessages->setStandardButtons(QMessageBox::Ok);
        calibrationMessages->setText("You need to connect the board before calibrating it!");
        calibrationMessages->exec();
        return;
    }

    //Abort if Scope is uncalibrated
    if ((ui->controller_iso->ch1_ref == 1.65) && (ui->controller_iso->ch2_ref == 1.65) && (ui->controller_iso->frontendGain_CH1 ==  R4/(R3+R4)) && (ui->controller_iso->frontendGain_CH2 == R4/(R3+R4)))\
    {
        calibrationMessages->setStandardButtons(QMessageBox::Ok);
        calibrationMessages->setText("You need to calibrate the oscilloscope before the power supply!");
        calibrationMessages->exec();
        return;
    }

    calibrationMessages->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    calibrationMessages->setText("Power Supply calibration requires me to control your power supply temporarily.  \n\nTO PREVENT BLUE SMOKE DAMAGE, DISCONNECT ANY CIRCUIT ATTACHED TO YOUR POWER SUPPLY NOW.");
    if (calibrationMessages->exec() == QMessageBox::Cancel) {
        return;
    }

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
    emit ui->controller_iso->setGain(4);

    //Remove the offset before setting it again; don't want them to stack!
    ui->controller_iso->driver->psu_offset = 0;

    qDebug() << "PSU Calibration routine beginning!";
    calibrationMessages->setStandardButtons(QMessageBox::Ok);
    calibrationMessages->setText("Please connect your Labrador's Oscilloscope CH1 (DC) pin to the Power Supply Output (positive) then press OK to continue.");
    calibrationMessages->exec();

    ui->controller_iso->driver->setPsu(5);
    ui->controller_iso->clearBuffers(isoDriver::Channel3751 | isoDriver::Channel3752 | isoDriver::Channel750);
    QTimer::singleShot(1800, this, SLOT(calibrate_psu_stage2()));
}

void MainWindow::calibrate_psu_stage2()
{
    PSU5 = ui->controller_iso->meanVoltageLast(1, 1, 128);
    qDebug() << "PSU5 =" << PSU5;
    if((PSU5 > 6) | (PSU5 < 4) ){
        ui->controller_iso->driver->setPsu(4.5);
        ui->psuSlider->setValue(0);
        ui->controller_iso->clearBuffers(isoDriver::Channel3751 | isoDriver::Channel3752 | isoDriver::Channel750);
        ui->controller_iso->setAutoGain(true);
        ui->controller_iso->autoGain();
        calibrationMessages->setText("Calibration has been abandoned due to out-of-range values.  The oscilloscope should show approximately 5V.  Please check all wires on your Labrador board and try again.");
        calibrationMessages->exec();
        return;
    }
    emit ui->controller_iso->setGain(1);
    ui->controller_iso->driver->setPsu(10);
    ui->controller_iso->clearBuffers(isoDriver::Channel3751 | isoDriver::Channel3752 | isoDriver::Channel750);
    QTimer::singleShot(1800, this, SLOT(calibrate_psu_stage3()));
}

void MainWindow::calibrate_psu_stage3()
{
    PSU10 = ui->controller_iso->meanVoltageLast(1, 1, 128);
    qDebug() << "PSU10 =" << PSU10;
    ui->controller_iso->driver->setPsu(4.5);
    ui->psuSlider->setValue(0);
    ui->controller_iso->clearBuffers(isoDriver::Channel3751 | isoDriver::Channel3752 | isoDriver::Channel750);
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
    Q_UNUSED(checked);
    ui->controller_iso->setSerialType(0);
}

void MainWindow::on_actionI2C_triggered(bool checked)
{
    Q_UNUSED(checked);
    ui->controller_iso->setSerialType(1);
}

void MainWindow::on_actionShow_Range_Dialog_on_Main_Page_triggered(bool checked)
{
#ifndef PLATFORM_ANDROID
    if (scopeRangeSwitch == nullptr)
    {
        scopeRangeSwitch = new scopeRangeEnterDialog(nullptr, false, ui->controller_iso->display.topRange, ui->controller_iso->display.botRange, ui->controller_iso->display.window, ui->controller_iso->display.delay);
        scopeRangeSwitch->setWindowFlags(Qt::Widget);
        ui->verticalLayout_5->insertWidget(2, scopeRangeSwitch);
        connect(scopeRangeSwitch, &scopeRangeEnterDialog::yTopUpdated, ui->controller_iso, &isoDriver::setTopRange);
        connect(scopeRangeSwitch, &scopeRangeEnterDialog::yBotUpdated, ui->controller_iso, &isoDriver::setBotRange);
        connect(scopeRangeSwitch, &scopeRangeEnterDialog::windowUpdated, ui->controller_iso, &isoDriver::setTimeWindow);
        connect(scopeRangeSwitch, &scopeRangeEnterDialog::delayUpdated, ui->controller_iso, &isoDriver::setDelay);
        connect(scopeRangeSwitch, &scopeRangeEnterDialog::autoClicked, this, &MainWindow::on_setAutoScopeRange);

        connect(ui->controller_iso, &isoDriver::topRangeUpdated, scopeRangeSwitch, &scopeRangeEnterDialog::yTopChanged);
        connect(ui->controller_iso, &isoDriver::botRangeUpdated, scopeRangeSwitch, &scopeRangeEnterDialog::yBotChanged);
        connect(ui->controller_iso, &isoDriver::timeWindowUpdated, scopeRangeSwitch, &scopeRangeEnterDialog::windowChanged);
        connect(ui->controller_iso, &isoDriver::delayUpdated, scopeRangeSwitch, &scopeRangeEnterDialog::delayChanged);
    }
    qDebug() << "on_actionShow_Range_Dialog_on_Main_Page_triggered" << checked;
    settings->setValue("ShowRangeDialog", checked);
    scopeRangeSwitch->setVisible(checked);
#endif

}

void MainWindow::paused(bool enabled)
{
#ifndef PLATFORM_ANDROID
	qDebug() << "MainWindow::paused(" << enabled << ")";
	ui->hideCH1Box->setVisible(enabled);
	ui->hideCH2Box->setVisible(enabled);
	
	if (! enabled)
	{
		ui->hideCH1Box->setChecked(false);
		ui->hideCH2Box->setChecked(false);
	}
#endif
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
    if (m_pinoutDialog) { // only allow one to exist
        return;
    }
    m_pinoutDialog = new pinoutDialog;
    m_pinoutDialog->show(); // don't exec, allows
}

void MainWindow::cursorGroupEnabled(bool enabled)
{
    static bool cursorStatsEnabledState;
    static bool makeCursorsNicerState;

    if (enabled)
    {
        ui->controller_iso->cursorStatsEnabled = cursorStatsEnabledState;
        ui->makeCursorsNicer->setTurnedOn(makeCursorsNicerState);
        ui->cursorGroup->setEnabled(true);
    }
    else
    {
        cursorStatsEnabledState = ui->controller_iso->cursorStatsEnabled;
        makeCursorsNicerState = ui->makeCursorsNicer->turnedOn();
        ui->controller_iso->cursorStatsEnabled = false;
        ui->makeCursorsNicer->setTurnedOn(false);
        ui->cursorGroup->setEnabled(false);
    }
    
}

void MainWindow::on_actionHide_Widget_Oscilloscope_triggered(bool checked)
{
    ui->scopeGroup_CH1->setVisible(!checked);
    ui->scopeGroup_CH2->setVisible(!checked);
    ui->cursorGroup->setVisible(!checked);
    ui->triggerGroup->setVisible(!checked);
}

void MainWindow::on_actionHide_Widget_SignalGen_triggered(bool checked)
{
    ui->signalGenGroup_CH1->setVisible(!checked);
    ui->signalGenGroup_CH2->setVisible(!checked);
}

void MainWindow::on_actionHide_Widget_Multimeter_triggered(bool checked)
{
    ui->multimeterGroup->setVisible(!checked);
}

void MainWindow::on_actionHide_Widget_PowerSupply_triggered(bool checked)
{
    ui->psuGroup->setVisible(!checked);
}

void MainWindow::on_actionHide_Widget_LogicAnalyzer_triggered(bool checked)
{
    ui->busSifferGroup_CH1->setVisible(!checked);
    ui->busSnifferGroup_CH2->setVisible(!checked);
    ui->digitalOutputGroup->setVisible(!checked);
}

void MainWindow::on_setAutoScopeRange()
{
    if (ui->controller_iso->numSamples() <= 0) {
        return;
    }

    const double max = ui->controller_iso->vMax();
    const double min = ui->controller_iso->vMin();
    ui->controller_iso->setTopRange(max + max * 0.1); // 10% extra above
    ui->controller_iso->setBotRange(min - min * 0.1); // 10% extra below


}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!(ui->scopeAxes->underMouse())) {
        QMainWindow::keyPressEvent(event);
        return;
    }
    switch(event->key()) {
    case Qt::Key_Down:
        if (event->modifiers() & Qt::ControlModifier) {
            ctrlArrowDownTriggered();
        } else {
            arrowDownTriggered();
        }
        break;
    case Qt::Key_Up:
        if (event->modifiers() & Qt::ControlModifier) {
            ctrlArrowUpTriggered();
        } else {
            arrowUpTriggered();
        }
        break;
    default:
        QMainWindow::keyPressEvent(event);
        return;
    }

    event->setAccepted(true);

}
