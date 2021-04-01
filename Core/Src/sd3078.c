/*
 * sd3078.c
 *
 *  Created on: 2020-03-30
 *      Author: wuliZhao_ch
 *       brief: Source file of SD3078.
 *   attention: Use for SD3078.
 */
#include "sd3078.h"


uint8_t WRTC1_CTR2_SET = 0X80;
uint8_t WRTC2_WRTC3_CTR1_SET = 0X84;

uint8_t WRTC1_CTR2_RESET = 0X00;
uint8_t WRTC2_WRTC3_CTR1_RESET = 0X00;

/* 0x8B bit7 1:24/Hour  0:12/Hour
    // Read the hour data, to screen the highest bit of the hour, otherwise the display will be a problem
    // 读取小时数据时, 要屏蔽小时的最高位, 否则显示会出问题
    // 写时间数据时,不可以单独对7个时间数据中的某一位写操作,要一次性写入7个实时时钟数据, 否则会引起时间数据错误进位
*/
/* Second-Minute-Hour-Week-Day-Month-Year  */
uint8_t Time_RTC_Init[TIME_RTC_LEN] = {0x00, 0x00, 0x89, 0x03, 0x31, 0x03, 0x21};


/**
  * @brief  Function Write a Byte to sd3078
  * @param  Addr: Start Write Address
  * @param  Data: Data Content Write
  * @param  Time_out: Timeout duration
  * @retval HAL status
  */
uint8_t sd3078_ByteWrite(uint16_t Addr, uint8_t* data, uint32_t Time_out)
{
    return HAL_I2C_Mem_Write(&IIC_HANDLE, SD3078_WRITE_ADDRESS, Addr, I2C_MEMADD_SIZE_8BIT, data, 1, Time_out);
}

/**
  * @brief  Function Write MultiByte to sd3078
  * @param  Addr: Start Write Address
  * @param  Data: Data Content Write
  * @param  size: Write data len
  * @param  Time_out: Timeout duration
  * @retval HAL status
  */
uint8_t sd3078_MultiByteWrite(uint16_t Addr, uint8_t* data, uint16_t size, uint32_t Time_out)
{
    return HAL_I2C_Mem_Write(&IIC_HANDLE, SD3078_WRITE_ADDRESS, Addr, I2C_MEMADD_SIZE_8BIT, data, size, Time_out);
}


/**
  * @brief  Function Read a Byte to sd3078
  * @param  Addr: Start Reading the Starting Address
  * @param  read_buff: Data Content Read
  * @param  Time_out: Timeout duration
  * @retval HAL status
  */
uint8_t sd3078_ByteRead(uint16_t Addr, uint8_t* read_buff, uint32_t Time_out)
{
    return HAL_I2C_Mem_Read(&IIC_HANDLE, SD3078_READ_ADDRESS, Addr, I2C_MEMADD_SIZE_8BIT, read_buff, 1, Time_out);
}

/**
  * @brief  Function Read MultiByte to sd3078
  * @param  Addr: Start Reading the Starting Address
  * @param  read_buff: Data Content Read
  * @param  Size: Amount of data to be sent
  * @param  Time_out: Timeout duration
  * @retval HAL status
  */
uint8_t sd3078_MultiByteRead(uint16_t Addr, uint8_t* read_buff, uint16_t size, uint32_t Time_out)
{
    return HAL_I2C_Mem_Read(&IIC_HANDLE, SD3078_READ_ADDRESS, Addr, I2C_MEMADD_SIZE_8BIT, read_buff, size, Time_out);
}

/**
  * @brief  Function Read Device ID
  * @param  Addr: Start Reading the Starting Address
  * @param  read_buffer: Data Content Read
  * @retval HAL status
  */
uint8_t sd3078_ReadDeviceID(uint16_t Addr, uint8_t *read_buffer)
{

    return sd3078_MultiByteRead(Addr, read_buffer, DEVICEID_LEN, SD3078_TIMEOUT);
}

/**
  * @brief  Function Read Device Temperature
  * @param  Addr: Start Reading the Starting Address
  * @param  read_buffer: Data Content Read
  * @retval HAL status
  */
uint8_t sd3078_ReadDeviceTemperature(uint16_t Addr, uint8_t *read_buffer)
{
    return sd3078_ByteRead(Addr, read_buffer, SD3078_TIMEOUT);
}

/**
  * @brief  Function Read Device VBAT
  * @param  Addr: Start Reading the Starting Address
  * @param  read_buffer: Data Content Read
  * @retval HAL status
  */
uint16_t sd3078_ReadDeviceVBAT(uint16_t Addr, uint8_t *read_buffer)
{
    uint16_t vbat_val = 0;
    /* Read sd3078 vbat value */
    sd3078_MultiByteRead(Addr, read_buffer, DEVICE_VBAT_LEN, SD3078_TIMEOUT);
    vbat_val = ((read_buffer[0] >> 7) * 256) + read_buffer[1];
    return vbat_val;
}

/**
  * @brief  Function Write Enable
  * @param  Addr: Start Write the Starting Address
  * @param  data: Data Content Write
  */
void sd3078_WriteEnable(uint16_t Addr_CTR2, uint16_t Addr_CTR1)
{
    if (sd3078_ByteWrite(Addr_CTR2, &WRTC1_CTR2_SET, SD3078_TIMEOUT) != HAL_OK)
    {
        Error_Handler();
    }

    if (sd3078_ByteWrite(Addr_CTR1, &WRTC2_WRTC3_CTR1_SET, SD3078_TIMEOUT) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief  Function Write Disable
  * @param  Addr: Start Write the Starting Address
  * @param  data: Data Content Write
  */
void sd3078_WriteDisable(uint16_t Addr_CTR1, uint16_t Addr_CTR2)
{
    if (sd3078_ByteWrite(Addr_CTR1, &WRTC2_WRTC3_CTR1_RESET, SD3078_TIMEOUT) != HAL_OK)
    {
        Error_Handler();
    }

    if (sd3078_ByteWrite(Addr_CTR2, &WRTC1_CTR2_RESET, SD3078_TIMEOUT) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief  Function Write RTC Date
  * @param  Addr: Start Write the Starting Address
  * @param  write_buffer: Data Content Write
  */
void sd3078_RTC_WriteDate(uint16_t Addr, uint8_t *write_buffer)
{
    sd3078_WriteEnable(SD3078_CONTROL_CTR2, SD3078_CONTROL_CTR1);
    HAL_Delay(100);

    sd3078_MultiByteWrite(Addr, write_buffer, TIME_RTC_LEN, SD3078_TIMEOUT);
    HAL_Delay(100);
    sd3078_WriteDisable(SD3078_CONTROL_CTR1, SD3078_CONTROL_CTR2);
}


/**
  * @brief  Function Read RTC Date
  * @param  Addr: Start Write the Starting Address
  * @param  Read_buffer: Data Content Read
  */
void sd3078_RTC_ReadDate(uint16_t Addr, uint8_t *Read_buffer)
{
    sd3078_MultiByteRead(Addr, Read_buffer, TIME_RTC_LEN, SD3078_TIMEOUT);
}

/**
  * @brief  Function CountDown Interrupt
  * @param  countdowninit:  CountDown init
  * @param  writeBuffer: Data Content Write
  */
void sd3078_CountDown_interrupt(SD3078_CountDownTypeDef *countdowninit, uint8_t *writeBuffer)
{
    uint8_t FLAG_TEP = 0XF0;
    writeBuffer[0] = (countdowninit->SD3078_IM << 4) | 0xB4;        // 10H
    writeBuffer[1] = (countdowninit->ClkSource) << 4;               // 11H
    writeBuffer[2] = 0X00;                                          // 12H
    writeBuffer[3] = countdowninit->Counter_val & 0X0000FF;         // 13H
    writeBuffer[4] = (countdowninit->Counter_val & 0X00FF00) >> 8;  // 14H
    writeBuffer[5] = (countdowninit->Counter_val & 0XFF0000) >> 16; // 15H

    sd3078_ByteWrite(SD3078_CONTROL_CTR2, &FLAG_TEP, SD3078_TIMEOUT);
    sd3078_MultiByteWrite(SD3078_CONTROL_CTR2, writeBuffer, 6, SD3078_TIMEOUT);
}

/**
  * @brief  Function CountDown Interrupt
  * @param  countdowninit:  CountDown init
  * @param  writeBuffer: Data Content Write
  */
void sd3078_FreOutput_Interrupt(SD3078_FreTypeDef freoutput)
{
    uint8_t fre_buffer[2] = {0};
    /*  0XA1 CTR2(0X10)
     *  WRTC1  IM  INTS1  INTS0  FOBAT  INTDE  INTAE  INTFE
     *    1     0    1      0      0      0      0      1  (0XA1)
     *  ARST  F32K  TDS1  TDS0    FS3    FS2    FS1    FS0
     *    0     0    0      0      1      1      1      1  (0X0F)
     * (FS3 FS2 FS1 FS0) These four bits choose the frequency of the output
     * */
    fre_buffer[0] = 0xA1;
    fre_buffer[1] = freoutput;
    sd3078_MultiByteWrite(SD3078_CONTROL_CTR2, fre_buffer, 2, SD3078_TIMEOUT);
}
