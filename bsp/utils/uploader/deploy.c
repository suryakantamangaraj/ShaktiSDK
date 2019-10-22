/***************************************************************************
* Project                               :  shakti devt board
* Name of the file                      :  deploy.c
* Brief Description of file             :  Deploy elf into flash in board.
* Name of Author                        :  Sathya Narayanan N & Anand Kumar S
* Email ID                              :  sathya281@gmail.com

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
#include <uart.h>
#include "spi.h"
#include "flashdata.h"

#define DEBUG

/** @fn main
 * @brief The function uploads the hex file to the flash starting from location 0x00b00000
 * @details The function performs the upload functionality. The bare metal appln is a hex file. 
 * This hex file is converted to an array. And this array is uploaded as a data section to memory.
 * Once the driver code runs, it writes the data section to flash.
 * @warning none
 * @param[in] none
 * @param[Out] none
 */
void main(){

	spi_init();
	flash_device_id(); 
	int read_address = 0x00b00000;  // read/write from/to this address
	int size_of_array;
#ifdef DEBUG
printf("\n SPI INIT done");
#endif

//flash write start
#ifdef DEBUG
printf("\n Starting write to FLASH");
#endif
		printf("\n Erasing FLASH\n");
		flash_write_enable();
		flash_erase(read_address); //erases an 64kb sector
		flash_status_register_read();

		flash_write_enable();
                flash_write(read_address,SIZE);
		flash_status_register_read();
		read_address+=4;
	size_of_array = write_data[0];

	for(int i =1; i < size_of_array; i++)
	{
		flash_write_enable();
        flash_write(read_address,write_data[i]);
		flash_status_register_read();
		read_address+=4;
	}
//flash write end
#ifdef DEBUG
printf("\n Completed write to FLASH\n");
#endif

asm volatile ("ebreak");
}
