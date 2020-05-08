/***************************************************************************
* Project                               :  shakti devt board
* Name of the file                      :  irrigationsystem.c
* Created date                          :  21.10.2019
* Brief Description of file             :  Sample project to demonstrate 
                                           integration of temperature and moiture sensors.
* Name of Author                        :  Anand Kumar S
* Email ID                              :  007334@imail.iitm.ac.in

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
#include "gpio.h"

extern void delay_loop(unsigned long cntr1, unsigned long cntr2);

#define MOTOR_ON (1 << 7)
#define MOTOR_OFF 0

/** @fn main
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */

void main()
{
    unsigned long readData = 0;
    unsigned long moistureDetetected = 0;

/*********************************************************************
   set the read & write bits in GPIO Direction Control Register
   Bit 0 for read, this corresponds to GPIO0 
   Bit 7 for write, this corresponds to GPIO7
*********************************************************************/
    write_word(GPIO_DIRECTION_CNTRL_REG, (0x00|MOTOR_ON));
    
    while (1) {
        readData = read_word(GPIO_DATA_REG);
        printf("\n Read Data:=%d", readData);
	moistureDetetected = ((readData & 1 ) == 1) ? 1 : 0;
        if (moistureDetetected == 0) {
            write_word(GPIO_DATA_REG, MOTOR_ON);
            printf("\nTurn on Motor");
        }
        else {
            write_word(GPIO_DATA_REG, MOTOR_OFF);
            printf("\nTurn off Motor");
        }
        delay_loop(1000,1000);
    } 
}
