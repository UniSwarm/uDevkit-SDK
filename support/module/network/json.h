#ifndef JSON_H
#define JSON_H

#include <string.h>
#include <stdlib.h>

#include "sys/buffer.h"

// parsing querry header
typedef enum
{
    JSON_QUERY_TYPE_
} JSON_QUERY_TYPE;

typedef struct
{
    Buffer buffer;
    int indent_level;
} JsonBuffer;


void json_init(JsonBuffer *buffer, char *data, size_t size);

void json_add_field_str(JsonBuffer *buffer, const char *name, const char *value);
void json_add_field_int(JsonBuffer *buffer, const char *name, const int value);
// void json_add_field_float(JsonBuffer *buffer, const char *name, const float value);

void json_open_object(JsonBuffer *buffer);
void json_close_object(JsonBuffer *buffer);
void json_add_object(JsonBuffer *buffer, const char *name);



// void json_open_list(JsonBuffer *buffer);
// void json_close_list(JsonBuffer *buffer);
// void json_add_list();

#endif // JSON_H
