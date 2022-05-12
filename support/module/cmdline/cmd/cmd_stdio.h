/**
 * @file cmd_stdio.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2022
 *
 * @date October 28, 2016, 11:44 PM
 *
 * @brief Helpers to print commands
 */

#ifndef CMD_STDIO_H
#define CMD_STDIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define puts(str)           cmd_puts((str))
#define printf(format, ...) cmd_printf((format), ##__VA_ARGS__)
#include "cmd.h"

#ifdef __cplusplus
}
#endif

#endif  // CMD_STDIO_H
