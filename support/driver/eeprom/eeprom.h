/**
 * @file eeprom.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2023
 *
 * @date January 18, 2023, 01:45 PM
 *
 * @brief EEPROM memory support drivers
 */

#ifndef EEPROM_H
#define EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "eeprom_device.h"

int eeprom_init(void);

// ===================== Read / write =====================
ssize_t eeprom_read(uint32_t addr, char *data, size_t size);
ssize_t eeprom_write(uint32_t addr, const char *data, size_t size);

// ===================== EEPROM status ====================
bool eeprom_ready(void);
void eeprom_waitForReady(void);

// ===================== dynamic clock ====================
void eeprom_reconfig(void);

#ifdef __cplusplus
}
#endif

#endif  // EEPROM_H
