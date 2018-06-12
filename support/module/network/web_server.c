/**
 * @file web_server.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date June 2, 2016, 15:40 PM
 *
 * @brief HTTP protocol parsing and formating
 */

#include "web_server.h"

#include "driver/esp8266/esp8266.h"

#include "fs_functions.h"

#include <string.h>

#include "board.h"

char web_server_buffer[2048];
void (*web_server_restApi)(char *restUrl, HTTP_QUERRY_TYPE querry_type, char *buffer) = NULL;

const Fs_FilesList *web_server_file_list = NULL;

void web_server_init()
{
    // services init
}

void web_server_task()
{
    if (esp8266_getRec() != 1)
        return;

    unsigned char sock = esp8266_getRecSocket();
    char *querry = esp8266_getRecData();
    HTTP_PARSER parser;
    char url[50];

    querry[esp8266_getRecSize()] = 0;

    http_parse_init(&parser, querry);
    HTTP_QUERRY_TYPE type = http_parse_querry(&parser, url);

    if (type != HTTP_QUERRY_TYPE_ERROR)
    {
        if (web_server_restApi && strncmp(url, "/api/", 5) == 0)
        {
            (*web_server_restApi)(url+5,
                                  type, web_server_buffer);
            esp8266_write_socket_string(sock, web_server_buffer);
        }
        else
        {
            const Fs_File *file;

            if (strcmp(url, "/") == 0)
                file = getFile(web_server_file_list, "index.html");
            else
                file = getFile(web_server_file_list, url + 1);

            if (file == NULL)  // search in fs
            {
                http_write_header_code(web_server_buffer, HTTP_NOT_FOUND);
                http_write_header_end(web_server_buffer);
                esp8266_write_socket_string(sock, web_server_buffer);
            }
            else
            {
                unsigned int idData = 0, start;
                http_write_header_code(web_server_buffer, HTTP_OK);

                // content type
                http_write_content_type(web_server_buffer, file->type);

                // end of header
                http_write_header_end(web_server_buffer);
                start = strlen(web_server_buffer);

                while (idData + 2048 < file->size)
                {
                    memcpy(web_server_buffer + start, file->data + idData,
                           2048 - start);
                    esp8266_write_socket(sock, web_server_buffer, 2048);
                    idData += 2048 - start;
                    start = 0;
                }
                memcpy(web_server_buffer + start, file->data + idData,
                       file->size - idData);
                esp8266_write_socket(sock, web_server_buffer,
                                     file->size - idData + start);
            }
        }
    }
    else
    {
        http_write_header_code(web_server_buffer, HTTP_BAD_REQUEST);
        http_write_header_end(web_server_buffer);
        esp8266_write_socket_string(sock, web_server_buffer);
    }
    esp8266_close_socket(sock);
}

void web_server_setRestApi( void (*restApi)(char *url, HTTP_QUERRY_TYPE code, char *buffer) )
{
    web_server_restApi = restApi;
}

void web_server_setRootFS(const Fs_FilesList *file_list)
{
    web_server_file_list = file_list;
}
