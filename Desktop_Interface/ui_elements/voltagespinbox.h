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

#ifndef VOLTAGESPINBOX_H
#define VOLTAGESPINBOX_H

#include <QWidget>
#include <QSpinBox>

//Wrapper for the spinboxes on the "Enter Scope Range" dialog (Oscilloscope->Range->Enter Manually; shortcut is "M").
//It needs to exist in order to map the setMaximum() and setMinimum() functions for QDOubleSpinbox to slots.

class voltageSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit voltageSpinBox(QWidget *parent = 0);
    bool min = false;
signals:

public slots:
    void setMax(double newMax);
    void setMin(double newMin);
};

#endif // VOLTAGESPINBOX_H
