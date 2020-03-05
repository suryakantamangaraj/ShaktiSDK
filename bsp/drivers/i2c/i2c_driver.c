/***************************************************************************
 * Project           			:  shakti devt board
 * Name of the file	     		:  i2c_driver.c
 * Created date			        :
 * Brief Description of file     :  Demonstartes the working of i2c protocol.
 */

/* Enable these bits only when corresponding interrupt is needed.*/

#include "i2c.h"//Includes the definitions of i2c communication protocol//
#include "log.h"
#include "utils.h"


/* Enable these bits only when corresponding interrupt is needed.*/

//#define USE_SA_WRITE_I2C_INTERRUPT 1
//#define USE_WRITE_I2C_INTERRUPT 1
//#define USE_READ_I2C_INTERRUPT 1

i2c_struct *i2c_instance[MAX_I2C_COUNT];

/**
 * @fn i2c_init()
 * @brief 
 * @details 
 * @warning 
 * @param[in] No input parameters.
 * @param[Out] 
 */

i2c_init()
{
	for(int i=0; i< MAX_I2C_COUNT; i++)
	{
		i2c_instance[i] = (i2c_struct*) (I2C0_BASE + (i * I2C_OFFSET));
	}
}

/** @fn static void init_i2c(unsigned char prescale_div, unsigned char
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

int config_i2c(i2c_struct * i2c_instance, unsigned char prescale_div, unsigned char scl_div)
{
	unsigned char temp = 0;
	log_debug("\tI2C: Initializing the Controller\n");

	if(prescale_div  != i2c_instance->prescale )
	{
		i2c_instance->prescale = prescale_div;
#ifdef DEBUG 
		temp = i2c_instance->prescale;

		if((temp | 0x00) != prescale_div)
		{
			log_error("\t Failed to write Prescale division Written Value: 0x%x; read Value: 0x%x\n", prescale_div, i2c_instance->prescale);
			return -ENXIO;
		}
		else
		{
			log_debug("\tPrescaler successfully initalized\n");
		}
#endif
	}

	if(scl_div != i2c_instance->scl )
	{
		i2c_instance->scl = scl_div;  //Setting the I2C clock value to be 1, which will set the clock for module and prescaler clock


#ifdef DEBUG 
		temp = i2c_instance->scl;

		/* Just reading the written value to see if all is well -- Compiler should not optimize this load!!! Compiler can just optimize the store to pointer address followed by load pointer to a register to just an immediate load to the register since clock register is not used anywhere -- but the purpose is lost. Don't give compiler optimizations */
		if((temp | 0x00) != scl_div)
		{
			log_error("\tClock initialization failed Write Value: 0x%x; read Value: 0x%x\n", scl_div, temp);
			return -ENXIO;
		}
		else
		{
			log_debug("\tClock successfully initalized\n");
		}
#endif
	}

	/* S1=0x80 S0 selected, serial interface off */
	log_debug("\tClearing the status register. \n");
	i2c_instance->control = I2C_PIN;

	// Reading set control Register Value to ensure sanctity
	log_debug("\tReading Status Register \n");
	temp = i2c_instance->control;

	//Check whether the status register is cleared or not.
	if((temp & 0x7f) != 0){
		log_error("\tDevice Not Recognized\n");
		return -ENXIO;
	}

	log_debug("\tWaiting for a specified time\n ");
	waitfor(900); //1 Second software wait -- Should be 900000 but setting to 900 now since simulation is already slow
	log_debug("\tDone Waiting \n ");
	log_info("\nControl: %x; Status: %x", i2c_instance->control, i2c_instance->status);
	/* Enable Serial Interface */
	i2c_instance->control = I2C_IDLE;
	waitfor(900); //1 Second software wait -- Should be 900000 but setting to 900 now since simulation is already slow

	temp = i2c_instance->status;

	/* Check to see if I2C is really in Idle and see if we can access the status register -- If not something wrong in initialization. This also verifies if Control is properly written since zero bit will be initialized to zero*/
	if(temp != (I2C_PIN | I2C_BB)){
		log_error("\n\tInitialization failed; Status Reg: %x\n", temp);
		return -ENXIO;
	}

	log_info("\tI2C Initialization success\n");
	return 0;
}


int wait_till_I2c_bus_free(i2c_struct * i2c_instance)
{
	log_debug("\tCheck for I2C Bus Busy to be free.\n");
	int timeout = DEF_TIMEOUT;
	int status;

	status = i2c_instance->status;

	while (!(status & I2C_BB) && --timeout) {
		waitfor(20000); /* wait for 100 us */
		status = i2c_instance->status;
	}

	if (timeout == 0) {
		log_error("\t Bus busy wait - timed out. Resetting\n");
		return ETIMEDOUT;
	}

	return 0;
}

int wait_till_txrx_operation_Completes(i2c_struct * i2c_instance, int *status)
{

	int timeout = DEF_TIMEOUT;

	*status = i2c_instance->status;

	while ((*status & I2C_PIN) && --timeout) {
		waitfor(10000); /* wait for 100 us */
		*status = i2c_instance->status;
	}

	if (timeout == 0){
		log_info("\tWait for pin timed out\n");
		return ETIMEDOUT;
	}
	log_debug("\n I2C tx_rx operation is completed");
	return 0;
}

int sendbytes(i2c_struct * i2c_instance, const char *buf, int count, int last, int eni)
{
	int wrcount, status, timeout;
	printf("\tStarting Write Transaction -- Did you create tri1 nets for SDA and SCL in verilog?\n");
	for (wrcount=0; wrcount<count; ++wrcount) {
		i2c_instance->data = buf[wrcount];
		timeout = wait_till_txrx_operation_Completes(i2c_instance, &status);
		if (timeout) {
			printf("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
			i2c_instance->control = I2C_STOP;
			return EREMOTEIO;
		}
		if (status & I2C_LRB) { // What error is this?
			i2c_instance->control = I2C_STOP;//~
			printf("\tSome status check failing\n");
			return EREMOTEIO;
		}
	}
	if (last){
		printf("\tLast byte sent : Issue a stop\n");
		i2c_instance->control = I2C_STOP;
	}
	else{
		printf("\tSending Rep Start and doing some other R/W transaction\n");

		if(!eni)
			i2c_instance->control = I2C_REPSTART;
		else
			i2c_instance->control = I2C_REPSTART_ENI;
	}

	return wrcount;
}

int readbytes(i2c_struct * i2c_instance, char *buf, int count, int last)
{
	int i, status;
	int wfp;
	int read_value = 0;


	/* increment number of bytes to read by one -- read dummy byte */
	for (i = 0; i <= count; i++) {
		wfp = wait_till_txrx_operation_Completes(i2c_instance, &status);
		if (wfp) {
			i2c_instance->control = I2C_STOP;
			return -1;
		}

		if ((status & I2C_LRB) && (i != count)) {
			i2c_instance->control = I2C_STOP;
			printf("\tNo ack\n");
			return -1;
		}

		if (i)
		{
			buf[i - 1] = i2c_instance->data;
			printf("\n Read Value: %x", buf[i - 1]);
		}
		else
			i2c_instance->data; /* dummy read */

		if (i == count - 1) {
			i2c_instance->control = I2C_ESO;
		} else if (i == count) {
			if (last)
				i2c_instance->control = I2C_STOP;
			else
				i2c_instance->control = I2C_REPSTART_ENI;
		}

	}

	return i-1; //excluding the dummy read
}


/************************************************************************
 * Brief Description     : Performs the intilization of i2c slave.
 * Parameters            : slave address.
 * Return                : int.
 *************************************************************************/

int i2c_send_slave_address(i2c_struct * i2c_instance, unsigned char slaveAddress, unsigned char rdWrCntrl, unsigned long delay)
{
	int timeout;
	unsigned char temp = 0;
	int status = 0;
	if(rdWrCntrl == 0)
		slaveAddress |= I2C_WRITE;
	else
		slaveAddress |= I2C_READ;
	log_debug("\n\tSetting Slave Address : 0x%x\n", slaveAddress);/* Writes the slave address to I2C controller */
	//Writing the slave address that needs to be written into data register.
	i2c_instance->data = slaveAddress;
	log_debug("\tSlave Address is written into data register\n");

	//Reads back the data register to confirm
	temp = i2c_instance->data; //Reads the slave address from I2C controller
	log_debug("\tSet slave address read again, which is 0x%x\n",temp);
	if(slaveAddress != (int)temp)
	{
		log_error("\tSlave address is not matching; Written Add. Value: 0x%x; Read Add. Value: 0x%x\n", slaveAddress, temp);
		log_error("\n There is some issue in AXI interface. Please check.");
		return EAXI_ERROR;
	}

	//Waits till the bus becomes free.
	while(wait_till_I2c_bus_free(i2c_instance))
	{
		log_error("\tError in Waiting for BB\n");
		return EI2C_BUS_ERROR;
	}


	//Send the start condition and slave address to slave
#ifndef USE_SA_WRITE_I2C_INTERRUPT
	i2c_instance->control = I2C_START; //Sending the slave address to the I2C slave
	waitfor(90000);
	//Wait for PIN to become low.
	timeout = wait_till_txrx_operation_Completes(i2c_instance, &status);
	if (timeout) {//Asking the controller to send a start signal to initiate the transaction
		printf("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
		i2c_instance->control = I2C_STOP; //~
		return EI2C_PIN_ERROR;
	}

	if (status & I2C_LRB) {
		i2c_instance->control = I2C_STOP; //~
		printf("\tSome status check failing\n");
		return EI2C_LRB_ERROR;
	}

#else
	i2c_complete_flag = 0;

	i2c_instance->control = I2C_START_ENI; //Sending the slave address to the I2C slave
	while(!i2c_complete_flag);
	log_info("\n Slave Address Write Operation is complete.");
	i2c_complete_flag = 0;
#endif
	log_debug("\n Slave address is written successfully");
	return I2C_SUCCESS;
}

/************************************************************************
 * Brief Description     : It does the reading or writing from the address specified .
 * Parameters            : starting address.
 * Return                : int.
 *************************************************************************/

int i2c_write_data(i2c_struct * i2c_instance, unsigned char writeData, unsigned char delay)
{
	int timeout;
	int status = 0;


	i2c_instance->data= writeData;
#ifndef USE_WRITE_I2C_INTERRUPT
	timeout = wait_till_txrx_operation_Completes(i2c_instance, &status);
	if (timeout) {
		printf("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
		i2c_instance->control = I2C_STOP; //~
		return EREMOTEIO;
	}

	if (status & I2C_LRB)
	{ // What error is this?
		i2c_instance->control = I2C_STOP; //~
		printf("\tSome status check failing\n");
		return EI2C_LRB_ERROR;
	}
#else
	i2c_complete_flag = 0;
	i2c_instance->control = I2C_STOP_ENI; //Sending the sslave address to the I2C slave

	while(!i2c_complete_flag);
	log_info("\n Write Operation is complete.");
	i2c_complete_flag = 0;
#endif

	return I2C_SUCCESS;
}




/************************************************************************
 * Brief Description     : It does the reading or writing from the address specified .
 * Parameters            : starting address.
 * Return                : int.
 *************************************************************************/
//#define READ_INTERRUPT 1
int i2c_read_data(i2c_struct * i2c_instance, unsigned char *read_data, unsigned char delay)
{
	int timeout;
	int status = 0;

	/* Make a dummy read as per spec of the I2C controller */

	*read_data = i2c_instance->data; //~

#ifdef USE_WRITE_I2C_INTERRUPT	
	i2c_complete_flag = 0;
	i2c_instance->control = I2C_REPSTART_ENI; //~
	while(!i2c_complete_flag);
	*read_data = i2c_instance->data;
	printf("\n I2C Read Data = %x", i2c_read_data);
#else
	while(wait_till_txrx_operation_Completes(i2c_instance, &status))
	{
		printf("\twaiting for pin\n");
		waitfor(delay);
	}
#endif
	return I2C_SUCCESS;
}

/************************************************************************
 * Brief Description     : Performs the intilization of i2c slave.
 * Parameters            : slave address.
 * Return                : int.
 *************************************************************************/

int i2c_send_interrupt_slave_address(i2c_struct * i2c_instance, unsigned char slaveAddress, unsigned char rdWrCntrl, unsigned long delay)
{
	int timeout;
	unsigned char temp = 0;
	int status = 0;
	if(rdWrCntrl == 0)
		slaveAddress |= I2C_WRITE;
	else
		slaveAddress |= I2C_READ;
	log_debug("\n\tSetting Slave Address : 0x%x\n", slaveAddress);/* Writes the slave address to I2C controller */
	//Writing the slave address that needs to be written into data register.
	i2c_instance->data = slaveAddress;
	log_debug("\tSlave Address is written into data register\n");

	//Reads back the data register to confirm
	temp = i2c_instance->data; //Reads the slave address from I2C controller
	log_debug("\tSet slave address read again, which is 0x%x\n",temp);
	if(slaveAddress != (int)temp)
	{
		log_error("\tSlave address is not matching; Written Add. Value: 0x%x; Read Add. Value: 0x%x\n", slaveAddress, temp);
		log_error("\n There is some issue in AXI interface. Please check.");
		return EAXI_ERROR;
	}

	//Waits till the bus becomes free.
	while(wait_till_I2c_bus_free(i2c_instance))
	{
		log_error("\tError in Waiting for BB\n");
		return EI2C_BUS_ERROR;
	}


	//Send the start condition and slave address to slave
#ifndef USE_SA_WRITE_I2C_INTERRUPT
	i2c_instance->control = I2C_START;; //Sending the slave address to the I2C slave
	//Wait for PIN to become low.
	timeout = wait_till_txrx_operation_Completes(i2c_instance, &status);
	if (timeout) {//Asking the controller to send a start signal to initiate the transaction
		printf("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
		i2c_instance->control = I2C_STOP; //~
		return EI2C_PIN_ERROR;
	}

	if (status & I2C_LRB) {
		i2c_instance->control = I2C_STOP; //~
		printf("\tSome status check failing\n");
		return EI2C_LRB_ERROR;
	}
#else
	i2c_complete_flag = 0;
	i2c_instance->control = I2C_REPSTART_ENI; //Sending the slave address to the I2C slave
	while(!i2c_complete_flag);
	log_info("\n Slave Address Write Operation is complete.");
	i2c_complete_flag = 0;
#endif
	log_info("\n Slave address is written successfully");
	return I2C_SUCCESS;
}



int i2c_read_interrupt_data(i2c_struct * i2c_instance, unsigned char *read_data, unsigned char delay, 
		unsigned char last)
{
	int timeout;
	int status = 0;

	/* Make a dummy read as per spec of the I2C controller */
	*read_data = i2c_instance->data;
	;
#ifdef USE_READ_I2C_INTERRUPT	
	i2c_complete_flag = 0;
	if(last)
	{
		i2c_instance->control = I2C_STOP_ENI; //~
		while(!i2c_complete_flag);
	}
	else
	{
		/* Needs to be tested */
		//			i2c_instance->control = I2C_REPSTART_ENI;
		//			printf("\n Call I2C rep. start eni");
		//			while(!i2c_complete_flag);
	}
	printf("\n I2C Read Data = %x", *read_data);
#else
	while(wait_till_txrx_operation_Completes(i2c_instance, &status))
	{
		printf("\twaiting for pin\n");
		waitfor(delay);
	}
	if(!last)
	{
		printf("\n Rep Start");				
		//				i2c_instance->control = I2C_REPSTART;
	}
	else
	{
		printf("\nCall I2C Stop");
		i2c_instance->control = I2C_STOP;
	}
#endif
	return I2C_SUCCESS;
}


int i2c_write_interrupt_data(i2c_struct * i2c_instance, unsigned char writeData, unsigned char delay, unsigned char last)
{
	int timeout;
	int status = 0;

	i2c_instance->data = writeData;
#ifndef USE_WRITE_I2C_INTERRUPT
	timeout = wait_till_txrx_operation_Completes(i2c_instance, &status);
	if (timeout) {
		printf("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
		i2c_instance->control = I2C_STOP; //~
		return EREMOTEIO;
	}

	if (status & I2C_LRB)
	{ // What error is this?
		i2c_instance->control = I2C_STOP;//~
		printf("\tSome status check failing\n");
		return EI2C_LRB_ERROR;
	}
	if(1 == last)
	{
		i2c_instance->control = I2C_STOP;;
		printf("\tI2C Write Success and completes\n");
	}
#else
	i2c_complete_flag = 0;
	if(last)
	{
		i2c_instance->control = I2C_STOP_ENI; //Sending the sslave address to the I2C slave
		printf("\n Calling stop eni write");
		while(!i2c_complete_flag);
	}
	else
	{
		//			i2c_instance->control = I2C_REPSTART_ENI;
		//			printf("\n Calling repstart eni write");
		//		while(!i2c_complete_flag);
	}
	log_info("\n Write Operation is complete.");
	i2c_complete_flag = 0;
#endif

	return I2C_SUCCESS;
}

