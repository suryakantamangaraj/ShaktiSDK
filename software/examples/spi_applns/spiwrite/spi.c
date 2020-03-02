#include <stdint.h>
#include "spi.h"

/** @fn main
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
void main()
{
	int write_address = 0x00b00000;  // read/write from/to this address
	int data = 0xDEADBEEF; //32 bits of data can be written at a time
	
    configure_spi(SPI1_OFFSET);
	spi_init();
	
	printf("SPI init done\n");

	flash_device_id(); 

	waitfor(200);

	flash_write_enable();
	flash_erase(0x00b00000); //erases an entire sector
	flash_status_register_read();

	//flash write
	flash_write_enable();
	flash_write( write_address,data);
	printf("Flash write done on address %x and data %x \n", 
	       write_address, data);

	asm volatile ("ebreak");
} 

