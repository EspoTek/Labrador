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

#ifndef ESPOSPINBOX_H
#define ESPOSPINBOX_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <math.h>

//espoSpinBox is a subclass of QSpinbox.  It can talk to other espoSpinBoxes and change their min/max values.

class espoSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit espoSpinBox(QWidget *parent = 0);
	QValidator::State validate(QString& text, int& pos) const override;
private:
    QString textFromValue(double value) const override;
	double valueFromText(const QString &text) const override;
	mutable double lastValidValue = -1;
signals:

public slots:
    void maximumChanged(double linked);
    void setMax(double newMax);
    void setMin(double newMin);
    void changeStepping(double value);
};

#endif // ESPOSPINBOX_H
