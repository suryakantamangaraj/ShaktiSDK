/***************************************************************************
* Project           			:  shakti devt board
* Name of the file	     		:  btnled.c
* Created date			        :  26.02.2019
* Brief Description of file             :  Controls the led operation with help of button,gpio based.
* Name of Author    	                :  Sathya Narayanan N & Raghav
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
#include "gpio.h" // includes definitions of gpio pins and read, write function
#include "platform.h"

/*********************************************************************
* Brief Description     : Performs the intilization of the corresponding registers of gpio pins.
* Parameters            : Registers,conrol word.
********************************************************************/
/** @fn void init()
 * @brief Performs the intilization of the corresponding registers of gpio pins.
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
void init()
{
	write_word(GPIO_DIRECTION_CNTRL_REG, ~(1 << 0) );
}

/*********************************************************************
* Brief Description     : Performs the printing of hello. 
* Return                : int.
********************************************************************/
/** @fn int main(void)
 * @brief Performs the printing of hello. 
 * @details 
 * @warning
 * @param[in] 
 * @param[Out] 
 */
int main(void)
{
	printf("Hello\n");
	
	init();

	while(1)
	{
		unsigned long readData = 0;

		readData =  read_word(GPIO_DATA_REG) & 0x1;//copies the GPIO_DATA_REG Register contents// 


		printf("\n Read Data is :0x%08lx", readData);

		if (readData )/*if readdata */
		{
			printf("; LED ON");
			write_word(GPIO_DATA_REG, 0X2);//makes the led to turn on//
		}
		else/*if not */
		{
			printf("; LED OFF");
			write_word(GPIO_DATA_REG, 0X0);//makes the led to turn off//
		}
		DelayLoop(1000,1000);
	}
	
	int count =1;

	while(count < 200)
	{
		count =count+1;
	};
	asm volatile("exit_handler : j exit_handler");
	return 0;
}
