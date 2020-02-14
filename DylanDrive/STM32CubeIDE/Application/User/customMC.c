#include "main.h"
#include "customMC.h"

extern MCI_Handle_t* pMCI[NBR_OF_MOTORS];
extern SpeednTorqCtrl_Handle_t *pSTC[NBR_OF_MOTORS];

void Motor_Init()
{
	Motor_PID_Init();
	Motor_Set_Speed(10);
	MotorStart;
	ESCRegister.CON.MotorEnable = 1;
}



void Motor_PID_Init()
{
	PID_SetKP(pSTC[0]->PISpeed, ESCRegister.SPDPG);
	PID_SetKI(pSTC[0]->PISpeed, ESCRegister.SPDIG);
	PID_SetKD(pSTC[0]->PISpeed, ESCRegister.SPDDG);
}


/*
 * Command to move motor
 *
 * retval		Return true on update of speed
 * 				Return false on invalid percentage value
 *
 * percentage	Range from -100 to 100
 */
bool Motor_Set_Speed(float percentage)
{
	int motor_value;

	// Return false if percentage out or range
	if(percentage < -100 || percentage > 100) return false;
	percentage /= 100.0;

	motor_value = (percentage * CUSTOM_MAX_RPM)/6;
	MC_ProgramSpeedRampMotor1(motor_value, 50);
	return true;
}
