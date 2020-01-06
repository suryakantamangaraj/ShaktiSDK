#ifndef BUTTON_DRIVER_H
#define BUTTON_DRIVER_H

#if defined(ARTIX7_35T) || defined(ARTIX7_100T)

/**
 * @file button_driver.h
 * @project 
 * @brief   
 */

#include "platform.h"
#include "gpio.h"
//Buttons
#define BTN0 GPIO28
#define BTN1 GPIO29
#define BTN2 GPIO30
#define BTN3 GPIO31

#define ALL_BTNS (BTN0 | BTN1 | BTN2 | BTN3)

// function prototype
void configure_btn(unsigned long pinCntrl);
void configure_all_btn();

#endif
#endif
