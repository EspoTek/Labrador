/*
 * tiny_eeprom.c
 *
 * Created: 22/04/2017 12:37:21 PM
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

#include <asf.h>
#include "tiny_eeprom.h"

void eeprom_safe_read(){
	unsigned char previous_clk_settings = CLK.PSCTRL;
	CLK.PSCTRL = CLK_PSADIV4_bm; //Slow down the clock to prevent EEPROM misses
	nvm_eeprom_read_buffer(EEPROM_CURRENT_PAGE*EEPROM_PAGE_SIZE, eeprom_buffer_read, EEPROM_PAGE_SIZE);
	CLK.PSCTRL = previous_clk_settings;
	return;
}

void eeprom_safe_write(){
	unsigned char previous_clk_settings = CLK.PSCTRL;
	CLK.PSCTRL = CLK_PSADIV4_bm; //Slow down the clock to prevent EEPROM misses
	nvm_eeprom_load_page_to_buffer(eeprom_buffer_write);
	nvm_eeprom_atomic_write_page(EEPROM_CURRENT_PAGE);
	CLK.PSCTRL = previous_clk_settings;
	return;
}
