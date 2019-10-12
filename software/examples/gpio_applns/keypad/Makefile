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

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>

SHELL := /bin/bash # Use bash syntax
XLEN=64
DC=

#default target board
TARGET ?= artix7_35t
DEBUG ?=

ifeq ($(TARGET),artix7_35t)
	XLEN=32
	flags= -D ARTIX7_35T
 	MARCH=rv32imac
	MABI=ilp32
endif

ifeq ($(TARGET),artix7_100t)
	XLEN=64
	flags= -D ARTIX7_100T
	MARCH=rv64imac
	MABI=lp64
endif

ifeq ($(DEBUG),DEBUG)
	DC=-g
endif

#bsp incl file path
bspinc:=../../../../bsp/include
bspdri:=../../../../bsp/drivers
#bsp lib file path
bsplib:=../../../../bsp/libwrap
#bsp board specific files path
bspboard:=../../../../bsp/third_party/$(TARGET)/


all: create_dir
	make keypad.riscv


keypad.riscv: crt.o syscalls.shakti create_dir
	@echo -e "$(GREEN) Compiling GPIO KEYPAD TEST code $(NC)"
	@echo -e "$(RED) Caveat: GPIO Code starts at 0x80000000. Configure RTL appropriately $(NC)"
	@riscv$(XLEN)-unknown-elf-gcc -w $(DC) -mcmodel=medany -static -std=gnu99 -fno-builtin-printf $(flags) -I$(bspinc) -I$(bspdri) -I$(bspboard) -c ./keypad.c -o ./output/keypad.o -march=$(MARCH) -mabi=$(MABI) -lm -lgcc
	@riscv$(XLEN)-unknown-elf-gcc -w $(DC) -mcmodel=medany -static -std=gnu99 -fno-builtin-printf  -I$(bspinc)  -c $(bsplib)/util.c -o ./output/util.o -march=$(MARCH) -mabi=$(MABI) -lm -lgcc
	@riscv$(XLEN)-unknown-elf-gcc -w $(DC) -mcmodel=medany -static -std=gnu99 -fno-builtin-printf  -I$(bspinc)   -c $(bspboard)/uart.c -o ./output/uart.o -march=$(MARCH) -mabi=$(MABI) -lm -lgcc
	@riscv$(XLEN)-unknown-elf-gcc -T $(bspboard)/link.ld ./output/util.o ./output/keypad.o  ./output/uart.o ./output/syscalls.shakti ./output/crt.o -o ./output/keypad.shakti -static -nostartfiles -lm -lgcc
	@riscv$(XLEN)-unknown-elf-objdump -D ./output/keypad.shakti > ./output/keypad.dump

create_dir:
	@mkdir -p ./output


crt.o: create_dir
	@riscv$(XLEN)-unknown-elf-gcc -march=$(MARCH) -mabi=$(MABI)  -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf -D__ASSEMBLY__=1 -c $(bspinc)/crt.S -o ./output/crt.o

syscalls.shakti:
	@riscv$(XLEN)-unknown-elf-gcc -march=$(MARCH) -mabi=$(MABI)  -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf $(flags) -c $(bsplib)/syscalls.c -o ./output/syscalls.shakti -I$(bspinc)
