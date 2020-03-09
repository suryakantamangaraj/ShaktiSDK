/***************************************************************************
* Project           			:  shakti devt board
* Name of the file	     		:  led_driver.c
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

#if defined(ARTIX7_35T) || defined(ARTIX7_100T)

#include "platform.h"
#include "gpio.h"
#include "led_driver.h"

extern void delay_loop(unsigned long , unsigned long );

 /** @fn static void configure_ledx()
 * @brief Configures Individual LED pins as output.
 * @details 8 GPIO pins are mapped to 8 LEDs. This function configures
 *          each LED as output pin.
 * @warning Nil.
 * @param[in] pin_cntrl - Pin that needs to be configured as LED.
 * @param[Out] No output parameters.
 */
void configure_ledx(unsigned long pin_cntrl)
{
	unsigned long read_data = 0;
	read_data = read_word(GPIO_DIRECTION_CNTRL_REG);
	write_word(GPIO_DIRECTION_CNTRL_REG, ( read_data | pin_cntrl ) );
	return ;
}

/** @fn static void configure_rgb_ledx()
 * @brief Configures Individual RGB LED pins as output.
 * @details 8 GPIO pins are mapped to 2 RGB LEDs. This function configures
 *          each LED as output pin.
 * @warning Nil.
 * @param[in] led_no - RGB LED that needs to be configured.
 * @param[Out] No output parameters.
 */
void configure_rgb_ledx(unsigned char led_no)
{
	unsigned long read_data = 0;
	read_data = read_word(GPIO_DIRECTION_CNTRL_REG);
  if (0 == led_no)
    write_word(GPIO_DIRECTION_CNTRL_REG, ( read_data | RGB0 ) );
  else if (1 == led_no)
    write_word(GPIO_DIRECTION_CNTRL_REG, ( read_data | RGB1  ) );
  else
    printf("\nInvalid LED No. Permissable values [0,1]");
	return ;
}

/*
 * @fn static void configure_normal_leds()
 * @brief Configures Normal LEDs 3 & 4 as as output.
 * @details This function configures GPIO pins mapped to 
 *          Normal LEDs as output pins.
 * @warning Nil.
 * @param[in]
 * @param[Out] No output parameters.
 */
void configure_normal_leds()
{
	unsigned long read_data = 0;
	read_data = read_word(GPIO_DIRECTION_CNTRL_REG);
  	write_word(GPIO_DIRECTION_CNTRL_REG, ( read_data | NORMAL_LEDS ) ) ;
	return ;
}

/*
 * @fn static void rgb_leds_configure()
 * @brief Configures RGB LEDs 0 & 1 as as output pins.
 * @details 8 GPIO pins are mapped to 2 normal LEDs. This function configures
 *          gpio pins mapped to both RGB LEDs as output pins.
 * @warning Nil.
 * @param[in]
 * @param[Out] No output parameters.
 */
void configure_rgb_leds()
{
	unsigned long read_data = 0;
	read_data = read_word(GPIO_DIRECTION_CNTRL_REG);
  	write_word(GPIO_DIRECTION_CNTRL_REG, ( read_data | ( RGB_LEDS ) ) );
	return ;
}

/** @fn static void configure_all_leds()
 * @brief Configures GPIO pins mapped to all LEDs as as output pins.
 * @details 8 GPIO pins are mapped to 2 normal LEDs. This function configures
 *          all GPIO pins mapped to all the LEDs as output pins.
 * @warning Nil.
 * @param[in]
 * @param[Out] No output parameters.
 */
void configure_all_leds()
{
	unsigned long read_data = 0;
	read_data = read_word(GPIO_DIRECTION_CNTRL_REG);
  	write_word(GPIO_DIRECTION_CNTRL_REG, ( read_data | ALL_LEDS ) );
	return ;
}

/** @fn static void turn_on_ledx()
 * @brief turn ON the Individual LEDs.
 * @details This function switches ON the LED based on
 *          the GPIO pin position passed.
 * @warning Nil.
 * @param[in] pin_cntrl - GPIO Pin position of the LED that needs to be switched ON.
 * @param[Out] No output parameters.
 */
void turn_on_ledx(unsigned long pin_cntrl)
{
	unsigned long read_data = 0;
	read_data = read_word(GPIO_DATA_REG);
	write_word(GPIO_DATA_REG, ( read_data | pin_cntrl ) );
	return ;
}

 /** @fn static void turn_off_ledx()
 * @brief turn OFF the Individual LEDs.
 * @details This function switches OFF the LED based on
 *          the GPIO pin position passed.
 * @warning Nil.
 * @param[in] pin_cntrl - GPIO Pin position of the LED that needs to be switched OFF.
 * @param[Out] No output parameters.
 */
void turn_off_ledx(unsigned long pin_cntrl)
{
	unsigned long read_data = 0;
	read_data = read_word(GPIO_DATA_REG);
	write_word(GPIO_DATA_REG, ( read_data & (~pin_cntrl) )   );
	return ;
}

/** @fn static void turn_on_normal_leds()
 * @brief turn ON the all Normal LEDs.
 * @details This function switches ON the Normal LEDs
 * @warning Nil.
 * @param[in] Nil.
 * @param[Out] No output parameters.
 */
void turn_on_normal_leds()
{
	unsigned long read_data = 0;
	read_data = read_word(GPIO_DATA_REG);
 	write_word(GPIO_DATA_REG, ( read_data | NORMAL_LEDS ) );
	return ;
}

/** @fn static void turn_off_normal_leds()
 * @brief turn OFF the all Normal LEDs.
 * @details This function switches ON both RGB LED.
 * @warning Nil.
 * @param[in] Nil.
 * @param[Out] No output parameters.
 */
void turn_off_normal_leds()
{
	unsigned long read_data = 0;
	read_data = read_word(GPIO_DATA_REG);
	write_word(GPIO_DATA_REG, ( read_data & (~NORMAL_LEDS) ) );
	return ;
}

/** @fn static void turn_on_rgb_ledx()
 * @brief turn ON the Individual RGB LED.
 * @details 8 GPIO pins are mapped to 2 RGB LEDs. This function switches
 *          on passed RGB LED.
 * @warning Nil.
 * @param[in] RGB LED that needs to be switched On[0,1].
 * @param[Out] No output parameters.
 */
void turn_on_rgb_ledx(unsigned char led_no)
{
	unsigned long read_data = 0;
	read_data = read_word(GPIO_DATA_REG);
  if (0 == led_no)
    write_word(GPIO_DATA_REG, ( read_data | RGB0 ) );
  else if (1 == led_no)
    write_word(GPIO_DATA_REG, ( read_data | RGB1 ) );
  else
    printf("\n RGB Led number is not valid [0,1]");
	return ;
}

/** @fn static void turn_off_rgb_ledx()
 * @brief turn OFF the Individual RGB LED.
 * @details 8 GPIO pins are mapped to 2 RGB LEDs. This function switches
 *          OFF passed RGB LED.
 * @warning Nil.
 * @param[in] RGB LED that needs to be switched OFF[0,1].
 * @param[Out] No output parameters.
 */
void turn_off_rgb_ledx(unsigned char led_no)
{
	unsigned long read_data = 0;
	read_data = read_word(GPIO_DATA_REG);
  if (0 == led_no)
	 write_word(GPIO_DATA_REG, ( read_data & (~RGB0) ) );
  else if (1 == led_no)
 	  write_word(GPIO_DATA_REG, ( read_data & (~RGB1) ) );
  else
    printf("\n RGB Led number is not valid [0,1]");
	return ;
}

/** @fn static void turn_on_rgb_leds()
 * @brief turn ON the all RGB LEDs.
 *
 * @details 8 GPIO pins are mapped to 2 RGB LEDs. This function switches
 *          ON both RGB LED.
 * @warning Nil.
 * @param[in] Nil.
 * @param[Out] No output parameters.
 */
void turn_on_rgb_leds()
{
	unsigned long read_data = 0;
	read_data = read_word(GPIO_DATA_REG);
    write_word(GPIO_DATA_REG, ( read_data | RGB_LEDS ) );
	return ;
}

/** @fn static void turn_off_rgb_leds()
 * @brief turn ON the all RGB LEDs.
 * @details This function switches ON both RGB LED.
 * @warning Nil.
 * @param[in] Nil.
 * @param[Out] No output parameters.
 */
void turn_off_rgb_leds()
{
	unsigned long read_data = 0;
	read_data = read_word(GPIO_DATA_REG);
 	write_word(GPIO_DATA_REG, ( read_data & (~RGB_LEDS) ) );
	return ;
}

/** @fn static void turn_on_all_leds()
 * @brief turn ON the all LEDs.
 * @details This function switches ON all LEDs.
 * @warning Nil.
 * @param[in] Nil.
 * @param[Out] No output parameters.
 */
void turn_on_all_leds()
{
	unsigned long read_data = 0;
	read_data = read_word(GPIO_DATA_REG);
	write_word(GPIO_DATA_REG, ( read_data | ALL_LEDS ) );
	return ;
}

/** @fn static void turn_off_all_leds()
 * @brief turn OFF the all LEDs.
 * @details This function switches OFF all LEDs.
 * @warning Nil.
 * @param[in] Nil.
 * @param[Out] No output parameters.
 */
void turn_off_all_leds()
{
	unsigned long read_data = 0;
	read_data = read_word(GPIO_DATA_REG);
  write_word(GPIO_DATA_REG, ( read_data & (~ALL_LEDS) ) );
	return ;
}

 /** @fn static void toggle_ledx()
 * @brief Toggles the passed LED.
 * @details This function toggles given LED.
 * @warning Nil.
 * @param[in] Led that needs to be toggled, delay.
 * @param[Out] No output parameters.
 */
void toggle_ledx(unsigned long pin_cntrl, unsigned long delay1, unsigned long delay2)
{
	unsigned long read_data = 0;
	read_data = read_word(GPIO_DATA_REG);
	write_word (GPIO_DATA_REG, ( read_data | (pin_cntrl ) ) );
	delay_loop(delay1, delay2);
	write_word(GPIO_DATA_REG, ( read_data & (~pin_cntrl) ) );
	delay_loop(delay1, delay2);
	return ;
}

 /** @fn static void toggle_normal_leds()
 * @brief toggles normal LEDs.
 * @details This function toggles given both the 
 *          normal LEDs.
 * @warning Nil.
 * @param[in] delay1, delay2 
 * @param[Out] No output parameters.
 */
void toggle_normal_leds( unsigned long delay1, unsigned long delay2 )
{
	unsigned long read_data = 0;
	read_data = read_word(GPIO_DATA_REG);
	write_word(GPIO_DATA_REG, ( read_data | NORMAL_LEDS ) );
	delay_loop(delay1, delay2);
 	write_word(GPIO_DATA_REG, ( read_data & (~NORMAL_LEDS) ) );
	delay_loop(delay1, delay2);
	return ;
}

/** @fn static void Toggle_RGB_Leds()
 * @brief Toggles RGB LED.
 * @details This function toggles the RGB LEDs.
 * @warning Nil.
 * @param[in] delay1, delay2.
 * @param[Out] No output parameters.
 */
void toggle_rgb_leds( unsigned long delay1, unsigned long delay2 )
{
	unsigned long read_data = 0;
	read_data = read_word(GPIO_DATA_REG);
	write_word(GPIO_DATA_REG, ( read_data | RGB_LEDS ) );
	delay_loop(delay1, delay2);
 	write_word(GPIO_DATA_REG, ( read_data & (~RGB_LEDS) ) );
	delay_loop(delay1, delay2);
	return ;
}

/** @fn static void toggle_all_leds()
 * @brief Toggles All LEDs.
 * @details This function toggles  all the LEDs with a delay.
 * @warning Nil.
 * @param[in] delay.
 * @param[Out] No output parameters.
 */
void toggle_all_leds( unsigned long delay1, unsigned long delay2)
{
	unsigned long read_data = 0;
	read_data = read_word(GPIO_DATA_REG);
	write_word(GPIO_DATA_REG, ( read_data | ALL_LEDS ) );
	delay_loop(delay1, delay2);
	write_word(GPIO_DATA_REG, ( read_data & (~ALL_LEDS) ) );
	delay_loop(delay1, delay2);
	return ;
}
#endif
