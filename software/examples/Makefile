#Created by Sathya Narayanan N
# Email id: sathya281@gmail.com

#   Copyright (C) 2019  IIT Madras. All rights reserved.

#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.

#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.

#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.






export TARGET
export PROGRAM
export DEBUG

# appln and target board
PROGRAM ?= all
TARGET ?=artix7_35t
DEBUG ?=
UPLOAD ?=

# Invoke all possible combinations of applns for different targets
# There is a provision to make in the exact folder where code is written
# We are using that provision to invole appropriate makefile scripts from top folder
all:
	@echo "$(TARGET)"
ifeq ($(PROGRAM),hello)
ifeq ($(UPLOAD),UPLOAD)
	cd uart_applns/hello && $(MAKE) upload TARGET=$(TARGET) DEBUG=$(DEBUG)
else 
	cd uart_applns/hello && $(MAKE) $(PROGRAM).riscv TARGET=$(TARGET) DEBUG=$(DEBUG)
endif
else
ifeq ($(PROGRAM),asm_calculator)
ifeq ($(UPLOAD),UPLOAD)
	cd uart_applns/asm_calculator && $(MAKE) upload TARGET=$(TARGET) DEBUG=$(DEBUG)
else 
	cd uart_applns/asm_calculator && $(MAKE) $(PROGRAM).riscv TARGET=$(TARGET) DEBUG=$(DEBUG)
endif
else
ifeq ($(PROGRAM),maze)
ifeq ($(UPLOAD),UPLOAD)
	cd uart_applns/wifi && $(MAKE) upload TARGET=$(TARGET) DEBUG=$(DEBUG)
else
	cd uart_applns/wifi && $(MAKE) $(PROGRAM).riscv TARGET=$(TARGET) DEBUG=$(DEBUG)
endif
else
ifeq ($(PROGRAM),lm75)
ifeq ($(UPLOAD),UPLOAD)
	cd i2c_applns/lm75 && $(MAKE) upload TARGET=$(TARGET) DEBUG=$(DEBUG)
else
	cd i2c_applns/lm75 && $(MAKE) $(PROGRAM).riscv TARGET=$(TARGET) DEBUG=$(DEBUG)
endif
else
ifeq ($(PROGRAM),btnled)
ifeq ($(UPLOAD),UPLOAD)
	cd gpio_applns/btnled && $(MAKE) upload TARGET=$(TARGET) DEBUG=$(DEBUG)
else
	cd gpio_applns/btnled && $(MAKE) $(PROGRAM).riscv TARGET=$(TARGET) DEBUG=$(DEBUG)
endif
else
ifeq ($(PROGRAM),tglgpio)
ifeq ($(UPLOAD),UPLOAD)
	cd gpio_applns/tglgpio && $(MAKE) upload TARGET=$(TARGET) DEBUG=$(DEBUG)
else
	cd gpio_applns/tglgpio && $(MAKE) $(PROGRAM).riscv TARGET=$(TARGET) DEBUG=$(DEBUG)
endif
else
ifeq ($(PROGRAM),rdgpio)
ifeq ($(UPLOAD),UPLOAD)
	cd gpio_applns/rdgpio && $(MAKE) upload TARGET=$(TARGET) DEBUG=$(DEBUG)
else
	cd gpio_applns/rdgpio && $(MAKE) $(PROGRAM).riscv TARGET=$(TARGET) DEBUG=$(DEBUG)
endif
else
ifeq ($(PROGRAM),motor)
ifeq ($(UPLOAD),UPLOAD)
	cd gpio_applns/motor && $(MAKE) upload TARGET=$(TARGET) DEBUG=$(DEBUG)
else
	cd gpio_applns/motor && $(MAKE) $(PROGRAM).riscv TARGET=$(TARGET) DEBUG=$(DEBUG)
endif
else
ifeq ($(PROGRAM),keypad)
ifeq ($(UPLOAD),UPLOAD)
	cd gpio_applns/keypad && $(MAKE) upload TARGET=$(TARGET) DEBUG=$(DEBUG)
else
	cd gpio_applns/keypad && $(MAKE) $(PROGRAM).riscv TARGET=$(TARGET) DEBUG=$(DEBUG)
endif
else
ifeq ($(PROGRAM),gyro_softi2c)
ifeq ($(UPLOAD),UPLOAD)
	cd gpio_applns/gyro_softi2c && $(MAKE) upload TARGET=$(TARGET) DEBUG=$(DEBUG)
else
	cd gpio_applns/gyro_softi2c && $(MAKE) $(PROGRAM).riscv TARGET=$(TARGET) DEBUG=$(DEBUG)
endif
endif
endif
endif
endif
endif
endif
endif
endif
endif
endif
