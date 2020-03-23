/************************************************************************
 * Project           			: shakti devt board
 * Name of the file	     		: Keypad.c 
 * Brief Description of file    :
 * Name of Author    	        : Kotteeswaran
 * Email ID                     : kottee.1@gmail.com
  
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

************************************************************************/
#include "gpio.h"
#include "platform.h"
#include "keypad.h"//Includes the definitions of keypad function//

/* global variable definition*/

// initialize key and colrow to -1 indicate no key is pressed
int key = -1;
int col_row = -1;

unsigned int row_pins[ROWNUM];
unsigned int col_pins[COLNUM];
unsigned int col[4]={0, 1, 2, 3};
unsigned int row[4]={4, 5, 6, 7};
int key_map[COLNUM][ROWNUM];


int  key_table[4][4] =
{
	{  1,  4,  7,  0},
	{  2,  5,  8, 15},
	{  3,  6,  9, 14},
	{ 10, 11, 12, 13}
};

/** @fn set_pins
 * @brief This function sets the pins for the row and column
 * @details 
 * @warning 
 * @param[in] unsigned int*, unsigned int*
 * @param[Out] No output parameter
 */
void set_pins(unsigned int*  row, unsigned int* col)
{
	for(int i = 0 ; i < COLNUM ; i++)
	{
		col_pins[i] = col[i];// set col
	}
	for(int j = 0 ; j < ROWNUM ; j++) // set row
	{
		row_pins[j] = row[j];
	}
}

/** @fn set_key_map
 * @brief This function maps table in to keymap
 * @details 
 * @warning 
 * @param[in] int
 * @param[Out] No output parameter
 */
void set_key_map(int table[COLNUM][ROWNUM])
{
	for(int i = 0 ; i < COLNUM ; i++)
	{
		for(int j = 0 ; j < ROWNUM ; j++)
		{
			key_map[i][j] = table[i][j];
		}
	}
}

/** @fn get_key_another_way
 * @brief This function returns the corresponding value in the keymap
 * @details 
 * @warning 
 * @param[in] No input parameter
 * @param[Out] int
 */
int get_key_another_way()
{

	write_word(GPIO_DATA_REG, (0xF << OUTPINS_OFFSET) );

	for (int i = 0 ; i < COLNUM ; i++)
	{
		write_word(GPIO_DATA_REG, ~(0x1 << (OUTPINS_OFFSET + i) )   );

		for (int j = 0 ; j < ROWNUM ; j++)
		{
			if ( ( read_word(row_pins[j]) & (INPINS << INPINS_OFFSET )  ) == 0)
			{
				return key_map[i][j];
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
 * @param[in] int
 * @param[Out] int
 */
int get_key(int col_row)
{
    return key_map[col_row>>16][0xFFFF & col_row];
}

/** @fn get_col_row
 * @brief This function returns the column-row
 * @details Identifies the pressed key by making the corresponding coloumn
   low and reading the row values     
 * @warning 
 * @param[in] No output parameter
 * @param[Out] int
 */
int get_col_row(void)
{
	int col_row = 0;
	unsigned long read_value = 0;

	write_word(GPIO_DATA_REG, (0xF << OUTPINS_OFFSET) );

	for(int i = 0 ; i < COLNUM ; i++)
	{
		write_word(GPIO_DATA_REG, ~(0x1 << (/* OUTPINS_OFFSET  +*/ i) )   );

		for(int j = 0 ; j < ROWNUM ; j++)
		{
			read_value =  read_word(GPIO_DATA_REG);

			if( ( read_value & (1 << row_pins[j] ) ) == 0 )
			{
					return key_map[i][j];
			}
		}

		write_word(GPIO_DATA_REG, (0xF << OUTPINS_OFFSET) );
	}

	return -1;
}

/** @fn gpio_init
 * @brief This maps the keypad from pins
 * @details    
 * @warning 
 * @param[in] No input parameter
 * @param[Out] No output parameter
 */
void gpio_init()
{
	set_pins(row, col);

	set_key_map(key_table);

	//Configure direction of GPIO pins (1 ---> Output, 0 --> input)
	write_word(GPIO_DIRECTION_CNTRL_REG, OUTPINS);
}

/** @fn main
 * @brief 
 * @details    
 * @warning 
 * @param[in] No input parameter
 * @param[Out] int
 */
int main()
{
	int prev_col_row = 0;
	gpio_init(); //Intialization of gpio //

	printf("\nGPIO Init Done");
	while(1)
	{
		col_row = get_col_row();

		if( col_row != -1 )
		{
			log_info("\nThe %x Key Pressed", col_row);
				delay_loop(600, 2000);
		}
	}

	return 0;
}
