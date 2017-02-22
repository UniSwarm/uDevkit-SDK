# Sensor RTProg module

This module contains sensor management and sensor drivers.

To use it, include the support in your Makefile by adding:

    MODULES += sensor

To include sensor driver interface, add it with :

    SENSOR_DRIVERS = sharp

Available driver list :

|name|description|
|----|-----------|
|sharp|infrared distance sensor with analog interface|
|a6   |RS485 wired protocol|
