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


# Default PROGRAM and TARGET
PROGRAM ?= hello
TARGET ?= artix7_35t
DEBUG ?= DEBUG
CLEAR ?=

#############################################################
# Prints help message
#############################################################
.PHONY: help
help:
	@echo " Shakti Software Development Kit "
	@echo " Makefile features:"
	@echo ""
	@echo " list_targets"
	@echo " lists the boards supported"
	@echo ""
	@echo " list_applns"
	@echo " lists the example applns availabel to user"
	@echo ""
	@echo " software [PROGRAM=$(PROGRAM)] [TARGET=$(TARGET)]"
	@echo " Builds the requested PROGRAM for the given TARGET"
	@echo ""
	@echo " debug [PROGRAM=$(PROGRAM)] [TARGET=$(TARGET)]"
	@echo " Builds the requested PROGRAM with debug options"
	@echo ""
	@echo ""
	@echo " clean" 
	@echo " Cleans compiled objects in every example applns."
	@echo ""
	@echo " clean [CLEAR=$(PROGRAM)]"
	@echo " Cleans compiled objects of that example appln."



#BOARD_DIR holds the list of boards in a third_party path
BOARD_DIR := $(shell ls ./bsp/third_party) 


#Below variables hold the list of C files in there path
#Each C file corresponds to a appln. Each appln has a label in makefile
#that corresponds to each C file.

GPIO_DIR := $(shell cd ./software/examples/gpio_applns/ && ls -d ./*/  )
UART_DIR := $(shell cd ./software/examples/uart_applns/ && ls -d ./*/ )
I2C_DIR := $(shell cd software/examples/i2c_applns/ && ls -d ./*/  )
APP_DIR := $(GPIO_DIR) $(UART_DIR) $(I2C_DIR)



#List the boards that are supported by Shakti Sdk
.PHONY: all 
all:
	cd  ./software/examples/gpio_applns && $(MAKE) all
	cd  ./software/examples/uart_applns && $(MAKE) all
	cd  ./software/examples/i2c_applns && $(MAKE) all

.PHONY: target
list_targets:
	@echo $(sort $(BOARD_DIR))

#List the example applns running on Shakti
.PHONY: appln
list_applns:
	@echo $(sort $(APP_DIR))

#Software commands
.PHONY: software
software:
	@echo $(PROGRAM) $(TARGET)
	@echo "make for that program on that board"
	cd ./software/examples && $(MAKE) PROGRAM=$(PROGRAM) TARGET=$(TARGET)
	
.PHONY: debug
debug:
	@echo $(PROGRAM) $(TARGET) $(DEBUG)
	@echo "make for that program on that board"
	cd ./software/examples/ && $(MAKE) PROGRAM=$(PROGRAM) TARGET=$(TARGET) DEBUG=$(DEBUG)

.PHONY: clean
clean:
ifeq ($(CLEAR),hello)
	cd ./software/examples/uart_applns && $(MAKE) clean CLEAR=$(CLEAR)
else
ifeq ($(CLEAR),uartmp3)
	cd ./software/examples/uart_applns && $(MAKE) clean CLEAR=$(CLEAR)
else
ifeq ($(CLEAR),lm75)
	cd ./software/examples/i2c_applns && $(MAKE) clean CLEAR=$(CLEAR)
else
ifeq ($(CLEAR),btnled)
	cd ./software/examples/gpio_applns && $(MAKE) clean CLEAR=$(CLEAR)
else
ifeq ($(CLEAR),tglgpio)
	cd ./software/examples/gpio_applns && $(MAKE) clean CLEAR=$(CLEAR)
else
ifeq ($(CLEAR),rdgpio)
	cd ./software/examples/gpio_applns && $(MAKE) clean CLEAR=$(CLEAR)
else
ifeq ($(CLEAR),motor)
	cd ./software/examples/gpio_applns && $(MAKE) clean CLEAR=$(CLEAR)
else
ifeq ($(CLEAR),keypad)
	cd ./software/examples/gpio_applns && $(MAKE) clean CLEAR=$(CLEAR)
else
ifeq ($(CLEAR),maze)
	cd ./software/examples/uart_applns && $(MAKE) clean CLEAR=$(CLEAR)
else
ifeq ($(CLEAR),)
	cd ./software/examples/uart_applns && $(MAKE) clean CLEAR=$(CLEAR)
	cd ./software/examples/i2c_applns && $(MAKE) clean CLEAR=$(CLEAR)
	cd ./software/examples/gpio_applns && $(MAKE) clean CLEAR=$(CLEAR)
else
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
