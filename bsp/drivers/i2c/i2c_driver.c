// SPDX-License-Identifier: GPL-2.0-or-later
/*
 *
 *   Copyright (C) 1995-1997 Simon G. Vogl
 *		   1998-2000 Hans Berglund
 *
 * With some changes from Kyösti Mälkki <kmalkki@cc.hut.fi> and
 * Frodo Looijaard <frodol@dds.nl>, and also from Martin Bailey
 * <mbailey@littlefeet-inc.com>
 *
 * Partially rewriten by Oleg I. Vdovikin <vdovikin@jscc.ru> to handle multiple
 * messages, proper stop/repstart signaling during receive, added detect code
 *
 * Partially rewritten by Vinod <g.vinod1993@gmail.com> and Kotteeswaran <kottee.1@gmail.com> for shakti i2c
 *
 *  i2c-algo-pcf.c i2c driver algorithms for PCF8584 adapters was modified to this file.
 */

/***************************************************************************
* Project           			:  shakti devt board
* Name of the file	     		:  i2c_driver.c
* Created date			        :
* Brief Description of file     :  Demonstartes the working of i2c protocol.
*/
#define I2C_DRV
#include "i2c.h"//Includes the definitions of i2c communication protocol//
#include "log.h"
#include "utils.h"

/** @fn static void get_i2c_shakti(unsigned char delay)
 * @brief Reads  into any of the shakti io locations (Here mainly I2C).
 *
 * @details There are 5 registers which are configurable. This function
 *  reads into the register based on the passed address.
 *
 * @warning Nil.
 *
 * @param[in] address from where data needs to be read.
 * @param[Out] Data read from the passed address.
 */
char get_i2c_shakti(char *addr)
{
#ifdef ASM
	char val;
	log_debug("\n The address is %p;", (char *) addr);
	asm volatile("lb %0, 0(%1)" : "=r" (val) : "r" (*addr));
	return val;
#else
//	printf("\nRead: Address: %x; Value: %x", addr, *addr);
  return *addr;
#endif
}

/** @fn static void set_i2c_shakti(unsigned char delay)
 * @brief Writes into any of the shakti io locations (Here mainly I2C).
 *
 * @details There are 4 registers which are configurable. This function
 *  writes into the register based on the passed address.
 *
 * @warning Nil.
 *
 * @param[in] address at which data needs to be written, data .
 * @param[Out] No output parameters.
 */
void set_i2c_shakti(int *addr, int val)
{
#ifdef ASM
	log_info("\n The address is %p; value: %x", (char *) addr, val);
	asm volatile("sb %0, 0(%1)" : : "r" (val), "r" (*addr));
#else
    *addr = val;
//		printf("\nWrite: Address: %x; Value: %x", addr, *addr);
#endif
}

void i2c_start()
{
	set_i2c_shakti(i2c_control, I2C_SHAKTI_START);
}

void i2c_start_eni()
{
	set_i2c_shakti(i2c_control, I2C_SHAKTI_START);
}

void i2c_repstart()
{
	set_i2c_shakti(i2c_control, I2C_SHAKTI_REPSTART);
}

void i2c_repstart_eni()
{
	set_i2c_shakti(i2c_control, I2C_SHAKTI_REPSTART);
}

void i2c_stop()
{
	set_i2c_shakti(i2c_control, I2C_SHAKTI_STOP);
}


void i2c_nack()
{
	set_i2c_shakti(i2c_control, I2C_SHAKTI_NACK);
}

void i2c_idle()
{
	set_i2c_shakti(i2c_control, I2C_SHAKTI_IDLE);
}

/** @fn static void shakti_init_i2c(unsigned char prescale_div, unsigned char
 *             scl_div)
 * @brief This routine configures the serial clock frequency count and
 * prescaler count.
 *
 * @details There are 4 registers which are configurable. This function
 *  writes into the register based on the passed address. he serial clock count
 *  and prescalar count decides the frequency (sck) that needs to be used for
 *  the I2C serial communication. Then resets status register.
 *
 * @warning Nil.
 *
 * @param[in] prescale_div, scl_div.
 * @param[Out] No output parameters.
 */
 int shakti_init_i2c(unsigned char prescale_div, unsigned char scl_div)
{
   unsigned char temp = 0;
    log_debug("\tI2C: Initializing the Controller\n");

    /* Doing an initialization sequence as how PCF8584 was supposed to be initialized                                                       */
    /* The Initialization Sequence is as follows                                                                                            */
    /* Reset Minimum 30 Clock Cycles -- Not necessary in our case                                                                           */
    /* Load Byte 80H into Control                                                                                                           */
    /* load Clock Register S2 */ /* We are doing the opposite -- Setting the clock and then the registers -- Doesn't really matter actually */
    /* Send C1H to S1 - Set I2C to Idle mode -- SDA and SCL should be high                                                                  */
		if(prescale_div  != get_i2c_shakti(i2c_prescale) )
		{
	    set_i2c_shakti(i2c_prescale, prescale_div);  //Setting the I2C clock value to be 1, which will set the clock for module and prescaler clock
	    temp = get_i2c_shakti(i2c_prescale);
			/* Just reading the written value to see if all is well -- Compiler should not optimize this load!!! Compiler can just optimize the store to pointer address followed by load pointer to a register to just an immediate load to the register since clock register is not used anywhere -- but the purpose is lost. Don't give compiler optimizations */
			    if((temp | 0x00) != prescale_div)
					{
			        log_error("\t Failed to write Prescale division Written Value: 0x%02x; read Value: 0x%02x\n", prescale_div, temp);
			        return -ENXIO;
			    }
			    else
					{
			        log_debug("\tPrescaler successfully initalized\n");
			    }
			}

		if(scl_div != get_i2c_shakti(i2c_scl) )
		{
	    set_i2c_shakti(i2c_scl, scl_div);  //Setting the I2C clock value to be 1, which will set the clock for module and prescaler clock
	    temp = get_i2c_shakti(i2c_scl);

	/* Just reading the written value to see if all is well -- Compiler should not optimize this load!!! Compiler can just optimize the store to pointer address followed by load pointer to a register to just an immediate load to the register since clock register is not used anywhere -- but the purpose is lost. Don't give compiler optimizations */
	    if((temp | 0x00) != scl_div){
	        log_error("\tClock initialization failed Write Value: 0x%02x; read Value: 0x%02x\n", scl_div, temp);
	        return -ENXIO;
	    }
	    else{
	        log_debug("\tClock successfully initalized\n");
	    }
		}


    /* S1=0x80 S0 selected, serial interface off */
    log_debug("\tClearing the status register. \n");
		set_i2c_shakti(i2c_control, I2C_SHAKTI_PIN);

    // Reading set control Register Value to ensure sanctity
    log_debug("\tReading Status Register \n");
    temp = get_i2c_shakti(i2c_control);

//Check whether the status register is cleared or not.
    if((temp & 0x7f) != 0){
        log_error("\tDevice Not Recognized\n");
        return -ENXIO;
    }

    log_debug("\tWaiting for a specified time\n ");
    waitfor(900); //1 Second software wait -- Should be 900000 but setting to 900 now since simulation is already slow
    log_debug("\tDone Waiting \n ");
	log_info("\nControl: %02x; Status: %02x", get_i2c_shakti(i2c_control), get_i2c_shakti(i2c_status));
    /* Enable Serial Interface */
    set_i2c_shakti(i2c_control, I2C_SHAKTI_IDLE);
    waitfor(900); //1 Second software wait -- Should be 900000 but setting to 900 now since simulation is already slow

#if 1
    temp = get_i2c_shakti(i2c_status);
//    printf("\tStatus Reg value after sending I2C_SHAKTI_IDLE is : 0x%x \n",temp);

    /* Check to see if I2C is really in Idle and see if we can access the status register -- If not something wrong in initialization. This also verifies if Control is properly written since zero bit will be initialized to zero*/
    if(temp != (I2C_SHAKTI_PIN | I2C_SHAKTI_BB)){
        log_error("\n\tInitialization failed; Status Reg: %02x\n", temp);
        return -ENXIO;
    }
    else
        log_debug("\tAll is well till here \n");
#endif
    log_info("\tI2C Initialization success\n");
		return 0;
}

int wait_till_I2c_bus_free()
{
  log_debug("\tCheck for I2C Bus Busy to be free.\n");
	int timeout = DEF_TIMEOUT;
	int status;

	status = get_i2c_shakti(i2c_status);

	while (!(status & I2C_SHAKTI_BB) && --timeout) {
		waitfor(20000); /* wait for 100 us */
		status = get_i2c_shakti(i2c_status);
	}

	if (timeout == 0) {
        log_error("\t Bus busy wait - timed out. Resetting\n");
		return ETIMEDOUT;
	}

	return 0;
}

int wait_till_txrx_operation_Completes(int *status)
{

	int timeout = DEF_TIMEOUT;

	*status = get_i2c_shakti(i2c_status);

	while ((*status & I2C_SHAKTI_PIN) && --timeout) {
		waitfor(10000); /* wait for 100 us */
		*status = get_i2c_shakti(i2c_status);
	}

	if (timeout == 0){
        log_info("\tWait for pin timed out\n");
		return ETIMEDOUT;
    }
	log_debug("\n I2C tx_rx operation is completed");
	return 0;
}

int shakti_sendbytes( const char *buf, int count, int last, int eni)
{
	int wrcount, status, timeout;
    printf("\tStarting Write Transaction -- Did you create tri1 nets for SDA and SCL in verilog?\n");
	for (wrcount=0; wrcount<count; ++wrcount) {
		set_i2c_shakti(i2c_data,buf[wrcount]);
		timeout = wait_till_txrx_operation_Completes(&status);
		if (timeout) {
            printf("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
						i2c_stop();
						return EREMOTEIO;
		}
		if (status & I2C_SHAKTI_LRB) { // What error is this?
			i2c_stop();//~
            printf("\tSome status check failing\n");
			return EREMOTEIO;
		}
	}
	if (last){
        printf("\tLast byte sent : Issue a stop\n");
		i2c_stop();
    }
	else{
        printf("\tSending Rep Start and doing some other R/W transaction\n");
		if(!eni)
            i2c_repstart();
        else
            i2c_repstart_eni();
    }

	return wrcount;
}

//#ifdef DEBUG
int shakti_readbytes(char *buf, int count, int last)
{
	int i, status;
	int wfp;
    int read_value = 0;
	/* increment number of bytes to read by one -- read dummy byte */
	for (i = 0; i <= count; i++) {
        wfp = wait_till_txrx_operation_Completes(&status);
		if (wfp) {
			i2c_stop();
            return -1;
		}

		if ((status & I2C_SHAKTI_LRB) && (i != count)) {
			i2c_stop();
			printf("\tNo ack\n");
			return -1;
		}

        if (i)
	{
		buf[i - 1] = get_i2c_shakti(i2c_data);
		printf("\n Read Value: %x", buf[i - 1]);
	}
		else
			get_i2c_shakti(i2c_data); /* dummy read */

		if (i == count - 1) {
			set_i2c_shakti(i2c_control, I2C_SHAKTI_ESO);
		} else if (i == count) {
			if (last)
				i2c_stop();
			else
				i2c_repstart();
		}

		}

	return i-1; //excluding the dummy read
}
//#endif


/************************************************************************
* Brief Description     : Performs the intilization of i2c slave.
* Parameters            : slave address.
* Return                : int.
*************************************************************************/

int i2c_send_slave_address(unsigned char slaveAddress, unsigned char rdWrCntrl, unsigned long delay)
{
	int timeout;
	unsigned char temp = 0;
	int status = 0;
	if(rdWrCntrl == 0)
		slaveAddress |= I2C_WRITE;
	else
		slaveAddress |= I2C_READ;
	log_debug("\n\tSetting Slave Address : 0x%02x\n", slaveAddress);/* Writes the slave address to I2C controller */
//Writing the slave address that needs to be written into data register.
	set_i2c_shakti(i2c_data, slaveAddress);
	log_debug("\tSlave Address is written into data register\n");

//Reads back the data register to confirm
	temp = get_i2c_shakti(i2c_data); //Reads the slave address from I2C controller
	log_debug("\tSet slave address read again, which is 0x%x\n",temp);
	if(slaveAddress != (int)temp)
	{
		log_error("\tSlave address is not matching; Written Add. Value: 0x%02x; Read Add. Value: 0x%02x\n", slaveAddress, temp);
		log_error("\n There is some issue in AXI interface. Please check.");
		return EAXI_ERROR;
	}

		//Waits till the bus becomes free.
			while(wait_till_I2c_bus_free())
			{
			 log_error("\tError in Waiting for BB\n");
			 return EI2C_BUS_ERROR;
			}


//Send the start condition and slave address to slave
	i2c_start(); //Sending the slave address to the I2C slave

//Wait for PIN to become low.
	timeout = wait_till_txrx_operation_Completes(&status);
	if (timeout) {//Asking the controller to send a start signal to initiate the transaction
		printf("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
		i2c_stop(); //~
		return EI2C_PIN_ERROR;
	}

	if (status & I2C_SHAKTI_LRB) {
	    i2c_stop();
		printf("\tSome status check failing\n");
		return EI2C_LRB_ERROR;
	}
//	i2c_stop();
//	delay_loop(delay, delay);
#ifdef DEBUG_PRINT
	printf("\n Slave address is written successfully");
#endif
	return I2C_SUCCESS;
}

/************************************************************************
* Brief Description     : It does the reading or writing from the address specified .
* Parameters            : starting address.
* Return                : int.
*************************************************************************/

int i2c_write_data(unsigned char writeData, unsigned char delay)
{
	int timeout;
	int status = 0;

	set_i2c_shakti(i2c_data, writeData);
	timeout = wait_till_txrx_operation_Completes(&status);
	if (timeout) {
		printf("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
		i2c_stop(); //~
		return EREMOTEIO;
	}

	if (status & I2C_SHAKTI_LRB)
	{ // What error is this?
		i2c_stop();//~
		printf("\tSome status check failing\n");
		return EI2C_LRB_ERROR;
	}
	return I2C_SUCCESS;
}


/************************************************************************
* Brief Description     : It does the reading or writing from the address specified .
* Parameters            : starting address.
* Return                : int.
*************************************************************************/

int i2c_read_data(unsigned char *read_data, unsigned char delay)
{
	int timeout;
	int status = 0;

	/* Make a dummy read as per spec of the I2C controller */
			*read_data = get_i2c_shakti(i2c_data);
			while(wait_till_txrx_operation_Completes(&status))
				{
						printf("\twaiting for pin\n");
						waitfor(delay);
				}
				return I2C_SUCCESS;
}
