/**
 * @file can_sim.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Uniswarm 2018-2020
 *
 * @date September 3 2018, 17:01 PM
 *
 * @brief CAN udevkit simulator support for simulation purpose
 */

#include "can.h"
#include "can_sim.h"
#include "simulator.h"

#include "driver/sysclock.h"
#include "sys/fifo.h"

#include <stdio.h>
#include <string.h>

#if defined (WIN32) || defined (_WIN32)
    #include <winsock2.h>
    #define SOCKET_MODE 0

#elif defined (linux) || defined (LINUX) || defined (__linux__) \
    || defined (unix) || defined (UNIX) || defined (__unix__) \
    || defined (__APPLE__)
    #include <fcntl.h>
    #include <sys/ioctl.h>
    #include <net/if.h>
    #include <linux/can.h>
    #include <linux/can/raw.h>
#else
  #error can sim not supported for your platform
#endif

static int soc;

#if !defined (CAN_COUNT) || CAN_COUNT==0
    #warning No device
#endif

can_dev cans[] = {
    {.bitRate = 0,
    .bus = "can0"},
#if CAN_COUNT>=2
    {.bitRate = 0,
    .bus = "can1"},
#endif
#if CAN_COUNT>=3
    {.bitRate = 0,
    .bus = "can2"},
#endif
#if CAN_COUNT>=4
    {.bitRate = 0,
    .bus = "can3"},
#endif
};

void can_sendconfig(uint8_t can)
{
    simulator_send(CAN_SIM_MODULE, can, CAN_SIM_CONFIG, (char*)&cans[can], sizeof(can_dev));
}

rt_dev_t can_getFreeDevice()
{
    uint8_t i;
    rt_dev_t device;

    for (i = 0; i < CAN_COUNT; i++)
    {
        if (cans[i].used == 0)
        {
            break;
        }
    }
    if (i == CAN_COUNT)
    {
        return NULLDEV;
    }
    device = MKDEV(DEV_CLASS_CAN, i);

    can_open(i);

    return device;
}

int can_sim_setBus(rt_dev_t device, char *bus)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }
    strcpy(cans[can].bus, bus);
    return 0;
}

int can_open(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }
    cans[can].used = 1;
    can_sendconfig(can);

#ifdef SIM_UNIX
    struct ifreq ifr;
    struct sockaddr_can addr;

    /* open socket */
    soc = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (soc < 0)
    {
        return -1;
    }

    addr.can_family = AF_CAN;
    strcpy(ifr.ifr_name, cans[can].bus);

    if (ioctl(soc, SIOCGIFINDEX, &ifr) < 0)
    {
        return -1;
    }

    addr.can_ifindex = ifr.ifr_ifindex;

    fcntl(soc, F_SETFL, O_NONBLOCK);

    if (bind(soc, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        return -1;
    }
#endif

    return 0;
}

int can_close(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    cans[can].used = 0;
    can_sendconfig(can);

    return 0;
}

int can_enable(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    cans[can].enabled = 0;
    can_sendconfig(can);

    return 0;
}

int can_disable(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    cans[can].enabled = 0;
    can_sendconfig(can);

    return 0;
}

int can_setMode(rt_dev_t device, CAN_MODE mode)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    cans[can].mode = mode;
    can_sendconfig(can);

    return 0;
}

CAN_MODE can_mode(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    return cans[can].mode;
}

int can_setBitTiming(rt_dev_t device, uint32_t bitRate, uint8_t propagSeg, uint8_t s1Seg, uint8_t s2Seg)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    cans[can].bitRate = bitRate;
    cans[can].propagSeg = propagSeg;
    cans[can].s1Seg = s1Seg;
    cans[can].s2Seg = s2Seg;
    can_sendconfig(can);

    return 0;
}

uint32_t can_bitRate(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    return cans[can].bitRate;
}

uint32_t can_effectiveBitRate(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    return cans[can].bitRate;
}

uint8_t can_propagSeg(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    return cans[can].propagSeg;
}

uint8_t can_s1Seg(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    return cans[can].s1Seg;
}

uint8_t can_s2Seg(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    return cans[can].s2Seg;
}

int can_send(rt_dev_t device, uint8_t fifo, CAN_MSG_HEADER *header, char *data)
{
    UDK_UNUSED(fifo);

    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

#ifdef SIM_UNIX
    int retval, i;
    struct can_frame frame;

    frame.can_id = header->id;

    if((header->flags & CAN_VERS2BA) == CAN_VERS2BA)
    {
        frame.can_id += 0x80000000;
    }

    if (header->size > 8)
    {
        header->size = 8;
    }
    frame.can_dlc = header->size; // Data Length
    for (i=0; i < header->size; i++)
    {
        frame.data[i] = data[i];
    }
    retval = write(soc, &frame, sizeof(struct can_frame));
    if (retval != sizeof(struct can_frame))
    {
        return -1;
    }
// TODO format data
    //simulator_send(CAN_SIM_MODULE, can, CAN_SIM_WRITE, data, size);
#endif

    return 1;
}

int can_rec(rt_dev_t device, uint8_t fifo, CAN_MSG_HEADER *header, char *data)
{
    UDK_UNUSED(fifo);

    int i;
    ssize_t size_read;
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }
    // TODO
    /*simulator_rec_task();
    size_read = simulator_recv(CAN_SIM_MODULE, can, CAN_SIM_READ, data, 64);
    if (size_read < 0)
        size_read = 0;*/

#ifdef SIM_UNIX
    struct can_frame frame;

    int recvbytes = read(soc, &frame, sizeof(struct can_frame));
    if (recvbytes >= 0)
    {
        header->id = frame.can_id & 0x1FFFFFFF;
        header->size = frame.can_dlc; // Data Length
        header->flags = 0;
        if ((frame.can_id & 0x80000000))
        {
            header->flags += CAN_VERS2BA;
        }
        if ((frame.can_id & CAN_RTR_FLAG) != 0)
        {
            header->flags += CAN_RTR;
        }

        for (i=0; i < header->size; i++)
        {
            data[i] = (char)frame.data[i];
        }
        return 1;
    }
#endif

    can_sim_frame sim_frame;
    simulator_rec_task();
    size_read = simulator_recv(CAN_SIM_MODULE, can, CAN_SIM_READ, (char*)&sim_frame, sizeof(sim_frame));
    if (size_read < 0)
    {
        return 0;
    }

    header->id = sim_frame.can_id;
    header->size = sim_frame.can_dlc; // Data Length
    for (i=0; i < header->size; i++)
    {
        data[i] = sim_frame.data[i];
    }
    //printf("dlc = %d, data = %s\n", frame.can_dlc, frame.data);
    // TODO format data

    return 0;
}

int can_filterConfiguration(rt_dev_t device, uint8_t nFilter, uint8_t fifo,
			    uint32_t idFilter, uint32_t mask, CAN_FRAME_FORMAT_FLAGS frame)
{
    UDK_UNUSED(idFilter);
    UDK_UNUSED(mask);
    UDK_UNUSED(frame);

    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    if ((nFilter > CAN_FILTER_COUNT) || (fifo > CAN_FIFO_COUNT))
    {
        return -1;
    }

   //TODO
        // simulator_filterConfiguration

    return 0;
}

int can_filterEnable(rt_dev_t device, uint8_t nFilter)
{

    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    if (nFilter > CAN_FILTER_COUNT)
    {
        return -1;
    }

    //TODO
    // simulator_filterEnable

    return 0;
}


int can_filterDisable(rt_dev_t device, uint8_t nFilter)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    if (nFilter > CAN_FILTER_COUNT)
    {
        return -1;
    }

    //TODO
    // simulator_filterDisable

    return 0;

}
