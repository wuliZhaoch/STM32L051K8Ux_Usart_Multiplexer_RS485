/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SGM4581_Addr_A_Pin GPIO_PIN_5
#define SGM4581_Addr_A_GPIO_Port GPIOA
#define SGM4581_Addr_B_Pin GPIO_PIN_6
#define SGM4581_Addr_B_GPIO_Port GPIOA
#define SGM4581_Addr_C_Pin GPIO_PIN_7
#define SGM4581_Addr_C_GPIO_Port GPIOA
#define Debug_GPIO1_Pin GPIO_PIN_1
#define Debug_GPIO1_GPIO_Port GPIOB
#define Debug_GPIO2_Pin GPIO_PIN_2
#define Debug_GPIO2_GPIO_Port GPIOB
#define RS485_TX_Pin GPIO_PIN_9
#define RS485_TX_GPIO_Port GPIOA
#define RS485_RX_Pin GPIO_PIN_10
#define RS485_RX_GPIO_Port GPIOA
#define RS485_REDE_Pin GPIO_PIN_12
#define RS485_REDE_GPIO_Port GPIOA
#define SYSTEM_LED_Pin GPIO_PIN_15
#define SYSTEM_LED_GPIO_Port GPIOA
#define Debug_GPIO3_Pin GPIO_PIN_3
#define Debug_GPIO3_GPIO_Port GPIOB
#define Debug_GPIO4_Pin GPIO_PIN_4
#define Debug_GPIO4_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
