/**
 * @file uio44.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2022
 *
 * @date November 28, 2018, 09:30 AM
 *
 * @brief Code for UIO44(FR) / UIO44(FR)-I board
 *
 * product page:
 *  https://uniswarm.eu/uboards/uio/uio44
 */

#ifndef UIO44FR_H
#define UIO44FR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <archi.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME    "UIO44FR"
#define SYSCLOCK_POSC 24000000  // 24MHz

// ==== pins define ====
// leds
#define LED_COUNT     6
#define LEDOUT1       0
#define LEDOUT2       1
#define LEDOUT3       2
#define LEDOUT4       3
#define LED5          4  // RS485 err
#define LED_RS485_ERR LED5
#define LED6          5  // CAN err
#define LED_CANFD_ERR LED6
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// coms
#define CAN_ID_CAN_BUS    1
#define UART_ID_RS485_BUS 1
#define UART_ID_DBG       2

// buttons
#define BUTTON_COUNT 0
int8_t board_getButton(uint8_t button);

// outs
#define OUT_COUNT 4
typedef enum
{
    DO_OFF,
    DO_OPEN_DRAIN,
    DO_OPEN_SOURCE,
    DO_PUSH_PULL
} DO_MODE;
int board_setIO(uint8_t io, uint16_t state);
int board_setIOMode(uint8_t io, DO_MODE mode);
#define board_setIOPWMFrequency(a, b)

// Analog input
#define ANALOGIN_COUNT     4
#define BOARD_IN0_ADC_CHAN 0
#define BOARD_IN1_ADC_CHAN 1
#define BOARD_IN2_ADC_CHAN 9
#define BOARD_IN3_ADC_CHAN 3
uint8_t board_analogin(uint8_t io);

// Memory page adress
#define ADRESS_PAGE_1_COM 0x52000
#define ADRESS_PAGE_2_MS  0x53000
#define ADRESS_PAGE_3_APP 0x54000
#define ADRESS_PAGE_4_APP 0x55000
#define ADRESS_PAGE_5_CAL 0x56000

#define OTP_SECTOR_BEGINADDR      (0x801700 * 2)
#define OTP_SECTOR_SECTOR_ENDADDR (0x801800 * 2)
#define OTPSECTOR_BYTE_SIZE       (OTP_SECTOR_SECTOR_ENDADDR - OTP_SECTOR_BEGINADDR)

#ifdef __cplusplus
}
#endif

#endif  // UIO44FR_H
