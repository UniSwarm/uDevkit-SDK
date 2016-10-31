
#include "board.h"

#include "cmd_stdio.h"

#if   defined(LED3)
    #define LED_COUNT 3
#elif defined(LED2)
    #define LED_COUNT 2
#elif defined(LED)
    #define LED_COUNT 1
#else
    #define LED_COUNT 0
#endif

int cmd_led(int argc, char **argv)
{
    char ledid = 255;
    char status;

    if(argc < 2)
        return 1;

    // first arg numeric : convert to ledid
    ledid = atoi(argv[1]);
    if(ledid >= LED_COUNT)
    {
        puts("Invalid led id");
        return 1;
    }

    // if no more arg, print status of led
    // led status > led <led-id>
    if(argc == 2)
    {
        switch(ledid)
        {
#if LED_COUNT>=1
        case 0:
            status = LED;
            break;
#endif
#if LED_COUNT>=2
        case 1:
            status = LED2;
            break;
#endif
#if LED_COUNT>=3
        case 2:
            status = LED3;
            break;
#endif
        }
        if(status == 1)
            puts("LED is on");
        else
            puts("LED is off");

        return 0;
    }

    // led on or led off > led <led-id> <0-1>
    if(argv[2][0]=='1')
        status = 1;
    else
        status = 0;

    switch(ledid)
    {
#if LED_COUNT>=1
    case 0:
        LED = status;
        break;
#endif
#if LED_COUNT>=2
    case 1:
        LED2 = status;
        break;
#endif
#if LED_COUNT>=3
    case 2:
        LED3 = status;
        break;
#endif
    }

    return 0;
}
