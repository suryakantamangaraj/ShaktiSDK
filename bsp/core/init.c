/***************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: init.c
 * Brief Description of file    : source file for system initialization.
 * Name of Author    	        : Sathya Narayanan N & Abhinav Ramnath
 * Email ID                     : sathya281@gmail.com

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

 ****************************************************************************/
/**
@file init.c
@brief source file for system initialization
@detail 
*/ 

#include "traps.h"
#include "plic_driver.h"
#include "clint_driver.h"
#include "log.h"
#include "utils.h"
#include "qspi.h"
#include "platform.h"
#include "defines.h"
#include "uart.h"

extern void trap_entry();
extern uart_struct *uart_instance[MAX_UART_COUNT];

extern char _stack_end[];
extern char _stack[];
extern char _heap[];
extern char _heap_end[];
extern char __bss_end[];
extern char __bss_start[];
extern char __sbss_end[];
extern char __sbss_start[];

char *stack_end=(char *)&_stack_end;
char *stack_start=(char *)&_stack;
char *heap_start=(char *)&_heap;
char *heap_end=(char *)&_heap_end;
char *bss_end=(char *)&__bss_end;
char *bss_start=(char *)&__bss_start;
char *sbss_end=(char *)&__sbss_end;
char *sbss_start=(char *)&__sbss_start;

mtrap_fptr_t mcause_trap_table[MAX_TRAP_VALUE];
mtrap_fptr_t mcause_interrupt_table[MAX_INTERRUPT_VALUE];
plic_fptr_t isr_table[PLIC_MAX_INTERRUPT_SRC];


/** @fn section_init
 * @brief resets the different sections
 * @details Explicitly 0x0 or 0xffffffff is written all the addresses in different "write" sections of memory
 * @warning takes long time. so the caller is diabled as of now
 */
void section_init()
{
	while(bss_start<=bss_end)
	{
		*bss_start=0x0;
		bss_start++;
	}

	while(sbss_start<=sbss_end)
	{
		*sbss_start=0x0;
		sbss_start++;
	}

	while(heap_start<=heap_end)
	{
		*heap_start=0xffffffff;
		heap_start++;
	}

	while(stack_end>=stack_start)
	{
		*stack_end=0x0;
		stack_end--;
	}
}

/** @fn trap_init
 * @brief Initialize the trap/interrupt callback routines with user defined handler.
 * @details Assign default handler for trap / interrupt that does not have user defined
 *          callback routines"
 */
void trap_init()
{
	log_info("trap_init entered \n ");



	mcause_interrupt_table[USER_SW_INTERRUPT]        = default_handler;
	mcause_interrupt_table[SUPER_SW_INTERRUPT]       = default_handler;
	mcause_interrupt_table[RESERVED_INTERRUPT0]      = default_handler;
	mcause_interrupt_table[MACH_SW_INTERRUPT]        = default_handler;
	mcause_interrupt_table[USER_TIMER_INTERRUPT]     = default_handler;
	mcause_interrupt_table[SUPER_TIMER_INTERRUPT]    = default_handler;
	mcause_interrupt_table[RESERVED_INTERRUPT1]      = default_handler;
	mcause_interrupt_table[MACH_TIMER_INTERRUPT]     = mach_clint_handler;
	mcause_interrupt_table[USER_EXT_INTERRUPT]       = default_handler;
	mcause_interrupt_table[SUPERVISOR_EXT_INTERRUPT] = default_handler;
	mcause_interrupt_table[RESERVED_INTERRUPT2]      = default_handler;
	mcause_interrupt_table[MACH_EXTERNAL_INTERRUPT]  = mach_plic_handler;
	mcause_interrupt_table[RESERVED_INTERRUPT3]      = default_handler;
	mcause_interrupt_table[RESERVED_INTERRUPT4]      = default_handler;
	mcause_interrupt_table[RESERVED_INTERRUPT5]      = default_handler;
	mcause_interrupt_table[RESERVED_INTERRUPT6]      = default_handler;


	mcause_trap_table[INSTRUCTION_ADDRESS_MISALIGNED] =
		default_handler;
	mcause_trap_table[INSTRUCTION_ACCESS_FAULT] =
		default_handler;
	mcause_trap_table[ILLEGAL_INSTRUCTION] =
		default_handler;
	mcause_trap_table[BREAKPOINT] =
		default_handler;
	mcause_trap_table[LOAD_ADDRESS_MISALIGNED] =
		default_handler;
	mcause_trap_table[LOAD_ACCESS_FAULT] =
		default_handler;
	mcause_trap_table[STORE_AMO_ADDRESS_MISALIGNED] =
		default_handler;
	mcause_trap_table[STORE_AMO_ACCESS_FAULT] =
		default_handler;
	mcause_trap_table[ENVIRONMENT_CALL_FROM_U_MODE] =
		default_handler;
	mcause_trap_table[ENVIRONMENT_CALL_FROM_S_MODE] =
		default_handler;
	mcause_trap_table[RESERVED_TRAP1] =
		default_handler;
	mcause_trap_table[ENVIRONMENT_CALL_FROM_M_MODE] =
		default_handler;
	mcause_trap_table[INSTRUCTION_PAGE_FAULT] =
		default_handler;
	mcause_trap_table[LOAD_PAGE_FAULT] =
		default_handler;
	mcause_trap_table[RESERVED_TRAP2] =
		default_handler;
	mcause_trap_table[STORE_AMO_PAGE_FAULT] =
		default_handler;
	log_info("trap_init exited \n ");
}

/** @fn init
 * @brief initialize the necessary variables for system start
 */
void init(void)
{

	uart_init();
	
	log_info("init entered \n ");

	asm volatile("la t0, trap_entry\t\n"
			" csrw mtvec, t0\t\n");

#ifdef AARDONYX
	micron_disable_xip_volatile(0,0);
	flashMemInit();
#endif


//	section_init();
	trap_init();

	main();

	log_info("init exited\n");
}

