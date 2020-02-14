#include "WS2812.h"

void WS2812_Mode_Display(uint8_t mode)
{
	int counter;
	for(counter = 4; counter >= 0; counter--) LED[counter].data = 0;
	WS2812_Write_LED(64, 64, 64, 1);
	if(mode >= 2) WS2812_Write_LED(64, 64, 64, 2);
	if(mode >= 3) 	WS2812_Write_LED(64, 64, 64, 3);
	if(mode >= 4) WS2812_Write_LED(64, 64, 64, 4);
	if(mode >= 5) WS2812_Write_LED(64, 64, 64, 5);
	WS2812_Load();
}

void WS2812_Write_LED(uint8_t red, uint8_t green, uint8_t blue, uint8_t LED_Number)
{
	switch(LED_Number)
	{
		case 1:
			LED_Number = 4;
			break;

		case 2:
			LED_Number = 3;
			break;

		case 3:
			LED_Number = 2;
			break;

		case 4:
			LED_Number = 1;
			break;

		case 5:
			LED_Number = 0;
			break;

		default:
			return;
	}
	LED[LED_Number].Red = red;
	LED[LED_Number].Green = green;
	LED[LED_Number].Blue = blue;
}

void WS2812_Load()
{
	uint8_t bit;
	LED_Counter = 4;
	Bit_Counter = 24;
	bit = (LED[LED_Counter].data >> (Bit_Counter-1)) & 0x00000001;
	if(bit == 0) TIM4->CCR1 = 63;
	else TIM4->CCR1 = 136;

	test = 0;
	TIM4->ARR = 213;
	TIM4->SR = TIM4->SR & 0xFFFFFFFC;
	WS2812_Start;
	HAL_Delay(1);

}

void WS2812_Testrun()
{
	int counter;
	for(counter = 4; counter >= 0; counter--) LED[counter].data = 0;
	WS2812_Load();
	for(counter = 4; counter >= 0; counter--)
	{
		while(LED[counter].Red < 255)
		{
			LED[counter].Red++;
			WS2812_Load();
		}
		while(LED[counter].Blue < 255)
		{
			LED[counter].Blue++;
			WS2812_Load();
		}
		while(LED[counter].Green < 255)
		{
			LED[counter].Green++;
			WS2812_Load();
		}

	  }
}

void WS2812_Update()
{
	//if(TXR_Buffer.CH7 < 500)
	//{
		switch(LESC_Status)
		{
			case 0:
				WS2812_Write_LED(128, 0, 0, 2);
				break;

			case 1:
				WS2812_Write_LED(128, 0, 128, 2);
				break;

			case 2:
				if(Motor_Armed == 0) WS2812_Write_LED(0, 0, 128, 2);
				else WS2812_Write_LED(0, 128, 0, 2);
				break;

			default:
				WS2812_Write_LED(0, 0, 0, 2);
				break;
		}

		switch(RESC_Status)
		{
			case 0:
				WS2812_Write_LED(128, 0, 0, 4);
				break;

			case 1:
				WS2812_Write_LED(128, 0, 128, 4);
				break;

			case 2:
				if(Motor_Armed == 0) WS2812_Write_LED(0, 0, 128, 4);
				else WS2812_Write_LED(0, 128, 0, 4);
				break;

			default:
				WS2812_Write_LED(0, 0, 0, 4);
				break;
		}

		if(TXR_Status < 1) WS2812_Write_LED(128, 0, 0, 3);
		else WS2812_Write_LED(0, 128, 0, 3);

		if(LINE_ADC[0] < LINE_ADC[2]) WS2812_Write_LED(128, 0, 0, 1);	// white
		else WS2812_Write_LED(0, 128, 0, 1);		// black

		if(LINE_ADC[1] < LINE_ADC[2]) WS2812_Write_LED(128, 0, 0, 5);
		else WS2812_Write_LED(0, 128, 0, 5);
	//}
	/*else if (TXR_Buffer.CH7 < 1200)
	{
		// Display Control Battery Status
		if(Battery_Control_Voltage >= 6.9) WS2812_Write_LED(128, 0, 0, 1);
		else WS2812_Write_LED(0, 0, 0, 1);
		if(Battery_Control_Voltage >= 7.2) WS2812_Write_LED(128, 0, 0, 2);
		else WS2812_Write_LED(0, 0, 0, 2);
		if(Battery_Control_Voltage >= 7.5) WS2812_Write_LED(0, 0, 128, 3);
		else WS2812_Write_LED(0, 0, 0, 3);
		if(Battery_Control_Voltage >= 7.8) WS2812_Write_LED(0, 128, 0, 4);
		else WS2812_Write_LED(0, 0, 0, 4);
		if(Battery_Control_Voltage >= 8.1) WS2812_Write_LED(0, 128, 0, 5);
		else WS2812_Write_LED(0, 0, 0, 5);
	}
	else
	{
		// Display Drive Battery Status
		if(Battery_Drive_Voltage >= 20.7) WS2812_Write_LED(128, 0, 0, 1);
		else WS2812_Write_LED(0, 0, 0, 1);
		if(Battery_Drive_Voltage >= 21.6) WS2812_Write_LED(128, 0, 0, 2);
		else WS2812_Write_LED(0, 0, 0, 2);
		if(Battery_Drive_Voltage >= 22.5) WS2812_Write_LED(0, 0, 128, 3);
		else WS2812_Write_LED(0, 0, 0, 3);
		if(Battery_Drive_Voltage >= 23.4) WS2812_Write_LED(0, 128, 0, 4);
		else WS2812_Write_LED(0, 0, 0, 4);
		if(Battery_Drive_Voltage >= 24.3) WS2812_Write_LED(0, 128, 0, 5);
		else WS2812_Write_LED(0, 0, 0, 5);
	}*/


}
