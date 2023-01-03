# uDevkit SDK

[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](http://www.gnu.org/licenses/gpl-3.0)
[![Build Status](https://travis-ci.org/UniSwarm/uDevkit-SDK.svg?branch=master)](https://travis-ci.org/UniSwarm/uDevkit-SDK)
[![Build status](https://ci.appveyor.com/api/projects/status/705wh874ftky5mx9?svg=true)](https://ci.appveyor.com/project/sebcaux/udevkit-sdk)

Embedded systems SDK for Uniswarm boards and others (dsPIC33, dsPIC30, PIC24 and PIC32 compatible) https://uniswarm.eu/udevkit

Currently works for all 16 bits and 32 bits Microchip devices (1087 devices on January 2023):

|Range|Famillies|Device count|
|-----|---------|-----------:|
|[Microchip 16bits](support/archi/pic16b/README.md)|[dsPIC30F](support/archi/dspic30f/README.md), [dsPIC33CH](support/archi/dspic33ch/README.md), [dsPIC33CK](support/archi/dspic33ck/README.md), [dsPIC33EP](support/archi/dspic33ep/README.md), [dsPIC33EV](support/archi/dspic33ev/README.md), [dsPIC33FJ](support/archi/dspic33fj/README.md), [PIC24EP](support/archi/pic24ep/README.md), [PIC24F](support/archi/pic24f/README.md), [PIC24FJ](support/archi/pic24fj/README.md) and [PIC24HJ](support/archi/pic24hj/README.md)|771|
|[Microchip 32bits](support/archi/pic32/README.md)|[PIC32MM](support/archi/pic32mm/README.md), [PIC32MK](support/archi/pic32mk/README.md), [PIC32MX](support/archi/pic32mx/README.md), [PIC32MZDA](support/archi/pic32mzda/README.md), [PIC32MZEC](support/archi/pic32mzec/README.md) and [PIC32MZEF](support/archi/pic32mzef/README.md)|316|

## How to use ?
uDevkit want to be very easy to use with no non-standard system. To manage your
project, it is simply based on a single Makefile.

Makefile example content :

```Makefile
UDEVKIT = /home/toto/uDevkit-sdk # path to uDevkit root directory

PROJECT = myproject              # project name
ROBOT = deltatips                # robot to use (or BOARD= if you want to choose only a board)
OUT_PWD = build                  # output directory

DRIVERS += uart ax12 i2c usb_serial
MODULES += cmdline mrobot

SRC += main.c

include $(UDEVKIT)/udevkit.mk
```

To build and program your board, simply launch :

```bash
make prog
```

[Complete list of drivers](support/driver/README.md)

[Complete list of boards](support/board/README.md)

[Complete list of modules](support/module/README.md)

An IDE named uDevkit-IDE is available : https://github.com/UniSwarm/uDevkit-IDE

## Prepare repository

To get all submodule used (USB), please do not forget to init and update submodule :

```bash
git submodule init
git submodule update
```

## dependencies

### Qt > 5.2

GUI tools are based on Qt like RTsim or img2raw. https://www.qt.io/

### MPLAB X IDE

To program and debug the device (only IPE is needed to program)

* windows : http://www.microchip.com/mplabx-ide-windows-installer
* linux : http://www.microchip.com/mplabx-ide-linux-installer

### XC16 compiler

Compiler for 16-bit devices (v1.26 minimum)

* windows : http://www.microchip.com/mplabxc16windows
* linux : http://www.microchip.com/mplabxc16linux

### XC32 compiler

Compiler for 32-bit devices (v1.30 minimum)

* windows : http://www.microchip.com/mplabxc32windows
* linux : http://www.microchip.com/mplabxc32linux

### default Windows PATHs

* C:\\Program Files (x86)\\Microchip\\xc16\\v1.26\\bin
* C:\\Program Files (x86)\\Microchip\\MPLABX\\v3.45\\mplab_ipe
