/**
 * @file simulator_pthread.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2022
 *
 * @date November 12, 2016, 22:11 PM
 *
 * @brief PThread support for testing purpose (windows and linux cross-platforms)
 */

#include "simulator_pthread.h"

#include <stdio.h>

void simulator_pthread_init(void)
{
}

#if defined(WIN32) || defined(_WIN32)
void usleep(__int64 usec)
{
    HANDLE timer;
    LARGE_INTEGER ft;

    ft.QuadPart = -(10 * usec);  // Convert to 100 nanosecond interval, negative value indicates relative time

    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
}
#endif
