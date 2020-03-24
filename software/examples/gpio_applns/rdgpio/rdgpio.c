/***************************************************************************
* Project           		   : shakti devt board
* Name of the file	     	   : rdgpio.c
* Brief Description of file    : Performs the reading operation with the help of gpio pins.
* Name of Author    	       : Sathya Narayanan N
* Email ID                     : sathya281@gmail.com

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

/** @fn delay_loop
 * @brief Maintains the required delay to perform an operation 
 * @warning No warning
 * @param[in] unsigned long, unsigned long
 * @param[Out] No output parameter
 */
extern void delay_loop(unsigned long cntr1, unsigned long cntr2);

/** @fn readData
 * @brief 
 * @details 
 * @warning 
 * @param[in] No input parameter
 * @param[Out] No output parameter
 */
void readData()
{
	unsigned long data = 0;
	write_word(GPIO_DIRECTION_CNTRL_REG, 0x00000000);

	while (1) {
		data =read_word(GPIO_DATA_REG);//copies the GPIO_DATA_REG Register contents//
		printf("\n Read Data is :%x", data);
		delay_loop(3000, 5000);
	}
}

/** @fn main
 * @brief 
 * @param[in] No input parameter
 * @param[Out] No output parameter
 */
void main()
{
    readData(); 
}


