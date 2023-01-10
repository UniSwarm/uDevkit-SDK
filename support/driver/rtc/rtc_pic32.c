/**
 * @file rtc_pic32.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2023
 *
 * @date January 9, 2023, 06:02 PM
 *
 * @brief RTC driver support for PIC32MK, PIC32MX, PIC32MZDA,
 * PIC32MZEC and PIC32MZEF
 *
 * Implementation based on Microchip document DS61125F :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/61125F.pdf
 */

#include "rtc_pic32.h"

#include <archi.h>

#include <time.h>

#if RTC_COUNT >= 1
static uint32_t _rtc_dectobcd(uint8_t dec);
uint32_t _rtc_dateToHw(const struct tm *dateTime);
uint32_t _rtc_timeToHw(const struct tm *dateTime);

static uint8_t _rtc_bcdtodec(uint32_t bcd);
void _rtc_hwToDate(uint32_t hwDate, struct tm *dateTime);
void _rtc_hwToTime(uint32_t hwTime, struct tm *dateTime);
#endif

#if RTC_COUNT >= 1
uint32_t _rtc_dectobcd(uint8_t dec)
{
    uint8_t tenth = dec / 10;
    return (tenth << 4) + (dec - tenth * 10);
}

uint32_t _rtc_dateToHw(const struct tm *dateTime)
{
    uint32_t hwDate = _rtc_dectobcd(dateTime->tm_wday);
    hwDate += _rtc_dectobcd(dateTime->tm_mday) << 8;
    hwDate += _rtc_dectobcd(dateTime->tm_mon) << 16;
    hwDate += _rtc_dectobcd(dateTime->tm_year - 100) << 24;
    return hwDate;
}

uint32_t _rtc_timeToHw(const struct tm *dateTime)
{
    uint32_t hwTime = 0;
    hwTime += _rtc_dectobcd(dateTime->tm_sec) << 8;
    hwTime += _rtc_dectobcd(dateTime->tm_min) << 16;
    hwTime += _rtc_dectobcd(dateTime->tm_hour) << 24;
    return hwTime;
}

uint8_t _rtc_bcdtodec(uint32_t bcd)
{
    return ((bcd & 0xF0) >> 4) * 10 + (bcd & 0x0F);
}

void _rtc_hwToDate(uint32_t hwDate, struct tm *dateTime)
{
    dateTime->tm_wday = _rtc_bcdtodec(hwDate);
    dateTime->tm_mday = _rtc_bcdtodec(hwDate >> 8);
    dateTime->tm_mon = _rtc_bcdtodec(hwDate >> 16);
    dateTime->tm_year = _rtc_bcdtodec(hwDate >> 24) + 100;
}

void _rtc_hwToTime(uint32_t hwTime, struct tm *dateTime)
{
    dateTime->tm_sec = _rtc_bcdtodec(hwTime >> 8);
    dateTime->tm_min = _rtc_bcdtodec(hwTime >> 16);
    dateTime->tm_hour = _rtc_bcdtodec(hwTime >> 24);
}
#endif

int rtc_init(void)
{
#if RTC_COUNT >= 1
    unlockConfig();
    RTCCONbits.RTCWREN = 1;  // Enable writes to RTCC
    lockConfig();

    RTCCONbits.RTCOE = 0;  // Disable RTCC output

    // Set RTCC clock source (LPRC/SOSC)
    RTCCONbits.RTCCLKSEL = 0b01;

    // start the RTC
    RTCCONbits.ON = 1;

    return 0;
#else
    return -1;
#endif
}

int rtc_setDateTime(const struct tm *dateTime)
{
#if RTC_COUNT >= 1
    if (RTCCONbits.RTCCLKON == 0)  // RTC is not running
    {
        return -1;
    }
    uint32_t hwDate = _rtc_dateToHw(dateTime);
    uint32_t hwTime = _rtc_timeToHw(dateTime);
    disable_interrupt();
    while (RTCCONbits.RTCSYNC == 1)
        ;
    RTCDATE = hwDate;
    RTCTIME = hwTime;
    enable_interrupt();
    return 0;
#else
    return -1;
#endif
}

int rtc_dateTime(struct tm *dateTime)
{
#if RTC_COUNT >= 1
    if (RTCCONbits.RTCCLKON == 0)  // RTC is not running
    {
        return -1;
    }
    _rtc_hwToDate(RTCDATE, dateTime);
    _rtc_hwToTime(RTCTIME, dateTime);

    dateTime->tm_yday = 0;
    dateTime->tm_isdst = 0;
    return 0;
#else
    return -1;
#endif
}
