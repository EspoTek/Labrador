/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <buffercontrol.h>
#include <cursorenabler.h>
#include <deviceconnecteddisplay.h>
#include <espocombobox.h>
#include <esposlider.h>
#include <espospinbox.h>
#include <functiongencontrol.h>
#include <isodriver.h>
#include <noclosemenu.h>
#include <timedtickbox.h>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionGainAuto;
    QAction *actionGain0_5;
    QAction *actionGain1;
    QAction *actionGain2;
    QAction *actionGain4;
    QAction *actionGain8;
    QAction *actionGain16;
    QAction *actionGain32;
    QAction *actionGain64;
    QAction *actionCalibrate;
    QAction *actionCursor_Stats;
    QAction *actionMax;
    QAction *actionMin;
    QAction *actionMean;
    QAction *actionRMS;
    QAction *actionMax_2;
    QAction *actionMin_2;
    QAction *actionMean_2;
    QAction *actionRMS_2;
    QAction *actionMV;
    QAction *actionV;
    QAction *actionAutoV;
    QAction *actionAutoI;
    QAction *actionMA;
    QAction *actionA;
    QAction *action300;
    QAction *action600;
    QAction *action1200;
    QAction *action2400;
    QAction *action4800;
    QAction *action9600;
    QAction *action14400;
    QAction *action19200;
    QAction *action28800;
    QAction *action38400;
    QAction *action57600;
    QAction *action115200;
    QAction *action8;
    QAction *actionNone;
    QAction *action300_2;
    QAction *action600_2;
    QAction *action1200_2;
    QAction *action2400_2;
    QAction *action4800_2;
    QAction *action9600_2;
    QAction *action14400_2;
    QAction *action19200_2;
    QAction *action28800_2;
    QAction *action38400_2;
    QAction *action57600_2;
    QAction *action115200_2;
    QAction *action8_2;
    QAction *actionNone_2;
    QAction *actionRecord;
    QAction *actionForce_Square;
    QAction *actionAutomatically_Enable_Cursors;
    QAction *action60FPS;
    QAction *action30FPS;
    QAction *action20FPS;
    QAction *action15FPS;
    QAction *action10FPS;
    QAction *action5FPS;
    QAction *actionAuto_Lock;
    QAction *actionSnap_to_Cursors;
    QAction *actionEnter_Manually;
    QAction *actionTake_Snapshot;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QCustomPlot *scopeAxes;
    QTextEdit *debugConsole;
    QSlider *timeBaseSlider;
    QPlainTextEdit *console1;
    QPlainTextEdit *console2;
    QVBoxLayout *verticalLayout_5;
    deviceConnectedDisplay *deviceConnected;
    QHBoxLayout *horizontalLayout_13;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *scopeGroup_CH1;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *pausedLabeL_CH1;
    QCheckBox *acCoupledLabel_CH1;
    QCheckBox *filterLabel_CH1;
    QCheckBox *doubleSampleLabel;
    QGridLayout *gridLayout_2;
    QLabel *voltageInfoMaxLabel_CH1;
    QLCDNumber *voltageInfoMaxDisplay_CH1;
    QLabel *voltageInfoMinLabel_CH1;
    QLCDNumber *voltageInfoMinDisplay_CH1;
    QLabel *VoltageInfoMeanLabel_CH1;
    QLabel *voltageInfoRmsLabel_CH1;
    QLCDNumber *voltageInfoRmsDisplay_CH1;
    QLCDNumber *voltageInfoMeanDisplay_CH1;
    QGroupBox *cursorGroup;
    QVBoxLayout *verticalLayout_8;
    QCheckBox *cursorHoriCheck;
    QCheckBox *cursorVertCheck;
    cursorEnabler *makeCursorsNicer;
    QVBoxLayout *verticalLayout_10;
    QGroupBox *scopeGroup_CH2;
    QVBoxLayout *verticalLayout_11;
    QCheckBox *pausedLabel_CH2;
    QCheckBox *acCoupledLabel_CH2;
    QCheckBox *filterLabel_CH2;
    QCheckBox *xyDisplayLabel;
    QGridLayout *gridLayout_3;
    QLabel *voltageInfoMaxLabel_CH2;
    QLCDNumber *voltageInfoMaxDisplay_CH2;
    QLabel *voltageInfoMinLabel_CH2;
    QLCDNumber *voltageInfoMinDisplay_CH2;
    QLabel *VoltageInfoMeanLabel_CH2;
    QLabel *voltageInfoRmsLabel_CH2;
    QLCDNumber *voltageInfoRmsDisplay_CH2;
    QLCDNumber *voltageInfoMeanDisplay_CH2;
    QGroupBox *triggerGroup;
    QVBoxLayout *verticalLayout_14;
    QComboBox *triggerChannelSelect;
    QDoubleSpinBox *triggerLevelValue;
    QCheckBox *singleShotCheckBox;
    QSpacerItem *verticalSpacer_3;
    QLabel *cursorStatsLabel;
    QGroupBox *multimeterGroup;
    QGridLayout *gridLayout;
    QComboBox *multimeterModeSelect;
    QFormLayout *formLayout;
    QLabel *multimeterMaxLabel;
    QLabel *multimeterMinLabel;
    QLCDNumber *multimeterMinDisplay;
    QLabel *multimeterMeanLabel;
    QLCDNumber *multimeterMeanDisplay;
    QLabel *multimeterRmsLabel;
    QLCDNumber *multimeterRmsDisplay;
    QLCDNumber *multimeterMaxDisplay;
    QCheckBox *multimeterPauseCheckBox;
    QLabel *multimeterResistanceLabel;
    QLabel *multimeterModeLabel;
    espoSpinBox *multimeterResistanceSelect;
    QSpacerItem *verticalSpacer_2;
    functionGenControl *controller_fg;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *signalGenGroup_CH1;
    QVBoxLayout *verticalLayout_19;
    QLabel *waveformLabel_CH1;
    espoComboBox *waveformSelect_CH1;
    QLabel *frequencyLabel_CH1;
    espoSpinBox *frequencyValue_CH1;
    QLabel *amplitudeLabel_CH1;
    espoSpinBox *amplitudeValue_CH1;
    QLabel *dcOffsetLabel_CH1;
    espoSpinBox *dcOffsetValue_CH1;
    QGroupBox *signalGenGroup_CH2;
    QVBoxLayout *verticalLayout_21;
    QLabel *waveformLabel_CH2;
    espoComboBox *waveformSelect_CH2;
    QLabel *frequencyLabel_CH2;
    espoSpinBox *frequencyValue_CH2;
    QLabel *amplitudeLabel_CH2;
    espoSpinBox *amplitudeValue_CH2;
    QLabel *dcOffsetLabel_CH2;
    espoSpinBox *dcOffsetValue_CH2;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *verticalSpacer_4;
    isoDriver *controller_iso;
    QVBoxLayout *verticalLayout_18;
    QGroupBox *psuGroup;
    QVBoxLayout *verticalLayout_15;
    espoSlider *psuSlider;
    timedTickBox *lockPsuCheckBox;
    QLCDNumber *psuDisplay;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *busSifferGroup_CH1;
    QVBoxLayout *verticalLayout_7;
    QCheckBox *pause_LA;
    QGroupBox *serialDecodingCheck_CH1;
    QVBoxLayout *verticalLayout_6;
    QComboBox *serialDecodingModeSelect_CH1;
    QGroupBox *busSnifferGroup_CH2;
    QVBoxLayout *verticalLayout_16;
    QGroupBox *serialDecodingCheck_CH2;
    QVBoxLayout *verticalLayout_17;
    QComboBox *serialDecodingModeSelect_CH2;
    QGroupBox *digitalOutputGroup;
    QGridLayout *gridLayout_4;
    QCheckBox *digitalOutCheckbox_CH3;
    QCheckBox *digitalOutCheckbox_CH2;
    QCheckBox *digitalOutCheckbox_CH1;
    QCheckBox *digitalOutCheckbox_CH4;
    QPushButton *debugButton1;
    QPushButton *debugButton2;
    bufferControl *bufferDisplay;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOscilloscope_2;
    QMenu *menuGain_2;
    noCloseMenu *menuCH1_Stats;
    noCloseMenu *menuCH2_Stats;
    QMenu *menuFrame_rate;
    QMenu *menuRange;
    QMenu *menuMultimeter_2;
    QMenu *menuV_2;
    QMenu *menuI_2;
    QMenu *menuBus_Sniffer;
    QMenu *menuUART_1;
    QMenu *menuBaud_Rate;
    QMenu *menuType_Here_2;
    QMenu *menuParity_Bit;
    QMenu *menuData_Bits;
    QMenu *menuUART_2;
    QMenu *menuBaud_Rate_2;
    QMenu *menuData_Bits_2;
    QMenu *menuParity_Bit_2;
    QMenu *menuPower_Supply;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1136, 768);
        MainWindow->setMinimumSize(QSize(1024, 768));
        actionGainAuto = new QAction(MainWindow);
        actionGainAuto->setObjectName(QStringLiteral("actionGainAuto"));
        actionGainAuto->setCheckable(true);
        actionGain0_5 = new QAction(MainWindow);
        actionGain0_5->setObjectName(QStringLiteral("actionGain0_5"));
        actionGain0_5->setCheckable(true);
        actionGain1 = new QAction(MainWindow);
        actionGain1->setObjectName(QStringLiteral("actionGain1"));
        actionGain1->setCheckable(true);
        actionGain2 = new QAction(MainWindow);
        actionGain2->setObjectName(QStringLiteral("actionGain2"));
        actionGain2->setCheckable(true);
        actionGain4 = new QAction(MainWindow);
        actionGain4->setObjectName(QStringLiteral("actionGain4"));
        actionGain4->setCheckable(true);
        actionGain8 = new QAction(MainWindow);
        actionGain8->setObjectName(QStringLiteral("actionGain8"));
        actionGain8->setCheckable(true);
        actionGain16 = new QAction(MainWindow);
        actionGain16->setObjectName(QStringLiteral("actionGain16"));
        actionGain16->setCheckable(true);
        actionGain32 = new QAction(MainWindow);
        actionGain32->setObjectName(QStringLiteral("actionGain32"));
        actionGain32->setCheckable(true);
        actionGain64 = new QAction(MainWindow);
        actionGain64->setObjectName(QStringLiteral("actionGain64"));
        actionGain64->setCheckable(true);
        actionGain64->setMenuRole(QAction::TextHeuristicRole);
        actionCalibrate = new QAction(MainWindow);
        actionCalibrate->setObjectName(QStringLiteral("actionCalibrate"));
        actionCursor_Stats = new QAction(MainWindow);
        actionCursor_Stats->setObjectName(QStringLiteral("actionCursor_Stats"));
        actionCursor_Stats->setCheckable(true);
        actionCursor_Stats->setChecked(true);
        actionMax = new QAction(MainWindow);
        actionMax->setObjectName(QStringLiteral("actionMax"));
        actionMax->setCheckable(true);
        actionMin = new QAction(MainWindow);
        actionMin->setObjectName(QStringLiteral("actionMin"));
        actionMin->setCheckable(true);
        actionMean = new QAction(MainWindow);
        actionMean->setObjectName(QStringLiteral("actionMean"));
        actionMean->setCheckable(true);
        actionRMS = new QAction(MainWindow);
        actionRMS->setObjectName(QStringLiteral("actionRMS"));
        actionRMS->setCheckable(true);
        actionMax_2 = new QAction(MainWindow);
        actionMax_2->setObjectName(QStringLiteral("actionMax_2"));
        actionMax_2->setCheckable(true);
        actionMin_2 = new QAction(MainWindow);
        actionMin_2->setObjectName(QStringLiteral("actionMin_2"));
        actionMin_2->setCheckable(true);
        actionMean_2 = new QAction(MainWindow);
        actionMean_2->setObjectName(QStringLiteral("actionMean_2"));
        actionMean_2->setCheckable(true);
        actionRMS_2 = new QAction(MainWindow);
        actionRMS_2->setObjectName(QStringLiteral("actionRMS_2"));
        actionRMS_2->setCheckable(true);
        actionMV = new QAction(MainWindow);
        actionMV->setObjectName(QStringLiteral("actionMV"));
        actionMV->setCheckable(true);
        actionMV->setChecked(false);
        actionV = new QAction(MainWindow);
        actionV->setObjectName(QStringLiteral("actionV"));
        actionV->setCheckable(true);
        actionV->setChecked(false);
        actionAutoV = new QAction(MainWindow);
        actionAutoV->setObjectName(QStringLiteral("actionAutoV"));
        actionAutoV->setCheckable(true);
        actionAutoV->setChecked(true);
        actionAutoI = new QAction(MainWindow);
        actionAutoI->setObjectName(QStringLiteral("actionAutoI"));
        actionAutoI->setCheckable(true);
        actionAutoI->setChecked(true);
        actionMA = new QAction(MainWindow);
        actionMA->setObjectName(QStringLiteral("actionMA"));
        actionMA->setCheckable(true);
        actionMA->setChecked(false);
        actionA = new QAction(MainWindow);
        actionA->setObjectName(QStringLiteral("actionA"));
        actionA->setCheckable(true);
        action300 = new QAction(MainWindow);
        action300->setObjectName(QStringLiteral("action300"));
        action300->setCheckable(true);
        action600 = new QAction(MainWindow);
        action600->setObjectName(QStringLiteral("action600"));
        action600->setCheckable(true);
        action1200 = new QAction(MainWindow);
        action1200->setObjectName(QStringLiteral("action1200"));
        action1200->setCheckable(true);
        action2400 = new QAction(MainWindow);
        action2400->setObjectName(QStringLiteral("action2400"));
        action2400->setCheckable(true);
        action4800 = new QAction(MainWindow);
        action4800->setObjectName(QStringLiteral("action4800"));
        action4800->setCheckable(true);
        action9600 = new QAction(MainWindow);
        action9600->setObjectName(QStringLiteral("action9600"));
        action9600->setCheckable(true);
        action14400 = new QAction(MainWindow);
        action14400->setObjectName(QStringLiteral("action14400"));
        action14400->setCheckable(true);
        action19200 = new QAction(MainWindow);
        action19200->setObjectName(QStringLiteral("action19200"));
        action19200->setCheckable(true);
        action28800 = new QAction(MainWindow);
        action28800->setObjectName(QStringLiteral("action28800"));
        action28800->setCheckable(true);
        action38400 = new QAction(MainWindow);
        action38400->setObjectName(QStringLiteral("action38400"));
        action38400->setCheckable(true);
        action57600 = new QAction(MainWindow);
        action57600->setObjectName(QStringLiteral("action57600"));
        action57600->setCheckable(true);
        action115200 = new QAction(MainWindow);
        action115200->setObjectName(QStringLiteral("action115200"));
        action115200->setCheckable(true);
        action8 = new QAction(MainWindow);
        action8->setObjectName(QStringLiteral("action8"));
        action8->setCheckable(true);
        actionNone = new QAction(MainWindow);
        actionNone->setObjectName(QStringLiteral("actionNone"));
        actionNone->setCheckable(true);
        action300_2 = new QAction(MainWindow);
        action300_2->setObjectName(QStringLiteral("action300_2"));
        action300_2->setCheckable(true);
        action600_2 = new QAction(MainWindow);
        action600_2->setObjectName(QStringLiteral("action600_2"));
        action600_2->setCheckable(true);
        action1200_2 = new QAction(MainWindow);
        action1200_2->setObjectName(QStringLiteral("action1200_2"));
        action1200_2->setCheckable(true);
        action2400_2 = new QAction(MainWindow);
        action2400_2->setObjectName(QStringLiteral("action2400_2"));
        action2400_2->setCheckable(true);
        action4800_2 = new QAction(MainWindow);
        action4800_2->setObjectName(QStringLiteral("action4800_2"));
        action4800_2->setCheckable(true);
        action9600_2 = new QAction(MainWindow);
        action9600_2->setObjectName(QStringLiteral("action9600_2"));
        action9600_2->setCheckable(true);
        action14400_2 = new QAction(MainWindow);
        action14400_2->setObjectName(QStringLiteral("action14400_2"));
        action14400_2->setCheckable(true);
        action19200_2 = new QAction(MainWindow);
        action19200_2->setObjectName(QStringLiteral("action19200_2"));
        action19200_2->setCheckable(true);
        action28800_2 = new QAction(MainWindow);
        action28800_2->setObjectName(QStringLiteral("action28800_2"));
        action28800_2->setCheckable(true);
        action38400_2 = new QAction(MainWindow);
        action38400_2->setObjectName(QStringLiteral("action38400_2"));
        action38400_2->setCheckable(true);
        action57600_2 = new QAction(MainWindow);
        action57600_2->setObjectName(QStringLiteral("action57600_2"));
        action57600_2->setCheckable(true);
        action115200_2 = new QAction(MainWindow);
        action115200_2->setObjectName(QStringLiteral("action115200_2"));
        action115200_2->setCheckable(true);
        action8_2 = new QAction(MainWindow);
        action8_2->setObjectName(QStringLiteral("action8_2"));
        action8_2->setCheckable(true);
        actionNone_2 = new QAction(MainWindow);
        actionNone_2->setObjectName(QStringLiteral("actionNone_2"));
        actionNone_2->setCheckable(true);
        actionRecord = new QAction(MainWindow);
        actionRecord->setObjectName(QStringLiteral("actionRecord"));
        actionRecord->setCheckable(true);
        actionForce_Square = new QAction(MainWindow);
        actionForce_Square->setObjectName(QStringLiteral("actionForce_Square"));
        actionForce_Square->setCheckable(true);
        actionAutomatically_Enable_Cursors = new QAction(MainWindow);
        actionAutomatically_Enable_Cursors->setObjectName(QStringLiteral("actionAutomatically_Enable_Cursors"));
        actionAutomatically_Enable_Cursors->setCheckable(true);
        actionAutomatically_Enable_Cursors->setChecked(true);
        action60FPS = new QAction(MainWindow);
        action60FPS->setObjectName(QStringLiteral("action60FPS"));
        action60FPS->setCheckable(true);
        action60FPS->setChecked(true);
        action30FPS = new QAction(MainWindow);
        action30FPS->setObjectName(QStringLiteral("action30FPS"));
        action30FPS->setCheckable(true);
        action20FPS = new QAction(MainWindow);
        action20FPS->setObjectName(QStringLiteral("action20FPS"));
        action20FPS->setCheckable(true);
        action15FPS = new QAction(MainWindow);
        action15FPS->setObjectName(QStringLiteral("action15FPS"));
        action15FPS->setCheckable(true);
        action10FPS = new QAction(MainWindow);
        action10FPS->setObjectName(QStringLiteral("action10FPS"));
        action10FPS->setCheckable(true);
        action5FPS = new QAction(MainWindow);
        action5FPS->setObjectName(QStringLiteral("action5FPS"));
        action5FPS->setCheckable(true);
        actionAuto_Lock = new QAction(MainWindow);
        actionAuto_Lock->setObjectName(QStringLiteral("actionAuto_Lock"));
        actionAuto_Lock->setCheckable(true);
        actionAuto_Lock->setChecked(true);
        actionSnap_to_Cursors = new QAction(MainWindow);
        actionSnap_to_Cursors->setObjectName(QStringLiteral("actionSnap_to_Cursors"));
        actionEnter_Manually = new QAction(MainWindow);
        actionEnter_Manually->setObjectName(QStringLiteral("actionEnter_Manually"));
        actionTake_Snapshot = new QAction(MainWindow);
        actionTake_Snapshot->setObjectName(QStringLiteral("actionTake_Snapshot"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        scopeAxes = new QCustomPlot(centralWidget);
        scopeAxes->setObjectName(QStringLiteral("scopeAxes"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scopeAxes->sizePolicy().hasHeightForWidth());
        scopeAxes->setSizePolicy(sizePolicy);
        scopeAxes->setMinimumSize(QSize(500, 400));
        scopeAxes->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(scopeAxes);

        debugConsole = new QTextEdit(centralWidget);
        debugConsole->setObjectName(QStringLiteral("debugConsole"));

        verticalLayout->addWidget(debugConsole);

        timeBaseSlider = new QSlider(centralWidget);
        timeBaseSlider->setObjectName(QStringLiteral("timeBaseSlider"));
        timeBaseSlider->setMinimum(-60);
        timeBaseSlider->setMaximum(10);
        timeBaseSlider->setPageStep(10);
        timeBaseSlider->setValue(-20);
        timeBaseSlider->setSliderPosition(-20);
        timeBaseSlider->setTracking(true);
        timeBaseSlider->setOrientation(Qt::Horizontal);
        timeBaseSlider->setTickPosition(QSlider::TicksBelow);
        timeBaseSlider->setTickInterval(10);

        verticalLayout->addWidget(timeBaseSlider);

        console1 = new QPlainTextEdit(centralWidget);
        console1->setObjectName(QStringLiteral("console1"));
        console1->setEnabled(true);
        console1->setMinimumSize(QSize(0, 0));
        console1->setMaximumSize(QSize(16777215, 48));
        console1->setReadOnly(true);

        verticalLayout->addWidget(console1);

        console2 = new QPlainTextEdit(centralWidget);
        console2->setObjectName(QStringLiteral("console2"));
        console2->setMaximumSize(QSize(16777215, 48));
        console2->setReadOnly(true);

        verticalLayout->addWidget(console2);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        deviceConnected = new deviceConnectedDisplay(centralWidget);
        deviceConnected->setObjectName(QStringLiteral("deviceConnected"));
        deviceConnected->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(deviceConnected);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        scopeGroup_CH1 = new QGroupBox(centralWidget);
        scopeGroup_CH1->setObjectName(QStringLiteral("scopeGroup_CH1"));
        scopeGroup_CH1->setFlat(false);
        scopeGroup_CH1->setCheckable(true);
        scopeGroup_CH1->setChecked(true);
        verticalLayout_2 = new QVBoxLayout(scopeGroup_CH1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        pausedLabeL_CH1 = new QCheckBox(scopeGroup_CH1);
        pausedLabeL_CH1->setObjectName(QStringLiteral("pausedLabeL_CH1"));

        verticalLayout_2->addWidget(pausedLabeL_CH1);

        acCoupledLabel_CH1 = new QCheckBox(scopeGroup_CH1);
        acCoupledLabel_CH1->setObjectName(QStringLiteral("acCoupledLabel_CH1"));

        verticalLayout_2->addWidget(acCoupledLabel_CH1);

        filterLabel_CH1 = new QCheckBox(scopeGroup_CH1);
        filterLabel_CH1->setObjectName(QStringLiteral("filterLabel_CH1"));

        verticalLayout_2->addWidget(filterLabel_CH1);

        doubleSampleLabel = new QCheckBox(scopeGroup_CH1);
        doubleSampleLabel->setObjectName(QStringLiteral("doubleSampleLabel"));

        verticalLayout_2->addWidget(doubleSampleLabel);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        voltageInfoMaxLabel_CH1 = new QLabel(scopeGroup_CH1);
        voltageInfoMaxLabel_CH1->setObjectName(QStringLiteral("voltageInfoMaxLabel_CH1"));

        gridLayout_2->addWidget(voltageInfoMaxLabel_CH1, 0, 0, 1, 1);

        voltageInfoMaxDisplay_CH1 = new QLCDNumber(scopeGroup_CH1);
        voltageInfoMaxDisplay_CH1->setObjectName(QStringLiteral("voltageInfoMaxDisplay_CH1"));
        voltageInfoMaxDisplay_CH1->setMinimumSize(QSize(0, 24));
        voltageInfoMaxDisplay_CH1->setFrameShape(QFrame::NoFrame);

        gridLayout_2->addWidget(voltageInfoMaxDisplay_CH1, 0, 1, 1, 1);

        voltageInfoMinLabel_CH1 = new QLabel(scopeGroup_CH1);
        voltageInfoMinLabel_CH1->setObjectName(QStringLiteral("voltageInfoMinLabel_CH1"));

        gridLayout_2->addWidget(voltageInfoMinLabel_CH1, 1, 0, 1, 1);

        voltageInfoMinDisplay_CH1 = new QLCDNumber(scopeGroup_CH1);
        voltageInfoMinDisplay_CH1->setObjectName(QStringLiteral("voltageInfoMinDisplay_CH1"));
        voltageInfoMinDisplay_CH1->setMinimumSize(QSize(0, 24));
        voltageInfoMinDisplay_CH1->setFrameShape(QFrame::NoFrame);

        gridLayout_2->addWidget(voltageInfoMinDisplay_CH1, 1, 1, 1, 1);

        VoltageInfoMeanLabel_CH1 = new QLabel(scopeGroup_CH1);
        VoltageInfoMeanLabel_CH1->setObjectName(QStringLiteral("VoltageInfoMeanLabel_CH1"));

        gridLayout_2->addWidget(VoltageInfoMeanLabel_CH1, 2, 0, 1, 1);

        voltageInfoRmsLabel_CH1 = new QLabel(scopeGroup_CH1);
        voltageInfoRmsLabel_CH1->setObjectName(QStringLiteral("voltageInfoRmsLabel_CH1"));

        gridLayout_2->addWidget(voltageInfoRmsLabel_CH1, 3, 0, 1, 1);

        voltageInfoRmsDisplay_CH1 = new QLCDNumber(scopeGroup_CH1);
        voltageInfoRmsDisplay_CH1->setObjectName(QStringLiteral("voltageInfoRmsDisplay_CH1"));
        voltageInfoRmsDisplay_CH1->setMinimumSize(QSize(0, 24));
        voltageInfoRmsDisplay_CH1->setFrameShape(QFrame::NoFrame);

        gridLayout_2->addWidget(voltageInfoRmsDisplay_CH1, 3, 1, 1, 1);

        voltageInfoMeanDisplay_CH1 = new QLCDNumber(scopeGroup_CH1);
        voltageInfoMeanDisplay_CH1->setObjectName(QStringLiteral("voltageInfoMeanDisplay_CH1"));
        voltageInfoMeanDisplay_CH1->setMinimumSize(QSize(0, 24));
        voltageInfoMeanDisplay_CH1->setFrameShape(QFrame::NoFrame);

        gridLayout_2->addWidget(voltageInfoMeanDisplay_CH1, 2, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);

        acCoupledLabel_CH1->raise();
        filterLabel_CH1->raise();
        pausedLabeL_CH1->raise();
        doubleSampleLabel->raise();

        verticalLayout_9->addWidget(scopeGroup_CH1);

        cursorGroup = new QGroupBox(centralWidget);
        cursorGroup->setObjectName(QStringLiteral("cursorGroup"));
        cursorGroup->setEnabled(true);
        cursorGroup->setCheckable(false);
        cursorGroup->setChecked(false);
        verticalLayout_8 = new QVBoxLayout(cursorGroup);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        cursorHoriCheck = new QCheckBox(cursorGroup);
        cursorHoriCheck->setObjectName(QStringLiteral("cursorHoriCheck"));

        verticalLayout_8->addWidget(cursorHoriCheck);

        cursorVertCheck = new QCheckBox(cursorGroup);
        cursorVertCheck->setObjectName(QStringLiteral("cursorVertCheck"));

        verticalLayout_8->addWidget(cursorVertCheck);

        makeCursorsNicer = new cursorEnabler(cursorGroup);
        makeCursorsNicer->setObjectName(QStringLiteral("makeCursorsNicer"));

        verticalLayout_8->addWidget(makeCursorsNicer);


        verticalLayout_9->addWidget(cursorGroup);


        horizontalLayout_13->addLayout(verticalLayout_9);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        scopeGroup_CH2 = new QGroupBox(centralWidget);
        scopeGroup_CH2->setObjectName(QStringLiteral("scopeGroup_CH2"));
        scopeGroup_CH2->setEnabled(true);
        scopeGroup_CH2->setFlat(false);
        scopeGroup_CH2->setCheckable(true);
        scopeGroup_CH2->setChecked(false);
        verticalLayout_11 = new QVBoxLayout(scopeGroup_CH2);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        pausedLabel_CH2 = new QCheckBox(scopeGroup_CH2);
        pausedLabel_CH2->setObjectName(QStringLiteral("pausedLabel_CH2"));

        verticalLayout_11->addWidget(pausedLabel_CH2);

        acCoupledLabel_CH2 = new QCheckBox(scopeGroup_CH2);
        acCoupledLabel_CH2->setObjectName(QStringLiteral("acCoupledLabel_CH2"));

        verticalLayout_11->addWidget(acCoupledLabel_CH2);

        filterLabel_CH2 = new QCheckBox(scopeGroup_CH2);
        filterLabel_CH2->setObjectName(QStringLiteral("filterLabel_CH2"));

        verticalLayout_11->addWidget(filterLabel_CH2);

        xyDisplayLabel = new QCheckBox(scopeGroup_CH2);
        xyDisplayLabel->setObjectName(QStringLiteral("xyDisplayLabel"));

        verticalLayout_11->addWidget(xyDisplayLabel);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        voltageInfoMaxLabel_CH2 = new QLabel(scopeGroup_CH2);
        voltageInfoMaxLabel_CH2->setObjectName(QStringLiteral("voltageInfoMaxLabel_CH2"));

        gridLayout_3->addWidget(voltageInfoMaxLabel_CH2, 0, 0, 1, 1);

        voltageInfoMaxDisplay_CH2 = new QLCDNumber(scopeGroup_CH2);
        voltageInfoMaxDisplay_CH2->setObjectName(QStringLiteral("voltageInfoMaxDisplay_CH2"));
        voltageInfoMaxDisplay_CH2->setMinimumSize(QSize(0, 24));
        voltageInfoMaxDisplay_CH2->setFrameShape(QFrame::NoFrame);

        gridLayout_3->addWidget(voltageInfoMaxDisplay_CH2, 0, 1, 1, 1);

        voltageInfoMinLabel_CH2 = new QLabel(scopeGroup_CH2);
        voltageInfoMinLabel_CH2->setObjectName(QStringLiteral("voltageInfoMinLabel_CH2"));

        gridLayout_3->addWidget(voltageInfoMinLabel_CH2, 1, 0, 1, 1);

        voltageInfoMinDisplay_CH2 = new QLCDNumber(scopeGroup_CH2);
        voltageInfoMinDisplay_CH2->setObjectName(QStringLiteral("voltageInfoMinDisplay_CH2"));
        voltageInfoMinDisplay_CH2->setMinimumSize(QSize(0, 24));
        voltageInfoMinDisplay_CH2->setFrameShape(QFrame::NoFrame);

        gridLayout_3->addWidget(voltageInfoMinDisplay_CH2, 1, 1, 1, 1);

        VoltageInfoMeanLabel_CH2 = new QLabel(scopeGroup_CH2);
        VoltageInfoMeanLabel_CH2->setObjectName(QStringLiteral("VoltageInfoMeanLabel_CH2"));

        gridLayout_3->addWidget(VoltageInfoMeanLabel_CH2, 2, 0, 1, 1);

        voltageInfoRmsLabel_CH2 = new QLabel(scopeGroup_CH2);
        voltageInfoRmsLabel_CH2->setObjectName(QStringLiteral("voltageInfoRmsLabel_CH2"));

        gridLayout_3->addWidget(voltageInfoRmsLabel_CH2, 3, 0, 1, 1);

        voltageInfoRmsDisplay_CH2 = new QLCDNumber(scopeGroup_CH2);
        voltageInfoRmsDisplay_CH2->setObjectName(QStringLiteral("voltageInfoRmsDisplay_CH2"));
        voltageInfoRmsDisplay_CH2->setMinimumSize(QSize(0, 24));
        voltageInfoRmsDisplay_CH2->setFrameShape(QFrame::NoFrame);

        gridLayout_3->addWidget(voltageInfoRmsDisplay_CH2, 3, 1, 1, 1);

        voltageInfoMeanDisplay_CH2 = new QLCDNumber(scopeGroup_CH2);
        voltageInfoMeanDisplay_CH2->setObjectName(QStringLiteral("voltageInfoMeanDisplay_CH2"));
        voltageInfoMeanDisplay_CH2->setMinimumSize(QSize(0, 24));
        voltageInfoMeanDisplay_CH2->setFrameShape(QFrame::NoFrame);

        gridLayout_3->addWidget(voltageInfoMeanDisplay_CH2, 2, 1, 1, 1);


        verticalLayout_11->addLayout(gridLayout_3);


        verticalLayout_10->addWidget(scopeGroup_CH2);

        triggerGroup = new QGroupBox(centralWidget);
        triggerGroup->setObjectName(QStringLiteral("triggerGroup"));
        triggerGroup->setEnabled(true);
        triggerGroup->setCheckable(true);
        triggerGroup->setChecked(false);
        verticalLayout_14 = new QVBoxLayout(triggerGroup);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        triggerChannelSelect = new QComboBox(triggerGroup);
        triggerChannelSelect->setObjectName(QStringLiteral("triggerChannelSelect"));

        verticalLayout_14->addWidget(triggerChannelSelect);

        triggerLevelValue = new QDoubleSpinBox(triggerGroup);
        triggerLevelValue->setObjectName(QStringLiteral("triggerLevelValue"));
        triggerLevelValue->setMinimum(-20);
        triggerLevelValue->setMaximum(20);
        triggerLevelValue->setSingleStep(0.1);

        verticalLayout_14->addWidget(triggerLevelValue);

        singleShotCheckBox = new QCheckBox(triggerGroup);
        singleShotCheckBox->setObjectName(QStringLiteral("singleShotCheckBox"));

        verticalLayout_14->addWidget(singleShotCheckBox);


        verticalLayout_10->addWidget(triggerGroup);


        horizontalLayout_13->addLayout(verticalLayout_10);


        verticalLayout_5->addLayout(horizontalLayout_13);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_3);

        cursorStatsLabel = new QLabel(centralWidget);
        cursorStatsLabel->setObjectName(QStringLiteral("cursorStatsLabel"));
        cursorStatsLabel->setMaximumSize(QSize(16777215, 48));
        cursorStatsLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(cursorStatsLabel);

        multimeterGroup = new QGroupBox(centralWidget);
        multimeterGroup->setObjectName(QStringLiteral("multimeterGroup"));
        multimeterGroup->setEnabled(false);
        multimeterGroup->setCheckable(true);
        multimeterGroup->setChecked(false);
        gridLayout = new QGridLayout(multimeterGroup);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        multimeterModeSelect = new QComboBox(multimeterGroup);
        multimeterModeSelect->setObjectName(QStringLiteral("multimeterModeSelect"));

        gridLayout->addWidget(multimeterModeSelect, 1, 0, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setHorizontalSpacing(0);
        formLayout->setVerticalSpacing(0);
        multimeterMaxLabel = new QLabel(multimeterGroup);
        multimeterMaxLabel->setObjectName(QStringLiteral("multimeterMaxLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, multimeterMaxLabel);

        multimeterMinLabel = new QLabel(multimeterGroup);
        multimeterMinLabel->setObjectName(QStringLiteral("multimeterMinLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, multimeterMinLabel);

        multimeterMinDisplay = new QLCDNumber(multimeterGroup);
        multimeterMinDisplay->setObjectName(QStringLiteral("multimeterMinDisplay"));
        multimeterMinDisplay->setMinimumSize(QSize(0, 24));
        multimeterMinDisplay->setFrameShape(QFrame::NoFrame);
        multimeterMinDisplay->setDigitCount(4);

        formLayout->setWidget(1, QFormLayout::FieldRole, multimeterMinDisplay);

        multimeterMeanLabel = new QLabel(multimeterGroup);
        multimeterMeanLabel->setObjectName(QStringLiteral("multimeterMeanLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, multimeterMeanLabel);

        multimeterMeanDisplay = new QLCDNumber(multimeterGroup);
        multimeterMeanDisplay->setObjectName(QStringLiteral("multimeterMeanDisplay"));
        multimeterMeanDisplay->setMinimumSize(QSize(0, 24));
        multimeterMeanDisplay->setFrameShape(QFrame::NoFrame);
        multimeterMeanDisplay->setDigitCount(4);

        formLayout->setWidget(2, QFormLayout::FieldRole, multimeterMeanDisplay);

        multimeterRmsLabel = new QLabel(multimeterGroup);
        multimeterRmsLabel->setObjectName(QStringLiteral("multimeterRmsLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, multimeterRmsLabel);

        multimeterRmsDisplay = new QLCDNumber(multimeterGroup);
        multimeterRmsDisplay->setObjectName(QStringLiteral("multimeterRmsDisplay"));
        multimeterRmsDisplay->setMinimumSize(QSize(0, 24));
        multimeterRmsDisplay->setFrameShape(QFrame::NoFrame);
        multimeterRmsDisplay->setDigitCount(4);

        formLayout->setWidget(3, QFormLayout::FieldRole, multimeterRmsDisplay);

        multimeterMaxDisplay = new QLCDNumber(multimeterGroup);
        multimeterMaxDisplay->setObjectName(QStringLiteral("multimeterMaxDisplay"));
        multimeterMaxDisplay->setMinimumSize(QSize(0, 24));
        multimeterMaxDisplay->setFrameShape(QFrame::NoFrame);
        multimeterMaxDisplay->setDigitCount(4);

        formLayout->setWidget(0, QFormLayout::FieldRole, multimeterMaxDisplay);


        gridLayout->addLayout(formLayout, 0, 1, 6, 1);

        multimeterPauseCheckBox = new QCheckBox(multimeterGroup);
        multimeterPauseCheckBox->setObjectName(QStringLiteral("multimeterPauseCheckBox"));

        gridLayout->addWidget(multimeterPauseCheckBox, 5, 0, 1, 1);

        multimeterResistanceLabel = new QLabel(multimeterGroup);
        multimeterResistanceLabel->setObjectName(QStringLiteral("multimeterResistanceLabel"));

        gridLayout->addWidget(multimeterResistanceLabel, 2, 0, 1, 1);

        multimeterModeLabel = new QLabel(multimeterGroup);
        multimeterModeLabel->setObjectName(QStringLiteral("multimeterModeLabel"));

        gridLayout->addWidget(multimeterModeLabel, 0, 0, 1, 1);

        multimeterResistanceSelect = new espoSpinBox(multimeterGroup);
        multimeterResistanceSelect->setObjectName(QStringLiteral("multimeterResistanceSelect"));
        multimeterResistanceSelect->setDecimals(0);
        multimeterResistanceSelect->setMaximum(1e+6);

        gridLayout->addWidget(multimeterResistanceSelect, 3, 0, 1, 1);


        verticalLayout_5->addWidget(multimeterGroup);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        controller_fg = new functionGenControl(centralWidget);
        controller_fg->setObjectName(QStringLiteral("controller_fg"));

        verticalLayout_5->addWidget(controller_fg);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        signalGenGroup_CH1 = new QGroupBox(centralWidget);
        signalGenGroup_CH1->setObjectName(QStringLiteral("signalGenGroup_CH1"));
        signalGenGroup_CH1->setEnabled(true);
        signalGenGroup_CH1->setCheckable(false);
        signalGenGroup_CH1->setChecked(false);
        verticalLayout_19 = new QVBoxLayout(signalGenGroup_CH1);
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setContentsMargins(11, 11, 11, 11);
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        waveformLabel_CH1 = new QLabel(signalGenGroup_CH1);
        waveformLabel_CH1->setObjectName(QStringLiteral("waveformLabel_CH1"));

        verticalLayout_19->addWidget(waveformLabel_CH1);

        waveformSelect_CH1 = new espoComboBox(signalGenGroup_CH1);
        waveformSelect_CH1->setObjectName(QStringLiteral("waveformSelect_CH1"));

        verticalLayout_19->addWidget(waveformSelect_CH1);

        frequencyLabel_CH1 = new QLabel(signalGenGroup_CH1);
        frequencyLabel_CH1->setObjectName(QStringLiteral("frequencyLabel_CH1"));

        verticalLayout_19->addWidget(frequencyLabel_CH1);

        frequencyValue_CH1 = new espoSpinBox(signalGenGroup_CH1);
        frequencyValue_CH1->setObjectName(QStringLiteral("frequencyValue_CH1"));
        frequencyValue_CH1->setSuffix(QStringLiteral("Hz"));
        frequencyValue_CH1->setDecimals(2);
        frequencyValue_CH1->setMinimum(0);
        frequencyValue_CH1->setMaximum(1e+6);
        frequencyValue_CH1->setSingleStep(100);
        frequencyValue_CH1->setValue(1000);

        verticalLayout_19->addWidget(frequencyValue_CH1);

        amplitudeLabel_CH1 = new QLabel(signalGenGroup_CH1);
        amplitudeLabel_CH1->setObjectName(QStringLiteral("amplitudeLabel_CH1"));

        verticalLayout_19->addWidget(amplitudeLabel_CH1);

        amplitudeValue_CH1 = new espoSpinBox(signalGenGroup_CH1);
        amplitudeValue_CH1->setObjectName(QStringLiteral("amplitudeValue_CH1"));
        amplitudeValue_CH1->setMaximum(9.6);
        amplitudeValue_CH1->setSingleStep(0.1);

        verticalLayout_19->addWidget(amplitudeValue_CH1);

        dcOffsetLabel_CH1 = new QLabel(signalGenGroup_CH1);
        dcOffsetLabel_CH1->setObjectName(QStringLiteral("dcOffsetLabel_CH1"));

        verticalLayout_19->addWidget(dcOffsetLabel_CH1);

        dcOffsetValue_CH1 = new espoSpinBox(signalGenGroup_CH1);
        dcOffsetValue_CH1->setObjectName(QStringLiteral("dcOffsetValue_CH1"));
        dcOffsetValue_CH1->setMaximum(9.6);
        dcOffsetValue_CH1->setSingleStep(0.1);

        verticalLayout_19->addWidget(dcOffsetValue_CH1);


        horizontalLayout_5->addWidget(signalGenGroup_CH1);

        signalGenGroup_CH2 = new QGroupBox(centralWidget);
        signalGenGroup_CH2->setObjectName(QStringLiteral("signalGenGroup_CH2"));
        signalGenGroup_CH2->setEnabled(true);
        signalGenGroup_CH2->setCheckable(false);
        signalGenGroup_CH2->setChecked(false);
        verticalLayout_21 = new QVBoxLayout(signalGenGroup_CH2);
        verticalLayout_21->setSpacing(6);
        verticalLayout_21->setContentsMargins(11, 11, 11, 11);
        verticalLayout_21->setObjectName(QStringLiteral("verticalLayout_21"));
        waveformLabel_CH2 = new QLabel(signalGenGroup_CH2);
        waveformLabel_CH2->setObjectName(QStringLiteral("waveformLabel_CH2"));
        waveformLabel_CH2->setEnabled(true);

        verticalLayout_21->addWidget(waveformLabel_CH2);

        waveformSelect_CH2 = new espoComboBox(signalGenGroup_CH2);
        waveformSelect_CH2->setObjectName(QStringLiteral("waveformSelect_CH2"));
        waveformSelect_CH2->setEnabled(true);

        verticalLayout_21->addWidget(waveformSelect_CH2);

        frequencyLabel_CH2 = new QLabel(signalGenGroup_CH2);
        frequencyLabel_CH2->setObjectName(QStringLiteral("frequencyLabel_CH2"));
        frequencyLabel_CH2->setEnabled(true);

        verticalLayout_21->addWidget(frequencyLabel_CH2);

        frequencyValue_CH2 = new espoSpinBox(signalGenGroup_CH2);
        frequencyValue_CH2->setObjectName(QStringLiteral("frequencyValue_CH2"));
        frequencyValue_CH2->setEnabled(true);
        frequencyValue_CH2->setSuffix(QStringLiteral("Hz"));
        frequencyValue_CH2->setDecimals(2);
        frequencyValue_CH2->setMaximum(1e+6);
        frequencyValue_CH2->setSingleStep(100);
        frequencyValue_CH2->setValue(1000);

        verticalLayout_21->addWidget(frequencyValue_CH2);

        amplitudeLabel_CH2 = new QLabel(signalGenGroup_CH2);
        amplitudeLabel_CH2->setObjectName(QStringLiteral("amplitudeLabel_CH2"));
        amplitudeLabel_CH2->setEnabled(true);

        verticalLayout_21->addWidget(amplitudeLabel_CH2);

        amplitudeValue_CH2 = new espoSpinBox(signalGenGroup_CH2);
        amplitudeValue_CH2->setObjectName(QStringLiteral("amplitudeValue_CH2"));
        amplitudeValue_CH2->setEnabled(true);
        amplitudeValue_CH2->setMaximum(10);
        amplitudeValue_CH2->setSingleStep(0.1);

        verticalLayout_21->addWidget(amplitudeValue_CH2);

        dcOffsetLabel_CH2 = new QLabel(signalGenGroup_CH2);
        dcOffsetLabel_CH2->setObjectName(QStringLiteral("dcOffsetLabel_CH2"));
        dcOffsetLabel_CH2->setEnabled(true);

        verticalLayout_21->addWidget(dcOffsetLabel_CH2);

        dcOffsetValue_CH2 = new espoSpinBox(signalGenGroup_CH2);
        dcOffsetValue_CH2->setObjectName(QStringLiteral("dcOffsetValue_CH2"));
        dcOffsetValue_CH2->setEnabled(true);
        dcOffsetValue_CH2->setMaximum(10);
        dcOffsetValue_CH2->setSingleStep(0.1);

        verticalLayout_21->addWidget(dcOffsetValue_CH2);


        horizontalLayout_5->addWidget(signalGenGroup_CH2);


        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));

        verticalLayout_5->addLayout(horizontalLayout_7);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_4);

        controller_iso = new isoDriver(centralWidget);
        controller_iso->setObjectName(QStringLiteral("controller_iso"));

        verticalLayout_5->addWidget(controller_iso);


        horizontalLayout->addLayout(verticalLayout_5);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        psuGroup = new QGroupBox(centralWidget);
        psuGroup->setObjectName(QStringLiteral("psuGroup"));
        psuGroup->setAutoFillBackground(false);
        verticalLayout_15 = new QVBoxLayout(psuGroup);
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setContentsMargins(11, 11, 11, 11);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        psuSlider = new espoSlider(psuGroup);
        psuSlider->setObjectName(QStringLiteral("psuSlider"));
        psuSlider->setEnabled(false);
        psuSlider->setMinimum(90);
        psuSlider->setMaximum(300);
        psuSlider->setSingleStep(1);
        psuSlider->setOrientation(Qt::Vertical);
        psuSlider->setTickPosition(QSlider::TicksBelow);
        psuSlider->setTickInterval(20);

        verticalLayout_15->addWidget(psuSlider);

        lockPsuCheckBox = new timedTickBox(psuGroup);
        lockPsuCheckBox->setObjectName(QStringLiteral("lockPsuCheckBox"));
        lockPsuCheckBox->setChecked(true);

        verticalLayout_15->addWidget(lockPsuCheckBox);

        psuDisplay = new QLCDNumber(psuGroup);
        psuDisplay->setObjectName(QStringLiteral("psuDisplay"));
        psuDisplay->setMinimumSize(QSize(108, 36));
        psuDisplay->setMaximumSize(QSize(108, 36));
        psuDisplay->setSmallDecimalPoint(true);
        psuDisplay->setDigitCount(4);
        psuDisplay->setProperty("value", QVariant(5));
        psuDisplay->setProperty("intValue", QVariant(5));

        verticalLayout_15->addWidget(psuDisplay);


        verticalLayout_18->addWidget(psuGroup);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        busSifferGroup_CH1 = new QGroupBox(centralWidget);
        busSifferGroup_CH1->setObjectName(QStringLiteral("busSifferGroup_CH1"));
        busSifferGroup_CH1->setCheckable(true);
        busSifferGroup_CH1->setChecked(false);
        verticalLayout_7 = new QVBoxLayout(busSifferGroup_CH1);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        pause_LA = new QCheckBox(busSifferGroup_CH1);
        pause_LA->setObjectName(QStringLiteral("pause_LA"));
        pause_LA->setEnabled(true);

        verticalLayout_7->addWidget(pause_LA);

        serialDecodingCheck_CH1 = new QGroupBox(busSifferGroup_CH1);
        serialDecodingCheck_CH1->setObjectName(QStringLiteral("serialDecodingCheck_CH1"));
        serialDecodingCheck_CH1->setFlat(true);
        serialDecodingCheck_CH1->setCheckable(true);
        serialDecodingCheck_CH1->setChecked(false);
        verticalLayout_6 = new QVBoxLayout(serialDecodingCheck_CH1);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 6, 0, 0);
        serialDecodingModeSelect_CH1 = new QComboBox(serialDecodingCheck_CH1);
        serialDecodingModeSelect_CH1->setObjectName(QStringLiteral("serialDecodingModeSelect_CH1"));

        verticalLayout_6->addWidget(serialDecodingModeSelect_CH1);


        verticalLayout_7->addWidget(serialDecodingCheck_CH1);


        verticalLayout_3->addWidget(busSifferGroup_CH1);

        busSnifferGroup_CH2 = new QGroupBox(centralWidget);
        busSnifferGroup_CH2->setObjectName(QStringLiteral("busSnifferGroup_CH2"));
        busSnifferGroup_CH2->setEnabled(false);
        busSnifferGroup_CH2->setCheckable(true);
        busSnifferGroup_CH2->setChecked(false);
        verticalLayout_16 = new QVBoxLayout(busSnifferGroup_CH2);
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        serialDecodingCheck_CH2 = new QGroupBox(busSnifferGroup_CH2);
        serialDecodingCheck_CH2->setObjectName(QStringLiteral("serialDecodingCheck_CH2"));
        serialDecodingCheck_CH2->setFlat(true);
        serialDecodingCheck_CH2->setCheckable(true);
        serialDecodingCheck_CH2->setChecked(false);
        verticalLayout_17 = new QVBoxLayout(serialDecodingCheck_CH2);
        verticalLayout_17->setSpacing(0);
        verticalLayout_17->setContentsMargins(11, 11, 11, 11);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        verticalLayout_17->setContentsMargins(0, 6, 0, 0);
        serialDecodingModeSelect_CH2 = new QComboBox(serialDecodingCheck_CH2);
        serialDecodingModeSelect_CH2->setObjectName(QStringLiteral("serialDecodingModeSelect_CH2"));

        verticalLayout_17->addWidget(serialDecodingModeSelect_CH2);


        verticalLayout_16->addWidget(serialDecodingCheck_CH2);


        verticalLayout_3->addWidget(busSnifferGroup_CH2);

        digitalOutputGroup = new QGroupBox(centralWidget);
        digitalOutputGroup->setObjectName(QStringLiteral("digitalOutputGroup"));
        gridLayout_4 = new QGridLayout(digitalOutputGroup);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        digitalOutCheckbox_CH3 = new QCheckBox(digitalOutputGroup);
        digitalOutCheckbox_CH3->setObjectName(QStringLiteral("digitalOutCheckbox_CH3"));

        gridLayout_4->addWidget(digitalOutCheckbox_CH3, 1, 0, 1, 1);

        digitalOutCheckbox_CH2 = new QCheckBox(digitalOutputGroup);
        digitalOutCheckbox_CH2->setObjectName(QStringLiteral("digitalOutCheckbox_CH2"));

        gridLayout_4->addWidget(digitalOutCheckbox_CH2, 0, 1, 1, 1);

        digitalOutCheckbox_CH1 = new QCheckBox(digitalOutputGroup);
        digitalOutCheckbox_CH1->setObjectName(QStringLiteral("digitalOutCheckbox_CH1"));

        gridLayout_4->addWidget(digitalOutCheckbox_CH1, 0, 0, 1, 1);

        digitalOutCheckbox_CH4 = new QCheckBox(digitalOutputGroup);
        digitalOutCheckbox_CH4->setObjectName(QStringLiteral("digitalOutCheckbox_CH4"));

        gridLayout_4->addWidget(digitalOutCheckbox_CH4, 1, 1, 1, 1);

        digitalOutCheckbox_CH2->raise();
        digitalOutCheckbox_CH1->raise();
        digitalOutCheckbox_CH3->raise();
        digitalOutCheckbox_CH4->raise();

        verticalLayout_3->addWidget(digitalOutputGroup);

        debugButton1 = new QPushButton(centralWidget);
        debugButton1->setObjectName(QStringLiteral("debugButton1"));

        verticalLayout_3->addWidget(debugButton1);

        debugButton2 = new QPushButton(centralWidget);
        debugButton2->setObjectName(QStringLiteral("debugButton2"));

        verticalLayout_3->addWidget(debugButton2);

        bufferDisplay = new bufferControl(centralWidget);
        bufferDisplay->setObjectName(QStringLiteral("bufferDisplay"));
        bufferDisplay->setMinimumSize(QSize(96, 36));
        bufferDisplay->setMaximumSize(QSize(96, 36));
        bufferDisplay->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(bufferDisplay);


        verticalLayout_18->addLayout(verticalLayout_3);


        horizontalLayout->addLayout(verticalLayout_18);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1136, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuOscilloscope_2 = new QMenu(menuBar);
        menuOscilloscope_2->setObjectName(QStringLiteral("menuOscilloscope_2"));
        menuGain_2 = new QMenu(menuOscilloscope_2);
        menuGain_2->setObjectName(QStringLiteral("menuGain_2"));
        menuCH1_Stats = new noCloseMenu(menuOscilloscope_2);
        menuCH1_Stats->setObjectName(QStringLiteral("menuCH1_Stats"));
        menuCH2_Stats = new noCloseMenu(menuOscilloscope_2);
        menuCH2_Stats->setObjectName(QStringLiteral("menuCH2_Stats"));
        menuFrame_rate = new QMenu(menuOscilloscope_2);
        menuFrame_rate->setObjectName(QStringLiteral("menuFrame_rate"));
        menuRange = new QMenu(menuOscilloscope_2);
        menuRange->setObjectName(QStringLiteral("menuRange"));
        menuMultimeter_2 = new QMenu(menuBar);
        menuMultimeter_2->setObjectName(QStringLiteral("menuMultimeter_2"));
        menuV_2 = new QMenu(menuMultimeter_2);
        menuV_2->setObjectName(QStringLiteral("menuV_2"));
        menuI_2 = new QMenu(menuMultimeter_2);
        menuI_2->setObjectName(QStringLiteral("menuI_2"));
        menuBus_Sniffer = new QMenu(menuBar);
        menuBus_Sniffer->setObjectName(QStringLiteral("menuBus_Sniffer"));
        menuUART_1 = new QMenu(menuBus_Sniffer);
        menuUART_1->setObjectName(QStringLiteral("menuUART_1"));
        menuBaud_Rate = new QMenu(menuUART_1);
        menuBaud_Rate->setObjectName(QStringLiteral("menuBaud_Rate"));
        menuType_Here_2 = new QMenu(menuUART_1);
        menuType_Here_2->setObjectName(QStringLiteral("menuType_Here_2"));
        menuParity_Bit = new QMenu(menuUART_1);
        menuParity_Bit->setObjectName(QStringLiteral("menuParity_Bit"));
        menuData_Bits = new QMenu(menuUART_1);
        menuData_Bits->setObjectName(QStringLiteral("menuData_Bits"));
        menuUART_2 = new QMenu(menuBus_Sniffer);
        menuUART_2->setObjectName(QStringLiteral("menuUART_2"));
        menuBaud_Rate_2 = new QMenu(menuUART_2);
        menuBaud_Rate_2->setObjectName(QStringLiteral("menuBaud_Rate_2"));
        menuData_Bits_2 = new QMenu(menuUART_2);
        menuData_Bits_2->setObjectName(QStringLiteral("menuData_Bits_2"));
        menuParity_Bit_2 = new QMenu(menuUART_2);
        menuParity_Bit_2->setObjectName(QStringLiteral("menuParity_Bit_2"));
        menuPower_Supply = new QMenu(menuBar);
        menuPower_Supply->setObjectName(QStringLiteral("menuPower_Supply"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuOscilloscope_2->menuAction());
        menuBar->addAction(menuMultimeter_2->menuAction());
        menuBar->addAction(menuBus_Sniffer->menuAction());
        menuBar->addAction(menuPower_Supply->menuAction());
        menuFile->addAction(actionRecord);
        menuFile->addAction(actionTake_Snapshot);
        menuOscilloscope_2->addAction(menuRange->menuAction());
        menuOscilloscope_2->addSeparator();
        menuOscilloscope_2->addAction(menuFrame_rate->menuAction());
        menuOscilloscope_2->addSeparator();
        menuOscilloscope_2->addAction(menuGain_2->menuAction());
        menuOscilloscope_2->addSeparator();
        menuOscilloscope_2->addAction(menuCH1_Stats->menuAction());
        menuOscilloscope_2->addAction(menuCH2_Stats->menuAction());
        menuOscilloscope_2->addAction(actionCursor_Stats);
        menuOscilloscope_2->addSeparator();
        menuOscilloscope_2->addAction(actionCalibrate);
        menuOscilloscope_2->addAction(actionForce_Square);
        menuOscilloscope_2->addAction(actionAutomatically_Enable_Cursors);
        menuGain_2->addAction(actionGainAuto);
        menuGain_2->addAction(actionGain0_5);
        menuGain_2->addAction(actionGain1);
        menuGain_2->addAction(actionGain2);
        menuGain_2->addAction(actionGain4);
        menuGain_2->addAction(actionGain8);
        menuGain_2->addAction(actionGain16);
        menuGain_2->addAction(actionGain32);
        menuGain_2->addAction(actionGain64);
        menuCH1_Stats->addAction(actionMax);
        menuCH1_Stats->addAction(actionMin);
        menuCH1_Stats->addAction(actionMean);
        menuCH1_Stats->addAction(actionRMS);
        menuCH2_Stats->addAction(actionMax_2);
        menuCH2_Stats->addAction(actionMin_2);
        menuCH2_Stats->addAction(actionMean_2);
        menuCH2_Stats->addAction(actionRMS_2);
        menuFrame_rate->addAction(action60FPS);
        menuFrame_rate->addAction(action30FPS);
        menuFrame_rate->addAction(action20FPS);
        menuFrame_rate->addAction(action15FPS);
        menuFrame_rate->addAction(action10FPS);
        menuFrame_rate->addAction(action5FPS);
        menuRange->addAction(actionSnap_to_Cursors);
        menuRange->addAction(actionEnter_Manually);
        menuMultimeter_2->addSeparator();
        menuMultimeter_2->addAction(menuV_2->menuAction());
        menuMultimeter_2->addAction(menuI_2->menuAction());
        menuV_2->addAction(actionAutoV);
        menuV_2->addAction(actionMV);
        menuV_2->addAction(actionV);
        menuI_2->addAction(actionAutoI);
        menuI_2->addAction(actionMA);
        menuI_2->addAction(actionA);
        menuBus_Sniffer->addAction(menuUART_1->menuAction());
        menuBus_Sniffer->addAction(menuUART_2->menuAction());
        menuUART_1->addAction(menuBaud_Rate->menuAction());
        menuUART_1->addAction(menuParity_Bit->menuAction());
        menuUART_1->addAction(menuData_Bits->menuAction());
        menuUART_1->addAction(menuType_Here_2->menuAction());
        menuBaud_Rate->addAction(action300);
        menuBaud_Rate->addAction(action600);
        menuBaud_Rate->addAction(action1200);
        menuBaud_Rate->addAction(action2400);
        menuBaud_Rate->addAction(action4800);
        menuBaud_Rate->addAction(action9600);
        menuBaud_Rate->addAction(action14400);
        menuBaud_Rate->addAction(action19200);
        menuBaud_Rate->addAction(action28800);
        menuBaud_Rate->addAction(action38400);
        menuBaud_Rate->addAction(action57600);
        menuBaud_Rate->addAction(action115200);
        menuParity_Bit->addAction(actionNone);
        menuData_Bits->addAction(action8);
        menuUART_2->addAction(menuBaud_Rate_2->menuAction());
        menuUART_2->addAction(menuData_Bits_2->menuAction());
        menuUART_2->addAction(menuParity_Bit_2->menuAction());
        menuBaud_Rate_2->addAction(action300_2);
        menuBaud_Rate_2->addAction(action600_2);
        menuBaud_Rate_2->addAction(action1200_2);
        menuBaud_Rate_2->addAction(action2400_2);
        menuBaud_Rate_2->addAction(action4800_2);
        menuBaud_Rate_2->addAction(action9600_2);
        menuBaud_Rate_2->addAction(action14400_2);
        menuBaud_Rate_2->addAction(action19200_2);
        menuBaud_Rate_2->addAction(action28800_2);
        menuBaud_Rate_2->addAction(action38400_2);
        menuBaud_Rate_2->addAction(action57600_2);
        menuBaud_Rate_2->addAction(action115200_2);
        menuData_Bits_2->addAction(action8_2);
        menuParity_Bit_2->addAction(actionNone_2);
        menuPower_Supply->addAction(actionAuto_Lock);

        retranslateUi(MainWindow);
        QObject::connect(scopeGroup_CH1, SIGNAL(toggled(bool)), bufferDisplay, SLOT(scopeIn_CH1(bool)));
        QObject::connect(scopeGroup_CH2, SIGNAL(toggled(bool)), bufferDisplay, SLOT(scopeIn_CH2(bool)));
        QObject::connect(signalGenGroup_CH2, SIGNAL(toggled(bool)), bufferDisplay, SLOT(signalGenIn(bool)));
        QObject::connect(bufferDisplay, SIGNAL(busSnifferOut_CH2(bool)), busSnifferGroup_CH2, SLOT(setEnabled(bool)));
        QObject::connect(bufferDisplay, SIGNAL(signalGenOut(bool)), signalGenGroup_CH2, SLOT(setEnabled(bool)));
        QObject::connect(bufferDisplay, SIGNAL(scopeOut_CH1(bool)), scopeGroup_CH1, SLOT(setEnabled(bool)));
        QObject::connect(bufferDisplay, SIGNAL(scopeOut_CH2(bool)), scopeGroup_CH2, SLOT(setEnabled(bool)));
        QObject::connect(bufferDisplay, SIGNAL(busSnifferUncheck(bool)), busSnifferGroup_CH2, SLOT(setChecked(bool)));
        QObject::connect(bufferDisplay, SIGNAL(scopeUncheck(bool)), scopeGroup_CH2, SLOT(setChecked(bool)));
        QObject::connect(doubleSampleLabel, SIGNAL(toggled(bool)), bufferDisplay, SLOT(scopeDsrIn(bool)));
        QObject::connect(bufferDisplay, SIGNAL(scopeDsrUncheck(bool)), doubleSampleLabel, SLOT(setChecked(bool)));
        QObject::connect(bufferDisplay, SIGNAL(scopeDsrOut(bool)), doubleSampleLabel, SLOT(setEnabled(bool)));
        QObject::connect(psuSlider, SIGNAL(valueChanged(int)), psuSlider, SLOT(selfMoved(int)));
        QObject::connect(psuSlider, SIGNAL(lcdOut(QString)), psuDisplay, SLOT(display(QString)));
        QObject::connect(amplitudeValue_CH1, SIGNAL(valueChanged(double)), dcOffsetValue_CH1, SLOT(maximumChanged(double)));
        QObject::connect(amplitudeValue_CH2, SIGNAL(valueChanged(double)), dcOffsetValue_CH2, SLOT(maximumChanged(double)));
        QObject::connect(dcOffsetValue_CH1, SIGNAL(valueChanged(double)), amplitudeValue_CH1, SLOT(maximumChanged(double)));
        QObject::connect(dcOffsetValue_CH2, SIGNAL(valueChanged(double)), amplitudeValue_CH2, SLOT(maximumChanged(double)));
        QObject::connect(waveformSelect_CH1, SIGNAL(currentTextChanged(QString)), controller_fg, SLOT(waveformName_CH1(QString)));
        QObject::connect(waveformSelect_CH2, SIGNAL(currentTextChanged(QString)), controller_fg, SLOT(waveformName_CH2(QString)));
        QObject::connect(amplitudeValue_CH1, SIGNAL(valueChanged(double)), controller_fg, SLOT(amplitudeUpdate_CH1(double)));
        QObject::connect(dcOffsetValue_CH1, SIGNAL(valueChanged(double)), controller_fg, SLOT(offsetUpdate_CH1(double)));
        QObject::connect(bufferDisplay, SIGNAL(busSnifferOut_CH1(bool)), busSifferGroup_CH1, SLOT(setEnabled(bool)));
        QObject::connect(bufferDisplay, SIGNAL(busSnifferOut_CH2(bool)), busSnifferGroup_CH2, SLOT(setEnabled(bool)));
        QObject::connect(busSifferGroup_CH1, SIGNAL(toggled(bool)), bufferDisplay, SLOT(busSnifferIn_CH1(bool)));
        QObject::connect(busSnifferGroup_CH2, SIGNAL(toggled(bool)), bufferDisplay, SLOT(busSnifferIn_CH2(bool)));
        QObject::connect(digitalOutCheckbox_CH1, SIGNAL(toggled(bool)), bufferDisplay, SLOT(digIn_CH1(bool)));
        QObject::connect(digitalOutCheckbox_CH2, SIGNAL(toggled(bool)), bufferDisplay, SLOT(digIn_CH2(bool)));
        QObject::connect(digitalOutCheckbox_CH3, SIGNAL(toggled(bool)), bufferDisplay, SLOT(digIn_CH3(bool)));
        QObject::connect(digitalOutCheckbox_CH4, SIGNAL(toggled(bool)), bufferDisplay, SLOT(digIn_CH4(bool)));
        QObject::connect(amplitudeValue_CH2, SIGNAL(valueChanged(double)), controller_fg, SLOT(amplitudeUpdate_CH2(double)));
        QObject::connect(dcOffsetValue_CH2, SIGNAL(valueChanged(double)), controller_fg, SLOT(offsetUpdate_CH2(double)));
        QObject::connect(timeBaseSlider, SIGNAL(valueChanged(int)), controller_iso, SLOT(setWindow(int)));
        QObject::connect(scopeAxes, SIGNAL(mouseWheel(QWheelEvent*)), controller_iso, SLOT(setVoltageRange(QWheelEvent*)));
        QObject::connect(pausedLabeL_CH1, SIGNAL(toggled(bool)), controller_iso, SLOT(pauseEnable_CH1(bool)));
        QObject::connect(pausedLabel_CH2, SIGNAL(toggled(bool)), controller_iso, SLOT(pauseEnable_CH2(bool)));
        QObject::connect(pausedLabeL_CH1, SIGNAL(toggled(bool)), pausedLabel_CH2, SLOT(setChecked(bool)));
        QObject::connect(pausedLabel_CH2, SIGNAL(toggled(bool)), pausedLabeL_CH1, SLOT(setChecked(bool)));
        QObject::connect(controller_iso, SIGNAL(disableWindow(bool)), MainWindow, SLOT(setEnabled(bool)));
        QObject::connect(scopeAxes, SIGNAL(mouseRelease(QMouseEvent*)), controller_iso, SLOT(graphMouseRelease(QMouseEvent*)));
        QObject::connect(cursorHoriCheck, SIGNAL(toggled(bool)), controller_iso, SLOT(cursorEnableHori(bool)));
        QObject::connect(cursorVertCheck, SIGNAL(toggled(bool)), controller_iso, SLOT(cursorEnableVert(bool)));
        QObject::connect(scopeAxes, SIGNAL(mouseMove(QMouseEvent*)), controller_iso, SLOT(graphMouseMove(QMouseEvent*)));
        QObject::connect(controller_iso, SIGNAL(setCursorStatsVisible(bool)), cursorStatsLabel, SLOT(setVisible(bool)));
        QObject::connect(lockPsuCheckBox, SIGNAL(toggled(bool)), psuSlider, SLOT(setDisabled(bool)));
        QObject::connect(triggerGroup, SIGNAL(toggled(bool)), controller_iso, SLOT(setTriggerEnabled(bool)));
        QObject::connect(triggerLevelValue, SIGNAL(valueChanged(double)), controller_iso, SLOT(setTriggerLevel(double)));
        QObject::connect(controller_iso, SIGNAL(singleShotTriggered(bool)), pausedLabeL_CH1, SLOT(setChecked(bool)));
        QObject::connect(singleShotCheckBox, SIGNAL(toggled(bool)), controller_iso, SLOT(setSingleShotEnabled(bool)));
        QObject::connect(triggerChannelSelect, SIGNAL(currentIndexChanged(int)), controller_iso, SLOT(setTriggerMode(int)));
        QObject::connect(acCoupledLabel_CH1, SIGNAL(toggled(bool)), controller_iso, SLOT(setAC_CH1(bool)));
        QObject::connect(acCoupledLabel_CH2, SIGNAL(toggled(bool)), controller_iso, SLOT(setAC_CH2(bool)));
        QObject::connect(multimeterGroup, SIGNAL(toggled(bool)), bufferDisplay, SLOT(multimeterIn(bool)));
        QObject::connect(bufferDisplay, SIGNAL(multimeterOut(bool)), multimeterGroup, SLOT(setEnabled(bool)));
        QObject::connect(multimeterModeSelect, SIGNAL(currentIndexChanged(int)), controller_iso, SLOT(setMultimeterType(int)));
        QObject::connect(controller_iso, SIGNAL(multimeterMax(double)), multimeterMaxDisplay, SLOT(display(double)));
        QObject::connect(controller_iso, SIGNAL(multimeterMin(double)), multimeterMinDisplay, SLOT(display(double)));
        QObject::connect(controller_iso, SIGNAL(multimeterMean(double)), multimeterMeanDisplay, SLOT(display(double)));
        QObject::connect(multimeterResistanceSelect, SIGNAL(valueChanged(double)), controller_iso, SLOT(setSeriesResistance(double)));
        QObject::connect(controller_iso, SIGNAL(sendMultimeterLabel1(QString)), multimeterMaxLabel, SLOT(setText(QString)));
        QObject::connect(controller_iso, SIGNAL(sendMultimeterLabel2(QString)), multimeterMinLabel, SLOT(setText(QString)));
        QObject::connect(controller_iso, SIGNAL(sendMultimeterLabel3(QString)), multimeterMeanLabel, SLOT(setText(QString)));
        QObject::connect(serialDecodingCheck_CH1, SIGNAL(toggled(bool)), controller_iso, SLOT(setSerialDecodeEnabled_CH1(bool)));
        QObject::connect(serialDecodingCheck_CH2, SIGNAL(toggled(bool)), controller_iso, SLOT(setSerialDecodeEnabled_CH2(bool)));
        QObject::connect(serialDecodingCheck_CH1, SIGNAL(toggled(bool)), console1, SLOT(setVisible(bool)));
        QObject::connect(serialDecodingCheck_CH2, SIGNAL(toggled(bool)), console2, SLOT(setVisible(bool)));
        QObject::connect(controller_iso, SIGNAL(changeTimeAxis(bool)), MainWindow, SLOT(timeBaseNeedsChanging(bool)));
        QObject::connect(xyDisplayLabel, SIGNAL(toggled(bool)), controller_iso, SLOT(setXYmode(bool)));
        QObject::connect(busSnifferGroup_CH2, SIGNAL(toggled(bool)), signalGenGroup_CH2, SLOT(setDisabled(bool)));
        QObject::connect(scopeAxes, SIGNAL(mousePress(QMouseEvent*)), makeCursorsNicer, SLOT(clickDetected(QMouseEvent*)));
        QObject::connect(makeCursorsNicer, SIGNAL(tickHori(bool)), cursorHoriCheck, SLOT(setChecked(bool)));
        QObject::connect(makeCursorsNicer, SIGNAL(tickVert(bool)), cursorVertCheck, SLOT(setChecked(bool)));
        QObject::connect(makeCursorsNicer, SIGNAL(passOnSignal(QMouseEvent*)), controller_iso, SLOT(graphMousePress(QMouseEvent*)));
        QObject::connect(controller_iso, SIGNAL(sendTriggerValue(double)), triggerLevelValue, SLOT(setValue(double)));
        QObject::connect(triggerGroup, SIGNAL(toggled(bool)), controller_iso, SLOT(triggerGroupStateChange(bool)));
        QObject::connect(controller_iso, SIGNAL(disableWindow(bool)), deviceConnected, SLOT(connectedStatusChanged(bool)));
        QObject::connect(multimeterPauseCheckBox, SIGNAL(toggled(bool)), controller_iso, SLOT(pauseEnable_multimeter(bool)));
        QObject::connect(controller_iso, SIGNAL(sendVmax_CH1(double)), voltageInfoMaxDisplay_CH1, SLOT(display(double)));
        QObject::connect(controller_iso, SIGNAL(sendVmin_CH1(double)), voltageInfoMinDisplay_CH1, SLOT(display(double)));
        QObject::connect(controller_iso, SIGNAL(sendVmean_CH1(double)), voltageInfoMeanDisplay_CH1, SLOT(display(double)));
        QObject::connect(controller_iso, SIGNAL(sendVmax_CH2(double)), voltageInfoMaxDisplay_CH2, SLOT(display(double)));
        QObject::connect(controller_iso, SIGNAL(sendVmin_CH2(double)), voltageInfoMinDisplay_CH2, SLOT(display(double)));
        QObject::connect(controller_iso, SIGNAL(sendVmean_CH2(double)), voltageInfoMeanDisplay_CH2, SLOT(display(double)));
        QObject::connect(lockPsuCheckBox, SIGNAL(toggled(bool)), lockPsuCheckBox, SLOT(resetTimer(bool)));
        QObject::connect(lockPsuCheckBox, SIGNAL(toggled(bool)), lockPsuCheckBox, SLOT(resetTimer()));
        QObject::connect(psuSlider, SIGNAL(sliderMoved(int)), lockPsuCheckBox, SLOT(resetTimer()));
        QObject::connect(pause_LA, SIGNAL(toggled(bool)), pausedLabeL_CH1, SLOT(setChecked(bool)));
        QObject::connect(pausedLabeL_CH1, SIGNAL(toggled(bool)), pause_LA, SLOT(setChecked(bool)));
        QObject::connect(controller_fg, SIGNAL(setMaxFreq_CH2(double)), frequencyValue_CH2, SLOT(setMax(double)));
        QObject::connect(controller_fg, SIGNAL(setMinFreq_CH2(double)), frequencyValue_CH2, SLOT(setMin(double)));
        QObject::connect(frequencyValue_CH2, SIGNAL(valueChanged(double)), controller_fg, SLOT(freqUpdate_CH2(double)));
        QObject::connect(frequencyValue_CH1, SIGNAL(valueChanged(double)), controller_fg, SLOT(freqUpdate_CH1(double)));
        QObject::connect(controller_fg, SIGNAL(setMaxFreq_CH1(double)), frequencyValue_CH1, SLOT(setMax(double)));
        QObject::connect(controller_fg, SIGNAL(setMinFreq_CH1(double)), frequencyValue_CH1, SLOT(setMin(double)));
        QObject::connect(frequencyValue_CH1, SIGNAL(valueChanged(double)), frequencyValue_CH1, SLOT(changeStepping(double)));
        QObject::connect(frequencyValue_CH2, SIGNAL(valueChanged(double)), frequencyValue_CH2, SLOT(changeStepping(double)));
        QObject::connect(debugButton2, SIGNAL(clicked()), MainWindow, SLOT(reinitUsb()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "EspoTek Labrador", 0));
        actionGainAuto->setText(QApplication::translate("MainWindow", "Auto", 0));
        actionGain0_5->setText(QApplication::translate("MainWindow", "0.5", 0));
        actionGain1->setText(QApplication::translate("MainWindow", "1", 0));
        actionGain2->setText(QApplication::translate("MainWindow", "2", 0));
        actionGain4->setText(QApplication::translate("MainWindow", "4", 0));
        actionGain8->setText(QApplication::translate("MainWindow", "8", 0));
        actionGain16->setText(QApplication::translate("MainWindow", "16", 0));
        actionGain32->setText(QApplication::translate("MainWindow", "32", 0));
        actionGain64->setText(QApplication::translate("MainWindow", "64", 0));
        actionCalibrate->setText(QApplication::translate("MainWindow", "Calibrate (coming soon!)", 0));
        actionCursor_Stats->setText(QApplication::translate("MainWindow", "Cursor Stats", 0));
        actionMax->setText(QApplication::translate("MainWindow", "Max", 0));
        actionMin->setText(QApplication::translate("MainWindow", "Min", 0));
        actionMean->setText(QApplication::translate("MainWindow", "Mean", 0));
        actionRMS->setText(QApplication::translate("MainWindow", "RMS", 0));
        actionMax_2->setText(QApplication::translate("MainWindow", "Max", 0));
        actionMin_2->setText(QApplication::translate("MainWindow", "Min", 0));
        actionMean_2->setText(QApplication::translate("MainWindow", "Mean", 0));
        actionRMS_2->setText(QApplication::translate("MainWindow", "RMS", 0));
        actionMV->setText(QApplication::translate("MainWindow", "mV", 0));
        actionV->setText(QApplication::translate("MainWindow", "V", 0));
        actionAutoV->setText(QApplication::translate("MainWindow", "Auto", 0));
        actionAutoI->setText(QApplication::translate("MainWindow", "Auto", 0));
        actionMA->setText(QApplication::translate("MainWindow", "mA", 0));
        actionA->setText(QApplication::translate("MainWindow", "A", 0));
        action300->setText(QApplication::translate("MainWindow", "300", 0));
        action600->setText(QApplication::translate("MainWindow", "600", 0));
        action1200->setText(QApplication::translate("MainWindow", "1200", 0));
        action2400->setText(QApplication::translate("MainWindow", "2400", 0));
        action4800->setText(QApplication::translate("MainWindow", "4800", 0));
        action9600->setText(QApplication::translate("MainWindow", "9600", 0));
        action14400->setText(QApplication::translate("MainWindow", "14400", 0));
        action19200->setText(QApplication::translate("MainWindow", "19200", 0));
        action28800->setText(QApplication::translate("MainWindow", "28800", 0));
        action38400->setText(QApplication::translate("MainWindow", "38400", 0));
        action57600->setText(QApplication::translate("MainWindow", "57600 (Glitchy)", 0));
        action115200->setText(QApplication::translate("MainWindow", "115200 (Glitchy)", 0));
        action8->setText(QApplication::translate("MainWindow", "8", 0));
        actionNone->setText(QApplication::translate("MainWindow", "None", 0));
        action300_2->setText(QApplication::translate("MainWindow", "300", 0));
        action600_2->setText(QApplication::translate("MainWindow", "600", 0));
        action1200_2->setText(QApplication::translate("MainWindow", "1200", 0));
        action2400_2->setText(QApplication::translate("MainWindow", "2400", 0));
        action4800_2->setText(QApplication::translate("MainWindow", "4800", 0));
        action9600_2->setText(QApplication::translate("MainWindow", "9600", 0));
        action14400_2->setText(QApplication::translate("MainWindow", "14400", 0));
        action19200_2->setText(QApplication::translate("MainWindow", "19200", 0));
        action28800_2->setText(QApplication::translate("MainWindow", "28800", 0));
        action38400_2->setText(QApplication::translate("MainWindow", "38400", 0));
        action57600_2->setText(QApplication::translate("MainWindow", "57600 (Glitchy)", 0));
        action115200_2->setText(QApplication::translate("MainWindow", "115200 (Glitchy)", 0));
        action8_2->setText(QApplication::translate("MainWindow", "8", 0));
        actionNone_2->setText(QApplication::translate("MainWindow", "None", 0));
        actionRecord->setText(QApplication::translate("MainWindow", "Record", 0));
        actionForce_Square->setText(QApplication::translate("MainWindow", "Force Square Display (Not Officially Supported)", 0));
        actionAutomatically_Enable_Cursors->setText(QApplication::translate("MainWindow", "Enable Cursors on Click", 0));
        action60FPS->setText(QApplication::translate("MainWindow", "60FPS", 0));
        action30FPS->setText(QApplication::translate("MainWindow", "30FPS", 0));
        action20FPS->setText(QApplication::translate("MainWindow", "20FPS", 0));
        action15FPS->setText(QApplication::translate("MainWindow", "15FPS", 0));
        action10FPS->setText(QApplication::translate("MainWindow", "10FPS", 0));
        action5FPS->setText(QApplication::translate("MainWindow", "5FPS", 0));
        actionAuto_Lock->setText(QApplication::translate("MainWindow", "Auto Lock", 0));
        actionSnap_to_Cursors->setText(QApplication::translate("MainWindow", "Snap to Cursors", 0));
        actionEnter_Manually->setText(QApplication::translate("MainWindow", "Enter Manually", 0));
        actionTake_Snapshot->setText(QApplication::translate("MainWindow", "Take Snapshot", 0));
        deviceConnected->setText(QApplication::translate("MainWindow", "Device disconnected!", 0));
        scopeGroup_CH1->setTitle(QApplication::translate("MainWindow", "Oscilloscope CH1", 0));
        pausedLabeL_CH1->setText(QApplication::translate("MainWindow", "Paused", 0));
        acCoupledLabel_CH1->setText(QApplication::translate("MainWindow", "AC Coupled", 0));
        filterLabel_CH1->setText(QApplication::translate("MainWindow", "Filter", 0));
        doubleSampleLabel->setText(QApplication::translate("MainWindow", "Double Sample Rate", 0));
        voltageInfoMaxLabel_CH1->setText(QApplication::translate("MainWindow", " Max", 0));
        voltageInfoMinLabel_CH1->setText(QApplication::translate("MainWindow", " Min", 0));
        VoltageInfoMeanLabel_CH1->setText(QApplication::translate("MainWindow", " Mean", 0));
        voltageInfoRmsLabel_CH1->setText(QApplication::translate("MainWindow", " RMS", 0));
        cursorGroup->setTitle(QApplication::translate("MainWindow", "Cursor", 0));
        cursorHoriCheck->setText(QApplication::translate("MainWindow", "Horizontal", 0));
        cursorVertCheck->setText(QApplication::translate("MainWindow", "Vertical", 0));
        makeCursorsNicer->setText(QApplication::translate("MainWindow", "CURSOR ENABLER", 0));
        scopeGroup_CH2->setTitle(QApplication::translate("MainWindow", "Oscilloscope CH2", 0));
        pausedLabel_CH2->setText(QApplication::translate("MainWindow", "Paused", 0));
        acCoupledLabel_CH2->setText(QApplication::translate("MainWindow", "AC Coupled", 0));
        filterLabel_CH2->setText(QApplication::translate("MainWindow", "Filter", 0));
        xyDisplayLabel->setText(QApplication::translate("MainWindow", "X-Y Display", 0));
        voltageInfoMaxLabel_CH2->setText(QApplication::translate("MainWindow", " Max", 0));
        voltageInfoMinLabel_CH2->setText(QApplication::translate("MainWindow", " Min", 0));
        VoltageInfoMeanLabel_CH2->setText(QApplication::translate("MainWindow", " Mean", 0));
        voltageInfoRmsLabel_CH2->setText(QApplication::translate("MainWindow", " RMS", 0));
        triggerGroup->setTitle(QApplication::translate("MainWindow", "Trigger", 0));
        triggerChannelSelect->clear();
        triggerChannelSelect->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "CH1 (Rising)", 0)
         << QApplication::translate("MainWindow", "CH1 (Falling)", 0)
         << QApplication::translate("MainWindow", "CH2 (Rising)", 0)
         << QApplication::translate("MainWindow", "CH2 (Falling)", 0)
        );
        singleShotCheckBox->setText(QApplication::translate("MainWindow", "Single Shot", 0));
        cursorStatsLabel->setText(QApplication::translate("MainWindow", "cursorStatsLabel", 0));
        multimeterGroup->setTitle(QApplication::translate("MainWindow", "Multimeter++", 0));
        multimeterModeSelect->clear();
        multimeterModeSelect->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "V", 0)
         << QApplication::translate("MainWindow", "I", 0)
         << QApplication::translate("MainWindow", "R", 0)
         << QApplication::translate("MainWindow", "C", 0)
        );
        multimeterMaxLabel->setText(QApplication::translate("MainWindow", " Max", 0));
        multimeterMinLabel->setText(QApplication::translate("MainWindow", " Min", 0));
        multimeterMeanLabel->setText(QApplication::translate("MainWindow", " Mean", 0));
        multimeterRmsLabel->setText(QApplication::translate("MainWindow", " RMS", 0));
        multimeterPauseCheckBox->setText(QApplication::translate("MainWindow", "Paused", 0));
        multimeterResistanceLabel->setText(QApplication::translate("MainWindow", "Series Resistance", 0));
        multimeterModeLabel->setText(QApplication::translate("MainWindow", "Mode", 0));
        multimeterResistanceSelect->setSuffix(QApplication::translate("MainWindow", "\316\251", 0));
        controller_fg->setText(QApplication::translate("MainWindow", "SALUTON MI ESTAS FUNCTION GENERATOR CONTROLLER", 0));
        signalGenGroup_CH1->setTitle(QApplication::translate("MainWindow", "Signal Gen CH1", 0));
        waveformLabel_CH1->setText(QApplication::translate("MainWindow", "Waveform", 0));
        frequencyLabel_CH1->setText(QApplication::translate("MainWindow", "Frequency", 0));
        amplitudeLabel_CH1->setText(QApplication::translate("MainWindow", "Amplitude (Peak-Peak)", 0));
        amplitudeValue_CH1->setSuffix(QApplication::translate("MainWindow", "V", 0));
        dcOffsetLabel_CH1->setText(QApplication::translate("MainWindow", "Offset", 0));
        dcOffsetValue_CH1->setSuffix(QApplication::translate("MainWindow", "V", 0));
        signalGenGroup_CH2->setTitle(QApplication::translate("MainWindow", "Signal Gen CH2", 0));
        waveformLabel_CH2->setText(QApplication::translate("MainWindow", "Waveform", 0));
        frequencyLabel_CH2->setText(QApplication::translate("MainWindow", "Frequency", 0));
        amplitudeLabel_CH2->setText(QApplication::translate("MainWindow", "Amplitude (Peak-Peak)", 0));
        amplitudeValue_CH2->setSuffix(QApplication::translate("MainWindow", "V", 0));
        dcOffsetLabel_CH2->setText(QApplication::translate("MainWindow", "Offset", 0));
        dcOffsetValue_CH2->setSuffix(QApplication::translate("MainWindow", "V", 0));
        controller_iso->setText(QApplication::translate("MainWindow", "SALUTON MI ESTAS ISO DRIVER", 0));
        psuGroup->setTitle(QApplication::translate("MainWindow", "PSU", 0));
        lockPsuCheckBox->setText(QApplication::translate("MainWindow", "Lock PSU", 0));
        busSifferGroup_CH1->setTitle(QApplication::translate("MainWindow", "Logic Analyzer CH1", 0));
        pause_LA->setText(QApplication::translate("MainWindow", "Pause", 0));
        serialDecodingCheck_CH1->setTitle(QApplication::translate("MainWindow", "Serial Decoding", 0));
        serialDecodingModeSelect_CH1->clear();
        serialDecodingModeSelect_CH1->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "UART", 0)
         << QApplication::translate("MainWindow", "SPI", 0)
         << QApplication::translate("MainWindow", "I2C", 0)
        );
        busSnifferGroup_CH2->setTitle(QApplication::translate("MainWindow", "Logic Analyzer CH2", 0));
        serialDecodingCheck_CH2->setTitle(QApplication::translate("MainWindow", "Serial Decoding", 0));
        serialDecodingModeSelect_CH2->clear();
        serialDecodingModeSelect_CH2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "UART", 0)
         << QApplication::translate("MainWindow", "SPI", 0)
         << QApplication::translate("MainWindow", "I2C", 0)
        );
        digitalOutputGroup->setTitle(QApplication::translate("MainWindow", "Digital Output", 0));
        digitalOutCheckbox_CH3->setText(QApplication::translate("MainWindow", "Pin 3", 0));
        digitalOutCheckbox_CH2->setText(QApplication::translate("MainWindow", "Pin 2", 0));
        digitalOutCheckbox_CH1->setText(QApplication::translate("MainWindow", "Pin 1", 0));
        digitalOutCheckbox_CH4->setText(QApplication::translate("MainWindow", "Pin 4", 0));
        debugButton1->setText(QApplication::translate("MainWindow", "Debug!", 0));
        debugButton2->setText(QApplication::translate("MainWindow", "ReinitUsb()", 0));
        bufferDisplay->setText(QApplication::translate("MainWindow", "BUFFER IMAGE HERE", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuOscilloscope_2->setTitle(QApplication::translate("MainWindow", "Oscilloscope", 0));
        menuGain_2->setTitle(QApplication::translate("MainWindow", "Gain", 0));
        menuCH1_Stats->setTitle(QApplication::translate("MainWindow", "CH1 Stats", 0));
        menuCH2_Stats->setTitle(QApplication::translate("MainWindow", "CH2 Stats", 0));
        menuFrame_rate->setTitle(QApplication::translate("MainWindow", "Frame rate", 0));
        menuRange->setTitle(QApplication::translate("MainWindow", "Range", 0));
        menuMultimeter_2->setTitle(QApplication::translate("MainWindow", "Multimeter", 0));
        menuV_2->setTitle(QApplication::translate("MainWindow", "Range (V)", 0));
        menuI_2->setTitle(QApplication::translate("MainWindow", "Range (I)", 0));
        menuBus_Sniffer->setTitle(QApplication::translate("MainWindow", "Logic Analyzer", 0));
        menuUART_1->setTitle(QApplication::translate("MainWindow", "UART 1", 0));
        menuBaud_Rate->setTitle(QApplication::translate("MainWindow", "Baud Rate", 0));
        menuType_Here_2->setTitle(QApplication::translate("MainWindow", "Type Here", 0));
        menuParity_Bit->setTitle(QApplication::translate("MainWindow", "Parity Bit", 0));
        menuData_Bits->setTitle(QApplication::translate("MainWindow", "Data Bits", 0));
        menuUART_2->setTitle(QApplication::translate("MainWindow", "UART 2", 0));
        menuBaud_Rate_2->setTitle(QApplication::translate("MainWindow", "Baud Rate", 0));
        menuData_Bits_2->setTitle(QApplication::translate("MainWindow", "Data Bits", 0));
        menuParity_Bit_2->setTitle(QApplication::translate("MainWindow", "Parity Bit", 0));
        menuPower_Supply->setTitle(QApplication::translate("MainWindow", "Power Supply", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
