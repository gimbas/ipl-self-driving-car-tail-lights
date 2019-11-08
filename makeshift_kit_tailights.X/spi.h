/* ************************************************************************** */
/** Descriptive File Name

  @Company
	Company Name

  @File Name
	filename.h

  @Summary
	Brief description of the file.

  @Description
	Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef SPI_H    /* Guard against multiple inclusion */
#define SPI_H

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <xc.h>
#include <sys/attribs.h>
#include "systick.h"

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */

#define SPI_MODE_0 0b000	//idle Low, edge from idle to active
#define SPI_MODE_1 0b001	//idle Low, edge from active to idle
#define SPI_MODE_2 0b100	//idle High, edge from idle to active
#define SPI_MODE_3 0b101	//idle High, edge from active to idle

namespace spi
{
	void init(uint8_t mode = SPI_MODE_0, uint32_t speed = 500000);
	void transfer(uint8_t* buff_tx, uint8_t* buff_rx, uint8_t length);
}


#endif /* SPI_H */