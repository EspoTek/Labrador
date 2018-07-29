/**
 * \file
 *
 * \brief ST7565R display controller driver configuration file.
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#ifndef CONF_ST7565R_H_INCLUDED
#define CONF_ST7565R_H_INCLUDED

#include <board.h>

#if BOARD == XMEGA_A3BU_XPLAINED
// Interface configuration for XMEGA-A3BU Xplained

#  define ST7565R_USART_SPI_INTERFACE
#  define ST7565R_USART_SPI    &USARTD0

#  define ST7565R_A0_PIN       NHD_C12832A1Z_REGISTER_SELECT
#  define ST7565R_CS_PIN       NHD_C12832A1Z_CSN
#  define ST7565R_RESET_PIN    NHD_C12832A1Z_RESETN

#else
// Interface configuration for other boards
#  warning ST7565R driver must be configured. Please see conf_st7565r.h.

// Interface possibilities:
// 1) Regular SPI interface
// #define ST7565R_SPI_INTERFACE
// #define ST7565R_SPI &SPID

// 2) USART SPI interface
// #define ST7565R_USART_SPI_INTERFACE
// #define ST7565R_USART_SPI &USARTD0

// Pin mapping:
// - Register select
// #define ST7565R_A0_PIN       0
// - Chip select
// #define ST7565R_CS_PIN       1
// - Reset
// #define ST7565R_RESET_PIN    2


// Placeholder setup

#  define ST7565R_SPI_INTERFACE
#  define ST7565R_SPI          0

#  define ST7565R_A0_PIN       0
#  define ST7565R_CS_PIN       1
#  define ST7565R_RESET_PIN    2

#endif // BOARD

// Board independent configuration

// Minimum clock period is 50ns@3.3V -> max frequency is 20MHz
#define ST7565R_CLOCK_SPEED          1000000
#define ST7565R_DISPLAY_CONTRAST_MAX 40
#define ST7565R_DISPLAY_CONTRAST_MIN 30

#endif /* CONF_ST7565R_H_INCLUDED */
