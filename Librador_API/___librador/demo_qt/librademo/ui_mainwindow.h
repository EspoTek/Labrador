/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_6;
    QPushButton *pushButton_4;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_9;
    QDoubleSpinBox *powerSupplySpinBox;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QComboBox *comboBox_3;
    QVBoxLayout *verticalLayout_8;
    QPushButton *pushButton_5;
    QPushButton *pushButton_15;
    QPushButton *pushButton_14;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox_frequency;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBox_amplitude;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox_offset;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_5;
    QComboBox *comboBox_signal_gen_type;
    QVBoxLayout *verticalLayout_7;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QCustomPlot *widget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 720);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        verticalLayout->addWidget(pushButton_6);

        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);

        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        verticalLayout->addWidget(pushButton_7);

        pushButton_8 = new QPushButton(centralWidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));

        verticalLayout->addWidget(pushButton_8);

        pushButton_10 = new QPushButton(centralWidget);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));

        verticalLayout->addWidget(pushButton_10);

        pushButton_11 = new QPushButton(centralWidget);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));

        verticalLayout->addWidget(pushButton_11);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_9 = new QPushButton(centralWidget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));

        horizontalLayout_3->addWidget(pushButton_9);

        powerSupplySpinBox = new QDoubleSpinBox(centralWidget);
        powerSupplySpinBox->setObjectName(QString::fromUtf8("powerSupplySpinBox"));
        powerSupplySpinBox->setMinimum(5.000000000000000);
        powerSupplySpinBox->setMaximum(12.000000000000000);

        horizontalLayout_3->addWidget(powerSupplySpinBox);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_2->addWidget(checkBox);

        checkBox_2 = new QCheckBox(centralWidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        horizontalLayout_2->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(centralWidget);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        horizontalLayout_2->addWidget(checkBox_3);

        checkBox_4 = new QCheckBox(centralWidget);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));

        horizontalLayout_2->addWidget(checkBox_4);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label);

        comboBox = new QComboBox(centralWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_4->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_2);

        comboBox_2 = new QComboBox(centralWidget);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        horizontalLayout_5->addWidget(comboBox_2);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        comboBox_3 = new QComboBox(centralWidget);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));

        verticalLayout_2->addWidget(comboBox_3);


        horizontalLayout_6->addLayout(verticalLayout_2);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        verticalLayout_8->addWidget(pushButton_5);

        pushButton_15 = new QPushButton(centralWidget);
        pushButton_15->setObjectName(QString::fromUtf8("pushButton_15"));

        verticalLayout_8->addWidget(pushButton_15);

        pushButton_14 = new QPushButton(centralWidget);
        pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));

        verticalLayout_8->addWidget(pushButton_14);


        horizontalLayout_6->addLayout(verticalLayout_8);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_3->addWidget(label_4);

        doubleSpinBox_frequency = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_frequency->setObjectName(QString::fromUtf8("doubleSpinBox_frequency"));

        verticalLayout_3->addWidget(doubleSpinBox_frequency);


        horizontalLayout_7->addLayout(verticalLayout_3);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_5->addWidget(label_6);

        doubleSpinBox_amplitude = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_amplitude->setObjectName(QString::fromUtf8("doubleSpinBox_amplitude"));
        doubleSpinBox_amplitude->setMaximum(10.000000000000000);

        verticalLayout_5->addWidget(doubleSpinBox_amplitude);


        horizontalLayout_7->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_6->addWidget(label_7);

        doubleSpinBox_offset = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_offset->setObjectName(QString::fromUtf8("doubleSpinBox_offset"));
        doubleSpinBox_offset->setMaximum(10.000000000000000);

        verticalLayout_6->addWidget(doubleSpinBox_offset);


        horizontalLayout_7->addLayout(verticalLayout_6);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_4->addWidget(label_5);

        comboBox_signal_gen_type = new QComboBox(centralWidget);
        comboBox_signal_gen_type->addItem(QString());
        comboBox_signal_gen_type->addItem(QString());
        comboBox_signal_gen_type->addItem(QString());
        comboBox_signal_gen_type->addItem(QString());
        comboBox_signal_gen_type->setObjectName(QString::fromUtf8("comboBox_signal_gen_type"));

        verticalLayout_4->addWidget(comboBox_signal_gen_type);


        horizontalLayout_7->addLayout(verticalLayout_4);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        pushButton_12 = new QPushButton(centralWidget);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));

        verticalLayout_7->addWidget(pushButton_12);

        pushButton_13 = new QPushButton(centralWidget);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));

        verticalLayout_7->addWidget(pushButton_13);


        horizontalLayout_7->addLayout(verticalLayout_7);


        verticalLayout->addLayout(horizontalLayout_7);


        horizontalLayout->addLayout(verticalLayout);

        widget = new QCustomPlot(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));

        horizontalLayout->addWidget(widget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Open API", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "Close API", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "Setup USB", nullptr));
        pushButton_6->setText(QApplication::translate("MainWindow", "Reset USB", nullptr));
        pushButton_4->setText(QApplication::translate("MainWindow", "avrDebug()", nullptr));
        pushButton_7->setText(QApplication::translate("MainWindow", "Get Firmware Version", nullptr));
        pushButton_8->setText(QApplication::translate("MainWindow", "Get Firmware Variant", nullptr));
        pushButton_10->setText(QApplication::translate("MainWindow", "Reset Labrador", nullptr));
        pushButton_11->setText(QApplication::translate("MainWindow", "Go to bootloader", nullptr));
        pushButton_9->setText(QApplication::translate("MainWindow", "Send Power Supply Voltage", nullptr));
        checkBox->setText(QApplication::translate("MainWindow", "Digital Out 1", nullptr));
        checkBox_2->setText(QApplication::translate("MainWindow", "Digital Out 2", nullptr));
        checkBox_3->setText(QApplication::translate("MainWindow", "Digital Out 3", nullptr));
        checkBox_4->setText(QApplication::translate("MainWindow", "Digital Out 4", nullptr));
        label->setText(QApplication::translate("MainWindow", "Set Gain:", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "0.5", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "1", nullptr));
        comboBox->setItemText(2, QApplication::translate("MainWindow", "2", nullptr));
        comboBox->setItemText(3, QApplication::translate("MainWindow", "4", nullptr));
        comboBox->setItemText(4, QApplication::translate("MainWindow", "8", nullptr));
        comboBox->setItemText(5, QApplication::translate("MainWindow", "16", nullptr));
        comboBox->setItemText(6, QApplication::translate("MainWindow", "32", nullptr));
        comboBox->setItemText(7, QApplication::translate("MainWindow", "64", nullptr));

        comboBox->setCurrentText(QApplication::translate("MainWindow", "0.5", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Set Mode", nullptr));
        comboBox_2->setItemText(0, QApplication::translate("MainWindow", "0", nullptr));
        comboBox_2->setItemText(1, QApplication::translate("MainWindow", "1", nullptr));
        comboBox_2->setItemText(2, QApplication::translate("MainWindow", "2", nullptr));
        comboBox_2->setItemText(3, QApplication::translate("MainWindow", "3", nullptr));
        comboBox_2->setItemText(4, QApplication::translate("MainWindow", "4", nullptr));
        comboBox_2->setItemText(5, QApplication::translate("MainWindow", "5", nullptr));
        comboBox_2->setItemText(6, QApplication::translate("MainWindow", "6", nullptr));
        comboBox_2->setItemText(7, QApplication::translate("MainWindow", "7", nullptr));

        label_3->setText(QApplication::translate("MainWindow", "Channel", nullptr));
        comboBox_3->setItemText(0, QApplication::translate("MainWindow", "1", nullptr));
        comboBox_3->setItemText(1, QApplication::translate("MainWindow", "2", nullptr));
        comboBox_3->setItemText(2, QApplication::translate("MainWindow", "Both", nullptr));

        pushButton_5->setText(QApplication::translate("MainWindow", "Get Scope Data (1s)", nullptr));
        pushButton_15->setText(QApplication::translate("MainWindow", "Get Digital (1s)", nullptr));
        pushButton_14->setText(QApplication::translate("MainWindow", "Get Scope Data (SinceLast)", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Frequency (Hz)", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Amplitude (V)", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Offset(V)", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Type", nullptr));
        comboBox_signal_gen_type->setItemText(0, QApplication::translate("MainWindow", "Sin", nullptr));
        comboBox_signal_gen_type->setItemText(1, QApplication::translate("MainWindow", "Square", nullptr));
        comboBox_signal_gen_type->setItemText(2, QApplication::translate("MainWindow", "Triangle", nullptr));
        comboBox_signal_gen_type->setItemText(3, QApplication::translate("MainWindow", "Sawtooth", nullptr));

        pushButton_12->setText(QApplication::translate("MainWindow", "Send CH1", nullptr));
        pushButton_13->setText(QApplication::translate("MainWindow", "Send CH2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
