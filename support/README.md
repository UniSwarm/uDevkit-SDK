# Support directory

This directory contains different levels of support. All theses support
files are automatically added to your project by different variables.

## module

A module is a set of functionalities independent of the processor that you use.

Usage :

	MODULES += cmd_line gui

[Advanced documentation and list of modules](module/README.md)

## robot

Robot support is the highest hardware support level for uDevkit-SDK. It includes a board,
mechanical properties and sensors of the robot.

You can only define one robot in your project but it is optional. If you
don't use it in your project, you need to define a board.

Usage :

	ROBOT = deltatips

[Advanced documentation and list of robots](robot/README.md)

## board

Board support defines an architecture and the processor used. It also maps
inputs and outputs of various devices to the board to the processor.

Usage :

	BOARD = rtboard

[Advanced documentation and list of boards](board/README.md)

## archi

Archi support define compiler to use with specific options and low level
architecture dependent code. You need to define the architecture family 
and the complete processor reference.

Usage :

	DEVICE = 33EP256MU806
	ARCHI = dspic33ep

[Advanced documentation and list of architectures](archi/README.md)

## driver

Low level driver dependent or not of the processor.

Usage :

	DRIVERS += uart spi timer

[Advanced documentation and list of drivers](driver/README.md)
