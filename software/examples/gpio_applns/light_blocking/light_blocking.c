/***************************************************************************
* 
* Project           			        :  shakti devt board
* Name of the file	     		        :  light_blocking.c
* Created date			                :  20.08.2019
* Name of Author               		    :  Soutrick Roy Chowdhury
* Email ID                       	    :  soutrick97@gmail.com
*
*****************************************************************************/


#include "gpio.h"
#include "platform.h"
#include <stdio.h>

extern void delay_loop(unsigned long cntr1, unsigned long cntr2);

/** @fn main
 * @brief Gives output as HIGH when partition is introduced and LOW when partition is removed       with the help of gpio pins 
 * @details    
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
void main()
{   
    unsigned long readData = 0;
    write_word(GPIO_DIRECTION_CNTRL_REG, 0x0000);

    while (1) {
        readData = read_word(GPIO_DATA_REG);

        if(readData == 0x00000001) {
            printf("\n Blocked");
        }
        else {
            printf("\n Not Blocked");
        }
        delay_loop(1000,1000);
    }
}
    
