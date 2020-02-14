/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"
#include "stm32g4xx_ll_pwr.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"
#include "WS2812.h"
#include "fdcan.h"
#include "SRF02.h"
#include "i2c.h"
#include "runtime.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

typedef union
{
	struct
	{
		uint8_t ID;
		uint8_t BUSV;
		uint8_t HST;
		uint8_t MSTS;
		uint8_t MPWR;
		uint16_t SPD;
		uint16_t FLUX;
		uint16_t TORQUE;
		uint16_t FAULT;
	};
	uint8_t array[13];
}ESC_FB;


struct
{
	uint8_t 	array[25];
	int16_t		CH1;			// Left Right
	int16_t		CH2;			// Forward Backward
	int16_t		CH5;			// Vacuum
	int16_t		CH6;			// Motor Arm/Disarm
	int16_t		CH7;			// LED Display
	int16_t 	CH8;			// ESC Fault Ack
}TXR_Buffer;

uint8_t BOOP;

uint8_t mode;
uint32_t LINE_ADC[3];
long unsigned int test;
uint8_t CAN_RX_Mailbox;
uint8_t CAN_RX_Buffer[4];
uint8_t CAN_TX_Buffer[10];
//uint8_t TXR_Buffer[25];
uint8_t RAMPD;
ESC_FB ESC_Left;
ESC_FB ESC_Right;
uint8_t LESC_Status;
uint8_t RESC_Status;
uint8_t TXR_Status;
FDCAN_RxHeaderTypeDef RX_Header;

uint8_t Motor_Armed;
uint8_t Vacuum_Armed;
uint8_t ACK_Toggle;
int16_t LeftMotorSpeed;
int16_t RightMotorSpeed;


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
#define BUTTON1_Pin GPIO_PIN_4
#define BUTTON1_GPIO_Port GPIOB
#define BUTTON2_Pin GPIO_PIN_5
#define BUTTON2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
