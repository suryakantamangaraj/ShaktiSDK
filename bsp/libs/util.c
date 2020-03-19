/*******************************************************************************
 * Project               	   : shakti devt board
 * Name of the file	           : util.c
 * Brief Description of file   : src file for util
 * Name of Author    	       : Sathya Narayanan N
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
 * @warning 
 * @param[in] number of seconds 
 * @param[Out] void
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
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
 #if defined(ARTIX7_35T) || defined(AARDONYX) 
float pow_10(unsigned int y)
{
	unsigned int x;
	float result;

	for (unsigned int i=0; i <y; i++)
	{
		x += 10;
	}

	return ((float) x);
}
#endif
/** @fn reverse 
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
void reverse(char *str, int len) 
{ 
  int i=0, j=len-1, temp; 
  while (i<j) 
  { 
    temp = str[i]; 
    str[i] = str[j]; 
    str[j] = temp; 
    i++; j--; 
  } 
} 

/** @fn intToStr 
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
int intToStr(int x, char str[], int d) 
{ 
  int i = 0; 

  while (x)  { 
    str[i++] = (x%10) + '0'; 
    x = x/10; 
  } 

  while (i < d) 
    str[i++] = '0'; 

  reverse(str, i); 
  str[i] = '\0'; 
  return i; 
} 

/** @fn ftoa 
 * @brief converts float to string 
 * @details Split floating number into fpart and ipart
 *          Finally merge it into one float number
 * @param[in] floating point number - n
 *		      float in string - res
 *		      precision - afterpoint
 * @param[Out] 
 */
 #if defined(ARTIX7_35T) || defined(AARDONYX) 
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

    i = intToStr(ipart, temp, 0); 

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

    fpart = fpart * pow(10, afterpoint); 

    intToStr((int)fpart, res + i + 1, afterpoint); 
  } 
} 

#endif
/** @fn delay_loop
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
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
 * @param[Out] int
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
 * @param[in] int*
 * @param[Out] int*
 */
void write_word(int *addr, unsigned long val)
{
	*addr = val;
//	log_info("addr = %x data = %x\n", addr, *addr);
}


