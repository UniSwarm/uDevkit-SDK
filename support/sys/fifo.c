
#include "sys/fifo.h"

void fifo_init(Fifo *fifo, char *data, size_t size)
{
    fifo->size = size;
    fifo->data = data;
    fifo->head = 0;
    fifo->tail = 0;
}

size_t fifo_size(Fifo *fifo)
{
    return (fifo->head >= fifo->tail) ? fifo->head - fifo->tail
                                      : fifo->size + fifo->head - fifo->tail;
}

void fifo_push(Fifo *fifo, const char *data, size_t size)
{
    const char *dataPtr = data;
    if(fifo_size(fifo) + size < fifo->size)
    {
        int id = fifo->head;
        int end = id + size;
        if(end > fifo->size)
            end = fifo->size;
        for (; id < end; id++)
            fifo->data[id] = *(dataPtr++);
        if(fifo->head + size > fifo->size)
        {
            end = fifo->head + size - fifo->size;
            for (id=0; id < end; id++)
                fifo->data[id] = *(dataPtr++);
        }
        fifo->head = end;
    }
}

size_t fifo_pop(Fifo *fifo, char *data, size_t max_size)
{
    char *dataPtr = data;
    int id = fifo->tail;
    int end;

    size_t size = fifo_size(fifo);
    if(size > max_size)
        size = max_size;

    end = id + size;
    if(end > fifo->size)
        end = fifo->size;
    for (; id < end; id++)
        *(dataPtr++) = fifo->data[id];
    
    if(fifo->tail + size > fifo->size)
    {
        end = fifo->tail + size - fifo->size;
        for (id=0; id < end; id++)
            *(dataPtr++) = fifo->data[id];
    }
    fifo->tail = id;
    return size;
}
