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

/**
 * @fn int getchar()
 * @brief Function to read a single character from the standard input device.
 * @details This function will be called to write a single character from the stdin.
 * @warning 
 * @param[in] No input parameters.
 * @param[Out] Character as int.
 */
#undef shakti_getchar
int shakti_getchar()
{
        char *ch;
//	while((SHAKTI_UART0->STATUS & STS_RECV_NOT_EMPTY) == 0); 
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
#undef shakti_putchar
int shakti_putchar(int ch)
{
	unsigned char txt = ch;
//	while((SHAKTI_UART0->STATUS & STS_TX_NOT_FULL) == 0); // commenting out to check for interupts
	SHAKTI_UART0->TX_REG = txt;
	return 0;
}


void shakti_print_uart_register_address(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART)
{
	printf("\n baud Register:%x", &ptr_SHAKTI_UART->BAUD);
	printf("\n write Register:%x", &ptr_SHAKTI_UART->TX_REG);
	printf("\n read Register:%x", &ptr_SHAKTI_UART->RCV_REG);
	printf("\n status Register:%x", &ptr_SHAKTI_UART->STATUS);
	printf("\n delay Register:%x", &ptr_SHAKTI_UART->DELAY);
	printf("\n control Register:%x", &ptr_SHAKTI_UART->CONTROL);
	printf("\n interrupt Register:%x", &ptr_SHAKTI_UART->IEN);
	printf("\n io cycles Register:%x", &ptr_SHAKTI_UART->IQCYCLES);

	printf("\n baud Register:%x", ptr_SHAKTI_UART->BAUD);
	printf("\n control Register:%x", ptr_SHAKTI_UART->CONTROL);
	printf("\n interrupt Register:%x", ptr_SHAKTI_UART->IEN);
}

void shakti_read_uart_status_register(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART)
{
	printf(" status Register:%x\n", ptr_SHAKTI_UART->STATUS);
}



void shakti_read_uart_registers(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART)
{
	printf("\n baud Register:%x", ptr_SHAKTI_UART->BAUD);
	printf("\n write Register:%x", ptr_SHAKTI_UART->TX_REG);
	printf("\n read Register:%x", ptr_SHAKTI_UART->RCV_REG);
	printf("\n status Register:%x", ptr_SHAKTI_UART->STATUS);
	printf("\n delay Register:%x", ptr_SHAKTI_UART->DELAY);
	printf("\n control Register:%x", ptr_SHAKTI_UART->CONTROL);
	printf("\n interrupt Register:%x", ptr_SHAKTI_UART->IEN);
	printf("\n io cycles Register:%x", ptr_SHAKTI_UART->IQCYCLES);
}
/*
			 --------------Baud Calculation------------
			   Baud = Clock_rate/(16 * Baudrate)
	*/
void shakti_init_uart(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART, unsigned int baudrate)
{
	unsigned int baud_count = 0;
	baud_count = CLOCK_FREQUENCY / (16 * baudrate);
	printf("Baud rate: %d; Baud_count = %d\n", baudrate, baud_count);
		ptr_SHAKTI_UART->BAUD = baud_count;
	printf("\n Baud value read: %x\n", ptr_SHAKTI_UART->BAUD);
}
	

void shakti_enable_uart_interrupt(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART, unsigned char interrupt)
{
	ptr_SHAKTI_UART->IEN = interrupt;             // Write the character to the TX buffer
	printf("\n IEN value read: %x\n", ptr_SHAKTI_UART->IEN);
}

/*****************************************************************************
** Function name:		PutTerminalCharacter
**
** Description:			This function writes a character, to
**                  a UART. Both the USART instance and the 
** 						character are passed .
**
** parameters:			ptr_SHAKTI_UART: A pointer to any UART on the target.
**                  character tp be printed: 
**
** Returned value:	void
**
*****************************************************************************/
uint32_t shakti_put_terminal_character(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART, uint8_t prn_character)
{
	//while (!((ptr_SHAKTI_UART->STATUS) & STS_TX_NOT_FULL)); // Wait for TX Ready
//S	while( ( (ptr_SHAKTI_UART->STATUS) & STS_TX_FULL) );
	while( ( (ptr_SHAKTI_UART->STATUS) & STS_TX_FULL) )
	{
		log_error("\n TX Fifo Full; Wait for Tx to complete");
		return -1;
	}
	ptr_SHAKTI_UART->TX_REG  = prn_character;             // Write the character to the TX buffer
	return;
}



/*****************************************************************************
** Function name:		PutTerminalString
**
** Description:			This function writes a string, one character at a time, to
**                  a UART. The string MUST be terminated by a terminating
**                  NUL ("\0") character. Both the UART instance and the 
string
**                  are passed into the function by reference using pointers.
**
** parameters:			ptr_SHAKTI_UART: A pointer to any USART on the target.
**                  ptr_string: A pointer to an array of char terminated by 
NUL.
**
** Returned value:	void
**
*****************************************************************************/
uint32_t shakti_put_terminal_string(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART, uint8_t * ptr_string)
{
  uint32_t i = 0;
  uint8_t temp;

  do {
    temp = ptr_string[i++];                   // Get the current character
	  //while (!((ptr_SHAKTI_UART->STATUS) & STS_TX_NOT_FULL)); // Wait for TX Ready
	while( ( (ptr_SHAKTI_UART->STATUS) & STS_TX_FULL) )
	{
		log_error("\n TX Fifo Full; Wait for Tx to complete");
		return -1;
	}
	  ptr_SHAKTI_UART->TX_REG  = temp;             // Write the character to the TX buffer
  } while (temp != 0);                        // NUL character terminates

  return 0;
}

/*****************************************************************************
** Function name:		GetTerminalCharacter
**
** Description:			This function accepts a string, one character at a time,
**                  from a UART. Both the USART instance and the array in
**                  which to store the string are passed into the function
**                  by reference using pointers.
**
** parameters:			ptr_SHAKTI_UART: A pointer to any USART on the target.
**                  ptr_string: A pointer to an array of char.
**
** Returned value:	length of the string not including the NUL terminator
**
*****************************************************************************/
uint32_t shakti_get_terminal_character(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART, char * prn_character)
{
	uint8_t temp = 0;
	//while (!((ptr_SHAKTI_UART->STATUS) & STS_RX_NOT_EMPTY));   // Wait for RX Ready
	while (!( (ptr_SHAKTI_UART->STATUS) & STS_RX_NOT_EMPTY) );   // Wait for RX Ready
	temp = ptr_SHAKTI_UART->RCV_REG ;			   // Read the current character from RXDAT 
	prn_character = temp;					 // Append the current	  character to the rx buffer
	printf("\n Rcv Data: %c", temp);
	//while (!((ptr_SHAKTI_UART->STATUS) & STS_TX_NOT_FULL));	// Wait for TXREADY
//	ptr_SHAKTI_UART->TX_REG  = temp;			   // Echo it back to the terminal
	return 1;
}




/*****************************************************************************
** Function name:		GetTerminalString
**
** Description:			This function accepts a string, one character at a time,
**                  from a UART. Both the UART instance and the array in
**                  which to store the string are passed into the function
**                  by reference using pointers.
**
** parameters:			ptr_SHAKTI_UART: A pointer to any UART on the target.
**                  ptr_string: A pointer to an array of char.
**
** Returned value:	length of the string not including the NUL terminator
**
*****************************************************************************/
uint32_t shakti_get_terminal_string(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART, char * ptr_string) 
{
	  uint32_t i = 0;
	  uint8_t temp = 0;
	
	  while (1) {
		while (!((ptr_SHAKTI_UART->STATUS) & STS_RX_NOT_EMPTY));	 // Wait for RX Ready
		temp = ptr_SHAKTI_UART->RCV_REG ;				 // Read the current character from RXDAT 
		ptr_string[i++] = temp; 					// Append the current character to the rx buffer
		//while (!((ptr_SHAKTI_UART->STATUS) & STS_TX_NOT_FULL));   // Wait for TXREADY
		//ptr_SHAKTI_UART->TX_REG  = temp;				 // Echo it back to the terminal
	
		if (temp == 0x0D) { 						
		// CR (carriage return) is current character or buffer full. End of string.
		  ptr_string[i++] = 0x0A;	
		// Append a new line Character to rx_buffer.
		  ptr_string[i++] = 0x00;
		// Append a NUL terminator character to rx_buffer to complete the string.
		  while (!( (ptr_SHAKTI_UART->STATUS) & STS_TX_FULL)); // Wait for TXREADY
		  ptr_SHAKTI_UART->TX_REG  = 0x0A;
		  // Echo a NL (new line) character to the terminal.
		  return(i);
		}
	  }
}



