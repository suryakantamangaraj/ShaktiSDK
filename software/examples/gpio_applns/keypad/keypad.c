/************************************************************************
 * Project           			:  shakti devt board
 * Name of the file	     		:  keypad.c
 * Created date			        :  26.02.2019
 * Brief Description of file     : This is an example on how to get the value of
 a key  pressed on a Pmod keypad.
 * keypad details : https://reference.digilentinc.com/reference/pmod/pmodkypd/start

  Author:	Michelle Yu				        	
  Copyright (c) 2011, Digilent Inc.  	    			        
	
  Modified to SHakti by Kottee.1@gmail.com

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/***********************************************************
*		Include File Definitions
************************************************************/

#include "gpio.h"
#include "platform.h"
#include "keypad.h"//Includes the definitions of keypad function//

/* global variable definition*/

// initialize key and colrow to -1 indicate no key is pressed
int key = -1;
int colRow = -1;

unsigned int rowPins[KYPD_ROWNUM];
unsigned int colPins[KYPD_COLNUM];
unsigned int col[4]={0, 1, 2, 3};
unsigned int row[4]={4, 5, 6, 7};
int keyMap[KYPD_COLNUM][KYPD_ROWNUM];

int  keyTable[4][4] =
{
	{  1,  4,  7,  0},
	{  2,  5,  8, 15},
	{  3,  6,  9, 14},
	{ 10, 11, 12, 13}
};

/** @fn void  setPins(unsigned int*  row, unsigned int* col)
 * @brief This function sets the pins for the row and column
 * @details Creates temp. copy of the col and row pins.
 * @warning 
 * @param[in] row,column
 * @param[Out] NULL
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

/** @fn void setKeyMap(int table[KYPD_COLNUM][KYPD_ROWNUM])
 * @brief This function maps table in to keymap
 * @details Maps the values to all the key entries.
 * @warning 
 * @param[in] KYPD_COLNUM,KYPD_ROWNUM
 * @param[Out] NULL
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

/** @fn int getKeyAnotherWay()
 * @brief This function returns the corresponding value in the keymap
 * @details 
 * @warning 
 * @param[in] NULL
 * @param[Out] int
 */

int getKeyAnotherWay()
{

	write_word(GPIO_DATA_REG, (0xF << OUTPINS_OFFSET) );

	for(int i = 0 ; i < KYPD_COLNUM ; i++)
	{
		write_word(GPIO_DATA_REG, ~(0x1 << (OUTPINS_OFFSET + i) )   );

		for(int j = 0 ; j < KYPD_ROWNUM ; j++)
		{
			if( ( read_word(rowPins[j]) & (INPINS << INPINS_OFFSET )  ) == 0)
			{
				return keyMap[i][j];
			}
		}
		write_word(GPIO_DATA_REG, (0xF << OUTPINS_OFFSET) );
	}

	return 0;
}

/** @fn int getKey(int colRow)
 * @brief This function returns the corresponding value in the keymap
          of the 32bit column-row indicator
 * @details 
 * @warning 
 * @param[in] colRow - a 32 bit column-row indicator, where the first 16 bit is
                       column and the last 16 bit is row
 * @param[Out]  int - key pressed
 */

int getKey(int colRow)
{
    return keyMap[colRow>>16][0xFFFF & colRow];
}

/** @fn int getColRow(void)
 * @brief This function returns the column-row
 * @details Identifies the pressed key by making the corresponding coloumn
            low and reading the row values.
 * @warning 
 * @param[in] NULL
 * @param[Out] int
 */

int getColRow(void)
{
	int colRow = 0;
	unsigned long readValue = 0;

	write_word(GPIO_DATA_REG, (0xF << OUTPINS_OFFSET) );

	for(int i = 0 ; i < KYPD_COLNUM ; i++)
	{
		write_word(GPIO_DATA_REG, ~(0x1 << (/* OUTPINS_OFFSET  +*/ i) )   );

		for(int j = 0 ; j < KYPD_ROWNUM ; j++)
		{
			readValue =  read_word(GPIO_DATA_REG);
//			printf("\n The read value is %lx; rowPins: %x", (readValue), rowPins[j]);

			if( ( readValue & (1 << rowPins[j] ) ) == 0 )
			{
	//			printf("\n The read value is %lx; [i:%d; j:%d] rowPins: %d; keyMap=%d", readValue, i, j, rowPins[j], keyMap[i][j]);
					return keyMap[i][j];
			}
		}

		write_word(GPIO_DATA_REG, (0xF << OUTPINS_OFFSET) );
	}

	return -1;
}

/** @fn void gpio_init()
 * @brief This maps the keypad from pins.
 * @details 
 * @warning 
 * @param[in] rows,columns
 * @param[Out] NULL
 */

void gpio_init()
{
	setPins(row, col);

	setKeyMap(keyTable);

	//Configure direction of GPIO pins (1 ---> Output, 0 --> input)
	write_word(GPIO_DIRECTION_CNTRL_REG, OUTPINS);
}

/** @fn int main()
 * @brief 
 * @details 
 * @warning 
 * @param[in] NULL
 * @param[Out] int
 */

int main()
{
	int prevColRow = 0;
	gpio_init(); //Intialization of gpio //

	printf("\nGPIO Init Done");
	while(1)
	{
		colRow = getColRow();

		if( colRow != -1 )
		{
//			key = getKey(colRow);
#if 0
				if(prevColRow != colRow)
				{
//			printf("\ncol: %d; row: %d is value: %d", colRow >> 16, (0xFFFF & colRow), key );
				prevColRow = colRow;
				printf("\nThe %x Key Pressed", colRow);
				}
#else
				printf("\nThe %x Key Pressed", colRow);
				DelayLoop(600, 2000);
#endif
		}

//		DelayLoop(100,2000);
	}

	return 0;
}
