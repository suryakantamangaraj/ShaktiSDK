/**********************************************************************
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors\ufffd
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

#ifndef __SHAKTI_UART_H
#define __SHAKTI_UART_H
#include <stdint.h>


// UART Control register
#define NO_OF_BITS    (0x3F << 5)
#define PARITY        (0x03 << 3)
#define STOP_BITS     (0x03 << 1)

// UART status register
#define STS_BREAK_ERROR		 1 << 7
#define STS_FRAME_ERROR		 1 << 6
#define STS_OVERRUN			 1 << 5
#define STS_PARITY_ERROR	 1 << 4

#if 0
#define STS_RECV_NOT_EMPTY	 1 << 3
#define STS_RECV_NOT_FULL	 1 << 2
#define STS_TX_NOT_FULL		 1 << 1
#define STS_TX_DONE			 1 << 0
#else
#define STS_RX_FULL 1 << 3
#define STS_RX_NOT_EMPTY 1 << 2
#define STS_TX_FULL 1 << 1
#define STS_TX_EMPTY 1 << 0
#endif

#if 0
// 8-bit Interrupt Enable register
#define ENABLE_BREAK_ERROR		 1 << 7
#define ENABLE_FRAME_ERROR		 1 << 6
#define ENABLE_OVERRUN			 1 << 5
#define ENABLE_PARITY_ERROR		 1 << 4
#define ENABLE_RECV_NOT_EMPTY	 1 << 3
#define ENABLE_RECV_NOT_FULL	 1 << 2
#define ENABLE_TX_NOT_FULL		 1 << 1
#define ENABLE_TX_DONE			 1 << 0
#else
#define ENABLE_BREAK_ERROR		 1 << 7
#define ENABLE_FRAME_ERROR		 1 << 6
#define ENABLE_OVERRUN			 1 << 5
#define ENABLE_PARITY_ERROR		 1 << 4
#define ENABLE_RX_FULL 1 << 3
#define ENABLE_RX_NOT_EMPTY 1 << 2
#define ENABLE_TX_FULL 1 << 1
#define ENABLE_TX_EMPTY 1 << 0
#endif

#define SHAKTI_UART0_BASE       (SHAKTI_UART_BASE + (0 * SHAKTI_UART_OFFSET ))
#define SHAKTI_UART1_BASE       (SHAKTI_UART_BASE + (1 * SHAKTI_UART_OFFSET ))
#define SHAKTI_UART2_BASE       (SHAKTI_UART_BASE + (2 * SHAKTI_UART_OFFSET ))

typedef struct
{
  unsigned short BAUD;								
  unsigned short DUMMY0;								
  unsigned int TX_REG;
  unsigned int RCV_REG;
  unsigned char STATUS;
  unsigned char DUMMY1;
  unsigned char DUMMY2;
  unsigned char DUMMY3;
  unsigned short DELAY;					
  unsigned short DUMMY4;					
  unsigned short CONTROL;
  unsigned short DUMMY5;					
  unsigned char IEN;
  unsigned char DUMMY6;
  unsigned char DUMMY7;
  unsigned char DUMMY8;
  unsigned int IQCYCLES;
} SHAKTI_UART_TypeDef;

#define SHAKTI_UART0            ((SHAKTI_UART_TypeDef   *) SHAKTI_UART0_BASE )
#define SHAKTI_UART1            ((SHAKTI_UART_TypeDef   *) SHAKTI_UART1_BASE )
#define SHAKTI_UART2            ((SHAKTI_UART_TypeDef   *) SHAKTI_UART2_BASE )




void shakti_print_uart_register_address(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART);
void shakti_print_uart_register_address(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART);
void shakti_read_uart_status_register(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART);
void shakti_read_uart_registers(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART);
void shakti_init_uart(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART, unsigned int baudrate);
void shakti_enable_uart_interrupt(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART, unsigned char interrupt);
uint32_t shakti_put_terminal_character(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART, uint8_t prn_character);
uint32_t shakti_put_terminal_string(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART, uint8_t * ptr_string);
uint32_t shakti_get_terminal_character(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART, char * prn_character);
uint32_t shakti_get_terminal_string(SHAKTI_UART_TypeDef * ptr_SHAKTI_UART, char * ptr_string) ;







#endif /* __SHAKTI_UART_H */

