
vpath %.c $(MODULEPATH)
vpath %.h $(MODULEPATH)

DRIVERS += uart

HEADER += esp8266.h
SRC += esp8266.c

SRC += fs_functions.c http_parser.c http_formater.c web_server.c json_formater.c
