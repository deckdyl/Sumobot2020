#ifndef SRF02_H_
#define SRF02_H_

// Comment out the following line if there is no side sensor
#define SIDE_SENSOR

#define SRF02_LEFT_ADDRESS		0xE0
#define SRF02_RIGHT_ADDRESS		0xE2
#define SRF02_SIDE_ADDRESS		0xE4

#include "stdbool.h"
#include "main.h"


uint8_t SRF02_Side_Buffer[2];
uint8_t SRF02_Left_Buffer[2];
uint8_t SRF02_Right_Buffer[2];
uint16_t SRF02_Side_Distance;
uint16_t SRF02_Left_Distance;
uint16_t SRF02_Right_Distance;
uint32_t SRF02_Side_Stop_Time;
uint32_t SRF02_Left_Stop_Time;
uint32_t SRF02_Right_Stop_Time;
uint8_t SRF02_Side_Status;
uint8_t SRF02_Left_Status;
uint8_t SRF02_Right_Status;

uint8_t SRF02_init();
void SRF02_Read_Distance();
void SRF02_Start(uint8_t Address);
void SRF02_Read(uint8_t Address, uint8_t * pdata);


#endif
