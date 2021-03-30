#include "includes.h"

uint32_t main_loop = 0;

void LED_Blink(uint16_t Blink_counter, uint16_t period)
{
    for (uint16_t i = 0; i < Blink_counter; i++)
    {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_15);
        HAL_Delay(period);
    }

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
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

    while (1)
    {
        LED_Blink(10, 200);

//        printf("System mainloop is : %ld\r\n", main_loop);
//        main_loop++;
//        HAL_Delay_US(1000000);

    }

}



