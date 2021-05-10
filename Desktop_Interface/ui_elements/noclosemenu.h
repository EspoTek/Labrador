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

#ifndef NOCLOSEMENU_H
#define NOCLOSEMENU_H

#include <QWidget>
#include <QMenu>

//The menubar in Qt closes by default once a box has been checked.
//noCloseMenu is a simple class that keeps the menu open even after a box is checked.

class noCloseMenu : public QMenu
{
    Q_OBJECT
public:
    explicit noCloseMenu(QWidget *parent = 0);
private:
    void mouseReleaseEvent(QMouseEvent *e);
signals:

public slots:
};

#endif // NOCLOSEMENU_H
