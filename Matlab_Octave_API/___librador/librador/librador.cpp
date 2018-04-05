#include "librador.h"
#include "librador_internal.h"
#include "usbcallhandler.h"

#include <vector>
#include <QThread>

Librador::Librador()
{
    usb_driver = new usbCallHandler(LABRADOR_VID, LABRADOR_PID);
}

int librador_init(){
    if(internal_librador_object != NULL){
        //Object already initialised
        return 1;
    }

    internal_librador_object = new Librador();
    if(internal_librador_object == NULL){
        //Object initialisation failed
        return -1;
    } else {
        //good, fresh initialisation
        return 0;
    }
}

int librador_exit(){
    CHECK_API_INITIALISED
    if(internal_librador_object == NULL){
        //Object not yet initialised
        return 1;
    }

    delete internal_librador_object;
    internal_librador_object = NULL;
    //Object deleted
    return 0;
}

int librador_setup_usb(){
    CHECK_API_INITIALISED
    int error;
    //Setup USB for Control (EP0) transfers.
    error = internal_librador_object->usb_driver->setup_usb_control();
    if(error < 0){
        return error;
    }
    //Setup USB for Isochronous transfers.
    error = internal_librador_object->usb_driver->setup_usb_iso();
    if(error < 0){
        return error - 1000;
    }
    return 0;
}

int librador_avr_debug(){
    CHECK_API_INITIALISED
    return internal_librador_object->usb_driver->avrDebug();
}

std::vector<double> * librador_get_iso_data(int numToGet, int interval_samples, int delay_sample, int filter_mode){
    return internal_librador_object->usb_driver->getMany_double(numToGet, interval_samples, delay_sample, filter_mode);
}

int librador_reset_usb(){
    printf("\n\n\nlibrador_reset_usb() received\n");
    //internal_librador_object->usb_driver->send_device_reset();
    delete internal_librador_object->usb_driver;
    internal_librador_object->usb_driver = new usbCallHandler(LABRADOR_VID, LABRADOR_PID);
    return 0;
}
