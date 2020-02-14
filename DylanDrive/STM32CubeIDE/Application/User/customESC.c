#include "main.h"
#include "customESC.h"

extern UART_HandleTypeDef huart2;

// ===== Command to Read from Flash Storage to custom ESC Register =====
void ESC_Read_Flash()
{
	int counter;
	for(counter = 0; counter < 12; counter++)
	{
		ESCRegister.FlashData32[counter] = *(uint32_t*)(ESC_FLASH_ADDRESS + (counter*4));
	}
}

/* ===== Command to Write custom ESC Register to Flash Storage =====
 *
 * Each command will be executed a maximum of 3 times on failure.
 * If error persist, function will return error.
 *
 * retval		Return true on successful write
 * 				Return false on error
 *
 */
bool ESC_Write_Flash()
{
	int attempt_count, counter;
	uint8_t motor_status;
	HAL_StatusTypeDef status;
	uint32_t PageError;
	FLASH_EraseInitTypeDef hFlashErase;

	motor_status = ESCRegister.MSTS;
	if(motor_status == RUN) { MotorStop; HAL_Delay(2000); }

	// Initialize flash erase handler
	hFlashErase.TypeErase = FLASH_TYPEERASE_PAGES;
	hFlashErase.Banks = FLASH_BANK_1;
	hFlashErase.Page = 62;
	hFlashErase.NbPages = 2;

	// Unlock the Flash memory to allow Write operation
	for(attempt_count = 0; attempt_count < 3; attempt_count++)
	{
		status = HAL_FLASH_Unlock();
		if(status == HAL_OK) break;
		if(attempt_count == 2) return false;
		HAL_Delay(1);
	}

	// Erase the Flash Section, a requirement for writing to flash
	for(attempt_count = 0; attempt_count < 3; attempt_count++)
	{
		status = HAL_FLASHEx_Erase(&hFlashErase, &PageError);
		if(status == HAL_OK) break;
		if(attempt_count == 2) return false;
		HAL_Delay(1);
	}

	// Write the ESC register to Flash
	for(counter = 0; counter < 6; counter++)
	{
		for(attempt_count = 0; attempt_count < 3; attempt_count++)
		{
			status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, (ESC_FLASH_ADDRESS + (counter*8)), ESCRegister.FlashData64[counter]);
			if(status == HAL_OK) break;
			if(attempt_count == 2) return false;
			HAL_Delay(1);
		}
	}

	// Lock the flash after writing to prevent stray writes
	for(attempt_count = 0; attempt_count < 3; attempt_count++)
	{
		status = HAL_FLASH_Lock();
		if(status == HAL_OK) break;
		if(attempt_count == 2) return false;
	}

	if(motor_status == RUN) MotorStart;

	return true;
}

void ESC_UART_Init()
{
	// De-initialize UART to stop all comms
	HAL_UART_DeInit(&huart2);

	// Initialize UART for comms with control board
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
	Error_Handler();
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
	Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
	Error_Handler();
	}
	if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
	{
	Error_Handler();
	}
	HAL_NVIC_DisableIRQ(USART2_IRQn);

}

void ESC_UART_TX_Feedback()
{
	int array_data_counter = 0;

	uint8_t DataBuffer[20] = {0};

	DataBuffer[array_data_counter] = ESCRegister.CON.ESC_ID;
	array_data_counter++;

	if(ESCRegister.UDFE.BusVoltage == 1)
	{
		DataBuffer[array_data_counter] = ESCRegister.BUSV;
		array_data_counter++;
	}

	if(ESCRegister.UDFE.HeatsinkTemperature == 1)
	{
		DataBuffer[array_data_counter] = ESCRegister.HST;
		array_data_counter++;
	}

	if(ESCRegister.UDFE.MotorStatus == 1)
	{
		DataBuffer[array_data_counter] = ESCRegister.MSTS;
		array_data_counter++;
	}

	if(ESCRegister.UDFE.MotorPower == 1)
	{
		DataBuffer[array_data_counter] = ESCRegister.MPWR;
		array_data_counter++;
	}

	if(ESCRegister.UDFE.SpeedMeasured == 1)
	{
		DataBuffer[array_data_counter] = ESCRegister.SPD & 0xFF;
		DataBuffer[array_data_counter + 1] = ESCRegister.SPD >> 8;
		array_data_counter += 2;
	}

	if(ESCRegister.UDFE.FluxCurrentMeasured == 1)
	{
		DataBuffer[array_data_counter] = ESCRegister.IDM & 0xFF;
		DataBuffer[array_data_counter + 1] = ESCRegister.IDM >> 8;
		array_data_counter += 2;
	}

	if(ESCRegister.UDFE.TorqueCurrentMeasured == 1)
	{
		DataBuffer[array_data_counter] = ESCRegister.IQM & 0xFF;
		DataBuffer[array_data_counter + 1] = ESCRegister.IQM >> 8;
		array_data_counter += 2;
	}

	if(ESCRegister.UDFE.TorqueCurrentMeasured == 1)
	{
		DataBuffer[array_data_counter] = ESCRegister.FLT.Now.data;
		DataBuffer[array_data_counter + 1] = ESCRegister.FLT.Occurred.data;
		array_data_counter += 2;
	}

	HAL_UART_Transmit_DMA(&huart2, DataBuffer, array_data_counter);
}

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
	hfdcan1filter.FilterID1 = ESCRegister.CON.ESC_ID;		// Set ID of packets to filter
	hfdcan1filter.FilterID2 = 0x00F;						// Compare all 11 ID bits

	if(HAL_FDCAN_ConfigFilter(hfdcan, &hfdcan1filter) != HAL_OK) return HAL_ERROR;

	hfdcan1filter.FilterIndex = 1;							// Set to Filter bank 1
	hfdcan1filter.FilterID1 = 0x0F;							// Set ID of packets to filter
	return HAL_FDCAN_ConfigFilter(hfdcan, &hfdcan1filter);
}

void CAN_TX_Init_Data(uint8_t reg, uint8_t arg0, uint8_t arg1, uint8_t * pdata)
{
	pdata[0] = ESCRegister.CON.ESC_ID;
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
HAL_StatusTypeDef FDCAN1_TX(FDCAN_HandleTypeDef *hfdcan, uint8_t *data)
{
	FDCAN_TxHeaderTypeDef TXHeader;
	TXHeader.IdType = FDCAN_STANDARD_ID;
	TXHeader.Identifier = 0;
	TXHeader.TxFrameType = FDCAN_DATA_FRAME;
	TXHeader.DataLength = FDCAN_DLC_BYTES_4;
	TXHeader.FDFormat = FDCAN_CLASSIC_CAN;
	TXHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;

	return HAL_FDCAN_AddMessageToTxFifoQ(hfdcan, &TXHeader, data);
}

bool ESCReg_Read(uint8_t reg, uint8_t * data0, uint8_t * data1)
{
	if(reg >= 0x30) return false;						// Validate Register value
	if(reg < 0x08 && reg != 0x02 && reg != 0x03)		// If register is 1 byte long
	{
		*data0 = 0;
		*data1 = ESCRegister.Register[reg];
	}
	else												// If register is 2 bytes long
	{
		*data0 = ESCRegister.Register[reg + 1];
		*data1 = ESCRegister.Register[reg];
	}
	return true;
}

bool ESCReg_Write(uint8_t reg, uint8_t data0, uint8_t data1)
{
	if(reg >= 0x30) return false;						// Validate Register value
	if(reg < 0x08 && reg != 0x02 && reg != 0x03)		// If register is 1 byte long
	{
		if(reg == 0) ESCRegister.Register[reg] = (ESCRegister.Register[reg] & 0xF0) + (data1 & 0x0F);
		ESCRegister.Register[reg] = data1;

	}
	else												// If register is 2 bytes long
	{
		ESCRegister.Register[reg + 1] = data0;
		ESCRegister.Register[reg] = data1;
	}

	ESCRegister_Update_Action(reg);

	return true;
}

void ESCRegister_Update_Action(uint8_t reg)
{
	switch(reg)
	{
		case CON_REG_ADDR:
			{
				/* Check for Register Reset*/
				if(ESCRegister.CON.RegisterReset == 1) ESCReg_Init();

				/* StartStop the Motor */
				if(ESCRegister.CON.MotorEnable == 0) MotorStop;
				else MotorStart;

				/* Configure Motor Mode */
				if(ESCRegister.CON.MotorMode == SPEED_MODE)
					MC_ProgramSpeedRampMotor1((ESCRegister.RAMPS/6), ESCRegister.RAMPD);
				else
					MC_ProgramTorqueRampMotor1( ESCRegister.IDS, ESCRegister.RAMPD);


			}
			break;

		case MAXSPD_REG_ADDR:
			// Do nothing for now
			break;

		case RAMPD_REG_ADDR:
			if(ESCRegister.CON.MotorMode == SPEED_MODE)
				MC_ProgramSpeedRampMotor1((ESCRegister.RAMPS/6), ESCRegister.RAMPD);
			else
				MC_ProgramTorqueRampMotor1( ESCRegister.IDS, ESCRegister.RAMPD);
			break;

		case RAMPS_REG_ADDR:
			MC_ProgramSpeedRampMotor1((ESCRegister.RAMPS/6), ESCRegister.RAMPD);
			break;

		case SPDPG_REG_ADDR:
			PID_SetKP(MCT_HANDLER->pPIDSpeed, ESCRegister.SPDPG);
			break;

		case SPDIG_REG_ADDR:
			PID_SetKI(MCT_HANDLER->pPIDSpeed, ESCRegister.SPDIG);
			break;

		case SPDDG_REG_ADDR:
			PID_SetKD(MCT_HANDLER->pPIDSpeed, ESCRegister.SPDDG);
			break;

		case IDS_REG_ADDR:
			{
				qd_t currComp;
				currComp.d = ESCRegister.IDS;
				currComp.q = ESCRegister.IQS;
				MCI_SetCurrentReferences(MCI_HANDLER, currComp);
			}
			break;

		case IDPG_REG_ADDR:
			PID_SetKP(MCT_HANDLER->pPIDId, ESCRegister.IDPG);
			break;

		case IDIG_REG_ADDR:
			PID_SetKI(MCT_HANDLER->pPIDId, ESCRegister.IDIG);
			break;

		case IDDG_REG_ADDR:
			PID_SetKD(MCT_HANDLER->pPIDId, ESCRegister.IDDG);
			break;

		case IQS_REG_ADDR:
			{
				qd_t currComp;
				currComp.d = ESCRegister.IDS;
				currComp.q = ESCRegister.IQS;
				MCI_SetCurrentReferences(MCI_HANDLER, currComp);
			}
			break;

		case IQPG_REG_ADDR:
			PID_SetKD(MCT_HANDLER->pPIDIq, ESCRegister.IQPG);
			break;

		case IQIG_REG_ADDR:
			PID_SetKD(MCT_HANDLER->pPIDIq, ESCRegister.IQIG);
			break;

		case IQDG_REG_ADDR:
			PID_SetKD(MCT_HANDLER->pPIDIq, ESCRegister.IQDG);
			break;

		case FLT_REG_ADDR:
			if(ESCRegister.FLT.data == 0) MC_AcknowledgeFaultMotor1();
			break;

		default:
			break;
	}
}

bool ESCReg_Refreshed()
{
	int counter;
	for(counter = 0; counter < 12; counter++)
		if(ESCRegister.FlashData32[counter] != 0xFFFFFFFF) return false;
	return true;
}

/* ===== Command to initialize custom ESC Register =====
 *
 */
void ESCReg_Init()
{
	ESCRegister.UDFE.data = 0xFF;
	ESCRegister.UDFI = 200;
	ESCRegister.FLTMSK.data = 0x0B0B;
	ESCRegister.SPDPG = 30000;
	ESCRegister.SPDIG = 2000;
	ESCRegister.SPDDG = 75;
}

void ESCReg_Clear()
{
	int counter;
	for(counter = 0; counter < 6; counter++) ESCRegister.FlashData64[counter] = 0;
}

void ESCReg_UpdateCycle()
{
	ESCRegister.BUSV 	= VBS_GetAvBusVoltage_V(MCT_HANDLER->pBusVoltageSensor) & 0xFF;
	ESCRegister.HST 	= NTC_GetAvTemp_C(MCT_HANDLER->pTemperatureSensor) & 0xFF;
	ESCRegister.MSTS 	= MCT_HANDLER->pStateMachine->bState;
	ESCRegister.MPWR 	= MCT_HANDLER->pMPM->hAvrgElMotorPowerW;
	ESCRegister.SPD 	= MCI_HANDLER->pSTC->SPD->hAvrMecSpeedUnit * 6;
	ESCRegister.MAXSPD 	= MCT_HANDLER->pSpeednTorqueCtrl->MaxAppPositiveMecSpeedUnit*6;
	ESCRegister.RAMPD 	= MCI_HANDLER->hDurationms;
	ESCRegister.RAMPS 	= MCI_HANDLER->hFinalSpeed * 6;
	ESCRegister.SPDPG 	= MCT_HANDLER->pPIDSpeed->hKpGain;
	ESCRegister.SPDIG 	= MCT_HANDLER->pPIDSpeed->hKiGain;
	ESCRegister.SPDDG 	= MCT_HANDLER->pPIDSpeed->hKdGain;
	ESCRegister.IDS		= MCI_HANDLER->pFOCVars->Iqdref.d;
	ESCRegister.IDM		= MCI_HANDLER->pFOCVars->Iqd.d;
	ESCRegister.IDPG	= MCT_HANDLER->pPIDId->hKpGain;
	ESCRegister.IDIG	= MCT_HANDLER->pPIDId->hKiGain;
	ESCRegister.IDDG	= MCT_HANDLER->pPIDId->hKdGain;
	ESCRegister.IQS		= MCI_HANDLER->pFOCVars->Iqdref.q;
	ESCRegister.IQM		= MCI_HANDLER->pFOCVars->Iqd.q;
	ESCRegister.IQPG	= MCT_HANDLER->pPIDIq->hKpGain;
	ESCRegister.IQIG	= MCT_HANDLER->pPIDIq->hKiGain;
	ESCRegister.IQDG	= MCT_HANDLER->pPIDIq->hKdGain;
	ESCRegister.FLT.Now.data		= MCI_HANDLER->pSTM->hFaultNow;
	ESCRegister.FLT.Occurred.data	= MCI_HANDLER->pSTM->hFaultOccurred;
}

bool validata(uint8_t * data1, uint8_t * data2, int size)
{
	int counter;
	for(counter = 0; counter < size; counter++)
	{
		if(data1[counter] != data2[counter]) return false;
	}
	return true;
}
