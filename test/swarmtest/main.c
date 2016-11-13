#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "board.h"
#include "archi.h"

#include "driver/motor.h"

#define MMAX  1200
#define MMAX2 800

rt_dev_t i2c;

#define VL6180X_IDENTIFICATION_MODEL_ID              0x0000
#define VL6180X_IDENTIFICATION_MODEL_REV_MAJOR       0x0001
#define VL6180X_IDENTIFICATION_MODEL_REV_MINOR       0x0002
#define VL6180X_IDENTIFICATION_MODULE_REV_MAJOR      0x0003
#define VL6180X_IDENTIFICATION_MODULE_REV_MINOR      0x0004
#define VL6180X_IDENTIFICATION_DATE                  0x0006 //16bit value
#define VL6180X_IDENTIFICATION_TIME                  0x0008 //16bit value

#define VL6180X_SYSTEM_MODE_GPIO0                    0x0010
#define VL6180X_SYSTEM_MODE_GPIO1                    0x0011
#define VL6180X_SYSTEM_HISTORY_CTRL                  0x0012
#define VL6180X_SYSTEM_INTERRUPT_CONFIG_GPIO         0x0014
#define VL6180X_SYSTEM_INTERRUPT_CLEAR               0x0015
#define VL6180X_SYSTEM_FRESH_OUT_OF_RESET            0x0016
#define VL6180X_SYSTEM_GROUPED_PARAMETER_HOLD        0x0017

#define VL6180X_SYSRANGE_START                       0x0018
#define VL6180X_SYSRANGE_THRESH_HIGH                 0x0019
#define VL6180X_SYSRANGE_THRESH_LOW                  0x001A
#define VL6180X_SYSRANGE_INTERMEASUREMENT_PERIOD     0x001B
#define VL6180X_SYSRANGE_MAX_CONVERGENCE_TIME        0x001C
#define VL6180X_SYSRANGE_CROSSTALK_COMPENSATION_RATE 0x001E
#define VL6180X_SYSRANGE_CROSSTALK_VALID_HEIGHT      0x0021
#define VL6180X_SYSRANGE_EARLY_CONVERGENCE_ESTIMATE  0x0022
#define VL6180X_SYSRANGE_PART_TO_PART_RANGE_OFFSET   0x0024
#define VL6180X_SYSRANGE_RANGE_IGNORE_VALID_HEIGHT   0x0025
#define VL6180X_SYSRANGE_RANGE_IGNORE_THRESHOLD      0x0026
#define VL6180X_SYSRANGE_MAX_AMBIENT_LEVEL_MULT      0x002C
#define VL6180X_SYSRANGE_RANGE_CHECK_ENABLES         0x002D
#define VL6180X_SYSRANGE_VHV_RECALIBRATE             0x002E
#define VL6180X_SYSRANGE_VHV_REPEAT_RATE             0x0031

#define VL6180X_SYSALS_START                         0x0038
#define VL6180X_SYSALS_THRESH_HIGH                   0x003A
#define VL6180X_SYSALS_THRESH_LOW                    0x003C
#define VL6180X_SYSALS_INTERMEASUREMENT_PERIOD       0x003E
#define VL6180X_SYSALS_ANALOGUE_GAIN                 0x003F
#define VL6180X_SYSALS_INTEGRATION_PERIOD            0x0040

#define VL6180X_RESULT_RANGE_STATUS                  0x004D
#define VL6180X_RESULT_ALS_STATUS                    0x004E
#define VL6180X_RESULT_INTERRUPT_STATUS_GPIO         0x004F
#define VL6180X_RESULT_ALS_VAL                       0x0050
#define VL6180X_RESULT_HISTORY_BUFFER                0x0052
#define VL6180X_RESULT_RANGE_VAL                     0x0062
#define VL6180X_RESULT_RANGE_RAW                     0x0064
#define VL6180X_RESULT_RANGE_RETURN_RATE             0x0066
#define VL6180X_RESULT_RANGE_REFERENCE_RATE          0x0068
#define VL6180X_RESULT_RANGE_RETURN_SIGNAL_COUNT     0x006C
#define VL6180X_RESULT_RANGE_REFERENCE_SIGNAL_COUNT  0x0070
#define VL6180X_RESULT_RANGE_RETURN_AMB_COUNT        0x0074
#define VL6180X_RESULT_RANGE_REFERENCE_AMB_COUNT     0x0078
#define VL6180X_RESULT_RANGE_RETURN_CONV_TIME        0x007C
#define VL6180X_RESULT_RANGE_REFERENCE_CONV_TIME     0x0080

#define VL6180X_READOUT_AVERAGING_SAMPLE_PERIOD      0x010A
#define VL6180X_FIRMWARE_BOOTUP                      0x0119
#define VL6180X_FIRMWARE_RESULT_SCALER               0x0120
#define VL6180X_I2C_SLAVE_DEVICE_ADDRESS             0x0212
#define VL6180X_INTERLEAVED_MODE_ENABLE              0x02A3

void setup_PWM(void)
{
	OC1CON1 = 0b0001110000000110;
	OC1CON2 = 0b0000000000011111;
	OC1R = 0;
	OC1RS = 1500;	// 20kz

	OC2CON1 = 0b0001110000000110;
	OC2CON2 = 0b0000000000011111;
	OC2R = 0;
	OC2RS = 1500;	// 20kz

	OC3CON1 = 0b0001110000000110;
	OC3CON2 = 0b0000000000011111;
	OC3R = 0;
	OC3RS = 1500;	// 20kz

	OC4CON1 = 0b0001110000000110;
	OC4CON2 = 0b0000000000011111;
	OC4R = 0;
	OC4RS = 1500;	// 20kz
}

void setM1A(short v)
{
    if(v >= 0)
    {
        OC1R = v;
        OC1CON2bits.OCINV = 0;
        M1A = 0;
    }
    else
    {
        OC1R = -v;
        OC1CON2bits.OCINV = 1;
        M1A = 1;
    }
}
void setM1B(short v)
{
    if(v >= 0)
    {
        OC2R = v;
        OC2CON2bits.OCINV = 0;
        M1B = 0;
    }
    else
    {
        OC2R = -v;
        OC2CON2bits.OCINV = 1;
        M1B = 1;
    }
}

void setM2A(short v)
{
    if(v >= 0)
    {
        OC3R = v;
        OC3CON2bits.OCINV = 0;
        M2A = 0;
    }
    else
    {
        OC3R = -v;
        OC3CON2bits.OCINV = 1;
        M2A = 1;
    }
}
void setM2B(short v)
{
    if(v >= 0)
    {
        OC4R = v;
        OC4CON2bits.OCINV = 0;
        M2B = 0;
    }
    else
    {
        OC4R = -v;
        OC4CON2bits.OCINV = 1;
        M2B = 1;
    }
}

void writeReg(uint16_t addr, uint8_t data)
{
    i2c_start(i2c);
    i2c_putc(i2c, 0x52); // address write
    i2c_putc(i2c, addr>>8); // reg high
    i2c_putc(i2c, addr&0x00FF); // reg low
    i2c_putc(i2c, data); // data to write
    i2c_stop(i2c);
}

void writeReg16(uint16_t addr, uint16_t data)
{
    i2c_start(i2c);
    i2c_putc(i2c, 0x52); // address write
    i2c_putc(i2c, addr>>8); // reg high
    i2c_putc(i2c, addr&0x00FF); // reg low
    i2c_putc(i2c, data>>8); // data to write
    i2c_putc(i2c, data&0x00FF); // data to write
    i2c_stop(i2c);
}

uint8_t readReg(uint16_t addr)
{
    uint8_t value;
    i2c_start(i2c);
    i2c_putc(i2c, 0x52); // address write
    i2c_putc(i2c, addr>>8); // reg high
    i2c_putc(i2c, addr&0x00FF); // reg low
    i2c_stop(i2c);
    i2c_start(i2c);
    i2c_putc(i2c, 0x53); // address read
    value = i2c_getc(i2c);
    i2c_nack(i2c);
    i2c_stop(i2c);
    return value;
}

int main(void)
{
	unsigned int i,j;
	rt_dev_t uartDbg;
	uint16_t value;
	char buff[100];

	sysclock_setClock(120000000);
	board_init();

	// warning keep this init order before remap support
	esp_init();
    board_setLed(1, 1);

	adc_init();

    setup_PWM();

    i2c = i2c_getFreeDevice();
    i2c_setBaudSpeed(i2c, I2C_BAUD_400K);
    i2c_enable(i2c);


    i2c_start(i2c);
    i2c_putc(i2c, 0x38);
    i2c_putc(i2c, 0x0D);
    i2c_restart(i2c);
    i2c_putc(i2c, 0x39);
    value = i2c_getc(i2c);
    i2c_nack(i2c);
    i2c_stop(i2c);

	for(j=0;j<2;j++) for(i=0;i<65000;i++);
    writeReg(0x0207, 0x01);
    writeReg(0x0208, 0x01);
    writeReg(0x0096, 0x00);
    writeReg(0x0097, 0xfd);
    writeReg(0x00e3, 0x00);
    writeReg(0x00e4, 0x04);
    writeReg(0x00e5, 0x02);
    writeReg(0x00e6, 0x01);
    writeReg(0x00e7, 0x03);
    writeReg(0x00f5, 0x02);
    writeReg(0x00d9, 0x05);
    writeReg(0x00db, 0xce);
    writeReg(0x00dc, 0x03);
    writeReg(0x00dd, 0xf8);
    writeReg(0x009f, 0x00);
    writeReg(0x00a3, 0x3c);
    writeReg(0x00b7, 0x00);
    writeReg(0x00bb, 0x3c);
    writeReg(0x00b2, 0x09);
    writeReg(0x00ca, 0x09);
    writeReg(0x0198, 0x01);
    writeReg(0x01b0, 0x17);
    writeReg(0x01ad, 0x00);
    writeReg(0x00ff, 0x05);
    writeReg(0x0100, 0x05);
    writeReg(0x0199, 0x05);
    writeReg(0x01a6, 0x1b);
    writeReg(0x01ac, 0x3e);
    writeReg(0x01a7, 0x1f);
    writeReg(0x0030, 0x00);

    //Enable Interrupts on Conversion Complete (any source)
    writeReg(VL6180X_SYSTEM_INTERRUPT_CONFIG_GPIO, (4 << 3)|(4) ); // Set GPIO1 high when sample complete


    writeReg(VL6180X_SYSTEM_MODE_GPIO1, 0x10); // Set GPIO1 high when sample complete
    writeReg(VL6180X_READOUT_AVERAGING_SAMPLE_PERIOD, 0x30); //Set Avg sample period
    writeReg(VL6180X_SYSALS_ANALOGUE_GAIN, 0x46); // Set the ALS gain
    writeReg(VL6180X_SYSRANGE_VHV_REPEAT_RATE, 0xFF); // Set auto calibration period (Max = 255)/(OFF = 0)
    writeReg(VL6180X_SYSALS_INTEGRATION_PERIOD, 0x63); // Set ALS integration time to 100ms
    writeReg(VL6180X_SYSRANGE_VHV_RECALIBRATE, 0x01); // perform a single temperature calibration
    //Optional settings from datasheet
    //http://www.st.com/st-web-ui/static/active/en/resource/technical/document/application_note/DM00122600.pdf
    writeReg(VL6180X_SYSRANGE_INTERMEASUREMENT_PERIOD, 0x09); // Set default ranging inter-measurement period to 100ms
    writeReg(VL6180X_SYSALS_INTERMEASUREMENT_PERIOD, 0x0A); // Set default ALS inter-measurement period to 100ms
    writeReg(VL6180X_SYSTEM_INTERRUPT_CONFIG_GPIO, 0x24); // Configures interrupt on ‘New Sample Ready threshold event’
    //Additional settings defaults from community
    writeReg(VL6180X_SYSRANGE_MAX_CONVERGENCE_TIME, 0x32);
    writeReg(VL6180X_SYSRANGE_RANGE_CHECK_ENABLES, 0x10 | 0x01);
    writeReg16(VL6180X_SYSRANGE_EARLY_CONVERGENCE_ESTIMATE, 0x7B );
    writeReg16(VL6180X_SYSALS_INTEGRATION_PERIOD, 0x64);

    writeReg(VL6180X_READOUT_AVERAGING_SAMPLE_PERIOD,0x30);
    writeReg(VL6180X_SYSALS_ANALOGUE_GAIN,0x40);
    writeReg(VL6180X_FIRMWARE_RESULT_SCALER,0x01);

	for(j=0;j<2;j++) for(i=0;i<65000;i++);
    readReg(0x0000);

    writeReg(0x0018, 0x01); // start

	// uart debug init
	uartDbg = uart_getFreeDevice();
	uart_setBaudSpeed(uartDbg, 115200);
	uart_setBitConfig(uartDbg, 8, UART_BIT_PARITY_NONE, 1);
	uart_enable(uartDbg);

    T1CON = 0;
    T1CONbits.TCKPS = 3;
    PR1 = 10000;
    T1CONbits.TON = 1;

	while(1)
	{
        writeReg(0x0018, 0x01); // start
		for(j=0;j<3;j++) for(i=0;i<65000;i++);
        value = readReg(0x0062);
        writeReg(0x0015, 0x07);
        if(value > 50)
        {
            board_setLed(1, 1);
            _T1IE = 1;
        }
        else
        {
            board_setLed(1, 0);
            _T1IE = 0;
        }

		value = adc_getValue(BOARD_VOLT_IN);	// BOARD_VOLT_IN
		sprintf(buff, "value: %dv", value);

		uart_write(uartDbg, buff, strlen(buff)+1);

		value = uart_read(uartDbg, buff, 100);
		if(value>0)
			uart_write(uartDbg, buff, value);
	}

	return 0;
}

uint8_t step = 0;
void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void)
{
    // Clear Timer 1 interrupt flag
    _T1IF = 0;

    switch(step)
    {
    case 0:
        board_setLed(0, 0);
        setM1A(MMAX2);
        setM1B(MMAX2);
        setM2A(MMAX2);
        setM2B(MMAX2);
        break;

    case 1:
        setM1A(0);
        setM1B(MMAX);
        setM2A(0);
        setM2B(MMAX);
        break;

    case 2:
        setM1A(-MMAX2);
        setM1B(MMAX2);
        setM2A(-MMAX2);
        setM2B(MMAX2);
        break;

    case 3:
        setM1A(-MMAX);
        setM1B(0);
        setM2A(-MMAX);
        setM2B(0);
        break;

    case 4:
        board_setLed(0, 1);
        setM1A(-MMAX2);
        setM1B(-MMAX2);
        setM2A(-MMAX2);
        setM2B(-MMAX2);
        break;

    case 5:
        setM1A(0);
        setM1B(-MMAX);
        setM2A(0);
        setM2B(-MMAX);
        break;

    case 6:
        setM1A(MMAX2);
        setM1B(-MMAX2);
        setM2A(MMAX2);
        setM2B(-MMAX2);
        break;

    case 7:
        setM1A(MMAX);
        setM1B(0);
        setM2A(MMAX);
        setM2B(0);
        break;
    }

    step++;
    if(step>=8)
        step=0;
}
