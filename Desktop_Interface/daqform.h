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

#ifndef DAQFORM_H
#define DAQFORM_H

#include <QDialog>

namespace Ui {
class daqForm;
}

class daqForm : public QDialog
{
    Q_OBJECT

public:
    explicit daqForm(QWidget *parent, int initialAverage, qulonglong initialMaxFileSize);
    ~daqForm();
signals:
    void updatedAveraging(int);
    void updatedMaxFileSize(qulonglong);
    void saveButtonPressed();
private:
    Ui::daqForm *ui;
private slots:
    void updateLabels();
    void updateValues();
    void trigger_saveButtonPressed();
};

#endif // DAQFORM_H
