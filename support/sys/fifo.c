
#include "sys/fifo.h"

#ifdef TEST_FIFO
  #include <stdio.h>
  #include <assert.h>
#endif

void fifo_init(Fifo *fifo, char *data, size_t size)
{
    fifo->size = size;
    fifo->data = data;
    fifo->head = 0;
    fifo->tail = size;
}

size_t fifo_size(Fifo *fifo)
{
    return fifo->size;
}

size_t fifo_len(Fifo *fifo)
{
    return (fifo->head > fifo->tail) ? fifo->head - fifo->tail - 1
                                     : fifo->size + fifo->head - fifo->tail;
}

size_t fifo_avail(Fifo *fifo)
{
    return fifo->size - fifo_len(fifo);
}

size_t fifo_push(Fifo *fifo, const char *data, size_t sizeToWrite)
{
    int id, end;
    const char *dataPtr = data;
    size_t len = fifo_len(fifo);
    if(sizeToWrite + len > fifo->size)
        sizeToWrite = fifo->size - len;
    if(sizeToWrite==0)
        return 0;

    id = fifo->head;
    if(id >= fifo->size)
        id=0;
    end = id + sizeToWrite;
    if(end > fifo->size)
        end = fifo->size;
    for (; id < end; id++)
        fifo->data[id] = *(dataPtr++);
    if(fifo->head + sizeToWrite > fifo->size)
    {
        end = fifo->head + sizeToWrite - fifo->size;
        for (id=0; id < end; id++)
        {
            fifo->data[id] = *(dataPtr++);
        }
        end--;
    }
    fifo->head = end;

    return sizeToWrite;
}

size_t fifo_pop(Fifo *fifo, char *data, size_t max_size)
{
    char *dataPtr = data;
    int id = fifo->tail + 1;
    int end;

    size_t len = fifo_len(fifo);
    if(len > max_size)
        len = max_size;

    if(id >= fifo->size)
        id=0;
    end = id + len;
    if(end > fifo->size)
        end = fifo->size;
    for (; id < end; id++)
        *(dataPtr++) = fifo->data[id];

    if(id + len > fifo->size + 1)
    {
        end = fifo->tail + len - fifo->size;
        for (id=0; id <= end; id++)
            *(dataPtr++) = fifo->data[id];
    }
    if(fifo->tail + len > fifo->size)
        fifo->tail = fifo->tail + len - fifo->size - 1;
    else
        fifo->tail = fifo->tail + len;
    return len;
}

#ifdef TEST_FIFO
int main(void)
{
    int i;
    char data[]="0123456789A";
    char dataout[50];

    STATIC_FIFO(fifo, 20);
    STATIC_FIFO_INIT(fifo, 20);

    // test empty just initialized fifo
    assert( fifo_size(&fifo)==20 );
    assert( fifo_len(&fifo)==0 );
    assert( fifo_avail(&fifo)==20 );

    for(i=0; i<30; i++)
    {
        printf("  + i : %d\n", i);
        assert( fifo_push(&fifo, data, 1)==1 );
        assert( fifo_size(&fifo)==20 );
        assert( fifo_len(&fifo)==1 );
        assert( fifo_avail(&fifo)==19 );

        assert( fifo_pop(&fifo, dataout, 50)==1 );

        assert( fifo_size(&fifo)==20 );
        assert( fifo_len(&fifo)==0 );
        assert( fifo_avail(&fifo)==20 );
    }

    // bigger insert
    assert( fifo_push(&fifo, data, 10)==10 );

    // sizes after one insert
    assert( fifo_size(&fifo)==20 );
    assert( fifo_len(&fifo)==10 );
    assert( fifo_avail(&fifo)==10 );

    // overflow
    assert( fifo_push(&fifo, data, 11)==10 );
    printf("'%s'\n", fifo.data);

    // sizes after overflow
    assert( fifo_size(&fifo)==20 );
    assert( fifo_len(&fifo)==20 );
    assert( fifo_avail(&fifo)==0 );

    assert( fifo_push(&fifo, data, 10)==0 );

    //
    assert( fifo_pop(&fifo, dataout, 50)==20 );
    // test empty after cleared fifo
    dataout[20]=0;
    printf("'%s'\n", fifo.data);
    printf("'%s'\n", dataout);
    assert( strcmp(dataout, "01234567890123456789")==0 );
    printf("  fifo->head: %d\n", (int)fifo.head);
    printf("  fifo->tail: %d\n", (int)fifo.tail);
    assert( fifo_size(&fifo)==20 );
    printf("  fifo->len: %d\n", (int)fifo_len(&fifo));
    assert( fifo_len(&fifo)==0 );
    assert( fifo_avail(&fifo)==20 );

    // middle align
    assert( fifo_push(&fifo, data, 5)==5 );
    assert( fifo_len(&fifo)==5 );
    assert( fifo_pop(&fifo, dataout, 50)==5 );
    dataout[5]=0;
    assert( strcmp(dataout, "01234")==0 );
    assert( fifo_len(&fifo)==0 );
    assert( fifo_pop(&fifo, dataout, 50)==0 );
    assert( fifo_len(&fifo)==0 );
    assert( fifo_push(&fifo, data, 10)==10 );
    assert( fifo_len(&fifo)==10 );
    assert( fifo_push(&fifo, data, 10)==10 );
    assert( fifo_len(&fifo)==20 );


    return 0;
};

#endif