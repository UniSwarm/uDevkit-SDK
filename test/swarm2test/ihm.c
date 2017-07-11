#include "ihm.h"

#include "board.h"
#include "module/gui.h"
#include "fonts.h"

#include "module/network.h"
#include "motors.h"

#include <stdio.h>

int ihm_count = 0;

int ihm_d1, ihm_d2, ihm_d3;

void ihm_screenClear();

#define SCREEN_COUNT 4
int8_t screen_id = 1;
int8_t screen_btn = 0;
void ihm_screenTof();
void ihm_screenBatt();
void ihm_screenCoder();
void ihm_screenWifi();

void ihm_init()
{
    gui_init(board_i2c_ihm());
    gui_setFont(&Lucida_Console10);
    gui_setBrushColor(0);
    gui_setPenColor(1);

    ihm_screenClear();
}

void ihm_screenClear()
{
    gui_drawFillRect(0, 0, 127, 63);
    gui_drawRect(0, 0, 127, 63);
    gui_drawLine(0, 15, 127, 15);
    gui_ctrl_update();
}

void ihm_task()
{
    int8_t btn = 0;

    // process buttons
    if (board_button(0) == 1)
        btn = 1;
    else if (board_button(1) == 1)
        btn = 2;
    else if (board_button(2) == 1)
        btn = 3;

    if (screen_btn == 0 && btn != 0)
    {
        // one button pressed
        //board_buzz(400);
        if (btn == 1)
        {
            screen_id++;
            ihm_screenClear();
        }
        if (btn == 2)
        {
            screen_id--;
            ihm_screenClear();
        }
        if (screen_id < 0)
            screen_id = SCREEN_COUNT - 1;
        if (screen_id >= SCREEN_COUNT)
            screen_id = 0;
        screen_btn = btn;
    }
    else
    {
        // no button pressed
        screen_btn = btn;
        //board_buzz(0);
    }

    // exec only one time on 10
    ihm_count++;
    if (ihm_count <= 5)
        return;
    ihm_count = 0;

    // call current ihm screen
    switch (screen_id)
    {
    case 0:
        ihm_screenTof();
        break;
    case 1:
        ihm_screenBatt();
        break;
    case 2:
        ihm_screenCoder();
        break;
    case 3:
        ihm_screenWifi();
        break;
    }
}

void ihm_screenTof()
{
    char text[60];
    gui_drawTextRect(1, 1, 126, 14, "<  swt2 : tof  >", GUI_FONT_ALIGN_VMIDDLE | GUI_FONT_ALIGN_HMIDDLE);

    gui_setBrushColor(0);
    sprintf(text, "%d", (int)ihm_d1);
    gui_drawTextRect(1, 50, 42, 13, text, GUI_FONT_ALIGN_VMIDDLE | GUI_FONT_ALIGN_HTOP);
    gui_setBrushColor(0); gui_drawFillRect(22, 18, 2, 33); // clear bar
    gui_setBrushColor(1); gui_drawFillRect(22, 19+30-ihm_d1/8, 2, ihm_d1/8);

    sprintf(text, "%d", (int)ihm_d2);
    gui_setBrushColor(0);
    gui_drawTextRect(43, 50, 42, 13, text, GUI_FONT_ALIGN_VMIDDLE | GUI_FONT_ALIGN_HTOP);
    gui_setBrushColor(0); gui_drawFillRect(40+24, 18, 2, 33); // clear bar
    gui_setBrushColor(1); gui_drawFillRect(40+24, 19+30-ihm_d2/8, 2, ihm_d2/8);

    sprintf(text, "%d", (int)ihm_d3);
    gui_setBrushColor(0);
    gui_drawTextRect(85, 50, 42, 13, text, GUI_FONT_ALIGN_VMIDDLE | GUI_FONT_ALIGN_HTOP);
    gui_setBrushColor(0); gui_drawFillRect(82+24, 18, 2, 33); // clear bar
    gui_setBrushColor(1); gui_drawFillRect(82+24, 19+30-ihm_d3/8, 2, ihm_d3/8);

    gui_setBrushColor(0);
    gui_ctrl_update();
}

void ihm_screenBatt()
{
    char text[60];
    float ihm_batt = board_getPowerVoltage();
    gui_drawTextRect(1, 1, 126, 14, "< swt2 : battery >", GUI_FONT_ALIGN_VMIDDLE | GUI_FONT_ALIGN_HMIDDLE);

    sprintf(text, "voltage : %.2fv", ihm_batt);
    gui_drawTextRect(5, 22, 118, 15, text, GUI_FONT_ALIGN_VMIDDLE | GUI_FONT_ALIGN_HMIDDLE);

    int i, x=33, y=42, percent=(ihm_batt-3.3)*100;
    if(percent > 100)
        percent = 100;
    if(percent < 0)
        percent = 0;

    gui_setBrushColor(0);
    gui_setPenColor(1);
    gui_drawRect(x, y, 26, 12);
    for (i=0; i<=percent/5; i++)
    {
        gui_drawLine(x+3+i,   y+4, x+3+i,   y+8);
    }
    gui_setPenColor(0);
    for (; i<=20; i++)
    {
        gui_drawLine(x+3+i,   y+4, x+3+i,   y+8);
    }

    gui_setPenColor(1);
    gui_drawLine(x+27, y+7, x+27, y+3);
    gui_drawLine(x+28, y+7, x+28, y+3);

    sprintf(text, "%d%%", percent);
    gui_drawTextRect(x+35, y, 55, 14, text, GUI_FONT_ALIGN_VLEFT | GUI_FONT_ALIGN_HTOP);

    if (CHARGER_CHARGING == 0)
        gui_drawTextRect(3, y, 30, 14, "chrg", GUI_FONT_ALIGN_VLEFT | GUI_FONT_ALIGN_HTOP);
    else
        gui_drawTextRect(3, y, 30, 14, " ", GUI_FONT_ALIGN_VLEFT | GUI_FONT_ALIGN_HTOP);

    gui_ctrl_update();
}

void ihm_screenCoder()
{
    char text[60];
    gui_drawTextRect(1, 1, 126, 14, "< swt2 : coders >", GUI_FONT_ALIGN_VMIDDLE | GUI_FONT_ALIGN_HMIDDLE);
    gui_drawLine(63, 15, 63, 63);

    // left coder
    gui_drawTextRect(1, 18, 62, 14, "left", GUI_FONT_ALIGN_VMIDDLE | GUI_FONT_ALIGN_HMIDDLE);
    gui_setBrushColor(C2A);
    gui_drawRect(20-5, 38-5, 9, 9);
    gui_drawFillRect(20-3, 38-3, 6, 6);
    gui_setBrushColor(C2B);
    gui_drawRect(40-5, 38-5, 9, 9);
    gui_drawFillRect(40-3, 38-3, 6, 6);
    sprintf(text, "%d", getC2());
    gui_setBrushColor(0);
    gui_drawTextRect(2, 48, 60, 14, text, GUI_FONT_ALIGN_VMIDDLE | GUI_FONT_ALIGN_HMIDDLE);

    // right coder
    gui_drawTextRect(64, 18, 62, 14, "right", GUI_FONT_ALIGN_VMIDDLE | GUI_FONT_ALIGN_HMIDDLE);
    gui_setBrushColor(C1A);
    gui_drawRect(63+20-5, 38-5, 9, 9);
    gui_drawFillRect(63+20-3, 38-3, 6, 6);
    gui_setBrushColor(C1B);
    gui_drawRect(63+40-5, 38-5, 9, 9);
    gui_drawFillRect(63+40-3, 38-3, 6, 6);
    sprintf(text, "%d", getC1());
    gui_setBrushColor(0);
    gui_drawTextRect(64, 48, 48, 14, text, GUI_FONT_ALIGN_VMIDDLE | GUI_FONT_ALIGN_HMIDDLE);

    gui_ctrl_update();
}

void ihm_screenWifi()
{
    char text[60];
    gui_drawTextRect(1, 1, 126, 14, "< swt2 : wifi >", GUI_FONT_ALIGN_VMIDDLE | GUI_FONT_ALIGN_HMIDDLE);

    // ip
    gui_drawTextRect(5, 18, 118, 14, esp8266_getIp(), GUI_FONT_ALIGN_VMIDDLE | GUI_FONT_ALIGN_HMIDDLE);
    gui_drawTextRect(5, 36, 118, 14, esp8266_getMac(), GUI_FONT_ALIGN_VMIDDLE | GUI_FONT_ALIGN_HMIDDLE);

    gui_ctrl_update();
}
