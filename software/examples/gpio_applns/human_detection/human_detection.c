/***************************************************************************
* 
* Project           			            :  shakti devt board
* Name of the file	     		          :  human_detection.c
* Created date			                  :  20.08.2019
* Brief Description of file     	    :  Helps to detects the persons around the range of the module with the help of gpio pins
* Name of Author               		    :  Soutrick Roy Chowdhury
* Email ID                       	    :  soutrick97@gmail.com
*
*****************************************************************************/


#include <stdio.h>
#include "gpio.h"
#include "platform.h"

extern void delay_loop(unsigned long cntr1, unsigned long cntr2);

/** @fn main
 * @brief Used to read through Human Detection Sensors
 * @details Printing the presence of a person near it
 * @warning We have to set the potentiometer correctly to get the correct result
 * @param[in] 
 * @param[Out] NULL
 */
void main()
{
    unsigned long readData = 0;
    write_word(GPIO_DIRECTION_CNTRL_REG, 0x00000000);
    
    while (1){
        	readData = read_word(GPIO_DATA_REG);
		      if (readData == 0x00000001){
              printf("\nHuman Detected");
            }
            else{
              printf("\nNo one detected");
            }
            
	      	delay_loop(1000, 1000);
    }
}
    
