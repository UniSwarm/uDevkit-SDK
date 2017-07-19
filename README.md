# RTprog {#mainpage}

[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](http://www.gnu.org/licenses/gpl-3.0)
[![Build Status](https://travis-ci.org/Robotips/rtprog.svg?branch=master)](https://travis-ci.org/Robotips/rtprog)
[![Build status](https://ci.appveyor.com/api/projects/status/yn3whlps1s3vy4ok?svg=true)](https://ci.appveyor.com/project/sebcaux/rtprog)

A tool to simplify module inclusions in embedded systems.

Currently works for all 16 bits and 32 bits Microchip devices (792 devices):

|Range|Famillies|List of devices|Device count|
|-----|---------|---------------|------------|
|Microchip 16bits|dsPIC30F, dsPIC33FJ, dsPIC33EP, dsPIC33EV, PIC24F, PIC24FJ, PIC24EP and PIC24HJ|[list](support/archi/pic16b/README.md)|517|
|Microchip 32bits|PIC32MM, PIC32MK, PIC32MX, PIC32MZDA, PIC32MZEC and PIC32MZEF|[list](support/archi/pic32/README.md)|275|

## How to use ?
RTprog want to be very easy to use with no non-standard system. To manage your
project, it is simply based on a single Makefile.

Makefile example content :

```Makefile
RTPROG = /home/toto/rtprog      # path to rtprog root directory

PROJECT = deltaApp              # project name
ROBOT = deltatips               # robot to use (or BOARD= if you want to choose only a board)
OUT_PWD = build                 # output directory

DRIVERS += uart ax12 i2c usb_serial
MODULES += cmdline mrobot

SRC += main.c

include $(RTPROG)/rtprog.mk
```

[Complete list of drivers](support/driver/README.md)

[Complete list of modules](support/module/README.md)

## Prepare repository

To get all submodule used (USB and FatFS), please do not forget to init and update submodule :

```bash
git submodule init
git submodule update
```

## dependencies
### Qt > 5.2
GUI tools are based on Qt like RTsim or img2raw. https://www.qt.io/

### MPLAB X IDE (to program Microchip devices with debugger)
To program and debug the device (only IPE is needed to program)

* windows : http://www.microchip.com/mplabx-ide-windows-installer
* linux : http://www.microchip.com/mplabx-ide-linux-installer

### XC16 compiler (gcc for Microchip 16 bits devices)
Compiler for 16-bit devices (v1.26 minimum)

* windows : http://www.microchip.com/mplabxc16windows
* linux : http://www.microchip.com/mplabxc16linux

### XC32 compiler (gcc for Microchip 32 bits devices)
Compiler for 32-bit devices (v1.30 minimum)

* windows : http://www.microchip.com/mplabxc32windows
* linux : http://www.microchip.com/mplabxc32linux

### default Windows PATHs
C:\\Program Files (x86)\\Microchip\\xc16\\v1.26\\bin

C:\\Program Files (x86)\\Microchip\\MPLABX\\v3.45\\mplab_ipe
