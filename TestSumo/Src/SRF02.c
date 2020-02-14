#include "SRF02.h"

uint8_t SRF02_init()
{
	uint8_t result = 0;
	int counter;
	uint8_t test_buffer;

	/* Initialize variables */
	SRF02_Side_Distance = 0;
	SRF02_Left_Distance = 0;
	SRF02_Right_Distance = 0;
	SRF02_Side_Stop_Time = 0;
	SRF02_Left_Stop_Time = 0;
	SRF02_Right_Stop_Time = 0;
	SRF02_Side_Status = 0;
	SRF02_Left_Status = 0;
	SRF02_Right_Status = 0;
	SRF02_Side_Buffer[0] = 0;
	SRF02_Side_Buffer[1] = 0;
	SRF02_Left_Buffer[0] = 0;
	SRF02_Left_Buffer[1] = 0;
	SRF02_Right_Buffer[0] = 0;
	SRF02_Right_Buffer[1] = 0;

	/* Check for Left Sensor online */
	counter = 0;
	while(1)
	{
		test_buffer = 1;
		HAL_I2C_Master_Transmit(&hi2c1, SRF02_LEFT_ADDRESS, &test_buffer, 1, 10);
		if(HAL_I2C_Master_Receive(&hi2c1, (SRF02_LEFT_ADDRESS + 1), &test_buffer, 1, 10) == HAL_OK)
		{
			if(test_buffer == 0x80) break;
		}
		counter++;
		if(counter >= 20)
		{
			result += 1;
			break;
		}
	}

	/* Check for Right Sensor online */
	counter = 0;
	while(1)
	{
		test_buffer = 1;
		HAL_I2C_Master_Transmit(&hi2c1, SRF02_RIGHT_ADDRESS, &test_buffer, 1, 10);
		if(HAL_I2C_Master_Receive(&hi2c1, (SRF02_RIGHT_ADDRESS + 1), &test_buffer, 1, 10) == HAL_OK)
		{
			if(test_buffer == 0x80) break;
		}
		counter++;
		if(counter >= 20)
		{
			result += 2;
			break;
		}
	}

#ifdef SIDE_SENSOR
	/* Check for Side Sensor online */
	counter = 0;
	while(1)
	{
		test_buffer = 1;
		HAL_I2C_Master_Transmit(&hi2c1, SRF02_SIDE_ADDRESS, &test_buffer, 1, 10);
		if(HAL_I2C_Master_Receive(&hi2c1, (SRF02_SIDE_ADDRESS + 1), &test_buffer, 1, 10) == HAL_OK)
		{
			if(test_buffer == 0x80) break;
		}
		counter++;
		if(counter >= 20)
		{
			result += 4;
			break;
		}
	}
#endif

	return result;

}

void SRF02_Read_Distance()
{
	uint32_t currentTick = HAL_GetTick();

	if(SRF02_Left_Status == 0)							// If Left sensor is not started, Start conversion
	{
		if((hi2c1.State & 0x03) == 0)
		{
			SRF02_Start(SRF02_LEFT_ADDRESS);			// Start left sensor conversion
			SRF02_Left_Status = 1;						// Set left sensor status to 1
			SRF02_Left_Stop_Time = HAL_GetTick() + 80;	// Set read time 80ms later (65ms for conversion)
		}

	}
	else												// If Left Sensor has started conversion
	{
		if(currentTick >= SRF02_Left_Stop_Time)			// If conversion time ended
		{
			// Read left sensor distance
			if((hi2c1.State & 0x03) == 0)
			{
				SRF02_Read(SRF02_LEFT_ADDRESS, SRF02_Left_Buffer);
				SRF02_Left_Distance = (SRF02_Left_Buffer[0] << 8) + SRF02_Left_Buffer[1];
				SRF02_Left_Status = 0;					// Set left sensor status to 0
			}
		}
	}

	if(SRF02_Right_Status == 0)							// If Right sensor is not started, Start conversion
	{
		SRF02_Start(SRF02_RIGHT_ADDRESS);		// Start right sensor conversion
		SRF02_Right_Status = 1;						// Set right sensor status to 1
		SRF02_Right_Stop_Time = HAL_GetTick() + 80;	// Set read time 80ms later (65ms for conversion)
	}
	else												// If Right Sensor has started conversion
	{
		if(currentTick >= SRF02_Right_Stop_Time)		// If conversion time ended
		{
			// Read right sensor distance
			if((hi2c1.State & 0x03) == 0)
			{
				SRF02_Read(SRF02_RIGHT_ADDRESS, SRF02_Right_Buffer);
				SRF02_Right_Distance = (SRF02_Right_Buffer[0] << 8) + SRF02_Right_Buffer[1];
				SRF02_Right_Status = 0;					// Set right sensor status to 2
			}
		}
	}

#ifdef SIDE_SENSOR
	if(SRF02_Side_Status == 0)							// If Side sensor is not started, Start conversion
	{
		SRF02_Start(SRF02_SIDE_ADDRESS);		// Start side sensor conversion
		SRF02_Side_Status = 1;							// Set side sensor status to 1
		SRF02_Side_Stop_Time = HAL_GetTick() + 80;		// Set read time 80ms later (65ms for conversion)
	}
	else												// If side Sensor has started conversion
	{
		if(currentTick >= SRF02_Side_Stop_Time)			// If conversion time ended
		{
			// Read side sensor distance
			if((hi2c1.State & 0x03) == 0)
			{
				SRF02_Read(SRF02_SIDE_ADDRESS, SRF02_Side_Buffer);
				SRF02_Side_Distance = (SRF02_Side_Buffer[0] << 8) + SRF02_Side_Buffer[1];
				SRF02_Side_Status = 0;					// Set side sensor status to 2

			}
		}
	}
#endif
}

void SRF02_Start(uint8_t Address)
{
	uint8_t data[2];
	data[0] = 0;
	data[1] = 81;
	HAL_I2C_Master_Transmit(&hi2c1, Address, data, 2, 2);
}


void SRF02_Read(uint8_t Address, uint8_t * pdata)
{
	uint8_t temp = 0x02;
	HAL_I2C_Master_Transmit(&hi2c1, Address, &temp, 1, 2);
	HAL_I2C_Master_Receive(&hi2c1, (Address + 1), pdata, 2, 2);
}
