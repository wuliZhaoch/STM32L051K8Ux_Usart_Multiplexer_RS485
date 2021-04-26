/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32l0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim6;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
/* USER CODE BEGIN EV */

extern uint8_t counter_time;
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32L0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel 2 and channel 3 interrupts.
  */
void DMA1_Channel2_3_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel2_3_IRQn 0 */

  /* USER CODE END DMA1_Channel2_3_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_tx);
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
  /* USER CODE BEGIN DMA1_Channel2_3_IRQn 1 */

  /* USER CODE END DMA1_Channel2_3_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel 4, channel 5, channel 6 and channel 7 interrupts.
  */
void DMA1_Channel4_5_6_7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel4_5_6_7_IRQn 0 */

  /* USER CODE END DMA1_Channel4_5_6_7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_tx);
  HAL_DMA_IRQHandler(&hdma_usart2_rx);
  /* USER CODE BEGIN DMA1_Channel4_5_6_7_IRQn 1 */

  /* USER CODE END DMA1_Channel4_5_6_7_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global interrupt and DAC1/DAC2 underrun error interrupts.
  */
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */

  /* USER CODE END TIM6_DAC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
  * @brief This function handles I2C1 event global interrupt / I2C1 wake-up interrupt through EXTI line 23.
  */
void I2C1_IRQHandler(void)
{
  /* USER CODE BEGIN I2C1_IRQn 0 */

  /* USER CODE END I2C1_IRQn 0 */
  if (hi2c1.Instance->ISR & (I2C_FLAG_BERR | I2C_FLAG_ARLO | I2C_FLAG_OVR)) {
    HAL_I2C_ER_IRQHandler(&hi2c1);
  } else {
    HAL_I2C_EV_IRQHandler(&hi2c1);
  }
  /* USER CODE BEGIN I2C1_IRQn 1 */

  /* USER CODE END I2C1_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt / USART1 wake-up interrupt through EXTI line 25.
  */
void USART1_IRQHandler(void)
{
    /* USER CODE BEGIN USART1_IRQn 0 */

    if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET)
    {
        __HAL_UART_CLEAR_IDLEFLAG(&huart1);
        HAL_UART_DMAStop(&huart1);
//        HAL_GPIO_TogglePin(GPIOA, SYSTEM_LED_Pin);
        HAL_UART_Receive_DMA(&huart1, USART1_ReceiveDef.Receive_pData, RECEIVE_LEN);
    }
    /* USER CODE END USART1_IRQn 0 */
    HAL_UART_IRQHandler(&huart1);
    /* USER CODE BEGIN USART1_IRQn 1 */

    /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt / USART2 wake-up interrupt through EXTI line 26.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
    uint32_t Counter = 0;

    if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_IDLE) != RESET)
    {
        __HAL_UART_CLEAR_IDLEFLAG(&huart2);
        HAL_UART_DMAStop(&huart2);
        Counter = __HAL_DMA_GET_COUNTER(&hdma_usart2_rx);
        USART2_ReceiveDef.Receive_LEN = RECEIVE_LEN - Counter;
        if (USART2_ReceiveDef.Receive_LEN > 0)
        {
            /*  红外测距接收数据处理 (GY-56)Infrared ranging receiving data processing */
            if ((USART2_ReceiveDef.Receive_pData[0] == 0x5A)
                && (USART2_ReceiveDef.Receive_pData[1] == 0x5A)
                && (USART2_ReceiveDef.Receive_pData[2] == 0x15)
                && (USART2_ReceiveDef.Receive_pData[3] == 0x04)
                && ((uint8_t) ((USART2_ReceiveDef.Receive_pData[0]
                + USART2_ReceiveDef.Receive_pData[1]
                + USART2_ReceiveDef.Receive_pData[2]
                + USART2_ReceiveDef.Receive_pData[3]
                + USART2_ReceiveDef.Receive_pData[4]
                + USART2_ReceiveDef.Receive_pData[5]
                + USART2_ReceiveDef.Receive_pData[6]
                + USART2_ReceiveDef.Receive_pData[7]))
                == USART2_ReceiveDef.Receive_pData[8])) {

                GY56_revDef.GY56_Flag = 1;

                memset(&GY56_revDef.GY56_pData, 0, sizeof(GY56_revDef.GY56_pData));
                GY56_revDef.GY56_LEN = USART2_ReceiveDef.Receive_LEN;
                memcpy(GY56_revDef.GY56_pData, USART2_ReceiveDef.Receive_pData, GY56_revDef.GY56_LEN);

            }

            /* 超声波测距接收数据处理 Ultrasonic ranging receiving data processing */
            if ((USART2_ReceiveDef.Receive_pData[0] == 0xFF)
                    && ((uint8_t)(USART2_ReceiveDef.Receive_pData[0] + USART2_ReceiveDef.Receive_pData[1]
                            + USART2_ReceiveDef.Receive_pData[2])
                            == USART2_ReceiveDef.Receive_pData[3])) {

                JSN_SR20_revDef.JSN_SR20_Flag = 1;

                memset(&JSN_SR20_revDef.JSN_SR20_pData, 0, sizeof(JSN_SR20_revDef.JSN_SR20_pData));
                JSN_SR20_revDef.JSN_SR20_LEN = USART2_ReceiveDef.Receive_LEN;

                memcpy(JSN_SR20_revDef.JSN_SR20_pData, USART2_ReceiveDef.Receive_pData, JSN_SR20_revDef.JSN_SR20_LEN);

            }

            /* 光照强度接收数据处理 Light intensity receiving data processing */
            if ((USART2_ReceiveDef.Receive_pData[0] == 0x4C)
                    && (USART2_ReceiveDef.Receive_pData[1] == 0x3A)
                    && (USART2_ReceiveDef.Receive_pData[USART2_ReceiveDef.Receive_LEN - 1] == 0x0A)
                    && (USART2_ReceiveDef.Receive_pData[USART2_ReceiveDef.Receive_LEN - 2] == 0x0D)) {

                GY301_revDef.GY301_Flag = 1;

                memset(&GY301_revDef.GY301_pData, 0, sizeof(GY301_revDef.GY301_pData));
                GY301_revDef.GY301_LEN = USART2_ReceiveDef.Receive_LEN;
                memcpy(GY301_revDef.GY301_pData, USART2_ReceiveDef.Receive_pData, GY301_revDef.GY301_LEN);

            }

            /*  红外测距接收数据处理 (GY-53L1)Infrared ranging receiving data processing */
            if ((USART2_ReceiveDef.Receive_pData[0] == 0x5A)
                && (USART2_ReceiveDef.Receive_pData[1] == 0x5A)
                && (USART2_ReceiveDef.Receive_pData[2] == 0x15)
                && (USART2_ReceiveDef.Receive_pData[3] == 0x03)
                && ((uint8_t) ((USART2_ReceiveDef.Receive_pData[0]
                + USART2_ReceiveDef.Receive_pData[1]
                + USART2_ReceiveDef.Receive_pData[2]
                + USART2_ReceiveDef.Receive_pData[3]
                + USART2_ReceiveDef.Receive_pData[4]
                + USART2_ReceiveDef.Receive_pData[5]
                + USART2_ReceiveDef.Receive_pData[6]))
                == USART2_ReceiveDef.Receive_pData[7])) {

                GY53L1_revDef.GY53L1_Flag = 1;

                memset(&GY53L1_revDef.GY53L1_pData, 0, sizeof(GY53L1_revDef.GY53L1_pData));
                GY53L1_revDef.GY53L1_LEN = USART2_ReceiveDef.Receive_LEN;
                memcpy(GY53L1_revDef.GY53L1_pData, USART2_ReceiveDef.Receive_pData, GY53L1_revDef.GY53L1_LEN);

            }

        }
        for (uint8_t i = 0; i < PACKAGE_BUFFER_LEN; i++)
        {
            PackBuffer.channel_buffer[PackBuffer.counter_time][i] = USART2_ReceiveDef.Receive_pData[i];
        }
        PackBuffer.counter_time++;
        memset(&USART2_ReceiveDef.Receive_pData, 0, sizeof(USART2_ReceiveDef.Receive_pData));
        HAL_UART_Receive_DMA(&huart2, USART2_ReceiveDef.Receive_pData, RECEIVE_LEN);
    }
  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
