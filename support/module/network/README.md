# Network RTProg module

This module contains network utilities and network interface drivers.

To use it, include the support in your Makefile by adding:

    MODULES += network

To include network driver interface, add it with :

    NETWORK_DRIVERS = esp8266

Available driver list :

|name|description|
|----|-----------|
|esp8266| wifi module with TCP/IP stack|
|a6     | RS485 wired protocol|
