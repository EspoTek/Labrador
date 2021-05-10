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

#include "noclosemenu.h"

noCloseMenu::noCloseMenu(QWidget *parent) : QMenu(parent)
{

}

//Dankon, Jakob Leben
//http://stackoverflow.com/questions/2050462/prevent-a-qmenu-from-closing-when-one-of-its-qaction-is-triggered

void noCloseMenu::mouseReleaseEvent(QMouseEvent *e)
{
    QAction *action = activeAction();
    if (action && action->isEnabled()) {
        action->setEnabled(false);
        QMenu::mouseReleaseEvent(e);
        action->setEnabled(true);
        action->trigger();
    }
    else
        QMenu::mouseReleaseEvent(e);
}
