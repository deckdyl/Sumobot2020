/**
  ******************************************************************************
  * File Name          : FDCAN.h
  * Description        : This file provides code for the configuration
  *                      of the FDCAN instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#ifndef __fdcan_H
#define __fdcan_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern FDCAN_HandleTypeDef hfdcan1;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_FDCAN1_Init(void);

/* USER CODE BEGIN Prototypes */
HAL_StatusTypeDef FDCAN1_RX_Filter_Init(FDCAN_HandleTypeDef * hfdcan);
HAL_StatusTypeDef FDCAN1_TX(FDCAN_HandleTypeDef *hfdcan, uint8_t *data, uint16_t ESC_ID);
void CAN_TX_Init_Data(uint8_t reg, uint8_t arg0, uint8_t arg1, uint8_t * pdata);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ fdcan_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
