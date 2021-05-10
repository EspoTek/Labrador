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

#ifndef WINUSBDRIVER_H
#define WINUSBDRIVER_H

//libusbK includes
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "libusbk.h"

#include "genericusbdriver.h"

//winUsbDriver handles the Windows-specific parts of USB communication, through libusbK.
//See genericUsbDriver for the non-platform-specific parts.
class winUsbDriver : public genericUsbDriver
{
    Q_OBJECT
public:
    //Generic Functions
    explicit winUsbDriver(QWidget *parent = 0);
    ~winUsbDriver();
    void usbSendControl(uint8_t RequestType, uint8_t Request, uint16_t Value, uint16_t Index, uint16_t Length, unsigned char *LDATA);
    char *isoRead(unsigned int *newLength);
    void manualFirmwareRecovery(void);
private:
    //USB Vars
    KUSB_HANDLE handle = NULL;
    //USBIso Vars
    PKISO_CONTEXT isoCtx[NUM_ISO_ENDPOINTS][NUM_FUTURE_CTX];
    KOVL_HANDLE ovlkHandle[NUM_ISO_ENDPOINTS][NUM_FUTURE_CTX];
    KOVL_POOL_HANDLE ovlPool;
    unsigned char dataBuffer[NUM_ISO_ENDPOINTS][NUM_FUTURE_CTX][ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX];
    //Generic Functions
    unsigned char usbInit(unsigned long VIDin, unsigned long PIDin);
    int usbIsoInit(void);
    int flashFirmware(void);
    bool allEndpointsComplete(int n);
signals:
public slots:
    void isoTimerTick(void);
    void recoveryTick();
    void shutdownProcedure(void);
};

#endif // WINUSBDRIVER_H
