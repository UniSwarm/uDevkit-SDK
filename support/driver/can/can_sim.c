/**
 * @file can_sim.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Uniswarm 2018-2020
 *
 * @date September 3 2018, 17:01 PM
 *
 * @brief CAN udevkit simulator support for simulation purpose
 */

#include "can_sim.h"
#include "can.h"
#include "simulator.h"

#include "driver/sysclock.h"
#include "sys/fifo.h"

#include <stdio.h>
#include <string.h>

#if defined(WIN32) || defined(_WIN32)
#    include <winsock2.h>
#    define SOCKET_MODE 0
SOCKET sim_can;

#elif defined(linux) || defined(LINUX) || defined(__linux__) || defined(unix) || defined(UNIX) || defined(__unix__) || \
    defined(__APPLE__)
#    include <fcntl.h>
#    include <linux/can.h>
#    include <linux/can/raw.h>
#    include <net/if.h>
#    include <sys/ioctl.h>
#else
#    error can sim not supported for your platform
#endif

#if !defined(CAN_COUNT) || CAN_COUNT == 0
#    warning No device
#endif

/****************************************************************************************/
/*          Privates functions                                                          */
void can_sendconfig(uint8_t can);

/****************************************************************************************/
/*          External variable                                                           */

/****************************************************************************************/
/*          Local variable                                                              */
int soc;
can_dev cans[] = {
    {.bitRate = 0, .bus = "can0"},
#if CAN_COUNT >= 2
    {.bitRate = 0, .bus = "can1"},
#endif
#if CAN_COUNT >= 3
    {.bitRate = 0, .bus = "can2"},
#endif
#if CAN_COUNT >= 4
    {.bitRate = 0, .bus = "can3"},
#endif
};

void can_sendconfig(uint8_t can)
{
    simulator_send(CAN_SIM_MODULE, can, CAN_SIM_CONFIG, (char *)&cans[can], sizeof(can_dev));
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
#ifdef SIM_WIN
    SOCKADDR_IN ssin;

#    if defined(WIN32) || defined(_WIN32)
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2, 2), &WSAData);
#    endif

    // socket creation
    sim_can = socket(AF_INET, SOCK_STREAM, 0);
    if (sim_can == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }

    // socket config
    ssin.sin_addr.s_addr = inet_addr("127.0.0.1");
    ssin.sin_family = AF_INET;
    ssin.sin_port = htons(35468);

    // socket connection to host
    if (connect(sim_can, (SOCKADDR *)&ssin, sizeof(ssin)) != SOCKET_ERROR)
    {
        printf("Connected successfully to port %s %d\n", inet_ntoa(ssin.sin_addr), htons(ssin.sin_port));
    }
    else
    {
        printf("Cannot connect to port %d\n", SIM_SOCKET_PORT);
        closesocket(sim_can);
        sim_can = 0;
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

#ifdef SIM_WIN
#    if defined(WIN32)
    WSACleanup();
#    endif

    closesocket(sim_can);
#endif

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

#ifdef SIM_WIN
    send(sim_can, "connect:can0\n", 13, 0);
    usleep(100);
#endif

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

    if ((header->flags & CAN_VERS2BA) == CAN_VERS2BA)
    {
        frame.can_id += 0x80000000;
    }

    if (header->size > 8)
    {
        header->size = 8;
    }
    frame.can_dlc = header->size;  // Data Length
    for (i = 0; i < header->size; i++)
    {
        frame.data[i] = data[i];
    }
    retval = write(soc, &frame, sizeof(struct can_frame));
    if (retval != sizeof(struct can_frame))
    {
        return -1;
    }
#endif

#ifdef SIM_WIN
    char sockdata[20];
    int id;
    id = sprintf(sockdata, "can0:%d##", header->id);
    for (int i = 0; i < header->size; i++)
    {
        sprintf(sockdata + id, "%02X", (unsigned char)data[i]);
        id += 2;
    }
    sockdata[id] = '\n';
    send(sim_can, sockdata, id + 1, 0);
#endif

    return 1;
}

#ifdef SIM_WIN
static const char RemoteRequestFlag = 'R';
static const char ExtendedFormatFlag = 'X';
static const char FlexibleDataRateFlag = 'F';
static const char BitRateSwitchFlag = 'B';
static const char ErrorStateFlag = 'E';
static const char LocalEchoFlag = 'L';
#endif

unsigned char hexToChar(unsigned char h)
{
    if (h >= '0' && h <= '9')
    {
        return h - '0';
    }
    if (h >= 'a' && h <= 'f')
    {
        return h - 'a' + 10;
    }
    if (h >= 'A' && h <= 'F')
    {
        return h - 'A' + 10;
    }
    return 0;
}

int can_rec(rt_dev_t device, uint8_t fifo, CAN_MSG_HEADER *header, char *data)
{
    UDK_UNUSED(fifo);

    int i;
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

#ifdef SIM_UNIX
    struct can_frame frame;

    int recvbytes = read(soc, &frame, sizeof(struct can_frame));
    if (recvbytes >= 0)
    {
        header->id = frame.can_id & 0x1FFFFFFF;
        header->size = frame.can_dlc;  // Data Length
        header->flags = 0;
        if ((frame.can_id & 0x80000000))
        {
            header->flags += CAN_VERS2BA;
        }
        if ((frame.can_id & CAN_RTR_FLAG) != 0)
        {
            header->flags += CAN_RTR;
        }

        for (i = 0; i < header->size; i++)
        {
            data[i] = (char)frame.data[i];
        }
        return 1;
    }
#endif

#ifdef SIM_WIN
    char sockdata[50];
    u_long ret;
    ioctlsocket(sim_can, FIONREAD, &ret);
    if (ret == 0)
    {
        return 0;
    }
    int size = recv(sim_can, sockdata, 50, SOCKET_MODE);
    if (size < 0)
    {
        return 0;
    }

    int id;
    int pos;
    sscanf(sockdata, "%d#%n", &id, &pos);
    header->id = id;
    header->flags = 0;
    while (sockdata[pos] != '#')
    {
        if (sockdata[pos] == RemoteRequestFlag)
        {
            header->flags += CAN_RTR;
        }
        if (sockdata[pos] == ExtendedFormatFlag)
        {
            header->flags += CAN_VERS2BA;
        }
        pos++;
    }
    pos++;
    header->size = (size - pos - 1) / 2;
    if (header->size > 8)
    {
        header->size = 8;
    }
    for (i = 0; i < header->size; i++)
    {
        data[i] = hexToChar(sockdata[pos]) * 16 + hexToChar(sockdata[pos + 1]);
        pos += 2;
    }
    return 1;
#endif

    return 0;
}

int can_filterConfiguration(rt_dev_t device,
                            uint8_t nFilter,
                            uint8_t fifo,
                            uint32_t idFilter,
                            uint32_t mask,
                            CAN_FRAME_FORMAT_FLAGS frame)
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

    // TODO
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

    // TODO
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

    // TODO
    // simulator_filterDisable

    return 0;
}
