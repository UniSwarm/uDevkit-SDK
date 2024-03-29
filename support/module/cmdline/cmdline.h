/**
 * @file cmdline.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date October 10, 2016, 10:44 PM
 *
 * @brief Base implementation for cmdline module
 */

#ifndef CMDLINE_H
#define CMDLINE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <driver/device.h>

void cmdline_init(void);
void cmdline_setDevice(rt_dev_t deviceIn, rt_dev_t deviceOut);
void cmdline_task(void);

int cmdline_addCommand(const char name[10], int (*cmdFnPtr)(int, char **));

#ifdef __cplusplus
}
#endif

#endif  // CMDLINE_H
