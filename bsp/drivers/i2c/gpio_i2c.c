/***************************************************************************
* Project           			:  shakti devt board
* Name of the file	     		:  gpio_i2c.c
* Created date			        :  9.07.2019
* Brief Description of file             :  Performs the I2C operations using gpio pins.
* Name of Author    	                :  Kotteeswaran
* Email ID                              :  kottee.1@gmail.com

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

***************************************************************************/
#include "platform.h"
#include "gpio.h"
#include "gpio_i2c.h"
extern void DelayLoop(unsigned long , unsigned long );

/** @fn static void SetSCLAsOutput()
 * @brief Function for configure GPIO pin (defined by I2C_SCL) as SCL output.
 * @details This function will be called to make the scl line (defined by I2C_SCL). 
 * The clock will always be output in our case. So the GPIO pin (defined by I2C_SCL macro)
 * will always configured as output. Should pass the value '1' to the GPIO pin.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param[in] No input parameters.
 * @param[Out] No output parameters.
 */
static void SetSCLAsOutput()
{
	unsigned long readData = 0;
	readData = read_word(GPIO_DIRECTION_CNTRL_REG);
	write_word(GPIO_DIRECTION_CNTRL_REG, (readData | I2C_SCL) );
	printf("Configure GPIO (SCL) as output\n");
}

/**@brief Function for configure GPIO(defined by I2C_SDA) as SDA output.
 * @details This function will be called to make the SDA line (defined by I2C_SDA)
 *  macro as output.
 * @warning This bit value can be changed as per I2C_SDA macro.
 * @param[in] in_out_cntrl [ 0 --> Configures SDA as input. 1 --> Configure SDA
 * as output]. Else throws error.
 * @param[Out] No output parameters.
 */
static void SetSdaDirection(int in_out_cntrl)
{
	unsigned long readData = 0;
	readData = read_word(GPIO_DIRECTION_CNTRL_REG);

	if(in_out_cntrl) // output
    {
		write_word(GPIO_DIRECTION_CNTRL_REG, (readData | I2C_SDA) );
		printf("\n\tSDA set as output\n");
	}
    else
    {
		write_word(GPIO_DIRECTION_CNTRL_REG, (readData & ~(I2C_SDA) ) );
		printf("\n\tSDA set as input\n");
	}
	else
    {
		printf("\n\tInvalid value passed to configure SDA\n");
	}
	
}

/** @fn static void start(unsigned char delay)
 * @brief Sending start condition for the I2C.
 * @details Start condition is making SDA low when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param[in] delay.
 * @param[Out] No output parameters.
 */
/********************************************************
 * scl (1) ---------------
 *  
 *     (0)
 * 
 * sda (1)------
 *             |
 * sda (0)      ----------
 ********************************************************/

static void start(unsigned char delay)
{

//	Make SDA High;
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SDA | I2C_SCL) );
	DelayLoop(delay, delay);

//		Make SCL high;
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SCL) );
	DelayLoop(delay, delay);

//		Make SDA low;
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(I2C_SDA)) );
	DelayLoop(delay, delay);

//		Make SCL low;
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(I2C_SCL) ) );
	DelayLoop(delay, delay);

	printf("\n\tI2C: I2C Start condition sent\n");
}

/** @fn static void stop(unsigned long delay)
 * @brief Sending stop condition for the I2C.
 * @details Stop condition is making data line (SDA) high when clock(SCL) is high.
 * @warning Nil
 * @param[in] delay.
 * @param[Out] No output parameters.
 */
/********************************************************
 * scl (1) ---------------
 *  
 *     (0)
 * 
 * sda (1)      ------
 *             |
 * sda (0)-----      
 ********************************************************/
static void stop(unsigned long delay)
{
//		Make SDA low;
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(I2C_SDA)) );
	DelayLoop(delay, delay);

//		Make SCL high;
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SCL) );
	DelayLoop(delay, delay);

//	Make SDA High;
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SDA) );
	DelayLoop(delay, delay);
	printf("\n\tI2C: I2C Start condition sent\n");

}

/** @fn static void I2cWriteByte(unsigned char i, unsigned long delay)
 * @brief Writes a byte to the I2C device.
 * @details Data is put on the SDA Line bit by bit and then makes the
 * SCL from low to high to write..
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param[in] writeData --> Value that needs to be written.
 * @param[in] delay.
 * @param[Out] No output parameters.
 */

void I2cWriteByte(unsigned char write_data, unsigned long delay)
{
	unsigned char j=0, k = 0;
	while(j < 8)
	{
		k = write_data;
		k = ( k << j ) & 0x80;
//		printf("\n\r i: %d; j: %d; k: %d", i, j, k);
//		sda=CY;
//The bit value to be transferred over SDA is zero if k is zero. If k == 1, the 
//Bit value to be transferred over SDA will be 1
		if(k == 0)
		{
			write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(I2C_SDA)) );
			DelayLoop(delay, delay);
		}
		else
		{
			write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SDA) );
			DelayLoop(delay, delay);
		}

	//	scl=1;
		write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SCL) );
		DelayLoop(delay, delay);


	//	scl=0;
		write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(I2C_SCL) ) );
		DelayLoop(delay, delay);
		++j;
	}
}

/** @fn static unsigned char I2cReadByte(unsigned long delay)
 * @brief Reads a byte from the I2C device.
 * @details Clock line is made low to high and the slave puts the Data
 *  bit on the SDA line and master stores the value to form a byte.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param[in] delay.
 * @param[Out] returns the value of readData .
 */

unsigned char I2cReadByte(unsigned long delay)
{
/* count value for bit shift */
    unsigned char j = 0;
/* Carries the read SDA bit value */
	unsigned char bit_value;
/* Concatenates the bit values to make a byte */
	unsigned char read_data = 0;
/* Temporary storage for gpio data register */
  unsigned long read_gpio_data = 0;
	read_data = read_word(GPIO_DATA_REG);

	while(j < 8)
	{
	//	Make SCL high to read SDA Bit value 
	    write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SCL) );
		DelayLoop(delay, delay);

//		Read the SDA value
		read_gpio_data = read_word(GPIO_DATA_REG)  & I2C_SDA;
		if(read_gpio_data != 0) //SDA value is 1
			bit_value = 1; 
		else
			bit_value = 0; //SDA value is 0
			
	    read_data = read_data << 1;
		read_data = read_data | bit_value;
		DelayLoop(delay, delay);

	//	Make clock SCL low to read next bit;
		write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(I2C_SCL) ) );
		DelayLoop(delay, delay);

		++j;
	}

	return read_data;
}

/** @fn static unsigned char ReadAckForWrite(unsigned long delay)
 * @brief After the write operation is done, the slave will send Ack
 *        if there is slave. 
 * @details Clock line is made low to high and the slave puts the Data
 *          bit on the SDA line and master stores the value to form a byte.
 * @warning Nil
 * @param[in] delay.
 * @param[Out] NULL.
 */

unsigned char ReadAckForWrite(unsigned long delay)
{
	unsigned long read_data = 0;
	printf("\n\tI2C: I2C Read\n");
	read_data = read_word(GPIO_DATA_REG);
	DelayLoop(delay, delay);
//	Make I2C clock line high to read the ACK 
	printf("\n\tI2C: I2C Write\n");
	write_word(GPIO_DATA_REG, (read_data | I2C_SCL) );
	DelayLoop(delay, delay);

		printf("\n\tI2C: I2C Write\n");
		read_data = read_word(GPIO_DATA_REG)  & I2C_SDA;

//	Make clock ling low;
	printf("\n\tI2C: I2C Write\n");
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(I2C_SCL) ) );
	DelayLoop(delay, delay);
	printf("\n\tI2C: I2C ReadNackForWrite sent\n");
    
    if(!read_data)
        return 0;
    else
        return 1;
}

/** @fn static void SendAckForRead(unsigned long delay)
 * @brief After the READ operation is done, the master will send Ack
 *        to slave.
 * @details The master will send the ACK (0, pulling the line low) to slave to 
 *          acknowledge that it has received a byte.
 *          The ack is sent by pulling the SDA line low and then one SCL
 *          transition..
 * @warning Nil
 * @param[in] delay.
 * @param[Out] NULL.
 */

 static void SendAckForRead(unsigned long delay)
{
  SetSdaDirection(GPIOD_IS_OUT);

//	readData = read_word(GPIO_DATA_REG);

//	sda=0;
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(I2C_SDA)) );
	DelayLoop(delay, delay);

//	scl=1;
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SCL) );
	DelayLoop(delay, delay);

//	scl=0;
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(I2C_SCL) ) );
	DelayLoop(delay, delay);

  SetSdaDirection(GPIOD_IS_IN);

}

/** @fn static void SendNackForRead(unsigned char delay)
 * @brief After the READ operation is done the master will send Nack
 *        to slave if it wants to terminates the I2C communication.
 * @details The master will send nack if it wants to tell the slave that it is not
 *          able to receive the slave's data byte. 
 *          The ack is sent by pulling the SDA line high (just doesn't do anything
 *          on SDA line) and then one SCL transition..
 * @warning Nil
 * @param[in] delay.
 * @param[Out] NULL.
 */

 static void SendNackForRead(unsigned long delay)
 {
  SetSdaDirection(GPIOD_IS_OUT);

 //	readData = read_word(GPIO_DATA_REG);

 //	sda=0;
  write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG)  | (I2C_SDA)) );
  DelayLoop(delay, delay);

 //	scl=1;
  write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SCL) );
  DelayLoop(delay, delay);

 //	scl=0;
  write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(I2C_SCL) ) );
  DelayLoop(delay, delay);

  SetSdaDirection(GPIOD_IS_IN);

 }

/** @fn static void I2cInit()
 * @brief Configuring the SDA and SCL as OUTPUTS so that Start, Slave address
 * ,and register address or register value that needs to be writen.
 * @details I2C master Inits makes the master ready for either read or write
 * operation.
 * @warning Nil.
 * @param[in] Null.
 * @param[Out] Null.
 */

void I2cInit()
{
  SetSCLAsOutput();
  SetSdaDirection(GPIOD_IS_OUT);
  printf("Initialization successfully done");
}

/** @fn static void I2cSendSlaveAddress(unsigned char slaveAddress, unsigned char rdWRCntrl, unsigned long delay)
 * @brief Sends the slave address to the I2C device and check for acknowledge
 *        from the slave.
 * @details The master has to send the slave address along with read or write
 *          control to to access the internal registers of the I2C slave. The slave device
 *          will respond its presence by sending ack from its side
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param[in] Slave Address.
 * @param[in] Read / Write Control (0 --> Write, 1 --> Read).
 * @param[Out] NULL.
 */

void I2cSendSlaveAddress(unsigned char slave_address, unsigned char rd_wr_cntrl, unsigned long delay)
{
  SetSdaDirection(GPIOD_IS_OUT);

  printf("\n\tI2C: I2C Start\n");
  start(delay);

  printf("\n\tI2C: I2C Send a Byte (Slave Address)\n");
  if(rd_wr_cntrl)
	{
     printf("\n\tI2C: I2C Read\n");
    I2cWriteByte( (slave_address | I2C_READ), delay);
	}
  else
	{
     printf("\n\tI2C: I2C Write\n");
    I2cWriteByte( (slave_address | I2C_WRITE), delay);
	}
  //	Make SDA high to complete the I2C Transmit
  write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SDA) );
  DelayLoop(delay, delay);

  printf("\n\tI2C: I2C Write Ack\n");
  SetSdaDirection(GPIOD_IS_IN);
    ReadAckForWrite(delay);
}

/** @fn static void I2cWriteData(unsigned char writeData, unsigned long delay)
 * @brief Complete function to write a byte in to the I2C slave device.
 * @details When writing a byte, the master has to send the data first and then
 * it needs to check the acknowledgement from the slave.
 * @warning Nil.
 * @param[in] : Data that needs to be written (can be either register address,
 * or register value).
 * @param[Out] NULL.
 */

void I2cWriteData(unsigned char write_data, unsigned long delay)
{
  SetSdaDirection(GPIOD_IS_OUT);
  printf("\n\tI2C: I2C Write\n");
  I2cWriteByte( writeData, delay);
  //	sda=1;
  write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SDA) );
  DelayLoop(delay, delay);

  printf("\n\tI2C: I2C Write Ack\n");
  SetSdaDirection(GPIOD_IS_IN);
  ReadAckForWrite(delay);

}

/** @fn static unsigned char I2cReadDataAck(unsigned long delay)
 * @brief Sends ack for the read byte.
 * @details The I2C controller (master) sends Ack to the slave so that it can 
 * make sure the data that slave can continue sending next data.
 * @warning Nil.
 * @param[in] delay.
 * @param[Out] returns the value of readData .
 */

unsigned char I2cReadDataAck(unsigned long delay)
{
  unsigned char readData = 0;
  SetSdaDirection(GPIOD_IS_IN);
	printf("\n\tI2C: I2C Read\n");
	readData = I2cReadByte(delay);
	SetSdaDirection(GPIOD_IS_OUT);
	printf("\n\tI2C: I2C Read Ack\n");
	SendAckForRead(delay);
  return readData;
}

/** @fn static unsigned char I2cReadDataNack(unsigned char delay)
 * @brief Reads a byte from the I2C device.
 * @details Whenever the master wants to read register or memory from a device,
 * the master can perform this action and respond with Nack to terminate the
 * transfer.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param[in] delay.
 * @param[Out] returns the value of readData .
 */

unsigned char I2cReadDataNack(unsigned char delay)
{
  unsigned char readData = 0;
  SetSdaDirection(GPIOD_IS_IN);
 	printf("\n\tI2C: I2C Read\n");
  readData = I2cReadByte(delay);
	SetSdaDirection(GPIOD_IS_OUT);
  	printf("\n\tI2C: I2C Read NAck\n");
  	SendNackForRead(delay);
    return readData;
}

/** @fn static void start(unsigned long delay)
 * @brief Sending start condition to start accessing the slave.
 * @details Start condition is making SDA low when clock is high.
 * @warning Nil
 * @param[in] delay.
 * @param[Out] No output parameters.
 */

void I2cStart(unsigned long delay)
{
  printf("\n\tI2C: I2C start\n");
  start(delay);
}

/** @fn static void stop(unsigned long delay)
 * @brief Sending stop condition for the I2C.
 * @details Stop condition is making SDA high when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param[in] delay.
 * @param[Out] No output parameters.
 */

void I2cStop(unsigned long delay)
{
  printf("\n\tI2C: I2C stop\n");
  stop(delay);
}

 /** @fn void I2c_Write_byte(unsigned char slave_address,unsigned char reg_address, unsigned char data, unsigned char delay )
 * @brief To write one byte of data into a particular register of a particular slave
 * @details: To make a complete one byte of data along with slave address, register offset can be done with this function. 
 * @warning: Nil
 * @param[in] slave address, register address, data to be written
 * @param[Out] none
 */

void I2c_Write_byte(unsigned char slave_address,unsigned char reg_address, unsigned char data, unsigned char delay )
{
	I2cSendSlaveAddress(slave_address, I2C_WRITE, delay);
	I2cWriteData(reg_address, delay);
	I2cWriteData(data,delay);
	I2cStop(delay);
}

 /** @fn int I2c_Read_byte(unsigned char slave_address,unsigned char reg_address, unsigned char delay)
 * @brief To read one byte of data from a particular register of a partivular slave
 * @details: To make a one complete I2C byte read operation along with slave address,
 *           register offset is done in this function.
 * @warning 
 * @param[in] slave address, register address
 * @param[Out] readdata
 */

int I2c_Read_byte(unsigned char slave_address,unsigned char reg_address, unsigned char delay)
{
	unsigned char readData;
	I2cSendSlaveAddress(slave_address, I2C_WRITE, delay);//selecting slave to be read
	I2cWriteData(reg_address, delay);//selecting register to be read
	I2cSendSlaveAddress(slave_address, I2C_READ, delay);
	readData = I2cReadDataAck(delay);
	I2cStop(delay);
	return (int) readData;
}

/** @fn int I2c_shakti_readbytes(char *buf, int count, int last, unsigned char delay)
 * @brief To burst read (i.e read multiple bytes byte of data)
 * @details: To write n bytes of data to slave assuming the slave address and register 
 *           offset are set.
 * @warning: Nil 
 * @param[in] readbuf to store read data, count to tell how many bytes to read , last
 * @param[Out] No. of values(bytes) read
 */
 
int I2c_shakti_readbytes(char *buf, int count, int last, unsigned char delay)
{
	printf("start reading the slave device\n");
	int i=0;
#ifdef PCF8584
	for(i=0;i<=count;i++)
	{
		if(i!=0 && i<count)
		{
			readbuf[i]=I2cReadDataAck(delay);

		}
		else if(i==0) I2cReadDataAck(delay);//dummy read
		else
		{
			readbuf[i] = I2cReadDataNack(delay);
		}
		/*The following loop is useful only  for eeprom*/
		if (last)  I2cStop(delay);
		else  I2cStart(delay);//sending repeated start
	}
	return i-1; //excluding the dummy read
#else
	for(i=0;i<count-1;i++)
		*(buf + i) = I2cReadDataAck(delay);
	*(buf + i) = I2cReadDataNack(delay);

	/*The following loop is useful only  for eeprom*/
	if (last)
		I2cStop(delay);
	else
		I2cStart(delay);//sending repeated start
#endif
	return i+1;
}
