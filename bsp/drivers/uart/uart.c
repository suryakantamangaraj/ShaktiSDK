/****************************************************************************
 * Project                               : shakti devt board
 * Name of the file                      : uart.c
 * Brief Description of file             : src  file for uart
 * Name of Author                        : Niketan Shahapur
 * Email ID                              : <niketanshahpur@gmail.com> 
    
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

*****************************************************************************/

#include "uart.h"

#include "gpio.h"

uart_struct *uart_instance[MAX_UART_COUNT];

#if defined(ARTIX7_35T) || defined(AARDONYX)

#define RTS GPIO4
#define USE_INTERRUPT 1
#define UART_DRIVERS 1

unsigned char uart0_complete = 0;
unsigned char uart1_complete = 0;
unsigned char uart2_complete = 0;
unsigned int uart0_tx_isr_count = 0;
unsigned int uart0_rcv_isr_count = 0;
unsigned int uart1_tx_isr_count = 0;
unsigned int uart1_rcv_isr_count = 0;
unsigned int uart2_tx_isr_count = 0;
unsigned int uart2_rcv_isr_count = 0;
unsigned char u0_rcv_char[UARTX_BUFFER_SIZE] = {'\0'};
unsigned char u1_rcv_char[UARTX_BUFFER_SIZE] = {'\0'};
unsigned char u2_rcv_char[UARTX_BUFFER_SIZE] = {'\0'};

uart_struct *uart_instance[MAX_UART_COUNT];

/**
 * @fn init_uart
 * @brief 
 * @details 
 * @warning 
 * @param[in] No input parameters.
 * @param[Out] 
 */
uart_init()
{
	for(int i=0; i< MAX_UART_COUNT; i++)
	{
		uart_instance[i] = (uart_struct*) (UART0_START+i*UART_OFFSET);
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
	while((uart_instance[0]->status & STS_RX_NOT_EMPTY) == 0); 
	return (uart_instance[0]->rcv_reg);
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
//	uart_instance[0] = 0x11300 ;
	while(uart_instance[0]->status & STS_TX_FULL);
	uart_instance[0]->tx_reg = ch;
	return 0;
}

/**
 * @fn void set_baud_rate(uart_struct * UART, unsigned int baudrate)
 * @brief Function to initialize a specific UART with the baudrate.
 * @details This function will be called to initialize a specific UART by passing baudrate value
 * which in turn used to calculate the baud_count to set the baudrate.
 * @warning
 * @param[in] UART instance and baudrate.
 * @param[Out] No output parameters.
*/
void set_baud_rate(uart_struct *uart_instance, unsigned int baudrate)
{
	unsigned int baud_count = 0;
	baud_count = CLOCK_FREQUENCY / (16 * baudrate);
	uart_instance->baud = baud_count;
}

/**
 * @fn void enable_uart_interrupts(uart_struct * uart_instance, unsigned char interrupt) 
 * @brief Function to enable the interrupts of a perticular uart_instance.
 * @details This function will be called to enable the interrupts of a specific uart_instance by passing
 * the interrupt's values.
 * @warning
 * @param[in] uart_instance instance and interrupt value.
 * @param[Out] No output parameters.
*/	
void enable_uart_interrupts(uart_struct * uart_instance, unsigned char interrupt)
{
	uart_instance->ien = interrupt; 
}


#ifdef USE_RX_THRESHOLD
/**
 * @fn void set_uart_rx_threshold(uart_struct * uart_instance, unsigned char rxthreshold)
 * @brief Funtion to set the threshold value of the Rx FIFO.
 * @details This function will be called to set the threshold value of the Rx FIFO of a specific uart_instance
 * by passing the threshold value.
 * @warning
 * @param[in] uart_instance instance and threshold value.
 * @param[Out] No output parameters.
*/
void set_uart_rx_threshold(uart_struct * uart_instance, unsigned char rxthreshold)
{
	uart_instance->rx_threshold = rxthreshold;
}
#endif

/**
 * @fn uint32_t write_uart_character(uart_struct * uart_instance, uint8_t prn_character)
 * @brief Function to write a single character to a specific uart_instance. 
 * @details This function will be called to write a character to a specific uart_instance by passing the
 * character.
 * @warning
 * @param[in] uart_instance instance and character.
 * @param[Out] No output parameters.
*/
uint32_t write_uart_character(uart_struct * uart_instance, uint8_t prn_character)
{
	while(uart_instance->status & STS_TX_FULL);
	uart_instance->tx_reg  = prn_character;
	return;
}

/**
 * @fn uint32_t write_uart_string(uart_struct * uart_instance, uint8_t * ptr_string)
 * @brief Function to write a string to a specific uart_instance.
 * @details This function will be called to write a string to a specific uart_instance by passing the
 * string.
 * @warning
 * @param[in] uart_instance instance and string.
 * @param[Out] No output parameters.
*/
uint32_t write_uart_string(uart_struct * uart_instance, uint8_t * ptr_string)
{
	uint32_t i = 0;
	uint8_t temp;
	do 
	{
		temp = ptr_string[i++];
		write_uart_character(uart_instance, temp);
	} while(temp != 0);
	return 0;
}

/**
 * @fn uint8_t read_uart_character(uart_instance_TypeDef * uart_instance, char * prn_character)
 * @brief Function to read a character from a specific uart_instance.
 * @details This function will be called to read a character from a specific uart_instance by passing the
 * character pointer to store the character.
 * @warning
 * @param[in] uart_instance instance and pointer to a character.
 * @param[Out] No output parameters.
*/
uint8_t read_uart_character(uart_struct * uart_instance, char * prn_character)
{
	uint8_t temp = 0;
	while ((uart_instance->status & STS_RX_NOT_EMPTY) == 0);
	temp = uart_instance->rcv_reg;
	*prn_character = temp;
	return 1;
}

/**
 * @fn uint8_t read_uart_string(uart_struct * uart_instance, char * ptr_string)
 * @brief Function to read a string from a specific uart_instance.
 * @details This function will be called to read a string, one character at a time from a 
 * specific uart_instance by passing the array in which to store the string by reference using pointers.
 * @warning
 * @param[in] UART instance and pointer to an array of character.
 * @param[Out] Length of the sring plus one(null character).
*/
uint8_t read_uart_string(uart_struct * uart_instance, char * ptr_string) 
{
	uint32_t i = 0;
	uint8_t temp = 0;
	while(1) 
	{
		while ((uart_instance->status & STS_RX_NOT_EMPTY) == 0);
		temp = uart_instance->rcv_reg;
		ptr_string[i++] = temp;	
		if (temp == 0x0D) 
		{ 						
			ptr_string[i++] = 0x0A;	
			ptr_string[i++] = 0x00;
			return(i);
		}
	  }
}

/**
 * @fn void flush_uart((uart_struct * uart_instance)
 * @brief Function to flush the UART fifo queue.
 * @details This function will be called to flush the previous values stored in the UART fifo queue by
 * passing UART number for different offset addresses.
 * @warning 
 * @param[in] UART instance. 
 * @param[Out] No output parameters.
 */
void flush_uart(uart_struct * uart_instance)
{
	char temp;
	while ((uart_instance->status & STS_RX_NOT_EMPTY) != 0)
	{
		temp = uart_instance->rcv_reg ;
	} 
}

/**
 * @fn unsigned char uart0_isr()
 * @brief Function to offer interrupt service routine for uart_instance[0].
 * @details This function will be called to offer interrupt service routine for UART0 to read the
 * array of characters by handling interrupts such as RX_threshold, Rx_full, and RX_not_empty
 * based on the Rx fifo status and handles accordingly.
 * @warning
 * @param[in] No input parameters.
 * @param[Out] No output parameters.
*/
#ifdef USE_INTERRUPT
unsigned char uart0_isr()
{
	int i;
	uint32_t read_value = '\0';
	if(uart_instance[0]->status & STS_RX_THRESHOLD)
	{
		while(uart_instance[0]->status & STS_RX_NOT_EMPTY)
                {
                        read_value = uart_instance[0]->rcv_reg;
                        u0_rcv_char[uart0_rcv_isr_count++] = read_value;
                        write_uart_character(uart_instance[0], read_value);
                }
	}
	else if(uart_instance[0]->status & STS_RX_FULL)
	{
		write_word(GPIO_DIRECTION_CNTRL_REG, RTS);
		write_word(GPIO_DATA_REG, read_word(GPIO_DATA_REG) | RTS);
		while(uart_instance[0]->status & STS_RX_NOT_EMPTY)
		{
			read_value = uart_instance[0]->rcv_reg;
			u0_rcv_char[uart0_rcv_isr_count++] = read_value;
			write_uart_character(uart_instance[0], read_value);
		}
		write_word(GPIO_DATA_REG, read_word(GPIO_DATA_REG) & ~(RTS));
	}
	else if(uart_instance[0]->status & STS_RX_NOT_EMPTY)
	{
		read_value = uart_instance[0]->rcv_reg;
		u0_rcv_char[uart0_rcv_isr_count++] = read_value;
		write_uart_character(uart_instance[0], read_value);
	}
}

/**
 * @fn unsigned char uart1_isr()
 * @brief Function to offer interrupt service routine for uart_instance[1].
 * @details This function will be called to offer interrupt service routine for uart_instance[1] to read the
 * array of characters by handling interrupts such as RX_threshold, Rx_full, and RX_not_empty
 * based on the Rx fifo status and handles accordingly.
 * @warning
 * @param[in] No input parameters.
 * @param[Out] No output parameters.
*/
unsigned char uart1_isr()
{
	uint32_t status = 0;
	uint32_t read_value = '\0';
	int i = 0;
	if(uart_instance[1]->status & STS_RX_THRESHOLD)
        {
                while(uart_instance[1]->status & STS_RX_NOT_EMPTY)
                {
                        read_value = uart_instance[1]->rcv_reg;
                        u1_rcv_char[uart1_rcv_isr_count++] = read_value;
                        write_uart_character(uart_instance[1], read_value);
                }
        }
        else if(uart_instance[1]->status & STS_RX_FULL)
	{
		write_word(GPIO_DIRECTION_CNTRL_REG, RTS);
		write_word(GPIO_DATA_REG, read_word(GPIO_DATA_REG) | RTS);
		while(uart_instance[1]->status & STS_RX_NOT_EMPTY)
		{	
			read_value = uart_instance[1]->rcv_reg;
			u1_rcv_char[uart1_rcv_isr_count++] = read_value;
			write_uart_character(uart_instance[1], read_value);
		}
		write_word(GPIO_DATA_REG, read_word(GPIO_DATA_REG) & ~(RTS));
	}
	else if(uart_instance[1]->status & STS_RX_NOT_EMPTY)
	{
		read_value = uart_instance[1]->rcv_reg;
		u1_rcv_char[uart1_rcv_isr_count++] = read_value;
		write_uart_character(uart_instance[1], read_value);
	}
}

/**
 * @fn unsigned char uart2_isr()
 * @brief Function to offer interrupt service routine for UART2.
 * @details This function will be called to offer interrupt service routine for UART2 to read the
 * array of characters by handling interrupts such as RX_threshold, Rx_full, and RX_not_empty
 * based on the Rx fifo status and handles accordingly.
 * @warning
 * @param[in] No input parameters.
 * @param[Out] No output parameters.
*/
unsigned char uart2_isr()
{
	uint32_t status = 0;
	int i = 0;
	uint32_t read_value = '\0';
	if(uart_instance[2]->status & STS_RX_THRESHOLD)
        {
                while(uart_instance[2]->status & STS_RX_NOT_EMPTY)
                {
                        read_value = uart_instance[2]->rcv_reg;
                        u2_rcv_char[uart2_rcv_isr_count++] = read_value;
                        write_uart_character(uart_instance[2], read_value);
                }
        }
        else if(uart_instance[2]->status & STS_RX_FULL)
	{
		write_word(GPIO_DIRECTION_CNTRL_REG, RTS);
		write_word(GPIO_DATA_REG, read_word(GPIO_DATA_REG) | RTS);
		while(uart_instance[2]->status & STS_RX_NOT_EMPTY)
		{	
			read_value = uart_instance[2]->rcv_reg;
			u2_rcv_char[uart2_rcv_isr_count++] = read_value;
			write_uart_character(uart_instance[2], read_value);
		}
		write_word(GPIO_DATA_REG, read_word(GPIO_DATA_REG) & ~(RTS));
	}
	else if(uart_instance[2]->status & STS_RX_NOT_EMPTY)
	{
		read_value = uart_instance[2]->rcv_reg;
		u2_rcv_char[uart2_rcv_isr_count++] = read_value;
		write_uart_character(uart_instance[2], read_value);
	}
}


#endif

#else

#define UART1_BASE_ADDRESS 0x11300
#define BASE_ADDR ((volatile unsigned int *) UART1_BASE_ADDRESS) /* 32 bits */
#define STATUS_REG ((volatile unsigned char *)(UART1_BASE_ADDRESS + 0xc)) /* 8 bits */
#define WRITE_REG ((volatile unsigned char *)(UART1_BASE_ADDRESS + 0x4)) /* 8 bits */
#define READ_REG ((volatile unsigned char *)(UART1_BASE_ADDRESS + 0x8)) /* 8 bits */
#define RECV_NOT_EMPTY 0x8
#define TRANS_NOT_FULL 0x2

/** @fn int getchar( )
 * @brief 
 * @details 
 * @warning 
 * @param[in] no input parameter
 * @param[Out] char
 */
 
#undef getchar
int getchar()
{
  char *ch;
	while((*STATUS_REG & RECV_NOT_EMPTY) == 0);
  ch = READ_REG;
  return *ch;
}


/** @fn int putchar(int ch)
 * @brief 
 * @details 
 * @warning 
 * @param[in] char
 * @param[Out] int
 */

#undef putchar
int putchar(int ch)
{
  unsigned char c = ch;
	while((*STATUS_REG & TRANS_NOT_FULL) == 0);
	*WRITE_REG = c;
	return 0;
}

#endif
