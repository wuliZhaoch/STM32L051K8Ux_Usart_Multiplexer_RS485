/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);

/* USER CODE BEGIN Prototypes */
#define RECEIVE_LEN         255
#define SR20_RECEIVE_LEN    4
#define GY53L1_RECEIVE_LEN  8
#define GY56_RECEIVE_LEN    8
#define GY301_RECEIVE_LEN   11

typedef struct {
    uint8_t     Receive_Flag:1;     // IDLE Receive Flag
    uint16_t    Receive_LEN;        // Receive Length
    uint8_t     Receive_pData[RECEIVE_LEN];
}Usart_ReceiveTypeDef;


typedef struct {
    uint8_t     JSN_SR20_LEN;
    uint8_t     JSN_SR20_pData[SR20_RECEIVE_LEN];
}JSN_SR20ReceiveTypeDef;

typedef struct {
    uint8_t     GY53L1_LEN;
    uint8_t     GY53L1_pData[GY53L1_RECEIVE_LEN];
}GY53L1_ReceiveTypeDef;

typedef struct {
    uint8_t     GY56_LEN;
    uint8_t     GY56_pData[GY56_RECEIVE_LEN];
}GY56_ReceiveTypeDef;

typedef struct {
    uint8_t     GY301_LEN;
    uint8_t     GY301_pData[GY301_RECEIVE_LEN];
}GY301_ReceiveTypeDef;



extern Usart_ReceiveTypeDef USART1_ReceiveDef;
extern Usart_ReceiveTypeDef USART2_ReceiveDef;

extern JSN_SR20ReceiveTypeDef JSN_SR20_revDef;
extern GY301_ReceiveTypeDef GY301_revDef;
extern GY53L1_ReceiveTypeDef GY53L1_revDef;
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
