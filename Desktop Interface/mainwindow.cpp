#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    readSettingsFile();
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
    ui->debugConsole->setVisible(0);
    ui->console1->setVisible(0);
    ui->console2->setVisible(0);
    ui->timeBaseSlider->setVisible(0);

    //ui->pausedLabel_CH2->setVisible(0);
    ui->filterLabel_CH1->setVisible(0);
    ui->filterLabel_CH2->setVisible(0);

    //Reset the device to ensure Labrador_libusbk gets handle!!
    #ifdef PLATFORM_WINDOWS
        ui->controller_iso->driver->usbSendControl(0x40, 0xa7, 0, 0, 0, NULL);
    #endif
    #ifdef PLATFORM_LINUX
        reinitUsb();
    #endif
    #ifdef PLATFORM_MAC
        //Reconnect the other objects.
        ui->controller_iso->driver->setBufferPtr(ui->bufferDisplay);
        connect(ui->pushButton, SIGNAL(clicked()), ui->controller_iso->driver, SLOT(avrDebug()));
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
    #endif
    connect(ui->controller_iso->driver, SIGNAL(killMe()), this, SLOT(reinitUsb()));
    //ui->console1->setMaximumBlockCount(MAX_CONSOLE_BLOCK_COUNT);
    //ui->console2->setMaximumBlockCount(MAX_CONSOLE_BLOCK_COUNT);
    ui->frequencyValue_CH2->setValue(912);
    ui->amplitudeValue_CH2->setValue(2);
    ui->controller_iso->doNotTouchGraph = false;
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


    QPen *dashPen = new QPen(Qt::white, 2);
    dashPen->setStyle(Qt::DashLine);

    ui->scopeAxes->graph(0)->setPen(QPen(Qt::yellow, 1));
    ui->scopeAxes->graph(1)->setPen(QPen(Qt::cyan, 1));
    ui->scopeAxes->graph(2)->setPen(QPen(Qt::white, 2));
    ui->scopeAxes->graph(3)->setPen(*(dashPen));
    ui->scopeAxes->graph(4)->setPen(QPen(Qt::white, 2));
    ui->scopeAxes->graph(5)->setPen(*(dashPen));

    ui->scopeAxes->yAxis->setAutoTickCount(9);
    ui->scopeAxes->xAxis->setAutoTickCount(9);


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
    shortcut_snapshot = new QShortcut(QKeySequence("c"), this);

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


    shortcut_Debug = new QShortcut(QKeySequence("Home"), this);


    connect(shortcut_cycleBaudRate_CH1, SIGNAL(activated()), this, SLOT(cycleBaudRate_CH1()));
    connect(shortcut_cycleBaudRateBackwards_CH1, SIGNAL(activated()), this, SLOT(cycleBaudRateBackwards_CH1()));
    connect(shortcut_cycleBaudRate_CH2, SIGNAL(activated()), this, SLOT(cycleBaudRate_CH2()));
    connect(shortcut_cycleBaudRateBackwards_CH2, SIGNAL(activated()), this, SLOT(cycleBaudRateBackwards_CH2()));
    connect(shortcut_snapshot, SIGNAL(activated()), this, SLOT(on_actionTake_Snapshot_triggered()));

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

    connect(shortcut_snapScopeToCursors, SIGNAL(activated()), this, SLOT(on_actionSnap_to_Cursors_triggered()));
    connect(shortcut_manualRange, SIGNAL(activated()), this, SLOT(on_actionEnter_Manually_triggered()));

    connect(shortcut_Debug, SIGNAL(activated()), this, SLOT(enableLabradorDebugging()));


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

void MainWindow::enableLabradorDebugging(){
    qDebug() << "DEBUG MODE ACTIVE";

    ui->debugButton1->setVisible(1);
    ui->debugButton2->setVisible(1);
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
    dialog.exec();
}

void MainWindow::helloWorld(){
    qDebug() << "Hello World!";
}

void MainWindow::readSettingsFile(){
    QFile *settings;
    settings = new QFile("settings.set");
#ifdef DEBUG_SETTINGSDOTSET
    goto createFile;
#endif
    if (!settings->open(QIODevice::ReadOnly | QIODevice::Text)){
        createFile:
        qDebug() << "settings.set does not exist!!!!  Creating...";
        settings->open(QIODevice::WriteOnly | QIODevice::Text);
        //Default init;
        settings->write("420\n");
        //Reset and continue;
        settings->close();
        settings->open(QIODevice::ReadOnly | QIODevice::Text);
    }
}

void MainWindow::on_actionRecord_triggered(bool checked)
{
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

    outputDir = new QDir();
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
}

void MainWindow::on_actionTake_Snapshot_triggered()
{
    ui->controller_iso->takeSnapshot();
}

void MainWindow::reinitUsb(void){
    int deviceMode;
    double scopeGain;
    double currentPsuVoltage;
    int digitalPinState;

    ui->controller_iso->doNotTouchGraph = true;
    ui->controller_iso->driver->saveState(&deviceMode, &scopeGain, &currentPsuVoltage, &digitalPinState);

    delete(ui->controller_iso->driver);
    ui->controller_iso->driver = new _PLATFORM_DEPENDENT_USB_OBJECT();

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
    connect(ui->controller_iso->driver, SIGNAL(killMe()), this, SLOT(reinitUsb()));

    //Setup all necessary state data;
    //ui->controller_iso->driver->setDeviceMode(deviceMode);
    ui->controller_iso->driver->setGain(scopeGain);
    //ui->controller_iso->driver->setPsu(currentPsuVoltage);
    ui->psuSlider->poke();
    //ui->controller_iso->driver->newDig(digitalPinState);
    ui->bufferDisplay->poke();
    ui->controller_iso->driver->setFunctionGen(0,ui->controller_fg);
    ui->controller_iso->driver->setFunctionGen(1,ui->controller_fg);

    ui->controller_iso->clearBuffers(1,1,1);
    ui->controller_iso->doNotTouchGraph = false;
}

