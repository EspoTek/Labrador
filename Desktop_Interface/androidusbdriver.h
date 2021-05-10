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

#ifndef androidUsbDriver_H
#define androidUsbDriver_H

#include <QWidget>
#include <QThread>
#include <QMutex>
#include <QDateTime>

#include "unixusbdriver.h"
#include "libusb.h"
#include <QAndroidJniObject>
#include <QtAndroid>


class androidUsbDriver : public unixUsbDriver
{
    Q_OBJECT
public:
    explicit androidUsbDriver(QWidget *parent = 0);
    ~androidUsbDriver();
private:
    //Generic Functions
    QAndroidJniObject mainActivity;
    unsigned char usbInit(unsigned long VIDin, unsigned long PIDin);
    int flashFirmware(void);
    int get_new_bootloader_ctx(libusb_device **device_ptr, libusb_device_handle **handle, libusb_context **ctx);
};

#endif // unixUsbDriver_H
