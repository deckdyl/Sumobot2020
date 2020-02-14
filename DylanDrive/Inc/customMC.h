#ifndef CUSTOMMC_H
#define CUSTOMMC_H

#include <stdint.h>

typedef union
{
	struct
	{
		uint8_t	FOC_Duration	:1;
		uint8_t Over_Voltage	:1;
		uint8_t Under_Voltage	:1;
		uint8_t Overheat		:1;
		uint8_t Startup_Failure	:1;
		uint8_t Speed_Feedback	:1;
		uint8_t Over_Current	:1;
		uint8_t Software_Error	:1;
	};
	uint8_t data;
}FAULT;

#define	CUSTOM_MAX_RPM	12000		// Wheels Rotate 5 Rounds a second at Max Speed

#define	MotorStart		MC_StartMotor1()
#define MotorStop		MC_StopMotor1()
#define MotorGetFault	STM_GetFaultState( pMCI[0]->pSTM )

void Motor_Init();
void Motor_PID_Init();
bool Motor_Set_Speed(float percentage);

#endif
