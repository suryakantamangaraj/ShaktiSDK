/***************************************************************************
 * Project           			:  shakti devt board
 * Name of the file	     		:  log.c
 * Created date			        :  
 * Brief Description of file    :   print control for all operation
 * Name of Author    	        :  Sathya Narayanan N & Abhinav ramnath
 * Email ID                     :  sathya281@gmail.com

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
#include "log.h"
#include "uart.h"

/*Use -D compiler flag to set the LOG_LEVEL; default value is 1*/
#ifndef LOG_LEVEL
#define LOG_LEVEL 5 
#endif

/** @fn void log_trace(const char*fmt, ...);
 * @brief Function to print trace logs
 * @details This function print trace logs if the LOG_LEVEL allows trace logs
 * @param[in] printf formatted arguments with format specifiers
 * @param[Out] returns nothing.
 */
void log_trace(const char* fmt, ...)
{
	if (TRACE <= LOG_LEVEL) {
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	}
}

/** @fn void log_info(const char*fmt, ...);
 * @brief Function to print info logs
 * @details This function print info logs if the LOG_LEVEL allows info logs
 * @param[in] printf formatted arguments with format specifiers
 * @param[Out] returns nothing.
 */
void log_info(const char* fmt, ...)
{
	if (INFO <= LOG_LEVEL) {
	va_list ap;
	va_start(ap, fmt);

	_printf_( fmt, ap);

	va_end(ap);
	}
}

/** @fn void log_debug(const char*fmt, ...);
 * @brief Function to print debug logs
 * @details This function print debug logs if the LOG_LEVEL allows debug logs
 * @param[in] printf formatted arguments with format specifiers
 * @param[Out] returns nothing.
 */
void log_debug(const char* fmt, ...)
{
	if (DEBUG <= LOG_LEVEL) {
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	}
}

/** @fn void log_warn(const char*fmt, ...);
 * @brief Function to print warn logs
 * @details This function print trace warn if the LOG_LEVEL allows warn logs
 * @param[in] printf formatted arguments with format specifiers
 * @param[Out] returns nothing.
 */
void log_warn(const char* fmt, ...)
{
	if (WARN <= LOG_LEVEL) {
	va_list ap;
	va_start(ap, fmt);

	_printf_( fmt, ap);

	va_end(ap);
	}
}

/** @fn void log_error(const char*fmt, ...);
 * @brief Function to print error logs
 * @details This function print error logs if the LOG_LEVEL allows error logs
 * @param[in] printf formatted arguments with format specifiers
 * @param[Out] returns nothing.
 */
void log_error(const char* fmt, ...)
{
	if (ERROR <= LOG_LEVEL) {
	va_list ap;
	va_start(ap, fmt);

	_printf_( fmt, ap);

	va_end(ap);
	}
}

/** @fn void log_fatal(const char*fmt, ...);
 * @brief Function to print fatal logs
 * @details This function print fatal logs if the LOG_LEVEL allows fatal logs
 * @param[in] printf formatted arguments with format specifiers
 * @param[Out] returns nothing.
 */
void log_fatal(const char* fmt, ...)
{
	if (FATAL <= LOG_LEVEL) {
	va_list ap;
	va_start(ap, fmt);

	_printf_( fmt, ap);

	va_end(ap);
	}

	log_info("\n panic \n");
	while (1);
}
