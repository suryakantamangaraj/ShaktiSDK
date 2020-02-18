/***************************************************************************
* 
* Project           			        :  shakti devt board
* Name of the file	     		        :  rgb.c
* Created date			                :  20.08.2019
* Name of Author               		    :  Soutrick Roy Chowdhury
* Email ID                       	    :  soutrick97@gmail.com
*
*****************************************************************************/


#include "platform.h"
#include "gpio.h"

/** @fn delay_loop
 * @brief Maintains the required delay to perform an operation
 * @details 
 * @warning 
 * @param[in] Delay  Required(ms)
 * @param[Out] NULL
 */
extern void delay_loop(unsigned long cntr1, unsigned long cntr2);

/** @fn main
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] NULL
 */
void main()
{
    //Assume  0 for INPUT and  1 for OUTPUT
    write_word(GPIO_DIRECTION_CNTRL_REG, 0x00000FFF);

    while (1) {
        write_word(GPIO_DATA_REG, GPIO0);
	    delay_loop(1000, 1000);
	printf("\nRED LIGHT");			//RED LIGHT.
        write_word(GPIO_DATA_REG, 0x00);
        delay_loop(1000,1000);

        write_word(GPIO_DATA_REG, GPIO1);
	    delay_loop(1000, 1000);
	printf("\nGREEN LIGHT");			//GREEN LIGHT.
        write_word(GPIO_DATA_REG, 0x00);
        delay_loop(1000,1000);
        
        write_word(GPIO_DATA_REG, GPIO2);
	    delay_loop(1000, 1000);
	printf("\nBLUE LIGHT");			//BLUE LIGHT.
        write_word(GPIO_DATA_REG, 0x00);
        delay_loop(1000,1000);
    }
}
