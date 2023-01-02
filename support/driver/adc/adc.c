/**
 * @file adc.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2022
 *
 * @date November 25, 2022, 12:53 PM
 *
 * @brief ADC common functions
 */

#include "adc.h"

bool adc_channelExists(uint8_t channel)
{
    if (channel > ADC_CHANNEL_MAX)
    {
        return false;
    }
    return (((1UL << channel) & ADC_CHANNEL_HAVE_MASK) != 0);
}
