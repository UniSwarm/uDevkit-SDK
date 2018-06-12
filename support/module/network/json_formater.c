/**
 * @file json.c
 * @author Charles-Antoine NOURY (charlybigoud)
 * @copyright Robotips 2017
 *
 * @date June 4, 2017, 11:15 AM
 *
 * @brief JSON formating protocol
 */

#include "json.h"

void json_set_indentation(JsonBuffer *json)
{
    int i;
    if (json->syntax == JSON_STANDARD)
    {
        for (i = 0 ; i < json->indent_level; ++i)
            buffer_astring(&json->buffer, "\t");
    }
}

void json_carriage_return(JsonBuffer *json)
{
    if (json->syntax == JSON_STANDARD)
        buffer_astring(&json->buffer, "\n");

    json_set_indentation(json);
}

void json_init(JsonBuffer *json, char *data, size_t size, JSON_SYNTAX s)
{
    buffer_init(&json->buffer, data, size);
    json->indent_level = 0;
    json->syntax = s;
}

void json_add_field_str(JsonBuffer *json, const char *name, const char* value)
{
    buffer_astring(&json->buffer, "\"");
    buffer_astring(&json->buffer, name);
    buffer_astring(&json->buffer, "\": \"");
    buffer_astring(&json->buffer, value);
    buffer_astring(&json->buffer, "\",");
}

void json_add_field_int(JsonBuffer *json, const char *name, const int value)
{
    buffer_astring(&json->buffer, "\"");
    buffer_astring(&json->buffer, name);
    buffer_astring(&json->buffer, "\": \"");
    buffer_aint(&json->buffer, value);
    buffer_astring(&json->buffer, "\",");
}

// void json_add_field_float(JsonBuffer *json, const char *name, const float value)
// {
//     buffer_astring(&json->buffer, "\"");
//     buffer_astring(&json->buffer, name);
//     buffer_astring(&json->buffer, "\": \"");
//     // buffer_afloat(&json->buffer, value);
//     buffer_astring(&json->buffer, "\",");
// }

void json_open_object(JsonBuffer *json)
{
    buffer_astring(&json->buffer, "{");

    if (json->syntax == JSON_STANDARD)
        buffer_astring(&json->buffer, "\n");

    json->indent_level++;
    json_set_indentation(json);
}

void json_close_object(JsonBuffer *json)
{
    json->indent_level--;

    //delete last comma
    if (*(json->buffer.tail - 1) == ',')
        *(json->buffer.tail - 1) = ' ';

    if (json->syntax == JSON_STANDARD)
        buffer_astring(&json->buffer, "\n");

    json_set_indentation(json);
    buffer_astring(&json->buffer, "}");

    //add a comma exept at last object
    if (json->indent_level != 0)
        buffer_astring(&json->buffer, ",");

}

void json_add_object(JsonBuffer *json, const char *name)
{
    buffer_astring(&json->buffer, "\"");
    buffer_astring(&json->buffer, name);
    buffer_astring(&json->buffer, "\": ");

    json_open_object(json);
}

void json_open_list(JsonBuffer *json)
{
    buffer_astring(&json->buffer, "[");
}

void json_close_list(JsonBuffer *json)
{
    //delete last comma
    if (*(json->buffer.tail - 1) == ',')
        *(json->buffer.tail - 1) = ' ';

    buffer_astring(&json->buffer, "]");

    //add a comma exept at last object
    if (json->indent_level != 0)
        buffer_astring(&json->buffer, ",");
}

void json_add_list(JsonBuffer *json, const char *name)
{
    buffer_astring(&json->buffer, "\"");
    buffer_astring(&json->buffer, name);
    buffer_astring(&json->buffer, "\": ");

    json_open_list(json);
}

#ifdef TEST_JSON_FORMAT
#include <stdio.h>
#include <string.h>
#include "../../sys/buffer.c"

int main(void)
{
    JsonBuffer json;
    char data [500];

    // json_init(&json, data, 500, JSON_MONOBLOC);
    json_init(&json, data, 500, JSON_STANDARD);

    printf("json.buffer.data_size: %ld", json.buffer.data_size);
    printf("%s\n", json.buffer.data);
    printf("\n");

    json_open_object(&json);

        json_add_field_str(&json, "name1", "value1");
        json_carriage_return(&json);
        json_add_field_int(&json, "name2", 42);
        json_carriage_return(&json);
        json_add_list(&json, "list1");
            json_add_field_str(&json, "name10", "value10");
            json_add_field_str(&json, "name11", "value11");
            json_add_field_str(&json, "name12", "value12");
        json_close_list(&json);
        json_carriage_return(&json);

            json_add_object(&json, "obj1");
            json_add_field_int(&json, "name3", 42);
            json_carriage_return(&json);
            json_add_field_int(&json, "name4", 42);
            json_close_object(&json);

        json_carriage_return(&json);

            json_add_object(&json, "obj2");
            json_add_field_int(&json, "name5", 42);
            json_carriage_return(&json);
            json_add_field_int(&json, "name6", 42);
            json_close_object(&json);

        json_carriage_return(&json);
        json_add_list(&json, "list2");
            json_add_field_str(&json, "name20", "value20");
            json_add_field_str(&json, "name21", "value21");
            json_add_field_str(&json, "name22", "value22");
        json_close_list(&json);

    json_close_object(&json);

    printf("%s\n", json.buffer.data);

    return 0;
}

#endif // TEST_JSON_FORMAT
