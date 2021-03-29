#include "includes.h"

uint32_t main_loop = 0;

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
        printf("System mainloop is : %ld\r\n", main_loop);
        main_loop++;
        HAL_Delay_US(1000000);

    }

}



