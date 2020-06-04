/***************************************************************************
* Project           		:  shakti devt board
* Name of the file	     	:  hello.c
* Brief Description of file     :  Does the printing of hello with the help of uart communication protocol.
* Name of Author    	        :  Sathya Narayanan N
* Email ID                      :  sathya281@gmail.com

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
@file hello.c
@brief Does the printing of hello with the help of uart communication
@detail 
*/

#include<uart.h>

/** @fn void main()
 * @brief prints hello world
 */
void main()
{
	float x=.9898;

	printf ("Hello World !\n");
	printf ("%f\n",x);
	 x=0.8;
	printf ("%f\n",x);
}
