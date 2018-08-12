/*****************************************************************************
 *
 * \file
 *
 * \brief SPI driver for AVR.
 *
 * This file defines a useful set of functions for the SPI interface on AVR
 * devices.
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
 ******************************************************************************/
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */


#ifndef _SPI_H_
#define _SPI_H_

/**
 * \defgroup group_xmega_drivers_spi SPI - Serial Peripheral Interface
 *
 * Driver for the Serial Peripheral Interface (SPI).
 * Provides functions for configuring and using the SPI.
 *
 * \{
 */

#include "compiler.h"
#include "status_codes.h"
#include "ioport.h"

/*! \brief Calculates the SPI baudrate divider.
 *
 * \param baudrate The expected baudrate on the SPI.
 * \param clkper_hz  SPI module input clock frequency (Peripheral clock, Hz).
 * \param spi The SPI module address
 *
 * \return Divider or error code.
 *   \retval >=0  Success.
 *   \retval  <0  Error.
 */
int8_t spi_xmega_set_baud_div(SPI_t *spi, uint32_t baudrate, uint32_t clkper_hz);

/*! \brief Enables the SPI.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_enable(SPI_t *spi)
{
	spi->CTRL |= SPI_ENABLE_bm;
}

/*! \brief Disables the SPI.
 *
 * Ensures that nothing is transferred while setting up buffers.
 *
 * \param spi Base address of the SPI instance.
 *
 * \warning This may cause data loss if used on a slave SPI.
 */
static inline void spi_disable(SPI_t *spi)
{
	spi->CTRL &= ~SPI_ENABLE_bm;
}

/*! \brief Tests if the SPI is enabled.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c 1 if the SPI is enabled, otherwise \c 0.
 */
static inline bool spi_is_enabled(SPI_t *spi)
{
	return spi->CTRL & SPI_ENABLE_bm ? true : false;
}

/*! \brief Put one data byte to a SPI peripheral.
 *
 * \param spi Base address of the SPI instance.
 * \param data The data byte to be loaded
 *
 */
static inline void spi_put(SPI_t *spi, uint8_t data)
{
	spi->DATA = data;
}

/*! \brief Get one data byte to a SPI peripheral.
 *
 * \param spi Base address of the SPI instance.
 * \return The data byte
 *
 */
static inline uint8_t spi_get(SPI_t *spi)
{
	return spi->DATA;
}

/*! \brief Tests if the SPI contains a received character.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c 1 if the SPI Receive Holding Register is full, otherwise \c 0.
 */
static inline bool spi_is_tx_ok(SPI_t *spi)
{
	return spi->STATUS & SPI_IF_bm ? true : false;
}

/*! \brief Activate SPI master mode of a SPI peripheral
 *
 * \param spi Base address of the SPI instance.
 *
 * \warning This may cause data loss if used on a slave SPI.
 */
static inline void spi_enable_master_mode(SPI_t *spi)
{
	spi->CTRL |= SPI_MASTER_bm;
}

/*! \name Part Specific SPI Driver
 */
//! @{
//! @}

/**
 * \}
 */

#endif  // _SPI_H_
