/***************************************************************************
* Project           			:  shakti devt board
* Name of the file	     		:  hello.c
* Created date			        :  26.02.2019
* Brief Description of file             :  Does the printing of hello with the help of uart communication protocol.
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

#include "platform.h"
#include "shakti_uart.h"
#include "uart.h"

/** @fn main
 * @brief prints hello world 
 * @param[in] NULL
 * @param[Out] NULL
 */

void main()
{
	long long int i= 0xfffff;
	i = i;
	printf("%s","Hello world !");
	printf("\n%lu\n",i);
	printf("\n%llu\n",i);
	printf("\n%lld\n",i);
	printf("\n%ld\n",i);
while(1);

}


