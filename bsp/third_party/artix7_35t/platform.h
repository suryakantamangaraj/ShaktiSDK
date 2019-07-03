
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

#define GPIO_START 0x00000000
#define GPIO_DIRECTION_CNTRL_REG (GPIO_START)
#define GPIO_DATA_REG  (GPIO_START + 0X08)

#define MTIME 0x0200BFF8



#endif
