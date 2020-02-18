/*****************************
***This file contains the UART FUNCTIONS TO SEND AND RECIEVE DATA FOR GATEWAY INTERFACING.
****************************/

#define UART0_BASE_ADDRESS 0x11200
#define UART_LINE_STATUS_REGISTER 5
#define UART1 1
#define UART1_BASE_ADDRESS 0x11300


void Delay(uint16_t Cnt1, uint16_t Cnt2)
{
	uint16_t i = 0, j = 0;
	for( i = 0; i < Cnt1; i++)
		for( j = 0; j < Cnt2; j++);

}

unsigned char ReadFromUart(unsigned char offSet, unsigned char uartSel)
{
	int * readAddress = NULL;
	if(1 == uartSel )
		readAddress = (UART1_BASE_ADDRESS + offSet);
	else
		readAddress = (UART0_BASE_ADDRESS + offSet);
	return (*readAddress) ;
}


void WriteIntoUart(unsigned char offSet, unsigned char uartSel, unsigned char writeData)
{
	int * writeAddress = NULL;
	if(1 == uartSel )
		writeAddress = (UART1_BASE_ADDRESS + offSet);
	else
		writeAddress = (UART0_BASE_ADDRESS + offSet);

		*writeAddress  = writeData;

}



unsigned int UartTxReady()
{
	unsigned int readData = 0;
	readData = ReadFromUart(UART_LINE_STATUS_REGISTER, 1);
	return readData;
}




void UartTransmitCharacter(char c)
{
	unsigned int status, tx_empty;


	while(1)
	{
		status = UartTxReady();
		if( 1 == ( (status >> 5) & 0x1) )
			break;
	}
	// tx must be empty now so send
	WriteIntoUart(UART_DATA_REGISTER, UART1, (unsigned int) c);
}

unsigned int UartTxReady()
{
	unsigned int readData = 0;
	readData = ReadFromUart(UART_LINE_STATUS_REGISTER, 1);
	return readData;
}

void UartTransmitCharacter(char c)
{
	unsigned int status, tx_empty;


	while(1)
	{
		status = UartTxReady();
		if( 1 == ( (status >> 5) & 0x1) )
			break;
	}
	// tx must be empty now so send
	WriteIntoUart(UART_DATA_REGISTER, UART1, (unsigned int) c);
}


void UartTransmitString(char *s)
{
	for(; *s != NULL; s++)
		UartTransmitCharacter(*s);
}


int UartCheckReceiveReady(void)
{
	unsigned int readData = 0;
	readData = ReadFromUart(UART_LINE_STATUS_REGISTER, UART1);
	return (readData & 0x01);
}


char UartReceiveCharacter(void)
{
	while(!UartCheckReceiveReady()) ;
	return (unsigned char) ReadFromUart(UART_DATA_REGISTER, UART1);
}



char UartRecieveString(void)
{	
	int i=0;
char *buff
	while( UartReceiveCharacter() != NULL )
		{
		   buff[i] = UartReceiveCharacter;
           i++;
		}
	return *buff;
		
}





void UartTransmitString(char *s)
{
	for(; *s != NULL; s++)
		UartTransmitCharacter(*s);
}


