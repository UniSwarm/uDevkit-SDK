/**
 * @file json.h
 * @author Charles-Antoine NOURY (charlybigoud)
 * @copyright Robotips 2017
 *
 * @date June 4, 2017, 11:15 AM
 *
 * @brief JSON formating and parsing protocols
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

void json_init(JsonBuffer *json, char *data, size_t size, JSON_SYNTAX s);

//FORMATING
void json_add_field_str(JsonBuffer *json, const char *name, const char *value);
void json_add_field_int(JsonBuffer *json, const char *name, const int value);
// void json_add_field_float(JsonBuffer *json, const char *name, const float value);

void json_open_object(JsonBuffer *json);
void json_close_object(JsonBuffer *json);
void json_add_object(JsonBuffer *json, const char *name);

void json_open_list(JsonBuffer *json);
void json_close_list(JsonBuffer *json);
void json_add_list(JsonBuffer *json, const char *name);

//PARSING
void json_get_next_field(const JsonBuffer *json, char *name, char *value);

#endif // JSON_H
