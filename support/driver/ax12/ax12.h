/**
 * @file ax12.h
 * @author Sebastien CAUX (sebcaux) / Charles-Antoine NOURY (charlybigoud)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2022
 *
 * @date April 16, 2016, 14:41 PM
 *
 * @brief AX12 servomotor support
 */

#ifndef AX12_H
#define AX12_H

#include "driver/gpio.h"
#include "driver/uart.h"

void ax12_init(rt_dev_t uart, rt_dev_t txen, uint8_t inverted);

void ax12_send_char(uint8_t ax_id, uint8_t param, uint8_t val);
void ax12_send_1_short(uint8_t ax_id, uint8_t param, uint16_t val);
void ax12_send_2_short(uint8_t ax_id, uint8_t param, uint16_t val, uint16_t val2);
void ax12_send_3_short(uint8_t ax_id, uint8_t param, uint16_t val, uint16_t val2, uint16_t val3);

/*void read_param_ax(uint8_t ax_id, uint8_t param, uint8_t nbParam);
uint8_t parseResponse6(uint8_t ax_id, uint16_t *pos, uint16_t *speed, uint16_t *load);
void clearAxResponse(void);*/

void ax12_moveTo(uint8_t ax_id, uint16_t position, uint16_t speed, uint16_t torque);
void ax12_setPosition(uint8_t ax_id, uint16_t position);
void ax12_setSpeed(uint8_t ax_id, uint16_t speed);
void ax12_setTorque(uint8_t ax_id, uint16_t torque);
void ax12_setLed(uint8_t ax_id, uint8_t led);
void ax12_setId(uint8_t ax_id, uint8_t newId);

//--- Control Table Address ---
// EEPROM AREA
#define P_MODEL_NUMBER_L     0
#define P_MODOEL_NUMBER_H    1
#define P_VERSION            2
#define P_ID                 3
#define P_BAUD_RATE          4
#define P_RETURN_DELAY_TIME  5
#define P_CW_ANGLE_LIMIT_L   6
#define P_CW_ANGLE_LIMIT_H   7
#define P_CCW_ANGLE_LIMIT_L  8
#define P_CCW_ANGLE_LIMIT_H  9
#define P_SYSTEM_DATA2       10
#define P_LIMIT_TEMPERATURE  11
#define P_DOWN_LIMIT_VOLTAGE 12
#define P_UP_LIMIT_VOLTAGE   13
#define P_MAX_TORQUE_L       14
#define P_MAX_TORQUE_H       15
#define P_RETURN_LEVEL       16
#define P_ALARM_LED          17
#define P_ALARM_SHUTDOWN     18
#define P_OPERATING_MODE     19
#define P_DOWN_CALIBRATION_L 20
#define P_DOWN_CALIBRATION_H 21
#define P_UP_CALIBRATION_L   22
#define P_UP_CALIBRATION_H   23

// RAM AREA
#define P_TORQUE_ENABLE          (24)
#define P_LED                    (25)
#define P_CW_COMPLIANCE_MARGIN   (26)
#define P_CCW_COMPLIANCE_MARGIN  (27)
#define P_CW_COMPLIANCE_SLOPE    (28)
#define P_CCW_COMPLIANCE_SLOPE   (29)
#define P_GOAL_POSITION_L        (30)
#define P_GOAL_POSITION_H        (31)
#define P_GOAL_SPEED_L           (32)
#define P_GOAL_SPEED_H           (33)
#define P_TORQUE_LIMIT_L         (34)
#define P_TORQUE_LIMIT_H         (35)
#define P_PRESENT_POSITION_L     (36)
#define P_PRESENT_POSITION_H     (37)
#define P_PRESENT_SPEED_L        (38)
#define P_PRESENT_SPEED_H        (39)
#define P_PRESENT_LOAD_L         (40)
#define P_PRESENT_LOAD_H         (41)
#define P_PRESENT_VOLTAGE        (42)
#define P_PRESENT_TEMPERATURE    (43)
#define P_REGISTERED_INSTRUCTION (44)
#define P_PAUSE_TIME             (45)
#define P_MOVING                 (46)
#define P_LOCK                   (47)
#define P_PUNCH_L                (48)
#define P_PUNCH_H                (49)

//--- Instruction ---
#define INST_PING           0x01
#define INST_READ           0x02
#define INST_WRITE          0x03
#define INST_REG_WRITE      0x04
#define INST_ACTION         0x05
#define INST_RESET          0x06
#define INST_DIGITAL_RESET  0x07
#define INST_SYSTEM_READ    0x0C
#define INST_SYSTEM_WRITE   0x0D
#define INST_SYNC_WRITE     0x83
#define INST_SYNC_REG_WRITE 0x84

#endif  // AX12_H
