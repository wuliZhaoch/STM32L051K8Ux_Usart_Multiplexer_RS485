#include "includes.h"

uint32_t main_loop = 0;

uint8_t RS485_Send_buffer[5] = {0x12, 0x55, 0xff, 0x12, 0x55};

uint8_t JSN_SR20_CMD = 0X55;
uint8_t GY301_CMD = 0XAA;
uint8_t GY53L1_Buf_CMD[3] = {0XA5, 0X15, 0XBA};
uint8_t ODOA_Buff[2] = {0x0d,0x0a};

uint8_t rs485_buf[23] = {0};

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



    while (1)
    {
        SGM4581_Address_set(Select_Address_x6);
        HAL_Delay(100);
        HAL_UART_Transmit(&huart2, GY53L1_Buf_CMD, 3, 200);
        HAL_Delay(100);

        SGM4581_Address_set(Select_Address_x5);
        HAL_Delay(100);
        HAL_UART_Transmit(&huart2, &JSN_SR20_CMD, 1, 200);
        HAL_Delay(100);

        SGM4581_Address_set(Select_Address_x4);
        HAL_Delay(100);
        HAL_UART_Transmit(&huart2, &GY301_CMD, 1, 200);
        HAL_Delay(100);


        for (uint8_t i = 0; i < GY53L1_RECEIVE_LEN; i++)
        {
            rs485_buf[i] = GY53L1_revDef.GY53L1_pData[i];
        }
        for (uint8_t i = 0; i < SR20_RECEIVE_LEN; i++)
        {
            rs485_buf[i + GY53L1_RECEIVE_LEN] = JSN_SR20_revDef.JSN_SR20_pData[i];
        }
        for (uint8_t i = 0; i < GY301_RECEIVE_LEN; i++)
        {
            rs485_buf[i + GY53L1_RECEIVE_LEN + SR20_RECEIVE_LEN] = GY301_revDef.GY301_pData[i];
        }

        RS485_TRANSMIT_MODE;
        HAL_Delay(10);
        HAL_UART_Transmit(&huart1, rs485_buf, 23, 200);
        HAL_Delay(100);
//        HAL_UART_Transmit(&huart1, GY53L1_revDef.GY53L1_pData, GY53L1_RECEIVE_LEN, 200);
//        HAL_Delay(100);
//
//        HAL_UART_Transmit(&huart1, JSN_SR20_revDef.JSN_SR20_pData, SR20_RECEIVE_LEN, 200);
//        HAL_Delay(100);
//
//        HAL_UART_Transmit(&huart1, GY301_revDef.GY301_pData, GY301_RECEIVE_LEN, 200);
//        HAL_Delay(100);
        RS485_RECEIVE_MODE;

        HAL_Delay(2000);

    }

}



