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

std::vector<double> * librador_get_iso_data(double timeWindow_seconds, double sample_rate_hz, double delay_seconds, int filter_mode){
    double samples_per_second = internal_librador_object->usb_driver->get_samples_per_second();

    if(samples_per_second == 0){
        return NULL;
    }


    int interval_samples = round(samples_per_second / sample_rate_hz);
    int delay_samples = round(delay_seconds * samples_per_second);
    int numToGet = round(timeWindow_seconds * samples_per_second);
    return internal_librador_object->usb_driver->getMany_double(numToGet, interval_samples, delay_samples, filter_mode);
}

int librador_reset_usb(){
    CHECK_API_INITIALISED
    delete internal_librador_object->usb_driver;
    internal_librador_object->usb_driver = new usbCallHandler(LABRADOR_VID, LABRADOR_PID);
    return 0;
}

int librador_update_signal_gen_settings(int channel, unsigned char *sampleBuffer, int numSamples, double usecs_between_samples, double amplitude_v, double offset_v){
    CHECK_API_INITIALISED
    return internal_librador_object->usb_driver->update_function_gen_settings(channel, sampleBuffer, numSamples, usecs_between_samples, amplitude_v, offset_v);
}

int librador_send_signal_gen_settings(int channel){
    CHECK_API_INITIALISED
    return internal_librador_object->usb_driver->send_function_gen_settings(channel);
}

int librador_set_power_supply_voltage(double voltage){
    CHECK_API_INITIALISED
    return internal_librador_object->usb_driver->set_psu_voltage(voltage);
}

int librador_set_device_mode(int mode){
    CHECK_API_INITIALISED
    return internal_librador_object->usb_driver->set_device_mode(mode);
}

int librador_set_oscilloscope_gain(double gain){
    CHECK_API_INITIALISED
    return internal_librador_object->usb_driver->set_gain(gain);
}

int librador_set_digital_out(int channel, bool state_on){
    CHECK_API_INITIALISED
    static uint8_t channelStates[4] = {0, 0, 0, 0};
    channel--;
    if((channel < 0) || (channel > 3)){
        return -1000; //Invalid Channel
    }
    channelStates[channel] = state_on ? 1 : 0;

    return internal_librador_object->usb_driver->set_digital_state((channelStates [0] | channelStates[1] << 1 | channelStates[2] << 2 | channelStates[3] << 3));
}

int librador_reset_device(){
    CHECK_API_INITIALISED
    return internal_librador_object->usb_driver->reset_device(false);
}

int librador_jump_to_bootloader(){
    CHECK_API_INITIALISED
    return internal_librador_object->usb_driver->reset_device(true);
}

uint16_t librador_get_device_firmware_version(){
    CHECK_API_INITIALISED
    return internal_librador_object->usb_driver->get_firmware_version();
}

uint8_t librador_get_device_firmware_variant(){
    CHECK_API_INITIALISED
    return internal_librador_object->usb_driver->get_firmware_variant();
}
