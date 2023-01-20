/**
 * @file buffer.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2020
 *
 * @date August 03, 2016, 16:30 PM
 *
 * @brief Buffer for string construction
 */

#ifndef BUFFER_H
#define BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    size_t data_size;
    size_t size;
    char *tail;
    char *data;
} Buffer;

#define STATIC_BUFFER(x, y)                                                                                                                                    \
    char x##_data[y];                                                                                                                                          \
    Buffer x
#define STATIC_BUFFER_INIT(x, y)                                                                                                                               \
    x.data_size = y;                                                                                                                                           \
    x.size = 0;                                                                                                                                                \
    x.tail = x##_data;                                                                                                                                         \
    x.data = x##_data;                                                                                                                                         \
    x.data[0] = 0;

void buffer_init(Buffer *buffer, char *data, size_t size);
size_t buffer_size(Buffer *buffer);
void buffer_clear(Buffer *buffer);

void buffer_aint(Buffer *buffer, const int i);
void buffer_achar(Buffer *buffer, const char c);
void buffer_astring(Buffer *buffer, const char *str);

#ifdef __cplusplus
}
#endif

#endif  // BUFFER_H
