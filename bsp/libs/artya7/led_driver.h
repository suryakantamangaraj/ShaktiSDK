/********************************************************************************************** 
Copyright (c) 2018, IIT Madras All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted
provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions
  and the following disclaimer.  
* Redistributions in binary form must reproduce the above copyright notice, this list of 
  conditions and the following disclaimer in the documentation and/or other materials provided 
 with the distribution.  
* Neither the name of IIT Madras  nor the names of its contributors may be used to endorse or 
  promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
****************************************************************************************************/

 /**
 * @file led_driver.h
 * @project 
 * @brief  All the definitions are very specific to ARTY A7 (35T & 100T) boards
 */
 
#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include "platform.h" //Contains arty a7 gpio definitions.
#include "gpio.h"  //Contains the methods to Access GPIOs

#if defined(ARTIX7_35T) || defined(ARTIX7_100T)
/*! RGB LED 0 defines */
#define LED0_R GPIO16 
#define LED0_G GPIO17
#define LED0_B GPIO18

/*! RGB LED 1 defines */
#define LED1_R GPIO19
#define LED1_G GPIO20
#define LED1_B GPIO21

/*! Normal LED 1 defines */
#define LED2 GPIO22

/*! Normal LED 2 defines */
#define LED3 GPIO23


/*! Combined RGB LED defines */
#define RGB0 (LED0_R | LED0_G | LED0_B )
#define RGB1 (LED1_R | LED1_G | LED1_B )

/*! Combined Normal LED defines */
#define NORMAL_LEDS ( LED2 | LED3 )
#define RGB_LEDS ( RGB0 | RGB1 )

/*! Combines ALL LED defines */
#define ALL_LEDS (RGB_LEDS | NORMAL_LEDS)


/*! Control for all LEDS */
#define NORMAL_LED0 0
#define NORMAL_LED1 1

#define RGB_LED0 0
#define RGB_LED1 1

// function prototype
void configure_ledx(unsigned long pin_cntrl);
void configure_rgb_ledx(unsigned char led_no);
void configure_normal_leds();
void configure_rgb_leds();
void configure_all_leds();
void turn_on_ledx(unsigned long pin_cntrl);
void turn_off_ledx(unsigned long pin_cntrl);
void turn_on_normal_leds();
void turn_off_normal_leds();
void turn_on_rgb_ledx(unsigned char led_no);
void turn_off_rgb_ledx(unsigned char led_no);
void turn_on_rgb_leds();
void turn_off_rgb_leds();
void turn_on_all_leds();
void turn_off_all_leds();
void toggle_ledx(unsigned long pin_cntrl, unsigned long delay1, unsigned long delay2);
void toggle_normal_leds( unsigned long delay1, unsigned long delay2 );
void toggle_rgb_leds( unsigned long delay1, unsigned long delay2 );
void toggle_all_leds( unsigned long delay1, unsigned long delay2);


#endif
#endif
