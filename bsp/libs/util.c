/*******************************************************************************
 * Project               	     : shakti devt board
 * Name of the file	           : util.c
 * Brief Description of file   : src file for util
 * Name of Author    	         : Sathya Narayanan N
 * Email ID                    : sathya281@gmail.com

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
 *********************************************************************************/
/** @fn  waitfor
 * @brief stall the process fro given time 
 * @warning No warning
 * @param[in] unsigned int
 * @param[Out] No output parameter
 */
void waitfor(unsigned int secs) 
{
	unsigned int time = 0;
	while (time++ < secs);
}

/** @fn delay
 * @brief  sleeps for number seconds 
 * @warning none 
 * @param[in] unsigned long (number of seconds) 
 * @param[Out] No output parameter
 */
void delay(unsigned long seconds)
{
	unsigned long cntr1 = seconds *1000;
	unsigned long tmpCntr;

	while (cntr1--) {
		tmpCntr = 1000;
		while (tmpCntr--);
	}
}

/** @fn pow_10
 * @brief generate different powers of 10 
 * @warning none
 * @param[in] unsigned int
 * @param[Out] return result in float 
 */
float pow_10(unsigned int y)
{
	unsigned int x=1;
	float result=1;

	for (unsigned int i=0; i <y; i++)
	{
		x *= 10;
	}

	return ((float) x);
}
/** @fn reverse 
 * @brief reverse a string and store in the same string
 * @warning none
 * @param[in] char, int
 * @param[Out] No output parameter
 */
void reverse(char *str, int length) 
{ 
	int i = 0;
	int j = length - 1;
	char tmp;

	while (i<j) 
	{ 
		tmp = str[i]; 
		str[i] = str[j]; 
		str[j] = tmp; 

		i++;
		j--; 
	} 
} 

/** @fn int_to_string
 * @brief convert decimal numbers to string
 * @details Takes num as input and converts it to string.
 *	    The converted string is stored in str. The 
 * position of last character in the str is returned.
 * This function is tailored to support ftoa.
 * @warning 
 * @param[in] int, char, int
 * @param[Out] int
 */
int int_to_string(int number, char str[], int afterpoint) 
{ 
	int i = 0; 

	/*extract each digit and put into str[i]*/

	while (number != 0) { 
		str[i] = ((number%10) + '0'); 
		i++;    
		num = num/10; 
	} 

	/*insert 0 after the numbers, if count of digits less than afterpoint*/

	while (i < afterpoint) {
		str[i] = '0'; 
		i++;
	}

	/*
	   zeroth digit is in oth position in array,
	   To read digits properly, reverse array
	 */
	reverse(str, i); 
	str[i] = '\0'; 

	return i; 
} 

/** @fn ftoa 
 * @brief converts float to string 
 * @details Split floating number into fpart and ipart
 *          Finally merge it into one float number
 * @param[in] float (floating point number - n)
 *		        char (float in string - res)
 *		        int (precision - afterpoint)
 * @param[Out]  No output parameter
 */
void ftoa(float n, char *res, int afterpoint) 
{ 
	int i=0;
	char temp[30]={'\0'};

	// Extract integer part 
	int ipart = (int)n; 

	// Extract floating part 
	float fpart = (float) (n - (float)ipart); 
	int j=0;

	if(n < (0/1))
	{
		res[j]='-';
		j=1;
	}

	if (ipart == 0)
	{
		res[j]='0';
		j=j+1;
	}
	else{
		if (ipart <0)
		{
			ipart =(-1)*ipart;
		}

		i = int_to_string(ipart, temp, 0); 

		strcpy(res+j,temp);
	}

	i = i+j;

	// check for display option after point 
	if (afterpoint != 0) 
	{ 
		res[i] = '.'; // add dot 

		if (fpart < 0/1)
		{

			fpart = (-1)*fpart;

		}
		else if (fpart == 0/1)
		{
			fpart = fpart;
		}

		fpart = fpart * pow_10( afterpoint); 

		int_to_string((int)fpart, res + i + 1, afterpoint); 
	} 
} 

/** @fn delay_loop
 * @brief Delay calculated interms of iterative operation 
 * @warning none
 * @param[in] unsigned long , unsigned long
 * @param[Out] No output parameter
 */
void delay_loop(unsigned long cntr1, unsigned long cntr2)
{
	unsigned long tmpCntr = cntr2;
	while (cntr1--) {
		tmpCntr = cntr2;
		while (tmpCntr--);
	}
}

/** @fn read_word
 * @brief returns the value stored at a given address
 Here we assume the word size to be 32 bits for gpio
 * @details
 * @warning
 * @param[in] int*
 * @param[Out] long int
 */
long int read_word(int *addr)
{
	//	log_info("addr = %x data = %x\n", addr, *addr);
	return *addr;
}

/** @fn write_word
 * @brief  writes a value to an address
 * @details
 * @warning
 * @param[in] int* ,unsigned long
 * @param[Out] No output parameter
 */
void write_word(int *addr, unsigned long val)
{
	*addr = val;
	//	log_info("addr = %x data = %x\n", addr, *addr);
}

