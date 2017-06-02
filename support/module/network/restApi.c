#include "restApi.h"

#include <stdio.h>
#include <string.h>

#include "board.h"

void write_header_json(char *buffer)
{
    http_write_header_code(buffer, HTTP_OK);
    http_write_content_type(buffer, "application/json");
    http_write_header_end(buffer);
}

void rest_api_init()
{
}

void rest_api_exec(HTTP_PARSE_RESULT *http_parse_result, char *buffer)
{
    char *restUrl = http_parse_result->url+5;
    if(strcmp(restUrl, "status")==0)
    {
        if(http_parse_result->type==HTTP_QUERRY_TYPE_GET)
        {
            write_header_json(buffer);
            sprintf(buffer+strlen(buffer),"{\"batteryLevel\":\"26%%\"}");
        }
    }
    else if(strcmp(restUrl, "led")==0)
    {
        if(http_parse_result->type==HTTP_QUERRY_TYPE_POST)
        {
            http_write_header_code(buffer, HTTP_OK);

        }
        else if(http_parse_result->type==HTTP_QUERRY_TYPE_GET)
        {
            write_header_json(buffer);
            strcat(buffer, "{\"ledStatus\":\"");
            if(board_getLed(0)==0)
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
