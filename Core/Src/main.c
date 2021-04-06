#include "includes.h"


#define STOPMODE_WAKEUP_TIME    10

SD3078_DeviceIDypeDef DeviceID;
uint8_t sd3078_DeviceTemp = 0;

uint8_t sd3078_countDown_buffer[6] = {0};

uint8_t sd3078_VBATBUFF[2] = {0};
uint16_t sd3078_VBAT = 0;
SD3078_TimeTypeDef sd3078_readtime_buf;
SD3078_CountDownTypeDef sd3078_countDown_init;
ChipIDTypeDef ChipID_VAL;

uint8_t eeprom_readbuffer[100] = {0};
uint8_t eeprom_writebuffer[5] = {0x12, 0x34, 0x56, 0xff, 0xA5};

FLASH_EraseInitTypeDef EraseInitStruct;


uint32_t main_loop = 0;

void LED_Blink(uint16_t Blink_counter, uint16_t period)
{
    for (uint16_t i = 0; i < Blink_counter; i++)
    {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_15);
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
        HAL_Delay(period);
    }

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
}

void Enter_into_lowpower_config(void)
{
    /* Enable Ultra low power mode */
    HAL_PWREx_EnableUltraLowPower();
    /* Enable the fast wake up from Ultra low power mode */
    HAL_PWREx_EnableFastWakeUp();
    /* Select HSI as system clock source after Wake Up from Stop mode */
    __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_HSI);
}


void Enter_into_Stopmode(uint32_t wakeup_sec)
{
    Enter_into_lowPower_GpioConfig();
    HAL_Delay(10);

    HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
    HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, wakeup_sec, RTC_WAKEUPCLOCK_CK_SPRE_16BITS);
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);


    __HAL_RCC_PWR_CLK_ENABLE();
    SystemClock_Config();

    MX_GPIO_Init();
    HAL_UART_DeInit(&huart1);
    MX_USART1_UART_Init();
    MX_RTC_Init();
}

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_I2C1_Init();
    MX_RTC_Init();

    HAL_Delay(1000);

    GET_ChipID(&ChipID_VAL);
    printf("Chip ID is: %ld-%ld-%ld\r\n", ChipID_VAL.Chip_ID_H, ChipID_VAL.Chip_ID_M, ChipID_VAL.Chip_ID_L);

    HAL_Delay(200);
    chip_eeprom_writeByte(0x00, eeprom_writebuffer, 5);
    HAL_Delay(200);
    chip_eeprom_readByte(0x00, eeprom_readbuffer, 5);
    /* RTC Time set */
//    sd3078_RTC_WriteDate(SD3078_RTC_SECOND, Time_RTC_Init);
//    HAL_Delay(200);
//
//    sd3078_RTC_ReadDate(SD3078_RTC_SECOND, sd3078_readtime_buf.sd3078_readtime_buf);
//    printf("SD3078 RTC Time is: %d/%d/%d %d  %d:%d:%d\r\n",
//            sd3078_readtime_buf.sd3078_readtime_buf[6],
//            sd3078_readtime_buf.sd3078_readtime_buf[5],
//            sd3078_readtime_buf.sd3078_readtime_buf[4],
//            sd3078_readtime_buf.sd3078_readtime_buf[3],
//            sd3078_readtime_buf.sd3078_readtime_buf[2] & 0x7F,
//            sd3078_readtime_buf.sd3078_readtime_buf[1],
//            sd3078_readtime_buf.sd3078_readtime_buf[0]);
//
//
//    sd3078_countDown_init.SD3078_IM = 0x01;
//    sd3078_countDown_init.ClkSource = Source_1S;
//    sd3078_countDown_init.Counter_val = 0x0A;
//    sd3078_CountDown_interrupt(&sd3078_countDown_init, sd3078_countDown_buffer);
//
//    /* sd3078 Device ID */
//    if (sd3078_ReadDeviceID(SD3078_DEVICE_ID1, DeviceID.DeviceID_Buffer) == HAL_OK)
//    {
//        HAL_UART_Transmit(&huart1, DeviceID.DeviceID_Buffer, DEVICEID_LEN, HAL_MAX_DELAY);
//    } else {
//        Error_Handler();
//    }
//    HAL_Delay(200);
//
//
//
//    /* sd3078 Device Temperature */
//    if (sd3078_ReadDeviceTemperature(SD3078_DEVICE_ID1, &sd3078_DeviceTemp) == HAL_OK)
//    {
//        HAL_UART_Transmit(&huart1, &sd3078_DeviceTemp, 1, HAL_MAX_DELAY);
//    } else {
//        Error_Handler();
//    }
//
//    HAL_Delay(100);
//    sd3078_VBAT = sd3078_ReadDeviceVBAT(SD3078_EXPANSION_CTR5, sd3078_VBATBUFF);
//
//    /* Enter into Low Power Config */
//    Enter_into_lowpower_config();

    while (1)
    {
        LED_Blink(10, 200);

//        sd3078_VBAT = sd3078_ReadDeviceVBAT(SD3078_EXPANSION_CTR5, sd3078_VBATBUFF);
//        printf("VBAT is : %d.%d%d V\r\n", sd3078_VBAT/100, sd3078_VBAT%100/10, sd3078_VBAT%10);
//
//        char *str = "Enter into stop mode\r\n";
//        HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
//
//        /* Enter into Stop Mode */
//        Enter_into_Stopmode(STOPMODE_WAKEUP_TIME);
//
//        char *str1 = "Wakeup From stop mode \r\n";
//        HAL_UART_Transmit(&huart1, (uint8_t *)str1, strlen(str1), HAL_MAX_DELAY);


//        printf("System mainloop is : %ld\r\n", main_loop);
//        main_loop++;
//        HAL_Delay_US(1000000);

    }

}



