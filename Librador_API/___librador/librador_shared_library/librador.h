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

#ifndef LIBRADOR_H
#define LIBRADOR_H

#include "librador_global.h"
#include <vector>
#include <stdint.h>

int LIBRADORSHARED_EXPORT librador_init();
int LIBRADORSHARED_EXPORT librador_exit();
int LIBRADORSHARED_EXPORT librador_setup_usb();
int LIBRADORSHARED_EXPORT librador_reset_usb();
//Control
//a0
int LIBRADORSHARED_EXPORT librador_avr_debug();
//a1
int LIBRADORSHARED_EXPORT librador_update_signal_gen_settings(int channel, unsigned char* sampleBuffer, int numSamples, double usecs_between_samples, double amplitude_v, double offset_v);
int LIBRADORSHARED_EXPORT librador_send_sin_wave(int channel, double frequency_Hz, double amplitude_v, double offset_v);
int LIBRADORSHARED_EXPORT librador_send_square_wave(int channel, double frequency_Hz, double amplitude_v, double offset_v);
int LIBRADORSHARED_EXPORT librador_send_sawtooth_wave(int channel, double frequency_Hz, double amplitude_v, double offset_v);
int LIBRADORSHARED_EXPORT librador_send_triangle_wave(int channel, double frequency_Hz, double amplitude_v, double offset_v);
//a2
////As above
//a3
int LIBRADORSHARED_EXPORT librador_set_power_supply_voltage(double voltage);
//a4
///As above, a1 and a2
//a5
int LIBRADORSHARED_EXPORT librador_set_device_mode(int mode);
int LIBRADORSHARED_EXPORT librador_set_oscilloscope_gain(double gain);
//a6
int LIBRADORSHARED_EXPORT librador_set_digital_out(int channel, bool state_on);
//a7
int LIBRADORSHARED_EXPORT librador_reset_device();
int LIBRADORSHARED_EXPORT librador_jump_to_bootloader();
//a8
uint16_t LIBRADORSHARED_EXPORT librador_get_device_firmware_version();
//a9
uint8_t LIBRADORSHARED_EXPORT librador_get_device_firmware_variant();
//aa
//int LIBRADORSHARED_EXPORT librador_kickstart_isochronous_loop();

std::vector<double> * LIBRADORSHARED_EXPORT librador_get_analog_data(int channel, double timeWindow_seconds, double sample_rate_hz, double delay_seconds, int filter_mode);
std::vector<double> * LIBRADORSHARED_EXPORT librador_get_analog_data_sincelast(int channel, double timeWindow_max_seconds, double sample_rate_hz, double delay_seconds, int filter_mode);
std::vector<uint8_t> * LIBRADORSHARED_EXPORT librador_get_digital_data(int channel, double timeWindow_seconds, double sample_rate_hz, double delay_seconds);

//TODO: flashFirmware();


/*
 * Should never be unsynchronised...  Hide these ones
int LIBRADORSHARED_EXPORT librador_synchronise_begin();
int LIBRADORSHARED_EXPORT librador_synchronise_end();
*/


#endif // LIBRADOR_H
