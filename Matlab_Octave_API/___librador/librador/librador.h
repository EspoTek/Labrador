#ifndef LIBRADOR_H
#define LIBRADOR_H

#include "librador_global.h"

int LIBRADORSHARED_EXPORT librador_init();
int LIBRADORSHARED_EXPORT librador_exit();
int LIBRADORSHARED_EXPORT librador_setup_usb();
int LIBRADORSHARED_EXPORT librador_avr_debug();

#endif // LIBRADOR_H
