# Developing an application on shakti 

Steps: 

* [Load the RTL bitstream to the board](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/doc/board_use.md).
* [Develop the code using shakti-sdk](#software-archietecture).
* [Set up the board](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/doc/board_use.md).
* [Load the code to the board and test](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/doc/board_use.md).


## Software Archietecture

The software architecture of shakti-sdk is broadly divided in to two parts namely,

- `software` 
  * Host the applications/projects designed and developed in shakti-sdk.
  * Any piece of software developed falls under the [software](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/software) repository.
  * An application development wil involve writing high level code and using bsp wrapper calls.

![](https://gitlab.com/shaktiproject/software/shakti-sdk/raw/master/doc/images/arch_sdk.png)

- `bsp`
  * The bsp has a set of low level function calls, board utility macros and core libraries.
  * These functions help to communicate with sensors/peripherals.
  * The core libraries has system calls and assmebly routines to work seamlessly with the core.
  * The bsp is designed in such a way that it is simpler and arduino compatible.

![](https://gitlab.com/shaktiproject/software/shakti-sdk/raw/master/doc/images/bsp.jpg)

**Note**: To develop your own software, you need to understand the file directory structure. <br/>
The file directory structure is under README. And it, briefly states the use of each directory.

### How to write a C program to add 2 numbers ? ###

- Shakti-sdk provides a platform to develop different applications for shakti core.
- Essentially you need to write the code and bsp provides platform supports. There are numerous [examples](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/software/examples) for reference.
- The sdk classifies software into New application and New project.
- Read through ['project devt'](#project-development), if the software is going to use multiple peripherals or a larger project.
- Read through ['application devt'](#developing-a-stand-alone-application) for smaller or single sensor projects.

#### Project development ####


shakti-sdk defines a new project to involve a variety of C and H files. The project is supposed to involve several sensors or/and has a larger memory foot print. Below things are to be done for a new project,

- Create a new directory corresponding to the application name under [projects](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/software/projects).
- Under that directory, create a Makefile for compiling the application. Making corresponding changes in other Makefiles.
- Under that directory, create src and header files for the application.


#### Developing a stand-alone application ####

A newer application is a small program that works with a sensor/peripheral. It essentially means creating two things,

- All changes happens inside one of the [example](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/software/examples) directory.
- The [example](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/software/examples) directory has  a sub directory for each and every peripheral.
- Create a directory for your application. Make sure the directory is under the right sub-directory.
- Create src and header files for the application.
- Create a new makefile for the application. Follow existing examples for reference.
- Make an entry in the existing [Makefile](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/software/examples/Makefile) under examples.
- Make an entry in the Top [Makefile](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/Makefile) for `make clean` command.
- The name of the directory corresponds to the name of the application.
- This name will echo everywhere in the shakti-sdk.
- Do `make list-applns`, this will list applications in shakti-sdk.



### Example program ###

For example if you want to write a hello world program

- The device required is uart. Include uart headers for the program.
- Write your program in [software/examples/uart_applns/](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/software/examples/uart_applns).
- Create a directory called 'hello'.
- Create a .c file and write a program for that.
- Create and edit a Makefile for the program and save.
- Make an entry in the existing [Makefile](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/software/examples) under examples.
![ex1](https://gitlab.com/shaktiproject/software/shakti-sdk/raw/master/doc/images/ex1.jpg)
- Make an entry in the Top [Makefile](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/Makefile) for `make clean` command.
![ex2](https://gitlab.com/shaktiproject/software/shakti-sdk/raw/master/doc/images/ex2.jpg)

E class memory map:

| Sl. No  | Peripheral  | Base Address Start  | Base Address End | 
| ------- | ----------- | ------------------- | ---------------- |
| 1. | Memory (TCM) (128kB)  | 0x80000000  | 0x87FFFFFF | 
| 2. | Debug  | 0x00000010  | 0x0000001F | 
| 3. | PWM 0  | 0x00030000  | 0x000300FF | 
| 4. | PWM 1  | 0x00030100  | 0x000301FF | 
| 5. | PWM 2  | 0x00030200  | 0x000302FF | 
| 6.  | PWM 3  | 0x00030300  | 0x000303FF | 
| 7. | PWM 4  | 0x00030400  | 0x000304FF | 
| 8.  | PWM 5  |  0x00030500 | 0x000305FF | 
| 9.  | SPI 0  | 0x00020000  | 0x000200FF | 
| 10.  | SPI 1  | 0x00020100  | 0x000201FF | 
| 11.  | SPI 2  | 0x00020200  | 0X000202FF | 
| 12.  |  Uart 0 | 0x00011300  | 0x00011340 | 
| 13.  | Uart 1  | 0x00011400  |  0x00011440 |
| 14.  | Uart 2  | 0x00011500  | 0x00011540 | 
| 15.  | Clint  | 0x02000000  | 0x020BFFFF | 
| 16.  | Gpio  | 0x00040200  | 0x000402FF | 
| 17. | Plic  | 0x00040100  | 0x000401FF | 
| 18.  | I2C  | 0x00040000  | 0x000400FF | 
| 19.  | XADC  | 0x00041000  |  0x00041400 |

C class memory map

| Sl. No  | Peripheral  | Base Address Start  | Base Address End |
| ------- | ----------- | ------------------- | ---------------- |
| 1. | Memory (DDR) (128Mb)  | 0x80000000  | 0x87FFFFFF| 
| 2. | Debug  | 0x00000000  | 0x0000000F| 
| 3. | Uart  | 0x00011300  | 0x00011340| 
| 4. | Gpio  | 0x02100000  | 0x021000FF| 
| 5. | I2C  | 0x020C0000  | 0x020C00FF| 
| 6. | Clint  | 0x02000000  | 0x020BFFFF| 
| 7. | Plic  | 0x020D0000  | 0x020D00FF|  

### Video tutorial

Coming soon....

