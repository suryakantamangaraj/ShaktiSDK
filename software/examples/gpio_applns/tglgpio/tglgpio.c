/***************************************************************************
* Project           			: shakti devt board
* Name of the file	     		: tglgpio.c
* Brief Description of file     : Control an led with the help of a button, gpio based.
* Name of Author    	        : Sathya Narayanan N
* Email ID                      : sathya281@gmail.com

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

#include "platform.h"
#include "utils.h" 
#include "gpio.h" 

/** @fn tglgpio
 * @brief Performs the toggling operation  with the help of button.
 * @warning No warning
 * @param[in] Registers,control word
 * @param[Out] No output parameter
 */
void tglgpio()
{
//Assumption 1 ---> output, 0 ---> input
	write_word(GPIO_DIRECTION_CNTRL_REG, 0x00FFFFFF);

	while (1) {
		write_word(GPIO_DATA_REG, 0x00FFFFFF);
		delay_loop(1000, 5000);
		write_word(GPIO_DATA_REG, 0x00);
		delay_loop(1000, 5000);
	}
}

/** @fn main
 * @brief Initiates writing to gpio pins by calling tglgpio
 * @warning No warning
 * @param[in] No input parameter
 * @param[Out] No output parameter
 */ 
void main()
{
	tglgpio();
	return 0;
}

