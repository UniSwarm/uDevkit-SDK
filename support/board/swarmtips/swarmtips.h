/**
 * @file swarmtips.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2021
 *
 * @date August 13, 2016, 12:04 PM
 *
 * @brief Definitions for Swarmtips platform from Robotips
 */

#ifndef SWARMTIPS_H
#define SWARMTIPS_H

#include <archi.h>

#include <stdint.h>
#include <driver/device.h>

int board_init(void);

#define BOARD_NAME "swarmtips"

// ==== pins define ====

// voltage measurement
#define BOARD_VOLT_IN 8 // RB8		// analog board voltage channel

// leds
#define LED_COUNT 3
#define LED1 LATBbits.LATB3
#define LED2 LATDbits.LATD11
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

#define BUTTON_COUNT 0
int8_t board_getButton(uint8_t button);

// motors pins
#define M1A LATEbits.LATE4          // A pin direction
#define M1B LATEbits.LATE6          // B pin direction

#define M2A LATEbits.LATE1          // A pin direction
#define M2B LATEbits.LATE3          // B pin direction

// ==== motor config ====
#define MOTOR_COUNT 2

// ESP8266
#define ESP8266_UART 1

rt_dev_t board_i2c_tof(void);
#define TOF_ADDR       0x52


#endif // SWARMTIPS_H
