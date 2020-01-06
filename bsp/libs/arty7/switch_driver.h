#ifndef SWITCH_DRIVER_H
#define SWITCH_DRIVER_H

#if defined(ARTIX7_35T) || defined(ARTIX7_100T)

/**
 * @file switch_driver.h
 * @project
 * @brief  
 */
#include "platform.h"
#include "gpio.h"

//Switches
#define SW0 GPIO24
#define SW1 GPIO25
#define SW2 GPIO26
#define SW3 GPIO27

#define ALL_SWITCHES (SW0 | SW1 | SW2 | SW3)

// function prototype
void configure_switch(unsigned long pinCntrl);
void configure_all_switchs();
#endif
#endif
