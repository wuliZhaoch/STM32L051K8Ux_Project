/*
 * sd3078.h
 *
 *  Created on: 2021-03-30
 *      Author: wuliZhao_ch
 */
#ifndef SD3078_H_
#define SD3078_H_

#include "main.h"
#include "system.h"
#include "i2c.h"

#define DEVICEID_LEN        8
#define DEVICE_VBAT_LEN     2
#define TIME_RTC_LEN        7

typedef enum {
    Source_4096Hz = 0,
    Source_1024Hz,
    Source_1S,
    Source_1Min
} SD3078_ClkSourceTypeDef;

typedef struct {
    SD3078_ClkSourceTypeDef ClkSource;
    uint8_t SD3078_IM;
    uint32_t Counter_val;
} SD3078_CountDownTypeDef;

typedef struct
{
    uint8_t sd3078_secend;
    uint8_t sd3078_minute;
    uint8_t sd3078_hour;
    uint8_t sd3078_week;
    uint8_t sd3078_day;
    uint8_t sd3078_month;
    uint8_t sd3078_year;
    uint8_t sd3078_readtime_buf[TIME_RTC_LEN];
} SD3078_TimeTypeDef;


typedef struct
{
    uint8_t DeviceID_len;
    uint8_t DeviceID_Buffer[DEVICEID_LEN];

} SD3078_DeviceIDypeDef;


extern uint8_t Time_RTC_Init[TIME_RTC_LEN];

extern uint8_t WRTC1_CTR2_SET;
extern uint8_t WRTC2_WRTC3_CTR1_SET;

extern uint8_t WRTC1_CTR2_RESET;
extern uint8_t WRTC2_WRTC3_CTR1_RESET;


#define SD3078_TIMEOUT      1000

#define IIC_HANDLE              hi2c1

#define SD3078_WRITE_ADDRESS    0x64        /* sd3078 Write Address */
#define SD3078_READ_ADDRESS     0X65        /* sd3078 Read Address  */

/* Real time clock register */
#define SD3078_RTC_SECOND           0X00    /* RTC Second   */
#define SD3078_RTC_MINUTE           0X01    /* RTC Minute   */
#define SD3078_RTC_HOUR             0X02    /* RTC Hour     */

#define SD3078_RTC_WEEK             0X03    /* RTC Week  */
#define SD3078_RTC_DAY              0X04    /* RTC Day   */
#define SD3078_RTC_MONTH            0X05    /* RTC Month */
#define SD3078_RTC_YEAR             0X06    /* RTC Year  */

/* Time alarm register */
#define SD3078_ALARM_SECOND         0X07    /* Alarm Second */
#define SD3078_ALARM_MINUTE         0X08    /* Alarm Minute */
#define SD3078_ALARM_HOUR           0X09    /* Alarm Hour   */

#define SD3078_ALARM_WEEK           0X0A    /* Alarm Week   */
#define SD3078_ALARM_DAY            0X0B    /* Alarm Day    */
#define SD3078_ALARM_MONTH          0X0C    /* Alarm Month  */
#define SD3078_ALARM_YEAR           0X0D    /* Alarm Year   */
#define SD3078_ALARM_ENABLE         0X0E    /* Alarm Enable */

/* Control register */
#define SD3078_CONTROL_CTR1         0X0F    /* Control register CTR1 */
#define SD3078_CONTROL_CTR2         0X10    /* Control register CTR2 */
#define SD3078_CONTROL_CTR3         0X11    /* Control register CTR3 */
#define SD3078_25_TTF               0X12    /* Control register TTF */

#define SD3078_TIMER_COUNTER_1      0X13    /* Control register - TIMER Counter1 */
#define SD3078_TIMER_COUNTER_2      0X14    /* Control register - TIMER Counter2 */
#define SD3078_TIMER_COUNTER_3      0X15    /* Control register - TIMER Counter3 */

/* Temperature  register */
#define SD3078_TEMPERATURE          0X16    /* Temperature */

/* IIC Control register */
#define SD3078_AGTC                 0X17    /* IIC Control AGTC */

/* Charging register */
#define SD3078_CHARGE               0X18    /* Charging */

/* Expansion register */
#define SD3078_EXPANSION_CTR4       0X19    /* Expansion CTR4 */
#define SD3078_EXPANSION_CTR5       0X1A    /* Expansion CTR5 */

/* Battery power register */
#define SD3078_BAT_VAL              0X1B    /* Battery power value */

/* Low/High temperature alarm register */
#define SD3078_TEMP_AL              0X1C    /* Low temperature alarm                */
#define SD3078_TEMP_AH              0X1D    /* High temperature alarm               */

/* History of low/high temperature register */
#define SD3078_TEMP_HISL            0X1E    /* History of low temperature           */
#define SD3078_TEMP_HISH            0x1F    /* History of high temperature          */

/* The lowest temperature in history register */
#define SD3078_TEMP_LOW_MINUTE      0X20    /* Minimum temperature time - Minutes   */
#define SD3078_TEMP_LOW_HOUR        0X21    /* Minimum temperature time - Hour      */
#define SD3078_TEMP_LOW_WEEK        0X22    /* Minimum temperature time - Week      */
#define SD3078_TEMP_LOW_DAY         0X23    /* Minimum temperature time - Day       */
#define SD3078_TEMP_LOW_MONTH       0X24    /* Minimum temperature time - Month     */
#define SD3078_TEMP_LOW_YEAR        0X25    /* Minimum temperature time - Year      */

/* The time when the highest temperature ever occurred */
#define SD3078_TEMP_HIGH_MINUTE     0X26    /* Maximum temperature time - Minutes   */
#define SD3078_TEMP_HIGH_HOUR       0X27    /* Maximum temperature time - Hour      */
#define SD3078_TEMP_HIGH_WEEK       0X28    /* Maximum temperature time - Week      */
#define SD3078_TEMP_HIGH_DAY        0X29    /* Maximum temperature time - Day       */
#define SD3078_TEMP_HIGH_MONTH      0X2A    /* Maximum temperature time - Month     */
#define SD3078_TEMP_HIGH_YEAR       0X2B    /* Maximum temperature time - Year      */

/* User RAM register */

/* Device ID register */
#define SD3078_DEVICE_ID1           0X72    /* Productive Year              */
#define SD3078_DEVICE_ID2           0X73    /* Productive months            */
#define SD3078_DEVICE_ID3           0X74    /* Productive days              */
#define SD3078_DEVICE_ID4           0X75    /* Production machine number    */
#define SD3078_DEVICE_ID5           0X76    /* Production order number 1    */
#define SD3078_DEVICE_ID6           0X77    /* Production order number 2    */
#define SD3078_DEVICE_ID7           0X78    /* The internal serial number 1 */
#define SD3078_DEVICE_ID8           0X79    /* The internal serial number 2 */


uint8_t sd3078_ByteWrite(uint16_t Addr, uint8_t* data, uint32_t Time_out);      // SD3078 Write Byte
uint8_t sd3078_MultiByteWrite(uint16_t Addr, uint8_t* data, uint16_t size, uint32_t Time_out);
uint8_t sd3078_ByteRead(uint16_t Addr, uint8_t* read_buff, uint32_t Time_out);      // SD3078 Read Byte
uint8_t sd3078_MultiByteRead(uint16_t Addr, uint8_t* read_buff, uint16_t size, uint32_t Time_out);      // SD3078 Read Multi Byte

uint8_t sd3078_ReadDeviceID(uint16_t Addr, uint8_t *read_buffer);       // Read sd3078 Device ID
uint8_t sd3078_ReadDeviceTemperature(uint16_t Addr, uint8_t *read_buffer);     // Read sd3078 Device Temperature
uint16_t sd3078_ReadDeviceVBAT(uint16_t Addr, uint8_t *read_buffer);        // Read sd3078 VBAT
void sd3078_WriteEnable(uint16_t Addr_CTR2, uint16_t Addr_CTR1);
void sd3078_WriteDisable(uint16_t Addr_CTR1, uint16_t Addr_CTR2);
void sd3078_RTC_WriteDate(uint16_t Addr, uint8_t *write_buffer);
void sd3078_RTC_ReadDate(uint16_t Addr, uint8_t *Read_buffer);
void sd3078_CountDown_interrupt(SD3078_CountDownTypeDef *countdowninit, uint8_t *writeBuffer);

#endif
