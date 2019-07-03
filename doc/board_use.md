## Board setup 

The below steps need to be followed to setup the board.

1. Generating the RTL bitstream for a particular class of shakti processor and loading it to the board.
2. Connecting the JTAG module to the board and settint up the wiring for the application.
3. Compiling the application for the corresponding class of processor and running it.

### Set up board with RTL bitstream ###

* Generate and load the RTL bitstream for E class on artix7 35T from [here](https://gitlab.com/shaktiproject/cores/shakti-soc/tree/12-eclass-on-35t/fpga/boards/artya7-35t/e-class).
* Generate and load the RTL bitstream for C class on artix7 100T from [here](https://gitlab.com/shaktiproject/cores/shakti-soc/tree/master/fpga/boards/artya7-100t/c-class).

### JTAG-Board connection ###

Currently the artix7* build only supports booting in debug mode. On reset the, the core will start executing the infinite debug-loop at 0x00000000.<br />
The board has to be used along with a [`debugger version 10.1 part no 8.08.90`](https://www.segger.com/products/debug-probes/j-link/models/j-link-edu/).

![](https://gitlab.com/shaktiproject/software/shakti-sdk/raw/master/doc/images/connections.jpg)

    
#### Accessories & Wires ####

* Connect neccessories sensors to devices on SoC.
* The pin mapping for GPIO, I2C  and other devices geven below. (Coming soon)

### Software image

Please compile the application image for the corresponding board. <br />
Please check [here](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/doc/howto.md) for application development.

## Connecting to the board

After setting up the board with RTL bitstream loaded, please follow the below procedure.

Pre-requisites:

* sudo apt-get install python-serial

* There will be three terminals required. 
  - One terminal for openocd.
  - Another for gdb server
  - And the last one for uart terminal display.

Follow the steps below to set up and run programs

* Open a terminal and launch OpenOCD with sudo permissions.
  Assume you are in the shakti-sdk directory.

        $ cd ./bsp/third_party/artix7_35t
        $ sudo openocd -f spike.cfg

* Open another terminal and launch gdb

        $ riscv64-unknown-elf-gdb -x gdb.script
        $ file "executable with absolute path"
        $ load
        $ c

* Open another terminal to capture UART output (The default baud rate is 19200)

        $ sudo miniterm.py /dev/ttyUSB1 240000

For UART, we need miniterm or GTKterm.
