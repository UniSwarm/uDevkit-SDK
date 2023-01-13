#include <stdio.h>
#include <string.h>

#include "board.h"
#include <module/network.h>

int id = 0;

void write_header_json(char *buffer)
{
    http_write_header_code(buffer, HTTP_OK);
    http_write_content_type(buffer, "application/json");
    http_write_header_end(buffer);
}

void rest_api_exec(char *restUrl, HTTP_QUERRY_TYPE querry_type, char *buffer)
{
    JsonBuffer json;
    write_header_json(buffer);
    json_init(&json, buffer + strlen(buffer), 100, JSON_MONOBLOC);

    if (strcmp(restUrl, "status") == 0)
    {
        if (querry_type == HTTP_QUERRY_TYPE_GET)
        {
            id++;
            json_open_object(&json);
            json_add_field_int(&json, "batteryLevel", id);
            json_close_object(&json);
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
            json_open_object(&json);
            json_add_field_int(&json, "ledStatus", board_getLed(0));
            json_close_object(&json);
        }
    }
    else
    {
        http_write_header_code(buffer, HTTP_NOT_FOUND);
        http_write_header_end(buffer);
    }
}
