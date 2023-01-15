/**
 * @file pic32mk.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2023
 *
 * @date July 10, 2017, 16:15 PM
 *
 * @brief Architecture low level definitions for PIC32MK
 */

#include <archi.h>

void archi_init(void)
{
    // enable multiple vector interrupts
    INTCONSET = _INTCON_MVEC_MASK;

#if defined(DEVICE_32MK0512GPD064) || defined(DEVICE_32MK0512GPD100) || defined(DEVICE_32MK0512GPE064) || defined(DEVICE_32MK0512GPE100)                       \
    || defined(DEVICE_32MK0512MCF064) || defined(DEVICE_32MK0512MCF100) || defined(DEVICE_32MK1024GPD064) || defined(DEVICE_32MK1024GPD100)                    \
    || defined(DEVICE_32MK1024GPE064) || defined(DEVICE_32MK1024GPE100) || defined(DEVICE_32MK1024MCF064) || defined(DEVICE_32MK1024MCF100)
    PRISS = 0x11110000;  // interrupts with priority >= 4 use shadow reg set 1, other shadows reg set 0
#else
    PRISS = 0x76543210;  // Shadows registers assigned to each priority
#endif
    enable_interrupt();
}

void archi_prefetch_enable(void)
{
    _mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, (_mfc0(_CP0_CONFIG, _CP0_CONFIG_SELECT) | 0x3));
}

void archi_prefetch_disable(void)
{
    _mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, ((_mfc0(_CP0_CONFIG, _CP0_CONFIG_SELECT) & 0xFFFFFFFC) | 0x2));
}
