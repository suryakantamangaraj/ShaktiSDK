#include "platform.h"
#include "gpio.h"

extern void delay_loop(unsigned long cntr1, unsigned long cntr2);

/** @fn main
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */

void main()
{
    unsigned long readData = 0;
    
    while (1) {
        write_word(GPIO_DIRECTION_CNTRL_REG, 0x00);
        readData = read_word(GPIO_DATA_REG);
        printf("\n Read Data:=0x%x", readData);
        if (readData == 0x00000001) {
            write_word(GPIO_DIRECTION_CNTRL_REG, 0x00000002);
            write_word(GPIO_DATA_REG, 0x00000002);
            printf("\nTurn on Motor");
        }
        else {
            printf("\nTurn off Motor");
        }
        delay_loop(1000,1000);
    } 
}
