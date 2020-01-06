SHELL := /bin/bash # Use bash syntax
XLEN=64
MAIN1=./global_interrupts.c
MAIN2=./ld_access_fault

#Define a main file using $MAIN if you want a main function from here or command line
all:
	make nomain.riscv

main.riscv: crt.o syscalls.shakti
	@riscv$(XLEN)-unknown-elf-gcc -w -mcmodel=medany -static -std=gnu99 -fno-builtin-printf  -c -I/scratch/git_repo/c64_intel_release/peripherals/software/Common  $(MAIN1) -o $(MAIN1).o -march=rv$(XLEN)imafd -lm -lgcc
#	@riscv$(XLEN)-unknown-elf-gcc -w -mcmodel=medany -static -std=gnu99 -fno-builtin-printf  -c $(MAIN2) -o $(MAIN2).o -march=rv$(XLEN)imafd -lm -lgcc
	@riscv$(XLEN)-unknown-elf-gcc -T ./link.ld $(MAIN1).o syscalls.shakti crt.o -o main.shakti -static -nostartfiles -lm -lgcc
	@riscv$(XLEN)-unknown-elf-objdump -D main.shakti > main.dump
	@riscv$(XLEN)-unknown-elf-objcopy -O ihex main.shakti output.hex 
	@elf2hex 2 524288 main.shakti 536870912 > code.mem 
	@cut -c1-8 code.mem > code.mem.MSB
	@cut -c9-16 code.mem > code.mem.LSB

nomain.riscv: crt.o syscalls.shakti
	@riscv$(XLEN)-unknown-elf-gcc -march=rv$(XLEN)imafd  -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf -D__ASSEMBLY__=1 -c $(MAIN2).S  -o $(MAIN2).o
	@riscv$(XLEN)-unknown-elf-gcc -T ./link.ld syscalls.shakti crt.o $(MAIN2).o -o main.shakti -static -nostartfiles -lm -lgcc
	@riscv$(XLEN)-unknown-elf-objdump -D main.shakti > main.dump
	@riscv$(XLEN)-unknown-elf-objcopy -S -O ihex main.shakti output.hex 
	@elf2hex 2  524288 main.shakti 536870912 > code.mem 
	@cut -c1-8 code.mem > code.mem.MSB
	@cut -c9-16 code.mem > code.mem.LSB

crt.o:
	@riscv$(XLEN)-unknown-elf-gcc -march=rv$(XLEN)imafd  -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf -D__ASSEMBLY__=1 -c crt.S -o crt.o

syscalls.shakti:
	@riscv$(XLEN)-unknown-elf-gcc -march=rv$(XLEN)imafd  -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf  -c syscalls.c -o syscalls.shakti

clean:
	@rm -rf *.shakti *.o code.mem* *.dump
	@echo "Cleaned"
