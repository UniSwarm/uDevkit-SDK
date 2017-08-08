#ifndef SYSTEM_H
#define SYSTEM_H

#include <archi.h>
#include <stdbool.h>

/*** System States **************************************************/
typedef enum
{
    SYSTEM_STATE_USB_START,
    SYSTEM_STATE_USB_SUSPEND,
    SYSTEM_STATE_USB_RESUME
} SYSTEM_STATE;

void SYSTEM_Initialize( SYSTEM_STATE state );

#endif //SYSTEM_H
