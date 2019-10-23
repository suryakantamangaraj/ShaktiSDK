/***************************************************************************
* Project                               :  shakti devt board
* Name of the file                      :  spi_driver.c
* Brief Description of file             :  Driver to control the spi device.
* Name of Author                        :  Kaustubh Ghormade
* Email ID                              :  kaustubh4347@gmail.com

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

#include "spi.h"

int* spi_cr1    = (int*) SPI_CR1;
int* spi_cr2    = (int*) SPI_CR2;
int* spi_sr     = (int*) SPI_SR ;
int* spi_dr1    = (int*) SPI_DR1 ;
int* spi_dr2    = (int*) SPI_DR2 ;
int* spi_dr3    = (int*) SPI_DR3 ;
int* spi_dr4    = (int*) SPI_DR4 ;
int* spi_dr5    = (int*) SPI_DR5 ;
int* spi_crcpr  = (int*) SPI_CRCPR;
int* spi_rxcrcr = (int*) SPI_RXCRCR;
int* spi_txcrcr = (int*) SPI_TXCRCR; 


/** @fn set_spi
 * @brief to assign value to memory mapped spi register
 * @details 
 * @warning 
 * @param[in] int
 * @param[Out] No output parameter 
 */
void set_spi(int* addr, int val)
{
	*addr = val;
}

/** @fn get_spi
 * @brief to get vlue for memory mapped spi register
 * @details 
 * @warning 
 * @param[in] int 
 * @param[Out] int
 */
int get_spi(int* addr)
{
	return *addr;
}

/** @fn spi_init
 * @brief setting up baud rate and clock pole and phase 
 * @details 
 * @warning 
 * @param[in] No input parameter
 * @param[Out] No output parameter
 */
void spi_init()
{
	set_spi(spi_cr1, (SPI_BR(7)|SPI_CPHA|SPI_CPOL));
}

/** @fn spi_tx_rx_start
 * @brief to start receiving data as soon as transmit state is complete
 * @details 
 * @warning 
 * @param[in] No input parameters
 * @param[Out] No output parameters
 */
void spi_tx_rx_start()
{
	set_spi(spi_cr2, (SPI_RX_IMM_START));
}

/** @fn spi_enable
 * @brief 
 * @details 
 * @warning 
 * @param[in] No input parameter
 * @param[Out] No output parameter
 */
void spi_enable()
{
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(4)|SPI_TOTAL_BITS_RX(16)|SPI_SPE));
}

/** @fn spi_rx_enable
 * @brief to start receive state 
 * @details 
 * @warning 
 * @param[in] No input parameter
 * @param[Out] No output parameter
 */
void spi_rx_enable()
{
	set_spi(spi_cr2, (SPI_RX_START));
}

/** @fn bitExtracted
 * @brief Extract the k number of bit from (p-1) position of 'number'
 * @details 
 * @warning 
 * @param[in] int
 * @param[Out] int
 */

int bitExtracted(int number, int k, int p) 
{
	return (((1 << k) - 1) & (number >> (p - 1))); 
}

/** @fn concat
 * @brief concatenate two intergers
 * @details 
 * @warning 
 * @param[in] int
 * @param[Out] int
 */

int concat(int x, int y) 
{
	unsigned pow = 10;

	while (y >= pow)
		pow *= 10;

	return x * pow + y;
}

/** @fn spi_rxne_enable
 * @brief to check if receive buffer is empty or not
 * @details As soons as data come to receive buffer this bit is set.  
 * @warning 
 * @param[in] No input parameter
 * @param[Out] int
 */

int spi_rxne_enable()
{
	int value = 0;

	while (!(value & 0x1))
	{
		waitfor(100);
		value = get_spi(spi_sr);
	}
	return 1;
}

/** @fn spi_notbusy
 * @brief to check if spi is ready for next transaction or busy with previous one
 * @details it read the status of bsy bit in spi_sr 
 * @warning 
 * @param[in] No input parameter
 * @param[Out] int
 */

int spi_notbusy()
{
	int value = 0x80;

	while ((value & 0x80))
	{
		waitfor(10);
		value = get_spi(spi_sr);
	}

	return 1;
}

/** @fn bin
 * @brief 
 * @details 
 * @warning 
 * @param[in] unsigned int
 * @param[Out] No output parameter
 */

void bin(unsigned n)
{ 
	unsigned i;

	for (i = 1 << 31; i > 0; i = i / 2) 
		(n & i)? printf("1"): printf("0"); 
} 

/** @fn  waitfor
 * @brief satllt the process fro given time
 * @details 
 * @warning 
 * @param[in] unsigned int
 * @param[Out] No output parameter
 */

void waitfor(unsigned int secs) 
{
	unsigned int time = 0;
	while (time++ < secs);
}

/** @fn flash_write_enable
 * @brief to set the WEL (Write Enable Latch) bit in status register
 * @details Before modifying content of flash, one should enable the WEL bit first
 * @warning Without enabling this bit one cannot erase/write into the flash
 * @param[in] No input parameter
 * @param[Out] int
 */

int flash_write_enable()
{
	set_spi(spi_dr1, 0x06000000);
	set_spi(spi_dr5, 0x06);
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(8)|SPI_TOTAL_BITS_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	spi_notbusy();
	return 1;
}

/** @fn flash_clear_sr
 * @brief to reset the status register
 * @details 
 * @warning 
 * @param[in] No input parameter
 * @param[Out] int
 */

int flash_clear_sr()
{
	set_spi(spi_dr1,0x30000000);
	set_spi(spi_dr5,0x30);
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(8)|SPI_TOTAL_BITS_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	spi_notbusy();

	return 1;
}

/** @fn flash_cmd_addr
 * @brief Use for sending 8bit of command + 32 bit of address 
 * @details Useful for function like erase
 * @warning to move data drom dr register to fifo there must be some data into spi_dr5 
 * @param[in] int
 * @param[Out] int
 */

int flash_cmd_addr(int command, int addr)
{
	int address1 = bitExtracted(addr, 24, 9);
	int address2 = bitExtracted(addr, 8, 1);
	int data1 = command | address1 ;

	address2 = address2 << 24;
	printf("Erase dr1 \n");
	bin(data1);
	printf("\n");
	set_spi(spi_dr1, data1);
	set_spi(spi_dr2, address2);
	set_spi(spi_dr5, 0);
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(40)|SPI_TOTAL_BITS_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	waitfor(20);
	spi_notbusy();

	return 1;
}

/** @fn flash_cmd_addr_data
 * @brief use for sending 8bit command +32bit of write address + 32 bit of write data
 * @details useful for function like Write
 * @warning to move data from data register to fifo there must be some data into spi_dr5g 
 * @param[in] int
 * @param[Out] No output parameter 
 */

void flash_cmd_addr_data(int command, int addr, int data)
{
	int address1 = bitExtracted(addr, 24, 9);
	int address2 = bitExtracted(addr, 8, 1);
	int cmd_addr = command  | address1;
	address2 = address2 << 24;
	int data1 = bitExtracted(data, 24, 9);
	data1 = address2 | data1;
	int data2 = bitExtracted(data, 8, 1);
	data2 = data2 << 24;
	set_spi(spi_dr1, cmd_addr);
	set_spi(spi_dr2, data1);
	set_spi(spi_dr3, data2);
	set_spi(spi_dr5, 0);
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(72)|SPI_TOTAL_BITS_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	waitfor(20);
	spi_notbusy();
}

/** @fn flash_write
 * @brief  Write 4bytes of data from given address
 * @details 
 * @warning before writing into the flash one should enable the WEL bit spi_sr
 * @param[in] int
 * @param[Out] No output parameter 
 */

void flash_write(int address, int data)
{
	flash_cmd_addr_data(0x12000000, address,data);
}

/** @fn flash_cmd_to_read
* @briefUse for sending command of 8bit + read address of 32bit + 8bit of dummy cycle and receive 32bit value from flash 
 * @details useful for function like read
 * @warning As receive shoild start as soon as transmit state end, use spi_rx_tx_start() befor setting control register 1
 * @param[in] int
 * @param[Out] int
 */

int flash_cmd_to_read(int command, int addr)
{
	int dr5;
	int address1 = bitExtracted(addr, 24, 9);
	int address2 = bitExtracted(addr, 8, 1);
	int cmd_addr = command  | address1;
	address2 = address2 << 24;
	set_spi(spi_dr1, cmd_addr);
	set_spi(spi_dr2, address2);
	set_spi(spi_dr5, 0);
	spi_tx_rx_start();
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(48)|SPI_TOTAL_BITS_RX(32)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	waitfor(20);

	if(spi_rxne_enable()) 
	{
		dr5 = *spi_dr5;
	}

	return dr5;

}

/** @fn flash_read
 * @brief read the 4bytes data from given address 
 * @details 
 * @warning 
 * @param[in] int
 * @param[Out] int
 */

int flash_read(int address)
{
	int read_value = flash_cmd_to_read(0x0C000000,address);
	return read_value;
}

/** @fn flash_cmd_read
 * @brief use for sending 8bit command and receive the 32bit of data
 * @details usefull for reading status register
 * @warning 
 * @param[in] int
 * @param[Out] int
 */

int flash_cmd_read(int command)
{
	int dr1, dr2, dr5;
	set_spi(spi_dr1, command);
	set_spi(spi_dr5, command);
	spi_tx_rx_start();
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(8)|SPI_TOTAL_BITS_RX(32)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	if(spi_rxne_enable()) {
		dr5 = *spi_dr5;
		dr2 = *spi_dr2;
	}
	return dr5;
}

/** @fn flash_erase
 * @brief Erase the 64kb sector from given address
 * @details 
 * @warning 
 * @param[in] int
 * @param[Out] No output parameter
 */

void flash_erase(int address)
{
	printf("Cypress erase \n");
	flash_cmd_addr(0xdc000000, address);
	printf("Cypress erase done\n");
}

/** @fn flash_status_register_read
 * @briefRead read status register of flash
 * @details It is useful used to check status of WIP(Write in progress) and WEL(Write Enable Latch) bit 
 * @warning 
 * @param[in] No input parameter
 * @param[Out] int
 */

int flash_status_register_read()
{
	int stat = 0x3;

	while (stat & 0x03)
	{
		stat = flash_cmd_read(0x05000000);
		//printf("flash status register val %x\n", stat);
	}

	return 0;
}

/** @fn flash_device_id
 * @briefto read Device ID and Mfg. ID of flash
 * @details 
 * @warning to move data from data register to fifo there must be some data into spi_dr5
 * @param[in] No input parameter
 * @param[Out] int
 */

int flash_device_id()
{
	int dr1, dr2, dr3;
	int val1, val2;
	flash_write_enable();
	set_spi(spi_dr1, 0x9f000000);
	set_spi(spi_dr5, 0x9f000000);
	spi_tx_rx_start();
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(8)|SPI_TOTAL_BITS_RX(24)|SPI_SPE|SPI_CPHA|SPI_CPOL));

	if(spi_rxne_enable())
	{
		dr3 = *spi_dr5;
		dr2 = *spi_dr2;
	}

	val1 = bitExtracted(dr3, 8, 17);
	val2 = bitExtracted(dr3, 16, 1);
	dr1 = concat(val2, val1);

	printf("Device ID %x \n", val1);
	printf("extracted device id %x \n",val2);

	return 1;	
}
