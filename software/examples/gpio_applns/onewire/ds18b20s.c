#include <stdio.h>
#include "uart.h"
#include "gpio.h"
#include "platform.h"
#define GPIO_PIN (1 << 0)// set gpio pin 0 as a input/output 

unsigned char Check = 0;

/** @fn DelayUs
 * @brief 
 * @details 
 * @warning 
 * @param[in]  
 * @param[Out] 
 */
void DelayUs(unsigned long time)
{
//    unsigned int i = 0;
    while (time--);
}

/** @fn wait_for 
 * @brief 
 * @details 
 * @warning 
 * @param[in]  
 * @param[Out] 
 */
void wait_for(int time)
{   //1 mic`ro second
  while(time--) ;
}

 
int StartSignal()
{
  uint8_t okCount = 0, nOkCount = 0;
  nOkCount = 0;
  okCount = 0;
  int waittime = 50;
  int okWaitTime = 0;
  printf("enterig to start signal");
//Configure the GPIO pin as output
    write_word(GPIO_DIRECTION_CNTRL_REG,GPIO_PIN);

// keep the io line low for 480us
    write_word(GPIO_DATA_REG,read_word(GPIO_DATA_REG) & ~(GPIO_PIN) );
    wait_for(5000 /*976*/);// delay for 480 us
  /*  if(checkforwait(read_word(GPIO_DATA_REG)))
      printf("delay is happened");
    else
      printf("delay is not happened");*/
//Configure the GPIO pin as input

  printf("\nDS18B20-2");
  write_word(GPIO_DIRECTION_CNTRL_REG, ~(GPIO_PIN));
  wait_for(70); // delay for 60 us
//    printf("\nDS18B20-2");
     while (1)
     {
       if (read_word(GPIO_DATA_REG) & (GPIO_PIN) == 1)
       {
//         wait_for(1);
//         printf("xxx");
         if (nOkCount++ > 1000)
          return 1;
        }
        else
          break;
      }
      printf("\n Low Value detected.");
       while(read_word(GPIO_DATA_REG) & (GPIO_PIN) == 0)
       {
            wait_for(1);
            if (okWaitTime++ > 65)
            return 0;
        }
      return 1;
}

/** @fn write_byte
 * @brief 
 * @details 
 * @warning 
 * @param[in]  
 * @param[Out] 
 */
void write_byte(char val)
{
    int i;
    //Configure the GPIO pin as input
    write_word(GPIO_DIRECTION_CNTRL_REG, ~(GPIO_PIN));
    printf("\n entering into the write_byte");
   // DQ_TRIS = 1;set pin# to input (1)
	for (i = 0; i < 8; i++)
		{
			if((val & (1<<i))!= 0)
			{
			// write 1

            write_word(GPIO_DIRECTION_CNTRL_REG,GPIO_PIN); // set pin# to output (0)


            write_word(GPIO_DATA_REG,read_word(GPIO_DATA_REG) & ~(GPIO_PIN) ); // set pin# to low (0)
            wait_for(1); //__delay_us(1); // 1 wire require time delay

            // /Configure the GPIO as input and wait for 480 us
            write_word(GPIO_DIRECTION_CNTRL_REG, ~(GPIO_PIN) ); //set pin# to input (release the bus)
          //  write_word(GPIO_DATA_REG, DHT_GPIO_PIN); // make the line high
            wait_for(74); 			//__delay_us(60); 1 wire require time delay
            printf("\n write1 is completed");

			}
			else
			{
			//write 0
            write_word(GPIO_DIRECTION_CNTRL_REG,GPIO_PIN); //DQ_TRIS = 0;  set pin# to output (0)

            write_word(GPIO_DATA_REG,read_word(GPIO_DATA_REG) & ~(GPIO_PIN) ); //DQ = 0;  set pin(line) to low (0)
            wait_for(74); 			//__delay_us(60); 1 wire require time delay
            write_word(GPIO_DIRECTION_CNTRL_REG, ~(GPIO_PIN) ); //DQ_TRIS = 1; set pin# to input (release the bus)
            printf("\n write0 is completed");


			}
		}

}

/** @fn read_byte
 * @brief 
 * @details 
 * @warning 
 * @param[in]  
 * @param[Out] 
 */
int read_byte(void)
{
    int i,result = 0;
    printf("\n entering into the read_byte");
    write_word(GPIO_DIRECTION_CNTRL_REG, ~(GPIO_PIN) ); // set pin# to input (release the bus)
	for(i = 0; i < 8; i++)
		{

        write_word(GPIO_DIRECTION_CNTRL_REG,GPIO_PIN); // set pin# to output (0)

        write_word(GPIO_DATA_REG,read_word(GPIO_DATA_REG) & ~(GPIO_PIN) ); // set pin(line) to low (0)
		wait_for(1); //delay for 2 us
        write_word(GPIO_DIRECTION_CNTRL_REG, ~(GPIO_PIN) ); //set pin# to input (release the bus)
		if( read_word(GPIO_DATA_REG) & (GPIO_PIN))
		result |= 1<<i;
		wait_for(74); // wait for 60 us
		}
    printf("\n read_byte is completed ");
	return result;
}

