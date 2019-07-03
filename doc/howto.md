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
- Essentially you need to write the code and bsp provides platform supports. There are numerous [`examples`](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/software/examples) for reference.
- The sdk classifies software into New application and New project.,
- Read through ['project devt'](#project-development), if the software is going to use multiple peripherals or a larger project.
- Read through ['application devt'](#developing-a-stand-alone-application) for smaller or single sensor projects.

#### Project development ####


shakti-sdk defines a new project to involve a variety of C and H files. The project is supposed to involve several sensors or/and has a larger memory foot print.<br/>
Below things are to be done for a new project,

- Create a new directory corresponding to the application name under [projects](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/software/projects).
- Under that directory, create a Makefile for compiling the application. Making corresponding changes in other Makefiles.
- Under that directory, create src and header files for the application.


#### Developing a stand-alone application ####

A newer application is a small program that works with a sensor/peripheral. It essentially means creating two things,

- All changes happens inside one of the [example](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/software/examples) directory.
- The example directory has  a sub directory for each and every peripheral.
- Create a directory for your application. Make sure the directory is under the right sub-directory.
- Create src and header files for the application.
- Create a new makefile for the application. Follow existing examples for reference.
- Make an entry in the existing Makefile (under https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/software/examples ).
- The name of the directory corresponds to the name of the application.
- This name will echo everywhere in the shakti-sdk.
-  Do `make list-applns` for applications in shakti-sdk.



### Example program ###

For example if you want to write a hello world program

- The device required is uart. Include uart headers for the program.
- Write your program in software/examples/uart_projects/.
- Create a directory called 'hello'.
- Create a .c file and write a program for that.
- Create a Makefile for program.


### Video tutorial

Coming soon....

