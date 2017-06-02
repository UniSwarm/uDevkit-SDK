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
#include "http.h"
#include "restApi.h"

#include "fs_functions.h"

#include <string.h>

#include "board.h"

char web_server_buffer[2048];

void web_server_init()
{
    // services init
    rest_api_init();
}

void web_server_task()
{
    if (getRec() != 1)
        return;
    
    unsigned char sock = getRecSocket();
    char *querry = getRecData();
    HTTP_PARSE_RESULT *http_parse_result;

    http_parse_result = http_parse_querry(querry, getRecSize());

    if (http_parse_result->type != HTTP_QUERRY_TYPE_ERROR)
    {
        if (strncmp(http_parse_result->url, "/api/", 5) == 0)
        {
            // run restapi
            // LED1 = !LED1;

            rest_api_exec(http_parse_result, web_server_buffer);
            esp8266_write_socket_string(sock, web_server_buffer);
        }
        else
        {
            const Fs_File *file;

            file = getFile(http_parse_result->url + 1);
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
