#ifndef LIBRADOR_INTERNAL_H
#define LIBRADOR_INTERNAL_H

#endif // LIBRADOR_INTERNAL_H

#define LABRADOR_VID 0x03eb
#define LABRADOR_PID 0xba94

#define CHECK_API_INITIALISED if(internal_librador_object == NULL) return -420;

class usbCallHandler;

class Librador
{

public:
    Librador();
    usbCallHandler *usb_driver = NULL;
};

Librador *internal_librador_object = NULL;
