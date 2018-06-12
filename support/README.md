# Support directory

This directory contains differents level of support. All this support files
are automatically added to your project by differents variables.

## module

A module is a set of functionnalities independant of the processor that you use.

Use :

	MODULES += cmd_line gui

[Advanced documentation and list of modules](module/README.md)

## robot

Robot support is the highest hardware support level for uDevkit-SDK. It includes a board,
mecanical properties and sensors of the robot.

You can only define one robot in your project but it is optionnal. If you
don't use it in your project, you need to define a board.

Use :

	ROBOT = deltatips

[Advanced documentation and list of robots](robot/README.md)

## board

Board support defines an architechture and the processor used. It also map 
inputs and outputs of various devices to the board to the processor.

Use :

	BOARD = rtboard

[Advanced documentation and list of boards](board/README.md)

## archi

Archi support define compiler to use with specific options and low level
architechture dependant code. You need to define the architechture family 
and the complete processor reference.

Use :

	DEVICE = 33EP256MU806
	ARCHI = dspic33ep

[Advanced documentation and list of architechtures](archi/README.md)

## driver

Low level driver dependant or not of the processor.

Use :

	DRIVERS += uart spi timer

[Advanced documentation and list of drivers](driver/README.md)
