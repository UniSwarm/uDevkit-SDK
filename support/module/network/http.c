/**
 * @file http.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date June 2, 2016, 11:45 AM
 *
 * @brief HTTP protocol parsing and formating
 */

#include "http.h"

#include <string.h>
#include <stdlib.h>

char url[100];
HTTP_PARSE_RESULT result;

HTTP_PARSE_RESULT *http_parse_querry_str(char *querry_str)
{
    char *pt_querry_str, *pt_end_path, *pt_end_line, *pt_url;

    result.type = HTTP_QUERRY_TYPE_ERROR;
    result.url = url;

    pt_querry_str = querry_str;

    // type of querry
    if (strncmp(querry_str, "GET", 3) == 0)
    {
        result.type = HTTP_QUERRY_TYPE_GET;
        pt_querry_str += 3;
    }
    else if (strncmp(querry_str, "HEAD", 4) == 0)
    {
        result.type = HTTP_QUERRY_TYPE_HEAD;
        pt_querry_str += 4;
    }
    else if (strncmp(querry_str, "POST", 4) == 0)
    {
        result.type = HTTP_QUERRY_TYPE_POST;
        pt_querry_str += 4;
    }
    else if (strncmp(querry_str, "PUT", 3) == 0)
    {
        result.type = HTTP_QUERRY_TYPE_PUT;
        pt_querry_str += 3;
    }
    else if (strncmp(querry_str, "DELETE", 6) == 0)
    {
        result.type = HTTP_QUERRY_TYPE_DELETE;
        pt_querry_str += 6;
    }
#ifdef HTTP_COMPLETE_PROTO
    else if (strncmp(querry_str, "CONNECT", 7) == 0)
    {
        result.type = HTTP_QUERRY_TYPE_CONNECT;
        pt_querry_str += 7;
    }
    else if (strncmp(querry_str, "OPTIONS", 7) == 0)
    {
        result.type = HTTP_QUERRY_TYPE_OPTIONS;
        pt_querry_str += 7;
    }
    else if (strncmp(querry_str, "TRACE", 5) == 0)
    {
        result.type = HTTP_QUERRY_TYPE_TRACE;
        pt_querry_str += 5;
    }
#endif
    else
        return &result;

    // check the space after
    if (*pt_querry_str != ' ')
        return &result;

    // find the second space, to bracket the path and the end of line
    pt_querry_str++;
    pt_end_path = strchr(pt_querry_str, ' ');
    pt_end_line = strstr(pt_querry_str, "\r\n");
    if (pt_end_path == NULL && pt_end_line <= pt_end_path)
        return &result;

    // extract, decode and copy url
    pt_url = url;
    while (pt_querry_str < pt_end_path)
    {
        char c = *pt_querry_str;
        if (c == '%')
        {
            pt_querry_str++;
            c = (int)strtol(pt_querry_str, NULL, 16);
            pt_querry_str++;
        }
        *pt_url = c;
        pt_url++;
        pt_querry_str++;
    }
    *pt_url = 0;

    // result.type = HTTP_QUERRY_TYPE_ERROR;
    return &result;
}

HTTP_PARSE_RESULT *http_parse_querry(char *querry, unsigned short size)
{
    querry[size] = 0;
    return http_parse_querry_str(querry);
}

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

void http_write_content_lenght(char *buffer, unsigned int content_lenght)
{
    strcat(buffer, "Content-Length: ");
    // strcat(buffer, content_lenght);
    strcat(buffer, "\r\n");
}

void http_write_header_end(char *buffer)
{
    strcat(buffer, "\r\n");
}
