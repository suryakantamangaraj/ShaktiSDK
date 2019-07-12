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
* The pin mapping for GPIO, I2C  and other devices geven below.

1. Artix7_100T pin - board details

| s. no | pin description | artix7_100T pin mapping | remarks | peripheral |
| ------ | ----------------------- | ------------------------ | ------- | ---------- |
| 1. | GPIO0 | CKIO0 (J4[1],IO - Lower) | Arduino Header (ChipKit Outer Digital Header) | General Purpose Input/Output pins |
|  |GPIO1  |CKIO1 (J4[3],IO - Lower)| |  |
|  |GPIO2  |CIIO2 (J4[5],IO - Lower)| |  |
| |GPIO3  |CKIO3 (J4[7],IO - Lower)| |  |
| |GPIO4  |CKIO4 (J4[9],IO - Lower)| |  |
| |GPIO5 |CKIO5 (J4[11],IO - Lower)| |  |
| |GPIO6  |CKIO6 (J4[13],IO - Lower)| |  |
| |GPIO7  |CKIO7 (J4[15],IO - Lower)| |  |
| |GPIO8  |CKIO8 (J2[1],IO - Higher)| |  |
| |GPIO9  |CKIO9 (J2[3],IO - Higher)| |  |
| |GPIO10  |CKIO10 (J2[5],IO - Higher)| |  |
| |GPIO11  |CKIO11 (J2[7],IO - Higher)| |  |
| |GPIO12  |CKIO12 (J2[9],IO - Higher)| |  |
| |GPIO13  |CKIO13 (J2[11],IO - Higher)| |  |
| |GPIO14|CKIO26 (J4[2],IO - Lower) || |
| |GPIO15  |CKIO27 (J4[4],IO - Lower)| |  |
|2.|SDA  |CK|_SDA (J3[1] )  |J3|I2C  |
| |SCL  |CK|_SCL (J3[2])| |  |
|3.|TRST  |JA[4]  |PMOD Connector (JA)|JLINK JTAG - OPENOCD|
| |TDI  |JA[2]| |  |
| |TMS  |JA[1]| |  |
| |TCK  |JA[8]| |  |
| |TDO  |JA[7]| |  |
| |Vcc  |JA[6]| |  |
| |Gnd  |JA[5]| |  |
|4.|UART0 TX  |J10  |Digilent JTAG USB circuitry |UART |
| |UART0 RX  |J10| |  |
|5.|INTERRUPT 0  |CKIO28 (J4[6],IO - Lower)|Arduino Header (ChipKit Outer Digital Header) |Interrupts|
| |INTERRUPT 1  |CKIO29 (J4[8],IO - Lower)| |  |
| |INTERRUPT 2  |CKIO30 (J4[10],IO - Lower)| |  |
| |INTERRUPT 3  |CKIO31 (J4[12],IO - Lower)| |  |
| |INTERRUPT 4|CKIO32 (J4[14],IO - Lower) || |
| |INTERRUPT 5  |CKIO33 (J4[16],IO - Lower)| |  |
| |INTERRUPT 6 |CKIO34 (J2[2],IO - Lower)| |  |
| |INTERRUPT 7  |CKIO35 (J2[4],IO - Lower)| |  |
 

2. Artix7_35T pin - board details


| s. no | pin description | artix7_35T pin mapping | remarks | peripheral |
| ----- | ------------------------ | ------------------------ | -------- | ---------- |
| 1. |  GPIO0 | CKIO0 (J4[1],IO - Lower)  |  Arduino Header (ChipKit Outer Digital Header) |  General Purpose Input/Output pins |  
|  | GPIO1  | CKIO1 (J4[3],IO - Lower)  |   |   |  
|  | GPIO2  | CIIO2 (J4[5],IO - Lower)  |   |   |  
|  | GPIO3  | CKIO3 (J4[7],IO - Lower)  |   |   |  
|  | GPIO4  | CKIO4 (J4[9],IO - Lower)  |   |   |  
|  | GPIO5  | CKIO5 (J4[11],IO - Lower)  |   |   |  
|  | GPIO6  |  CKIO6 (J4[13],IO - Lower) |   |   |  
|  | GPIO7  |  CKIO7 (J4[15],IO - Lower) |   |   |  
|  | GPIO8  | CKIO8 (J2[1],IO - Higher)  |   |   |  
|  | GPIO9  | CKIO9 (J2[3],IO - Higher)  |   |   |  
|  | GPIO10  | CKIO10 (J2[5],IO - Higher)  |   |   |  
|  | GPIO11  |  CKIO11 (J2[7],IO - Higher) |   |   |  
|  | GPIO12  | CKIO12 (J2[9],IO - Higher)  |   |   |  
|  | GPIO13  | CKIO13 (J2[11],IO - Higher)  |   |   |  
|  | GPIO14  | CKIO26 (J4[2],IO - Lower)  |   |   |  
|  | GPIO15  | CKIO27 (J4[4],IO - Lower)  |   |   |  
| 2. | SDA  | CK\_SDA (J3[1] )  |  J3 |  I2C|  
|  | SCL  | CK\_SCL (J3[2])  |   |   |  
| 3.| TRST  | JA[4]  | PMOD Connector(JA) | JLINK JTAG -OPENOCD|  
|  | TDI  | JA[2]  |   |   |  
|  | TMS  | JA[1]  |   |   |  
|  |  TCK |  JA[8] |   |   |  
|  | TDO  | JA[7]  |   |   |  
| |Vcc  |JA[6]| |  |   |   |
| |Gnd  |JA[5]| |  |   |   |
|4.| UART0 TX  | J10  | Diligent JTAG USB circuitary  | UART |  
|  | UART0 RX  |  J10 |   |   |  
|5.|  UART1 TX |  JC[7] - 3P | UART1  |   |  
|  |  UART1 RX | JC[8] - 3N  |   |   |  
|6.| UART2 TX  | JC[9] - 4P  | UART2  |   |  
|  | UART2 RX  | JC[10] - 4N  |   |   |  
|7. |  INTERRUPT 0 | CKIO28 (J4[6],IO - Lower)  | Arduino Header (ChipKit Outer Digital Header) | Interrupts  |  
|  | INTERRUPT 1  | CKIO29 (J4[8],IO - Lower)  |   |   |  
| 8.| ADC 4  | CKA0  |  Single Ended ADCs| ADC  |  
|  | ADC 5  | CK A1  |   |   |  
|  | ADC 6  | CK A2  |   |   |  
|  | ADC 7  | CK A3  |   |   |  
|  |  ADC 15 | CK A4  |   |   |  
|  | ADC 0  |  CK A5 |   |   |  
|9.| ADC 12P  | CK A6  | Differential ADCs|   |  
|  | ADC 12N  | CK A7  |   |   |  
|10.| ADC 13P  | CK A8  |   |   |  
|  | ADC 13N  | CK A9  |   |   |  
|11.| ADC 14P  |  CK A10 |   |   |  
|  | ADC 14N  | CK A11|   |   |  
|12.| PWM 0  | JD[1]  | PULSE WIDTH MODULATION PINS  |  PWM PINS  |  
|  | PWM 1  | JD[2]  |   |   |  
|  | PWM 2  |  JD[3] |   |   |  
|  | PWM 3  |  JD[4] |   |   |  
|  | PWM 4  |   JD[7] |   |   |  
|  | PWM 5  |  JD[8] |   |   |  
|13.| SPI0 CS  | JB[1] - 1P  | SPI0  |   |  
|  | SPI0 SCLK  | JB[2] - 1N  |   |   |  
|  | SPI0 MISO  | JB[3] - 2P  |   |   |  
|  | SPI0 MOSI  | JB[4] - 2N  |   |   |  
|14.| SPI1 CS  | JB[7] - 3P  | SPI1  |   |  
|  | SPI1 SCLK  | JB[8] - 3N  |   |   |  
|  | SPI1 MISO  | JB[9] - 4P  |   |   |  
|  | SPI1 MOSI  | JB[10] - 4N  |   |   |  
|15.| SPI2 CS  | JC[1] - 1P  | SPI2  |   |  
|  | SPI2 SCLK  | JC[2] - 1N  |   |   |  
|  | SPI2 MISO  | JC[3] - 2P  |   |   |  
|  | SPI2 MOSI  | JC[4] - 2N  |   |   |  

### Software image

Please compile the application image for the corresponding board. <br />
Please check [here](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/doc/howto.md) for application development.

## Connecting to the board

After setting up the board with RTL bitstream loaded, please follow the below procedure.

Pre-requisites:

* sudo apt-get install python-serial

* Open three terminals, one for each of the following

  - One terminal for openocd.
  - Another for gdb server
  - And the last one for uart terminal display.

Follow the steps below to set up and run programs

* In the first terminal launch OpenOCD with sudo permission. Please ensure you are in the shakti-sdk directory.

For example,

        $ pwd
        /home/user/shakti-sdk

Running openocd:
```
        $ cd ./bsp/third_party/artix7_35t
        $ sudo openocd -f spike.cfg
```
* In the second terminal launch gdb. Applications will be loaded to memory in FPGA board and run in this terminal.

``` 
        $ riscv64-unknown-elf-gdb -x gdb.script
        $ file "executable with absolute path"
        $ load
        $ c
```
* In the third terminal open miniterm.py to display output from UART
```
        $ sudo miniterm.py /dev/ttyUSB1 19200
```
note: 
    1. For 32 bit applications, please use riscv32-unknown-elf-gdb
    2. To install miniterm.py, run sudo apt-get install pyserial in terminal.