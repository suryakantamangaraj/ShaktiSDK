/***************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: memory.c
 * Brief Description of file    : A library to display the memory contents
 * Name of Author    	        : Sathya Narayanan N
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
/**
@file memory.c
@brief A library to display the memory contents
@detail 
*/

/** @fn dump_word_memory
 * @brief dump contents of word addressabe location in the memory,
 *	 starting from the start address. 
 * @param unsigned int* 
 * @param unsigned int
 */
void dump_word_memory(unsigned int* start, unsigned int word_length)
{
	unsigned int i=0;
	void *address;

	address = (unsigned int *) start;

	while(i++< word_length)
	{
		log_info("address = %x data = %x\n", address, *(unsigned int *) address);
		address+=4;
	}
}

/** @fn dump_byte_memory
 * @brief dump contents of byte addressabe location in the memory,
 *	 starting from the start address. 
 * @param unsigned int*
 * @param unsigned int
 */
void dump_byte_memory(unsigned int* start, unsigned int word_length)
{
	unsigned int i=0;
	void *address;
	address = (unsigned char *) start;

	while(i++< word_length)
	{
		log_info("address = %x data = %x\n", address, *(unsigned char
							       *) address);
		address+=1;
	}
}
