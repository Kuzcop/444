/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#define ARM_MATH_CM4
#include "arm_math.h"
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ITM_Port32(n) (*((volatile unsigned long *) (0xE0000000+4*n)))
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define VALUE_LIMIT 2730

// Part 1
//#define SIZE 30

// Part 2 and 3
//#define SIZE 30
//#define AD_FREQ 20000
//#define TALKING_TIME_S 2
//#define AUDIO_SIZE TALKING_TIME_S*AD_FREQ

// Part 4
#define SIZE 3
#define AD_FREQ 20000
#define TALKING_TIME_S 2
#define AUDIO_SIZE TALKING_TIME_S*AD_FREQ
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
DAC_HandleTypeDef hdac1;
DMA_HandleTypeDef hdma_dac1_ch1;
DMA_HandleTypeDef hdma_dac1_ch2;

DFSDM_Filter_HandleTypeDef hdfsdm1_filter0;
DFSDM_Channel_HandleTypeDef hdfsdm1_channel2;
DMA_HandleTypeDef hdma_dfsdm1_flt0;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_DAC1_Init(void);
static void MX_TIM2_Init(void);
static void MX_DFSDM1_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM5_Init(void);
/* USER CODE BEGIN PFP */
void gen_sine(void);
//uint16_t* gen_notes(uint16_t);
void gen_notes(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//uint16_t sine[SIZE];
uint16_t sine[SIZE];
uint32_t audio[AUDIO_SIZE];
uint16_t sine_index = 0;
uint16_t counter = 0;
uint32_t val = 0;
uint16_t song_index = 0;
uint16_t state = -1;

uint32_t note_0[SIZE*20];
uint32_t note_1[SIZE*2];
uint32_t note_2[SIZE*4];
uint32_t note_3[SIZE*8];
uint32_t note_4[SIZE*16];
uint32_t note_5[SIZE*32];

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
  MX_DMA_Init();
  MX_DAC1_Init();
  MX_TIM2_Init();
  MX_DFSDM1_Init();
  MX_TIM4_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */
  /*
   * Part 1
   */
//  HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);
  /*
   * Part 2
   */
  //HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, sine, SIZE, DAC_ALIGN_12B_R);

  //HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_Base_Start_IT(&htim4);

  gen_sine();
  gen_notes();
//  *note_0 = gen_notes(SIZE*20);
//  *note_1 = gen_notes(SIZE*2);
//  *note_2 = gen_notes(SIZE*4);
//  *note_3 = gen_notes(SIZE*8);
//  *note_4 = gen_notes(SIZE*16);
//  *note_5 = gen_notes(SIZE*32);

  //HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, note_0, SIZE, DAC_ALIGN_12B_R);
  /* USER CODE END 2 */

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

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief DAC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC1_Init(void)
{

  /* USER CODE BEGIN DAC1_Init 0 */

  /* USER CODE END DAC1_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC1_Init 1 */

  /* USER CODE END DAC1_Init 1 */

  /** DAC Initialization
  */
  hdac1.Instance = DAC1;
  if (HAL_DAC_Init(&hdac1) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT1 config
  */
  sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;
  sConfig.DAC_Trigger = DAC_TRIGGER_T2_TRGO;
  sConfig.DAC_HighFrequency = DAC_HIGH_FREQUENCY_INTERFACE_MODE_ABOVE_80MHZ;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;
  sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
  if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT2 config
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_T4_TRGO;
  if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC1_Init 2 */

  /* USER CODE END DAC1_Init 2 */

}

/**
  * @brief DFSDM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_DFSDM1_Init(void)
{

  /* USER CODE BEGIN DFSDM1_Init 0 */

  /* USER CODE END DFSDM1_Init 0 */

  /* USER CODE BEGIN DFSDM1_Init 1 */

  /* USER CODE END DFSDM1_Init 1 */
  hdfsdm1_filter0.Instance = DFSDM1_Filter0;
  hdfsdm1_filter0.Init.RegularParam.Trigger = DFSDM_FILTER_SW_TRIGGER;
  hdfsdm1_filter0.Init.RegularParam.FastMode = ENABLE;
  hdfsdm1_filter0.Init.RegularParam.DmaMode = ENABLE;
  hdfsdm1_filter0.Init.FilterParam.SincOrder = DFSDM_FILTER_SINC3_ORDER;
  hdfsdm1_filter0.Init.FilterParam.Oversampling = 100;
  hdfsdm1_filter0.Init.FilterParam.IntOversampling = 1;
  if (HAL_DFSDM_FilterInit(&hdfsdm1_filter0) != HAL_OK)
  {
    Error_Handler();
  }
  hdfsdm1_channel2.Instance = DFSDM1_Channel2;
  hdfsdm1_channel2.Init.OutputClock.Activation = ENABLE;
  hdfsdm1_channel2.Init.OutputClock.Selection = DFSDM_CHANNEL_OUTPUT_CLOCK_SYSTEM;
  hdfsdm1_channel2.Init.OutputClock.Divider = 60;
  hdfsdm1_channel2.Init.Input.Multiplexer = DFSDM_CHANNEL_EXTERNAL_INPUTS;
  hdfsdm1_channel2.Init.Input.DataPacking = DFSDM_CHANNEL_STANDARD_MODE;
  hdfsdm1_channel2.Init.Input.Pins = DFSDM_CHANNEL_SAME_CHANNEL_PINS;
  hdfsdm1_channel2.Init.SerialInterface.Type = DFSDM_CHANNEL_SPI_RISING;
  hdfsdm1_channel2.Init.SerialInterface.SpiClock = DFSDM_CHANNEL_SPI_CLOCK_INTERNAL;
  hdfsdm1_channel2.Init.Awd.FilterOrder = DFSDM_CHANNEL_FASTSINC_ORDER;
  hdfsdm1_channel2.Init.Awd.Oversampling = 1;
  hdfsdm1_channel2.Init.Offset = 0;
  hdfsdm1_channel2.Init.RightBitShift = 0x00;
  if (HAL_DFSDM_ChannelInit(&hdfsdm1_channel2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DFSDM_FilterConfigRegChannel(&hdfsdm1_filter0, DFSDM_CHANNEL_2, DFSDM_CONTINUOUS_CONV_ON) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DFSDM1_Init 2 */

  /* USER CODE END DFSDM1_Init 2 */

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

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 2721;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 10000;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 3000;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 6000;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 40000;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 6000;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMAMUX1_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  /* DMA1_Channel2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB_Pin */
  GPIO_InitStruct.Pin = PB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(PB_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

// Part 1
//void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin){
//	//start timer for led
//	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//}

/*
 * Part 1
 */
//void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef * htim){
//	counter++;
//	if (counter == 14){
//		HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, (uint32_t)(sine[sine_index]));
//		sine_index++;
//		counter = 0;
//		if (sine_index == SIZE) sine_index = 0;
//	}
//
//}

// Part 3
/*
void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin){
	HAL_TIM_Base_Start_IT(&htim3);				// Start timer 3 for LED
	HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_2);	// Stop playing looped audio
	HAL_DFSDM_FilterRegularStart_DMA(&hdfsdm1_filter0, audio, AUDIO_SIZE);	// Start recording
}

void HAL_DFSDM_FilterRegConvCpltCallback (DFSDM_Filter_HandleTypeDef * hdfsdm_filter){
	HAL_DFSDM_FilterRegularStop_DMA(&hdfsdm1_filter0);			// Stop recording
	HAL_TIM_Base_Stop_IT(&htim3);								// Stop timer for led
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);	// Turn on Led

	// Scale audio
	for (int i = 0; i<AUDIO_SIZE; i++){
		val = (uint32_t)(audio[i]/256 + pow(2, 23)/pow(2,12));
		audio[i]= val;
	}
	HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_2, audio, AUDIO_SIZE, DAC_ALIGN_12B_R);	// Play looped audio
}

void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef * htim){
	if (htim == &htim3){
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	}

}
*/

// Part 4
void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin){
	song_index = 0;
	state = (state + 1)%2;
	if (state == 0){
		HAL_TIM_Base_Stop_IT(&htim5);
		HAL_TIM_Base_Start_IT(&htim3);				// Start timer 3 for LED
		HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_2);	// Stop playing looped audio
		HAL_DFSDM_FilterRegularStart_DMA(&hdfsdm1_filter0, audio, AUDIO_SIZE);	// Start recording
	}
	else if(state == 1){
		HAL_TIM_Base_Start_IT(&htim5);
	}
}

void HAL_DFSDM_FilterRegConvCpltCallback (DFSDM_Filter_HandleTypeDef * hdfsdm_filter){
	HAL_DFSDM_FilterRegularStop_DMA(&hdfsdm1_filter0);			// Stop recording
	HAL_TIM_Base_Stop_IT(&htim3);								// Stop timer for led
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);	// Turn on Led

	// Scale audio
	for (int i = 0; i<AUDIO_SIZE; i++){
		val = (((audio[i] >> 8)+ pow(2, 23))/pow(2,12))*2/3;
		audio[i]= val;
	}

}

void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef * htim){
	if (htim == &htim3){
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	}
	if (htim == &htim5){
		HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_2);	// Stop playing looped audio
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);	// Turn on Led
		song_index - 5;
		switch(song_index) {
			case 5:
				HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_2);	// Stop playing looped audio

				HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_2, note_0, SIZE*20, DAC_ALIGN_12B_R);
			     break;
			case 4:
				HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_2);	// Stop playing looped audio

				HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_2, note_1, SIZE*2, DAC_ALIGN_12B_R);
			     break;
			case 3:
				HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_2);	// Stop playing looped audio

				HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_2, note_2, SIZE*4, DAC_ALIGN_12B_R);
				break;
			case 2:
				HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_2);	// Stop playing looped audio

				HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_2, note_3, SIZE*8, DAC_ALIGN_12B_R);
				break;
			case 1:
				HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_2);	// Stop playing looped audio

				HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_2, note_4, SIZE*16, DAC_ALIGN_12B_R);
				break;
			case 0:
				HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_2);	// Stop playing looped audio

				HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_2, note_5, SIZE*32, DAC_ALIGN_12B_R);
				break;
			default:
				HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_2, audio, AUDIO_SIZE, DAC_ALIGN_12B_R);
			 }
		song_index = (song_index + 1) % 7;
	}

}

void gen_sine(void){
	float theta = 0.0;
	float val = 0.0;
	for (int i = 0; i < SIZE; i++){
		val = (VALUE_LIMIT/2.0)*arm_sin_f32(theta);
		sine[i] = (uint16_t)(val + (VALUE_LIMIT/2.0));
		theta += (2*PI)/(30);
	}
}

//uint16_t* gen_notes(uint16_t size){
//
//	uint16_t *arr = (uint16_t *) malloc(size*sizeof(uint16_t));
//	float theta = 0.0;
//	float val = 0.0;
//	for (int i = 0; i < size; i++){
//		val = (VALUE_LIMIT/2.0)*arm_sin_f32(theta);
//		arr[i] = (uint16_t)(val + (VALUE_LIMIT/2.0));
//		theta += (2*PI)/(size);
//	}
//	return arr;
//}

void gen_notes(void){

	float theta = 0.0;
	float val = 0.0;
	uint32_t size = SIZE*20;
	for (int i = 0; i < size; i++){
		val = (VALUE_LIMIT/2.0)*arm_sin_f32(theta);
		note_0[i] = (uint32_t)(val + (VALUE_LIMIT/2.0));
		theta += (2*PI)/(size);
	}
	theta = 0.0;
	val = 0.0;
	size = SIZE*2;
	for (int i = 0; i < size; i++){
		val = (VALUE_LIMIT/2.0)*arm_sin_f32(theta);
		val = (uint32_t)(val + (VALUE_LIMIT/2.0));
		note_1[i] = val;
		theta += (2*PI)/(size);
	}
	theta = 0.0;
	val = 0.0;
	size = SIZE*4;
	for (int i = 0; i < size; i++){
		val = (VALUE_LIMIT/2.0)*arm_sin_f32(theta);
		note_2[i] = (uint32_t)(val + (VALUE_LIMIT/2.0));
		theta += (2*PI)/(size);
	}
	theta = 0.0;
	val = 0.0;
	size = SIZE*8;
	for (int i = 0; i < size; i++){
		val = (VALUE_LIMIT/2.0)*arm_sin_f32(theta);
		note_3[i] = (uint32_t)(val + (VALUE_LIMIT/2.0));
		theta += (2*PI)/(size);
	}
	theta = 0.0;
	val = 0.0;
	size = SIZE*16;
	for (int i = 0; i < size; i++){
		val = (VALUE_LIMIT/2.0)*arm_sin_f32(theta);
		note_4[i] = (uint32_t)(val + (VALUE_LIMIT/2.0));
		theta += (2*PI)/(size);
	}
	theta = 0.0;
	val = 0.0;
	size = SIZE*32;
	for (int i = 0; i < size; i++){
		val = (VALUE_LIMIT/2.0)*arm_sin_f32(theta);
		note_5[i] = (uint32_t)(val + (VALUE_LIMIT/2.0));
		theta += (2*PI)/(size);
	}
}
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
