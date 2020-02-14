#ifndef WS2812_H_
#define WS2812_H_

#define WS2812_Start				TIM4->CR1 = (TIM4->CR1 & 0xFFFE) + 1;
#define WS2812_Stop 				TIM4->CR1 = TIM4->CR1 & 0xFFFE
#define WS2812_Clear_Period_Flag	TIM4->SR = TIM4->SR & 0xFFFFFFFE
#define WS2812_Clear_CC1_Flag		TIM4->SR = TIM4->SR & 0xFFFFFFFD
#define WS2812_CC1_Flag				(TIM4->SR & 0x00000002)

#include "main.h"

typedef union
{
	struct
	{
		uint8_t Blue;
		uint8_t Red;
		uint8_t Green;
		uint8_t Blank;
	};
	uint32_t data;
}RGB;

uint8_t	Bit_Counter;
uint8_t LED_Counter;
RGB 	LED[5];

void WS2812_Mode_Display(uint8_t mode);
void WS2812_Write_LED(uint8_t red, uint8_t green, uint8_t blue, uint8_t LED_Number);
void WS2812_Load();
void WS2812_Testrun();
void WS2812_Update();


#endif
