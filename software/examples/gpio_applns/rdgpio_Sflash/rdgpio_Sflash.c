/***************************************************************************
* Project           			:  shakti devt board
* Name of the file	     		:  rdgpio.c
* Created date			        :  19.01.2020
* Brief Description of file     :  Performs the reading operation with the help of gpio pins and write in spantionflash.
* Name of Author    	        :  G Nambirajan
* Email ID                      :  nambirajan2004@gmail.com

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

#include <stdio.h>//includes the definitions of standard input/output functions
#include "gpio.h" // includes definitions of gpio pins and read, write functions
#include "platform.h"
#define PINMUX_CONF_REG 0x40310
int * pinmux_reg  =   (const int*) PINMUX_CONF_REG;
extern void delay_loop(unsigned long cntr1, unsigned long cntr2);

/** @fn main
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] NULL
 */

void main()
{
	unsigned long readData = 0;
	write_word(GPIO_DIRECTION_CNTRL_REG, 0x00000000);
	readData =read_word(GPIO_DATA_REG);//copies the GPIO_DATA_REG Register contents//
	printf("\n Read Data is :%x\n", readData);
	delay_loop(1000, 1000);
	write_word(GPIO_DIRECTION_CNTRL_REG, 0xFFFFFFFF);
	//*pinmux_reg = 0x154000;
	int write_address = 0x00b00000;  // read/write from/to this address
	int data = readData; //32 bits of data can be written at a time
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
}
