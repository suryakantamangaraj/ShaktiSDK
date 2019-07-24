## Guide

  * [Information](#information)
  * [Setting up the sdk](#setting-up-the-shakti-sdk)
  * [Contents of sdk](#contents-of-shakti-sdk)
  * [Developing applications](#developing-applications)
  * [Logging issue](#logging-issue)
  * [Public release](#public-release)
  
## Information ##

* Master branch is the stable one. It has gpio, i2c, timer and uart support.
* Next release is expected to have qspi, spi and plic support.
* This repository is currently under in-house testing.
* Read the documents completely, before starting development.

Read the documents in the following order

1. [README](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/README.md)\( this document\)
2. [board_info](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/doc/board_info.md)
3. [board_use](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/doc/board_use.md)
4. [howto_develop](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/doc/howto_develop.md)
5. [License](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/LICENSE)

## Setting up the shakti-sdk 

### Prerequisites ###

To use this SDK, you will need the following OS and software packages available on your machine:

* OS = Ubuntu 16.04
* To solve software dependencies, copy paste the below command in terminal and press enter.

```
sudo apt-get install autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev libusb-1.0-0-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev device-tree-compiler pkg-config libexpat-dev
```
**note: shakti-sdk is tested in ubuntu 16.04 only.**

### Download the Repository ###

Please open the terminal and run the following commands to clone the repository:

```
git clone --recursive https://gitlab.com/shaktiproject/software/shakti-sdk.git
cd shakti-sdk
```

If you had omitted the `--recursive` option in the above command, you can update the submodules by running the following command:

```
git submodule update --init --recursive
```

### Setting up the toolchain ###
The shakti-sdk uses riscv-tools. The tool chain can be installed in two ways,

* 'Manual method' 
   - Build and install toolchain from [`riscv-tools`](https://gitlab.com/shaktiproject/software/riscv-tools.git).
   - The riscv-tools repository has the readme to install riscv toolchain for shakti-sdk.

* 'Automatic method' 
   - Toolchain executables are already hosted in shakti-sdk as a submodule ([shakti-tools](https://gitlab.com/shaktiproject/software/shakti-tools)).
   - The path to toolchain has to be added to "*PATH*" variable and exported, to use it across every directory in ubuntu. 
   - The steps to export PATH variable is provided below,
     * Assuming you are in shakti-sdk repository. Follow the below commands
        ```
        SHAKTISDK=/complete/path/of/shakti/sdk      --------> (shakti-sdk path in your system)
        export PATH=$PATH:$SHAKTISDK/shakti-tools/bin
        ```

Things to do

* Please add the above two lines in .bashrc file in home folder.

* The `$SHAKTISDK` is the location of `shakti-sdk`.

* The export command will make the PATH to toolchain available across every directory in linux.

* The command *which riscv64-unknown-elf-gcc* helps you to verify whether toolchain path is set correctly.

* If tools were installed manually, the *PATH* variable needs to be exported appropriately.

**Example:**

Automatic method


```
system:~$ pwd
/home/user
system:~$ git clone --recursive https://gitlab.com/shaktiproject/software/shakti-sdk.git
system:~$ cd shakti-sdk
system:~$ pwd
/home/user/shakti-sdk
system:~$ SHAKTISDK=/home/user/shakti-sdk
system:~$ export PATH=$PATH:$SHAKTISDK/shakti-tools/bin
system:~$ which riscv64-unknown-elf-gcc
/home/user/shakti-tools/bin/riscv64-unknown-elf-gcc
```


**Add export commands to .bashrc, save and close the file** <br/>
```
system:~$ gedit .bashrc
```
<img src="https://gitlab.com/shaktiproject/software/shakti-sdk/raw/master/doc/images/bashrc.png" alt="/home/user/.bashrc" width="50%" height="50%">

### Updating SHAKTI-SDK ###

Please follow the below commands, to update the shakti-sdk to the latest version.

```
cd $SHAKTISDK
git pull origin master
git submodule update --init --recursive
```
****

## Developing applications
  
  Shakti-sdk provides a platform to develop standalone applications and projects. Two FPGA development boards are supported for development.
  Please read files under [doc](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/doc) for further details.
  It is highly recommended to read through the rest of the document, before starting development.

## Contents of shakti-sdk

* **board support package** (found under [`bsp/`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/bsp))

  The `bsp` implements the board related software for application development. It includes the following
  - drivers [`bsp/drivers`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/bsp/drivers)
    * Exposes a set of APIs to upper layer.
    * These are low level API's to execute a particular task in the hardware.
    * These API's are usually peripheral specific.
  - include [`bsp/include`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/bsp/include)
    * This has header files for core and drivers.
  - libwrap [`bsp/libwrap`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/bsp/libwrap)
    * list of basic library functions.
  - Third party boards [`bsp/third_party/`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/bsp/third_party)
    * Configuration files and drivers needed to support third party FPGA boards are put in this directory.


* **doc** (found under [`doc/`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/doc))
   The 'doc' contains the following documents,

  - Shakti supported boards [`doc/board_info`](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/doc/board_info.md)
     * README explaining the different boards that shakti supports. 
  - Building new application [`doc/howto_develop`](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/doc/howto_develop.md)
     * README explaining the procedure to develop software using shakti-sdk.
  - How to use the board [`doc/board_use`](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/doc/board_use.md)
     * The procedure to generate the RTL and load the RTL to the board.
     * The procedure to upload an ELF image to the target board.
  
* **software** (found under [`software/`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/software))
  - The `software` houses three repos as below,
    * projects
      - This consists of applications developed using different sensors.
      - These are usually a combination of standalone applications under [`examples`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/software/examples).
      - These standalone applications can be combined to make a project.
    * benchmarking
      - Standalone projects and sub-modules that can be used to benchmark the shakti rtl.
      - These benchmarking repos usually describe the capability of shakti class of processors.
    * examples
      -	This is the place where all standalone applications are hosted.
      - The bsp and core support libraries can be found under [`bsp`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/bsp).
      - Few sensors are already developed for different peripherals and kept under [`examples`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/software/examples).
      - See [`here`](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/doc/howto_develop.md) for a detailed description on application development.

* **shakti-tools** (found under [`shakti-tools/`](https://gitlab.com/shaktiproject/software/shakti-tools))
  - The shakti-tools folder has "ready to use" RISC-V tools.
  - The tools by default support I, M, A, F, D and C.
  - It has RISC-V GNU tool chain, RISC-V instruction set simulator, OpenOCD (debugger) and RISC-V proxy kernel.
  - The tools needs to be exported to PATH variable to use everywhere.
  - Tools can also be installed manually from [`here`](https://gitlab.com/shaktiproject/software/riscv-tools).

* **Makefile** (found under [`./`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/Makefile)).
  - The Makefile has support for different target boards and applications. The supported `make` commands are

    * make help
      - lists the possible commands supported in Makefile.
    * make list_targets
      - list the target boards supported.
    * make list_applns
      - lists the example applns developed.
    * make software PROGRAM=`?` TARGET=`?`
      - PROGRAM can be found from "make list_applns"
      - TARGET= artix7_35t or artix7_100t
      - Default TARGET is artix7_35t
    * make debug PROGRAM=`?` TARGET=`?`
      - PROGRAM can be found from "make list_applns"
      - TARGET= artix7_35t or artix7_100t
      - Default TARGET is artix7_35t
      - debug command adds the debug support to applns.
    * make all
      - TARGET= artix7_35t
      - all the applications are compiled for above target.
    * make clean
      - clean all the executables.
      - The design overrides the executable generated by the last target with current target.
    * make clean CLEAR=?
      - CLEAR?= any application under list_applns
      - clean the executables for an application.
      

## Logging Issue 

Any issue or clarification can be raised under issues. <br/>
Before raising an issue, please check if there are any similar issues.

Please follow the below steps to create an issue.

- Go to [`Issues`](https://gitlab.com/shaktiproject/software/shakti-sdk/issues).
- After clicking on New Issue you will get an option to select a template.
- Click on choose template, list of available templates will be displayed, Select template "Bug".
- Once the template named 'Bug' is selected, the description text box is populated by the template.
- Please fill all the fields in the description textbox.

**Note**: Check [`docs`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/doc) for further information and check [Logging Issue](#logging-issue) section for any clarification.

## Public release

Our sincere thanks to Meity, GoI

![](https://gitlab.com/shaktiproject/software/shakti-sdk/raw/master/doc/images/inaug1.jpg) <br/>
