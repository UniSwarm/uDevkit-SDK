#ifndef CMD_STDIO_H
#define CMD_STDIO_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define puts(str) cmd_puts((str))
#define printf(format, ...) cmd_printf((format), ##__VA_ARGS__)
#include "cmd.h"

#endif // CMD_STDIO_H
