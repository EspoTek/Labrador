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

#ifndef ESPOCOMBOBOX_H
#define ESPOCOMBOBOX_H

#include <QWidget>
#include <QComboBox>
#include <QDebug>
#include <QDir>
#include <QFile>
#include "platformspecific.h"

//espoComboBox is a combo box that reads its contents externally from the waveforms file.

class espoComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit espoComboBox(QWidget *parent = 0);
    void readWaveformList(void);
private:
signals:

public slots:
};

#endif // ESPOCOMBOBOX_H
