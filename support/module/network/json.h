/**
 * @file json.h
 * @author Charles-Antoine NOURY (charlybigoud)
 * @copyright Robotips 2017
 *
 * @date June 4, 2017, 11:15 AM
 *
 * @brief JSON protocol formating and parsing
 */

#ifndef JSON_H
#define JSON_H

#include <string.h>
#include <stdlib.h>

#include "sys/buffer.h"

// typedef enum
// {
//     JSON_QUERY_TYPE_
// } JSON_QUERY_TYPE;

typedef enum
{
    JSON_STANDARD,
    JSON_MONOBLOC
} JSON_SYNTAX;

typedef struct
{
    Buffer buffer;
    int indent_level;
    JSON_SYNTAX syntax;
} JsonBuffer;

void json_init(JsonBuffer *buffer, char *data, size_t size, JSON_SYNTAX s);

//FORMATING
void json_add_field_str(JsonBuffer *buffer, const char *name, const char *value);
void json_add_field_int(JsonBuffer *buffer, const char *name, const int value);
// void json_add_field_float(JsonBuffer *buffer, const char *name, const float value);

void json_open_object(JsonBuffer *buffer);
void json_close_object(JsonBuffer *buffer);
void json_add_object(JsonBuffer *buffer, const char *name);

// void json_open_list(JsonBuffer *buffer);
// void json_close_list(JsonBuffer *buffer);
// void json_add_list();

//PARSING

#endif // JSON_H
