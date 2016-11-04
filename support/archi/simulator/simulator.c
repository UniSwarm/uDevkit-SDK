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

#include <signal.h>
#include <string.h>

void simulator_init()
{
    atexit(simulator_end);
    signal(SIGTERM, simulator_end);
    signal(SIGKILL, simulator_end);

    simulator_socket_init();
}

void simulator_end()
{
    simulator_socket_end();
    puts("end simulator execution\n");
    exit(0);
}

void simulator_send(uint16_t moduleId, uint16_t functionId, const char *data, size_t size)
{
    char *simDat = malloc(size + 4);
    ((unsigned short*)simDat)[0] = moduleId;
    ((unsigned short*)simDat)[1] = functionId;
    memcpy(simDat+4, data, size);
    simulator_socket_send(simDat, size + 4);
    free(simDat);
}
