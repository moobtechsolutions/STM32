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
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */

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
  MX_TIM1_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

  //inicializar os timer 01 e os canais 1 e 2
  // Pinos de saida Chanel 1 = PA8
  // Pinos de saida Chanel 2 = PA9
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);

  //inicializar os timer 02 e os canais 1 e 2
  // Pinos de saida Chanel 1 = PA0
  // Pinos de saida Chanel 2 = PA1
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

  //inicializar os timer 03 e os canais 1 e 2
  // Pinos de saida Chanel 1 = PA6
  // Pinos de saida Chanel 2 = PA7
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);



  /* Certifique-se de que a instância do timer está declarada (geralmente htim1 ou htim8) */
  extern TIM_HandleTypeDef htim1;

  /**
    * @brief  Executa a partida suave (Soft-Start) para a topologia Push-Pull.
    * @note   ARR = 2000. Alvo final de 50% de Duty Cycle.
    * @param  passos: Quantos incrementos a rampa terá até atingir o valor final.
    * @param  atraso_ms: Tempo de espera em milissegundos entre cada passo da rampa.
    */
  void Executar_SoftStart_PushPull_50PercentTIM1(uint16_t passos, uint32_t atraso_ms)
  {
      // Valores Iniciais solicitados
      uint16_t pulse_A = 100;
      uint16_t pulse_B = 1900;

      // Valores Finais calculados para 50% de Duty Cycle máximo (ARR = 2000)
      uint16_t alvo_A = 999;
      uint16_t alvo_B = 1001;

      // Calcula o tamanho do degrau de incremento/decremento para cada passo da rampa
      float incremento_A = (float)(alvo_A - pulse_A) / passos;
      float decremento_B = (float)(pulse_B - alvo_B) / passos;

      // 1. Define os valores iniciais nos registradores antes de ligar as saídas
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pulse_A);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pulse_B);

      // 2. Inicializa os canais PWM (Principal e Complementar se houver)
      HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
      //HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1); // Se usar CH1N

      HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
      //HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2); // Se usar CH2N

      // 3. Executa a rampa de subida suave
      for (uint16_t i = 0; i < passos; i++)
      {
          pulse_A += (uint16_t)incremento_A;
          pulse_B -= (uint16_t)decremento_B;

          // Atualiza os registradores de variação em tempo de execução
          __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pulse_A);
          __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pulse_B);

          // Atraso para controlar a velocidade do Soft-Start
          HAL_Delay(atraso_ms);
      }

      // 4. Garante que os valores finais fiquem cravados exatamente no alvo de 50%
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, alvo_A);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, alvo_B);
  }


  void Executar_SoftStart_PushPull_50PercentTIM2(uint16_t passos, uint32_t atraso_ms)
    {
        // Valores Iniciais solicitados
        uint16_t pulse_A = 100;
        uint16_t pulse_B = 1900;

        // Valores Finais calculados para 50% de Duty Cycle máximo (ARR = 2000)
        uint16_t alvo_A = 999;
        uint16_t alvo_B = 1001;

        // Calcula o tamanho do degrau de incremento/decremento para cada passo da rampa
        float incremento_A = (float)(alvo_A - pulse_A) / passos;
        float decremento_B = (float)(pulse_B - alvo_B) / passos;

        // 1. Define os valores iniciais nos registradores antes de ligar as saídas
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pulse_A);
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pulse_B);

        // 2. Inicializa os canais PWM (Principal e Complementar se houver)
        HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
        //HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1); // Se usar CH1N

        HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
        //HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2); // Se usar CH2N

        // 3. Executa a rampa de subida suave
        for (uint16_t i = 0; i < passos; i++)
        {
            pulse_A += (uint16_t)incremento_A;
            pulse_B -= (uint16_t)decremento_B;

            // Atualiza os registradores de variação em tempo de execução
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pulse_A);
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pulse_B);

            // Atraso para controlar a velocidade do Soft-Start
            HAL_Delay(atraso_ms);
        }

        // 4. Garante que os valores finais fiquem cravados exatamente no alvo de 50%
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, alvo_A);
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, alvo_B);
    }

    void Executar_SoftStart_PushPull_50PercentTIM3(uint16_t passos, uint32_t atraso_ms)
    {
        // Valores Iniciais solicitados
        uint16_t pulse_A = 100;
        uint16_t pulse_B = 1900;

        // Valores Finais calculados para 50% de Duty Cycle máximo (ARR = 2000)
        uint16_t alvo_A = 995;
        uint16_t alvo_B = 1005;

        // Calcula o tamanho do degrau de incremento/decremento para cada passo da rampa
        float incremento_A = (float)(alvo_A - pulse_A) / passos;
        float decremento_B = (float)(pulse_B - alvo_B) / passos;

        // 1. Define os valores iniciais nos registradores antes de ligar as saídas
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulse_A);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pulse_B);

        // 2. Inicializa os canais PWM (Principal e Complementar se houver)
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
        //HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1); // Se usar CH1N

        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
        //HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2); // Se usar CH2N

        // 3. Executa a rampa de subida suave
        for (uint16_t i = 0; i < passos; i++)
        {
            pulse_A += (uint16_t)incremento_A;
            pulse_B -= (uint16_t)decremento_B;

            // Atualiza os registradores de variação em tempo de execução
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulse_A);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pulse_B);

            // Atraso para controlar a velocidade do Soft-Start
            HAL_Delay(atraso_ms);
        }

        // 4. Garante que os valores finais fiquem cravados exatamente no alvo de 50%
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, alvo_A);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, alvo_B);
    }                              //primeiro paramento é a divissão do passo por 400 exempo
                                   //segundo paramentro é daley igual al Hal_Delay 50
  //Executar_SoftStart_PushPull_50PercentTIM1(400, 10);

  //Executar_SoftStart_PushPull_50PercentTIM2(400, 50);

  Executar_SoftStart_PushPull_50PercentTIM3(400, 10);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  //uma forma de alterar estado do pinoi do led
	 	  HAL_GPIO_TogglePin(GPIOA, LD2_Pin);
	 	  HAL_Delay(1000);

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
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_CENTERALIGNED3;
  htim1.Init.Period = 2000;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 100;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM2;
  sConfigOC.Pulse = 1900;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_CENTERALIGNED3;
  htim2.Init.Period = 2000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 100;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM2;
  sConfigOC.Pulse = 1900;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_CENTERALIGNED3;
  htim3.Init.Period = 2000;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 100;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM2;
  sConfigOC.Pulse = 1900;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

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
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
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
