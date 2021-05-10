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

#ifndef DEVICECONNECTEDDISPLAY_H
#define DEVICECONNECTEDDISPLAY_H

#include <QWidget>
#include <QLabel>
#include <QDebug>

//deviceConnectedDisplay simply displays the "device connected" message.

class deviceConnectedDisplay : public QLabel
{
    Q_OBJECT
public:
    explicit deviceConnectedDisplay(QWidget *parent = 0);
signals:
public slots:
    void connectedStatusChanged(bool status);
    void flashingFirmware(void);
};

#endif // DEVICECONNECTEDDISPLAY_H
