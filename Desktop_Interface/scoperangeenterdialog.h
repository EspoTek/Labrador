// Copyright (C) 2017, 2018, 2019, 2020, 2021 Christopher Paul Esposito
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef SCOPERANGEENTERDIALOG_H
#define SCOPERANGEENTERDIALOG_H

#include <QDialog>
#include <QDebug>
#include "desktop_settings.h"

//ScopeRangeEnterDialog is the class for the "Enter Scope Range" dialog (Oscilloscope->Range->Enter Manually; shortcut is "M").
//This code in particular controls the voltageSpinBoxes in the dialog, to ensure they don't go out of range.

namespace Ui {
class scopeRangeEnterDialog;
}

class scopeRangeEnterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit scopeRangeEnterDialog(QWidget *parent = 0, bool buttonVisible = true, double yTop = 20, double yBot = -20, double window = -10, double delay = 0);
    ~scopeRangeEnterDialog();

private:
    Ui::scopeRangeEnterDialog *ui;
    double delay = 130065506;
    double timeWindow = 130065506;
    double yBot = 130065506;
    double yTop = 130065506;

signals:
    void yTopUpdated(double val);
    void yBotUpdated(double val);
    void windowUpdated(double val);
    void delayUpdated(double val);
private slots:
    void toUpdateYTop(double val);
    void toUpdateYBot(double val);
    void toUpdateWindow(double val);
    void toUpdateDelay(double val);
    void yTopChanged(double val);
    void yBotChanged(double val);
    void windowChanged(double val);
    void delayChanged(double val);
};

#endif // SCOPERANGEENTERDIALOG_H
