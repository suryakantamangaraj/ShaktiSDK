# Created by Madan Kumar S
# Email id: kumarmadan96@gmail.com

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

# Invoke all possible combinations of applns for different targets
# There is a provision to make in the exact folder where code is written
# We are using that provision to invole appropriate makefile scripts from top folder
all:
	@echo "$(TARGET)"
ifeq ($(PROGRAM),pathtracerrobot)
	cd projects/pathtracerrobot && $(MAKE) $(PROGRAM).riscv TARGET=$(TARGET) DEBUG=$(DEBUG)
else
ifeq ($(PROGRAM),robotmp3)
	cd projects/robotmp3 && $(MAKE) $(PROGRAM).riscv TARGET=$(TARGET) DEBUG=$(DEBUG)
else
ifeq ($(PROGRAM),homeautomation)
	cd projects/homeautomation && $(MAKE) $(PROGRAM).riscv TARGET=$(TARGET) DEBUG=$(DEBUG)
endif
endif
endif
