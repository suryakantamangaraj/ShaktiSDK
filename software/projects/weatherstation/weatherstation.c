/***************************************************************************
* Project           			:  shakti devt board
* Name of the file	     		:  weatherstation.c
* Created date			        :  22.10.2019
* Brief Description of file             :  A sample project to demonstrate 
					   integration of temperature sensor 
                                           and transmission of data to a website
* Name of Author    	                :  Anand Kumar S
* Email ID                              :  007334@imail.iitm.ac.in

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
#include "uart.h"//Includes the definitions of uart communication protocol//
#include "string.h"
#define LM75_SLAVE_ADDRESS 0x90//Defines the Starting address of slave
#define API_KEY "9T40C2TMUSU1ZX6E"

int write_to_esp8266(char *data,uart_num sel,int baudrate) {
	while (*data != '\0') {
		write_uart(*data,sel,baudrate);
		data++;
	}
	write_uart('\r',sel,baudrate);
	write_uart('\n',sel,baudrate);

}

int write_enter_to_esp8266(uart_num sel,int baudrate){
	write_uart('\r',sel,baudrate);
	write_uart('\n',sel,baudrate);
}

int read_from_esp8266(char *data,uart_num sel,int baudrate) {
	int ch;
        char *str = data;
        char *test = data;
	for(int i=0;i<198;i++) {
		ch = read_uart(sel,baudrate);
		//printf("read from esp %c  \n",ch);
		*str = ch;
		str++; 
		*str = '\0';
		//printf("string is %s\n",test);
		if(strstr(test,"OK") != NULL)  {
			//printf("read from esp8266 %s\n",test);
			return;
		}
		if(strstr(test,"ERROR") != NULL) {
			//printf("read from esp8266 %s\n",test);
			return;
		}
		if(strstr(test,">") != NULL) {
			//printf("read from esp8266 %s\n",test);
			return;
		}
                if(strstr(test,"RECV") != NULL) {
                        //printf("read from esp8266 %s\n",test);
                        return;
                }
	}
	*str = '\0';
	return 1;
}

void transmit_data(int temperature, int baudrate) {
/***************************************************
    AT – response OK
    AT+CWLAP – list nearby available WiFi networks
    AT+CIPMUX=0
    AT+CIPSTART="TCP","api.thingspeak.com",80
    AT+CIPSEND=75
    GET https://api.thingspeak.com/update?api_key=9T40C2TMUSU1ZX6E&field1=45

**************************************************/


	char data[200];
	char sendData[76];
	sprintf(sendData,"GET https://api.thingspeak.com/update?api_key=%s&field1=%d",API_KEY,temperature);
	//printf("\n send data %s\n",sendData);
	// Connect to Wifi using esp8266
	flush_uart(UART1);
	printf(" \nsending AT command to esp\n");
	write_to_esp8266("AT",UART1,baudrate);
	read_from_esp8266(data,UART1,baudrate);
	printf(" data from esp :%s\n",data);

	flush_uart(UART1);
	printf(" sending AT Echo off command to esp\n");
	write_to_esp8266("ATE0",UART1,baudrate);
	read_from_esp8266(data,UART1,baudrate);
	printf(" data from esp :%s\n",data);


	printf(" write AT+CIPMUX\n");
	flush_uart(UART1);
	write_to_esp8266("AT+CIPMUX=0",UART1,baudrate);
	read_from_esp8266(data,UART1,baudrate);
	printf(" data from esp :%s\n",data);

	//printf(" Waiting to get IP\n",data);
	//delay(2);
/*
	delay(2);
	flush_uart(UART1);
	write_to_esp8266("AT+CIFSR",UART1,baudrate);
	read_from_esp8266(data,UART1,baudrate);
	printf(" data from esp :%s\n",data);

*/
	flush_uart(UART1);
	write_to_esp8266("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80",UART1,baudrate);
	read_from_esp8266(data,UART1,baudrate);
	printf(" data from esp :%s\n",data);

	printf(" write AT+CIPSEND\n");
	flush_uart(UART1);
	write_to_esp8266("AT+CIPSEND=75",UART1,baudrate);
	read_from_esp8266(data,UART1,baudrate);
	printf(" data from esp :%s\n",data);

	printf(" write Data\n");
	flush_uart(UART1);
	//write_to_esp8266("GET https://api.thingspeak.com/update?api_key=9T40C2TMUSU1ZX6E&field1=45",UART1,baudrate);
	write_to_esp8266(sendData,UART1,baudrate);

	//flush_uart(UART1);
	write_enter_to_esp8266(UART1,baudrate);
	read_from_esp8266(data,UART1,baudrate);
	printf(" data from esp :%s\n",data);

	// disconnect from server
	printf(" write AT+CIPCLOSE\n");
	flush_uart(UART1);
	write_to_esp8266("AT+CIPCLOSE",UART1,baudrate);
	read_from_esp8266(data,UART1,baudrate);
	printf(" data from esp :%s\n",data);


}
void main()
{	
	int i=0;
	int baudrate = 9600;
	int temperature = 24;
	printf("\n Sending temperature data to cloud server!....\n");
	printf("\n Baud rate set to %d \n",baudrate);
	printf("\n Waiting to ESP8266 to initialize \n");
	delay(3);
	while (1) {
		temperature = temperature_value();
		if (temperature != 999)
			transmit_data(temperature, baudrate); 
		delay(60);
	}
}
