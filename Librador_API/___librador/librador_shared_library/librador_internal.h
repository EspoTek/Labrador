// Copyright (C) 2018, 2019 Christopher Paul Esposito
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

#ifndef LIBRADOR_INTERNAL_H
#define LIBRADOR_INTERNAL_H

#endif // LIBRADOR_INTERNAL_H

#define LABRADOR_VID 0x03eb
#define LABRADOR_PID 0xba94

#define CHECK_API_INITIALISED if(internal_librador_object == NULL) return -420;
#define CHECK_USB_INITIALISED if(!internal_librador_object->usb_driver->connected) return -421;

#define VECTOR_API_INIT_CHECK if(internal_librador_object == NULL) return NULL;
#define VECTOR_USB_INIT_CHECK if(!internal_librador_object->usb_driver->connected) return NULL;


class usbCallHandler;

class Librador
{

public:
    Librador();
    usbCallHandler *usb_driver = NULL;
};

Librador *internal_librador_object = NULL;
