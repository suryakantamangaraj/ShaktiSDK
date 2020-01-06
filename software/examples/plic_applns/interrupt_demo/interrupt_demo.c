/***************************************************************************
 * Project           			:  shakti devt board
 * Name of the file	     		:
 * Created date			        :  
 * Brief Description of file             :  
 * Name of Author    	                :  Sathya Narayanan N 
 * Email ID                              :  sathya281@gmail.com

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

#include "gpio.h"
#include "uart.h"
#include "traps.h"
#include "platform.h"
#include "plic_driver.h"
#include "log.h"
#include "defines.h"
#include "pwm_driver.h"

/** @fn 
 * @brief 
 *
 * @details 
 *  
 *
 * @warning 
 *
 * @param[in] 
 * @param[Out] 
 */

void dump_word_memory(unsigned int* start, unsigned int word_length)
{
	unsigned int i=0;
	void *address;

	address = (unsigned int *) start;

	while(i++< word_length)
	{
		log_info("address = %x data = %x\n", address, *(unsigned int *) address);
		address+=4;
	}
}

/** @fn 
 * @brief 
 *
 * @details 
 *  
 *
 * @warning 
 *
 * @param[in] 
 * @param[Out] 
 */

void dump_byte_memory(unsigned int* start, unsigned int word_length)
{
	unsigned int i=0;
	void *address;

	address = (unsigned char *) start;

	while(i++< word_length)
	{
		log_info("address = %x data = %x\n", address, *(unsigned char
							       *) address);
		address+=1;
	}
}

/** @fn 
 * @brief 
 *
 * @details 
 *  
 *
 * @warning 
 *
 * @param[in] 
 * @param[Out] 
 */

unsigned handle_button_press (unsigned num)
{
	log_info("button pressed\n");
	return 0;
}

int main(void){
	unsigned int int_id = 1;
	register uint32_t retval;
	int i;

	isr_table[PLIC_INTERRUPT_1] = handle_button_press;

	dump_word_memory(0x0c000000, 24);
	dump_byte_memory(0x0c001000, 4);
	dump_byte_memory(0x0c002000, 4);
	read_word(0x0c010000);
	read_word(0x0c010010);

	plic_init();

	//interrupt id 13, 10, 14, 20, 21 are coming continuously without manual trigger

	for(int i=1;i<25;i++)
		configure_interrupt(i);

	dump_word_memory(0x0c000000, 24);
	dump_byte_memory(0x0c001000, 4);
	dump_byte_memory(0x0c002000, 4);
	read_word(0x0c010000);
	read_word(0x0c010010);


	// Enable Global (PLIC) interrupts.
	asm volatile("li      t0, 8\t\n"
		     "csrrs   zero, mstatus, t0\t\n"
		    );

	asm volatile("li      t0, 0x800\t\n"
		     "csrrs   zero, mie, t0\t\n"
		    );

	asm volatile(
		     "csrr %[retval], mstatus\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	printf(" retval = %x\n", retval);

	asm volatile(
		     "csrr %[retval], mie\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	printf(" retval = %x\n", retval);

	asm volatile(
		     "csrr %[retval], mip\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	printf(" retval = %x\n", retval);

	while(1){
		asm volatile(
			     "csrr %[retval], mip\n"
			     :
			     [retval]
			     "=r"
			     (retval)
			    );

		i++;

		if((i%10000000) == 0){
			printf(" retval = %x\n", retval);
			dump_word_memory(0x0c000000, 24);
			dump_byte_memory(0x0c001000, 4);
			dump_byte_memory(0x0c002000, 4);
			read_word(0x0c010000);
			read_word(0x0c010010);
		}

	}

	return 0;
}

