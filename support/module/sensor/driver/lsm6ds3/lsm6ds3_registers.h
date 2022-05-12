/**
 * @file lsm6ds3_registers.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2022
 *
 * @date October 13, 2017, 14:37 PM
 *
 * @brief LSM6DS3 internal registers addresses
 */

#ifndef LSM6DS3_REGISTERS_H
#define LSM6DS3_REGISTERS_H

#ifdef __cplusplus
extern "C" {
#endif

// sensor registers
#define LSM6DS3_TEST_PAGE        0x00
#define LSM6DS3_RAM_ACCESS       0x01
#define LSM6DS3_SENSOR_SYNC_TIME 0x04
#define LSM6DS3_SENSOR_SYNC_EN   0x05
#define LSM6DS3_FIFO_CTRL1       0x06
#define LSM6DS3_FIFO_CTRL2       0x07
#define LSM6DS3_FIFO_CTRL3       0x08
#define LSM6DS3_FIFO_CTRL4       0x09
#define LSM6DS3_FIFO_CTRL5       0x0A
#define LSM6DS3_ORIENT_CFG_G     0x0B
#define LSM6DS3_REFERENCE_G      0x0C
#define LSM6DS3_INT1_CTRL        0x0D
#define LSM6DS3_INT2_CTRL        0x0E
#define LSM6DS3_WHO_AM_I_REG     0x0F
#define LSM6DS3_CTRL1_XL         0x10
#define LSM6DS3_CTRL2_G          0x11
#define LSM6DS3_CTRL3_C          0x12
#define LSM6DS3_CTRL4_C          0x13
#define LSM6DS3_CTRL5_C          0x14
#define LSM6DS3_CTRL6_G          0x15
#define LSM6DS3_CTRL7_G          0x16
#define LSM6DS3_CTRL8_XL         0x17
#define LSM6DS3_CTRL9_XL         0x18
#define LSM6DS3_CTRL10_C         0x19
#define LSM6DS3_MASTER_CONFIG    0x1A
#define LSM6DS3_WAKE_UP_SRC      0x1B
#define LSM6DS3_TAP_SRC          0x1C
#define LSM6DS3_D6D_SRC          0x1D
#define LSM6DS3_STATUS_REG       0x1E
#define LSM6DS3_OUT_TEMP_L       0x20
#define LSM6DS3_OUT_TEMP_H       0x21
#define LSM6DS3_OUTX_L_G         0x22
#define LSM6DS3_OUTX_H_G         0x23
#define LSM6DS3_OUTY_L_G         0x24
#define LSM6DS3_OUTY_H_G         0x25
#define LSM6DS3_OUTZ_L_G         0x26
#define LSM6DS3_OUTZ_H_G         0x27
#define LSM6DS3_OUTX_L_XL        0x28
#define LSM6DS3_OUTX_H_XL        0x29
#define LSM6DS3_OUTY_L_XL        0x2A
#define LSM6DS3_OUTY_H_XL        0x2B
#define LSM6DS3_OUTZ_L_XL        0x2C
#define LSM6DS3_OUTZ_H_XL        0x2D
#define LSM6DS3_SENSORHUB1_REG   0x2E
#define LSM6DS3_SENSORHUB2_REG   0x2F
#define LSM6DS3_SENSORHUB3_REG   0x30
#define LSM6DS3_SENSORHUB4_REG   0x31
#define LSM6DS3_SENSORHUB5_REG   0x32
#define LSM6DS3_SENSORHUB6_REG   0x33
#define LSM6DS3_SENSORHUB7_REG   0x34
#define LSM6DS3_SENSORHUB8_REG   0x35
#define LSM6DS3_SENSORHUB9_REG   0x36
#define LSM6DS3_SENSORHUB10_REG  0x37
#define LSM6DS3_SENSORHUB11_REG  0x38
#define LSM6DS3_SENSORHUB12_REG  0x39
#define LSM6DS3_FIFO_STATUS1     0x3A
#define LSM6DS3_FIFO_STATUS2     0x3B
#define LSM6DS3_FIFO_STATUS3     0x3C
#define LSM6DS3_FIFO_STATUS4     0x3D
#define LSM6DS3_FIFO_DATA_OUT_L  0x3E
#define LSM6DS3_FIFO_DATA_OUT_H  0x3F
#define LSM6DS3_TIMESTAMP0_REG   0x40
#define LSM6DS3_TIMESTAMP1_REG   0x41
#define LSM6DS3_TIMESTAMP2_REG   0x42
#define LSM6DS3_STEP_COUNTER_L   0x4B
#define LSM6DS3_STEP_COUNTER_H   0x4C
#define LSM6DS3_FUNC_SRC         0x53
#define LSM6DS3_TAP_CFG1         0x58
#define LSM6DS3_TAP_THS_6D       0x59
#define LSM6DS3_INT_DUR2         0x5A
#define LSM6DS3_WAKE_UP_THS      0x5B
#define LSM6DS3_WAKE_UP_DUR      0x5C
#define LSM6DS3_FREE_FALL        0x5D
#define LSM6DS3_MD1_CFG          0x5E
#define LSM6DS3_MD2_CFG          0x5F

// RAM registers access
#define LSM6DS3_ADDR0_TO_RW_RAM  0x62
#define LSM6DS3_ADDR1_TO_RW_RAM  0x63
#define LSM6DS3_DATA_TO_WR_RAM   0x64
#define LSM6DS3_DATA_RD_FROM_RAM 0x65

#define LSM6DS3_RAM_SIZE 4096

#ifdef __cplusplus
}
#endif

#endif  // LSM6DS3_REGISTERS_H
