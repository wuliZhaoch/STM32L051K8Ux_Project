/*
 * sd3078.c
 *
 *  Created on: 2020-03-30
 *      Author: wuliZhao_ch
 *       brief: Source file of SD3078.
 *   attention: Use for SD3078.
 */
#include "sd3078.h"


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
  * @brief  Function Read a Byte to sd3078
  * @param  Addr: Start Reading the Starting Address
  * @param  Data: Data Content Read
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
  * @param  Read_Data: Data Content Read
  * @param  Size: Amount of data to be sent
  * @param  Time_out: Timeout duration
  * @retval HAL status
  */
uint8_t sd3078_MultiByteRead(uint16_t Addr, uint8_t* read_buff, uint16_t size, uint32_t Time_out)
{
    return HAL_I2C_Mem_Read(&IIC_HANDLE, SD3078_READ_ADDRESS, Addr, I2C_MEMADD_SIZE_8BIT, read_buff, size, Time_out);
}
