/**
 * \file
 *
 * \brief AVR XMEGA USART in SPI mode driver functions.
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
#include "usart_spi.h"
#include "sysclk.h"

void usart_spi_init(USART_t *usart)
{
#ifdef USARTC0
	if((uint16_t)usart == (uint16_t)&USARTC0) {
		sysclk_enable_module(SYSCLK_PORT_C,PR_USART0_bm);
	}
#endif
#ifdef USARTC1
	else
	if((uint16_t)usart == (uint16_t)&USARTC1) {
		sysclk_enable_module(SYSCLK_PORT_C,PR_USART1_bm);
	}
#endif
#ifdef USARTD0
	else
	if((uint16_t)usart == (uint16_t)&USARTD0) {
		sysclk_enable_module(SYSCLK_PORT_D,PR_USART0_bm);
	}
#endif
#ifdef USARTD1
	else
	if((uint16_t)usart == (uint16_t)&USARTD1) {
		sysclk_enable_module(SYSCLK_PORT_D,PR_USART1_bm);
	}
#endif
#ifdef USARTE0
	else
	if((uint16_t)usart == (uint16_t)&USARTE0) {
		sysclk_enable_module(SYSCLK_PORT_E,PR_USART0_bm);
	}
#endif
#ifdef USARTE1
	else
	if((uint16_t)usart == (uint16_t)&USARTE1) {
		sysclk_enable_module(SYSCLK_PORT_E,PR_USART1_bm);
	}
#endif
#ifdef USARTF0
	else
	if((uint16_t)usart == (uint16_t)&USARTF0) {
		sysclk_enable_module(SYSCLK_PORT_F,PR_USART0_bm);
	}
#endif
#ifdef USARTF1
	else
	if((uint16_t)usart == (uint16_t)&USARTF1) {
		sysclk_enable_module(SYSCLK_PORT_F,PR_USART1_bm);
	}
#endif
}

void usart_spi_setup_device(USART_t *usart, struct usart_spi_device *device,
     spi_flags_t flags, unsigned long baud_rate,
     board_spi_select_id_t sel_id)
{
	usart_spi_options_t opt;
	opt.baudrate=baud_rate;
	opt.spimode=flags;
	opt.data_order=false;
	usart_init_spi(usart, &opt);
}

status_code_t usart_spi_write_packet(USART_t *usart,const uint8_t *data, size_t len)
{
	size_t i=0;
	while(len) {
		usart_spi_transmit(usart,*(data+i));
		len--;
		i++;
	}
	return STATUS_OK;
}

status_code_t usart_spi_read_packet(USART_t *usart, uint8_t *data, size_t len)
{
	while(len) {
		*data = usart_spi_transmit(usart, CONFIG_USART_SPI_DUMMY);
		len--;
		data++;
 	}
	return STATUS_OK;
}

void usart_spi_select_device(USART_t *usart, struct usart_spi_device *device)
{
	ioport_set_pin_low(device->id);
}

void usart_spi_deselect_device(USART_t *usart, struct usart_spi_device *device)
{
	ioport_set_pin_high(device->id);
}
