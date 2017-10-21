/**
 * \file
 *
 * \brief ST7565R display controller driver.
 *
 * Copyright (c) 2011-2015 Atmel Corporation. All rights reserved.
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
#ifndef ST7565R_H_INCLUDED
#define ST7565R_H_INCLUDED

#include <compiler.h>
#include <sysclk.h>
#include <ioport.h>
#include <status_codes.h>
#include <delay.h>

// controller and LCD configuration file
#include "conf_st7565r.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup st7565r_lcd_controller_group ST7565R LCD Controller Low-level\
 * driver
 *
 * This is a low level driver for the ST7565R LCD controller. It provides basic
 * functions for initializing and writing to the LCD controller. In addition to
 * hardware control and use of the LCD controller internal functions .
 *
 * Before writing data to the display call \ref st7565r_init() which will set up
 * the physical interface and the LCD. A file named \ref conf_st7565r.h is needed
 * to define which interface to use. For more information see the Interface
 * selection section. In addition one also need to define the pins
 * \ref ST7565R_A0_PIN, \ref ST7565R_CS_PIN and \ref ST7565R_RESET_PIN and the
 * display \ref ST7565R_CLOCK_SPEED.
 *
 * \warning This driver is not reentrant and can not be used in interrupt\
 * service routines without extra care.
 *
 * As a safety feature one also need to set the max and min contrast levels that
 * the \ref st7565r_set_contrast using the defines
 * \ref ST7565R_DISPLAY_CONTRAST_MAX and \ref ST7565R_DISPLAY_CONTRAST_MIN to
 * protect the display from too high voltage, please see the
 * \ref st7565r_set_contrast function for more details.
 *
 * An example \ref conf_st7565r.h file could look like
 * \code
	 // interface selection
	 #define ST7565R_USART_SPI_INTERFACE
	 #define ST7565R_USART_SPI            &USARTD0

	 // minimum clock period is 50ns@3.3V -> max frequency is 20MHz
	 #define ST7565R_CLOCK_SPEED          1000000

	 #define ST7565R_DISPLAY_CONTRAST_MAX 40
	 #define ST7565R_DISPLAY_CONTRAST_MIN 30

	 #define ST7565R_A0_PIN               NHD_C12832A1Z_REGISTER_SELECT
	 #define ST7565R_CS_PIN               NHD_C12832A1Z_CSN
	 #define ST7565R_RESET_PIN            NHD_C12832A1Z_RESETN
\endcode
 *
 * \section dependencies Dependencies
 * This driver depends on the following modules:
 * - \ref ioport_group for IO port control.
 * - \ref sysclk_group for getting system clock speeds for init functions.
 * - \ref usart_spi_group or \ref spi_group for communication with the LCD
 * controller
 * @{
 */

//! \name Command defines
//@{
#define ST7565R_CMD_DISPLAY_ON                     0xAF
#define ST7565R_CMD_DISPLAY_OFF                    0xAE
#define ST7565R_CMD_START_LINE_SET(line)           (0x40 | (line))
#define ST7565R_CMD_PAGE_ADDRESS_SET(page)         (0xB0 | (page))
#define ST7565R_CMD_COLUMN_ADDRESS_SET_MSB(column) (0x10 | (column))
#define ST7565R_CMD_COLUMN_ADDRESS_SET_LSB(column) (0x00 | (column))
#define ST7565R_CMD_ADC_NORMAL                     0xA0
#define ST7565R_CMD_ADC_REVERSE                    0xA1
#define ST7565R_CMD_DISPLAY_NORMAL                 0xA6
#define ST7565R_CMD_DISPLAY_REVERSE                0xA7
#define ST7565R_CMD_DISPLAY_ALL_POINTS_OFF         0xA4
#define ST7565R_CMD_DISPLAY_ALL_POINTS_ON          0xA5
#define ST7565R_CMD_LCD_BIAS_1_DIV_5_DUTY33        0xA1
#define ST7565R_CMD_LCD_BIAS_1_DIV_6_DUTY33        0xA2
#define ST7565R_CMD_NORMAL_SCAN_DIRECTION          0xC0
#define ST7565R_CMD_REVERSE_SCAN_DIRECTION         0xC8
#define ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_0       0x20
#define ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_1       0x21
#define ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_2       0x22
#define ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_3       0x23
#define ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_4       0x24
#define ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_5       0x25
#define ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_6       0x26
#define ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_7       0x27
#define ST7565R_CMD_POWER_CTRL_ALL_ON              0x2F
#define ST7565R_CMD_SLEEP_MODE                     0xAC
#define ST7565R_CMD_NORMAL_MODE                    0xAD
#define ST7565R_CMD_RESET                          0xE2
#define ST7565R_CMD_NOP                            0xE3
#define ST7565R_CMD_ELECTRONIC_VOLUME_MODE_SET     0x81
#define ST7565R_CMD_ELECTRONIC_VOLUME(volume)      (0x3F & (~volume))
#define ST7565R_CMD_BOOSTER_RATIO_SET              0xF8
#define ST7565R_CMD_BOOSTER_RATIO_2X_3X_4X         0x00
#define ST7565R_CMD_BOOSTER_RATIO_5X               0x01
#define ST7565R_CMD_BOOSTER_RATIO_6X               0x03
#define ST7565R_CMD_STATUS_READ                    0x00
#define ST7565R_CMD_END                            0xEE
#define ST7565R_CMD_READ_MODIFY_WRITE              0xE0
//@}

/**
 * \name Interface selection
 *
 * The LCD controller support both serial and parallel mode, that means there
 * is a number of possible ways of interfacing the controller using different
 * AVR peripherals. The different interfaces can be selected using different
 * defines. This driver supports the serial communication mode using an
 * USART in Master SPI mode by defining \ref ST7565R_USART_SPI_INTERFACE, and a
 * normal SPI in Master Mode by defining \ref ST7565R_SPI_INTERFACE.
 *
 * \note The current driver only support serial mode.
 */
//@{
#if defined(__DOXYGEN__)
//! \brief Select the a USART SPI interface.
# define ST7565R_USART_SPI_INTERFACE
//! \brief Select the normal SPI peripheral interface.
# define ST7565R_SPI_INTERFACE
#endif

#if defined(ST7565R_USART_SPI_INTERFACE)
# include <usart_spi.h>
#elif defined(ST7565R_SPI_INTERFACE)
# include <spi_master.h>
#else
#error "Interface not supported by the driver"
#endif
//@}

#if defined(ST7565R_USART_SPI_INTERFACE) || defined(ST7565R_SPI_INTERFACE)
//
# define ST7565R_SERIAL_INTERFACE
#endif

//! \name LCD controller write and read functions
//@{
/**
 * \brief Writes a command to the display controller
 *
 * This functions pull pin A0 low before writing to the controller. Different
 * data write function is called based on the selected interface.
 *
 * \param command the command to write
 */
static inline void st7565r_write_command(uint8_t command)
{
#if defined(ST7565R_USART_SPI_INTERFACE)
	struct usart_spi_device device = {.id = ST7565R_CS_PIN};
	usart_spi_select_device(ST7565R_USART_SPI, &device);
	ioport_set_pin_low(ST7565R_A0_PIN);
	usart_spi_transmit(ST7565R_USART_SPI, command);
	usart_spi_deselect_device(ST7565R_USART_SPI, &device);
#elif defined(ST7565R_SPI_INTERFACE)
	struct spi_device device = {.id = ST7565R_CS_PIN};
	spi_select_device(ST7565R_SPI, &device);
	ioport_set_pin_low(ST7565R_A0_PIN);
	spi_write_single(ST7565R_SPI, command);
	spi_deselect_device(ST7565R_SPI, &device);
#endif
}

/**
 * \brief Write data to the display controller
 *
 * This functions sets the pin A0 before writing to the controller. Different
 * data write function is called based on the selected interface.
 *
 * \param data the data to write
 */
static inline void st7565r_write_data(uint8_t data)
{
#if defined(ST7565R_USART_SPI_INTERFACE)
	struct usart_spi_device device = {.id = ST7565R_CS_PIN};
	usart_spi_select_device(ST7565R_USART_SPI, &device);
	ioport_set_pin_high(ST7565R_A0_PIN);
	usart_spi_transmit(ST7565R_USART_SPI, data);
	ioport_set_pin_low(ST7565R_A0_PIN);
	usart_spi_deselect_device(ST7565R_USART_SPI, &device);
#elif defined(ST7565R_SPI_INTERFACE)
	struct spi_device device = {.id = ST7565R_CS_PIN};
	spi_select_device(ST7565R_SPI, &device);
	ioport_set_pin_high(ST7565R_A0_PIN);
	spi_write_single(ST7565R_SPI, data);
	ioport_set_pin_low(ST7565R_A0_PIN);
	spi_deselect_device(ST7565R_SPI, &device);
#endif
}

/**
 * \brief Read data from the controller
 *
 * \note The controller does not support read in serial mode.
 *
 * \retval 8 bit data read from the controller
 */
static inline uint8_t st7565r_read_data(void)
{
	return 0;
}

/**
 * \brief Read status from the controller
 *
 * \note The controller does not support read in serial mode.
 *
 * \retval 8 bit status read from the controller
 */
static inline uint8_t st7565r_get_status(void)
{
	return 0;
}
//@}

//! \name LCD Controller reset
//@{
/**
 * \brief Perform a soft reset of the LCD controller
 *
 * This functions will reset the LCD controller by sending the reset command.
 * \note this functions should not be confused with the \ref st7565r_hard_reset()
 * function, this command will not control the RST pin.
 */
static inline void st7565r_soft_reset(void)
{
	st7565r_write_command(ST7565R_CMD_RESET);
}

/**
 * \brief Perform a hard reset of the LCD controller
 *
 * This functions will reset the LCD controller by setting the reset pin low.
 * \note this functions should not be confused with the \ref st7565r_soft_reset()
 * function, this command will control the RST pin.
 */
static inline void st7565r_hard_reset(void)
{
	ioport_set_pin_low(ST7565R_RESET_PIN);
	delay_us(10);
	ioport_set_pin_high(ST7565R_RESET_PIN);
	delay_us(10);
}
//@}

//! \name Sleep control
//@{
/**
 * \brief Enable the LCD sleep mode
 */
static inline void st7565r_sleep_enable(void)
{
	st7565r_write_command(ST7565R_CMD_SLEEP_MODE);
}

/**
 * \brief Disable the LCD sleep mode
 */
static inline void st7565r_sleep_disable(void)
{
	st7565r_write_command(ST7565R_CMD_NORMAL_MODE);
}
//@}

//! \name Address setup for the LCD
//@{
/**
 * \brief Set current page in display RAM
 *
 * This command is usually followed by the configuration of the column address
 * because this scheme will provide access to all locations in the display
 * RAM.
 *
 * \param address the page address
 */
static inline void st7565r_set_page_address(uint8_t address)
{
	// Make sure that the address is 4 bits (only 8 pages)
	address &= 0x0F;
	st7565r_write_command(ST7565R_CMD_PAGE_ADDRESS_SET(address));
}

/**
 * \brief Set current column in display RAM
 *
 * \param address the column address
 */
static inline void st7565r_set_column_address(uint8_t address)
{
	// Make sure the address is 7 bits
	address &= 0x7F;
	st7565r_write_command(ST7565R_CMD_COLUMN_ADDRESS_SET_MSB(address >> 4));
	st7565r_write_command(ST7565R_CMD_COLUMN_ADDRESS_SET_LSB(address & 0x0F));
}

/**
 * \brief Set the display start draw line address
 *
 * This function will set which line should be the start draw line for the LCD.
 */
static inline void st7565r_set_display_start_line_address(uint8_t address)
{
	// Make sure address is 6 bits
	address &= 0x3F;
	st7565r_write_command(ST7565R_CMD_START_LINE_SET(address));
}
//@}

//! \name Display hardware control
//@{
/**
 * \brief Turn the LCD display on
 *
 * This function will turn on the LCD.
 */
static inline void st7565r_display_on(void)
{
	st7565r_write_command(ST7565R_CMD_DISPLAY_ON);
}

/**
 * \brief Turn the LCD display off
 *
 * This function will turn off the LCD.
 */
static inline void st7565r_display_off(void)
{
	st7565r_write_command(ST7565R_CMD_DISPLAY_OFF);
}

/**
 * \brief Sets all LCD pixels on
 *
 * This function can be used to test the LCD by setting all pixels on, this will
 * not affect the current LCD RAM.
 *
 * \param pixels_on if true all the LCD pixels are turned on, false the display
 *                  is back in normal mode displaying what is in the display
 *                  RAM.
 */
static inline void st7565r_set_all_pixels(bool pixels_on)
{
	if (pixels_on) {
		st7565r_write_command(ST7565R_CMD_DISPLAY_ALL_POINTS_ON);
	} else {
		st7565r_write_command(ST7565R_CMD_DISPLAY_ALL_POINTS_OFF);
	}
}

/**
 * \brief Set the LCD contrast level
 *
 * \warning This will set the voltage for the LCD, settings this value too high
 * may result in damage to the LCD. Hence the limit for these settings must be
 * defined in the \ref conf_st7565r.h file.
 *
 * Contrast values outside the max and min values will be clipped to the defined
 * \ref ST7565R_DISPLAY_CONTRAST_MAX and \ref ST7565R_DISPLAY_CONTRAST_MIN.
 *
 * \param contrast a number between 0 and 63 where the max values is given by
 *                 the LCD.
 *
 * \retval contrast the contrast value written to the LCD controller
 */
static inline uint8_t st7565r_set_contrast(uint8_t contrast)
{
	if (contrast < ST7565R_DISPLAY_CONTRAST_MIN) {
		contrast = ST7565R_DISPLAY_CONTRAST_MIN;
	}
	if (contrast > ST7565R_DISPLAY_CONTRAST_MAX) {
		contrast = ST7565R_DISPLAY_CONTRAST_MAX;
	}
	st7565r_write_command(ST7565R_CMD_ELECTRONIC_VOLUME_MODE_SET);
	st7565r_write_command(ST7565R_CMD_ELECTRONIC_VOLUME(contrast));
	return contrast;
}

/**
 * \brief Invert all pixels on the device
 *
 * This function will invert all pixels on the LCD
 *
 */
static inline void st7565r_display_invert_enable(void)
{
	st7565r_write_command(ST7565R_CMD_DISPLAY_REVERSE);
}

/**
 * \brief Disable invert of all pixels on the device
 *
 * This function will disable invert on all pixels on the LCD
 *
 */
static inline void st7565r_display_invert_disable(void)
{
	st7565r_write_command(ST7565R_CMD_DISPLAY_NORMAL);
}
//@}

//! \name Initialization
//@{
void st7565r_init(void);
//@}

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* ST7565R_H_INCLUDED */
