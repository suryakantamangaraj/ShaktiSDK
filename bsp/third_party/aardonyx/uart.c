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
#include <stdint.h>
#include "uart.h"
#include "shakti_uart.h"
#include "platform.h"

short int* baud;
volatile unsigned char* write_reg;
volatile unsigned char* read_reg;
volatile unsigned char* status_reg;
volatile unsigned char* delay_reg;
volatile unsigned char* control_reg;
volatile unsigned char* interrupt_ena_reg;
volatile unsigned char* io_cycles_reg;


void print_uart_register_address(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART)
{
#if 1
	printf("\n baud Register:%x", &ptr_SHAKTI_UART->BAUD);
	printf("\n write Register:%x", &ptr_SHAKTI_UART->TX_REG);
	printf("\n read Register:%x", &ptr_SHAKTI_UART->RCV_REG);
	printf("\n status Register:%x", &ptr_SHAKTI_UART->STATUS);
	printf("\n delay Register:%x", &ptr_SHAKTI_UART->DELAY);
	printf("\n control Register:%x", &ptr_SHAKTI_UART->CONTROL);
	printf("\n interrupt Register:%x", &ptr_SHAKTI_UART->IEN);
	printf("\n io cycles Register:%x\n", &ptr_SHAKTI_UART->IQCYCLES);

#else
	printf("\n baud Register:%x", ptr_SHAKTI_UART->BAUD);
	printf("\n control Register:%x", ptr_SHAKTI_UART->CONTROL);
	printf("\n interrupt Register:%x", ptr_SHAKTI_UART->IEN);
	printf("\n baud Register:%x", ptr_SHAKTI_UART->BAUD);
	printf("\n write Register:%x", ptr_SHAKTI_UART->TX_REG);
	printf("\n read Register:%x", ptr_SHAKTI_UART->RCV_REG);
	printf("\n status Register:%x", ptr_SHAKTI_UART->STATUS);
	printf("\n delay Register:%x", ptr_SHAKTI_UART->DELAY);
	printf("\n control Register:%x", ptr_SHAKTI_UART->CONTROL);
	printf("\n interrupt Register:%x", ptr_SHAKTI_UART->IEN);
	printf("\n io cycles Register:%x\n", ptr_SHAKTI_UART->IQCYCLES);
#endif
}

unsigned char read_uart_status_register(uart_num sel)
{
	status_reg = (UART_START + (sel * 0x100) + UART_STATUS_REG);
//	printf(" status Register:%x\n", *status_reg);
	return *status_reg;
}



void read_uart_registers(uart_num sel)
{
	baud = (UART_START + (sel * 0x100) + UART_BAUD_REG);
	write_reg = (UART_START + (sel * 0x100) + UART_WRITE_REG);
	read_reg = (UART_START + (sel * 0x100) + UART_READ_REG);
	status_reg = (UART_START + (sel * 0x100) + UART_STATUS_REG);
	delay_reg = (UART_START + (sel * 0x100) + UART_DELAY_REG);
	control_reg = (UART_START + (sel * 0x100) + UART_CONTROL_REG);
	interrupt_ena_reg = (UART_START + (sel * 0x100) + UART_INTERRUPT_ENABLE_REG);
	io_cycles_reg = (UART_START + (sel * 0x100) + UART_IO_CYCLES_REG);
	printf("\n baud Register:%x", *baud);
	printf("\n write Register:%x", *write_reg);
	printf("\n read Register:%x", *read_reg);
	printf("\n status Register:%x", *status_reg);
	printf("\n delay Register:%x", *delay_reg);
	printf("\n control Register:%x", *control_reg);
	printf("\n interrupt Register:%x", *interrupt_ena_reg);
	printf("\n io cycles Register:%x", *io_cycles_reg);
}

/*
			 --------------Baud Calculation------------
			   Baud = Clock_rate/(16 * Baudrate)
	*/
void init_uart(uart_num sel , unsigned short baudrate)
{
	unsigned int baud_count = 0;
	baud = (UART_START + (sel * 0x100) + UART_BAUD_REG);
	baud_count = CLOCK_FREQUENCY / (16 * baudrate);
	printf("\n baud rate: %d; baud_count = %d", baudrate, baud_count);
	*baud = baud_count;
}
void enable_uart_interrupt(uart_num sel , unsigned int interrupt)
{
	unsigned int baud_count = 0;
	interrupt_ena_reg = UART_START + ( sel * 0x100) + UART_INTERRUPT_ENABLE_REG;
	*interrupt_ena_reg = interrupt;
}

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
	baud = (UART_START + (sel * 0x100) + UART_BAUD_REG);
	write_reg = (UART_START + (sel * 0x100) + UART_WRITE_REG);
	read_reg = (UART_START + (sel * 0x100) + UART_READ_REG);
	status_reg = (UART_START + (sel * 0x100) + UART_STATUS_REG);
	delay_reg = (UART_START + (sel * 0x100) + UART_DELAY_REG);
	control_reg = (UART_START + (sel * 0x100) + UART_CONTROL_REG);
	interrupt_ena_reg = (UART_START + (sel * 0x100) + UART_INTERRUPT_ENABLE_REG);
	io_cycles_reg = (UART_START + (sel * 0x100) + UART_IO_CYCLES_REG);
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
	unsigned char txt = ch;
	baud = (UART_START + (sel * 0x100) + UART_BAUD_REG);
	write_reg = (UART_START + (sel * 0x100) + UART_WRITE_REG);
	read_reg = (UART_START + (sel * 0x100) + UART_READ_REG);
	status_reg = (UART_START + (sel * 0x100) + UART_STATUS_REG);
	delay_reg = (UART_START + (sel * 0x100) + UART_DELAY_REG);
	control_reg = (UART_START + (sel * 0x100) + UART_CONTROL_REG);
	interrupt_ena_reg = (UART_START + (sel * 0x100) + UART_INTERRUPT_ENABLE_REG);
	io_cycles_reg = (UART_START + (sel * 0x100) + UART_IO_CYCLES_REG);
    while ((*status_reg & TRANS_FULL) == 1);
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
		read_reg = (UART_START + (sel * 0x100) + UART_READ_REG);
		status_reg = (UART_START + (sel * 0x100) + UART_STATUS_REG);
        while ((*status_reg & RECV_NOT_EMPTY) != 0) {
          ch = *read_reg;
        }
}

#if 0
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
	while((*STATUS_REG & TRANS_FULL) == 1);
	*WRITE_REG = txt;
	return 0;
#if 0
register char a0 asm("a0") = ch;                                                                  
 asm volatile ("li t1, 0x11300" "\n\t" //The base address of UART config registers                
       "uart_status_simple: lb a1, 12(t1)" "\n\t"                                                  
       "andi a1,a1,0x2" "\n\t"                                                                    
       "bnez a1, uart_status_simple" "\n\t"                                                        
       "sb a0, 4(t1)"  "\n\t"                                                                      
       :                                                                                          
       :                                                                                          
       :"a0","t1","cc","memory");                                                                  
#endif	   
 return 0;                              
}
#else
int getchar()
{
        char *ch;
	while((SHAKTI_UART0->STATUS & RECV_NOT_EMPTY) == 0); 
        ch = SHAKTI_UART0->RCV_REG;
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
#if 1
//	unsigned char txt = ch;
	while((SHAKTI_UART0->STATUS & STS_TX_FULL) );
	SHAKTI_UART0->TX_REG = ch;
	return 0;
#else
register char a0 asm("a0") = ch;                                                                  
 asm volatile ("li t1, 0x11300" "\n\t" //The base address of UART config registers                
       "uart_status_simple: lb a1, 12(t1)" "\n\t"                                                  
       "andi a1,a1,0x2" "\n\t"                                                                    
       "bnez a1, uart_status_simple" "\n\t"                                                        
       "sb a0, 4(t1)"  "\n\t"                                                                      
       :                                                                                          
       :                                                                                          
       :"a0","t1","cc","memory");                                                                  
#endif	   
 return 0;                              
}

#endif


