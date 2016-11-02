# RTprog
A tool to simplify module inclusions in embedded systems.

Currently works for all 16 bits Microchip devices (608 devices including
dsPIC30F, dsPIC33FJ, dsPIC33EP, dsPIC33EV, PIC24F, PIC24FJ, PIC24EP and PIC24HJ).
[Complete list of 16bits devices](support/archi/pic16b/README.md)

Porting to all 32 bits devices in fews weeks (254 devices including
PIC32MM, PIC32MX, PIC32MZEC and PIC32MZEF).
[Complete list of 32bits devices](support/archi/pic32/README.md)

## How to use ?
RTprog want to be very easy to use with no non-standard system. To manage your
project, it is simply based on a single Makefile.

Makefile example content :

	RTPROG = /home/toto/rtprog      # path to rtprog root directory
	
	PROJECT = deltaApp              # project name
	ROBOT = deltatips               # robot to use (or BOARD= if you want to choose only a board)
	OUT_PWD = build                 # output directory
	
	DRIVERS += uart ax12 asserv i2c usb_serial
	MODULES += cmdline
	
	SRC += main.c
	
	include $(RTPROG)/rtprog.mk


## To compile Tools
	make tools

## dependencies
### MPLAB
To program and debug the device

* windows : http://www.microchip.com/mplabx-ide-windows-installer
* linux : http://www.microchip.com/mplabx-ide-linux-installer

### XC16 compiler (for 16 bits devices)
Compiler for 16-bit devices (v1.26 minimum)

* windows : http://www.microchip.com/mplabxc16windows
* linux : http://www.microchip.com/mplabxc16linux

### XC32 compiler (for 32 bits devices)
Compiler for 32-bit devices (v1.30 minimum)

* windows : http://www.microchip.com/mplabxc32windows
* linux : http://www.microchip.com/mplabxc32linux

### default Windows PATHs
C:\Program Files (x86)\Microchip\xc16\v1.26\bin

C:\Program Files (x86)\Microchip\MPLABX\v3.45\mplab_ipe
