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

#ifndef TIMEDTICKBOX_H
#define TIMEDTICKBOX_H

#include <QCheckBox>
#include <QTimer>
#include <QDebug>

//timedTickBox is used to re-lock the power supply after a few seconds.
//It's just a tickbox with a timer on it.

class timedTickBox : public QCheckBox
{
    Q_OBJECT
public:
    explicit timedTickBox(QWidget *parent = 0);
    bool timerEnabled = true;
    int timerLength = 7500;
    QTimer *timer = NULL;

signals:

public slots:
    void resetTimer();
    void timerTick();
    void enableTimer(bool enabled);
};

#endif // TIMEDTICKBOX_H
