#include "includes.h"


#define STOPMODE_WAKEUP_TIME    10


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

    /* Debug Mode Use */
    HAL_DBGMCU_DBG_DisableLowPowerConfig(DBGMCU_STOP || DBGMCU_SLEEP || DBGMCU_STANDBY);
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
    MX_RTC_Init();

    HAL_Delay(5000);
    /* Enter into Low Power Config */
    Enter_into_lowpower_config();

    while (1)
    {
        LED_Blink(10, 200);

        char *str = "Enter into stop mode\r\n";
        HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);

        /* Enter into Stop Mode */
        Enter_into_Stopmode(STOPMODE_WAKEUP_TIME);

        char *str1 = "Wakeup From stop mode \r\n";
        HAL_UART_Transmit(&huart1, (uint8_t *)str1, strlen(str1), HAL_MAX_DELAY);


//        printf("System mainloop is : %ld\r\n", main_loop);
//        main_loop++;
//        HAL_Delay_US(1000000);

    }

}



