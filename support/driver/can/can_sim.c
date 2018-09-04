/**
 * @file can_sim.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Uniswarm 2018
 *
 * @date September 3 2018, 17:01 PM
 *
 * @brief CAN udevkit simulator support for simulation purpose
 */

#include "can.h"

// TODO : dummy implementation, please implement me

int can_open(rt_dev_t device)
{
	return 0;
}

int can_close(rt_dev_t device)
{
	return 0;
}

int can_enable(rt_dev_t device)
{
	return 0;
}

int can_disable(rt_dev_t device)
{
	return 0;
}

int can_setMode(rt_dev_t device, CAN_MODE mode)
{
	return 0;
}

CAN_MODE can_mode(rt_dev_t device)
{
	return 0;
}

int can_setBitTiming(rt_dev_t device, uint32_t bitRate, uint8_t propagSeg, uint8_t s1Seg, uint8_t s2Seg)
{
	return 0;
}

uint32_t can_bitRate(rt_dev_t device)
{
	return 0;
}

uint32_t can_effectiveBitRate(rt_dev_t device)
{
	return 0;
}

uint8_t can_propagSeg(rt_dev_t device)
{
	return 0;
}

uint8_t can_s1Seg(rt_dev_t device)
{
	return 0;
}

uint8_t can_s2Seg(rt_dev_t device)
{
	return 0;
}

int can_send(rt_dev_t device, uint8_t fifo, uint32_t id, char *data, uint8_t size, CAN_FLAGS flags)
{
	return 0;
}

int can_rec(rt_dev_t device, uint8_t fifo, uint32_t *id, char *data, uint8_t *size, CAN_FLAGS *flags)
{
	return 0;
}
