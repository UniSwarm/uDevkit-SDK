 /**
 * @file simulator.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date November 3, 2016, 22:44 PM
 *
 * @brief Simulator for debug purpose
 */

#ifndef SIMULATOR_H
#define SIMULATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined (WIN32) || defined (_WIN32)
    #define SIM_WIN

#elif defined (linux) || defined (LINUX) || defined (__linux__) \
   || defined (unix) || defined (UNIX) || defined (__unix__) \
   || defined (__APPLE__)
    #define SIM_UNIX
#endif

#include <stdint.h>
#include <driver/device.h>

#include "simulator_socket.h"
#include "simulator_pthread.h"

#define UNUSED(x) (void)(x)

void simulator_init();
void simulator_end();
void simulator_send(uint16_t moduleId, uint16_t periphId, uint16_t functionId, const char *data, size_t size);
int simulator_recv(uint16_t moduleId, uint16_t periphId, uint16_t functionId, char *data, size_t size);
int simulator_rec_task();

#define archi_init() simulator_init()

#ifdef __cplusplus
}
#endif

#endif // SIMULATOR_H
