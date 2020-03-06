/************************************************************************
 * Project           			: Shakti development board
 * Name of the file	     		: Intruder detection.c
 * Created date			        : 28.01.2020
 * Brief Description of file    : This is a program for Intruder Detection System which uses PIR Sensor to detect any intrusion
 * Modified to Shakti by        : Sambhav Jain  
 * Email ID                     : sambhav.jv@gmail.com             	    			        	
 
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
 along with this program.  If not, see <https://www.gnu.org/licenses/>

****************************************************************************************/

/***********************************************************
 *		Pin Definitions
 ************************************************************/
// GPIOx       - Pin Mapped
//     	0       -Keypad Top Line-4   	(Output)
//		1       -Keypad Top Line-3		(Output)
// 		2       -Keypad Top Line-2		(Output)
//		3       -Keypad Top Line-1		(Output)
//		4       -Keypad Bottom Line-4	(Output)
//		5       -Keypad Bottom Line-3	(Output)
//		6       -Keypad Bottom Line-2	(Output)
//		7       -Keypad Bottom Line-1	(Output)
//		Gnd		-Keypad Bottom Line-5	
//		Vcc		-Keypad Bottom Line-6	


//		8		-PIR Sensor Output Pin	(Input)
//		16		-LED P1					(Output)
//		19		-LED P2					(Output)
//		11		-Buzzer					(Output)
//		18		-LED P3					(Output)
//		21		-LED P4					(Output)
//		28		-Panic Button			(Input)
//		24		-Power Switch   		(Input)
//		25		-Deactivation Switch	(Input)

/***********************************************************
 		Include File Definitions
************************************************************/
#include "gpio.h"
#include "platform.h"
#include "intruder_detection.h"  //Includes the definitions//

/* global variable definition*/

int PIR_presentState = 0;
int PIR_previousState = 0;

int panicPresentState=0;
int panicPreviousState=0;

int alarmPresentState=0;
int alarmPreviousState=0;

int firstFlag = 1; 
int alarmFlag = 0;
int deactivateFlag = 0;
int alarmCounterFlag=1; //Default value 1
int keypadPasswordFlag=0;

int alarmCounter = 0;
int keypadCounter= 0;

// initialize key and colrow to -1 indicate no key is pressed
int key = -1;
int colRow = -1;

unsigned int rowPins[KYPD_ROWNUM];
unsigned int colPins[KYPD_COLNUM];
unsigned int col[4]={0, 1, 2, 3};
unsigned int row[4]={4, 5, 6, 7};
int keyMap[KYPD_COLNUM][KYPD_ROWNUM];
//Password
int passData[passNum];

//
int  keyTable[4][4] =
{
	{  1,  4,  7,  0},
	{  2,  5,  8, 15},
	{  3,  6,  9, 14},
	{ 10, 11, 12, 13}
};


/** @fn WriteGPIO
 * @brief This function Writes to the Data Register 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
void WriteGPIO(unsigned long GPIO_pin,int GPIO_pin_mode )
{
	unsigned long read_data = 0;
	read_data = read_word(GPIO_DATA_REG);
	if(GPIO_pin_mode == 1)
	{
		write_word (GPIO_DATA_REG, ( read_data | (GPIO_pin ) ) );
	}
	else
	{
		write_word(GPIO_DATA_REG, ( read_data & (~GPIO_pin) ) );  
	}

}

/** @fn PIR_ReadState
 * @brief Reads the State of the PIR Sensor Output 
 * @details 
 * @warning 
 * @param[in] Data Register
 * @param[Out] 
 */
int PIR_ReadState(unsigned long tempReadData)
{
	PIR_presentState= ((PIR_IN & tempReadData)>>PIR_OFFSET);  
	if( (PIR_presentState== 1) && (PIR_previousState== 0) )
	{
		//State of 0->1
		//printf("\nHuman Detected - Intrusion Alert %x -- %x ",PIR_presentState,PIR_previousState);
		PIR_previousState = PIR_presentState;
		return 1;
	}
	else if((PIR_presentState== 1) && (PIR_previousState== 1))
	{
		//State of 1 -> 1

		// printf("\nCode 2 %x -- %x ",PIR_presentState,PIR_previousState);
		PIR_previousState = PIR_presentState;
		return 2;
	}
	else
	{
		//State of 1->0 and 0->0
		//printf("\n. %x -- %x",PIR_presentState,PIR_previousState);
		PIR_previousState =PIR_presentState;
		return 0;
	}
}

/** @fn panicButtonReadState
 * @brief Reads the State of the Panic Button 
 * @details 
 * @warning 
 * @param[in] Data Register
 * @param[Out] 
 */
int panicButtonReadState(unsigned long tempReadData)
{
	panicPresentState= ((panicButton & tempReadData)>>PANIC_BUTTON_OFFSET);  
	if( (panicPresentState== 1) && (panicPreviousState== 0) )
	{
		// printf("\nHuman Detected - Intrusion Alert %x -- %x ",PIR_presentState,PIR_previousState);
		// printf("\nSOS -Panic Button Activated");

		panicPreviousState= panicPresentState;
		return 1;
	}
	else if((panicPreviousState == 1) && (panicPresentState == 1))
	{
		//Function Returns 2 when mode is 1-1 (present and prev state)
		// printf("\nCode 2 %x -- %x ",PIR_presentState,PIR_previousState);
		panicPreviousState= panicPresentState;;
		return 2;
	}
	else
	{
		// printf("\n. %x -- %x",PIR_presentState,PIR_previousState);
		panicPreviousState= panicPresentState;
		return 0;
	}
}

/** @fn buzzerTone
 * @brief Outputs the Buzzer Tone
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
void buzzerTone()
{
	int i=0;
	for (i = 0; i < 4; i++)
	{
		//printf("\nbuzz");

		WriteGPIO(Buzzer,HIGH);	//Sends tone
		delay_loop(800,800);
		WriteGPIO(Buzzer,LOW);		//No tone
		delay_loop(500,500);
	}
}

/** @fn setPins
 * @brief This function sets the pins for the row and column
 * @details 
 * @warning 	
 * @param[in] 
 * @param[Out] 
 */
void  setPins(unsigned int*  row, unsigned int* col)
{
	for(int i = 0 ; i < KYPD_COLNUM ; i++)
	{
		colPins[i] = col[i];// set col
	}
	for(int j = 0 ; j < KYPD_ROWNUM ; j++) // set row
	{
		rowPins[j] = row[j];
	}

}

/** @fn setKeyMap
 * @brief This function maps table in to keymap
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
void setKeyMap(int table[KYPD_COLNUM][KYPD_ROWNUM])
{

	for(int i = 0 ; i < KYPD_COLNUM ; i++)
	{
		for(int j = 0 ; j < KYPD_ROWNUM ; j++)
		{
			keyMap[i][j] = table[i][j];
		}
	}
}

/** @fn getKeyAnotherWay
 * @brief This function returns the corresponding value in the keymap
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
int getKeyAnotherWay()
{
	write_word(GPIO_DATA_REG, (0xF << OUTPINS_OFFSET) );

	for (int i = 0 ; i < KYPD_COLNUM ; i++)
	{
		write_word(GPIO_DATA_REG, ~(0x1 << (OUTPINS_OFFSET + i) )   );

		for (int j = 0 ; j < KYPD_ROWNUM ; j++)
		{
			if ( ( read_word(rowPins[j]) & (INPINS << INPINS_OFFSET )  ) == 0)
			{
				return keyMap[i][j];
			}
		}
		write_word(GPIO_DATA_REG, (0xF << OUTPINS_OFFSET) );
	}
	return 0;
}

/** @fn getkey
 * @brief This function returns the corresponding value in the keymap
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
int getKey(int colRow)
{
	return keyMap[colRow>>16][0xFFFF & colRow];
}

/** @fn getColRow
 * @brief This function returns the column-row
 * @details Identifies the pressed key by making the corresponding coloumn
 low and reading the row values     
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
int getColRow(void)
{
	int colRow = 0;
	unsigned long readValue = 0;
	unsigned long tempReadData = 0;

	//Masking Data Reg 
	tempReadData = read_word(GPIO_DATA_REG);
	write_word(GPIO_DATA_REG,( tempReadData | (0xF << OUTPINS_OFFSET) ) );

	for(int i= 0 ; i < KYPD_COLNUM ; i++)
	{
		tempReadData = read_word(GPIO_DATA_REG);
		write_word(GPIO_DATA_REG, ( (0xF << OUTPINS_OFFSET)  &  (~(0x1 << (/* OUTPINS_OFFSET  +*/i) ) ) ) );

		for(int j = 0 ; j < KYPD_ROWNUM ; j++)
		{
			readValue =  read_word(GPIO_DATA_REG);
			//printf("\n The read value is %lx; rowPins: %x", (readValue), rowPins[j]);
			if( ( readValue & (1 << rowPins[j] ) ) == 0 )
			{
				//printf("\n The read value is %lx; [i:%d; j:%d] rowPins: %d; keyMap=%d", readValue, i, j, rowPins[j], keyMap[i][j]);
				return keyMap[i][j];
			}
		}
		tempReadData = read_word(GPIO_DATA_REG);
		write_word(GPIO_DATA_REG,(tempReadData | (0xF << OUTPINS_OFFSET) ) );
	}

	return -1;
}

/** @fn gpio_init
 * @brief This maps the keypad from pins
 * @details    
 * @warning 
 * @param[in] rows,columns
 * @param[Out] NULL
 */
void gpio_init()
{
	setPins(row, col);	
	setKeyMap(keyTable);

	unsigned long read_data = 0;
	read_data = read_word(GPIO_DIRECTION_CNTRL_REG);
	write_word (GPIO_DIRECTION_CNTRL_REG, ( read_data | (OUTPINS ) ) );

	read_data = read_word(GPIO_DIRECTION_CNTRL_REG);
	//Configure direction of GPIO pins (1 ---> Output, 0 --> input)
	write_word(GPIO_DIRECTION_CNTRL_REG, ( read_data | GPIO_OUTPINS ) );
	//printf("\n GPIO Init- %x",(read_data | GPIO_OUTPINS));


	//All the LED initially set to LOW
	WriteGPIO(LED_P1,LOW);
	WriteGPIO(LED_P2,LOW);
	WriteGPIO(LED_P3,LOW);
	WriteGPIO(LED_P4,LOW);
	WriteGPIO(Buzzer,LOW);
}

/** @fn main
 * @brief 
 * @details    
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
int main()
{
	//Clearing the Data Register
	unsigned long readData = 0;
	printf("\n\n\tIntrusion Detection System");
	int prevColRow = 0;
	gpio_init(); //Intialization of gpio //

	printf("\nInitialising...");
	while(1)
	{	

		readData = read_word(GPIO_DATA_REG);
		if(powerSwitch & readData)
		{
			if(firstFlag)
			{
				//First time giving the sensor to calibrate 
				delay_loop(4000,4000);
				printf("\nIntruder System activated");
				firstFlag=0;
				alarmCounterFlag =1;
			}
			//Intruder System - ON
			WriteGPIO(LED_P2,HIGH);

			//Deactivation of Alarm Switch
			if(deactivateSwitch & readData)
			{
				deactivateFlag =1;
			}
			else
			{
				deactivateFlag =0;
			}

			int tempReadPIR  =PIR_ReadState(readData);
			int tempReadPanic=panicButtonReadState(readData);
			alarmPresentState= ((tempReadPIR > 0) || (tempReadPanic== 1) || alarmFlag==1 ) && (deactivateFlag == 0);

			if(alarmPresentState == 1 && alarmPreviousState ==0)
			{
				//printf("\n%x   %x",alarmPreviousState,alarmPresentState);
				if(tempReadPIR == 1){printf("\nHuman Detection\nDeactivate to stop Alarm");  }
				else if(tempReadPanic== 1){printf("\nPanic Button\nDeactivate to stop Alarm");}
				//else {printf("\nDeactivate the Alarm to stop...");}

				WriteGPIO(LED_P1,HIGH);
				buzzerTone();
				alarmFlag =1;



				alarmPreviousState = alarmPresentState;

			}
			else if(alarmPresentState == 1 && alarmPreviousState == 1)
			{
				//printf("\n%x   %x",alarmPreviousState,alarmPresentState);
				WriteGPIO(LED_P1,HIGH);
				buzzerTone();
				alarmFlag =1;
				alarmPreviousState = alarmPresentState;


				alarmCounter++;
				//printf("\n\t\t\t%x",alarmCounter);
				if(alarmCounter == ALARM_TIMER & ( alarmCounterFlag ==1 ) )
				{
					WriteGPIO(LED_P3,HIGH);

					printf("\nContacting Police for Assistance");
					alarmCounterFlag=0;
					alarmCounter=0;
				}
				else if(alarmCounter == ALARM_TIMER)
				{
					//Making Sure the alarm counter does not overflow
					alarmCounter=0;
				}

			}
			else if(alarmPresentState == 0 && alarmPreviousState == 1)
			{
				//printf("\n%x   %x",alarmPreviousState,alarmPresentState);
				//printf("\n.");
				alarmFlag =0;
				WriteGPIO(LED_P1,LOW);


				WriteGPIO(LED_P3,LOW);
				alarmCounterFlag =1;
				alarmCounter=0;

				printf("\nAlarm Succesfully devactivated successfully");
				alarmPreviousState = alarmPresentState;

			}
			else
			{
				//Flags
				alarmFlag =0;
				alarmCounter=0;
				alarmCounterFlag =1;

				//WriteGPIO(LED_P3,LOW);
				WriteGPIO(LED_P1,LOW);
				alarmPreviousState = alarmPresentState ;
			}

			colRow = getColRow();
			//KeyPad Sensor 
			if( colRow != -1 )
			{
				printf("\nThe %x Key Pressed", colRow);

				if( colRow == keyMap[3][3])
				{
					printf("\nEnter Password-");
					delay_loop(600, 2000);
				}
			}
			else
			{	
				//Intruder System Off
				WriteGPIO(LED_P2,LOW);
				firstFlag=1;
				//printf("\nIntruder System Deactivated");
			}
			//end of infinite while loop
		}

		return 0;
	}
}
