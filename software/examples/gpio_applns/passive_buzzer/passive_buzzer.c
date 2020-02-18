/***************************************************************************
* 
* Project           			        :  shakti devt board
* Name of the file	     		        :  passive_buzzer.c
* Created date			                :  20.08.2019
* Name of Author               		    :  Soutrick Roy Chowdhury
* Email ID                       	    :  soutrick97@gmail.com
*
*****************************************************************************/

#include "platform.h"
#include "gpio.h"

extern void delay_loop(unsigned long cntr1, unsigned long cntr2);

/** @fn main
 * @brief A passive buzzer (AKA magnetic transducer) can make different tones,
 *  but the devices that controls the buzzer has to provide it with an oscillating
 *  electronic signal at a desired frequency. The supplied frequency will determine 
 *  the tone. Supplying just a fixed voltage will generate no sound, except perhaps
 *  a slight "tick" at the point when the power source is connected or disconnected from the buzzer.
 * @param[in]  
 * @param[Out] 
 */
void main()
{
    // Assume 0 for Input and 1 for Output
    write_word(GPIO_DIRECTION_CNTRL_REG, GPIO0);	//Connect in a Bit 0
    int i = 0;

    while (1) {
        for (i = 0; i < 80; i++) {			        //When a frequency sound 
            write_word(GPIO_DATA_REG, GPIO0);	//Sends tone
            delay_loop(1000,1000);
            write_word(GPIO_DATA_REG, 0x00);		//No tone
            delay_loop(1000,1000);
        }

        for (i = 0; i < 80; i++) {
            write_word(GPIO_DATA_REG, GPIO0);
            delay_loop(1000,1000);
            write_word(GPIO_DATA_REG, 0x00);
            delay_loop(1000,1000);
        }
        
    }
}
    
