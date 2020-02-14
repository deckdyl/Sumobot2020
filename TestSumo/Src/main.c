/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "fdcan.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void Variable_Init()
{
	int counter;

	test = 0;
	mode = 1;

	Bit_Counter = 23;
	LED_Counter = 5;
	for(counter = 0; counter < 5; counter++) LED[counter].data = 0;

	for(counter = 0; counter < 4; counter++) CAN_RX_Buffer[counter] = 0;
	for(counter = 0; counter < 10; counter++) CAN_TX_Buffer[counter] = 0;
	for(counter = 0; counter < 25; counter++) TXR_Buffer.array[counter] = 0;
	LESC_Status = 0;
	RESC_Status = 0;
	TXR_Status = 0;
	CAN_RX_Mailbox = 0;
	Motor_Armed = 0;
	Vacuum_Armed = 0;
	ACK_Toggle = 0;
	LeftMotorSpeed = 0;
	RightMotorSpeed = 0;
	LINE_ADC[0] = 0;
	LINE_ADC[1] = 0;

	RAMPD = 50;
}

void Peripheral_Init()
{
	int counter;

	// Start Battery ADC Conversion
	HAL_TIM_Base_Start_IT(&htim6);

	// WS2812 Init
	HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_1);
	for(counter = 0; counter < 5; counter++) WS2812_Load();

	// Vacuum Init
	TIM1->CCR1 = 1000;
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

	// Start UART DMA
	HAL_UART_Receive_DMA(&huart4, ESC_Right.array, 13);
	HAL_UART_Receive_DMA(&huart5, ESC_Left.array, 13);
	HAL_UART_Receive_DMA(&huart3, TXR_Buffer.array, 25);

	// Initialize CAN bus
	HAL_FDCAN_MspInit(&hfdcan1);
	FDCAN1_RX_Filter_Init(&hfdcan1);
	HAL_FDCAN_Start(&hfdcan1);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
uint32_t TICK;
uint32_t refrence;
	int counter;
  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM6_Init();
  MX_TIM4_Init();
  MX_FDCAN1_Init();
  MX_UART4_Init();
  MX_UART5_Init();
  MX_USART3_UART_Init();
  MX_ADC2_Init();
  MX_TIM1_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  // Initialize all variables
  Variable_Init();
 // SRF02_init();

  // Initialize all variables
  Peripheral_Init();

  while(1)
	  Remote_Control_Mode();

  while(1)
  {
	  if(CAN_RX_Mailbox > 0) Resolve_CAN_RX_Mailbox();
	  WS2812_Update();
  	  WS2812_Load();
  	  if(LESC_Status == 2 && RESC_Status == 2) break;
  }
  HAL_Delay(500);

  LeftMotorSpeed = 0;
  RightMotorSpeed = 0;
  for(counter = 0; counter < 3; counter++)
  {
	  Motor_Arm();
	  WS2812_Update();
	  WS2812_Load();
	  Update_Motor_Speed();
	  if(CAN_RX_Mailbox > 0) Resolve_CAN_RX_Mailbox();
	  HAL_Delay(500);
	  Motor_Disarm();
	  WS2812_Update();
	  WS2812_Load();
	  Update_Motor_Speed();
	  if(CAN_RX_Mailbox > 0) Resolve_CAN_RX_Mailbox();
	  HAL_Delay(500);
  }
  Motor_Arm();
  Update_Motor_Speed();
  if(CAN_RX_Mailbox > 0) Resolve_CAN_RX_Mailbox();
  HAL_Delay(500);
  WS2812_Update();
  WS2812_Load();

  while(HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin) == 0)
  {
	  WS2812_Update();
	  WS2812_Load();
	  HAL_Delay(10);
  }
  if(HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin) == 1)
  {
	  while(1)
	  {
		  HAL_Delay(10);
		  if(HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin) == 0)
		  {
			  HAL_Delay(100);
			  break;
		  }
	  }
  }
  refrence = LINE_ADC[2];



  TIM1->CCR1 = 2000;
  while(1)
  {
	  if(LINE_ADC[0] > refrence && LINE_ADC[1] > refrence)
	  {
		  // forward
		  LeftMotorSpeed = -15000;
	  	  RightMotorSpeed = 15000;
	  	  Update_Motor_Speed();
	  	  HAL_Delay(10);
	  }
	  if(LINE_ADC[0] <= refrence && LINE_ADC[1] > refrence)
	  {
		  while(LINE_ADC[0] <= refrence)
		  {
			  LeftMotorSpeed = -15000;
			  RightMotorSpeed = -15000;
			  Update_Motor_Speed();
			  HAL_Delay(10);
		  }
	  }

	  if(LINE_ADC[0] > refrence && LINE_ADC[1] <= refrence)
	  {
		  while(LINE_ADC[1] <= refrence)
		  {
			  LeftMotorSpeed = 15000;
			  RightMotorSpeed = 15000;
			  Update_Motor_Speed();
			  HAL_Delay(10);
		  }
	  }

	  if(LINE_ADC[0] <= refrence && LINE_ADC[1] <= refrence)
	  {
		  LeftMotorSpeed = 15000;
		  RightMotorSpeed = 15000;
		  Update_Motor_Speed();
		  HAL_Delay(50);
	  }

	  if(HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin) == 1)
	  {
		  Motor_Disarm();
		  TIM1->CCR1 = 1000;
		  while(1) HAL_Delay(10);
	  }

	  /*
			  // backward
			  LeftMotorSpeed = 2400;
			  RightMotorSpeed = -2400;

		  // forward
		  LeftMotorSpeed = -2400;
		  RightMotorSpeed = 2400;
	  }*/

	  WS2812_Update();
	  WS2812_Load();
  }


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  HAL_Delay(10);


	  if(HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin) == 1)
	  {
		  while(1)
		  {
			  HAL_Delay(100);
			  if(HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin) == 0)
			  {
				  HAL_Delay(100);
				  mode++;
				  if(mode == 6) mode = 1;
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
				  switch(mode)
				  {
					  case 1:
						  ADC_Calibration_Mode();
						  break;

					  case 2:
						  Remote_Control_Mode();
						  break;

					  case 3:
						  Autonomous_Mode();
						  break;

					  case 4:
						  Ultrasonic_Sensor_Program();
						  break;

					  case 5:
						  Ultrasonic_Sensor_Test();
						  break;
				  }
			  }
		  }
	  }
	  WS2812_Mode_Display(mode);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage 
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_8) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the peripherals clocks 
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_UART4
                              |RCC_PERIPHCLK_UART5|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_ADC12|RCC_PERIPHCLK_FDCAN;
  PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  PeriphClkInit.Uart4ClockSelection = RCC_UART4CLKSOURCE_PCLK1;
  PeriphClkInit.Uart5ClockSelection = RCC_UART5CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12CLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
