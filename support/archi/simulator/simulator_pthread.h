/**
 * @file simulator_pthread.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2020
 *
 * @date November 12, 2016, 22:11 PM
 *
 * @brief PThread support for testing purpose (windows and linux cross-platforms)
 *
 * Widely inspired by http://franckh.developpez.com/tutoriels/posix/pthreads/
 */

#ifndef SIMULATOR_PTHREAD_H
#define SIMULATOR_PTHREAD_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(WIN32) || defined(_WIN32)
#    include <windows.h>
#    define psleep(m_sec) Sleep((m_sec))

#elif defined(linux) || defined(LINUX) || defined(__linux__) || defined(unix) || defined(UNIX) || defined(__unix__) || \
    defined(__APPLE__)
#    include <unistd.h>
#    define psleep(m_sec) usleep((m_sec)*1000)

#else
#    error pthread not supported for your platform
#endif

void simulator_pthread_init();

#endif  // SIMULATOR_PTHREAD_H
