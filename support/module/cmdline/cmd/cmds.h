/**
 * @file cmds.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date October 10, 2016, 10:44 PM
 *
 * @brief Headers for all commands
 */

#ifndef CMDS_H
#define CMDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "modules.h"

#ifdef USE_adc
int cmd_adc(int argc, char **argv);
#endif
#ifdef USE_ax12
int cmd_ax(int argc, char **argv);
#endif
#ifdef USE_can
int cmd_can(int argc, char **argv);
#endif
#ifdef USE_gpio
int cmd_gpio(int argc, char **argv);
#endif
#ifdef USE_i2c
int cmd_i2c(int argc, char **argv);
#endif
int cmd_led(int argc, char **argv);
#ifdef USE_MODULE_mrobot
int cmd_mrobot(int argc, char **argv);
#endif
int cmd_reg(int argc, char **argv);
#ifdef USE_sysclock
int cmd_sysclock(int argc, char **argv);
#endif
#ifdef USE_timer
int cmd_timer(int argc, char **argv);
#endif
#ifdef USE_uart
int cmd_uart(int argc, char **argv);
#endif

#ifdef __cplusplus
}
#endif

#endif  // CMDS_H
