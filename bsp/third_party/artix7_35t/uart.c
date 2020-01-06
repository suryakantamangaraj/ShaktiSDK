/*
    uart.c - src  file for uart

    Created by Niketan Shahapur <niketanshahpur@gmail.com>

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
#include "platform.h"



#define RECV_NOT_EMPTY   0x8
#define TRANS_NOT_FULL   0x2
#define OFFSET_TXREG     0x4
#define OFFSET_RXREG     0x8
#define OFFSET_STATUSREG 0xC


#define STATUS_REG ((volatile unsigned char *)(UART0_START + 0xC)) /* 8 bits */
#define WRITE_REG  ((volatile unsigned char *)(UART0_START + 0x4)) /* 8 bits */
#define READ_REG   ((volatile unsigned char *)(UART0_START + 0x8)) /* 8 bits */

volatile unsigned char* status_reg;
volatile unsigned char* write_reg;
volatile unsigned char* read_reg;
short int* baud;

/**
 * @fn int read_uart(uart_num sel, unsigned int baudrate)
 * @brief Function to provide a generic API for getchar functionality.
 * @details This function will be called to read  a single character from the stdin by passing 
 * uart number for different offset addresses, and baudrate value for different baudrates.
 * @warning 
 * @param[in] UART number, and baudarate. 
 * @param[Out] Character as int.
 */
int read_uart(uart_num sel, unsigned int baudrate)
{
	if(sel == 0)
	{
		baud = UART0_START;
		read_reg = (UART0_START + OFFSET_RXREG);
		status_reg = (UART0_START + OFFSET_STATUSREG);
	}
	else if(sel == 1)
	{
		baud = UART1_START;
		read_reg = (UART1_START + OFFSET_RXREG);
                status_reg = (UART1_START + OFFSET_STATUSREG);
	}
	else
	{
		baud = UART2_START;
		read_reg = (UART2_START + OFFSET_RXREG);
                status_reg = (UART2_START + OFFSET_STATUSREG);
	}
	/*
                 --------------Baud Calculation------------
                   Baud = Clock_rate/(16 * Baudrate)
        */
	switch(baudrate)
	{
		case 9600:	*baud = (short int)325;
				break;
		case 19200:	*baud = (short int)162;
				break;
		case 38400:	*baud = (short int)81;
				break;
		case 57600:	*baud = (short int)54;
				break;
		case 115200:	*baud = (short int)27;
				break;
		default:	*baud = (short int)325;
                                break;
        }
	char *ch;
        while((*status_reg & RECV_NOT_EMPTY) == 0);
        ch = read_reg;
        return *ch;
}

/**
 * @fn int write_uart(int ch, uart_num sel, unsigned int baudrate)
 * @brief Function to provide a generic API for putchar functionality.
 * @details This function will be called to write a single character to the stdout by passing 
 * character as an integer, uart number for different offset addresses, and baudrate value for
 * different baudrates.
 * @warning 
 * @param[in] character as int, UART number, and baudarate. 
 * @param[Out] No output parameters.
 */
int write_uart(int ch, uart_num sel, unsigned int baudrate)
{
	if (sel == 0) {
                baud = UART0_START;
                write_reg = (UART0_START + OFFSET_TXREG);
                status_reg = (UART0_START + OFFSET_STATUSREG);
        }
        else if (sel == 1) {
                baud = UART1_START;
                write_reg = (UART1_START + OFFSET_TXREG);
                status_reg = (UART1_START + OFFSET_STATUSREG);
        }
        else {
                baud = UART2_START;
                write_reg = (UART2_START + OFFSET_TXREG);
                status_reg = (UART2_START + OFFSET_STATUSREG);
        }
	/*
		 --------------Baud Calculation------------
		   Baud = Clock_rate/(16 * Baudrate)
	*/
        switch(baudrate)
        {
                case 9600:      *baud = (short int)325;
                                break;
                case 19200:     *baud = (short int)162;
                                break;
                case 38400:     *baud = (short int)81;
                                break;
                case 57600:     *baud = (short int)54;
                                break;
                case 115200:    *baud = (short int)27;
                                break;
		default:        *baud = (short int)325;
                                break;
        }
	unsigned char txt = ch;
        while ((*status_reg & TRANS_NOT_FULL) == 0);
        *write_reg = txt;
	return 0;
}

/**
 * @fn void flush_uart(uart_num sel)
 * @brief Function to flush the uart fifo queue.
 * @details This function will be called to flush the previous values stored in the uart fifo queue by 
 * passing uart number for different offset addresses.
 * @warning 
 * @param[in] UART number. 
 * @param[Out] No output parameters.
 */
void flush_uart(uart_num sel)
{
        char ch;
	if (sel == 0) {
		read_reg = (UART0_START + OFFSET_RXREG);
                status_reg = (UART0_START + OFFSET_STATUSREG);
        }
        else if (sel == 1) {
		read_reg = (UART1_START + OFFSET_RXREG);
                status_reg = (UART1_START + OFFSET_STATUSREG);
        }
        else {
		read_reg = (UART2_START + OFFSET_RXREG);
                status_reg = (UART2_START + OFFSET_STATUSREG);
        }
        while ((*status_reg & RECV_NOT_EMPTY) != 0) {
          ch = *read_reg;
        }
}

/**
 * @fn int getchar()
 * @brief Function to read a single character from the standard input device.
 * @details This function will be called to write a single character from the stdin.
 * @warning 
 * @param[in] No input parameters.
 * @param[Out] Character as int.
 */
#undef getchar
int getchar()
{
        char *ch;
	while((*STATUS_REG & RECV_NOT_EMPTY) == 0); 
        ch = READ_REG;
	return *ch;
}

/**
 * @fn int putchar(int ch)
 * @brief Function to write a single character to the standard output device.
 * @details This function will be called to print a single character to the stdout by passing 
 * character as an integer.
 * @warning 
 * @param[in] character as int.
 * @param[Out] No output parameters.
 */
#undef putchar
int putchar(int ch)
{
	unsigned char txt = ch;
	while((*STATUS_REG & TRANS_NOT_FULL) == 0);
	*WRITE_REG = txt;
	return 0;
}
