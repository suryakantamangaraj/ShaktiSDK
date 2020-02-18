/************************************************************************
 * Project           			:  Shakti development board
 * Name of the file	     		:  Intruder detection.c
 * Created date			        :  28.01.2020
 * Brief Description of file    :  This is a program for Intruder Detection System which uses PIR Sensor to detect any intrusion
 *                                   	    			        	
     Modified to SHakti by Sambhav Jain 
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

/**
 * @file intruder_detection.h
 * @project shakti devt board
 * @brief   .
 * @detail Include File Definitions	
 */

#if !defined(INTRUDER_DETECTION_H)
#define INTRUDER_DETECTION_H

#define KYPD_ROWNUM 4
#define KYPD_COLNUM 4

#define OUTPINS_OFFSET 0
#define INPINS_OFFSET 4
#define OUTPINS (0xF << OUTPINS_OFFSET)
#define INPINS  (0xF << INPINS_OFFSET)

//LED Pins
#define LED_P1          GPIO16
#define LED_P2          GPIO19
#define Buzzer          GPIO11
#define LED_P3          GPIO18
#define LED_P4          GPIO21

#define panicButton     GPIO28          //Input 
#define powerSwitch     GPIO24
#define deactivateSwitch GPIO25

#define GPIO_OUTPINS    (LED_P1 | LED_P2 | LED_P3 | LED_P4 | Buzzer)
#define PIR_IN	        GPIO8
#define PANIC_BUTTON_OFFSET 28
#define PIR_OFFSET          8
#define ALARM_TIMER         5          //


#define HIGH                1
#define LOW                 0

//Keypad 
#define passNum         4               //Number of Digits Password
//function prototype
void setPins(unsigned int* row, unsigned int* col);
void setKeyMap(int table[KYPD_COLNUM][KYPD_ROWNUM]);
int getKey();
int getColRow(void);
unsigned int rowPins[KYPD_ROWNUM];
unsigned int colPins[KYPD_COLNUM];
int keyMap[KYPD_COLNUM][KYPD_ROWNUM];

#endif
