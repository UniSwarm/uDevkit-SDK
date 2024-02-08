/**
 * @file uio32test.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2024
 *
 * @date January 21, 2024, 10:30 AM
 *
 * @brief Board support package for UIO32TEST board
 *
 * product page:
 *  https://uniswarm.eu/uboards/uio/uio32test
 */

#ifndef UIO32TEST_H
#define UIO32TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <archi.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME    "UIO32TEST"
#define SYSCLOCK_POSC 24000000  // 24MHz

// ==== pins define ====
// leds
#define LED_COUNT 1
#define LEDOUT1   0
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// coms
#define CAN_ID_CAN_BUS    1
#define UART_ID_RS485_BUS 1

// buttons
#define BUTTON_COUNT 0
int8_t board_getButton(uint8_t button);

// DIPs
#define DIP1 PORTCbits.RC3
#define DIP2 PORTCbits.RC2
#define DIP3 PORTCbits.RC1
#define DIP4 PORTCbits.RC0
uint8_t board_dipId(void);

// Analog input
#define ANALOGIN_COUNT     5
#define VOLTAGEIN_ADC_CHAN 16
#define BOARD_IN1_ADC_CHAN 0
#define BOARD_IN2_ADC_CHAN 1  // ANA1
#define BOARD_IN3_ADC_CHAN 9
#define BOARD_IN4_ADC_CHAN 3
uint8_t board_analogin(uint8_t io);

// outs
#define LED_LAT LATBbits.LATB2

// IOs
uint32_t portsToGlobal32(uint16_t ports[]);
void global32ToPorts(uint32_t global, uint16_t ports[]);

#define IO01_LAT LATDbits.LATD1
#define IO02_LAT LATDbits.LATD0
#define IO03_LAT LATBbits.LATB10
#define IO04_LAT LATBbits.LATB11
#define IO05_LAT LATBbits.LATB12
#define IO06_LAT LATBbits.LATB13
#define IO07_LAT LATBbits.LATB14
#define IO08_LAT LATBbits.LATB15

#define IO09_LAT LATCbits.LATC12
#define IO10_LAT LATCbits.LATC13
#define IO11_LAT LATCbits.LATC14
#define IO12_LAT LATCbits.LATC15
#define IO13_LAT LATDbits.LATD15
#define IO14_LAT LATDbits.LATD14
#define IO15_LAT LATDbits.LATD12
#define IO16_LAT LATCbits.LATC8

#define IO17_LAT LATCbits.LATC9
#define IO18_LAT LATDbits.LATD9
#define IO19_LAT LATDbits.LATD8
#define IO20_LAT LATDbits.LATD7
#define IO21_LAT LATDbits.LATD6
#define IO22_LAT LATDbits.LATD5
#define IO23_LAT LATBbits.LATB5
#define IO24_LAT LATBbits.LATB6

#define IO25_LAT LATCbits.LATC4
#define IO26_LAT LATCbits.LATC5
#define IO27_LAT LATCbits.LATC10
#define IO28_LAT LATCbits.LATC11
#define IO29_LAT LATDbits.LATD4
#define IO30_LAT LATDbits.LATD3
#define IO31_LAT LATDbits.LATD2
#define IO32_LAT LATBbits.LATB9

// TRIS
#define IO01_TRIS TRISDbits.TRISD1
#define IO02_TRIS TRISDbits.TRISD0
#define IO03_TRIS TRISBbits.TRISB10
#define IO04_TRIS TRISBbits.TRISB11
#define IO05_TRIS TRISBbits.TRISB12
#define IO06_TRIS TRISBbits.TRISB13
#define IO07_TRIS TRISBbits.TRISB14
#define IO08_TRIS TRISBbits.TRISB15

#define IO09_TRIS TRISCbits.TRISC12
#define IO10_TRIS TRISCbits.TRISC13
#define IO11_TRIS TRISCbits.TRISC14
#define IO12_TRIS TRISCbits.TRISC15
#define IO13_TRIS TRISDbits.TRISD15
#define IO14_TRIS TRISDbits.TRISD14
#define IO15_TRIS TRISDbits.TRISD12
#define IO16_TRIS TRISCbits.TRISC8

#define IO17_TRIS TRISCbits.TRISC9
#define IO18_TRIS TRISDbits.TRISD9
#define IO19_TRIS TRISDbits.TRISD8
#define IO20_TRIS TRISDbits.TRISD7
#define IO21_TRIS TRISDbits.TRISD6
#define IO22_TRIS TRISDbits.TRISD5
#define IO23_TRIS TRISBbits.TRISB5
#define IO24_TRIS TRISBbits.TRISB6

#define IO25_TRIS TRISCbits.TRISC4
#define IO26_TRIS TRISCbits.TRISC5
#define IO27_TRIS TRISCbits.TRISC10
#define IO28_TRIS TRISCbits.TRISC11
#define IO29_TRIS TRISDbits.TRISD4
#define IO30_TRIS TRISDbits.TRISD3
#define IO31_TRIS TRISDbits.TRISD2
#define IO32_TRIS TRISBbits.TRISB9

#ifdef __cplusplus
}
#endif

#endif  // UIO32TEST_H
