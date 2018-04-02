#ifndef LIBRADOR_H
#define LIBRADOR_H

#include "librador_global.h"

int LIBRADORSHARED_EXPORT librador_init();
int LIBRADORSHARED_EXPORT librador_exit();
int LIBRADORSHARED_EXPORT librador_setup_usb();
int LIBRADORSHARED_EXPORT librador_reset_usb();
int LIBRADORSHARED_EXPORT librador_avr_debug();
std::vector<double> * LIBRADORSHARED_EXPORT librador_get_iso_data(int numToGet, int interval_samples, int delay_sample, int filter_mode);

#endif // LIBRADOR_H
