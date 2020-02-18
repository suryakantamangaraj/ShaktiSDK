/***************************************************************************
* Project           			:  shakti devt board
* Name of the file	     		:  lm75_softi2c.c
* Created date			        :  20.08.2019
* Brief Description of file     :  Helps to find out temperature of a surrounding with the help of gpio pins.
* Name of Author                :  Soutrick Roy Chowdhury.
* Email ID                      :  soutrick97@gmail.com
*****************************************************************************/
#include "gpio_i2c.h"

#define LM75_SLAVE_ADDRESS 0x90

#define DELAY_COUNT 200

/** @fn Lm75ReadTemperature
 * @brief Complete function to read value from LM75 sensors
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] NULL
 */
unsigned int Lm75ReadTemperature(unsigned long delay)
{
	unsigned char readBuf = 0;
	unsigned short readValue = 0;
	I2cSendSlaveAddress(LM75_SLAVE_ADDRESS, I2C_READ, delay);
	readBuf = I2cReadDataAck(delay);
	readValue = (readBuf << 1);
	readBuf = I2cReadDataNack(delay);
	I2cStop(delay);  
	readValue = (readBuf >> 7) | readValue;
	return readValue;
}

/** @fn main
 * @brief Calling Lm75ReadTemperature to find the temperature
 * @details Printing the Current temperature
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
void main() 
{
	unsigned short tempRead = 0;
	unsigned short temp = 0;
	printf("\n\ttemp sensor initiating!");
	I2cInit();
	tempRead = Lm75ReadTemperature(DELAY_COUNT);
	if(tempRead & 0x100) {
		tempRead = ( (~tempRead) + 1 ) >> 1;
		printf("\n\t Current Temperature:=-%u°C",tempRead);
	}		
	else {
		tempRead = tempRead >> 1;
		printf("\n\t Current Temperature:=+%u°C",tempRead);
	 }
	delay_loop(10000,20000);
}
