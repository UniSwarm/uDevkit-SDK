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
#define BOARD_IN0_ADC_CHAN 12
#define BOARD_IN1_ADC_CHAN 0
#define BOARD_IN2_ADC_CHAN 1  // ANA1
#define BOARD_IN3_ADC_CHAN 9
#define BOARD_IN4_ADC_CHAN 3
uint8_t board_analogin(uint8_t io);

// outs
#define LED_LAT LATBbits.LATB2

// IOs
#define IO1_LAT LATDbits.LATD1
#define IO2_LAT LATDbits.LATD0
#define IO3_LAT LATBbits.LATB10
#define IO4_LAT LATBbits.LATB11
#define IO5_LAT LATBbits.LATB12
#define IO6_LAT LATBbits.LATB13
#define IO7_LAT LATBbits.LATB14
#define IO8_LAT LATBbits.LATB15

#define I09_LAT LATCbits.LATC12
#define I10_LAT LATCbits.LATC13
#define I11_LAT LATCbits.LATC14
#define I12_LAT LATCbits.LATC15
#define I13_LAT LATDbits.LATD15
#define I14_LAT LATDbits.LATD14
#define I15_LAT LATDbits.LATD12
#define I16_LAT LATCbits.LATC8

#define I17_LAT LATCbits.LATC9
#define I18_LAT LATDbits.LATD9
#define I19_LAT LATDbits.LATD8
#define I20_LAT LATDbits.LATD7
#define I21_LAT LATDbits.LATD6
#define I22_LAT LATDbits.LATD5
#define I23_LAT LATBbits.LATB5
#define I24_LAT LATBbits.LATB6

#define I25_LAT LATCbits.LATC4
#define I26_LAT LATCbits.LATC5
#define I27_LAT LATCbits.LATC10
#define I28_LAT LATCbits.LATC11
#define I29_LAT LATDbits.LATD4
#define I30_LAT LATDbits.LATD3
#define I31_LAT LATDbits.LATD2
#define I32_LAT LATBbits.LATB9

#ifdef __cplusplus
}
#endif

#endif  // UIO32TEST_H
