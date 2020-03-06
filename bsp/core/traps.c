/***************************************************************************
 * Project           			: shakti devt board
 * Name of the file	     		: traps.c
 * Brief Description of file    : source file for first level of trap handling.
 * Name of Author    	        : Sathya Narayanan N
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

 ***************************************************************************/
#include "traps.h"

/** @fn extract_ie_code
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
unsigned int extract_ie_code(unsigned int num)
{
	unsigned int exception_code;

	log_trace("\nextract_ie_code entered\n");

	exception_code = (num & 0X7FFFFFFF);

	log_info("exception code = %x\n",exception_code);

	log_trace("extract_ie_code exited\n");

	return exception_code;
}

/** @fn default_handler
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
void default_handler(uintptr_t mcause, uintptr_t epc)
{
	log_trace("\ndefault_handler entered\n");

	while(1);

	log_trace("default_handler exited\n");
}

/** @fn handle_trap
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
uintptr_t handle_trap(uintptr_t mcause, uintptr_t epc)
{
	unsigned int ie_entry = 0;;

	log_trace("\nhandle_trap entered\n");

	/*
	   risc v priv spec v1.10 section 3.1.20 Machine Cause Register (mcause)

	   XLEN -1   XLEN-2                                           0
	   ------------------------------------------------------------
	   | Interrupt |    Exception code                            |
	   ------------------------------------------------------------
	   1                            XLEN-1

	   The mcause register is an XLEN-bit read-write register formatted as shown in Figure 3.2
	   1. When a trap is taken into M-mode, mcause is written with a code indicating the event that caused the trap.
	   Otherwise, mcause is never written by the implementation, though it may be explicitly written by software.
	 */

	log_info("mcause = %x, epc = %x\n", mcause, epc);

	/*
	   The Interrupt bit in the mcause register is set if the trap was caused by an interrupt.
	   The Exception Code field contains a code identifying the last exception
	 */

	if (mcause & 0x80000000){

		ie_entry = extract_ie_code(mcause);

		log_debug("Source of Trap: Interrupt\n");

		mcause_interrupt_table[ie_entry](mcause, epc);
	}
	else{
		log_debug("Source of Trap: Software\n");

		mcause_trap_table[mcause](mcause, epc);
	}

	log_trace("handle_trap exited\n");

return epc;
}

