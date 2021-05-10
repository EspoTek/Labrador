/*
 * tiny_dma.h
 *
 * Created: 25/06/2015 9:01:15 AM
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


#ifndef TINY_DMA_H_
#define TINY_DMA_H_

#include <stdio.h>
#include <asf.h>
#include "globals.h"

void tiny_dma_setup(void);
void tiny_dma_flush(void);

void tiny_dma_set_mode_0(void);
void tiny_dma_loop_mode_0(void);

void tiny_dma_set_mode_1(void);
void tiny_dma_loop_mode_1(void);

void tiny_dma_set_mode_2(void);
void tiny_dma_loop_mode_2(void);

void tiny_dma_set_mode_3(void);
void tiny_dma_loop_mode_3(void);

void tiny_dma_set_mode_4(void);
void tiny_dma_loop_mode_4(void);

void tiny_dma_set_mode_5(void);

void tiny_dma_set_mode_6(void);
void tiny_dma_loop_mode_6(void);

void tiny_dma_set_mode_7(void);
void tiny_dma_loop_mode_7(void);

void tiny_dma_delayed_set(unsigned char mode);


#endif /* TINY_DMA_H_ */
