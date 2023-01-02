/**
 * @file cmd_can.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2022
 *
 * @date November 14, 2022, 02:46 PM
 *
 * @brief CAN commands
 */

#include "cmds.h"

#include "../cmdline_curses.h"
#include "cmd_stdio.h"

#include <driver/can.h>

static void _cmd_can_help(void);
static void _cmd_can_printConfig(rt_dev_t can_dev);
static void _cmd_can_dump(int can_id, CAN_MSG_HEADER *can_header, char rdata[]);
static int _cmd_can_dump_task(void);

static uint8_t _cmd_can_id = 0;
static rt_dev_t _cmd_can_can_dev = 0;
static uint8_t _cmd_can_fifo_id = 0;

#if (defined(CAN_COUNT) && CAN_COUNT > 0)
void _cmd_can_help(void)
{
    puts("can");
    puts("can <can-id>");
    puts("can <can-id> rec <fifo-id>");
    puts("can <can-id> dump <fifo-id>");
    // puts("can <can-id> send <fifo-id> <id> <data-to-send>");
}

void _cmd_can_printConfig(rt_dev_t can_dev)
{
    if (can_isOpened(can_dev))
    {
        printf(CMDLINE_GRN " Opened," CMDLINE_NRM);
    }
    else
    {
        printf(CMDLINE_RED " Closed," CMDLINE_NRM);
    }

    if (can_isEnabled(can_dev))
    {
        printf(CMDLINE_GRN " enabled, " CMDLINE_NRM);
    }
    else
    {
        printf(CMDLINE_RED " disabled," CMDLINE_NRM);
    }
    printf(" config: %lubds (%lubds real)\r\n", can_bitRate(can_dev), can_effectiveBitRate(can_dev));
}

void _cmd_can_dump(int can_id, CAN_MSG_HEADER *can_header, char rdata[])
{
    char buffer[50] = "";
    char *str = buffer;

    str += sprintf(str, "can%d  ", can_id);
    if ((can_header->flags & CAN_VERS2BA) == CAN_VERS2BA)
    {
        str += sprintf(str, "%08" CMD_X32, can_header->id & 0x1FFFFFFF);
    }
    else
    {
        str += sprintf(str, "%03" CMD_X32, can_header->id & 0x7FF);
    }

    str += sprintf(str, "   [%d]", can_header->size);
    if (can_header->flags & CAN_RTR)
    {
        str += sprintf(str, "  remote request");
    }
    else
    {
        const char *hex = "0123456789ABCDEF";
        *(str++) = ' ';
        for (int i = 0; i < can_header->size; i++)
        {
            *(str++) = ' ';
            *(str++) = hex[(rdata[i] >> 4) & 0x0F];
            *(str++) = hex[(rdata[i]) & 0x0F];
        }
    }
    *(str++) = '\0';

    puts(buffer);
}
#endif

int cmd_can(int argc, char **argv)
{
#if (!defined(CAN_COUNT) || CAN_COUNT == 0)
    puts("No CAN module");
    return 0;
#else
    // no args -> print number of cans
    if (argc == 1)
    {
        printf("count: %d\r\n", (int)CAN_COUNT);
        for (uint8_t can_id = 1; can_id <= CAN_COUNT; can_id++)
        {
            printf("CAN %d:", can_id);
            rt_dev_t can_dev = can(can_id);
            _cmd_can_printConfig(can_dev);
        }
        return 0;
    }

    // help
    if (strcmp(argv[1], "help") == 0)
    {
        _cmd_can_help();
        return 0;
    }

    // first arg numeric : convert to can id
    uint8_t can_id = 255;
    char c = argv[1][0];
    if (isdigit(c))
    {
        can_id = c - '0';
        c = argv[1][1];
        if (isdigit(c))
        {
            can_id = can_id * 10 + (c - '0');
        }
    }
    if (can_id <= 0 || can_id > CAN_COUNT)
    {
        printf("Invalid can id %d\r\n", can_id);
        return -1;
    }
    rt_dev_t can_dev = can(can_id);

    // if no more arg, print properties of can
    // > can <can-id>
    if (argc == 2)
    {
        _cmd_can_printConfig(can_dev);
        return 0;
    }

    // parse argv 2
    if (argc < 4)
    {
        puts("Invalid arguments");
        return -1;
    }

    uint8_t fifo_id = atoi(argv[3]);
    // == rec > can <can-id> rec <fifo-id>
    if (strcmp(argv[2], "rec") == 0)
    {
        CAN_MSG_HEADER can_header;
        char buffer[8];
        if (can_rec(can_dev, fifo_id, &can_header, buffer) == 1)
        {
            _cmd_can_dump(can_id, &can_header, buffer);
        }
        return 0;
    }
    // == dump > can <can-id> dump <fifo-id>
    if (strcmp(argv[2], "dump") == 0)
    {
        _cmd_can_id = can_id;
        _cmd_can_can_dev = can_dev;
        _cmd_can_fifo_id = fifo_id;
        cmd_setTask(_cmd_can_dump_task);
        return 1;  // not finished
    }

    /*if (argc < 4)
        return 1;
    // == send > can <can-id> send <fifo> <id> <data-to-send>
    if (strcmp(argv[2], "send") == 0)
    {
        // TODO : converting the <fifo> (char*) to the fifo_id (uint8)

        fifo_id = 0;

        size_t sent = can_send(can_dev, fifo_id, *argv[1], argv[5], strlen(argv[5]), 0x03); //(rt_dev_t device, uint8_t fifo, uint32_t id, char *data, uint8_t
    size, CAN_FLAGS flags)
        // printf("ok %d data sent\r\n", sent);
        printf("ok %d data sent : %s \r\n", strlen(argv[5]), argv[5]);
        return 0;
    }*/

    return -1;
#endif
}

#if (defined(CAN_COUNT) && CAN_COUNT > 0)
int _cmd_can_dump_task(void)
{
    CAN_MSG_HEADER can_header;
    char buffer[8];
    while (can_rec(_cmd_can_can_dev, _cmd_can_fifo_id, &can_header, buffer) == 1)
    {
        _cmd_can_dump(_cmd_can_id, &can_header, buffer);
    }
    return 1;  // not finished
}
#endif
