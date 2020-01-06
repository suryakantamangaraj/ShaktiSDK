/************************************************************************
* Project           			:  shakti devt board
* Name of the file	     		:  uart.h
* Brief Description of file     :  Header file for uart.
* Name of Author    	        :  Niketan Shahapur & Sathya Narayanan N
* Email ID                      :  niketanshahpur@gmail.com, sathya281@gmail.com

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

/**
 * @file uart.h
 * @project shakti devt board
 * @brief Header file for uart  
 */
#ifndef UART_H
#define UART_H

#define UART_START 0x11300

#define TX_REG_OFFSET     0x4
#define RX_REG_OFFSET     0x8
#define STATUS_REG_OFFSET 0xC


#define WRITE_REG  ((volatile unsigned char *)(UART0_START + 0x4)) /* 8 bits */
#define READ_REG   ((volatile unsigned char *)(UART0_START + 0x8)) /* 8 bits */
#define STATUS_REG ((volatile unsigned char *)(UART0_START + 0xC)) /* 8 bits */



#if 0
#define U0_BAUD_REG  ((volatile unsigned char *) (UART0_BASE_ADDRESS + 0x0)) /* 8 bits */
#define U0_WRITE_REG  ((volatile unsigned char *)(UART0_BASE_ADDRESS + 0x4)) /* 8 bits */
#define U0_READ_REG   ((volatile unsigned char *)(UART0_BASE_ADDRESS + 0x8)) /* 8 bits */
#define U0_STATUS_REG ((volatile unsigned char *)(UART0_BASE_ADDRESS + 0xC)) /* 8 bits */
#define U0_DELAY_REG   ((volatile unsigned char *)(UART0_BASE_ADDRESS + 0x10)) /* 8 bits */
#define U0_CONTROL_REG   ((volatile unsigned char *)(UART0_BASE_ADDRESS + 0x14)) /* 8 bits */
#define U0_INTERRUPT_ENABLE_REG   ((volatile unsigned char *)(UART0_BASE_ADDRESS + 0x18)) /* 8 bits */
#define U0_IO_CYCLES_REG   ((volatile unsigned char *)(UART0_BASE_ADDRESS + 0x1C)) /* 8 bits */

#define U1_BAUD_REG  ((volatile unsigned char *) (UART1_BASE_ADDRESS + 0x0)) /* 8 bits */
#define U1_WRITE_REG  ((volatile unsigned char *)(UART1_BASE_ADDRESS + 0x4)) /* 8 bits */
#define U1_READ_REG   ((volatile unsigned char *)(UART1_BASE_ADDRESS + 0x8)) /* 8 bits */
#define U1_STATUS_REG ((volatile unsigned char *)(UART1_BASE_ADDRESS + 0xC)) /* 8 bits */
#define U1_DELAY_REG   ((volatile unsigned char *)(UART1_BASE_ADDRESS + 0x10)) /* 8 bits */
#define U1_CONTROL_REG   ((volatile unsigned char *)(UART1_BASE_ADDRESS + 0x14)) /* 8 bits */
#define U1_INTERRUPT_ENABLE_REG   ((volatile unsigned char *)(UART1_BASE_ADDRESS + 0x18)) /* 8 bits */
#define U1_IO_CYCLES_REG   ((volatile unsigned char *)(UART1_BASE_ADDRESS + 0x1C)) /* 8 bits */

#define U2_BAUD_REG  ((volatile unsigned char *) (UART2_BASE_ADDRESS + 0x0)) /* 8 bits */
#define U2_WRITE_REG  ((volatile unsigned char *)(UART2_BASE_ADDRESS + 0x4)) /* 8 bits */
#define U2_READ_REG   ((volatile unsigned char *)(UART2_BASE_ADDRESS + 0x8)) /* 8 bits */
#define U2_STATUS_REG ((volatile unsigned char *)(UART2_BASE_ADDRESS + 0xC)) /* 8 bits */
#define U2_DELAY_REG   ((volatile unsigned char *)(UART2_BASE_ADDRESS + 0x10)) /* 8 bits */
#define U2_CONTROL_REG   ((volatile unsigned char *)(UART2_BASE_ADDRESS + 0x14)) /* 8 bits */
#define U2_INTERRUPT_ENABLE_REG   ((volatile unsigned char *)(UART2_BASE_ADDRESS + 0x18)) /* 8 bits */
#define U2_IO_CYCLES_REG   ((volatile unsigned char *)(UART2_BASE_ADDRESS + 0x1C)) /* 8 bits */
#else
#define UART_BAUD_REG    0x00 /* 8 bits */
#define UART_WRITE_REG   0x04 /* 8 bits */
#define UART_READ_REG    0x08 /* 8 bits */
#define UART_STATUS_REG  0x0C /* 8 bits */
#define UART_DELAY_REG   0x10 /* 8 bits */
#define UART_CONTROL_REG 0x14 /* 8 bits */
#define UART_INTERRUPT_ENABLE_REG   0x18 /* 8 bits */
#define UART_IO_CYCLES_REG   0x1C /* 8 bits */
#endif

#define RECV_NOT_EMPTY   0x8
#define TRANS_FULL   0x2


#define CLOCK_FREQUENCY 40000000

// 8-bit Interrupt Enable register
#define ENABLE_BREAK_ERROR		 1 << 7
#define ENABLE_FRAME_ERROR		 1 << 6
#define ENABLE_OVERRUN			 1 << 5
#define ENABLE_PARITY_ERROR		 1 << 4
/*
#define ENABLE_RECV_NOT_EMPTY	 1 << 3
#define ENABLE_RECV_NOT_FULL	 1 << 2
#define ENABLE_TX_NOT_FULL		 1 << 1
#define ENABLE_TX_DONE			 1 << 0


#define STS_TX_EMPTY 1 << 0
#define STS_TX_FULL 1 << 1
#define STS_RX_NOT_EMPTY 1 << 2
#define STS_RX_FULL 1 << 3


#define ENABLE_TX_EMPTY 1 << 0
#define ENABLE_TX_FULL 1 << 1
#define ENABLE_RX_NOT_EMPTY 1 << 2
#define ENABLE_RX_FULL 1 << 3


*/

/**
 * @brief Enumeration to select one of the UART base address. 
 */
typedef enum uart_num {
    UART0,
    UART1, 
    UART2
} uart_num;

//function prototype
int read_uart(uart_num sel, unsigned int baudrate);
int write_uart(int ch, uart_num sel, unsigned int baudrate);
void flush_uart(uart_num sel);
#undef putchar
int putchar(int ch);
#undef getchar
int getchar();
#ifdef SHAKTI_UART
void enable_uart_interrupt(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART, unsigned char interrupt);
void init_uart(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART, unsigned int baudrate);
#endif


#ifdef UART_NUM
void enable_uart_interrupt(uart_num sel , unsigned int interrupt);
void init_uart(uart_num sel , unsigned short baudrate);
#endif



#endif
