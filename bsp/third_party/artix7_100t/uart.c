/*
uart.c - src file for uart

    Created by Arjun menon <c.arjunmenon@gmail.com> and Kotteeswaran <kottee.1@gmail.com>

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
*/

#include "uart.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define UART0_BASE_ADDRESS 0x11200
#define UART1_BASE_ADDRESS 0x11300

void uart_write(unsigned char offSet, unsigned char uartSel, unsigned char writeData)
{
	int * writeAddress = NULL;
	if(1 == uartSel )
		writeAddress = (UART1_BASE_ADDRESS + offSet);
	else
		writeAddress = (UART0_BASE_ADDRESS + offSet);

		*writeAddress  = writeData;

}

unsigned char uart_read(unsigned char offSet, unsigned char uartSel)
{
	int * readAddress = NULL;
	if(1 == uartSel )
		readAddress = (UART1_BASE_ADDRESS + offSet);
	else
		readAddress = (UART0_BASE_ADDRESS + offSet);
	return (*readAddress) ;
}

#undef getchar
int getchar()
{
 register char a0 asm("a0");
       asm volatile ("li t1, 0x11300" "\n\t" //The base address of UART config registers
           		  	"uart_statusr: lb t2, 40(t1)" "\n\t"
    				"andi t2, t2, 0x1" "\n\t"
	    			"beqz t2, uart_statusr" "\n\t"
                    "lb a0, 0(t1)"  "\n\t"      //The base address of UART data register
                    :
                    :
                    :"a0","t1","t2","cc","memory");

   return a0;
}

#undef putchar
int putchar(int ch)
{
  register char a0 asm("a0") = ch;
  asm volatile ("li t1, 0x11300" "\n\t"	//The base address of UART config registers
        "uart_status_simple: lb a1, 12(t1)" "\n\t"
        "andi a1,a1,0x2" "\n\t"
        "beqz a1, uart_status_simple" "\n\t"
				"sb a0, 4(t1)"  "\n\t"
				:
				:
				:"a0","t1","cc","memory");
  return 0;
}

// fnuction used to check if UART is empty. Can be used before exiting a function
int is_empty()
{
    asm volatile (
        "uart_end: li t1, 0x11300" "\n\t"	//The base address of UART config registers
        "lb a0, 12(t1)" "\n\t"
        "andi a0, a0, 0x1" "\n\t"
        "beqz a0, uart_end" "\n\t"
				:
				:
				:"a0","t1","cc","memory");
  return 0;
}
