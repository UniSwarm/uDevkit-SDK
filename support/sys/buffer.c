/**
 * @file buffer.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date August 03, 2016, 16:30 PM
 *
 * @brief Buffer for string construction
 */
 
#include "sys/buffer.h"

void buffer_init(Buffer *buffer, char *data, size_t size)
{
    buffer->size = 0;
    buffer->data_size = size;
    buffer->data = data;
    buffer->tail = data;
    buffer->data[0] = 0;
}

size_t buffer_size(Buffer *buffer)
{
    return buffer->size;
}

inline void buffer_clear(Buffer *buffer)
{
    buffer->size = 0;
    buffer->tail = buffer->data;
    buffer->data[0] = 0;
}

void buffer_aint(Buffer *buffer, const int i)
{
    char buff[11];
    div_t res;
    int n = i;
    uint8_t pos = 0, size = 0;
    
    // int to string conversion (reversed)
    if(i < 0)
    {
        n = -i;
        size++;
    }
    do
    {
        res = div(n, 10);
        n = res.quot;
        buff[pos] = res.rem + '0';
        pos++;
    } while (n != 0);
    size += pos;
    
    // buffer size checking
    if(buffer->size + size >= buffer->data_size)
        return;
    buffer->size += size;
    
    // copy char with reverse order
    if(i < 0)
    {
        (*buffer->tail) = '-';
        buffer->tail++;
    }
    while (pos != 0)
    {
        pos--;
        (*buffer->tail) = buff[pos];
        buffer->tail++;
    }
    (*buffer->tail) = 0;
}

void buffer_achar(Buffer *buffer, const char c)
{
    // buffer size checking
    if(buffer->size + 1 >= buffer->data_size)
        return;
    buffer->size++;
    
    // append char and update tail and size
    (*buffer->tail) = c;
    buffer->tail++;
    (*buffer->tail) = 0;
}

void buffer_astring(Buffer *buffer, const char *str)
{
    const char *ptr = str;
    
    // buffer size checking
    size_t size = strlen(str);
    if(buffer->size + size >= buffer->data_size)
        size = buffer->data_size - buffer->size - 1;
    buffer->size += size;
    
    // copy char with reverse order
    while (size != 0)
    {
        (*buffer->tail) = *ptr;
        buffer->tail++;
        ptr++;
        size--;
    }
    (*buffer->tail) = 0;
}
