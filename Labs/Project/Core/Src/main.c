/* USER CODE BEGIN Header */
/**
******************************************************************************
* @file           : main.c
* @brief          : Main program body
* Author: 		  : Quinn Maloney
* SID:			  : 200431628
******************************************************************************
* @attention
*
* Copyright (c) 2024 STMicroelectronics.
* All rights reserved.
*
* This software is licensed under terms that can be found in the LICENSE file
* in the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*
******************************************************************************
*/
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "CLI.h"
#include "lights.h"

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
UART_HandleTypeDef huart2;

/* Definitions for CLI_Input */
osThreadId_t CLI_InputHandle;
const osThreadAttr_t CLI_Input_attributes = {
  .name = "CLI_Input",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Change_Light */
osThreadId_t Change_LightHandle;
const osThreadAttr_t Change_Light_attributes = {
  .name = "Change_Light",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for CLI_Update */
osThreadId_t CLI_UpdateHandle;
const osThreadAttr_t CLI_Update_attributes = {
  .name = "CLI_Update",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for CLI_Queue */
osMessageQueueId_t CLI_QueueHandle;
const osMessageQueueAttr_t CLI_Queue_attributes = {
  .name = "CLI_Queue"
};
/* Definitions for ped_Queue */
osMessageQueueId_t ped_QueueHandle;
const osMessageQueueAttr_t ped_Queue_attributes = {
  .name = "ped_Queue"
};
/* Definitions for Maintenance_Queue */
osMessageQueueId_t Maintenance_QueueHandle;
const osMessageQueueAttr_t Maintenance_Queue_attributes = {
  .name = "Maintenance_Queue"
};
/* Definitions for Emergency_Queue */
osMessageQueueId_t Emergency_QueueHandle;
const osMessageQueueAttr_t Emergency_Queue_attributes = {
  .name = "Emergency_Queue"
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
void Start_CLI_Input(void *argument);
void Start_Change_Light(void *argument);
void Start_CLI_Update(void *argument);

/* USER CODE BEGIN PFP */

uint8_t cliRXChar;
uint8_t cliBufferRX[30];
int counter = 0;
uint8_t maintenance = 0;

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  // this initializes the program. It prepares the usart buffer to receive characters and prints to the terminal to set it up for use
  HAL_UART_Receive_IT (&huart2, &cliRXChar, 1);
  char newLineMessage[] = "Enter a command: ";
  char scrollBox[] = "\x1b[5;r";
  char initialMoveCursor[] = "\x1b[5;0H";

  for(int x = 0; x < sizeof initialMoveCursor; x++)
  	  HAL_UART_Transmit(&huart2, (unsigned char *)&initialMoveCursor[x], 1, 100);
  for(int x = 0; x < sizeof scrollBox; x++)
  	  HAL_UART_Transmit(&huart2, (unsigned char *)&scrollBox[x], 1, 100);
  for(int x = 0; x < sizeof initialMoveCursor; x++)
	  HAL_UART_Transmit(&huart2, (unsigned char *)&initialMoveCursor[x], 1, 100);
  for(int x = 0; x < sizeof newLineMessage; x++)
  	  HAL_UART_Transmit(&huart2, (unsigned char *)&newLineMessage[x], 1, 100);
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of CLI_Queue */
  CLI_QueueHandle = osMessageQueueNew (1, sizeof(uint8_t), &CLI_Queue_attributes);

  /* creation of ped_Queue */
  ped_QueueHandle = osMessageQueueNew (4, sizeof(uint8_t), &ped_Queue_attributes);

  /* creation of Maintenance_Queue */
  Maintenance_QueueHandle = osMessageQueueNew (1, sizeof(uint8_t), &Maintenance_Queue_attributes);

  /* creation of Emergency_Queue */
  Emergency_QueueHandle = osMessageQueueNew (1, sizeof(uint8_t), &Emergency_Queue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of CLI_Input */
  CLI_InputHandle = osThreadNew(Start_CLI_Input, NULL, &CLI_Input_attributes);

  /* creation of Change_Light */
  Change_LightHandle = osThreadNew(Start_Change_Light, NULL, &Change_Light_attributes);

  /* creation of CLI_Update */
  CLI_UpdateHandle = osThreadNew(Start_CLI_Update, NULL, &CLI_Update_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
* @brief USART2 Initialization Function
* @param None
* @retval None
*/
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
* @brief GPIO Initialization Function
* @param None
* @retval None
*/
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, Red_N_S_Pin|Yellow_N_S_Pin|Green_N_S_Pin|LD2_Pin
                          |Turn_E_W_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Turn_N_S_Pin|Red_E_W_Pin|Yellow_E_W_Pin|Green_E_W_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : Maintenance_Mode_Pin */
  GPIO_InitStruct.Pin = Maintenance_Mode_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Maintenance_Mode_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Red_N_S_Pin Yellow_N_S_Pin Green_N_S_Pin LD2_Pin
                           Turn_E_W_Pin */
  GPIO_InitStruct.Pin = Red_N_S_Pin|Yellow_N_S_Pin|Green_N_S_Pin|LD2_Pin
                          |Turn_E_W_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : Turn_N_S_Pin Red_E_W_Pin Yellow_E_W_Pin Green_E_W_Pin */
  GPIO_InitStruct.Pin = Turn_N_S_Pin|Red_E_W_Pin|Yellow_E_W_Pin|Green_E_W_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/**
* @brief  Function implementing the USART interrupt. It stores the character received in a buffer.
* @param  husart: the pin used in this case HUSART2
* @retval None
*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef * husart)
{
	while((HAL_UART_GetState(&huart2)&HAL_UART_STATE_BUSY_RX)==HAL_UART_STATE_BUSY_RX);
	//Listen for the interrupt and buffer one character at a time.
	HAL_UART_Receive_IT(&huart2, &cliRXChar ,1);
}

/**
* @brief  Function implementing the GPIOC pin 13 interrupt (user button). It sends a value to the maintenance
* 		queue to notify the Change_Light thread.
* @param  GPIO_Pin: the in causing the interrupt. In this case GPIOC pin 13
* @retval None
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_13)
	{
		if(maintenance == 0)
		{
			maintenance = 1;
			xQueueGenericSendFromISR(Maintenance_QueueHandle, &maintenance, pdTRUE, NULL);
		}
		else
		{
			maintenance = 0;
			xQueueGenericSendFromISR(Maintenance_QueueHandle, &maintenance, pdTRUE, NULL);
		}
	}
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_Start_CLI_Input */
/**
* @brief  Function implementing the CLI_Input thread. It is responsible for updating the terminal with the user
* 		input and handling it accordingly. When a pedestrian event is requested it puts that in the ped queue
* 		and when an emergency vehicle is requested it puts that in the Emergency queue. This queue is used by
* 		the Change_Light thread.
* @param  argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_CLI_Input */
void Start_CLI_Input(void *argument)
{
  /* USER CODE BEGIN 5 */
  uint8_t input = 0;
  /* Infinite loop */
  for(;;)
  {
	if(cliRXChar != '\0')
	{
		input = CLI_Receive();
		if(input == 1 || input == 2)
			osMessageQueuePut(ped_QueueHandle, &input, 0, 500);
		else if(input == 3 || input == 4)
			osMessageQueuePut(Emergency_QueueHandle, &input, 0, 500);
	}
    osDelay(100);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_Start_Change_Light */
/**
* @brief Function implementing the Change_Light thread. This is responsible for changing the light state. This
* 		 includes both updating the internal state and changing the physical lights to match the state. It does
* 		 not update the CLI state however. For that it sends a message to the CLI queue where it is handled by
* 		 the CLI_Update thread. Emergency state is also checked in this thread where the states are frozen
* 		 temporarily.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Change_Light */
void Start_Change_Light(void *argument)
{
  /* USER CODE BEGIN Start_Change_Light */
  uint8_t lightState = 0;
  uint8_t newLightState = 0;
  uint16_t lightCounter = 0;
  uint8_t pedestrian = 0;
  uint8_t pedestrianNS = 0;
  uint8_t pedestrianEW = 0;
  uint8_t emergency = 0;
  uint8_t emergencyNS = 0;
  uint8_t emergencyEW = 0;
  uint8_t isMaintenance = 0;
  /* Infinite loop */
  for(;;)
  {
	osMessageQueueGet(Maintenance_QueueHandle, &isMaintenance, NULL, 200);
	if(isMaintenance == 1)
	{
		startMaintenanceMode();
		lightState = 0;
		newLightState = 0;
		counter = 0;
		isMaintenance = 2;
	}
	if(isMaintenance == 2)
		maintenanceMode();
	else
	{
		osMessageQueueGet(ped_QueueHandle, &pedestrian, NULL, 200);
		if(pedestrian == 1)
			pedestrianNS = 1;
		if(pedestrian == 2)
			pedestrianEW = 1;
		osMessageQueueGet(Emergency_QueueHandle, &emergency, NULL, 200);
		if(emergency == 3)
			emergencyNS = 1;
		if(emergency == 4)
			emergencyEW = 1;
		newLightState = lightStateChange(lightState, lightCounter, pedestrianNS, pedestrianEW, emergencyNS, emergencyEW);
		if (newLightState != lightState)
		{
			lightState = newLightState;
			osMessageQueuePut(CLI_QueueHandle, &lightState, 0, 500);
			lightCounter = 0;
			if(lightState == 0 || lightState == 4)
			{
				pedestrian = 0;
				pedestrianNS = 0;
				pedestrianEW = 0;
			}
			emergency = 0;
			emergencyNS = 0;
			emergencyEW = 0;
		}
		else
			lightCounter++;
		lightPhysicalChange(lightState);
	}
    osDelay(500);
  }
  /* USER CODE END Start_Change_Light */
}

/* USER CODE BEGIN Header_Start_CLI_Update */
/**
* @brief Function implementing the CLI_Update thread. It is responsible for updating the status of the terminal.
* 		 This is only fully executed on a state change which is indicated by the data in the CLI queue from the
* 		 Change_Light thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_CLI_Update */
void Start_CLI_Update(void *argument)
{
  /* USER CODE BEGIN Start_CLI_Update */
  uint8_t newState = 0;
  uint8_t lightState = 7;
  /* Infinite loop */
  for(;;)
  {
	osMessageQueueGet(CLI_QueueHandle, &newState, NULL, 200);
	if (newState != lightState)
	{
		lightState = newState;
		CLI_Display(lightState);
	}
    osDelay(100);
  }
  /* USER CODE END Start_CLI_Update */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
