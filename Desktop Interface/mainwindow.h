#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QAction>
#include <QShortcut>
#include <QFont>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QThread>
#include <QPalette>
#include <QDebug>
#include <QBrush>
#include <QGridLayout>

#include <math.h>
#include "qcustomplot.h"

#include "platformspecific.h"
#include "qcustomplot.h"
#include "ui_mainwindow.h"
#include "scoperangeenterdialog.h"
#include "isobuffer.h"
#include "q_debugstream.h"


//The Main Window object.  This has a lot of control information too (keyboard shortcuts etc.)!



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void resizeEvent(QResizeEvent *event);
private slots:
    //Oscilloscope
    void on_actionGain0_5_triggered();
    void on_actionGain1_triggered();
    void on_actionGain2_triggered();
    void on_actionGain4_triggered();
    void on_actionGain8_triggered();
    void on_actionGain16_triggered();
    void on_actionGain32_triggered();
    void on_actionGain64_triggered();
    void on_actionGainAuto_triggered();
    void on_actionCursor_Stats_triggered(bool checked);
    void on_actionAutomatically_Enable_Cursors_toggled(bool arg1);
    void on_action60FPS_toggled(bool enabled);
    void on_action30FPS_toggled(bool enabled);
    void on_action20FPS_toggled(bool enabled);
    void on_action15FPS_toggled(bool enabled);
    void on_action10FPS_toggled(bool enabled);
    void on_action5FPS_toggled(bool enabled);
    void on_actionSnap_to_Cursors_triggered();
    void on_actionEnter_Manually_triggered();

    void connectDisplaySignals();

    //Logic Analyzer
    void on_action300_toggled(bool arg1);
    void on_action600_toggled(bool arg1);
    void on_action1200_toggled(bool arg1);
    void on_action2400_toggled(bool arg1);
    void on_action4800_toggled(bool arg1);
    void on_action9600_toggled(bool arg1);
    void on_action14400_toggled(bool arg1);
    void on_action19200_toggled(bool arg1);
    void on_action28800_toggled(bool arg1);
    void on_action38400_toggled(bool arg1);
    void on_action57600_toggled(bool arg1);
    void on_action115200_toggled(bool arg1);

    void on_action300_2_toggled(bool arg1);
    void on_action600_2_toggled(bool arg1);
    void on_action1200_2_toggled(bool arg1);
    void on_action2400_2_toggled(bool arg1);
    void on_action4800_2_toggled(bool arg1);
    void on_action9600_2_toggled(bool arg1);
    void on_action14400_2_toggled(bool arg1);
    void on_action19200_2_toggled(bool arg1);
    void on_action28800_2_toggled(bool arg1);
    void on_action38400_2_toggled(bool arg1);
    void on_action57600_2_toggled(bool arg1);
    void on_action115200_2_toggled(bool arg1);
    void cycleBaudRate_CH1();
    void cycleBaudRateBackwards_CH1();
    void cycleBaudRate_CH2();
    void cycleBaudRateBackwards_CH2();

    //Deprecated/Unsupported
    void timeBaseNeedsChanging(bool positive);
    void on_actionForce_Square_triggered(bool checked);
    void helloWorld();

    //Keyboard Shortcuts
    void arrowUpTriggered();
    void arrowDownTriggered();
    void ctrlArrowUpTriggered();
    void ctrlArrowDownTriggered();
    void cycleDelayLeft();
    void cycleDelayRight();
    void enableLabradorDebugging();

    //Power Supply
    void on_actionAuto_Lock_toggled(bool arg1);

    //File/other
    void on_actionRecord_triggered(bool checked);
    void on_actionTake_Snapshot_triggered();
    void reinitUsb(void);
private:
    //Generic Vars
    Ui::MainWindow *ui;
    QWheelEvent *wheelEmu;
    bool forceSquare = false;
    QCPItemText *textLabel;
    QDir *outputDir;
    QFile *output375_CH1, *output375_CH2, *output750;

    //Generic Functions
    void initialisePlot();
    void labelPsu();
    void menuSetup();
    void initShortcuts();
    void readSettingsFile();

    //Shortcut pointers
    QActionGroup *gainGroup;
    QActionGroup *rangeGroupV;
    QActionGroup *rangeGroupI;
    QActionGroup *uartBaudGroup_CH1;
    QActionGroup *uartBaudGroup_CH2;
    QActionGroup *fpsGroup;
    QShortcut *shortcut_cycleBaudRate_CH1;
    QShortcut *shortcut_cycleBaudRateBackwards_CH1;
    QShortcut *shortcut_cycleBaudRate_CH2;
    QShortcut *shortcut_cycleBaudRateBackwards_CH2;
    QShortcut *shortcut_ArrowUp;
    QShortcut *shortcut_ArrowDown;
    QShortcut *shortcut_CtrlArrowUp;
    QShortcut *shortcut_CtrlArrowDown;
    QShortcut *shortcut_w;
    QShortcut *shortcut_ctrlW;
    QShortcut *shortcut_s;
    QShortcut *shortcut_ctrlS;
    QShortcut *shortcut_a;
    QShortcut *shortcut_d;
    QShortcut *shortcut_ArrowLeft;
    QShortcut *shortcut_ArrowRight;
    QShortcut *shortcut_snapScopeToCursors;\
    QShortcut *shortcut_manualRange;
    QShortcut *shortcut_snapshot;
    QShortcut *shortcut_Debug;
};

#endif // MAINWINDOW_H
