 /**
 * @file simulator.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date November 3, 2016, 22:44 PM
 *
 * @brief Simulator for debug purpose
 */

#include "simulator.h"

#include "simulator_socket.h"
#include "simulator_pthread.h"

#include <signal.h>
#include <string.h>
#include <stdio.h>

void simulator_init()
{
    atexit(simulator_end);
    signal(SIGTERM, simulator_end);

    simulator_socket_init();
    simulator_pthread_init();
}

void simulator_end()
{
    simulator_socket_end();
    puts("end simulator execution\n");
}

void simulator_send(uint16_t moduleId, uint16_t functionId, const char *data, size_t size)
{
    char *simDat = malloc(size + 6);
    ((unsigned short*)simDat)[0] = size + 6;
    ((unsigned short*)simDat)[1] = moduleId;
    ((unsigned short*)simDat)[2] = functionId;
    memcpy(simDat+6, data, size);
    simulator_socket_send(simDat, size + 6);
    free(simDat);
}
