/*
 Created by Kotteeswaran
 Email id: kottee.1@gmail.com

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
*/



#include <stdint.h>//Includes the definitions of standard input/output functions//
#include "i2c.h"
#include "log.h"


#define LM75_SLAVE_ADDRESS 0x90//Defines the Starting address of slave//
#define LM75_TEMP_REG_OFFSET 0x00
#define LM75_CONF_REG_OFFSET 0x01
#define LM75_HYST_REG_OFFSET 0x02
#define LM75_OFFSET_REG_OFFSET 0x03
#define DELAY_VALUE 900

int read_lm75_register(unsigned int reg_offset, unsigned int *readTemp, unsigned long delay)
{
	unsigned char read_buf[4] = {'\0'};
	int i = 0, j = 0,  k = 0, status=0;
	unsigned char temp = 0;
//Writes the slave address for write
		i2c_send_slave_address(LM75_SLAVE_ADDRESS, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
		i2c_write_data(reg_offset  /*LM75_TEMP_REG_OFFSET */, delay);
//Stops the I2C transaction to start reading the temperature value.
		i2c_stop();
//		delay_loop(800, 800);


//Writes the slave address for read
		i2c_send_slave_address(LM75_SLAVE_ADDRESS, I2C_READ, 800);


/* Make a dummy read as per spec of the I2C controller */
		i2c_read_data(&temp, delay);

//Reads the MSB Byte of temperature [D9 - D1]
			i2c_read_data(&read_buf[1], delay);
			i2c_nack();

//Reads the MSB Byte of temperature [D9 - D1]
			i2c_read_data(&read_buf[0], delay);
			i2c_stop();
			*readTemp = (read_buf[1] << 1) | (read_buf[0] >> 7);

			return 0;
}

int write_lm75_register(unsigned int reg_offset, unsigned int write_value, unsigned long delay)
{
	int i = 0, j = 0,  k = 0, status=0;
	unsigned int temp = 0;
		i2c_send_slave_address(LM75_SLAVE_ADDRESS, I2C_WRITE, delay);
		i2c_write_data(reg_offset /*LM75_TEMP_REG_OFFSET */, delay);
		i2c_write_data( ( (write_value >> 1) & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
		printf("\n Write Value[0]: %02x", (write_value >> 1) & 0xff);
		i2c_write_data( ( ( (write_value & 0x01) << 7) & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
		printf("\n Write Value[1]: %02x", ( ( (write_value & 0x01) << 7) & 0xff));
//Stops the I2C transaction to start reading the temperature value.
		i2c_stop();
//		delay_loop(800, 800);


			return 0;
}

int main()

{
    temperature_reading();
    return(1);
}    

int temperature_reading()
    {
	int timeout;
	unsigned int tempReadValue = 0;
	unsigned long delay = 1000;


	log_debug("\tI2C: Starting Transaction\n");

	//Initialises I2C Controller
		if(shakti_init_i2c(0x1F,0x91))
		{
				log_error("\tSomething Wrong In Initialization\n");
				return -1;
		}
	else
				log_info("\tIntilization Happened Fine\n");

	write_lm75_register(LM75_HYST_REG_OFFSET, 0x30, delay);
	write_lm75_register(LM75_OFFSET_REG_OFFSET, 0x35, delay);

	while(1)
	{
		if(0 == read_lm75_register(LM75_HYST_REG_OFFSET, &tempReadValue, delay))
		{
			//Display Temperature value
//			printf("\nTemperature read value is %x", tempReadValue);
//				tempReadValue = ( (~tempReadValue) + 1 );
				log_info("\n\t Hyst Reg Value:=%u",tempReadValue);
		}
		else
		{
	//Display the error
			log_error("\nHyst Reg Value failed.");
		}
		if(0 == read_lm75_register(LM75_OFFSET_REG_OFFSET, &tempReadValue, delay))
		{
			//Display Temperature value
				log_info("\n\t Offset Reg Value:=%u",tempReadValue);
		}
		else
		{
	//Display the error
			log_error("\nOffset Reg Value failed.");
		}

		if(0 == read_lm75_register(LM75_TEMP_REG_OFFSET, &tempReadValue, delay))
		{
			//Display Temperature value
//			printf("\nTemperature read value is %x", tempReadValue);
			if(tempReadValue & 0x100) {
				tempReadValue = ( (~tempReadValue) + 1 ) >> 1;
				log_info("\n\t Current Temperature:=-%u°C",tempReadValue);
			}
			else {
				tempReadValue = tempReadValue >> 1;
				log_info("\n\t Current Temperature:=+%u°C",tempReadValue);
			 }
		}
		else
		{
	//Display the error
			log_error("\nTemperature read failed.");
		}
		delay_loop(1000, 1000);
	}


	return 0;
}
