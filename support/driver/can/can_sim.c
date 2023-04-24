/**
 * @file can_sim.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2023
 *
 * @date September 3 2018, 17:01 PM
 *
 * @brief CAN udevkit simulator support for simulation purpose
 */

#include "can_sim.h"

#include "can.h"

#include <driver/sysclock.h>

#include <stdio.h>
#include <string.h>

#include "simulator.h"

void can_sendconfig(uint8_t can);

static can_sim_dev _cans[] = {
#if CAN_COUNT >= 1
    {.bitRate = 0, .socket = -1, .bus = "can0"},
#endif
#if CAN_COUNT >= 2
    {.bitRate = 0, .socket = -1, .bus = "can1"},
#endif
#if CAN_COUNT >= 3
    {.bitRate = 0, .socket = -1, .bus = "can2"},
#endif
#if CAN_COUNT >= 4
    {.bitRate = 0, .socket = -1, .bus = "can3"},
#endif
};

void can_sendconfig(uint8_t can)
{
    simulator_send(CAN_SIM_MODULE, can, CAN_SIM_CONFIG, (char *)&_cans[can], sizeof(can_sim_dev));
}

rt_dev_t can_getFreeDevice(void)
{
    uint8_t i;
    rt_dev_t device;

    for (i = 0; i < CAN_COUNT; i++)
    {
        if (_cans[i].used == 0)
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
    strcpy(_cans[can].bus, bus);
    return 0;
}

int can_sim_isConnected(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    if (_cans[can].used == 0)
    {
        return 0;
    }

#ifdef SIM_UNIX
    if (_cans[can].socket == -1)
    {
        return 0;
    }

    int error = 0;
    socklen_t len = sizeof(error);
    int retval = getsockopt(_cans[can].socket, SOL_SOCKET, SO_ERROR, &error, &len);
    if (retval != 0 || error != 0)
    {
        can_close(device);
        return 0;
    }
#endif

    return 1;
}

int can_open(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }
    _cans[can].used = 1;
    can_sendconfig(can);

#ifdef SIM_UNIX
    struct ifreq ifr;
    struct sockaddr_can addr;

    // open socket
    _cans[can].socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (_cans[can].socket < 0)
    {
        return -1;
    }

    addr.can_family = AF_CAN;
    strcpy(ifr.ifr_name, _cans[can].bus);

    if (ioctl(_cans[can].socket, SIOCGIFINDEX, &ifr) < 0)
    {
        printf("[CAN] Cannot connect to %s, please create it with theses commands and restart:\r\n", _cans[can].bus);
        printf("\tip link add dev %s type vcan\r\n", _cans[can].bus);
        printf("\tip link set up %s\r\n", _cans[can].bus);
        _cans[can].socket = -1;
        close(_cans[can].socket);
        return -1;
    }

    addr.can_ifindex = ifr.ifr_ifindex;

    fcntl(_cans[can].socket, F_SETFL, O_NONBLOCK);

    if (bind(_cans[can].socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        _cans[can].socket = -1;
        close(_cans[can].socket);
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
    _cans[can].socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_cans[can].socket == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }

    // socket config
    ssin.sin_addr.s_addr = inet_addr("127.0.0.1");
    ssin.sin_family = AF_INET;
    ssin.sin_port = htons(35468);

    // socket connection to host
    if (connect(_cans[can].socket, (SOCKADDR *)&ssin, sizeof(ssin)) != SOCKET_ERROR)
    {
        printf("Connected successfully to port %s %d\n", inet_ntoa(ssin.sin_addr), htons(ssin.sin_port));
    }
    else
    {
        printf("Cannot connect to port %d\n", SIM_SOCKET_PORT);
        closesocket(_cans[can].socket);
        _cans[can].socket = 0;
    }
    u_long ret;
    u_long ul = 1;
    ioctlsocket(_cans[can].socket, FIONBIO, (unsigned long *)&ul);
    if (ret == 0)
    {
        return 0;
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

    _cans[can].used = 0;
    can_sendconfig(can);

#ifdef SIM_UNIX
    close(_cans[can].socket);
#endif

#ifdef SIM_WIN
#    if defined(WIN32)
    WSACleanup();
#    endif

    closesocket(_cans[can].socket);
#endif

    return 0;
}

/**
 * @brief CAN sdk state
 * @param device can device number
 * @return true if can was openned by can_open function
 */
bool can_isOpened(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    return (_cans[can].used == 1);
}

int can_enable(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    _cans[can].enabled = 0;
    can_sendconfig(can);

#ifdef SIM_WIN
    send(_cans[can].socket, "connect:can0\n", 13, 0);
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

    _cans[can].enabled = 0;
    can_sendconfig(can);

    return 0;
}

/**
 * @brief Can sdk enabled state
 * @param device can device number
 * @return true if can was enabled by can_enable function
 */
bool can_isEnabled(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    return (_cans[can].enabled == 1);
}

int can_setMode(rt_dev_t device, CAN_MODE mode)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    _cans[can].mode = mode;
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

    return _cans[can].mode;
}

int can_setBitTiming(rt_dev_t device, uint32_t bitRate, uint8_t propagSeg, uint8_t s1Seg, uint8_t s2Seg)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    _cans[can].bitRate = bitRate;
    _cans[can].propagSeg = propagSeg;
    _cans[can].s1Seg = s1Seg;
    _cans[can].s2Seg = s2Seg;
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

    return _cans[can].bitRate;
}

uint32_t can_effectiveBitRate(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    return _cans[can].bitRate;
}

uint8_t can_propagSeg(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    return _cans[can].propagSeg;
}

uint8_t can_s1Seg(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    return _cans[can].s1Seg;
}

uint8_t can_s2Seg(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    return _cans[can].s2Seg;
}

int can_setTxFifo(rt_dev_t device, uint8_t fifo, uint8_t messageCount)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    // TODO implement me
    return 0;
}

int can_setRxFifo(rt_dev_t device, uint8_t fifo, uint8_t messageCount)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    // TODO implement me
    return 0;
}

int can_setFifoHandler(rt_dev_t device, void (*handler)(uint8_t fifo, uint8_t event))
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    // TODO implement me
    return 0;
}

int can_setFifoEventsHandler(rt_dev_t device, uint8_t fifo, CAN_FIFO_EVENTS eventBits)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    // TODO implement me
    return 0;
}

int can_send(rt_dev_t device, uint8_t fifo, CAN_MSG_HEADER *header, const char *data)
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
    retval = write(_cans[can].socket, &frame, sizeof(struct can_frame));
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
    send(_cans[can].socket, sockdata, id + 1, 0);
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

unsigned char can_hexToChar(unsigned char h);

unsigned char can_hexToChar(unsigned char h)
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

#endif

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

    int recvbytes = read(_cans[can].socket, &frame, sizeof(struct can_frame));
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
    int size = recv(_cans[can].socket, sockdata, 50, SOCKET_MODE);
    if (size <= 0)
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
        data[i] = can_hexToChar(sockdata[pos]) * 16 + can_hexToChar(sockdata[pos + 1]);
        pos += 2;
    }
    return 1;
#endif

    return 0;
}

int can_filterSet(rt_dev_t device, uint8_t nFilter, uint8_t fifo, uint32_t idFilter, uint32_t mask, CAN_FRAME_FORMAT_FLAGS frame)
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
