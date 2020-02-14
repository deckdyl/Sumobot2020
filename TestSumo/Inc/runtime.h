#ifndef RUNTIME_H_
#define RUNTIME_H_

#define MAX_SPEED		18000
#define SPEED_MODIFIER	(MAX_SPEED/800)

#include "main.h"

void Calculate_TXR_Channel();
void Resolve_CAN_RX_Mailbox();
void Calculate_Motor_Speed();
void Update_Motor_Speed();
void Motor_Arm();
void Motor_Disarm();
void Vacuum_Toggle_Check();
void ACK_Toggle_Check();

void ADC_Calibration_Mode();
void Remote_Control_Mode();
void Autonomous_Mode();
void Ultrasonic_Sensor_Program();
void Ultrasonic_Sensor_Test();

#endif
