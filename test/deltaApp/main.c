#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "archi.h"
#include "modules.h"
#include "robot.h"

extern void rest_api_exec(char *restUrl, HTTP_QUERRY_TYPE querry_type, char *buffer);
extern const Fs_FilesList file_list;

// #include "a6channels.h"

unsigned int pos[] = {1500, 1000, 2000, 1000, 2000, 1500, 1500, 1500};
unsigned char step = 2;

int main(void)
{
    unsigned int i, j, e = 0;
    uint16_t value_x, value_y, value_z;
    rt_dev_t uartDbg;
    rt_dev_t i2c;
    rt_dev_t usb_serial;
    uint16_t value, value2, percent, volt;
    char buff[200];
    uint8_t acc[8];
    MrobotPose pose;
    float valueF;
    char led = 0;

    robot_init();
    sysclock_setClock(120000000);

    usb_serial = usb_serial_getFreeDevice();

    network_init();
    a6_init(uart(A6_UART), gpio_pin(A6_RW_PORT, A6_RW_PIN), 0);
    web_server_setRestApi(rest_api_exec);
    web_server_setRootFS(&file_list);

    // ax12
    ax12_init(uart(AX12_UART), gpio_pin(AX12_TXEN_PORT, AX12_TXEN_PIN), 0);

    adc_init();

    // uart debug init
    uartDbg = uart_getFreeDevice();
    uart_setBaudSpeed(uartDbg, 115200);
    uart_setBitConfig(uartDbg, 8, UART_BIT_PARITY_NONE, 1);
    uart_enable(uartDbg);

    // console init
    cmdline_init();
    cmdline_setDevice(usb_serial, usb_serial);
    board_setLed(0, 1);

    // i2c init
    i2c = i2c_getFreeDevice();
    i2c_setBaudSpeed(i2c, I2C_BAUD_400K);
    i2c_enable(i2c);

    i2c_writereg(i2c, 0x38, 0x2A, 0x01, I2C_REG8 | I2C_REGADDR8);

    pose.x = 1500;
    pose.y = 1000;
    pose.t = 0;
    mrobot_setPose(pose);

    MrobotPoint pos;
    pos.x = 1500;
    pos.y = 1000;
    mrobot_goto(pos, 100);

    j = 0;
    while (1)
    {
        network_task();
        usb_serial_task();
        for (i = 0; i < 65000; i++)
        {
            ;
        }

#ifdef SIMULATOR
        usleep(1000);
#endif

        /*if(asserv_getDistance() <= 15.0)
        {
            for(j=0;j<10;j++) for(i=0;i<65000;i++);
            step += 2;
            if(step > 6)
                step = 0;
            asserv_goTo(pos[step], pos[step+1]);
        }*/

        value = sharp_convert(adc_getValue(ANS0), FarSharp);
        /*value = adc_getValue(25);	// AnS2*/
        value2 = sharp_convert(adc_getValue(ANS2), FarSharp);
        // ax12_moveTo(1, value, 512, 512);

        if (value < 150 || value2 < 150)
        {
            mrobot_pause();
        }
        else
        {
            mrobot_restart();
        }

        i2c_readregs(i2c, 0x38, 0x00, acc, 7, I2C_REG8 | I2C_REGADDR8);
        if (acc[0] & 0x08)
        {
            value_x = acc[1];
            value_y = acc[3];
            value_z = acc[5];
        }

        pose = mrobot_pose();
        sprintf(buff,
                "d1:%d\td2:%d\tx:%d\ty:%d\tt:%d\tacx:%d\tacy:%d\tacz:%d\r\n",
                value,
                value2,
                (int)pose.x,
                (int)pose.y,
                (int)(pose.t / 3.14 * 180.0),
                value_x,
                value_y,
                value_z);

        if (e++ > 10)
        {
            // ==================== USB =======================
            // usb_serial_write(usb_serial, buff, strlen(buff));
            e = 0;
        }

        if (j++ > 50)
        {
            int16_t *ptr;
            ptr = (int16_t *)buff;

            *ptr = 0xA6;

            ptr++;
            volt = adc_getValue(BOARD_VOLT_IN);
            percent = (volt - 305) * 2;
            *ptr = percent;

            ptr++;
            valueF = (float)volt * 35.6;  // mV
            *ptr = (uint16_t)valueF;

            ptr++;
            *ptr = value;

            ptr++;
            *ptr = value2;

            ptr++;
            *ptr = pose.x;

            ptr++;
            *ptr = pose.y;

            ptr++;
            *ptr = pose.t * 180.0 / 3.1415;

            a6_write(buff, 16);
            j = 0;
            board_setLed(0, led);
            led++;
            // uart_write(uartDbg, buff, strlen(buff));
        }

        cmdline_task();

        /*switch(a6Chan)
        {
        case 0:
            // batt level and voltage
            value = (adc_getValue(BOARD_VOLT_IN) - 305) * 2;
            a6_writeShort(A6_BATT_LEVEL, value);
            break;
        case 1:
            // batt level and voltage
            valueF = (float)adc_getValue(BOARD_VOLT_IN) * 35.6;
            a6_writeShort(A6_BATT_MVOLT, (uint16_t)valueF);
            break;
        }*/
    }

    return 0;
}
