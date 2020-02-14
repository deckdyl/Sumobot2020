#include "runtime.h"

extern FDCAN_HandleTypeDef hfdcan1;

void Calculate_TXR_Channel()
{
	TXR_Buffer.CH1 = ((TXR_Buffer.array[2] << 8) + TXR_Buffer.array[1]) & 0x07FF;
	TXR_Buffer.CH2 = ((TXR_Buffer.array[3] << 5) + (TXR_Buffer.array[2] >> 3)) & 0x07FF;
	TXR_Buffer.CH5 = ((TXR_Buffer.array[7] << 4) + (TXR_Buffer.array[6] >> 4)) & 0x07FF;
	TXR_Buffer.CH6 = ((TXR_Buffer.array[9] << 9)
		  + (TXR_Buffer.array[8] << 1)
		  + (TXR_Buffer.array[7] >> 7)) & 0x07FF;
	TXR_Buffer.CH7 = ((TXR_Buffer.array[10] << 6) + (TXR_Buffer.array[9] >> 2)) & 0x07FF;
	TXR_Buffer.CH8 = ((TXR_Buffer.array[11] << 3) + (TXR_Buffer.array[10] >> 5)) & 0x07FF;
}

void Resolve_CAN_RX_Mailbox()
{
	HAL_FDCAN_GetRxMessage(&hfdcan1, FDCAN_RX_FIFO0, &RX_Header, CAN_RX_Buffer);
	CAN_RX_Mailbox--;
	if(CAN_RX_Buffer[1] == 0)
	{
		CAN_TX_Init_Data(255, 255, 255, CAN_TX_Buffer);
		FDCAN1_TX(&hfdcan1, CAN_TX_Buffer, CAN_RX_Buffer[0]);
		if(CAN_RX_Buffer[0] == 5) LESC_Status = 2;
		if(CAN_RX_Buffer[0] == 4) RESC_Status = 2;
	}
}

void Calculate_Motor_Speed()
{
	TXR_Buffer.CH2 -= 0x3DE;
	if(TXR_Buffer.CH2 < 25 && TXR_Buffer.CH2 > -25)
	{
		LeftMotorSpeed = 0;
		RightMotorSpeed = 0;
	}
	else
	{
		LeftMotorSpeed = TXR_Buffer.CH2 * SPEED_MODIFIER;
		RightMotorSpeed = TXR_Buffer.CH2 * SPEED_MODIFIER;
	}

	TXR_Buffer.CH1 -= 0x3DE;
	if(TXR_Buffer.CH1 > 25)
	{
		LeftMotorSpeed += (TXR_Buffer.CH1*SPEED_MODIFIER);
		RightMotorSpeed -= (TXR_Buffer.CH1*SPEED_MODIFIER);
		if(LeftMotorSpeed > (MAX_SPEED+2000)) LeftMotorSpeed = (MAX_SPEED+2000);
		if(RightMotorSpeed < (-MAX_SPEED-2000)) RightMotorSpeed = (-MAX_SPEED - 2000);
	}
	if(TXR_Buffer.CH1 < -25)
	{
		LeftMotorSpeed += (TXR_Buffer.CH1*SPEED_MODIFIER);
		RightMotorSpeed -= (TXR_Buffer.CH1*SPEED_MODIFIER);
		if(LeftMotorSpeed < (-MAX_SPEED - 2000)) LeftMotorSpeed = (-MAX_SPEED - 2000);
		if(RightMotorSpeed > (MAX_SPEED+2000)) RightMotorSpeed = (MAX_SPEED+2000);
	}

	if(LeftMotorSpeed != 0) LeftMotorSpeed *= -1;
}

void Update_Motor_Speed()
{
	FDCAN_TxHeaderTypeDef TXHeader;
	TXHeader.IdType = FDCAN_STANDARD_ID;
	TXHeader.Identifier = 0xF;
	TXHeader.TxFrameType = FDCAN_DATA_FRAME;
	TXHeader.DataLength = FDCAN_DLC_BYTES_6;
	TXHeader.FDFormat = FDCAN_CLASSIC_CAN;
	TXHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;



	CAN_TX_Buffer[0] = 0;
	CAN_TX_Buffer[1] = 0x0E;
	CAN_TX_Buffer[2] = LeftMotorSpeed >> 8;
	CAN_TX_Buffer[3] = LeftMotorSpeed & 0xFF;
	CAN_TX_Buffer[4] = RightMotorSpeed >> 8;
	CAN_TX_Buffer[5] = RightMotorSpeed & 0xFF;
	HAL_Delay(10);
	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TXHeader, CAN_TX_Buffer);



/*
	if(RESC_Status == 2)
	{
		// Set Ramp Speed
		HAL_Delay(10);
		CAN_TX_Init_Data(0x0E, (RightMotorSpeed >> 8), RightMotorSpeed, CAN_TX_Buffer);
		FDCAN1_TX(&hfdcan1, CAN_TX_Buffer, 4);
	}

	if(LESC_Status == 2)
	{
		// Set Ramp Speed
		if(LeftMotorSpeed != 0) LeftMotorSpeed *= -1;
		HAL_Delay(10);
		CAN_TX_Init_Data(0x0E, (LeftMotorSpeed >> 8), LeftMotorSpeed, CAN_TX_Buffer);
		FDCAN1_TX(&hfdcan1, CAN_TX_Buffer, 5);
	}*/
}

void Motor_Arm()
{
	Motor_Armed = 1;

	// Set Ramp Speed to 200
	HAL_Delay(50);
	RightMotorSpeed = 200;
	LeftMotorSpeed = 200;
	Update_Motor_Speed();

	// Set Ramp time (Default 50ms)
	HAL_Delay(50);
	CAN_TX_Init_Data(0x0C, 0x00, RAMPD, CAN_TX_Buffer);
	FDCAN1_TX(&hfdcan1, CAN_TX_Buffer, 0x0F);

	// Start Motor
	HAL_Delay(50);
	CAN_TX_Init_Data(0x00, 0x00, 0x01, CAN_TX_Buffer);
	FDCAN1_TX(&hfdcan1, CAN_TX_Buffer, 0x0F);

	// Set Speed to 0;
	HAL_Delay(20);
	RightMotorSpeed = 0;
	LeftMotorSpeed = 0;
	Update_Motor_Speed();
}

void Motor_Disarm()
{
	// Stop Motor
	Motor_Armed = 0;
	HAL_Delay(20);
	CAN_TX_Init_Data(0x00, 0x00, 0x00, CAN_TX_Buffer);
	FDCAN1_TX(&hfdcan1, CAN_TX_Buffer, 0x0F);
	HAL_Delay(50);
	FDCAN1_TX(&hfdcan1, CAN_TX_Buffer, 0x0F);
}

void Vacuum_Toggle_Check()
{
	if(TXR_Buffer.CH5 < 500 && Vacuum_Armed == 1)
	{
		Vacuum_Armed = 0;
		TIM1->CCR1 = 1000;
	}
	else if(TXR_Buffer.CH5 > 500 && Vacuum_Armed == 0)
	{
		Vacuum_Armed = 1;
		TIM1->CCR1 = 2000;
	}
}

void ACK_Toggle_Check()
{
	if(ACK_Toggle == 0 && TXR_Buffer.CH8 > 500) ACK_Toggle = 1;
	else if(ACK_Toggle == 1 && TXR_Buffer.CH8 < 500)
	{
		ACK_Toggle = 0;
		CAN_TX_Init_Data(0x2A, 0x00, 0x00, CAN_TX_Buffer);
		FDCAN1_TX(&hfdcan1, CAN_TX_Buffer, 0x0F);

		if(Motor_Armed == 1)
		{
			// Start Motor
			HAL_Delay(20);
			CAN_TX_Init_Data(0x00, 0x00, 0x01, CAN_TX_Buffer);
			FDCAN1_TX(&hfdcan1, CAN_TX_Buffer, 0x0F);

			// Set Speed to 0;
			HAL_Delay(20);
			CAN_TX_Init_Data(0x0E, 0x00, 0x00, CAN_TX_Buffer);
			FDCAN1_TX(&hfdcan1, CAN_TX_Buffer, 0x0F);
		}

		else
		{
			// Stop Motor
			Motor_Armed = 0;
			HAL_Delay(20);
			CAN_TX_Init_Data(0x00, 0x00, 0x00, CAN_TX_Buffer);
			FDCAN1_TX(&hfdcan1, CAN_TX_Buffer, 0x0F);
		}
	}
}

void ADC_Calibration_Mode()
{

}

void Remote_Control_Mode()
{
	/* Check for any CAN Messages */
	if(CAN_RX_Mailbox > 0) Resolve_CAN_RX_Mailbox();

	// Calculate Channel Value;
	Calculate_TXR_Channel();

	// Update LEDs
	WS2812_Update();
	WS2812_Load();

	// Check for CH5 to On/Off Vacuum
	Vacuum_Toggle_Check();

	// Check for CH6 to Arm / Disarm Motor
	if(Motor_Armed == 0 && TXR_Buffer.CH6 > 500) Motor_Arm();
	else if(Motor_Armed == 1 && TXR_Buffer.CH6 < 500) Motor_Disarm();

	// Check for CH8 to toggle ACK
	ACK_Toggle_Check();

	// Calculate Motor Speed
	Calculate_Motor_Speed();

	// Update Motor Speed if motor armed
	if(Motor_Armed == 1) Update_Motor_Speed();
}

void Autonomous_Mode()
{

}

void Ultrasonic_Sensor_Program()
{
	uint8_t data[4];
	int counter;
	uint8_t address = 1;
	while(1)
	{
		if(HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin) == 1)
		{
		  while(1)
		  {
			  HAL_Delay(100);
			  if(HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin) == 0)
			  {
				  HAL_Delay(100);
				  address++;
				  if(address == 3) address = 1;
				  break;
			  }
		  }
		}
		if(HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin) == 1)
		{
		  while(1)
		  {
			  HAL_Delay(100);
			  if(HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin) == 0)
			  {
				  HAL_Delay(100);
				  	 data[0] = 0;
					data[1] = 0xA0;
					if(address == 1) data[2] = 0xE2;
					else data[2] = 0xE4;
					if(HAL_I2C_Master_Transmit(&hi2c1, 0xE0, data, 2, 10) == HAL_OK)
						WS2812_Write_LED(0, 64, 0, 1);
					else
						WS2812_Write_LED(64, 0, 0, 1);

					data[1] = 0xAA;
					if(HAL_I2C_Master_Transmit(&hi2c1, 0xE0, data, 2, 10) == HAL_OK)
						WS2812_Write_LED(0, 64, 0, 2);
					else
						WS2812_Write_LED(64, 0, 0, 2);

					data[1] = 0xA5;
					if(HAL_I2C_Master_Transmit(&hi2c1, 0xE0, data, 2, 10) == HAL_OK)
						WS2812_Write_LED(0, 64, 0, 3);
					else
						WS2812_Write_LED(64, 0, 0, 3);

					if(address == 1) data[1] = 0xE2;
					else data[1] = 0xE4;
					if(HAL_I2C_Master_Transmit(&hi2c1, 0xE0, data, 2, 10) == HAL_OK)
						WS2812_Write_LED(0, 64, 0, 4);
					else
						WS2812_Write_LED(64, 0, 0, 4);

					WS2812_Write_LED(0, 64, 0, 5);
					WS2812_Load();
					HAL_Delay(1000);
					for(counter = 4; counter >= 0; counter--) LED[counter].data = 0;
				  return;
			  }
		  }
		}

		WS2812_Mode_Display(address);
	}
}

void Ultrasonic_Sensor_Test()
{
	int counter;
	uint8_t result;
	//result = SRF02_init();

	while(1)
	{
		SRF02_Read_Distance();
		HAL_Delay(1);
	}

	for(counter = 4; counter >= 0; counter--) LED[counter].data = 0;

	if((result % 2) == 1) WS2812_Write_LED(64, 0, 0, 2);
	else WS2812_Write_LED(0, 64, 0, 2);
	if(((result >> 1)%2) == 1) WS2812_Write_LED(64, 0, 0, 3);
	else WS2812_Write_LED(0, 64, 0, 3);
	if((result >> 2)%2 == 1) WS2812_Write_LED(64, 0, 0, 4);
	else WS2812_Write_LED(0, 64, 0, 4);
	WS2812_Load();
	HAL_Delay(2000);
}
