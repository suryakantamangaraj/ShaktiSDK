/***************************************************************************
* 
* Project           			        :  shakti devt board
* Name of the file	     		        :  active_buzzer.c
* Created date			                :  20.08.2019
* Name of Author               		    :  Soutrick Roy Chowdhury
* Email ID                       	    :  soutrick97@gmail.com
*
*****************************************************************************/

#include "platform.h"
#include "gpio.h"

extern void delay_loop(unsigned long cntr1, unsigned long cntr2);

/** @fn main
 * @brief Correspondingly making GPIO0 as HIGH and LOW.
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
void main()
{
    //Assumption 1 ---> output, 0 ---> input
    write_word(GPIO_DIRECTION_CNTRL_REG, GPIO0);

    while (1) {
        write_word(GPIO_DATA_REG, 0x0000);

        delay_loop(1000, 1000);
        write_word(GPIO_DATA_REG, GPIO0);
        
        delay_loop(1000,1000);
        printf("\nWORKED SUCCESSFULLY");
    }
}
