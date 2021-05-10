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

#ifndef DAQLOADPROMPT_H
#define DAQLOADPROMPT_H

#include <QDialog>

namespace Ui {
class daqLoadPrompt;
}

class daqLoadPrompt : public QDialog
{
    Q_OBJECT

public:
    explicit daqLoadPrompt(QWidget *parent, double minTime, double maxTime);
    ~daqLoadPrompt();

private:
    double min_interval;
    Ui::daqLoadPrompt *ui;
signals:
    void startTime(double);
    void endTime(double);

public slots:
    void valueChange(void);
};

#endif // DAQLOADPROMPT_H
