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
    write_word(GPIO_DIRECTION_CNTRL_REG, 0x00000001);
    
    while (1) {
        write_word(GPIO_DATA_REG, 0x00000001);
        delay_loop(1000,5000);
        write_word(GPIO_DATA_REG, 0x00);
        delay_loop(1000,5000);
        printf("\nWORKING");
    }
    
}