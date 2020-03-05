/***************************************************************************
* 
* Project           			        :  shakti devt board
* Name of the file	     		        :  light_blocking.c
* Created date			                :  20.08.2019
* Name of Author               		    :  Soutrick Roy Chowdhury
* Email ID                       	    :  soutrick97@gmail.com
*

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

*****************************************************************************/


#include "gpio.h"
#include "platform.h"
#include <stdio.h>

extern void delay_loop(unsigned long cntr1, unsigned long cntr2);

/** @fn main
 * @brief Gives output as HIGH when partition is introduced and LOW when partition is removed       with the help of gpio pins 
 * @details    
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
void main()
{   
    unsigned long readData = 0;
    write_word(GPIO_DIRECTION_CNTRL_REG, 0x0000);

    while (1) {
        readData = read_word(GPIO_DATA_REG);

        if(readData == 0x00000001) {
            printf("\n Blocked");
        }
        else {
            printf("\n Not Blocked");
        }
        delay_loop(1000,1000);
    }
}
    
