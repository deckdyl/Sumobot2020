#ifndef CUSTOM_ESC_H
#define CUSTOM_ESC_H

// ===== Defines here =====
#define	ESC_FLASH_ADDRESS	0x0801F000
#define MCT_HANDLER			MCP_UI_Params._Super.pMCT[MCP_UI_Params._Super.bSelectedDrive]
#define MCI_HANDLER			MCP_UI_Params._Super.pMCI[MCP_UI_Params._Super.bSelectedDrive]
#define SPEED_MODE			0
#define TORQUE_MODE			1

// ===== Register Address Defines =====
#define CON_REG_ADDR		0x00
#define UDFE_REG_ADDR		0x01
#define UDFI_REG_ADDR		0x02
#define BUSV_REG_ADDR		0x04
#define HST_REG_ADDR		0x05
#define MSTS_REG_ADDR		0x06
#define MPWR_REG_ADDR		0x07
#define SPD_REG_ADDR		0x08
#define MAXSPD_REG_ADDR		0x0A
#define RAMPD_REG_ADDR		0x0C
#define RAMPS_REG_ADDR		0x0E
#define SPDPG_REG_ADDR		0x10
#define SPDIG_REG_ADDR		0x12
#define SPDDG_REG_ADDR		0x14
#define IDS_REG_ADDR		0x16
#define IDM_REG_ADDR		0x18
#define IDPG_REG_ADDR		0x1A
#define IDIG_REG_ADDR		0x1C
#define IDDG_REG_ADDR		0x1E
#define IQS_REG_ADDR		0x20
#define IQM_REG_ADDR		0x22
#define IQPG_REG_ADDR		0x24
#define IQIG_REG_ADDR		0x26
#define IQDG_REG_ADDR		0x28
#define FLT_REG_ADDR		0x2A
#define FLTMSK_REG_ADDR		0x2C


// ===== Includes here =====
#include "main.h"
#include "customMC.h"
#include "motor_control_protocol.h"


// Custom Register (48 Bytes)
union
{
	struct
	{

		/* ===== Control Register =====
		 *
		 * Motor Enable		- Turns the motor on/off
		 * 		0 - OFF
		 * 		1 - ON
		 * Motor Mode		- Sets the ESC to Speed / Torque mode
		 * 		0 - Speed Mode
		 * 		1 - Torque Mode
		 * Register Reset	- Resets the custom ESC register to default values
		 * 		0 - Default state
		 * 		1 - Reset register, upon completion, software will clear to 0
		 * ESC_ID			- Sets the ESC ID for CAN identification
		 *
		 */
		union
		{
			struct
			{
				uint8_t MotorEnable				:1;
				uint8_t MotorMode				:1;
				uint8_t RegisterReset			:1;
				uint8_t							:1;
				uint8_t	ESC_ID					:4;
			};
			uint8_t data;
		}CON;

		/* ===== USART Data Feedback Enable Register =====
		 *
		 * This register controls the type of data fed back to main controller.
		 * USART length of data trasferred depends on number and types of registers enabled.
		 * USART transmission data sequence begins MSB of Fault Register and ends with
		 * LSB of Bus Voltage Register.
		 *
		 * 		0 - Disable Corrresponding Register Feedback
		 * 		1 - Enable Corresponding Register Feedback
		 *
		 */
		union
		{
			struct
			{
				uint8_t BusVoltage				:1;
				uint8_t HeatsinkTemperature		:1;
				uint8_t MotorStatus				:1;
				uint8_t MotorPower				:1;
				uint8_t SpeedMeasured			:1;
				uint8_t FluxCurrentMeasured		:1;
				uint8_t TorqueCurrentMeasured	:1;
				uint8_t Fault					:1;
			};
			uint8_t data;
		}UDFE;

		/* ===== USART Data Feedback Interval Register =====
		 *
		 * This register holds the USART transmission interval value in milliseconds.
		 *
		 */
		uint16_t UDFI;

		/* ===== Bus Voltage Register =====
		 *
		 * This register holds the Bus Voltage value in Volts.
		 *
		 */
		uint8_t BUSV;

		/* ===== Heatsink Temperature Register =====
		 *
		 * This register holds the Heatsink Temperature value in degree celcius.
		 *
		 */
		uint8_t HST;

		/* ===== Motor Status Register =====
		 *
		 * This register holds the motor status.
		 * Look at "State_t" enumeration in "state_machine.h" for corresponding details.
		 *
		 */
		uint8_t MSTS;

		/* ===== Motor Power Register =====
		 *
		 * This register holds the Motor Power value in watts.
		 *
		 */
		uint8_t MPWR;

		/* ===== Speed Register =====
		 *
		 * This register holds the current motor speed in RPM.
		 *
		 */
		int16_t SPD;

		/* ===== Max Speed Register =====
		 *
		 * This register holds the motor maximum speed limit in RPM.
		 *
		 */
		uint16_t MAXSPD;

		/* ===== Ramp Duration Register =====
		 *
		 * This register holds the Ramp duration in milliseconds.
		 *
		 */
		uint16_t RAMPD;

		/* ===== Ramp Speed Register =====
		 *
		 * This register holds the Ramp Speed in RPM.
		 *
		 */
		int16_t RAMPS;

		/* ===== Speed P Gain Register =====
		 *
		 * This register holds the P Gain values for speed PID Control.
		 *
		 */
		uint16_t SPDPG;

		/* ===== Speed I Gain Register =====
		 *
		 * This register holds the I Gain values for speed PID Control.
		 *
		 */
		uint16_t SPDIG;

		/* ===== Speed D Gain Register =====
		 *
		 * This register holds the D Gain values for speed PID Control.
		 *
		 */
		uint16_t SPDDG;

		/* ===== Flux Current (Id) Set Register =====
		 *
		 * This register holds the flux current set value.
		 *
		 */
		int16_t IDS;

		/* ===== Flux Current (Id) Measured Register =====
		 *
		 * This register holds the flux current measure value.
		 *
		 */
		int16_t IDM;

		/* ===== Flux Current (Id) P Gain Register =====
		 *
		 * This register holds the P Gain values for flux current PID Control.
		 *
		 */
		uint16_t IDPG;

		/* ===== Flux Current (Id) I Gain Register =====
		 *
		 * This register holds the I Gain values for flux current PID Control.
		 *
		 */
		uint16_t IDIG;

		/* ===== Flux Current (Id) D Gain Register =====
		 *
		 * This register holds the D Gain values for flux current PID Control.
		 *
		 */
		uint16_t IDDG;

		/* ===== Torque Current (Iq) Set Register =====
		 *
		 * This register holds the torque current set value.
		 *
		 */
		int16_t IQS;

		/* ===== Torque Current (Iq) Measured Register =====
		 *
		 * This register holds the torque current measure value.
		 *
		 */
		int16_t IQM;

		/* ===== Torque Current (Iq) P Gain Register =====
		 *
		 * This register holds the P Gain values for torque current PID Control.
		 *
		 */
		uint16_t IQPG;

		/* ===== Torque Current (Iq) I Gain Register =====
		 *
		 * This register holds the I Gain values for torque current PID Control.
		 *
		 */
		uint16_t IQIG;

		/* ===== Torque Current (Iq) D Gain Register =====
		 *
		 * This register holds the D Gain values for torque current PID Control.
		 *
		 */
		uint16_t IQDG;

		/* ===== Fault Register =====
		 *
		 * This register holds the fault values for now and occured.
		 * Most significant 8 bits store occured fault.
		 * Least significant 8 bits store now fault.
		 * Look at "FAULT" for more details.
		 *
		 */
		union
		{
			struct
			{
				FAULT Now;
				FAULT Occurred;
			};
			uint16_t data;
		}FLT;

		/* ===== Fault Register =====
		 *
		 * This register holds the fault values for now and occured.
		 * Most significant 8 bits store occured fault mask.
		 * Least significant 8 bits store now fault mask.
		 * Look at "FAULT" for more details.
		 *
		 */
		union
		{
			struct
			{
				FAULT Now;
				FAULT Occurred;
			};
			uint16_t data;
		}FLTMSK;

		// Blank space to fill the 48 bytes
		uint16_t buffer;

	};
	uint8_t Register[48];
	uint32_t FlashData32[12];
	uint64_t FlashData64[6];
}ESCRegister;

extern MCP_Handle_t MCP_UI_Params;
extern FDCAN_HandleTypeDef hfdcan1;


//===== Prototypes Declaration here =====

// Flash R/W functions
void ESC_Read_Flash();
bool ESC_Write_Flash();

// UART functions
void ESC_UART_Init();
void ESC_UART_TX_Feedback();

// CAN Functions
HAL_StatusTypeDef FDCAN1_RX_Filter_Init(FDCAN_HandleTypeDef * hfdcan);
void CAN_TX_Init_Data(uint8_t reg, uint8_t arg0, uint8_t arg1, uint8_t * pdata);
HAL_StatusTypeDef FDCAN1_TX();

// Register Read functions


// Register Write functions
bool ESCReg_Read(uint8_t reg, uint8_t * data0, uint8_t * data1);
bool ESCReg_Write(uint8_t reg, uint8_t data0, uint8_t data1);
void ESCRegister_Update_Action(uint8_t reg);
bool ESCReg_Refreshed();
void ESCReg_Init();
void ESCReg_Clear();
void ESCReg_UpdateCycle();

bool validata(uint8_t * data1, uint8_t * data2, int size);

#endif
