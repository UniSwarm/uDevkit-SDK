/**
 * @file fifo.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date June 13, 2016, 18:30 PM
 *
 * @brief Font structure for gui module
 */

#ifndef FIFO_H
#define FIFO_H

#include <stdlib.h>
#include <stdint.h>

typedef struct
{
    size_t size;
    volatile uint16_t head;
    volatile uint16_t tail;
    char *data;
} Fifo;

#define STATIC_FIFO(x,y) char x##_data[y]; Fifo x
#define STATIC_FIFO_INIT(x,y) x.size = y; x.head = 0; x.tail = 0; x.data = x##_data;

inline void fifo_init(Fifo *fifo, char *data, size_t size);
inline size_t fifo_size(Fifo *fifo);

void fifo_push(Fifo *fifo, const char *data, size_t size);
size_t fifo_pop(Fifo *fifo, char *data, size_t max_size);

#endif // FIFO_H