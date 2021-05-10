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

#ifndef ESPOSLIDER_H
#define ESPOSLIDER_H

#include <QSlider>
#include <QString>
#include <QDebug>
#include <QLabel>
#include <QLayout>
#include <QString>

//espoSlider is a slider but with the ticks placed at the same position as the numbers.  Nothing more, nothing less.

class espoSlider : public QSlider
{
    Q_OBJECT
public:
    explicit espoSlider(QWidget *parent = 0);
    bool setTickLabel(QString label, int position);
    void resizeEvent(QResizeEvent *event);
    void moveEvent(QMoveEvent *event);
    void setTickInterval(int ti);
    int maxTick();
    int maxTick(int ti);
private:
    int debug_var = 0;
    void rearrange();
    std::vector<QLabel*> addressBook;
    QWidget* windowPointer;
    int labelMargin;
signals:
    void lcdOut(QString values);
    void voltageChanged(double newVoltage);
public slots:
    void selfMoved(int newval);
    void poke(void);
};

#endif // ESPOSLIDER_H
