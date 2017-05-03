/**
 * @file d51e5ta7601.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date November 06, 2016, 15:20 AM
 *
 * @brief d51e5ta7601 support driver
 */

#include "board.h"
#include "screenController.h"

#include <archi.h>

#include <stdint.h>

#define WINDOW_XADDR_START  0x0045 // Horizontal Start Address Set
#define WINDOW_XADDR_END    0x0044 // Horizontal End Address Set
#define WINDOW_YADDR_START  0x0047 // Vertical Start Address Set
#define WINDOW_YADDR_END    0x0046 // Vertical End Address Set
#define GRAM_ADR_ROW_S      0x0020 // init to 0 , UPDATE FIRST
#define GRAM_ADR_COL_S      0x0021 // init to 319 , UPDATE LAST
#define GRAMWR              0x0022 // memory write

// <TODO write this functions correctly
void delay_ms(uint16_t ms)
{
    int i, j;
    for(j=0; j<ms; j++) for(i=0; i<6210; i++) asm("NOP");
}

void delay_us(uint16_t us)
{
    int i, j;
    for(j=0; j<us; j++) for(i=0; i<6; i++) asm("NOP");
}
// TODO/>

void gui_ctrl_write_command(uint16_t cmd)
{
    SCREEN_PORT_OUTPUT;
    SCREEN_RS = 0;
    SCREEN_CS = 0;
    SCREEN_PORT_OUT = cmd;
    SCREEN_RW = 0;
    SCREEN_RW = 1;
    SCREEN_CS = 1;
    SCREEN_RS = 1;
}

void gui_ctrl_write_data(uint16_t data)
{
    SCREEN_PORT_OUTPUT;
    SCREEN_CS = 0;
    SCREEN_PORT_OUT = data;
    SCREEN_RW = 0;
    SCREEN_RW = 1;
    SCREEN_CS = 1;
}

uint16_t gui_ctrl_read_data()
{
    uint16_t data;
    SCREEN_PORT_INPUT;
    SCREEN_CS = 0;
    SCREEN_RD = 0;
    asm("NOP");
    data = SCREEN_PORT_IN;
    SCREEN_RD = 1;
    SCREEN_CS = 1;
    return data;
}

void gui_ctrl_write_command_data(uint8_t cmd, uint16_t data)
{
    gui_ctrl_write_command(cmd);
    gui_ctrl_write_data(data);
}

void gui_ctrl_init(rt_dev_t dev)
{
	SCREEN_LEDBL = 1;

    SCREEN_CS = 1;
    SCREEN_RS = 1;
    SCREEN_RW = 1;
    SCREEN_RD = 1;
    SCREEN_RST = 1;
    delay_ms(5);
    SCREEN_RST = 0;
    delay_ms(5);
    SCREEN_RST = 1;
    delay_ms(5);

    gui_ctrl_write_command_data(0x0001, 0x003C);
    gui_ctrl_write_command_data(0x0002, 0x0100);
    gui_ctrl_write_command_data(0x0003, 0x1030);
    gui_ctrl_write_command_data(0x0008, 0x0808);
    gui_ctrl_write_command_data(0x000A, 0x0500);
    gui_ctrl_write_command_data(0x000B, 0x0000);
    gui_ctrl_write_command_data(0x000C, 0x0770);
    gui_ctrl_write_command_data(0x000D, 0x0000);
    gui_ctrl_write_command_data(0x000E, 0x0001);
    gui_ctrl_write_command_data(0x0011, 0x0406);
    gui_ctrl_write_command_data(0x0012, 0x000E);
    gui_ctrl_write_command_data(0x0013, 0x0222);
    gui_ctrl_write_command_data(0x0014, 0x0015);
    gui_ctrl_write_command_data(0x0015, 0x4277);
    gui_ctrl_write_command_data(0x0016, 0x0000);
    gui_ctrl_write_command_data(0x0030, 0x6A50);
    gui_ctrl_write_command_data(0x0031, 0x00C9);
    gui_ctrl_write_command_data(0x0032, 0xC7BE);
    gui_ctrl_write_command_data(0x0033, 0x0003);
    gui_ctrl_write_command_data(0x0036, 0x3443);
    gui_ctrl_write_command_data(0x003B, 0x0000);
    gui_ctrl_write_command_data(0x003C, 0x0000);
    gui_ctrl_write_command_data(0x002C, 0x6A50);
    gui_ctrl_write_command_data(0x002D, 0x00C9);
    gui_ctrl_write_command_data(0x002E, 0xC7BE);
    gui_ctrl_write_command_data(0x002F, 0x0003);
    gui_ctrl_write_command_data(0x0035, 0x3443);
    gui_ctrl_write_command_data(0x0039, 0x0000);
    gui_ctrl_write_command_data(0x003A, 0x0000);
    gui_ctrl_write_command_data(0x0028, 0x6A50);
    gui_ctrl_write_command_data(0x0029, 0x00C9);
    gui_ctrl_write_command_data(0x002A, 0xC7BE);
    gui_ctrl_write_command_data(0x002B, 0x0003);
    gui_ctrl_write_command_data(0x0034, 0x3443);
    gui_ctrl_write_command_data(0x0037, 0x0000);
    gui_ctrl_write_command_data(0x0038, 0x0000);
    delay_ms(20);  // delay 20 ms
    gui_ctrl_write_command_data(0x0012, 0x200E);
    delay_ms(160);  // delay 160 ms
    gui_ctrl_write_command_data(0x0012, 0x2003);
    delay_ms(40);  // delay 40 ms

    gui_ctrl_write_command_data(WINDOW_XADDR_END, 0x013F);
    gui_ctrl_write_command_data(WINDOW_XADDR_START, 0x0000);
    gui_ctrl_write_command_data(WINDOW_YADDR_END, 0x01DF);
    gui_ctrl_write_command_data(WINDOW_YADDR_START, 0x0000);

    gui_ctrl_write_command_data(GRAM_ADR_ROW_S, 0x0000);
    gui_ctrl_write_command_data(GRAM_ADR_COL_S, 0x013F);
    gui_ctrl_write_command_data(0x0007, 0x0012);
    delay_ms(40);  // delay 40 ms
    gui_ctrl_write_command_data(0x0007, 0x0017);
}

void gui_ctrl_setRectScreen(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    gui_ctrl_write_command_data(WINDOW_XADDR_START, y);
    gui_ctrl_write_command_data(WINDOW_XADDR_END, y+h-1);
    gui_ctrl_write_command_data(WINDOW_YADDR_START, x);
    gui_ctrl_write_command_data(WINDOW_YADDR_END, x+w-1);
    gui_ctrl_write_command_data(GRAM_ADR_ROW_S, x);
    gui_ctrl_write_command_data(GRAM_ADR_COL_S, y);

    gui_ctrl_write_command(0x22);
}

void gui_ctrl_setPos(uint16_t x, uint16_t y)
{
    gui_ctrl_write_command_data(GRAM_ADR_ROW_S, x);
    gui_ctrl_write_command_data(GRAM_ADR_COL_S, y);

    gui_ctrl_write_command(0x22);
}

void gui_ctrl_drawPoint(uint16_t x, uint16_t y, uint16_t color)
{
    //uint16_t data;
    gui_ctrl_setPos(x, y);

    gui_ctrl_write_data(color);
    /*data=gui_read_data();
    data=gui_read_data();*/

    // warning fixme double pixel send
    gui_ctrl_write_data(color);
}
