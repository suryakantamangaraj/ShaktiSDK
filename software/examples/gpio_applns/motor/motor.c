/***************************************************************************
 * Project           			:  shakti devt board
 * Name of the file	     		:  motor.c
 * Created date			        :  26.02.2019
 * Brief Description of file             :  Determines the functioning of stepper motor with the  help of gpio pins.  
 * Name of Author    	                :  Sathya Narayanan N
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
#include <stdio.h>/* Includes definitions of standard input/output functions*/
#include "gpio.h"/*Incudes the defintions of gpio functions and registers*/
#include "platform.h"

#define MOTOR_FORWARD_CNTRL (0xA << 0)/*Defines the Required Forward control word*/
#define MOTOR_REVERSE_CNTRL (0x5 << 0)/*Defines the Required Reverse control word*/
/*********************************************************************
 * Brief Description     : Performs the intilization of the corresponding registers of gpio pins.
 * Parameters            : Registers,conrol word.
 ********************************************************************/
void main()
{
	printf("Motor Control\n");
	write_word(GPIO_DIRECTION_CNTRL_REG, 0xFFFFFFFF);

#ifndef ARTIX7_35T
	write_word(GPIO_PULL_UP_CNTRL_REG, 0x00);
	write_word(GPIO_DRV_CNTRL_REG0, 0xFFFFFFFF);
	write_word(GPIO_DRV_CNTRL_REG1, 0xFFFFFFFF);
	write_word(GPIO_DRV_CNTRL_REG2, 0x00);
	write_word(GPIO_MODE_SEL_REG, 0xFFFFFFFF);
	write_word(GPIO_MODE_SEL_REG, 0xFFFFFFFF);
#endif

	while(1)
	{
		write_word(GPIO_DATA_REG, MOTOR_FORWARD_CNTRL);
		printf("Forward\n");
		printf("GPIO Data Register Value: %d\n",GPIO_DATA_REG);
		DelayLoop(5000, 5000);

		write_word(GPIO_DATA_REG, MOTOR_REVERSE_CNTRL);
		printf("Reverse\n");
		printf("GPIO Data Register Value: %d\n",GPIO_DATA_REG);
		DelayLoop(5000, 5000);
	}

	DelayLoop(5000, 5000);
}