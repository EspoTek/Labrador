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

#ifndef SWIPEYSTACK_H
#define SWIPEYSTACK_H

#include <QStackedWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QDateTime>

#define SWIPEYSTACK_MIN_DELTAX 20
#define SWIPEYSTACK_MAX_DRAG_TIME 500


class swipeyStack : public QStackedWidget
{
    Q_OBJECT
public:
    explicit swipeyStack(QWidget *parent = 0);
private:
    int initial_x;
    int initial_y;
    qint64 initial_epochTime;
    bool wrapEnabled = true;
signals:

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enableWrapping(bool enabled);
    void cycleStack(int delta);
};

#endif // SWIPEYSTACK_H
