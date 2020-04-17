/***************************************************************************
* Project           			: shakti devt board
* Name of the file	     		: clint_driver.c
* Brief Description of file     : source file for clint.
* Name of Author    	        : Sathya Narayanan N
* Email ID                      : sathya281@gmail.com

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

#include "clint_driver.h"
#include "log.h"
#include "defines.h"

uint64_t* mtime    = 0x0200bff8;
uint64_t* mtimecmp = 0x02004000;

/** @fn mtime_low
 * @brief return the lower 32bit of mtime.
 * @details return the lower half of mtime. And this is needed mostly in dealing mtime in 32 bit      *          machines.
 * @warning No warning
 * @param[in] No input parameter
 * @param[Out] unsigned long
 */
static unsigned long mtime_low( )
{
  return *(volatile unsigned long *)(CLINT_BASE + MTIME);
}

/*
Get each 32 bit and append for full timer value
*/

/** @fn  mtime_high
 * @brief return the upper 32 bit of mtime
 * @details return the upper 32 bit of mtime register. This is very useful incase of 32 bit core.     *          Incase of 64 bit core this has to be appended with lower 32 bits adn sent.
 * @warning No warning
 * @param[in] No input parameter
 * @param[Out] unsigned 32bit int
 */
static uint32_t mtime_high(void)
{
  return *(volatile uint32_t *)(CLINT_BASE + MTIME + 4);
}

/** @fn  get_timer_value
 * @brief return the mtime value for a 32 bit or 64 bit machine
 * @details return the mtime value based on the __riscv_xlen. Incase of 64 bit, this joins the upper  *          and lower 32 bits of mtime and return
 * @warning No warning
 * @param[in] No input parameter
 * @param[Out] unsigned 64bit int
 */
uint64_t get_timer_value()
{

#if __riscv_xlen == 32
   return ( ((uint64_t)mtime_high() << 32) | mtime_low());
#else
  return mtime_low();
#endif
}

/** @fn configure_counter
 * @brief sets up the timer
 * @details sets the mtimecmp to current mtime + delta
 * @warning No warning
 * @param[in] unsigned 64bit int (delta value after which interrupt happens)
 * @param[Out] No output parameter
 */
void configure_counter( uint64_t value)
{
	*mtimecmp = *mtime + value;
	log_info("mtimecmp value = %x\n", *mtimecmp);
	log_info("mtime value = %x\n", *mtime);
}

/** @fn  mach_clint_handler
 * @brief handler for machine timer interrupt
 * @details handler for machine timer interrupt. This handles the timer interrupt and sets mtimecmp to clear timer interrupt.
 * @warning No warning
 * @param[in] unsigned int ptr
 * @param[Out] No output parameter
 */
void mach_clint_handler(uintptr_t int_id, uintptr_t epc)
{
	unsigned int  interrupt_id;

	log_trace("\nmach_clint_handler entered\n");

	log_debug("mtimecmp value = %x\n", *mtimecmp);
	log_debug("mtime value = %x\n", *mtime);
  printf("Timer interrupt handled\n");
	
  *mtimecmp = (uint64_t) -1;

	log_info("mtimecmp value = %x\n", *mtimecmp);
	log_info("mtime value = %x\n", *((uint32_t *)(0x0200bffc)));

	log_trace("mach_clint_handler exited\n");
}
