/**
 * @file eeprom_pic32mk.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2023
 *
 * @date January 18, 2023, 01:45 PM
 *
 * @brief EEPROM memory support drivers for PIC32MK
 */

#ifndef EEPROM_PIC32_H
#define EEPROM_PIC32_H

#ifdef __cplusplus
extern "C" {
#endif

int eeprom_readWord(uint32_t addr, uint32_t *data);
int eeprom_writeWord(uint32_t addr, uint32_t *data);

#if defined(DEVICE_32MK0512GPD064) || defined(DEVICE_32MK0512GPD100) || defined(DEVICE_32MK0512GPE064) || defined(DEVICE_32MK0512GPE100)                       \
    || defined(DEVICE_32MK0512GPK064) || defined(DEVICE_32MK0512GPK100) || defined(DEVICE_32MK0512MCF064) || defined(DEVICE_32MK0512MCF100)                    \
    || defined(DEVICE_32MK0512MCM064) || defined(DEVICE_32MK0512MCM100) || defined(DEVICE_32MK1024GPD064) || defined(DEVICE_32MK1024GPD100)                    \
    || defined(DEVICE_32MK1024GPE064) || defined(DEVICE_32MK1024GPE100) || defined(DEVICE_32MK1024GPK064) || defined(DEVICE_32MK1024GPK100)                    \
    || defined(DEVICE_32MK1024MCF064) || defined(DEVICE_32MK1024MCF100) || defined(DEVICE_32MK1024MCM064) || defined(DEVICE_32MK1024MCM100)
#    define EEPROM_COUNT 1
#    define EEPROM_SIZE  4096
#else
#    define EEPROM_COUNT 0
#    define EEPROM_SIZE  0
#endif

#ifdef __cplusplus
}
#endif

#endif  // EEPROM_PIC32_H
