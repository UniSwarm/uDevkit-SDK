/**
 * @file widget.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date June 24, 2016, 06:24 PM
 *
 * @brief Widget structure for gui module
 */

#ifndef WIDGET_H
#define WIDGET_H

// widget type enum
#define WIDGET_TYPE_BUTTON   0x01
#define WIDGET_TYPE_LABEL    0x02
#define WIDGET_TYPE_IMAGE    0x03
#define WIDGET_TYPE_SLIDER   0x04

typedef struct widget_t
{
	uint8_t type;
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
	void *data;
	void (*action_callback)(struct widget_t *widget);
} Widget;

void widget_init();
void widget_addButton(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

#endif // WIDGET_H
