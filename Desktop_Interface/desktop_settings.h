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

#ifndef DESKTOP_SETTINGS_H
#define DESKTOP_SETTINGS_H

#include <QMutex>
#include <algorithm>

//Just a whole lot of variables not directly related to xmega.

//USB iso stuff
extern int MAX_TRANSFER_SIZE;
extern int MAX_PENDING_TRANSFERS;
extern int MAX_PENDING_IO;

//Plot settings
extern int GRAPH_SAMPLES;
extern int TIMER_PERIOD;
extern int ISO_RECOVERY_TIME;
extern int MAX_WINDOW_SIZE;
extern int TICK_SEPARATION;

//Multimeter settings
extern int MULTIMETER_PERIOD;

extern double SERIAL_DELAY;

extern QMutex tcBlockMutex;
extern QMutex unixDriverDeleteMutex;
extern struct timeval tv;

extern unsigned char expected_variant;

#define DEBUG_SETTINGSDOTSET

#define USB_RECONNECT_PERIOD 420

#define VALID_DATA_PER_375 375

#define VALID_DATA_PER_750 750

#define COLUMN_BREAK VALID_DATA_PER_750

//#define MAX_CONSOLE_BLOCK_COUNT 512
#define SERIAL_BUFFER_LENGTH 8192

#define ANDROID_SCALE_INSENSITIVITY 1.2

#define NUM_BYTES_STORED_PER_DAQ_SAMPLE 9

#endif // DESKTOP_SETTINGS_H

