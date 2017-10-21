/*****************************************************************************
 *
 * \file
 *
 * \brief SPI Master driver for AVR.
 *
 * This file defines a useful set of functions for the SPI interface on AVR
 * devices.
 *
 * Copyright (c) 2009-2015 Atmel Corporation. All rights reserved.
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
 ******************************************************************************/
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */


#ifndef _SPI_MASTER_H_
#define _SPI_MASTER_H_

#include "compiler.h"
#include "status_codes.h"
#include "ioport.h"
#include "spi.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup xmega_spi_master_group XMEGA SPI master service.
 *
 * This is the API for SPI master service on XMEGA.
 *
 * @{
 *
 * \section xmega_spi_master_qucikstart_section Quick Start Guide
 * See \ref common_spi_master_quickstart
 */

/*! \name Spi Master Management Configuration
 */
//! @{
#include "conf_spi_master.h"

//! Default Config Spi Master Dummy Field
#ifndef CONFIG_SPI_MASTER_DUMMY
#define CONFIG_SPI_MASTER_DUMMY              0xFF
#endif
//! @}

/**
 * \brief Clock phase
 */
#define SPI_CPHA	(1 << 0)

/**
 * \brief Clock polarity
 */
#define SPI_CPOL	(1 << 1)

/**
 * \brief SPI mode 0
 */
#define SPI_MODE_0	0
/**
 * \brief SPI mode 1
 */
#define SPI_MODE_1	(SPI_CPHA)
/**
 * \brief SPI mode 2
 */
#define SPI_MODE_2	(SPI_CPOL)
/**
 * \brief SPI mode 3
 */
#define SPI_MODE_3	(SPI_CPOL | SPI_CPHA)

typedef uint8_t spi_flags_t;
typedef uint32_t board_spi_select_id_t;

//! \brief Polled SPI device definition
struct spi_device {
	//! Board specific select id
	port_pin_t	id;
};

/*! \brief Initializes the SPI in master mode.
 *
 * \param spi       Base address of the SPI instance.
 *
 */
extern void spi_master_init(SPI_t *spi);

/**
 * \brief Setup a SPI device.
 *
 * The returned device descriptor structure must be passed to the driver
 * whenever that device should be used as current slave device.
 *
 * \param spi Base address of the SPI instance.
 * \param device    Pointer to SPI device struct that should be initialized.
 * \param flags     SPI configuration flags. Common flags for all
 *                  implementations are the SPI modes SPI_MODE_0 ...
 *                  SPI_MODE_3.
 * \param baud_rate Baud rate for communication with slave device in Hz.
 * \param sel_id    Board specific select id
 */
extern void spi_master_setup_device(SPI_t *spi, struct spi_device *device,
     spi_flags_t flags, unsigned long baud_rate,
     board_spi_select_id_t sel_id);

/*! \brief Enables the SPI.
 *
 * \param spi Base address of the SPI instance.
 */
extern void spi_enable(SPI_t *spi);

/*! \brief Disables the SPI.
 *
 * Ensures that nothing is transferred while setting up buffers.
 *
 * \param spi Base address of the SPI instance.
 *
 * \warning This may cause data loss if used on a slave SPI.
 */
extern void spi_disable(SPI_t *spi);


/*! \brief Tests if the SPI is enabled.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c 1 if the SPI is enabled, otherwise \c 0.
 */
extern bool spi_is_enabled(SPI_t *spi);

/**
 * \brief Select given device on the SPI bus
 *
 * Set device specific setting and calls board chip select.
 *
 * \param spi Base address of the SPI instance.
 * \param device SPI device
 *
 */
extern void spi_select_device(SPI_t *spi, struct spi_device *device);

/**
 * \brief Deselect given device on the SPI bus
 *
 * Calls board chip deselect.
 *
 * \param spi Base address of the SPI instance.
 * \param device SPI device
 *
 * \pre SPI device must be selected with spi_select_device() first
 */
extern void spi_deselect_device(SPI_t *spi, struct spi_device *device);

/*! \brief Write one byte to a SPI device.
 *
 * \param spi Base address of the SPI instance.
 * \param data The data byte to be loaded
 *
 */
__always_inline static void spi_write_single(SPI_t *spi, uint8_t data)
{
	spi_put(spi,data);
}

/**
 * \brief Send a sequence of bytes to a SPI device
 *
 * Received bytes on the SPI bus are discarded.
 *
 * \param spi Base address of the SPI instance.
 * \param data   data buffer to write
 * \param len    Length of data
 *
 * \pre SPI device must be selected with spi_select_device() first
 */
extern status_code_t spi_write_packet(SPI_t *spi,const uint8_t *data, size_t len);


/*! \brief Receive one byte from a SPI device.
 *
 * \param spi Base address of the SPI instance.
 * \param data Pointer to the data byte where to store the received data.
 *
 */
inline static void spi_read_single(SPI_t *spi, uint8_t *data)
{
	*data=spi_get(spi);
}

/**
 * \brief Receive a sequence of bytes from a SPI device
 *
 * All bytes sent out on SPI bus are sent as value 0.
 *
 * \param spi Base address of the SPI instance.
 * \param data   data buffer to read
 * \param len    Length of data
 *
 * \pre SPI device must be selected with spi_select_device() first
 */
extern status_code_t spi_read_packet(SPI_t *spi, uint8_t *data, size_t len);

/*! \brief Checks if all transmissions are complete.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return Status.
 *   \retval 1  All transmissions complete.
 *   \retval 0  Transmissions not complete.
 */
inline static bool spi_is_tx_empty(SPI_t *spi)
{
	return spi_is_tx_ok(spi);
}

/*! \brief Checks if all transmissions is ready.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return Status.
 *   \retval 1  All transmissions complete.
 *   \retval 0  Transmissions not complete.
 */
inline static bool spi_is_tx_ready(SPI_t *spi)
{
	return spi_is_tx_ok(spi);
}

/*! \brief Tests if the SPI contains a received character.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c 1 if the SPI Receive Holding Register is full, otherwise \c 0.
 */
inline static bool spi_is_rx_full(SPI_t *spi)
{
	return spi_is_tx_ok(spi);
}

/*! \brief Checks if all reception is ready.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c 1 if the SPI Receiver is ready, otherwise \c 0.
 */
inline static bool spi_is_rx_ready(SPI_t *spi)
{
	return spi_is_tx_ok(spi);
}

//! @}



#ifdef __cplusplus
}
#endif

/**
 * \page spi_master_xmega Quick start guide for SPI master on XMEGA devices
 *
 * \section spi_master_xmega_basic Basic setup for XMEGA devices
 * The SPI module will be set up as master:
 *  - SPI on PORTD
 *  - 1MHz SPI clock speed
 *  - Slave Chip Select connected on PORTD pin 1
 *  - SPI mode 0 (data on rising clock edge)
 *
 * \section   spi_master_xmega_basic_setup Setup steps
 * \subsection spi_master_xmega_basic_setup_code Example code
 * Add to application C-file (e.g. main.c):
 * \code
	   void spi_init_pins(void)
	   {
	       ioport_configure_port_pin(&PORTD, PIN1_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);

	       ioport_configure_port_pin(&PORTD, PIN4_bm, IOPORT_PULL_UP | IOPORT_DIR_INPUT);
	       ioport_configure_port_pin(&PORTD, PIN5_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	       ioport_configure_port_pin(&PORTD, PIN6_bm, IOPORT_DIR_INPUT);
	       ioport_configure_port_pin(&PORTD, PIN7_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	   }

	   void spi_init_module(void)
	   {
	      struct spi_device spi_device_conf = {
	          .id = IOPORT_CREATE_PIN(PORTD, 1)
	      };

	      spi_master_init(&SPID);
	      spi_master_setup_device(&SPID, &spi_device_conf, SPI_MODE_0, 1000000, 0);
	      spi_enable(&SPID);
	   }
\endcode
 *
 * \subsection spi_master_xmega_basic_setup Workflow
 * -# Ensure that \ref conf_spi_master.h is present for the driver.
 *  - \note This file is only for the driver and should not be included by the
 * user. In this example the file can be left empty.
 * -# Initialize the pins used by the SPI interface (this initialization is for
 * the ATxmega32A4U device).
 *  -# Set the pin used for slave select as output high:
 *    \code
	ioport_configure_port_pin(&PORTD, PIN1_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
\endcode
 *  -# Enable pull-up on own chip select (SS):
 *    \code
	ioport_configure_port_pin(&PORTD, PIN4_bm, IOPORT_PULL_UP | IOPORT_DIR_INPUT);
\endcode
 *    \attention If this pin is pulled low the SPI module will go into slave mode.
 *  -# Set MOSI and SCL as output high, and set MISO as input:
 *    \code
	ioport_configure_port_pin(&PORTD, PIN5_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	ioport_configure_port_pin(&PORTD, PIN6_bm, IOPORT_DIR_INPUT);
	ioport_configure_port_pin(&PORTD, PIN7_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
\endcode
 * -# Define the SPI device configuration struct to describe which pin the
 * slave select (slave chip select) is connected to, in this case the slave
 * select pin has been connected to PORTD pin 1 (PD1):
 *  - \code
	struct spi_device spi_device_conf = {
	    .id = IOPORT_CREATE_PIN(PORTD, 1)
	};
\endcode
 * -# Initialize the SPI module, in this case SPI on PORTD has been chosen:
 *  - \code
	spi_master_init(&SPID);
\endcode
 * -# Setup the SPI master module for a specific device:
 *  - \code
	spi_master_setup_device(&SPID, &spi_device_conf, SPI_MODE_0, 1000000, 0);
\endcode
 *  - \note The last argument, which is zero in this case, can be ignored and is
 *  only included for compatibility purposes.
 * -# Then enable the SPI:
 *  - \code
	spi_enable(&SPID);
\endcode
 *
 * \section spi_master_xmega_basic_usage Usage steps
 * \subsection spi_master_xmega_basic_usage_code Example code
 * Add to, e.g., the main loop in the application C-file:
 * \code
	   uint8_t data_buffer[1] = {0xAA};

	   struct spi_device spi_device_conf = {
	       .id = IOPORT_CREATE_PIN(PORTD, 1)
	   };

	   spi_select_device(&SPID, &spi_device_conf);

	   spi_write_packet(&SPID, data_buffer, 1);
	   spi_read_packet(&SPID, data_buffer, 1);

	   spi_deselect_device(&SPID, &spi_device_conf);
\endcode
 *
 * \subsection spi_master_xmega_basic_usage_flow Workflow
 * -# Create a buffer for data to be sent/received on the SPI bus, in this case
 * a single byte buffer is used. The buffer can be of arbitrary size as long as
 * there is space left in SRAM:
 *  - \code
	uint8_t data_buffer[1] = {0xAA};
\endcode
 * -# Define the SPI device configuration struct to describe which pin the
 * slave select (slave chip select) is connected to, in this case the slave
 * select pin has been connected to PORTD pin 1 (PD1):
 *  - \code
	struct spi_device spi_device_conf = {
	    .id = IOPORT_CREATE_PIN(PORTD, 1)
	};
\endcode
 *  - \note As this struct is the same for both the initializing part and the usage
 * part it could be a good idea to make the struct global, and hence accessible
 * for both the initializing part and usage part. Another solution could be to
 * create the struct in the main function and pass the address of the struct to
 * the spi_init_module() function, e.g.:
 *  \code
	   void spi_init_module(struct spi_device *spi_device_conf)
	   {
	       ...

	       spi_master_setup_device(&SPID, spi_device_conf, SPI_MODE_0, 1000000, 0);

	       ...
	   }
\endcode
 * -# Write data to the SPI slave device, in this case write one byte from the
 * data_buffer:
 *  - \code
	spi_write_packet(&SPID, data_buffer, 1);
\endcode
 * -# Read data from the SPI slave device, in this case read one byte and put it
 * into the data_buffer:
 *  - \code
	spi_read_packet(&SPID, data_buffer, 1);
\endcode
 *  - \attention As the SPI works as a shift register so that data is shifted in at
 * the same time as data is shifted out a read operation will mean that a dummy
 * byte \ref CONFIG_SPI_MASTER_DUMMY is written to the SPI bus. \ref CONFIG_SPI_MASTER_DUMMY
 * defaults to 0xFF, but can be changed by defining it inside the \ref conf_spi_master.h
 * file.
 * -# When read and write operations is done de-select the slave:
 *  - \code
	spi_deselect_device(&SPID, &spi_device_conf);
\endcode
 *
 */

#endif  // _SPI_MASTER_H_
