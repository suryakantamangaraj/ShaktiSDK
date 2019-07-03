/************************************************************************
* Project           			:  shakti devt board
* Name of the file	     		:  uart.h
* Brief Description of file             :  Header file for uart.
*  Name of Author    	                :  Sathya Narayanan N
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

   ************************************************************************/
#ifndef UART_H
#define UART_H
// UART TX (W) and RX (R) buffers
#define UART_DATA_REGISTER 0
// UART interrupt enable (RW)
#define UART_INT_ENABLE_REGISTER 1
// UART interrupt identification (R)
#define UART_INT_IDENTI_REGISTER 2
// UART FIFO control (W)
#define UART_FIFO_CTRL_REGISTER 2
// UART Line Control Register (RW)
#define UART_LINE_CTRL_REGISTER 3
// UART Modem Control (W)
#define UART_MODEM_CTRL_REGISTER 4
// UART Line Status (R)
#define UART_LINE_STATUS_REGISTER 5
// UART Modem Status (R)
#define UART_MODEM_STATUS_REGISTER 6
// UART base address of peripheral in NIOS memory map
#define UART_SCRATCH_REGISTER 7

// UART Divisor Registers offsets
#define UART_DIVISOR_LSB_LATCH_REGISTER 0
#define UART_DIVISOR_MSB_LATCH_REGISTER 1


#define INPUT_CLOCK_FREQ 20000000

#define UART0 0
#define UART1 1


int uart_0_init();

void uart_write(unsigned char offSet, unsigned char uartSel, unsigned char writeData);

unsigned char uart_read(unsigned char offSet, unsigned char uartSel);

void uart_1_init(int baud);

int putchar(int ch);

int getchar();

#endif
