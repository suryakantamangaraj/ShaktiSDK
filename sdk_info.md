## Guide
  * [Information](#information)
  * [Setting up the sdk](#setting-up-the-shakti-sdk)
  * [Contents of sdk](#contents-of-shakti-sdk)
  * [Logging issue](#logging-issue)
  
## Information ##

* Master branch is the stable one. It has gpio, i2c, timer and uart support.
* Next release is expected to have qspi, spi and plic support.
* This repository is currently under inhouse testing.

## Setting up the shakti-sdk 

### Prerequisites ###

To use this SDK, you will need the following OS/software available on your machine:

* OS = Ubuntu 16.04
* sudo apt-get install autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev libusb-1.0-0-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev device-tree-compiler pkg-config libexpat-dev

note: SDK is tested in ubuntu 16.04 alone. We are not sure about the risc v toolchain behavior in ubuntu 18. 

### Download the Repository ###

This repository can be cloned by running the following commands:

```
git clone --recursive https://gitlab.com/shaktiproject/software/shakti-sdk.git
cd shakti-sdk
```

The `--recursive` option is required to clone the git submodules included in the
repository. If at first you omit the `--recursive` option, you can achieve
the same effect by updating submodules using the command:

```
git submodule update --init --recursive
```

### Setting up the toolchain ###
The shakti-sdk uses riscv-tools. The tool chain can be installed in two ways,

* 'Manual' Toolchain can be downloaded from [`here`](https://gitlab.com/shaktiproject/software/riscv-tools.git) and installed.
* 'Automatic' Toolchain executables are already found at [`shakti-tools/`](https://gitlab.com/shaktiproject/software/shakti-tools). Export them to *PATH* and use.

#### Exporting the tool chain ####
Export the tool chain to the `PATH` variable. This will help in using the toolchain everywhere in linux.

```
export PATH=$PATH:$PWD/shakti-tools/bin
```

Things to do

* Please put the above line in bashrc

* The $PWD is the location of top folder (i.e. `shakti-sdk/`) in this repository.

* The command *which riscv64-unknown-elf-gcc* helps you to verify the export of toolchain.

* If tools were installed manually, the *PATH* variable needs to be exported appropriately.

### Updating your SDK ###

If you'd like to update your SDK to the latest version:

```
git pull origin master
git submodule update --init --recursive
```
****
## Contents of shakti-sdk
  
* software (found under [`software/`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/software))
  - The `software` houses three repos as below,
    * projects
      - This consists of applications developed using different sensors.
      - These are usually a combination of standalone applns under [`examples`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/software/examples).
    * benchmarking
      - Standalone projects and sub-modules that can be used to benchmark the shakti rtl.
      - These benchmarking repos usually describe the capabiity of shakti class of processors.
    * examples
      -	This is the place where any new standalone application is built.
      - The bsp and core support libraries can be found under [`bsp`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/bsp).
      - Few sensors are already developed for different peripherals and kept under [`examples`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/software/examples).
      - See [`here`](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/doc/howto.md) for a detail description on application development.

* board support package (found under [`bsp/`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/bsp))

  The `bsp` implements the board related softwares for application developement. It includes the following
  - drivers [`bsp/drivers`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/bsp/drivers)
    * Exposes a set of wrapper APIs to upper layer. 
    * These are low level API's to execute a particular task in the hardware.
    * These API's are usually peripheral specific.
  - include[`bsp/include`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/bsp/include)
    * This has header files for core and drivers.
  - libwrap [`bsp/libwrap`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/bsp/libwrap)
    * list of basic library functions.
  - Third party boards [`bsp/third_party/`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/bsp/third_party)
    * List of FPGA boards shakti supports.

* doc (found under [`doc/`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/doc))
  - Shakti supported boards [`doc/board_info`](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/doc/board_info.md)
     * README explaining the different boards that shakti supports. 
  - Building new application [`doc/howto`](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/doc/howto.md)
     * README explaining the procedure to develop software using shakti-sdk.
  - How to use the board [`doc/board_use`](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/doc/board_use.md)
     * The procedure to generte the rtl and load the rtl to board.
     * The procedure to upload an elf image to target boards.

* tools (found under [`shakti-tools/`](https://gitlab.com/shaktiproject/software/shakti-tools))
  - The tools folder has "ready to use" riscv tools.
  - It has a risc-v gnu tool chain, risc-v intruction set simulator, openocd (debugger) and riscv proxy kernel.
  - The tools needs to be exported for use.
  - Tools can be installed manually from [`here`](https://gitlab.com/shaktiproject/software/riscv-tools).

* Makefile (found under [`./`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/Makefile)).
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
      - clean the executables for a application.
      
* gdb.script (found under ./)
  - This has the scripts to be used along with the gdb server . See [`here`](https://gitlab.com/shaktiproject/software/shakti-sdk/blob/master/doc/board_use.md) for further details.


## Logging Issue 

Any issue or clarification can be raised under issues. <br/>
Before raising an issue, please check if there are any similar issues.

Please follow the below steps to create a issue.

- Go to [`issues`](https://gitlab.com/shaktiproject/software/shakti-sdk/issues).
- After clicking on New Issue you will get an option to select a template.
- Click on choose template, list of available templates will be displayed, Select template "Bug".
- Once the template Bug is selected, empty template is populated in the description field.
- Please fill all the fields in the description.

**Note**: Check [`docs`](https://gitlab.com/shaktiproject/software/shakti-sdk/tree/master/doc) for further information and check [Logging Issue](#logging-issue) section for any clarification.