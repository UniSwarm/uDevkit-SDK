/**
 * @file fifo.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2020
 *
 * @date June 13, 2016, 18:30 PM
 *
 * @brief Low level fifo for udevkit-SDK
 */

#ifndef FIFO_H
#define FIFO_H

#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    size_t size;
    volatile uint16_t head;
    volatile uint16_t tail;
    uint16_t mask;
    char *data;
} Fifo;

#define STATIC_FIFO(x, y)                                                                                                                                      \
    char x##_data[y];                                                                                                                                          \
    Fifo x

#define STATIC_FIFO_INIT(x, y)                                                                                                                                 \
    x.size = (y);                                                                                                                                              \
    x.head = 0;                                                                                                                                                \
    x.tail = 0;                                                                                                                                                \
    x.data = x##_data;                                                                                                                                         \
    x.mask = (y - 1)

void fifo_init(Fifo *fifo, char *data, size_t size);
size_t fifo_size(Fifo *fifo);
size_t fifo_len(Fifo *fifo);
size_t fifo_avail(Fifo *fifo);

size_t fifo_push(Fifo *fifo, const char *data, size_t sizeToWrite);
size_t fifo_pop(Fifo *fifo, char *data, size_t max_size);

#endif  // FIFO_H
