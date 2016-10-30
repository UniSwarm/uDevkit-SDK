
#include "driver/adc.h"

#include "cmd_stdio.h"

int cmd_adc(int argc, char **argv)
{
    int8_t param;
    uint16_t value;
    if(argc < 2)
        return 1;
    param = atoi(argv[2]);

    value = adc_getValue(param);
    printf("%d => %.3fV", value, (float)value / 1024.0 * 3.3);

    return 0;
}
