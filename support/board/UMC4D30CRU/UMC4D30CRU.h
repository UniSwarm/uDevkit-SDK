/**
 * @file UMC4D30CRU.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2023
 *
 * @date March 21, 2018, 20:00 PM
 *
 * @brief Code for UMC4D30CRU board (or UMC4D30CRU-I)
 *
 * product page:
 *  http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=DM320106
 * datasheet:
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005316A.pdf
 */

#ifndef UMC4D30CRU_H
#define UMC4D30CRU_H

#ifdef __cplusplus
extern "C" {
#endif

#include <archi.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME    "UMC4D30CRU"
#define SYSCLOCK_XTAL 24000000

// ==== pins define ====
// leds
#define LED_COUNT 6
#define LED1      LATAbits.LATA8  // OC9
#define LED2      IOCON2bits.OVRDAT
#define LEDM1     LATGbits.LATG15
#define LEDM2     LATDbits.LATD13
#define LEDM3     LATGbits.LATG11
#define LEDM4     LATBbits.LATB13
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// analog pins
#define Imot1  3
#define BefmA1 4
#define BefmB1 5
#define Temp1  21

#define Imot2  0
#define BefmA2 1
#define BefmB2 2
#define Temp2  45

#define Imot3  6
#define BefmA3 24
#define BefmB3 25
#define Temp3  38

#define Imot4  9
#define BefmA4 7
#define BefmB4 8
#define Temp4  20

#define Temp   36
#define VPower 11

#define PMW1 5
#define PMW2 2
#define PMW3 3
#define PMW4 4

#define AM1    IOCON5bits.OVRDAT
#define BM1    LATGbits.LATG7
#define FailM1 PORTGbits.RG6

#define AM2    LATBbits.LATB9
#define BM2    LATDbits.LATD8
#define FailM2 PORTBbits.RB8

#define AM3    LATDbits.LATD6
#define BM3    LATDbits.LATD5
#define FailM3 PORTCbits.RC9

#define AM4    LATGbits.LATG8
#define BM4    LATGbits.LATG10
#define FailM4 PORTGbits.RG9

// buttons
#define BUTTON_COUNT 0
int8_t board_getButton(uint8_t button);

#ifdef __cplusplus
}
#endif

#endif  // UMC4D30CRU_H
