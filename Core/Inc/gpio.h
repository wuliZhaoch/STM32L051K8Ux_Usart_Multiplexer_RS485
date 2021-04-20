/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
typedef enum {
    Select_Address_x0 = 0x00,
    Select_Address_x1 = 0x01,
    Select_Address_x2 = 0x02,
    Select_Address_x3 = 0x03,
    Select_Address_x4 = 0x04,
    Select_Address_x5 = 0x05,
    Select_Address_x6 = 0x06,
    Select_Address_x7 = 0x07
} SGM4581_SelectInputTypeDef;

#define SELECT_INT_A_SET    HAL_GPIO_WritePin(SGM4581_Addr_A_GPIO_Port, SGM4581_Addr_A_Pin, GPIO_PIN_SET)
#define SELECT_INT_A_RESET  HAL_GPIO_WritePin(SGM4581_Addr_A_GPIO_Port, SGM4581_Addr_A_Pin, GPIO_PIN_RESET)

#define SELECT_INT_B_SET    HAL_GPIO_WritePin(SGM4581_Addr_B_GPIO_Port, SGM4581_Addr_B_Pin, GPIO_PIN_SET)
#define SELECT_INT_B_RESET  HAL_GPIO_WritePin(SGM4581_Addr_B_GPIO_Port, SGM4581_Addr_B_Pin, GPIO_PIN_RESET)

#define SELECT_INT_C_SET    HAL_GPIO_WritePin(SGM4581_Addr_C_GPIO_Port, SGM4581_Addr_C_Pin, GPIO_PIN_SET)
#define SELECT_INT_C_RESET  HAL_GPIO_WritePin(SGM4581_Addr_C_GPIO_Port, SGM4581_Addr_C_Pin, GPIO_PIN_RESET)

#define RS485_TRANSMIT_MODE     HAL_GPIO_WritePin(GPIOA, RS485_REDE_Pin, GPIO_PIN_SET)
#define RS485_RECEIVE_MODE      HAL_GPIO_WritePin(GPIOA, RS485_REDE_Pin, GPIO_PIN_RESET)

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
void SGM4581_Address_set(SGM4581_SelectInputTypeDef Addr_Flag);
void System_LED_Blink(uint16_t blinkCount, uint32_t period);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
