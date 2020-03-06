/***************************************************************************
 * Project           			: shakti devt board
 * Name of the file	     		: tglgpio.c
 * Created date			        : 2.01.2020
 * Brief Description of file    : Control an led with the help of a read from Spansion Flash.
 * Name of Author    	        : G Nambirajan
 * Email ID                     : nambirajan2004@gmail.com

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
#include "gpio.h" // includes definitions of gpio pins and read, write functions//
#include <stdint.h>
#include "spi.h"

#define PINMUX_CONF_REG 0x40310

int * pinmux_reg  =   (const int*) PINMUX_CONF_REG;

/** @fn delay_loop
 * @brief Maintains the required delay to perform an operation
 * @warning No warning
 * @param[in] Delay Required(ms)
 * @param[Out] No output parameter
 */
extern void delay_loop(unsigned long cntr1, unsigned long cntr2);

/** @fn main
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
void main(){
	*pinmux_reg = 0x154000;
	int i=4;
	spi_init();
	printf("SPI init done\n");
	flash_device_id();
	waitfor(200);
	int total_data = 10; //total data you want to read/write
	int read_address = 0x00b00000;  //read from this address
	int* bram_address = (int*) 0x80010000; //write to this address

	int read_value= flash_read(read_address);
		printf("Flash write done on address %x \n", read_address);
        printf("data:%x \n",read_value); 
		*(bram_address+i) = read_value;
	


	*pinmux_reg = 0x000;
	write_word(GPIO_DIRECTION_CNTRL_REG, 0x00FFFFFF);

	while (1) {
		write_word(GPIO_DATA_REG, read_value);
		delay_loop(1000,1000);
		write_word(GPIO_DATA_REG, 0x00);
		delay_loop(1000, 1000);
	}


	while(1);
} 
