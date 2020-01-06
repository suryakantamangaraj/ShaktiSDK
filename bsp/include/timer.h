/************************************************************************
* Project           			:  shakti devt board
* Name of the file	     		:  timer.h
* Brief Description of file             :  Headerfile for Timer .
*  Name of Author    	                :  Sathya Narayanan N
* Email ID                              :  sathya281@gmail.com

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

   ************************************************************************/

/**
 * @file timer.h
 * @project shakti devt board
 * @brief Headerfile for Timer  
 */
#ifndef TIMER_H
#define TIMER_H

#define CLINT_CTRL_ADDR 0x02000000
#define  CLINT_MTIME 0xbff8

// function prototype
uint64_t get_timer_value();

#endif
