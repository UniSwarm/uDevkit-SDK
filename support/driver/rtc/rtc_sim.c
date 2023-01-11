/**
 * @file rtc_sim.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2023
 *
 * @date January 11, 2023, 11:09 AM
 *
 * @brief RTC support for uDevKit SDK simulator
 */

#include "rtc.h"

#include <string.h>

static time_t _rtc_timestamp = 0;

int rtc_init(void)
{
#if RTC_COUNT >= 1
    _rtc_timestamp = time(NULL);

    return 0;
#else
    return -1;
#endif
}

int rtc_setDateTime(const struct tm *dateTime)
{
#if RTC_COUNT >= 1
    struct tm dateTimeLocal;
    memcpy(&dateTimeLocal, dateTime, sizeof(struct tm));
    _rtc_timestamp = time(NULL) - mktime(&dateTimeLocal);
    return 0;
#else
    return -1;
#endif
}

int rtc_dateTime(struct tm *dateTime)
{
#if RTC_COUNT >= 1
    time_t timestamp = time(NULL) - _rtc_timestamp;
    struct tm *timeInfos = localtime(&timestamp);
    memcpy(dateTime, timeInfos, sizeof(struct tm));
    return 0;
#else
    return -1;
#endif
}
