/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/**
  * @brief  SGM4581 Address Select.
  * @param  Addr_Flag Address Flag Select
  * @retval None
  */
void SGM4581_Address_set(SGM4581_SelectInputTypeDef Addr_Flag)
{
    switch(Addr_Flag)
    {
    case Select_Address_x0:
        SELECT_INT_A_RESET;
        SELECT_INT_B_RESET;
        SELECT_INT_C_RESET;
        break;
    case Select_Address_x1:
        SELECT_INT_A_SET;
        SELECT_INT_B_RESET;
        SELECT_INT_C_RESET;
        break;
    case Select_Address_x2:
        SELECT_INT_A_RESET;
        SELECT_INT_B_SET;
        SELECT_INT_C_RESET;
        break;
    case Select_Address_x3:
        SELECT_INT_A_SET;
        SELECT_INT_B_SET;
        SELECT_INT_C_RESET;
        break;
    case Select_Address_x4:
        SELECT_INT_A_RESET;
        SELECT_INT_B_RESET;
        SELECT_INT_C_SET;
        break;
    case Select_Address_x5:
        SELECT_INT_A_SET;
        SELECT_INT_B_RESET;
        SELECT_INT_C_SET;
        break;
    case Select_Address_x6:
        SELECT_INT_A_RESET;
        SELECT_INT_B_SET;
        SELECT_INT_C_SET;
        break;
    case Select_Address_x7:
        SELECT_INT_A_SET;
        SELECT_INT_B_SET;
        SELECT_INT_C_SET;
        break;
//    default:
//        SELECT_INT_A_RESET;
//        SELECT_INT_B_RESET;
//        SELECT_INT_C_RESET;
//        break;
    }

}

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SGM4581_Addr_A_Pin|SGM4581_Addr_B_Pin|SGM4581_Addr_C_Pin|SYSTEM_LED_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, SYSTEM_LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Debug_GPIO1_Pin|Debug_GPIO2_Pin|Debug_GPIO3_Pin|Debug_GPIO4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = SGM4581_Addr_A_Pin|SGM4581_Addr_B_Pin|SGM4581_Addr_C_Pin|SYSTEM_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = Debug_GPIO1_Pin|Debug_GPIO2_Pin|Debug_GPIO3_Pin|Debug_GPIO4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = RS485_REDE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOA, RS485_REDE_Pin, GPIO_PIN_RESET);

}

/* USER CODE BEGIN 2 */
void System_LED_Blink(uint16_t blinkCount, uint32_t period)
{
    for (int i = 0; i < blinkCount; i++)
    {
        HAL_GPIO_TogglePin(SYSTEM_LED_GPIO_Port, SYSTEM_LED_Pin);
        HAL_Delay(period);
    }
    HAL_GPIO_WritePin(SYSTEM_LED_GPIO_Port, SYSTEM_LED_Pin, GPIO_PIN_SET);
}
/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
