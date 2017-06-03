
#include "http.h"

#include <stdio.h>
#include <string.h>

#include "board.h"

int id = 0;

void write_header_json(char *buffer)
{
    http_write_header_code(buffer, HTTP_OK);
    http_write_content_type(buffer, "application/json");
    http_write_header_end(buffer);
}

void rest_api_exec(char *restUrl, HTTP_QUERRY_TYPE querry_type, char *buffer)
{
    if (strcmp(restUrl, "status") == 0)
    {
        if (querry_type==HTTP_QUERRY_TYPE_GET)
        {
            id++;
            write_header_json(buffer);
            sprintf(buffer+strlen(buffer), "{\"batteryLevel\":\"%d\"}", id);
        }
    }
    else if (strcmp(restUrl, "led") == 0)
    {
        if (querry_type == HTTP_QUERRY_TYPE_POST)
        {
            http_write_header_code(buffer, HTTP_OK);

        }
        else if (querry_type == HTTP_QUERRY_TYPE_GET)
        {
            write_header_json(buffer);
            strcat(buffer, "{\"ledStatus\":\"");
            if (board_getLed(0) == 0)
                strcat(buffer, "Off\"}");
            else
                strcat(buffer, "On\"}");
        }
    }
    else
    {
        http_write_header_code(buffer, HTTP_NOT_FOUND);
        http_write_header_end(buffer);
    }
}
