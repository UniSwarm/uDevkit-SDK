/**
 * @file rtc.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2023
 *
 * @date January 9, 2023, 05:22 PM
 *
 * @brief Real Time Clock (RTC) low level support driver for udevkit
 */

#ifndef RTC_H
#define RTC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rtc_device.h"

#include <time.h>

int rtc_init(void);

int rtc_setDateTime(const struct tm *dateTime);
int rtc_dateTime(struct tm *dateTime);

#ifdef __cplusplus
}
#endif

#endif  // RTC_H
