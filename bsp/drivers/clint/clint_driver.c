/***************************************************************************
* Project           			: shakti devt board
* Name of the file	     		: clint_driver.c
* Created date			        : 26.02.2019
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

uint64_t*  mtime   = 0x0200bff8;
uint64_t* mtimecmp = 0x02004000;

/** @fn mtime_low
 * @brief 
 * @details 
 * @warning 
 * @param[in] No input parameter
 * @param[Out] long
 */
static unsigned long mtime_low( )
{
  return *(volatile unsigned long *)(CLINT_BASE + MTIME);
}

/*
Get each 32 bit and append for full timer value
*/

/** @fn  mtime_high
 * @brief 
 * @details 
 * @warning 
 * @param[in] No input parameter
 * @param[Out] unsigned 32bit int
 */
static uint32_t mtime_high(void)
{
  return *(volatile uint32_t *)(CLINT_BASE + MTIME + 4);
}

/** @fn  get_timer_value
 * @brief 
 * @details 
 * @warning 
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
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
void configure_counter( uint64_t value)
{
	*mtimecmp = *mtime + value;
	log_info("mtimecmp value = %x\n", *mtimecmp);
	log_info("mtime value = %x\n", *mtime);
}

/** @fn  mach_clint_handler
 * @brief
 * @details
 * @warning
 * @param[in] unsigned int ptr
 * @param[Out] no output parameters
 */
void mach_clint_handler(uintptr_t int_id, uintptr_t epc)
{
	unsigned int  interrupt_id;

	log_trace("\nmach_clint_handler entered\n");

	log_info("mtimecmp value = %x\n", *mtimecmp);
	log_info("mtime value = %x\n", *mtime);

	*mtimecmp = (uint64_t) -1;

	log_info("mtimecmp value = %x\n", *mtimecmp);
	log_info("mtime value = %x\n", *((uint32_t *)(0x0200bffc)));

	log_trace("mach_clint_handler exited\n");
}

