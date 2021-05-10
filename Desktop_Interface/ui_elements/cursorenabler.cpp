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

#include "cursorenabler.h"
#include "platformspecific.h"

cursorEnabler::cursorEnabler(QWidget *parent) : QLabel(parent)
{
    this->setVisible(0);
#ifdef PLATFORM_ANDROID
    this->m_turnedOn = false;
#endif
}

void cursorEnabler::setTurnedOn(bool enabled){
    m_turnedOn = enabled;
    #ifdef PLATFORM_ANDROID
        this->m_turnedOn = false;
    #endif
}

void cursorEnabler::clickDetected(QMouseEvent* event){
    if(m_turnedOn){
        if (event->button() == Qt::LeftButton)
        {
            tickHori(1);
        }
        else if (event->button() == Qt::RightButton)
        {
            tickVert(1);
        }
    }
    passOnSignal(event);
}
