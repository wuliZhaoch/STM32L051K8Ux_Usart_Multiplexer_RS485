#include "includes.h"

uint32_t main_loop = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim6)
    {
        HAL_GPIO_TogglePin(SYSTEM_LED_GPIO_Port, SYSTEM_LED_Pin);
    }

}

int main(void)
{

    HAL_Init();


    SystemClock_Config();

    HAL_Delay_init();
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();
    MX_I2C1_Init();
    MX_TIM6_Init();

    SGM4581_Address_set(Select_Address_x7);
    while (1)
    {

        printf("System Mainloop is: %ld\r\n", main_loop);
        main_loop++;
        HAL_Delay_us(1000000);
//        HAL_Delay_ms(1000);
//        HAL_Delay(1000);
//        HAL_GPIO_TogglePin(SYSTEM_LED_GPIO_Port, SYSTEM_LED_Pin);


    }

}



