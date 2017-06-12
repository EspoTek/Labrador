/********************************************************************************
** Form generated from reading UI file 'scoperangeenterdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCOPERANGEENTERDIALOG_H
#define UI_SCOPERANGEENTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <voltagespinbox.h>

QT_BEGIN_NAMESPACE

class Ui_scopeRangeEnterDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    voltageSpinBox *vMaxBox;
    QLabel *label;
    voltageSpinBox *vMinBox;
    QLabel *label_2;
    voltageSpinBox *timeWindowBox;
    QLabel *label_3;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *scopeRangeEnterDialog)
    {
        if (scopeRangeEnterDialog->objectName().isEmpty())
            scopeRangeEnterDialog->setObjectName(QStringLiteral("scopeRangeEnterDialog"));
        scopeRangeEnterDialog->resize(187, 147);
        verticalLayout_2 = new QVBoxLayout(scopeRangeEnterDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        vMaxBox = new voltageSpinBox(scopeRangeEnterDialog);
        vMaxBox->setObjectName(QStringLiteral("vMaxBox"));
        vMaxBox->setMinimum(20);
        vMaxBox->setMaximum(20);

        formLayout->setWidget(0, QFormLayout::LabelRole, vMaxBox);

        label = new QLabel(scopeRangeEnterDialog);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::FieldRole, label);

        vMinBox = new voltageSpinBox(scopeRangeEnterDialog);
        vMinBox->setObjectName(QStringLiteral("vMinBox"));
        vMinBox->setMinimum(-20);
        vMinBox->setMaximum(-20);

        formLayout->setWidget(1, QFormLayout::LabelRole, vMinBox);

        label_2 = new QLabel(scopeRangeEnterDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::FieldRole, label_2);

        timeWindowBox = new voltageSpinBox(scopeRangeEnterDialog);
        timeWindowBox->setObjectName(QStringLiteral("timeWindowBox"));
        timeWindowBox->setDecimals(6);
        timeWindowBox->setMinimum(1e-6);
        timeWindowBox->setMaximum(10);

        formLayout->setWidget(2, QFormLayout::LabelRole, timeWindowBox);

        label_3 = new QLabel(scopeRangeEnterDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::FieldRole, label_3);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(scopeRangeEnterDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(scopeRangeEnterDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), scopeRangeEnterDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), scopeRangeEnterDialog, SLOT(reject()));
        QObject::connect(vMaxBox, SIGNAL(valueChanged(double)), scopeRangeEnterDialog, SLOT(toUpdateYTop(double)));
        QObject::connect(vMinBox, SIGNAL(valueChanged(double)), scopeRangeEnterDialog, SLOT(toUpdateYBot(double)));
        QObject::connect(vMaxBox, SIGNAL(valueChanged(double)), vMinBox, SLOT(setMax(double)));
        QObject::connect(vMinBox, SIGNAL(valueChanged(double)), vMaxBox, SLOT(setMin(double)));
        QObject::connect(timeWindowBox, SIGNAL(valueChanged(double)), scopeRangeEnterDialog, SLOT(toUpdateWindow(double)));

        QMetaObject::connectSlotsByName(scopeRangeEnterDialog);
    } // setupUi

    void retranslateUi(QDialog *scopeRangeEnterDialog)
    {
        scopeRangeEnterDialog->setWindowTitle(QApplication::translate("scopeRangeEnterDialog", "Enter Scope Range", Q_NULLPTR));
        label->setText(QApplication::translate("scopeRangeEnterDialog", "Vmax", Q_NULLPTR));
        label_2->setText(QApplication::translate("scopeRangeEnterDialog", "Vmin", Q_NULLPTR));
        label_3->setText(QApplication::translate("scopeRangeEnterDialog", "Time Window", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class scopeRangeEnterDialog: public Ui_scopeRangeEnterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCOPERANGEENTERDIALOG_H
