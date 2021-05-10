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

#include "desktop_settings.h"

//USB iso stuff
int MAX_TRANSFER_SIZE = 1023;
int MAX_PENDING_TRANSFERS = 512;
int MAX_PENDING_IO = 16;

//Plot settings
int GRAPH_SAMPLES = 1024;
int TIMER_PERIOD = 17;
int ISO_RECOVERY_TIME = (200);
int MAX_WINDOW_SIZE = 10;
int TICK_SEPARATION = 96;

//Multimeter settings
int MULTIMETER_PERIOD = 500;

double SERIAL_DELAY = 0.01;  //100 baud?

QMutex tcBlockMutex;
QMutex unixDriverDeleteMutex;

unsigned char expected_variant;

#ifndef PLATFORM_WINDOWS
struct timeval tv;
#endif

