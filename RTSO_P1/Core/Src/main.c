/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
ADC_HandleTypeDef hadc1;

UART_HandleTypeDef huart2;

/* Definitions for RTOS_LedAzul */
osThreadId_t RTOS_LedAzulHandle;
const osThreadAttr_t RTOS_LedAzul_attributes = {
  .name = "RTOS_LedAzul",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for RTOS_LedVermelh */
osThreadId_t RTOS_LedVermelhHandle;
const osThreadAttr_t RTOS_LedVermelh_attributes = {
  .name = "RTOS_LedVermelh",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for RTOS_LedVerde */
osThreadId_t RTOS_LedVerdeHandle;
const osThreadAttr_t RTOS_LedVerde_attributes = {
  .name = "RTOS_LedVerde",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for RTOS_LedAmarelo */
osThreadId_t RTOS_LedAmareloHandle;
const osThreadAttr_t RTOS_LedAmarelo_attributes = {
  .name = "RTOS_LedAmarelo",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for RTOS_LedBranco */
osThreadId_t RTOS_LedBrancoHandle;
const osThreadAttr_t RTOS_LedBranco_attributes = {
  .name = "RTOS_LedBranco",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Task_POT */
osThreadId_t Task_POTHandle;
const osThreadAttr_t Task_POT_attributes = {
  .name = "Task_POT",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC1_Init(void);
void StartRTOS_LedAzul(void *argument);
void StartRTOS_LedVermelho(void *argument);
void StartRTOS_LedVerde(void *argument);
void StartRTOS_LedAmarelo(void *argument);
void StartRTOS_LedBranco(void *argument);
void StartTaskPOT(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint16_t readValue = 100;

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
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */

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

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of RTOS_LedAzul */
  RTOS_LedAzulHandle = osThreadNew(StartRTOS_LedAzul, NULL, &RTOS_LedAzul_attributes);

  /* creation of RTOS_LedVermelh */
  RTOS_LedVermelhHandle = osThreadNew(StartRTOS_LedVermelho, NULL, &RTOS_LedVermelh_attributes);

  /* creation of RTOS_LedVerde */
  RTOS_LedVerdeHandle = osThreadNew(StartRTOS_LedVerde, NULL, &RTOS_LedVerde_attributes);

  /* creation of RTOS_LedAmarelo */
  RTOS_LedAmareloHandle = osThreadNew(StartRTOS_LedAmarelo, NULL, &RTOS_LedAmarelo_attributes);

  /* creation of RTOS_LedBranco */
  RTOS_LedBrancoHandle = osThreadNew(StartRTOS_LedBranco, NULL, &RTOS_LedBranco_attributes);

  /* creation of Task_POT */
  Task_POTHandle = osThreadNew(StartTaskPOT, NULL, &Task_POT_attributes);

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

	  // No FreeRTOS o lupe pincipal while nunca ser executado
	  /*HAL_GPIO_TogglePin(GPIOC, LED_Vermelho_Pin);
	    HAL_Delay(500);
	   */
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LED_Verde_Pin|LED_Vermelho_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_Azul_Pin|LED_Amarelo_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_Branco_GPIO_Port, LED_Branco_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_Verde_Pin LED_Vermelho_Pin */
  GPIO_InitStruct.Pin = LED_Verde_Pin|LED_Vermelho_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_Azul_Pin LED_Amarelo_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LED_Azul_Pin|LED_Amarelo_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_Branco_Pin */
  GPIO_InitStruct.Pin = LED_Branco_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_Branco_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartRTOS_LedAzul */
/**
  * @brief  Function implementing the RTOS_LedAzul thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartRTOS_LedAzul */
void StartRTOS_LedAzul(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
	//Led da propria NUCLEO

	//Led azul padrão placa nucleo porta A LD2_Pin
	HAL_GPIO_TogglePin(GPIOA, LED_Azul_Pin);
	osDelay(readValue+20);

  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartRTOS_LedVermelho */
/**
* @brief Function implementing the RTOS_LedVermelh thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartRTOS_LedVermelho */
void StartRTOS_LedVermelho(void *argument)
{
  /* USER CODE BEGIN StartRTOS_LedVermelho */
  /* Infinite loop */
  for(;;)
  {
		HAL_GPIO_TogglePin(GPIOC, LED_Vermelho_Pin);
			osDelay(readValue+40);
  }
  /* USER CODE END StartRTOS_LedVermelho */
}

/* USER CODE BEGIN Header_StartRTOS_LedVerde */
/**
* @brief Function implementing the RTOS_LedVerde thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartRTOS_LedVerde */
void StartRTOS_LedVerde(void *argument)
{
  /* USER CODE BEGIN StartRTOS_LedVerde */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(GPIOC, LED_Verde_Pin);
    osDelay(readValue+60);
  }
  /* USER CODE END StartRTOS_LedVerde */
}

/* USER CODE BEGIN Header_StartRTOS_LedAmarelo */
/**
* @brief Function implementing the RTOS_LedAmarelo thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartRTOS_LedAmarelo */
void StartRTOS_LedAmarelo(void *argument)
{
  /* USER CODE BEGIN StartRTOS_LedAmarelo */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(GPIOA, LED_Amarelo_Pin);
    osDelay(readValue+80);
  }
  /* USER CODE END StartRTOS_LedAmarelo */
}

/* USER CODE BEGIN Header_StartRTOS_LedBranco */
/**
* @brief Function implementing the RTOS_LedBranco thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartRTOS_LedBranco */
void StartRTOS_LedBranco(void *argument)
{
  /* USER CODE BEGIN StartRTOS_LedBranco */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(GPIOB, LED_Branco_Pin);
    osDelay(readValue+100);
  }
  /* USER CODE END StartRTOS_LedBranco */
}

/* USER CODE BEGIN Header_StartTaskPOT */
/**
* @brief Function implementing the Task_POT thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskPOT */
void StartTaskPOT(void *argument)
{
  /* USER CODE BEGIN StartTaskPOT */
  /* Infinite loop */
  for(;;)
  {
	  //inicializa o ADC
		  HAL_ADC_Start(&hadc1);

		  //converter o ADC por 1000 não sei ainda o que faz
		  HAL_ADC_PollForConversion(&hadc1, 100);

		  //pega valor lido em ADC e joga na variavel readValue
		  readValue = HAL_ADC_GetValue(&hadc1);

		  //stopa para do ADC
		  HAL_ADC_Stop(&hadc1);


		  HAL_GPIO_TogglePin(GPIOA, LD2_Pin);

		  osDelay(readValue);

  }
  /* USER CODE END StartTaskPOT */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM9 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM9)
  {
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
#ifdef USE_FULL_ASSERT
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
