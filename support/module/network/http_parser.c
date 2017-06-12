/**
 * @file http_parser.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date June 2, 2016, 11:45 AM
 *
 * @brief HTTP protocol parser
 */

#include "http.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void http_parse_init(HTTP_PARSER *parser, char *querry_str)
{
    parser->querry_str = querry_str;
    parser->ptr = querry_str;
}

HTTP_QUERRY_TYPE http_parse_querry(HTTP_PARSER *parser, char *url)
{
    HTTP_QUERRY_TYPE type;
    char *pt_querry_str, *pt_end_path, *pt_end_line, *pt_url;

    type = HTTP_QUERRY_TYPE_ERROR;

    pt_querry_str = parser->querry_str;

    // type of querry
    if (strncmp(pt_querry_str, "GET", 3) == 0)
    {
        type = HTTP_QUERRY_TYPE_GET;
        pt_querry_str += 3;
    }
    else if (strncmp(pt_querry_str, "HEAD", 4) == 0)
    {
        type = HTTP_QUERRY_TYPE_HEAD;
        pt_querry_str += 4;
    }
    else if (strncmp(pt_querry_str, "POST", 4) == 0)
    {
        type = HTTP_QUERRY_TYPE_POST;
        pt_querry_str += 4;
    }
    else if (strncmp(pt_querry_str, "PUT", 3) == 0)
    {
        type = HTTP_QUERRY_TYPE_PUT;
        pt_querry_str += 3;
    }
    else if (strncmp(pt_querry_str, "DELETE", 6) == 0)
    {
        type = HTTP_QUERRY_TYPE_DELETE;
        pt_querry_str += 6;
    }
#ifdef HTTP_COMPLETE_PROTO
    else if (strncmp(pt_querry_str, "CONNECT", 7) == 0)
    {
        type = HTTP_QUERRY_TYPE_CONNECT;
        pt_querry_str += 7;
    }
    else if (strncmp(pt_querry_str, "OPTIONS", 7) == 0)
    {
        type = HTTP_QUERRY_TYPE_OPTIONS;
        pt_querry_str += 7;
    }
    else if (strncmp(pt_querry_str, "TRACE", 5) == 0)
    {
        type = HTTP_QUERRY_TYPE_TRACE;
        pt_querry_str += 5;
    }
#endif
    else
        return HTTP_QUERRY_TYPE_ERROR;

    // check the space after
    if (*pt_querry_str != ' ')
        return HTTP_QUERRY_TYPE_ERROR;

    // find the second space, to bracket the path and the end of line
    pt_querry_str++;
    pt_end_path = strchr(pt_querry_str, ' ');
    pt_end_line = strstr(pt_querry_str, "\r\n");
    if ((pt_end_path == NULL && pt_end_line <= pt_end_path) || pt_end_line == NULL)
        return HTTP_QUERRY_TYPE_ERROR;

    // check protocol
    if (strncmp(pt_end_path+1, "HTTP/", 5) != 0)
        return HTTP_QUERRY_TYPE_ERROR;

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

    return type;
}

#ifdef TEST
#include <stdio.h>
#include <assert.h>
int main(void)
{
    char querry[]="GET /index.html HTTP/1.1\r\n\
Host: 192.168.4.1\r\n\
User-Agent: Mozilla/5.0 (Android 7.0; Mobile; rv:53.0) Gecko/53.0 Firefox/53.0\r\n\
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n\
Accept-Language: fr,fr-FR;q=0.8,en-US;q=0.5,en;q=0.3\r\n\
Accept-Encoding: gzip, deflate\r\n\
DNT: 1\r\n\
Connection: keep-alive\r\n\
Upgrade-Insecure-Requests: 1\r\n\
Cache-Control: max-age=0\r\n\
";

    HTTP_PARSER parser;
    char url[50];

    http_parse_init(&parser, querry);
    HTTP_QUERRY_TYPE type = http_parse_querry(&parser, url);

    assert( type == HTTP_QUERRY_TYPE_GET );
    assert( strcmp(url, "/index.html") == 0 );
    return 0;
};

#endif
