/*
 **************************************************************************
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
#include <stdio.h>
#include "spi.h"
#include "flashdata.h"

/** @fn deploy
 * @brief Erases flash and writes the hex array entry by entry into the flash
 * memory.
 * @param[in] none 
 * @param[Out] none
 */
void deploy()
{
	int read_address = 0x00b00000;  
	double count=0.0;

	spi_init();
	flash_device_id(); 

	printf("\n Erasing FLASH\n");

	flash_write_enable();
	flash_erase(read_address); 
	flash_status_register_read();

	flash_write_enable();
	flash_write(read_address,write_data[0]);
	flash_status_register_read();
	read_address+=4;

	for(int i =0; i< write_data[0]; i++)
	{
		flash_write_enable();
		flash_write(read_address,write_data[i+1]);
		flash_status_register_read();
		read_address+=4;
	}

	printf("\n Completed write to FLASH\n");
	asm volatile ("ebreak");
}

/** @fn main
 * @brief calls deploy function to load the code to flash memory
 * @param[in] none 
 * @param[Out] none
 */
void main(){

	deploy();
}

