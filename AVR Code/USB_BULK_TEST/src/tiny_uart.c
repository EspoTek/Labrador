/*
 * tiny_uart.c
 *
 * Created: 16/07/2015 6:32:52 PM
 *  Author: Esposch
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
	SPIC.CTRL = SPI_ENABLE_bm;  //Slave mode
	SPIC.INTCTRL = SPI_INTLVL_OFF_gc;
	//#ifdef VERO
		PORTC.PIN5CTRL = PORT_INVEN_bm | PORT_OPC_PULLUP_gc;
	//#else
	//	PORTC.PIN7CTRL = PORT_INVEN_bm | PORT_OPC_PULLUP_gc;  //Pin5 if not swapped		
	//#endif
		
	return;
}

ISR(SPIC_INT_vect){
	asm("nop");
}

ISR(USARTC0_RXC_vect){
	unsigned char temp = USARTC0.DATA;
	USARTC0.DATA = temp;
}