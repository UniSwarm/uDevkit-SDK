/**
 * @file http.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date June 2, 2016, 11:45 AM
 *
 * @brief HTTP protocol parsing and formating
 */

#ifndef HTTP_H
#define HTTP_H

// http querry parser
typedef enum
{
    HTTP_QUERRY_TYPE_ERROR = 0,
    HTTP_QUERRY_TYPE_CONNECT,
    HTTP_QUERRY_TYPE_DELETE,
    HTTP_QUERRY_TYPE_GET,
    HTTP_QUERRY_TYPE_HEAD,
    HTTP_QUERRY_TYPE_OPTIONS,
    HTTP_QUERRY_TYPE_POST,
    HTTP_QUERRY_TYPE_PUT,
    HTTP_QUERRY_TYPE_TRACE
} HTTP_QUERRY_TYPE;

typedef struct
{
    char *querry_str;
    char *ptr;
    HTTP_QUERRY_TYPE type;
} HTTP_PARSER;

void http_parse_init(HTTP_PARSER *parser, char *querry_str);
HTTP_QUERRY_TYPE http_parse_querry(HTTP_PARSER *parser, char *url);
int http_parse_field(HTTP_PARSER *parser, char *name, char *value);

// http formater
enum {
    HTTP_CONTINUE = 100,
    HTTP_SWITCHING_PROTOCOLS = 101,
    HTTP_OK = 200,
    HTTP_CREATED = 201,
    HTTP_ACCEPTED = 202,
    HTTP_NON_AUTHORITATIVE_INFO = 203,
    HTTP_NO_CONTENT = 204,
    HTTP_PARTIAL_CONTENT = 206,
    HTTP_MULTIPLE_CHOICES = 300,
    HTTP_MOVED_PERMANENTLY = 301,
    HTTP_MOVED_TEMPORARILY = 302,
    HTTP_NOT_MODIFIED = 304,
    HTTP_BAD_REQUEST = 400,  // malformed syntax
    HTTP_UNAUTHORIZED = 401, // authentication needed, respond with auth hdr
    HTTP_PAYMENT_REQUIRED = 402,
    HTTP_NOT_FOUND = 404,
    HTTP_FORBIDDEN = 403,
    HTTP_REQUEST_TIMEOUT = 408,
    HTTP_INTERNAL_SERVER_ERROR = 500,
    HTTP_NOT_IMPLEMENTED = 501,   // used for unrecognized requests
    HTTP_BAD_GATEWAY = 502,
    HTTP_SERVICE_UNAVAILABLE = 503 // overload, maintenance
};

void http_write_header_code(char *buffer, int result_code);
void http_write_content_type(char *buffer, const char *content_type);
void http_write_content_lenght(char *buffer, unsigned int content_lenght);
void http_write_header_end(char *buffer);

#endif // HTTP_H
