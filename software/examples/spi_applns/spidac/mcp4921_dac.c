/***************************************************************************
 * Project           					:  shakti devt board
 * Name of the file	     				:  spidac.c
 * Created date			        		:  05.02.2020
 * Brief Description of file             :  Performs the Digital to analog operation with spi writing .
 * Name of Author    	                :  G Nambirajan, Koteeswaran
 * Email ID                              :  nambirajan2004@gmail.com

 Copyright (C) 2019  IIT Madras. All rights reserved.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.

***************************************************************************/

#include "spi.h"
#include <stdint.h>

void spi_dac()
{
    configure_spi(SPI1_OFFSET);	
	spi_init();

	log_debug("SPI init done\n");

	waitfor(200);
	write_dac_value(0xffff);

	log_debug("\nDac Value Written\n");

	while(1)
	{
		write_dac_value(0xFFF);
		log_debug("Dac Value Written - 4096\n");

		delay_loop(0x750, 0x750);
		write_dac_value(0x0);
		log_debug("Dac Value Written - 0\n");

		delay_loop(0x750, 0x750);
	}
} 

int write_dac_value(unsigned dac_value)
{
	int* spi_dr1    = (int*) SPI_DR1 ;
	int* spi_dr5    = (int*) SPI_DR5 ;
	int* spi_cr1    = (int*) SPI_CR1;

	int data1 = ((0x3 << 28) | (dac_value << 16));

	log_info("\n Data value written: %x", data1);

	set_spi(spi_dr1, data1);
	set_spi(spi_dr5, 0);
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(16)|SPI_TOTAL_BITS_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));

	waitfor(20);
	spi_notbusy();

	return 1;
}

void main()
{
	spi_dac();
}
