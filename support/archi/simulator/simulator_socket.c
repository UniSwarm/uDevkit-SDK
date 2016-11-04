/**
 * @file simulator_socket.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date November 3, 2016, 22:44 PM
 *
 * @brief Communication by sockets for testing purpose (windows and linux cross-platforms)
 */

#include "simulator_socket.h"

#include <stdio.h>

SOCKET simulator_sock;

void simulator_socket_init()
{
    #if defined (WIN32)
        WSADATA WSAData;
        WSAStartup(MAKEWORD(2,2), &WSAData);
    #endif

    SOCKADDR_IN sin;

    // socket creation
    simulator_sock = socket(AF_INET, SOCK_STREAM, 0);

    // socket config
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(SIM_SOCKET_PORT);

    // socket connection to host
    if(connect(simulator_sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
        printf("Connected successfully to port %s %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
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
