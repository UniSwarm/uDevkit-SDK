
#include "sys/fifo.h"

#ifdef TEST_FIFO
  #include <stdio.h>
  #include <string.h>
  #include <assert.h>
#endif

void fifo_init(Fifo *fifo, char *data, size_t size)
{
    fifo->size = size;
    fifo->data = data;
    fifo->head = 0;
    fifo->tail = 0;
    fifo->mask = (size - 1);
}

size_t fifo_size(Fifo *fifo)
{
    return fifo->size;
}

size_t fifo_len(Fifo *fifo)
{
    return (fifo->tail > fifo->head) ? fifo->size + fifo->head - fifo->tail
                                     : fifo->head - fifo->tail;
}

size_t fifo_avail(Fifo *fifo)
{
    return fifo->size - fifo_len(fifo) - 1;
}

size_t fifo_push(Fifo *fifo, const char *data, size_t sizeToWrite)
{
    int id, i;
    const char *dataPtr = data;
    size_t len = fifo_len(fifo);
    if(sizeToWrite + len >= fifo->size)
        sizeToWrite = fifo->size - len - 1;
    if(sizeToWrite==0)
        return 0;

    //printf("< write head: %d tail: %d size: %d len: %d\n", fifo->head, fifo->tail, fifo->size, fifo_len(fifo));

    id = fifo->head;
    for (i=0; i < sizeToWrite; i++)
    {
        //printf("w%d'%c'\n", id, *dataPtr);
        fifo->data[id] = *(dataPtr++);
        id = (id + 1) & fifo->mask;
    }

    fifo->head = id;

    //printf("> write head: %d tail: %d size: %d len: %d\n", fifo->head, fifo->tail, fifo->size, fifo_len(fifo));

    return sizeToWrite;
}

size_t fifo_pop(Fifo *fifo, char *data, size_t max_size)
{
    char *dataPtr = data;
    int id, i;

    //printf("< read head: %d tail: %d size: %d len: %d\n", fifo->head, fifo->tail, fifo->size, fifo_len(fifo));

    size_t len = fifo_len(fifo);
    if(len > max_size)
        len = max_size;

    id = fifo->tail & fifo->mask;
    for (i=0; i < len; i++)
    {
        //printf("w%d'%c'\n", id, *dataPtr);
        *(dataPtr++) = fifo->data[id];
        id = (id + 1) & fifo->mask;
    }

    fifo->tail = id;
    /*if(fifo->tail > fifo->size)
        fifo->tail -= fifo->size;*/

    //printf("> read head: %d tail: %d size: %d len: %d\n", fifo->head, fifo->tail, fifo->size, fifo_len(fifo));

    return len;
}

#define fifo_push_str(ff, str) fifo_push(ff, str, strlen(str))

#ifdef TEST_FIFO
#include <string.h>
int main(void)
{
    int i;
    char data[]="0123456789A";
    char dataout[50];

    STATIC_FIFO(fifo, 16);
    STATIC_FIFO_INIT(fifo, 16);
    memcpy(fifo.data, "-|-|-|-|-|-|-|-|-|-|", 16);

    STATIC_FIFO(fifo2, 64);
    STATIC_FIFO_INIT(fifo2, 64);


    // test empty just initialized fifo
    assert( fifo_size(&fifo)==16 );
    assert( fifo_len(&fifo)==0 );
    assert( fifo_avail(&fifo)==15 );

    for(i=0; i<30; i++)
    {
        printf("  + i : %d\n", i);
        assert( fifo_push(&fifo, data, 1)==1 );
        assert( fifo_size(&fifo)==16 );
        assert( fifo_len(&fifo)==1 );
        assert( fifo_avail(&fifo)==14 );

        puts(fifo.data);
        assert( fifo_pop(&fifo, dataout, 50)==1 );
        printf("\n");
        assert( dataout[0]=='0' );

        assert( fifo_size(&fifo)==16 );
        assert( fifo_len(&fifo)==0 );
        assert( fifo_avail(&fifo)==15 );
    }

    // bigger insert
    assert( fifo_push(&fifo, data, 10)==10 );

    // sizes after one insert
    assert( fifo_size(&fifo)==16 );
    assert( fifo_len(&fifo)==10 );
    assert( fifo_avail(&fifo)==5 );

    // overflow
    assert( fifo_push(&fifo, data, 10)==5 );
    printf("'%s'\n", fifo.data);

    // sizes after overflow
    assert( fifo_size(&fifo)==16 );
    assert( fifo_len(&fifo)==15 );
    assert( fifo_avail(&fifo)==0 );

    assert( fifo_push(&fifo, data, 10)==0 );

    //
    assert( fifo_pop(&fifo, dataout, 50)==15 );
    // test empty after cleared fifo
    printf("'%s'\n", fifo.data);
    printf("'%s'\n", dataout);
    printf("  fifo->head: %d\n", (int)fifo.head);
    printf("  fifo->tail: %d\n", (int)fifo.tail);
    assert( fifo_size(&fifo)==16 );
    printf("  fifo->len: %d\n", (int)fifo_len(&fifo));
    assert( fifo_len(&fifo)==0 );
    assert( fifo_avail(&fifo)==15 );
    assert( strcmp(dataout, "012345678901234")==0 );

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
    assert( fifo_push(&fifo, data, 10)==5 );
    assert( fifo_len(&fifo)==15 );

    // reel test
    puts("----");
    char uart_tmpchar[2];
    uart_tmpchar[1] = '\0';

    fifo_push_str(&fifo2, "ATE1\r\n");
    while (fifo_pop(&fifo2, uart_tmpchar, 1) == 1) printf("%c", uart_tmpchar[0]);

    fifo_push_str(&fifo2, "AT+CIPMUX=1\r\n");
    while (fifo_pop(&fifo2, uart_tmpchar, 1) == 1) printf("%c", uart_tmpchar[0]);

    fifo_push_str(&fifo2, "AT+CWMODE_CUR=3\r\n");
    while (fifo_pop(&fifo2, uart_tmpchar, 1) == 1) printf("%c", uart_tmpchar[0]);

    fifo_push_str(&fifo2, "AT+CWJAP_CUR=\"iotRT\",\"iotwifiA\"\r\n");
    while (fifo_pop(&fifo2, uart_tmpchar, 1) == 1) printf("%c", uart_tmpchar[0]);

    return 0;
};

#endif
