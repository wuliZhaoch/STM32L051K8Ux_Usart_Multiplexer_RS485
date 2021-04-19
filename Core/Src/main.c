#include "includes.h"

uint32_t main_loop = 0;

uint8_t RS485_Send_buffer[5] = {0x12, 0x55, 0xff, 0x12, 0x55};

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim6)
    {
        HAL_GPIO_TogglePin(SYSTEM_LED_GPIO_Port, SYSTEM_LED_Pin);
    }

}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

    HAL_Init();

    /* System Clock Config */
    SystemClock_Config();

    /* System Delay Initialize */
    HAL_Delay_init();
    MX_GPIO_Init();         // System GPIO Initialize
    MX_DMA_Init();          // System DMA Initialize
    MX_USART1_UART_Init();  // System Usart1 Initialize (RS485)
    MX_USART2_UART_Init();  // System Usart2 Initialize
    MX_I2C1_Init();         // System IIC Initialize
    MX_TIM6_Init();         // System Timer Initialize (1S)

    SGM4581_Address_set(Select_Address_x7);     // Set up channel 7 to receive data



    while (1)
    {

        RS485_TRANSMIT_MODE;
        HAL_UART_Transmit(&huart1, RS485_Send_buffer, 5, 1000);
        HAL_Delay(200);
        RS485_RECEIVE_MODE;

        printf("System Mainloop is: %ld\r\n", main_loop);
        main_loop++;
        HAL_Delay_us(1000000);


    }

}



