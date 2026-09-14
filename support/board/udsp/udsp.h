/**
 * @file curiosity_dsPIC33AK128MC106.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2026
 *
 * @date September 13, 2026, 02:51 PM
 *
 * @brief Board support package for uDSP board
 */

#ifndef UDSP_H
#define UDSP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <archi.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME    "uDSP"
#define SYSCLOCK_XTAL 8000000

#define LED_COUNT    0
#define BUTTON_COUNT 0

#define CODEC_PDN LATBbits.LATB7

#ifdef __cplusplus
}
#endif

#endif  // UDSP_H
