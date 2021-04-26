#include "includes.h"

#define ADDRESS_DELAY   100
#define CMD_DELAY       200

uint32_t main_loop = 0;

uint8_t RS485_Send_buffer[5] = {0x12, 0x55, 0xff, 0x12, 0x55};

uint8_t JSN_SR20_Buf_CMD[1] = {0x55};               // JSN_SR20 Read Command
uint8_t GY301_Buf_CMD[1] = {0xAA};                  // GY301 Read Command
uint8_t GY53L1_Buf_CMD[3] = {0xA5, 0x15, 0xBA};     // GY53L1 Read Command
uint8_t GY56_Buf_CMD[4] = {0xA5, 0x65, 0x02, 0x0C}; // GY56 Read Command



uint8_t ODOA_Buff[2] = {0x0d,0x0a};

uint8_t rs485_buf[23] = {0};

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim6)
    {
//        HAL_GPIO_TogglePin(SYSTEM_LED_GPIO_Port, SYSTEM_LED_Pin);

    }
}


void Scan_Sensor_config(uint8_t device_channel)
{
    switch(device_channel)
    {
        case Select_Address_x0:
            SGM4581_Address_set(Select_Address_x0);
            HAL_Delay(ADDRESS_DELAY);

            HAL_UART_Transmit(&huart2, JSN_SR20_Buf_CMD, sizeof(JSN_SR20_Buf_CMD)/sizeof(JSN_SR20_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (JSN_SR20_revDef.JSN_SR20_Flag == 1)
            {
                JSN_SR20_revDef.JSN_SR20_Flag = 0;
                SenserCMD.channel_cmd0 = JSN_SR20_Buf_CMD;
                SenserLEN.channel_cmd0_len = sizeof(JSN_SR20_Buf_CMD)/sizeof(JSN_SR20_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY301_Buf_CMD, sizeof(GY301_Buf_CMD)/sizeof(GY301_Buf_CMD[0]), 200);
            HAL_Delay(500);
            if (GY301_revDef.GY301_Flag == 1)
            {
                GY301_revDef.GY301_Flag = 0;
                SenserCMD.channel_cmd0 = GY301_Buf_CMD;
                SenserLEN.channel_cmd0_len = sizeof(GY301_Buf_CMD)/sizeof(GY301_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY53L1_Buf_CMD, sizeof(GY53L1_Buf_CMD)/sizeof(GY53L1_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (GY53L1_revDef.GY53L1_Flag == 1)
            {
                GY53L1_revDef.GY53L1_Flag = 0;
                SenserCMD.channel_cmd0 = GY53L1_Buf_CMD;
                SenserLEN.channel_cmd0_len = sizeof(GY53L1_Buf_CMD)/sizeof(GY53L1_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY56_Buf_CMD, sizeof(GY56_Buf_CMD)/sizeof(GY56_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (GY56_revDef.GY56_Flag == 1)
            {
                GY56_revDef.GY56_Flag = 0;
                SenserCMD.channel_cmd0 = GY56_Buf_CMD;
                SenserLEN.channel_cmd0_len = sizeof(GY56_Buf_CMD)/sizeof(GY56_Buf_CMD[0]);
            }
            break;
        case Select_Address_x1:
            SGM4581_Address_set(Select_Address_x1);
            HAL_Delay(ADDRESS_DELAY);

            HAL_UART_Transmit(&huart2, JSN_SR20_Buf_CMD, sizeof(JSN_SR20_Buf_CMD)/sizeof(JSN_SR20_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (JSN_SR20_revDef.JSN_SR20_Flag == 1)
            {
                JSN_SR20_revDef.JSN_SR20_Flag = 0;
                SenserCMD.channel_cmd1 = JSN_SR20_Buf_CMD;
                SenserLEN.channel_cmd1_len = sizeof(JSN_SR20_Buf_CMD)/sizeof(JSN_SR20_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY301_Buf_CMD, sizeof(GY301_Buf_CMD)/sizeof(GY301_Buf_CMD[0]), 200);
            HAL_Delay(500);
            if (GY301_revDef.GY301_Flag == 1)
            {
                GY301_revDef.GY301_Flag = 0;
                SenserCMD.channel_cmd1 = GY301_Buf_CMD;
                SenserLEN.channel_cmd1_len = sizeof(GY301_Buf_CMD)/sizeof(GY301_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY53L1_Buf_CMD, sizeof(GY53L1_Buf_CMD)/sizeof(GY53L1_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (GY53L1_revDef.GY53L1_Flag == 1)
            {
                GY53L1_revDef.GY53L1_Flag = 0;
                SenserCMD.channel_cmd1 = GY53L1_Buf_CMD;
                SenserLEN.channel_cmd1_len = sizeof(GY53L1_Buf_CMD)/sizeof(GY53L1_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY56_Buf_CMD, sizeof(GY56_Buf_CMD)/sizeof(GY56_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (GY56_revDef.GY56_Flag == 1)
            {
                GY56_revDef.GY56_Flag = 0;
                SenserCMD.channel_cmd1 = GY56_Buf_CMD;
                SenserLEN.channel_cmd1_len = sizeof(GY56_Buf_CMD)/sizeof(GY56_Buf_CMD[0]);
            }
            break;
        case Select_Address_x2:
            SGM4581_Address_set(Select_Address_x2);
            HAL_Delay(ADDRESS_DELAY);

            HAL_UART_Transmit(&huart2, JSN_SR20_Buf_CMD, sizeof(JSN_SR20_Buf_CMD)/sizeof(JSN_SR20_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (JSN_SR20_revDef.JSN_SR20_Flag == 1)
            {
                JSN_SR20_revDef.JSN_SR20_Flag = 0;
                SenserCMD.channel_cmd2 = JSN_SR20_Buf_CMD;
                SenserLEN.channel_cmd2_len = sizeof(JSN_SR20_Buf_CMD)/sizeof(JSN_SR20_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY301_Buf_CMD, sizeof(GY301_Buf_CMD)/sizeof(GY301_Buf_CMD[0]), 200);
            HAL_Delay(500);
            if (GY301_revDef.GY301_Flag == 1)
            {
                GY301_revDef.GY301_Flag = 0;
                SenserCMD.channel_cmd2 = GY301_Buf_CMD;
                SenserLEN.channel_cmd2_len = sizeof(GY301_Buf_CMD)/sizeof(GY301_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY53L1_Buf_CMD, sizeof(GY53L1_Buf_CMD)/sizeof(GY53L1_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (GY53L1_revDef.GY53L1_Flag == 1)
            {
                GY53L1_revDef.GY53L1_Flag = 0;
                SenserCMD.channel_cmd2 = GY53L1_Buf_CMD;
                SenserLEN.channel_cmd2_len = sizeof(GY53L1_Buf_CMD)/sizeof(GY53L1_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY56_Buf_CMD, sizeof(GY56_Buf_CMD)/sizeof(GY56_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (GY56_revDef.GY56_Flag == 1)
            {
                GY56_revDef.GY56_Flag = 0;
                SenserCMD.channel_cmd2 = GY56_Buf_CMD;
                SenserLEN.channel_cmd2_len = sizeof(GY56_Buf_CMD)/sizeof(GY56_Buf_CMD[0]);
            }
            break;
        case Select_Address_x3:
            SGM4581_Address_set(Select_Address_x3);
            HAL_Delay(ADDRESS_DELAY);

            HAL_UART_Transmit(&huart2, JSN_SR20_Buf_CMD, sizeof(JSN_SR20_Buf_CMD)/sizeof(JSN_SR20_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (JSN_SR20_revDef.JSN_SR20_Flag == 1)
            {
                JSN_SR20_revDef.JSN_SR20_Flag = 0;
                SenserCMD.channel_cmd3 = JSN_SR20_Buf_CMD;
                SenserLEN.channel_cmd3_len = sizeof(JSN_SR20_Buf_CMD)/sizeof(JSN_SR20_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY301_Buf_CMD, sizeof(GY301_Buf_CMD)/sizeof(GY301_Buf_CMD[0]), 200);
            HAL_Delay(500);
            if (GY301_revDef.GY301_Flag == 1)
            {
                GY301_revDef.GY301_Flag = 0;
                SenserCMD.channel_cmd3 = GY301_Buf_CMD;
                SenserLEN.channel_cmd3_len = sizeof(GY301_Buf_CMD)/sizeof(GY301_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY53L1_Buf_CMD, sizeof(GY53L1_Buf_CMD)/sizeof(GY53L1_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (GY53L1_revDef.GY53L1_Flag == 1)
            {
                GY53L1_revDef.GY53L1_Flag = 0;
                SenserCMD.channel_cmd3 = GY53L1_Buf_CMD;
                SenserLEN.channel_cmd3_len = sizeof(GY53L1_Buf_CMD)/sizeof(GY53L1_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY56_Buf_CMD, sizeof(GY56_Buf_CMD)/sizeof(GY56_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (GY56_revDef.GY56_Flag == 1)
            {
                GY56_revDef.GY56_Flag = 0;
                SenserCMD.channel_cmd3 = GY56_Buf_CMD;
                SenserLEN.channel_cmd3_len = sizeof(GY56_Buf_CMD)/sizeof(GY56_Buf_CMD[0]);
            }
            break;
        case Select_Address_x4:
            SGM4581_Address_set(Select_Address_x4);
            HAL_Delay(ADDRESS_DELAY);

            HAL_UART_Transmit(&huart2, JSN_SR20_Buf_CMD, sizeof(JSN_SR20_Buf_CMD)/sizeof(JSN_SR20_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (JSN_SR20_revDef.JSN_SR20_Flag == 1)
            {
                JSN_SR20_revDef.JSN_SR20_Flag = 0;
                SenserCMD.channel_cmd4 = JSN_SR20_Buf_CMD;
                SenserLEN.channel_cmd4_len = sizeof(JSN_SR20_Buf_CMD)/sizeof(JSN_SR20_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY301_Buf_CMD, sizeof(GY301_Buf_CMD)/sizeof(GY301_Buf_CMD[0]), 200);
            HAL_Delay(500);
            if (GY301_revDef.GY301_Flag == 1)
            {
                GY301_revDef.GY301_Flag = 0;
                SenserCMD.channel_cmd4 = GY301_Buf_CMD;
                SenserLEN.channel_cmd4_len = sizeof(GY301_Buf_CMD)/sizeof(GY301_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY53L1_Buf_CMD, sizeof(GY53L1_Buf_CMD)/sizeof(GY53L1_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (GY53L1_revDef.GY53L1_Flag == 1)
            {
                GY53L1_revDef.GY53L1_Flag = 0;
                SenserCMD.channel_cmd4 = GY53L1_Buf_CMD;
                SenserLEN.channel_cmd4_len = sizeof(GY53L1_Buf_CMD)/sizeof(GY53L1_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY56_Buf_CMD, sizeof(GY56_Buf_CMD)/sizeof(GY56_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (GY56_revDef.GY56_Flag == 1)
            {
                GY56_revDef.GY56_Flag = 0;
                SenserCMD.channel_cmd4 = GY56_Buf_CMD;
                SenserLEN.channel_cmd4_len = sizeof(GY56_Buf_CMD)/sizeof(GY56_Buf_CMD[0]);
            }
            break;
        case Select_Address_x5:
            SGM4581_Address_set(Select_Address_x5);
            HAL_Delay(ADDRESS_DELAY);

            HAL_UART_Transmit(&huart2, JSN_SR20_Buf_CMD, sizeof(JSN_SR20_Buf_CMD)/sizeof(JSN_SR20_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (JSN_SR20_revDef.JSN_SR20_Flag == 1)
            {
                JSN_SR20_revDef.JSN_SR20_Flag = 0;
                SenserCMD.channel_cmd5 = JSN_SR20_Buf_CMD;
                SenserLEN.channel_cmd5_len = sizeof(JSN_SR20_Buf_CMD)/sizeof(JSN_SR20_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY301_Buf_CMD, sizeof(GY301_Buf_CMD)/sizeof(GY301_Buf_CMD[0]), 200);
            HAL_Delay(500);
            if (GY301_revDef.GY301_Flag == 1)
            {
                GY301_revDef.GY301_Flag = 0;
                SenserCMD.channel_cmd5 = GY301_Buf_CMD;
                SenserLEN.channel_cmd5_len = sizeof(GY301_Buf_CMD)/sizeof(GY301_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY53L1_Buf_CMD, sizeof(GY53L1_Buf_CMD)/sizeof(GY53L1_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (GY53L1_revDef.GY53L1_Flag == 1)
            {
                GY53L1_revDef.GY53L1_Flag = 0;
                SenserCMD.channel_cmd5 = GY53L1_Buf_CMD;
                SenserLEN.channel_cmd5_len = sizeof(GY53L1_Buf_CMD)/sizeof(GY53L1_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY56_Buf_CMD, sizeof(GY56_Buf_CMD)/sizeof(GY56_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (GY56_revDef.GY56_Flag == 1)
            {
                GY56_revDef.GY56_Flag = 0;
                SenserCMD.channel_cmd5 = GY56_Buf_CMD;
                SenserLEN.channel_cmd5_len = sizeof(GY56_Buf_CMD)/sizeof(GY56_Buf_CMD[0]);
            }
            break;
        case Select_Address_x6:
            SGM4581_Address_set(Select_Address_x6);
            HAL_Delay(ADDRESS_DELAY);

            HAL_UART_Transmit(&huart2, JSN_SR20_Buf_CMD, sizeof(JSN_SR20_Buf_CMD)/sizeof(JSN_SR20_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (JSN_SR20_revDef.JSN_SR20_Flag == 1)
            {
                JSN_SR20_revDef.JSN_SR20_Flag = 0;
                SenserCMD.channel_cmd6 = JSN_SR20_Buf_CMD;
                SenserLEN.channel_cmd6_len = sizeof(JSN_SR20_Buf_CMD)/sizeof(JSN_SR20_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY301_Buf_CMD, sizeof(GY301_Buf_CMD)/sizeof(GY301_Buf_CMD[0]), 200);
            HAL_Delay(500);
            if (GY301_revDef.GY301_Flag == 1)
            {
                GY301_revDef.GY301_Flag = 0;
                SenserCMD.channel_cmd6 = GY301_Buf_CMD;
                SenserLEN.channel_cmd6_len = sizeof(GY301_Buf_CMD)/sizeof(GY301_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY53L1_Buf_CMD, sizeof(GY53L1_Buf_CMD)/sizeof(GY53L1_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (GY53L1_revDef.GY53L1_Flag == 1)
            {
                GY53L1_revDef.GY53L1_Flag = 0;
                SenserCMD.channel_cmd6 = GY53L1_Buf_CMD;
                SenserLEN.channel_cmd6_len = sizeof(GY53L1_Buf_CMD)/sizeof(GY53L1_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY56_Buf_CMD, sizeof(GY56_Buf_CMD)/sizeof(GY56_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (GY56_revDef.GY56_Flag == 1)
            {
                GY56_revDef.GY56_Flag = 0;
                SenserCMD.channel_cmd6 = GY56_Buf_CMD;
                SenserLEN.channel_cmd6_len = sizeof(GY56_Buf_CMD)/sizeof(GY56_Buf_CMD[0]);
            }
            break;
        case Select_Address_x7:
            SGM4581_Address_set(Select_Address_x7);
            HAL_Delay(ADDRESS_DELAY);

            HAL_UART_Transmit(&huart2, JSN_SR20_Buf_CMD, sizeof(JSN_SR20_Buf_CMD)/sizeof(JSN_SR20_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (JSN_SR20_revDef.JSN_SR20_Flag == 1)
            {
                JSN_SR20_revDef.JSN_SR20_Flag = 0;
                SenserCMD.channel_cmd7 = JSN_SR20_Buf_CMD;
                SenserLEN.channel_cmd7_len = sizeof(JSN_SR20_Buf_CMD)/sizeof(JSN_SR20_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY301_Buf_CMD, sizeof(GY301_Buf_CMD)/sizeof(GY301_Buf_CMD[0]), 200);
            HAL_Delay(500);
            if (GY301_revDef.GY301_Flag == 1)
            {
                GY301_revDef.GY301_Flag = 0;
                SenserCMD.channel_cmd7 = GY301_Buf_CMD;
                SenserLEN.channel_cmd7_len = sizeof(GY301_Buf_CMD)/sizeof(GY301_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY53L1_Buf_CMD, sizeof(GY53L1_Buf_CMD)/sizeof(GY53L1_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (GY53L1_revDef.GY53L1_Flag == 1)
            {
                GY53L1_revDef.GY53L1_Flag = 0;
                SenserCMD.channel_cmd7 = GY53L1_Buf_CMD;
                SenserLEN.channel_cmd7_len = sizeof(GY53L1_Buf_CMD)/sizeof(GY53L1_Buf_CMD[0]);
            }

            HAL_UART_Transmit(&huart2, GY56_Buf_CMD, sizeof(GY56_Buf_CMD)/sizeof(GY56_Buf_CMD[0]), 200);
            HAL_Delay(CMD_DELAY);
            if (GY56_revDef.GY56_Flag == 1)
            {
                GY56_revDef.GY56_Flag = 0;
                SenserCMD.channel_cmd7 = GY56_Buf_CMD;
                SenserLEN.channel_cmd7_len = sizeof(GY56_Buf_CMD)/sizeof(GY56_Buf_CMD[0]);
            }
            break;
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

    PackBuffer.counter_time = 0;
    Scan_Sensor_config(Select_Address_x0);
    Scan_Sensor_config(Select_Address_x1);
    Scan_Sensor_config(Select_Address_x2);
    Scan_Sensor_config(Select_Address_x3);
    Scan_Sensor_config(Select_Address_x4);
    Scan_Sensor_config(Select_Address_x5);
    Scan_Sensor_config(Select_Address_x6);
    Scan_Sensor_config(Select_Address_x7);

    memset(&USART2_ReceiveDef.Receive_pData, 0, sizeof(USART2_ReceiveDef.Receive_pData));
    memset(&PackBuffer.channel_buffer, 0, sizeof(PackBuffer.channel_buffer));

    memset(&JSN_SR20_revDef.JSN_SR20_pData, 0, sizeof(JSN_SR20_revDef.JSN_SR20_pData));
    memset(&GY301_revDef.GY301_pData, 0, sizeof(GY301_revDef.GY301_pData));
    memset(&GY53L1_revDef.GY53L1_pData, 0, sizeof(GY53L1_revDef.GY53L1_pData));
    memset(&GY56_revDef.GY56_pData, 0, sizeof(GY56_revDef.GY56_pData));

    System_LED_Blink(20, 50);
    while (1)
    {
        HAL_Delay_ms(100);
        SGM4581_Address_set(Select_Address_x0);
        HAL_UART_Transmit(&huart2, SenserCMD.channel_cmd0, SenserLEN.channel_cmd0_len, 200);
        HAL_Delay_ms(100);

        SGM4581_Address_set(Select_Address_x1);
        HAL_UART_Transmit(&huart2, SenserCMD.channel_cmd1, SenserLEN.channel_cmd1_len, 200);
        HAL_Delay_ms(100);

        SGM4581_Address_set(Select_Address_x2);
        HAL_UART_Transmit(&huart2, SenserCMD.channel_cmd2, SenserLEN.channel_cmd2_len, 200);
        HAL_Delay_ms(100);

        SGM4581_Address_set(Select_Address_x3);
        HAL_UART_Transmit(&huart2, SenserCMD.channel_cmd3, SenserLEN.channel_cmd3_len, 200);
        HAL_Delay_ms(100);

        SGM4581_Address_set(Select_Address_x4);
        HAL_UART_Transmit(&huart2, SenserCMD.channel_cmd4, SenserLEN.channel_cmd4_len, 200);
        HAL_Delay_ms(100);

        SGM4581_Address_set(Select_Address_x5);
        HAL_UART_Transmit(&huart2, SenserCMD.channel_cmd5, SenserLEN.channel_cmd5_len, 200);
        HAL_Delay_ms(100);

        SGM4581_Address_set(Select_Address_x6);
        HAL_UART_Transmit(&huart2, SenserCMD.channel_cmd6, SenserLEN.channel_cmd6_len, 200);
        HAL_Delay_ms(100);

        SGM4581_Address_set(Select_Address_x7);
        HAL_UART_Transmit(&huart2, SenserCMD.channel_cmd7, SenserLEN.channel_cmd7_len, 200);
        HAL_Delay_ms(100);

        PackBuffer.counter_time = 0;
        memset(&PackBuffer.channel_buffer, 0, sizeof(PackBuffer.channel_buffer));


        RS485_TRANSMIT_MODE;
        HAL_Delay(10);
        HAL_UART_Transmit(&huart1, rs485_buf, 23, 200);
        RS485_RECEIVE_MODE;

    }

}



