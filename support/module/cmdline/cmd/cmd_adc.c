
#include "driver/adc.h"

#include "cmd_stdio.h"

int cmd_adc(int argc, char **argv)
{
    int8_t param;
    uint16_t value;
    if(argc < 2)
        return 1;

    // help
    if(strcmp(argv[1], "help")==0)
    {
        puts("adc <channel>");
        return 0;
    }

    param = atoi(argv[1]);

    // read value of an adc channel
    // > adc <adc-channel>
    value = adc_getValue(param);
    printf("%d/1023 => %.3fV\r\n", value, (float)value / 1024.0 * 3.3);

    return 0;
}
