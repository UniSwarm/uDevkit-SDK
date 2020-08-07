 /**
 * @file simulator.cpp
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
#include <stdio.h>
#include <string.h>

#include <map>
#include <queue>
#include <vector>
#include <iostream>

static std::map<uint64_t, std::queue<std::vector<char>> > packages;

void simulator_init()
{
    atexit(simulator_end);
    setbuf(stdout, NULL);
    //signal(SIGTERM, simulator_end);

    simulator_socket_init();
    simulator_pthread_init();
}

void simulator_end()
{
    simulator_socket_end();
    puts("end simulator execution\n");
}

void simulator_send(uint16_t moduleId, uint16_t periphId, uint16_t functionId, const char *data, size_t size)
{
    char *simDat = (char*)malloc(size + 8);
    ((unsigned short*)simDat)[0] = size + 8;
    ((unsigned short*)simDat)[1] = moduleId;
    ((unsigned short*)simDat)[2] = periphId;
    ((unsigned short*)simDat)[3] = functionId;
    memcpy(simDat + 8, data, size);
    simulator_socket_send(simDat, size + 8);
    free(simDat);
}

int simulator_rec_task()
{
    char data[2048];
    uint16_t sizePacket, moduleId, periphId, functionId;
    ssize_t size;
    
    // TODO debug this for multiple packet at the same time
    while ((size = simulator_socket_read(data, 2048)) >= 8)
    {
        sizePacket = ((uint16_t*)data)[0];
        moduleId = ((uint16_t*)data)[1];
        periphId = ((uint16_t*)data)[2];
        functionId = ((uint16_t*)data)[3];
        
        std::vector<char> dataPacket(data + 8, data + sizePacket);
        uint64_t key = ((uint64_t)moduleId << 32) + ((uint64_t)periphId << 16) + functionId;
        std::map<uint64_t, std::queue<std::vector<char> > >::iterator it = packages.find(key);
        
        if (it == packages.end())
        {
            std::queue<std::vector<char> > queue;
            queue.push(dataPacket);
            packages.insert(std::pair<uint64_t, std::queue<std::vector<char> > >(key, queue));
        }
        else
        {
            (*it).second.push(dataPacket);
        }
        
        //dbg
        data[size] = 0;
        //printf("module %d, periph %d, fct %d %s\n", moduleId, periphId, functionId, data + 8);
    }
    
    return 0;
}

int simulator_recv(uint16_t moduleId, uint16_t periphId, uint16_t functionId, char *data, size_t size)
{
    UDK_UNUSED(size);

    uint64_t key = ((uint64_t)moduleId << 32) + ((uint64_t)periphId << 16) + functionId;
    std::map<uint64_t, std::queue<std::vector<char> > >::iterator it = packages.find(key);
    if(it != packages.end())
    {
        if((*it).second.empty())
        {
            return -1;
        }

        std::vector<char> package = (*it).second.front();
        memcpy(data, package.data(), package.size());
        (*it).second.pop();

        return package.size();
    }
    return -1;
}
