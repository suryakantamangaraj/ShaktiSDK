/***************************************************************************
* Project                               :  shakti devt board
* Name of the file                      :  spi.c
* Brief Description of file             :  write data to flash by spi 
* Name of Author                        :  Kaustubh Ghormade
* Email ID                              :  kaustubh4347@gmail.com

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

#include <stdint.h>
#include "spi.h"

/** @fn main
 * @brief 
 * @details 
 * @warning 
 * @param[in] No input parameter
 * @param[Out] No output parameter
 */
void main()
{
	int write_address = 0x00b00000;  // read/write from/to this address
	int data = 0xDEADBEEF; //32 bits of data can be written at a time
	
    configure_spi(SPI1_OFFSET);
	spi_init();
	
	printf("SPI init done\n");

	flash_device_id(); 

	waitfor(200);

	flash_write_enable();
	flash_erase(0x00b00000); //erases an entire sector
	flash_status_register_read();

	//flash write
	flash_write_enable();
	flash_write( write_address,data);
	printf("Flash write done on address %x and data %x \n", 
	       write_address, data);

	asm volatile ("ebreak");
} 

