/*
 * tiny_uart.c
 *
 * Created: 16/07/2015 6:32:52 PM
 *  Author: Esposch
 */

/* Copyright (C) 2018 Christopher Paul Esposito

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:

   (1) Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

   (2) Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in
   the documentation and/or other materials provided with the
   distribution.

   (3)The name of the author may not be used to
   endorse or promote products derived from this software without
   specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
   IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
   INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
   STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
   IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

#include "tiny_uart.h"
#include "globals.h"


void tiny_uart_setup(void){
	PR.PRPC &= 0b11101111;
	//PR.PRPE &= 0b11111110;  ???

	PORTC.DIR |= 0b10101010;
	PORTC.OUT = 0xff;
	PORTC.PIN2CTRL = PORT_INVEN_bm | PORT_OPC_PULLUP_gc;
	//PORTC.REMAP = 0x10; //Remap USART to [7:4]
	//#ifndef VERO
//		PORTC.REMAP = 0x20; //Swap MOSI and SCK - for small boards only!!!
	//#endif

	USARTC0.CTRLA = USART_RXCINTLVL_HI_gc;
	USARTC0.CTRLC = USART_CMODE_MSPI_gc | 0b00000100; //LSB received first, UPCHA disabled
	#if OVERCLOCK == 48
		USARTC0.BAUDCTRLA = 7;  	//BSEL = fper/(2fbaud) -1;  48/(2*3) - 1 = 7
	#else
		USARTC0.BAUDCTRLA = 3;  	//BSEL = fper/(2fbaud) -1;  24/(2*3) - 1 = 3
	#endif
	USARTC0.BAUDCTRLB = 0x00;// USART_BSCALE0_bm goes to 1.5MHz for some reason;
	USARTC0.CTRLB = USART_RXEN_bm | USART_TXEN_bm;
}


void tiny_spi_setup(void){
	//Power Reduction disable
	PR.PRPC &= 0b11110111;

	//SPI enable
	SPIC.INTCTRL = SPI_INTLVL_OFF_gc;
	//#ifdef VERO
		PORTC.PIN5CTRL = PORT_INVEN_bm | PORT_OPC_PULLUP_gc;
	//#else
	//	PORTC.PIN7CTRL = PORT_INVEN_bm | PORT_OPC_PULLUP_gc;  //Pin5 if not swapped
	//#endif
	SPIC.CTRL = SPI_DORD_bm | SPI_ENABLE_bm;  //Slave mode
	return;
}

ISR(SPIC_INT_vect){
	asm("nop");
}

ISR(USARTC0_RXC_vect){
	unsigned char temp = USARTC0.DATA;
	USARTC0.DATA = temp;
}
