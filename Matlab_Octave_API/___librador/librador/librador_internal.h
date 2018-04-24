#ifndef LIBRADOR_INTERNAL_H
#define LIBRADOR_INTERNAL_H

#endif // LIBRADOR_INTERNAL_H

#define LABRADOR_VID 0x03eb
#define LABRADOR_PID 0xba94

#define CHECK_API_INITIALISED if(internal_librador_object == NULL) return -420;
#define CHECK_USB_INITIALISED if(!internal_librador_object->usb_driver->connected) return -420420;

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
