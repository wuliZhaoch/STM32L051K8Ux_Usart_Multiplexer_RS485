#include "includes.h"

#define ADDRESS_DELAY   100
#define CMD_DELAY       200

//#define DATA_TOTAL_LEN  92

#define RS485_ADDRESS_CODE          0x01
#define RS485_FUNCTION_CODE         0x06

#define RS485_ADDRESS_CODE_LEN      1
#define RS485_FUNCTION_CODE_LEN     1
#define RS485_CRC_LEN               2

uint8_t rs485_buff[40] = {0};

uint32_t main_loop = 0;
//uint8_t rs485_time = 0;

//uint8_t RS485_Send_buffer[5] = {0x12, 0x55, 0xff, 0x12, 0x55};

uint8_t JSN_SR20_Buf_CMD[1] = {0x55};               // JSN_SR20 Read Command
uint8_t GY301_Buf_CMD[1] = {0xAA};                  // GY301 Read Command
uint8_t GY53L1_Buf_CMD[3] = {0xA5, 0x15, 0xBA};     // GY53L1 Read Command
uint8_t GY56_Buf_CMD[4] = {0xA5, 0x65, 0x02, 0x0C}; // GY56 Read Command


//uint8_t rs485_Send_buf[DATA_TOTAL_LEN] = {0};

void Scan_Sensor_config(uint8_t device_channel);
void SensorDataBit_Package(uint8_t *buff);


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim6)
    {
//        HAL_GPIO_TogglePin(SYSTEM_LED_GPIO_Port, SYSTEM_LED_Pin);
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
        PackBuffer.counter_time = 0;
        memset(&PackBuffer.channel_buffer, 0, sizeof(PackBuffer.channel_buffer));

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

//        /* printf rs485_Send_buf[] data */
//        for (uint8_t i = 0; i < CHANNEL_NUMBER; i++)
//        {
//            for (uint8_t j = 0; j < PACKAGE_BUFFER_LEN; j++)
//            {
//                rs485_Send_buf[rs485_time] = PackBuffer.channel_buffer[i][j];
//                rs485_time++;
//            }
//        }

//        rs485_time = 0;

        SensorDataBit_Package(rs485_buff);
        RS485_TRANSMIT_MODE;
        HAL_Delay(10);
        HAL_UART_Transmit(&huart1, rs485_buff, 40, 200);
        RS485_RECEIVE_MODE;

    }

}



/**
  * @brief  Sensor Data Bit Package.
  * @retval None.
  */
void SensorDataBit_Package(uint8_t *buff)
{

    for (uint8_t i = 0; i < 8; i++)
    {
        /*  红外测距接收数据并提取数据域 (GY-56) */
        if ((PackBuffer.channel_buffer[i][0] == 0x5A)
                && (PackBuffer.channel_buffer[i][1] == 0x5A)
                && (PackBuffer.channel_buffer[i][2] == 0x15)
                && (PackBuffer.channel_buffer[i][3] == 0x04)
                && ((uint8_t) ((PackBuffer.channel_buffer[i][0]
                + PackBuffer.channel_buffer[i][1]
                + PackBuffer.channel_buffer[i][2]
                + PackBuffer.channel_buffer[i][3]
                + PackBuffer.channel_buffer[i][4]
                + PackBuffer.channel_buffer[i][5]
                + PackBuffer.channel_buffer[i][6]
                + PackBuffer.channel_buffer[i][7]))
                == PackBuffer.channel_buffer[i][8])) {
            *buff++ = PackBuffer.channel_buffer[i][4];
            *buff++ = PackBuffer.channel_buffer[i][5];
        }

        /*  红外测距接收数据并提取数据域 (GY-53L1) */
        if ((PackBuffer.channel_buffer[i][0] == 0x5A)
            && (PackBuffer.channel_buffer[i][1] == 0x5A)
            && (PackBuffer.channel_buffer[i][2] == 0x15)
            && (PackBuffer.channel_buffer[i][3] == 0x03)
            && ((uint8_t) ((PackBuffer.channel_buffer[i][0]
            + PackBuffer.channel_buffer[i][1]
            + PackBuffer.channel_buffer[i][2]
            + PackBuffer.channel_buffer[i][3]
            + PackBuffer.channel_buffer[i][4]
            + PackBuffer.channel_buffer[i][5]
            + PackBuffer.channel_buffer[i][6]))
            == PackBuffer.channel_buffer[i][7]))
        {
            *buff++ = PackBuffer.channel_buffer[i][4];
            *buff++ = PackBuffer.channel_buffer[i][5];
        }

        /* 光照强度接收数据并提取数据域 (GY-301) */
        if ((PackBuffer.channel_buffer[i][0] == 0x4C)
            && (PackBuffer.channel_buffer[i][1] == 0x3A)
            && (PackBuffer.channel_buffer[i][9] == 0x0D)
            && (PackBuffer.channel_buffer[i][10] == 0x0A))
        {
            *buff++ = PackBuffer.channel_buffer[i][2];
            *buff++ = PackBuffer.channel_buffer[i][3];
            *buff++ = PackBuffer.channel_buffer[i][4];
            *buff++ = PackBuffer.channel_buffer[i][5];
            *buff++ = PackBuffer.channel_buffer[i][6];
        }

        /* 超声波测距接收数据并提取数据域 JSN-SR20-Y1 */
        if ((PackBuffer.channel_buffer[i][0] == 0xFF)
            && ((uint8_t) ((PackBuffer.channel_buffer[i][0]
            + PackBuffer.channel_buffer[i][1]
            + PackBuffer.channel_buffer[i][2]))
            == PackBuffer.channel_buffer[i][3]))
        {
            *buff++ = PackBuffer.channel_buffer[i][1];
            *buff++ = PackBuffer.channel_buffer[i][2];
        }
    }

}

/**
  * @brief  Power on Scan Sensor Device.
  * @retval None.
  */
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

