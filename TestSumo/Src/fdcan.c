/**
  ******************************************************************************
  * File Name          : FDCAN.c
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

/* Includes ------------------------------------------------------------------*/
#include "fdcan.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

FDCAN_HandleTypeDef hfdcan1;

/* FDCAN1 init function */
void MX_FDCAN1_Init(void)
{

  hfdcan1.Instance = FDCAN1;
  hfdcan1.Init.ClockDivider = FDCAN_CLOCK_DIV1;
  hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
  hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan1.Init.AutoRetransmission = DISABLE;
  hfdcan1.Init.TransmitPause = DISABLE;
  hfdcan1.Init.ProtocolException = DISABLE;
  hfdcan1.Init.NominalPrescaler = 85;
  hfdcan1.Init.NominalSyncJumpWidth = 1;
  hfdcan1.Init.NominalTimeSeg1 = 13;
  hfdcan1.Init.NominalTimeSeg2 = 2;
  hfdcan1.Init.DataPrescaler = 10;
  hfdcan1.Init.DataSyncJumpWidth = 1;
  hfdcan1.Init.DataTimeSeg1 = 13;
  hfdcan1.Init.DataTimeSeg2 = 2;
  hfdcan1.Init.StdFiltersNbr = 2;
  hfdcan1.Init.ExtFiltersNbr = 0;
  hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef* fdcanHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(fdcanHandle->Instance==FDCAN1)
  {
  /* USER CODE BEGIN FDCAN1_MspInit 0 */

  /* USER CODE END FDCAN1_MspInit 0 */
    /* FDCAN1 clock enable */
    __HAL_RCC_FDCAN_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**FDCAN1 GPIO Configuration    
    PA11     ------> FDCAN1_RX
    PA12     ------> FDCAN1_TX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* FDCAN1 interrupt Init */
    HAL_NVIC_SetPriority(FDCAN1_IT1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(FDCAN1_IT1_IRQn);
  /* USER CODE BEGIN FDCAN1_MspInit 1 */
    FDCAN1->ILE = 2;
    FDCAN1->ILS = 1;
    FDCAN1->IE = 1;
  /* USER CODE END FDCAN1_MspInit 1 */
  }
}

void HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef* fdcanHandle)
{

  if(fdcanHandle->Instance==FDCAN1)
  {
  /* USER CODE BEGIN FDCAN1_MspDeInit 0 */

  /* USER CODE END FDCAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_FDCAN_CLK_DISABLE();
  
    /**FDCAN1 GPIO Configuration    
    PA11     ------> FDCAN1_RX
    PA12     ------> FDCAN1_TX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* FDCAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(FDCAN1_IT1_IRQn);
  /* USER CODE BEGIN FDCAN1_MspDeInit 1 */

  /* USER CODE END FDCAN1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
/* ===== Command to initialize FDCAN RX Filter =====
 *
 */
HAL_StatusTypeDef FDCAN1_RX_Filter_Init(FDCAN_HandleTypeDef * hfdcan)
{
	FDCAN_FilterTypeDef hfdcan1filter;

	hfdcan1filter.IdType = FDCAN_STANDARD_ID;				// Use standard 11 bit ID
	hfdcan1filter.FilterType = FDCAN_FILTER_MASK;			// Use filter ID and Mask
	hfdcan1filter.FilterIndex = 0;							// Set to Filter bank 0
	hfdcan1filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;	// Filter matching packets to FIFO0
	hfdcan1filter.FilterID1 = 0x00;							// Set ID of packets to filter
	hfdcan1filter.FilterID2 = 0x0FF;						// Compare all 11 ID bits

	HAL_FDCAN_ConfigGlobalFilter(hfdcan, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_REJECT_REMOTE);

	return HAL_FDCAN_ConfigFilter(hfdcan, &hfdcan1filter);
}

void CAN_TX_Init_Data(uint8_t reg, uint8_t arg0, uint8_t arg1, uint8_t * pdata)
{
	pdata[0] = 0;
	pdata[1] = reg;
	pdata[2] = arg0;
	pdata[3] = arg1;
}

/* ===== Command to Transmit data over CAN bus =====
 *
 *
 *
 * retval		HAL_OK
 * 				Return false on error
 *
 */
HAL_StatusTypeDef FDCAN1_TX(FDCAN_HandleTypeDef *hfdcan, uint8_t *data, uint16_t ESC_ID)
{
	FDCAN_TxHeaderTypeDef TXHeader;
	TXHeader.IdType = FDCAN_STANDARD_ID;
	TXHeader.Identifier = ESC_ID & 0x00F;
	TXHeader.TxFrameType = FDCAN_DATA_FRAME;
	TXHeader.DataLength = FDCAN_DLC_BYTES_4;
	TXHeader.FDFormat = FDCAN_CLASSIC_CAN;
	TXHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;

	return HAL_FDCAN_AddMessageToTxFifoQ(hfdcan, &TXHeader, data);
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
