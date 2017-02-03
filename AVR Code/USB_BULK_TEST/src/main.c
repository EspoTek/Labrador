//Include the ASF Licence!

#include <stdio.h>
#include <asf.h>
#include <string.h>

#include "ui.h"
#include "globals.h"
#include "tiny_adc.h"
#include "tiny_dma.h"
#include "tiny_timer.h"
#include "tiny_dac.h"
#include "tiny_uart.h"
#include "tiny_dig.h"
#include "tiny_calibration.h"

volatile bool main_b_vendor_enable = false;

COMPILER_WORD_ALIGNED
volatile unsigned char isoBuf[BUFFER_SIZE];
COMPILER_WORD_ALIGNED
volatile unsigned char dacBuf_CH1[DACBUF_SIZE];// = {128,  134,  140,  146,  153,  159,  165,  171,  177,  182,  188,  194,  199,  204,  209,  214,  218,  223,  227,  230,  234,  237,  240,  243,  246,  248,  250,  252,  253,  254,  255,  255,  255,  255,  254,  253,  252,  251,  249,  247,  245,  242,  239,  236,  232,  229,  225,  220,  216,  211,  206,  201,  196,  191,  185,  180,  174,  168,  162,  156,  149,  143,  137,  131,  124,  118,  112,  106,   99,   93,   87,   81,   75,   70,   64,   59,   54,   49,   44,   39,   35,   30,   26,   23,   19,   16,   13,   10,    8,    6,    4,    3,    2,    1,    0,    0,    0,    0,    1,    2,    3,    5,    7,    9,   12,   15,   18,   21,   25,   28,   32,   37,   41,   46,   51,   56,   61,   67,   73,   78,   84,   90,   96,  102,  109,  115,  121,  127};
volatile unsigned char dacBuf_CH2[DACBUF_SIZE];

volatile unsigned char b1_state = 0;
volatile unsigned char b2_state = 0;
volatile unsigned char usb_state = 0;

volatile uint16_t dacBuf_len = 128;
volatile uint16_t auxDacBufLen = 128;
volatile unsigned char dummy = 0x55;
volatile unsigned char global_mode = 255;

volatile char PSU_target = 0;

volatile unsigned char test_byte = 123;

uint32_t debug_counter;

unsigned char tripleUsbSuccess = 0;

volatile unsigned char firstFrame = 0;
volatile unsigned char tcinit = 0;

volatile unsigned int currentTrfcnt;
volatile unsigned char debugOnNextEnd = 0;

#define CNT_CNT_MAX 256
volatile unsigned short cntCnt[CNT_CNT_MAX];
volatile unsigned short cntCntCnt = 0;
#define DEBUG_DIVISION 0
volatile unsigned char debug_divider = 0;

volatile unsigned int median_TRFCNT = 65535;

volatile char debug_data[8] = "DEBUG123";

volatile unsigned short dma_ch0_ran;
volatile unsigned short dma_ch1_ran;

unified_debug uds;

int main(void){
	irq_initialize_vectors();
	cpu_irq_enable();
//	sysclk_init();	
	tiny_calibration_init();
		
	board_init();
	udc_start();
	tiny_dac_setup();
	tiny_dma_setup();
	tiny_adc_setup(0, 0);
	tiny_adc_pid_setup();
	tiny_adc_ch1setup(12);
	tiny_timer_setup();
	tiny_uart_setup();
	tiny_spi_setup();
	tiny_dig_setup();
			
	//USARTC0.DATA = 0x55;
	//asm("nop");

	strcpy(uds.header, "debug123");

	while (true) {
		debug_counter++;
		if(debug_counter > 100000000){
			debug_counter = 0;
		}
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
	//test_byte = ADCA.CH1.RESH;
	//DO NOTHING!
	}
}

//! Global variable to give and record information about setup request management
udd_ctrl_request_t udd_g_ctrlreq;

//CALLBACKS:
void main_suspend_action(void)
{
	return;
}

void main_resume_action(void)
{
	return;
}

void main_sof_action(void)
{
	cli();
	uds.trfcntL0 = DMA.CH0.TRFCNTL;
	uds.trfcntH0 = DMA.CH0.TRFCNTH;	
	uds.trfcntL1 = DMA.CH1.TRFCNTL;
	uds.trfcntH1 = DMA.CH1.TRFCNTH;
	uds.counterL = TC_CALI.CNTL;
	uds.counterH = TC_CALI.CNTH;
	if((DMA.CH0.TRFCNT > 325) && (DMA.CH0.TRFCNT < 425)){
		currentTrfcnt = DMA.CH0.TRFCNT;
		asm("nop");
	}
	if(firstFrame){
		tiny_calibration_first_sof();
		firstFrame = 0;
		tcinit = 1;
		sei();
		return;
	}
	else{
		if(tcinit){
			if(calibration_values_found == 0x03){
				tiny_calibration_maintain();
				tiny_calibration_layer2();
			} else tiny_calibration_find_values();
			if(debug_divider == DEBUG_DIVISION){
				debug_divider = 0;
				cntCnt[cntCntCnt] = DMA.CH0.TRFCNT;
				if(cntCntCnt == (CNT_CNT_MAX - 1)){
					cntCntCnt = 0;
				}
				else cntCntCnt++;
			}
			else debug_divider++;
		}
	}
	
	if(debugOnNextEnd){
		currentTrfcnt = DMA.CH0.TRFCNT;
		debugOnNextEnd = 0;
	}
	if(global_mode < 5){
		usb_state = (DMA.CH0.TRFCNT < 375) ? 1 : 0;
	}
	else{
		usb_state = (DMA.CH0.TRFCNT < 750) ? 1 : 0;
	}
	sei();
	return;
}

bool main_vendor_enable(void)
{
	main_b_vendor_enable = true;
	firstFrame = 1;
	udd_ep_run(0x81, false, (uint8_t *)&isoBuf[0], 125, iso_callback);
	udd_ep_run(0x82, false, (uint8_t *)&isoBuf[125], 125, iso_callback);
	udd_ep_run(0x83, false, (uint8_t *)&isoBuf[250], 125, iso_callback);
	udd_ep_run(0x84, false, (uint8_t *)&isoBuf[375], 125, iso_callback);
	udd_ep_run(0x85, false, (uint8_t *)&isoBuf[500], 125, iso_callback);
	udd_ep_run(0x86, false, (uint8_t *)&isoBuf[625], 125, iso_callback);
	return true;
}

void main_vendor_disable(void)
{
	main_b_vendor_enable = false;
}

bool main_setup_out_received(void)
{
	return 1;
}

bool main_setup_in_received(void)
{
	return true;
}

void iso_callback(udd_ep_status_t status, iram_size_t nb_transfered, udd_ep_id_t ep){
	unsigned short offset = (ep - 0x81) * 125;
	if (global_mode < 5){
		if(ep > 0x83) offset += 375; //Shift from range [375, 750]  to [750, 1125]  Don't do this in modes 6 and 7 because they use 750 byte long sub-buffers.
		udd_ep_run(ep, false, (uint8_t *)&isoBuf[usb_state * HALFPACKET_SIZE + offset], 125, iso_callback);
	}
	else{
		udd_ep_run(ep, false, (uint8_t *)&isoBuf[usb_state * PACKET_SIZE + offset], 125, iso_callback);
	}
	return;
}
