/**
 * @file simulator_socket.cpp
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date November 3, 2016, 22:44 PM
 *
 * @brief Communication by sockets for testing purpose (windows and linux cross-platforms)
 */

#include "simulator_socket.h"

#include <stdio.h>
#include <errno.h>

SOCKET simulator_sock;

void simulator_socket_init()
{
    SOCKADDR_IN ssin;

    #if defined (WIN32) || defined (_WIN32)
        WSADATA WSAData;
        WSAStartup(MAKEWORD(2,2), &WSAData);
    #endif

    // socket creation
    simulator_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(simulator_sock == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }

    // socket config
    ssin.sin_addr.s_addr = inet_addr("127.0.0.1");
    ssin.sin_family = AF_INET;
    ssin.sin_port = htons(SIM_SOCKET_PORT);

    // socket connection to host
    if(connect(simulator_sock, (SOCKADDR*)&ssin, sizeof(ssin)) != SOCKET_ERROR)
        printf("Connected successfully to port %s %d\n", inet_ntoa(ssin.sin_addr), htons(ssin.sin_port));
    else
    {
        printf("Cannot connect to port %d\n", SIM_SOCKET_PORT);
        closesocket(simulator_sock);
        simulator_sock = 0;
    }
}

void simulator_socket_end()
{
    #if defined (WIN32)
        WSACleanup();
    #endif

    closesocket(simulator_sock);
}

void simulator_socket_send(char *data, size_t size)
{
    if(simulator_sock != 0)
    {
        send(simulator_sock, data, size, 0);
    }
}

int simulator_socket_read(char *data, size_t size)
{
    if(simulator_sock != 0)
    {
        #if defined (WIN32) || defined (_WIN32)
            u_long ret;
            ioctlsocket(simulator_sock, FIONREAD, &ret);
            if(ret==0)
                return 0;
        #endif
        return recv(simulator_sock, data, size, SOCKET_MODE);
    }
    return 0;
}
