/*
platform.h - header file for platform

Created by Sathya Narayanan N
Email id: sathya281@gmail.com

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

*/
#ifndef PLATFORM_H
#define PLATFORM_H


#define MTIME 0x0200BFF8


#define MCAUSE_INT         0x80000000
#define MCAUSE_CAUSE       0x7FFFFFFF

/*
 *@brief RISCV - E CLASS SOC Memory mapping
 */
/*!Debugger Offset */
#define DBG_MEM_START 0x00000010

/*!Tightly Coupled Memory(TCM) Offset. Size 128kB */
#define TCM_MEM_START 0x80000000 /*! DDR3 Memory Start address */

/*!Pulse Width Modulation Start Offsets */
#define PWM0_START 0x00030000 /*!Pulse Width Modulator 0 */
#define PWM1_START 0x00030100 /*!Pulse Width Modulator 1 */
#define PWM2_START 0x00030200 /*!Pulse Width Modulator 2 */
#define PWM3_START 0x00030300 /*!Pulse Width Modulator 3 */
#define PWM4_START 0x00030400 /*!Pulse Width Modulator 4 */
#define PWM5_START 0x00030500 /*!Pulse Width Modulator 5 */

/*!Serial Peripheral Interface Offsets */
#define SPI0_START 0x00020000 /* Serial Peripheral Interface 0 */
#define SPI1_START 0x00020100 /* Serial Peripheral Interface 1 */
#define SPI2_START 0x00020200 /* Serial Peripheral Interface 2 */

/*!Universal Synchronous Receiver Transmitter Interface Offsets */
#define UART0_START 0x00011300 /*! UART 0 */
#define UART1_START 0x00011400 /*! UART 0 */
#define UART2_START 0x00011500 /*! UART 0 */

/*! Core Local Interruptor CLINT */
#define CLINT_START 0x02000000

/*! Inter Integrated Circuit (I2C) Interface */
#define I2C_START 0x00040000 /*! I2C Start Address */

/*! Programmable Logic Interrupt Interface */
#define PLIC_START 0x00040100 /*! PLIC Interface Start */

/*!General Purpose Input / Output */
#define GPIO_START 0x00040200 //GPIO Start Address */
#define GPIO_OFFSET 0x04 /*!Generic offset used to access GPIO registers*/



/* 
 * General Purpose IOs supported 
 */
#define GPIO_START 0x00
#define GPIO0 (1 <<  0)
#define GPIO0 (1 <<  1)
#define GPIO0 (1 <<  2)
#define GPIO0 (1 <<  3)
#define GPIO0 (1 <<  4)
#define GPIO0 (1 <<  5)
#define GPIO0 (1 <<  6)
#define GPIO0 (1 <<  7)
#define GPIO0 (1 <<  8)
#define GPIO0 (1 <<  9)
#define GPIO0 (1 << 10)
#define GPIO0 (1 << 11)
#define GPIO0 (1 << 12)
#define GPIO0 (1 << 13)
#define GPIO0 (1 << 14)
#define GPIO0 (1 << 15)
#define GPIO0 (1 << 16)
#define GPIO_END  0x10

#endif
