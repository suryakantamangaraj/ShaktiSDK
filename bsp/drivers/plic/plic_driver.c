/***************************************************************************
 * Project           			: shakti devt board
 * Name of the file	     		: plic_driver.c
 * Brief Description of file    : source file for plic.
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
#include "pwm_driver.h"
#include "plic_driver.h"
#include "platform.h"
#include "log.h"
#include "stddef.h"
#include "gpio.h"

/*
   Global interrupt data maintenance structure
 */

interrupt_data_t hart0_interrupt_matrix[PLIC_MAX_INTERRUPT_SRC];

/** @fn interrupt_complete
 * @brief write the int_id to complete register
 * @details Signals completion of interrupt. From s/w side the interrupt claim/complete 	                register is written with the interrupt id.
 * @warning No warning
 * @param[in] unsigned int
 * @param[Out] No output parameter
 */
void interrupt_complete(unsigned int interrupt_id)
{
	log_trace("\ninterrupt_complete entered\n");

	unsigned int *claim_addr =  (unsigned int *) (PLIC_BASE_ADDRESS +
						      PLIC_CLAIM_OFFSET);

	*claim_addr = interrupt_id;
	hart0_interrupt_matrix[interrupt_id].state = SERVICED;
	hart0_interrupt_matrix[interrupt_id].count++;

	log_info("interrupt id %d, state changed to %d\n", interrupt_id,
		 hart0_interrupt_matrix[interrupt_id].state);

	log_debug("interrupt id = %x \n reset to default values state = %x \
		  \n priority = %x\n count = %x\n", \
		  hart0_interrupt_matrix[interrupt_id].id, \
		  hart0_interrupt_matrix[interrupt_id].state, \
		  hart0_interrupt_matrix[interrupt_id].priority, \
		  hart0_interrupt_matrix[interrupt_id].count);

	log_trace("interrupt_complete exited\n");
}

/** @fn  interrupt_claim_request
 * @brief know the id of the interrupt
 * @details read the interrupt claim register to know the interrupt id of the highest priority        *          pending interrupt 
 * @warning No warning
 * @param[in] no input parameters
 * @param[Out] unsigned int
 */
unsigned int interrupt_claim_request()
{
	unsigned int *interrupt_claim_address = NULL;
	unsigned int interrupt_id;

	log_trace("\ninterrupt_claim_request entered\n");

	/*
	   return the interrupt id. This will be used to index into the plic isr table.
	   From the isr table, the exact isr will be called

	   refer https://gitlab.com/shaktiproject/uncore/devices/blob/master/plic/plic.bsv as on 26/8/2019
	 */

	interrupt_claim_address = (PLIC_BASE_ADDRESS + PLIC_CLAIM_OFFSET);

	interrupt_id = *interrupt_claim_address;

	log_info("interrupt id [%x] claimed  at address %x\n", interrupt_id,
		interrupt_claim_address );

	log_trace("interrupt_claim_request exited\n");

	return interrupt_id;
}

/** @fn mach_plic_handler
 * @brief handle machine mode plic interrupts
 * @details find the int id that caused of interrupt, process it and complete the interrupt.
 * @warning No warning
 * @param[in] unsigned int ptr, unsigned int ptr
 * @param[Out] No output parameter
 */
void mach_plic_handler(uintptr_t int_id, uintptr_t epc)
{
	unsigned int  interrupt_id;

	log_trace("\nmach_plic_handler entered\n");

	interrupt_id = interrupt_claim_request();

	log_debug("interrupt id claimed = %x\n", interrupt_id);

	if (interrupt_id <= 0 || interrupt_id > PLIC_MAX_INTERRUPT_SRC)
	{
		log_fatal("Fatal error, interrupt id [%x] claimed is wrong\n", interrupt_id);
	}

	/*
	   clear IP bit ?

	   After the highest-priority pending interrupt is claimed by a target and the corresponding
	   IP bit is cleared, other lower-priority pending interrupts might then become visible to
	   the target, and so the PLIC EIP bit might not be cleared after a claim

	   reference - risc v priv spec v1.10 section 7.10 Interrupt Claims
	 */

	/*change state to active*/
	hart0_interrupt_matrix[interrupt_id].state = ACTIVE;

	log_info("interrupt id %d, state changed to %d\n",
		 interrupt_id,hart0_interrupt_matrix[interrupt_id].state);

	/*call relevant interrupt service routine*/
	isr_table[interrupt_id](interrupt_id);

	interrupt_complete(interrupt_id);

	log_debug("interrupt id %d complete \n", interrupt_id);

	log_trace("\nmach_plic_handler exited\n");
}

/** @fn  int isr_default
 * @brief default interrupt service routine
 * @details Default isr. Use it when you dont know what to do with interrupts
 * @warning No warning
 * @param[in] unsigned int
 * @param[Out] unsigned int
 */
unsigned int isr_default(unsigned int interrupt_id)
{
	log_trace("\nisr_default entered\n");

	if( interrupt_id > 0 && interrupt_id < 7 )  //PWM Interrupts
	{
		/*
		   Assuming 6 pwm's are there
		 */

		if(pwm_check_continuous_mode((6-interrupt_id)) == 0)
		{
			set_pwm_control_register((6-interrupt_id),0x80);
		}
	}

	log_info("interrupt [%d] serviced\n",interrupt_id);

	log_trace("\nisr_default exited\n");

	return 0;
}

/** @fn interrupt_enable
 * @brief enable the interrupt
 * @details A single bit that enables an interrupt. The bit position corresponds to the interrupt id
 * @warning No warning
 * @param[in] unsigned int
 * @param[Out] no ouput parameters
 */
void interrupt_enable(unsigned int interrupt_id)
{
	uint8_t *interrupt_enable_addr;
	uint8_t current_value = 0x00, new_value;

	log_trace("\ninterrupt_enable entered \n");

	log_info("interrupt_id = %x\n", interrupt_id);

	log_debug("PLIC BASE ADDRESS = %x, PLIC ENABLE OFFSET = %x\n" \
		  ,PLIC_BASE_ADDRESS, PLIC_ENABLE_OFFSET);

	interrupt_enable_addr = (uint8_t *) (PLIC_BASE_ADDRESS +
					     PLIC_ENABLE_OFFSET +
					     (interrupt_id >> 3));

	current_value = *interrupt_enable_addr;

	log_debug("interrupt_enable_addr = %x current_value = %x \n", \
		  interrupt_enable_addr, current_value);

	/*set the bit corresponding to the interrupt src*/
	new_value = current_value | (0x1 << (interrupt_id & 0x07));

	*interrupt_enable_addr = new_value;

	log_info("interrupt_enable_addr = %x new_value = %x\n", \
		 interrupt_enable_addr, *interrupt_enable_addr);

	log_info("value read: new_value = %x\n", *interrupt_enable_addr);

	log_trace("\ninterrupt_enable exited \n");
}

/** @fn interrupt_disable
 * @brief disable an interrupt
 * @details A single bit that enables an interrupt. The bit position corresponds to the interrupt id
 * @warning No warning
 * @param[in] unsigned int
 * @param[Out] no output parameters
 */
void interrupt_disable(unsigned int interrupt_id)
{
	uint8_t *interrupt_disable_addr = 0;
	uint8_t current_value = 0x00, new_value;

	log_trace("\ninterrupt_disable entered \n");

	log_info("interrupt_id = %x\n", interrupt_id);

	log_debug("PLIC BASE ADDRESS = %x, PLIC ENABLE OFFSET = %x interrupt_id = %x\n",
		  PLIC_BASE_ADDRESS, PLIC_ENABLE_OFFSET, interrupt_id);

	interrupt_disable_addr = (uint8_t *) (PLIC_BASE_ADDRESS +
					      PLIC_ENABLE_OFFSET +
					      (interrupt_id >> 3));

	current_value = *interrupt_disable_addr;

	log_debug("interrupt_disable_addr = %x current_value = %x \n",
		  interrupt_disable_addr, current_value);

	/*unset the bit corresponding to the interrupt src*/
	new_value = current_value & (~(0x1 << (interrupt_id & 0x07)));

	*interrupt_disable_addr = new_value;

	hart0_interrupt_matrix[interrupt_id].state = INACTIVE;

	log_info("interrupt id %d, state changed to %d\n",
		 interrupt_id,hart0_interrupt_matrix[interrupt_id].state);

	log_info("interrupt_disable_addr = %x new_value = %x\n",
		 interrupt_disable_addr, *interrupt_disable_addr);

	log_trace("interrupt_disable exited\n");
}

/** @fn set_interrupt_threshold
 * @brief set priority threshold for all interrupts
 * @details set a threshold on interrrupt priority. Any interruptthat has lesser priority than the threshold is  * ignored.
 * @warning No warning
 * @param[in] unsigned int
 * @param[Out] no output parameters
 */
void set_interrupt_threshold(unsigned int priority_value)
{
	log_trace("\nset interrupt_threshold entered\n");

	unsigned int *interrupt_threshold_priority = NULL;

	interrupt_threshold_priority = (unsigned int *) (PLIC_BASE_ADDRESS +
							 PLIC_THRESHOLD_OFFSET);

	*interrupt_threshold_priority = priority_value;

	log_info("plic threshold set to %d\n", *interrupt_threshold_priority);

	log_trace("set interrupt_threshold exited\n");
}

/** @fn set_interrupt_priority
 * @brief set priority for an interrupt source
 * @details set priority for each interrupt. This is a 4 byte field.
 * @warning No warning
 * @param[in] unsigned int, unsigned int
 * @param[Out] no output parameters
 */
void set_interrupt_priority(unsigned int priority_value, unsigned int int_id)
{
	log_trace("\n set interrupt priority entered %x\n", priority_value);

	uint32_t * interrupt_priority_address;

	/*
	   based address + priority offset + 4*interruptId
	 */


	interrupt_priority_address = (uint32_t *) (PLIC_BASE_ADDRESS +
						      PLIC_PRIORITY_OFFSET +
						      (int_id <<
						       PLIC_PRIORITY_SHIFT_PER_INT));

	log_info("interrupt_priority_address = %x\n", interrupt_priority_address);

	log_info("current data at interrupt_priority_address = %x\n", *interrupt_priority_address);

	*interrupt_priority_address = priority_value;

	log_info(" new data at interrupt_priority_address = %x\n", *interrupt_priority_address);

	log_trace("set interrupt priority exited\n");
}

/** @fn configure_interrupt_pin
 * @brief configure a gpio pin for each interrupt
 * @details enable the corresponding gpio pin for a interrupt as read.
 * @warning No warning
 * @param[in] unsigned int
 * @param[Out] No output parameter
 */
void configure_interrupt_pin(unsigned int id)
{
	log_trace("\nconfigure interrupt pin entered\n");

	unsigned int read_data, pin;

	read_data = read_word(GPIO_DIRECTION_CNTRL_REG);

	log_debug("GPIO DIRECTION REGISTER VALUE = %x\n", read_data);

	write_word(GPIO_DIRECTION_CNTRL_REG, 0x00000000);

	log_debug("Data written to GPIO DIRECTION CTRL REG = %x\n", read_word(GPIO_DIRECTION_CNTRL_REG));

	log_trace("configure interrupt pin exited\n");
}

/** @fn plic_init
 * @brief intitializes the plic module
 * @details intitializes the registers to default values. sets up the plic meta data table. assigns the plic handler to  mcause_interrupt_table.,By default interrupts are disabled.
 * @warning No warning
 * @param[in] no input parameters
 * @param[Out] no output parameters
 */
void plic_init()
{
	unsigned int int_id = 0;

	log_trace("\nplic_init entered\n");

	/*Assign service routine for external interrupt in machine mode*/
	mcause_interrupt_table[MACH_EXTERNAL_INTERRUPT] = mach_plic_handler;

	log_info("Assigned mach_plic_handler to trap id : %d\n", MACH_EXTERNAL_INTERRUPT);

	/*
	   risc v priv spec v1.10 section 7.5 onwards

	   Global interrupt sources are assigned small unsigned integer identifiers, beginning at the value 1.
	   An interrupt ID of 0 is reserved to mean “no interrupt”.

	   The priority value 0 is reserved to mean “never interrupt”,
	   and interrupt priority increases with increasing integer values.
	 */

	hart0_interrupt_matrix[0].state = INACTIVE;
	hart0_interrupt_matrix[0].id = 0;
	hart0_interrupt_matrix[0].priority = 0;
	hart0_interrupt_matrix[0].count = 0;

	interrupt_disable(int_id);

	for(int_id = 1; int_id < PLIC_MAX_INTERRUPT_SRC; int_id++)
	{
		hart0_interrupt_matrix[int_id].state = INACTIVE;
		hart0_interrupt_matrix[int_id].id = int_id;
		hart0_interrupt_matrix[int_id].priority = PLIC_PRIORITY_3;
		hart0_interrupt_matrix[int_id].count = 0;

                log_debug("\n*************************************************");

		/*Disable all interrupts at the beginning*/
		interrupt_disable(int_id);

		/*assign a default isr for all interrupts*/
		isr_table[int_id] = isr_default;

		/*set priority for all interrupts*/

		set_interrupt_priority(PLIC_PRIORITY_3, int_id);

		log_debug("\ninterrupt id = %x \nreset to default values state = %x \
			   \npriority = %x\ncount = %x\n \
                           \n*************************************************",
			    hart0_interrupt_matrix[int_id].id, \
			    hart0_interrupt_matrix[int_id].state, \
			    hart0_interrupt_matrix[int_id].priority, \
			    hart0_interrupt_matrix[int_id].count);
	}

	/* An isr for each and every unique interrupt source has to be added explicitly at init time*/

	/*Enable required interrupts
	  interrupt_enable(int_id);
	 */
	/*set threshold value for interrupts*/
	set_interrupt_threshold(PLIC_PRIORITY_2);


	log_trace("plic_init exited \n");
}

/** @fn configure_interrupt 
 * @brief configure the interrupt pin and enable bit
 * @details enables the interrupt and corresponding physical pin. Needs to be called in every         *          interrupt trigger and handling flow
 * @warning Here it is assumed, to have a one to one mapping
 *          between interrupt enable bit and interrupt pin
 * @param[in] unsigned int 
 * @param[Out] No output parameter
 */
void configure_interrupt(unsigned int int_id)
{
	log_trace("\nconfigure_interrupt entered \n");

	log_info("interrupt id = %x \n", int_id);

	configure_interrupt_pin(int_id);

	interrupt_enable(int_id);

	log_trace("configure_interrupt exited \n");
}
