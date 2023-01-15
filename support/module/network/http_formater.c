/**
 * @file http_formater.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date June 2, 2016, 11:45 AM
 *
 * @brief HTTP protocol formater
 */

#include "http.h"

#include <stdlib.h>
#include <string.h>

void http_write_header_code(char *buffer, int result_code)
{
    strcpy(buffer, "HTTP/1.1 ");
    switch (result_code)
    {
        case HTTP_OK:
            strcat(buffer, "200 OK\r\n");
            break;

        case HTTP_BAD_REQUEST:
            strcat(buffer, "400 Bad Request\r\n");
            break;

        case HTTP_NOT_FOUND:
            strcat(buffer, "404 Not Found\r\n");
            break;

        default:
            break;
    }
}

void http_write_content_type(char *buffer, const char *content_type)
{
    strcat(buffer, "Content-Type: ");
    strcat(buffer, content_type);
    strcat(buffer, "\r\n");
}

void http_write_content_length(char *buffer, unsigned int content_length)
{
    strcat(buffer, "Content-Length: ");
    // strcat(buffer, content_length);
    strcat(buffer, "\r\n");
}

void http_write_header_end(char *buffer)
{
    strcat(buffer, "\r\n");
}
