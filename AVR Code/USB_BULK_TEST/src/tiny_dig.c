/*
 * tiny_dig_out.c
 *
 * Created: 14/10/2015 4:51:19 PM
 *  Author: Esposch
 */ 

#include "tiny_dig.h"
#include "globals.h"


void tiny_dig_setup(void){
	PORTE.DIR = 0x0f;
	PORTE.OUT = 0x05;
	return;
}
