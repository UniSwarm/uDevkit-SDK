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
    switch (channel)
    {
#ifdef ADC_CHANNEL_HAVE_CH0
        case 0:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH1
        case 1:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH2
        case 2:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH3
        case 3:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH4
        case 4:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH5
        case 5:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH6
        case 6:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH7
        case 7:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH8
        case 8:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH9
        case 9:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH10
        case 10:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH11
        case 11:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH12
        case 12:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH13
        case 13:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH14
        case 14:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH15
        case 15:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH16
        case 16:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH17
        case 17:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH18
        case 18:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH19
        case 19:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH20
        case 20:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH21
        case 21:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH22
        case 22:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH23
        case 23:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH24
        case 24:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH25
        case 25:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH26
        case 26:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH27
        case 27:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH28
        case 28:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH29
        case 29:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH30
        case 30:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH31
        case 31:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH32
        case 32:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH33
        case 33:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH34
        case 34:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH35
        case 35:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH36
        case 36:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH37
        case 37:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH38
        case 38:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH39
        case 39:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH40
        case 40:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH41
        case 41:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH42
        case 42:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH43
        case 43:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH44
        case 44:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH45
        case 45:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH46
        case 46:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH47
        case 47:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH48
        case 48:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH49
        case 49:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH50
        case 50:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH51
        case 51:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH52
        case 52:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH53
        case 53:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH54
        case 54:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH55
        case 55:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH56
        case 56:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH57
        case 57:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH58
        case 58:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH59
        case 59:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH60
        case 60:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH61
        case 61:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH62
        case 62:
            return true;
#endif
#ifdef ADC_CHANNEL_HAVE_CH63
        case 63:
            return true;
#endif
    }
    return false;
}
