#include "web_server.h"

#include "driver/esp8266/esp8266.h"
#include "http.h"
#include "restApi.h"

#include "fs_functions.h"

#include <string.h>

#include "board.h"

char buffer[2048];

void web_server_init()
{
	// comunication init
	/*esp_init();

	esp_send_cmd("ATE0");
	wait_ok();
	esp_send_cmd("AT+CWMODE=3");
	wait_ok();
	//esp_send_cmd("AT+CWJAP=\"wifi_iot_robotips\",\"iotwifiA\"");
	esp_send_cmd("AT+CWJAP=\"Livebox-FC0E\",\"ecseapakgu4grohymnes\"");
	wait_ok();
	esp_send_cmd("AT+CWSAP=\"ESP_01\",\"\",1,0");
	wait_ok();
	esp_send_cmd("AT+CIPMUX=1");
	wait_ok();
	esp_send_cmd("AT+CIPSERVER=1,80");
	wait_ok();*/

	//services init
	rest_api_init();
}

void web_server_task()
{
    if(getRec()==1)
    {
        unsigned char sock = getRecSocket();
        char *querry = getRecData();
        HTTP_PARSE_RESULT *http_parse_result;

        http_parse_result = http_parse_querry(querry, getRecSize());

        if(http_parse_result->type != HTTP_QUERRY_TYPE_ERROR)
        {
            if(strncmp(http_parse_result->url,    "/api/", 5)==0)
            {
                            // run restapi
                            //LED1 = !LED1;

                            rest_api_exec(http_parse_result, buffer);
                            esp8266_write_socket_string(sock, buffer);
            }
            else
            {
                const Fs_File *file;

                file = getFile(http_parse_result->url+1);
                if(file==NULL) // search in fs
                {
                    http_write_header_code(buffer, HTTP_NOT_FOUND);
                    http_write_header_end(buffer);
                    esp8266_write_socket_string(sock, buffer);
                }
                else
                {
                    unsigned int idData=0, start;
                    http_write_header_code(buffer, HTTP_OK);

                    // content type
                    http_write_content_type(buffer, file->type);

                    // end of header
                    http_write_header_end(buffer);
                    start=strlen(buffer);

                    while(idData+2048 < file->size)
                    {
                        memcpy(buffer+start, file->data+idData, 2048-start);
                        esp8266_write_socket(sock, buffer, 2048);
                        idData+=2048-start;
                        start=0;
                    }
                    memcpy(buffer+start, file->data+idData, file->size-idData-start);
                    esp8266_write_socket(sock, buffer, file->size-idData);
                }
            }
        }
        else
        {
            http_write_header_code(buffer, HTTP_BAD_REQUEST);
            http_write_header_end(buffer);
            esp8266_write_socket_string(sock, buffer);
        }
        esp8266_close_socket(sock);
    }
}