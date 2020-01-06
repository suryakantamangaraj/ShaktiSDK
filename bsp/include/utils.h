/*
utils.h - header file for handling traps

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

#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <stdint.h>

void waitfor(unsigned int secs);

void ftoa( float, char *, unsigned);

size_t strnlen(const char *s, size_t n);

#endif
