/**
 * @file VL6180X.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date February 05, 2017, 18:51 PM
 *
 * @brief VL6180X time of flight distance sensor driver support
 */

#include "VL6180X.h"

#include "driver/i2c.h"

rt_dev_t VL6180X_init(rt_dev_t i2c_bus, uint8_t i2c_addr)
{
    i2c_writereg(i2c_bus, i2c_addr, 0x0207, 0x01, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x0208, 0x01, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x0096, 0x00, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x0097, 0xfd, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x00e3, 0x00, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x00e4, 0x04, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x00e5, 0x02, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x00e6, 0x01, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x00e7, 0x03, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x00f5, 0x02, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x00d9, 0x05, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x00db, 0xce, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x00dc, 0x03, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x00dd, 0xf8, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x009f, 0x00, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x00a3, 0x3c, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x00b7, 0x00, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x00bb, 0x3c, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x00b2, 0x09, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x00ca, 0x09, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x0198, 0x01, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x01b0, 0x17, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x01ad, 0x00, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x00ff, 0x05, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x0100, 0x05, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x0199, 0x05, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x01a6, 0x1b, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x01ac, 0x3e, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x01a7, 0x1f, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, 0x0030, 0x00, I2C_REGADDR16);

    //Enable Interrupts on Conversion Complete (any source)
    i2c_writereg(i2c_bus, i2c_addr, VL6180X_SYSTEM_INTERRUPT_CONFIG_GPIO, (4 << 3)|(4) , I2C_REGADDR16); // Set GPIO1 high when sample complete

    i2c_writereg(i2c_bus, i2c_addr, VL6180X_SYSTEM_MODE_GPIO1, 0x10, I2C_REGADDR16); // Set GPIO1 high when sample complete
    i2c_writereg(i2c_bus, i2c_addr, VL6180X_READOUT_AVERAGING_SAMPLE_PERIOD, 0x30, I2C_REGADDR16); //Set Avg sample period
    i2c_writereg(i2c_bus, i2c_addr, VL6180X_SYSALS_ANALOGUE_GAIN, 0x46, I2C_REGADDR16); // Set the ALS gain
    i2c_writereg(i2c_bus, i2c_addr, VL6180X_SYSRANGE_VHV_REPEAT_RATE, 0xFF, I2C_REGADDR16); // Set auto calibration period (Max = 255)/(OFF = 0)
    i2c_writereg(i2c_bus, i2c_addr, VL6180X_SYSALS_INTEGRATION_PERIOD, 0x63, I2C_REGADDR16); // Set ALS integration time to 100ms
    i2c_writereg(i2c_bus, i2c_addr, VL6180X_SYSRANGE_VHV_RECALIBRATE, 0x01, I2C_REGADDR16); // perform a single temperature calibration
    //Optional settings from datasheet
    //http://www.st.com/st-web-ui/static/active/en/resource/technical/document/application_note/DM00122600.pdf
    i2c_writereg(i2c_bus, i2c_addr, VL6180X_SYSRANGE_INTERMEASUREMENT_PERIOD, 0x09, I2C_REGADDR16); // Set default ranging inter-measurement period to 100ms
    i2c_writereg(i2c_bus, i2c_addr, VL6180X_SYSALS_INTERMEASUREMENT_PERIOD, 0x0A, I2C_REGADDR16); // Set default ALS inter-measurement period to 100ms
    i2c_writereg(i2c_bus, i2c_addr, VL6180X_SYSTEM_INTERRUPT_CONFIG_GPIO, 0x24, I2C_REGADDR16); // Configures interrupt on ‘New Sample Ready threshold event’
    //Additional settings defaults from community
    i2c_writereg(i2c_bus, i2c_addr, VL6180X_SYSRANGE_MAX_CONVERGENCE_TIME, 0x32, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, VL6180X_SYSRANGE_RANGE_CHECK_ENABLES, 0x10 | 0x01, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, VL6180X_SYSRANGE_EARLY_CONVERGENCE_ESTIMATE, 0x7B , I2C_REGADDR16 | I2C_REG16);
    i2c_writereg(i2c_bus, i2c_addr, VL6180X_SYSALS_INTEGRATION_PERIOD, 0x64, I2C_REGADDR16 | I2C_REG16);

    i2c_writereg(i2c_bus, i2c_addr, VL6180X_READOUT_AVERAGING_SAMPLE_PERIOD, 0x30, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, VL6180X_SYSALS_ANALOGUE_GAIN, 0x40, I2C_REGADDR16);
    i2c_writereg(i2c_bus, i2c_addr, VL6180X_FIRMWARE_RESULT_SCALER, 0x01, I2C_REGADDR16);

    return 0; // TODO
}

uint16_t VL6180X_getDistance(rt_dev_t i2c_bus, uint8_t i2c_addr)
{
	uint16_t value;
    uint16_t i;
    i2c_writereg(i2c_bus, i2c_addr, VL6180X_SYSRANGE_START, 0x01, I2C_REGADDR16); // start
    for(i=0;i<65000;i++);
    value = i2c_readreg(i2c_bus, i2c_addr, VL6180X_RESULT_RANGE_VAL, I2C_REGADDR16 | I2C_READ_STOPSTART);
    i2c_writereg(i2c_bus, i2c_addr, VL6180X_SYSTEM_INTERRUPT_CLEAR, 0x07, I2C_REGADDR16);
    return value;
}

void VL6180X_setAddr(rt_dev_t i2c_bus, uint8_t i2c_addr, uint8_t i2c_newaddr)
{
    i2c_writereg(i2c_bus, i2c_addr, VL6180X_I2C_SLAVE_DEVICE_ADDRESS, i2c_newaddr>>1, I2C_REGADDR16);
}
