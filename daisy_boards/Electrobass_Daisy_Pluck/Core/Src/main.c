/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "i2c.h"
#include "rng.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "leaf.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SDRECORD 0
#define SAMPLE_RATE 48000

//#define MAPLE1
#define GREEN3
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t SPI_TX[32] __ATTR_RAM_D2;
uint8_t SPI_RX[32] __ATTR_RAM_D2;

#define NUM_ADC_CHANNELS 4
#define ADC_FRAME_SIZE 1
#define ADC_BUFFER_SIZE ADC_FRAME_SIZE * 2
#define NUM_STRINGS 4

uint32_t ADC_values[2 * ADC_BUFFER_SIZE] __ATTR_RAM_D2;

#define FILTER_ORDER 1
#define ATODB_TABLE_SIZE 25000
#define ATODB_TABLE_SIZE_MINUS_ONE 24999


#define MEDIUM_MEM_SIZE 300000
char mediumMemory[MEDIUM_MEM_SIZE] __ATTR_RAM_D1;
tMempool mediumPool;


int smoothedInt[NUM_STRINGS];
int smoothedInt2[NUM_STRINGS];
int dbSmoothedInt[NUM_STRINGS];
int tempAbsInt[NUM_STRINGS];
float atodbTable[ATODB_TABLE_SIZE];
int storedMaximums[NUM_STRINGS] = {10000.0f, 10000.0f, 10000.0f, 10000.0f};
float storedMaxFloats[NUM_STRINGS];
volatile uint16_t stringPositions[NUM_ADC_CHANNELS];
volatile uint16_t stringTouchRH[NUM_ADC_CHANNELS];
volatile uint16_t stringTouchRHPrev[NUM_ADC_CHANNELS];
volatile uint16_t stringTouchLH[NUM_ADC_CHANNELS];
volatile int didPlucked[NUM_ADC_CHANNELS];
volatile int stringSounding[NUM_ADC_CHANNELS];

int howManyFrames = 48000;
int brokedIt = 0;
int didPlucked2[4];
int pluckDelay[4];
int pluckValues[4];

float Dsmoothed;
float Dsmoothed2;
float dbSmoothed2;

float stringScaling[4] = {2.0f, 1.3f, 0.9f, 0.4f};
float stringScaling2[4] = {1.20f, 1.4f, 0.9f, 0.5f};
int armed[NUM_STRINGS] = {0,0,0,0};
float prevdbSmoothed2[NUM_STRINGS];
int threshOut = 0;
int stringMaxes[NUM_STRINGS] = {0,0,0,0};
int downCounter[NUM_STRINGS];
int armedCounter[NUM_STRINGS];
float slopeStorage[NUM_STRINGS];


tHighpass opticalHighpass[NUM_ADC_CHANNELS][FILTER_ORDER];
tHighpass EMHighpass[4];
tVZFilter opticalLowpass[NUM_ADC_CHANNELS][FILTER_ORDER];
tSlide fastSlide[NUM_ADC_CHANNELS];
tSlide slowSlide[NUM_ADC_CHANNELS];
tThreshold threshold[NUM_ADC_CHANNELS];
LEAF leaf;
int counter = 0;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
/* USER CODE BEGIN PFP */
void MPU_Conf(void);
float randomNumber(void);
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
  MPU_Conf();
  /* USER CODE END 1 */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

/* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_FMC_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_I2C1_Init();
  MX_RNG_Init();
  MX_ADC2_Init();
  MX_DAC1_Init();
  /* USER CODE BEGIN 2 */
  //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
  uint32_t tempFPURegisterVal = __get_FPSCR();
  tempFPURegisterVal |= (1<<24); // set the FTZ (flush-to-zero) bit in the FPU control register
  __set_FPSCR(tempFPURegisterVal);

  while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12) == 0)
  {
	  ;
  }
  for (int i = 0; i < 32; i++)
  {
	  SPI_TX[i] = i;
  }

  for (int i = 0; i < 8; i++)
  {
	  SPI_TX[i] = 0;
  }
  for (int i = 16; i < 24; i++)
  {
	  SPI_TX[i] = 0;
  }


  HAL_SPI_TransmitReceive_DMA(&hspi1, SPI_TX, SPI_RX, 32);
  //HAL_Delay(10);

  LEAF_init(&leaf, SAMPLE_RATE, mediumMemory, MEDIUM_MEM_SIZE, &randomNumber);

  for (int i = 0; i < NUM_ADC_CHANNELS; i++)
  {
  	tThreshold_init(&threshold[i],400.0f, 500.0f, &leaf);//.01 .05
  	tSlide_init(&fastSlide[i],1.0f,300.0f, &leaf); //500
  	tSlide_init(&slowSlide[i],1.0f,600.0f, &leaf); //500 //1000

  	storedMaxFloats[i] = (65535.0f / storedMaximums[i]);
  	for (int j = 0; j < FILTER_ORDER; j++)
  	{
  		tVZFilter_init(&opticalLowpass[i][j], Lowpass, 2000.0f, 0.2f, &leaf); //1000
  		tHighpass_init(&opticalHighpass[i][j], 50.0f, &leaf); //100
  	}
  }
  HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);
  HAL_DAC_Start(&hdac1, DAC_CHANNEL_2);
  LEAF_generate_atodb(atodbTable, ATODB_TABLE_SIZE);
  HAL_ADC_Start(&hadc2);
  HAL_ADCEx_MultiModeStart_DMA(&hadc1,(uint32_t*)&ADC_values,2 * ADC_BUFFER_SIZE);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);

	  HAL_Delay(100);

	  //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSE);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 6;
  RCC_OscInitStruct.PLL.PLLR = 8;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInitStruct.PLL3.PLL3M = 1;
  PeriphClkInitStruct.PLL3.PLL3N = 12;
  PeriphClkInitStruct.PLL3.PLL3P = 4;
  PeriphClkInitStruct.PLL3.PLL3Q = 8;
  PeriphClkInitStruct.PLL3.PLL3R = 16;
  PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_3;
  PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOWIDE;
  PeriphClkInitStruct.PLL3.PLL3FRACN = 2360;
  PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL3;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void MPU_Conf(void)
 {
	//code from Keshikan https://github.com/keshikan/STM32H7_DMA_sample
  //Thanks, Keshikan! This solves the issues with accessing the SRAM in the D2 area properly. -JS
	//should test the different possible settings to see what works best while avoiding needing to manually clear the cache -JS

	MPU_Region_InitTypeDef MPU_InitStruct;

	  HAL_MPU_Disable();

	  MPU_InitStruct.Enable = MPU_REGION_ENABLE;

	  //D2 Domain�SRAM1
	  MPU_InitStruct.BaseAddress = 0x30000000;
	  // Increased region size to 256k. In Keshikan's code, this was 512 bytes (that's all that application needed).
	  // Each audio buffer takes up the frame size * 8 (16 bits makes it *2 and stereo makes it *2 and double buffering makes it *2)
	  // So a buffer size for read/write of 4096 would take up 64k = 4096*8 * 2 (read and write).
	  // I increased that to 256k so that there would be room for the ADC knob inputs and other peripherals that might require DMA access.
	  // we have a total of 256k in SRAM1 (128k, 0x30000000-0x30020000) and SRAM2 (128k, 0x30020000-0x3004000) of D2 domain.
	  // There is an SRAM3 in D2 domain as well (32k, 0x30040000-0x3004800) that is currently not mapped by the MPU (memory protection unit) controller.

	  MPU_InitStruct.Size = MPU_REGION_SIZE_256KB;

	  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;

	  //AN4838
	  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
	  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
	  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;

	  //Shared Device
//	  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
//	  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
//	  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
//	  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;


	  MPU_InitStruct.Number = MPU_REGION_NUMBER0;

	  MPU_InitStruct.SubRegionDisable = 0x00;


	  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;


	  HAL_MPU_ConfigRegion(&MPU_InitStruct);


	  //now set up D3 domain RAM

	  MPU_InitStruct.Enable = MPU_REGION_ENABLE;

	  //D3 Domain�SRAM
	  MPU_InitStruct.BaseAddress = 0x38000000;


	  MPU_InitStruct.Size = MPU_REGION_SIZE_64KB;

	  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;

	  //AN4838
	  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
	  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
	  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;

	  //Shared Device
 //	  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
 //	  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
 //	  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
 //	  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;


	  MPU_InitStruct.Number = MPU_REGION_NUMBER1;

	  MPU_InitStruct.SubRegionDisable = 0x00;


	  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;


	  HAL_MPU_ConfigRegion(&MPU_InitStruct);


	  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

float randomNumber(void) {

	uint32_t rand;
	HAL_RNG_GenerateRandomNumber(&hrng, &rand);
	float num = (float)rand * INV_TWO_TO_32;
	return num;
}

volatile int totalMaximums[NUM_STRINGS];
volatile float pickupMaximums[NUM_STRINGS] = {0.0f, 0.0f, 0.0f, 0.0f};
volatile int outcountdown[NUM_STRINGS] = {-1,-1,-1,-1};

int stringStates[4];
uint16_t stringPressed[4];
int spiBuffer = 0;
int didPluckedWaiting[4] = {0,0,0,0};
int didPluckedWaitingCounter[4] = {0,0,0,0};
int openstrings[4] = {0,0,0,0};
int hammerOnWait[4] = {0,0,0,0};
int hammerOnWaiting[4] = {0,0,0,0};
int pullOffWait[4] = {-1,-1,-1,-1};

uint8_t stringFrozen[4] = {0,0,0,0};
int lastPlucked[4];

int test1 = 0;
int test2 = 0;
int test3 = 0;
int test4 = 0;
int test5 = 0;

uint16_t testAnalog = 0;
int testAnalog2 = 0;

float maxFlo[NUM_STRINGS] = {0.0f,0.0f,0.0f,0.0f};
float minFlo[NUM_STRINGS] = {0.0f,0.0f,0.0f,0.0f};
uint8_t numQuietFails[NUM_STRINGS] = {0,0,0,0};
uint8_t countingDown[NUM_STRINGS] = {0,0,0,0};
uint16_t pluckWaitCount[NUM_STRINGS] = {0,0,0,0};
uint8_t pluckWaitState[NUM_STRINGS] = {0,0,0,0};

int attackDetectPeak2 (int whichString, uint16_t tempInt)
{
	float output = -1;


	//if (stringTouchRH[whichString])
	{
		//stringSounding[whichString] = 0;
	}

	if (whichString == 0)
	{
		//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
	}
	float tempSamp = (((float)tempInt - TWO_TO_15) * INV_TWO_TO_15);

	for (int k = 0; k < FILTER_ORDER; k++)
	{
		// a highpass filter, remove any slow moving signal (effectively centers the signal around zero and gets rid of the signal that isn't high frequency vibration) cutoff of 100Hz, // applied 8 times to get rid of a lot of low frequency bumbling around
		tempSamp = tHighpass_tick(&opticalHighpass[whichString][k], tempSamp * 0.5f);
		tempSamp = tVZFilter_tickEfficient(&opticalLowpass[whichString][k], tempSamp);
	}
/*
	if (tempSamp > 1.0f)
	{
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_11);
	}
	else if (tempSamp < -1.0f)
	{
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_11);
	}
	*/
	testAnalog2 = (tempSamp * TWO_TO_15) + TWO_TO_15;

	//float tempAbs = fabsf(tempSamp);
	//take only postive half of wave, since negative half is messed up and clipped by poor opamp choice on this prototype
	float tempAbs  = LEAF_clip(0.0f, tempSamp, 1.0f);
	tempAbsInt[whichString] = (tempAbs * (TWO_TO_16 - 1));
	Dsmoothed = tSlide_tick(&fastSlide[whichString], tempAbs);
	smoothedInt[whichString] = (Dsmoothed * (TWO_TO_16 - 1));
	Dsmoothed2 = tSlide_tick(&slowSlide[whichString], Dsmoothed);

	Dsmoothed2 = LEAF_clip(0.0f, Dsmoothed2, 1.0f);
	smoothedInt2[whichString] = (Dsmoothed2 * (TWO_TO_16 - 1));


	//dbSmoothed2 = atodb(Dsmoothed2);
	//80db
	dbSmoothed2 = LEAF_clip(-120.0f, atodbTable[(uint32_t)(Dsmoothed2 * ATODB_TABLE_SIZE_MINUS_ONE)], 12.0f);
	dbSmoothedInt[whichString] = dbSmoothed2 * 100.0f;
	//dbSmoothed2 = LEAF_clip(-50.f, dbSmoothed2, 12.0f);
	//get the slope
	float slope = (dbSmoothed2 - prevdbSmoothed2[whichString]);
	slopeStorage[whichString] = slope;
	float integerVersion = Dsmoothed2 * (TWO_TO_16 - 1);
	//uint16_t toDac1 = ((uint16_t)LEAF_clip(-2048.0f, slope * 100.0f, 2048.0f))+2048;
	//uint16_t toDac1 = LEAF_clip(-4095, dbSmoothedInt[whichString]/3, 0) + 4095;
	//uint16_t toDac2 = smoothedInt2[whichString] >> 4;
	//uint16_t toDac2 = LEAF_clip(-2047, slope * 200.0f , 2047) + 2047;
	uint16_t toDac2 = TWO_TO_12 * (2.0f * maxFlo[whichString]);// - minFlo[whichString]);;

	if (whichString == 0)
	{
		//HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, testAnalog2 >> 4);
		//HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_2, DAC_ALIGN_12B_R, smoothedInt2[whichString] >> 4);
		HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_2, DAC_ALIGN_12B_R, toDac2);
	}
	//if (whichString == 0)
	{
		//HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, toDac1);
	}

	if (pluckWaitState[whichString] > 0)
	{
		pluckWaitCount[whichString]++;
		if (pluckWaitCount[whichString] > 1000)
		{
			pluckWaitState[whichString] = 0;
		}
	}

	threshOut = tThreshold_tick(&threshold[whichString], integerVersion);
	if (whichString == 0)
	{
		if (stringTouchRH[whichString])
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
		}

		if (threshOut > 0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
		}
		if (stringSounding[whichString] == 0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
		}
	}
	//if (whichString == 1)
	{
		//if (threshOut > 0)
		{
			//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
		}
		//else
		{
			//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
		}
	}
	if ((slope > 0.2f) && (threshOut > 0) && (!armed[whichString]) && (!stringStates[whichString]))
	{
		armed[whichString] = 1;
		pickupMaximums[whichString] = 0.0f;
		stringMaxes[whichString] = 0;
		maxFlo[whichString] = 0.0f;
		minFlo[whichString] = 0.0f;
		countingDown[whichString] = 0;
		outcountdown[whichString] = -1;
		if (whichString == 0)
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
		}
		numQuietFails[whichString] = 0;
	}

	if (armed[whichString] == 1)
	{
		if (tempSamp > maxFlo[whichString])
		{
			maxFlo[whichString] = tempSamp;
		}
		if (tempSamp < minFlo[whichString])
		{
			minFlo[whichString] = tempSamp;
		}

		if (integerVersion > stringMaxes[whichString])
		{
			stringMaxes[whichString] = integerVersion;
		}
		armedCounter[whichString]++;

		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);

		if (slope <= 0.0f)
		{
			downCounter[whichString]++;
			//if (whichString == 1)
			{
				//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
			}
		}
		if (slope > 0.01f)
		{
			downCounter[whichString] = 0;
			//if (whichString == 1)
			{
				//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
			}
		}
		if (whichString == 0)
		{
			HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, downCounter[whichString]*5);
		}

		if (downCounter[whichString] > 80) // was 100
		{

			if ((!stringTouchRH[whichString]) && (pluckWaitState[whichString] == 0))
			{
				//output = (float)stringMaxes[whichString];
				output = TWO_TO_16 * (2.0f * maxFlo[whichString]);// - minFlo[whichString]);

				if (storedMaximums[whichString] < output)
				{
					storedMaximums[whichString] = output; // TODO:new
				}

				output = LEAF_clip(0.0f, output, 65535.0f);

				testAnalog = output;

				armed[whichString] = 0;
				armedCounter[whichString] = 0;
				downCounter[whichString] = 0;
				stringMaxes[whichString] = 0;
				pluckWaitState[whichString] = 1;
				pluckWaitCount[whichString] = 0;
				if ((whichString == 0) && (output > 0))
				{
					//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);


					//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
				}
				if (whichString == 0)
				{
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
					//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
				}
				if (whichString == 0)
				{
					//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
				}
			}

			if (downCounter[whichString] > 200)
			{
				armed[whichString] = 0;
				armedCounter[whichString] = 0;
				downCounter[whichString] = 0;
				stringMaxes[whichString] = 0;

				if (whichString == 0)
				{
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
					//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
				}
				if (whichString == 0)
				{
					//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
				}
			}



		}

#if 0
		//slope went down but string was not released, based on rh touch data. So give up on this peak - probably not a pluck
		if (downCounter[whichString] > 400)
		{
			//found a peak?
			//output = stringMaxes[whichString];
			//output = (float)stringMaxes[whichString];

			//output = LEAF_clip(0.0f, output, 65535.0f);

			armed[whichString] = 0;
			armedCounter[whichString] = 0;
			downCounter[whichString] = 0;
			stringMaxes[whichString] = 0;

			//if (whichString == 1)
			{
				//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
			}

			if (whichString == 0)
			{
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
			}
			if (whichString == 0)
			{
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
			}

		}
		if ((outcountdown[whichString] > 0) && (countingDown[whichString]))
		{
			outcountdown[whichString]--;

		}
		else if ((!stringTouchRH[whichString]) && stringTouchRHPrev[whichString])
		{
			//right hand released the string - time to make a pluck!
			//found a peak?
			//output = stringMaxes[whichString];
			if (whichString == 0)
			{
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
			}
			outcountdown[whichString] = 300; //was 64/maybe sometimes gets rh touch release a little early if sensitivity is too low? Saw this on a scope reading and it was 1.4ms early so adding a 1.4ms delay to compensate
			countingDown[whichString] = 1;
		}
		else if ((outcountdown[whichString] == 0) || ((armedCounter[whichString] == 1) && (!stringTouchRH[whichString])))
		{
			//output = (float)stringMaxes[whichString];
			output = TWO_TO_16 * (maxFlo[whichString] - minFlo[whichString]);

			if (output < 400.0f)
			{
				if (numQuietFails[whichString] == 0)
				{
					outcountdown[whichString] = 200;
					numQuietFails[whichString] = 1;
				}
				else
				{
					output = -1.0f;
					armed[whichString] = 0;
					armedCounter[whichString] = 0;
					downCounter[whichString] = 0;
					stringMaxes[whichString] = 0;
					outcountdown[whichString] = -1;
					countingDown[whichString] = 0;
					if ((whichString == 0) && (output > 0))
					{
						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
					}
					if (whichString == 0)
					{
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
					}
					if (whichString == 0)
					{
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
					}
				}
			}
			else
			{
				if (storedMaximums[whichString] < output)
				{
					storedMaximums[whichString] = output; // TODO:new
				}

				output = LEAF_clip(0.0f, output, 65535.0f);

				testAnalog = output;
				//if (whichString == 0)
				//{
				//	HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, (uint16_t)testAnalog >> 4);
				//}
				armed[whichString] = 0;
				armedCounter[whichString] = 0;
				downCounter[whichString] = 0;
				stringMaxes[whichString] = 0;
				outcountdown[whichString] = -1;
				countingDown[whichString] = 0;
				if ((whichString == 0) && (output > 0))
				{
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
				}
				if (whichString == 0)
				{
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
				}
				if (whichString == 0)
				{
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
				}
			}

		}

#endif
	}
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, pluckWaitState[0]);
	prevdbSmoothed2[whichString] = dbSmoothed2;
	return (int)output;
}


void ADC_Frame(int offset)
{
	//HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_11);
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
	int changeHappened = 0;
	//sampRecords[currentSamp] = frameCount;
	//currentSamp++;
	uint16_t adcBytes[4];

	adcBytes[0] = ADC_values[offset*2] & 65535;
	adcBytes[1] = ADC_values[offset*2 + 1] & 65535;
	adcBytes[2] = ADC_values[offset*2] >> 16;
	adcBytes[3] = ADC_values[offset*2 + 1] >> 16;

	//HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_2, DAC_ALIGN_12B_R, adcBytes[0] >> 4);
	//HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, adcBytes[1] >> 4);
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
	for (int i = offset; i < ADC_FRAME_SIZE + offset; i++)
	{
		//for (int j = 0; j < NUM_ADC_CHANNELS; j++)
		if (howManyFrames > 0)
		{
			howManyFrames--;
		}
		for (int j = 0; j < 4; j++)
		{
			uint16_t tempInt = adcBytes[j];

			didPlucked[j] = attackDetectPeak2(j, tempInt);

			//stringTouchRH[j] = (SPI_RX[(16*spiBuffer) + 8] >> (j+4)) & 1;
			//stringTouchLH[j] = (SPI_RX[(16*spiBuffer) + 8] >> j) & 1;
			//int currentnumber = (j*2) + (16*spiBuffer);
			//stringPressed[j] = (SPI_RX[currentnumber] << 8) + SPI_RX[currentnumber+1];

			/*
			if (didPlucked2[j] < 0)
			{
				didPlucked2[j] = 0;
			}
			//didPlucked2[j] = tPluckDetectorInt_tick(&myPluck[j], tempInt);
			if (didPlucked[j] < 0)
			{
				didPlucked[j] = 0;
			}
			*/
			/*
			else if (didPlucked[j] > 0)
			{
				pluckDelay[j] = 1;
				pluckValues[j] = didPlucked[j];
			}

			int doIt = 0;
*/
			if (howManyFrames == 0)
			{
				/*
				if (pluckDelay[j] > 128)
				{
					doIt = 1;
					pluckDelay[j] = 0;
				}
				if (pluckDelay[j] > 0)
				{
					pluckDelay[j]++;
				}
*/

				//if (stringTouchLH[j] || stringTouchRH[j])
				//{
					//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
				//}
				int LHmuted = 0;
				//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, (GPIO_PinState) stringTouchRH[1]);
				if (stringTouchLH[j] && (stringPressed[j] == 65535))
				{
					LHmuted = 1;
				}
				else
				{
					LHmuted = 0;
				}




/*

				if (((didPlucked[j] > 0) && (!stringSounding[j])) && ((LHmuted)))
				{
					//got an attack but string is muted, hold this for a ms in case the touch sensor data is coming a little late
					didPluckedWaiting[j] = didPlucked[j];
					didPluckedWaitingCounter[j] = 00;//500
				}
				if (didPluckedWaitingCounter[j] == 0)
				{
					didPluckedWaiting[j] = -1;
				}
				if ((didPluckedWaiting[j] >= didPlucked[j]) && (didPluckedWaitingCounter[j] > 0) && (!armed[j]))
				{
					//didPlucked[j] = didPluckedWaiting[j];
					didPluckedWaitingCounter[j]--;
					if (!(LHmuted) && (!stringTouchRH[j]))
					{
						didPlucked[j] = didPluckedWaiting[j];
						didPluckedWaiting[j] = -1;
					}
				}
				else
				{
					didPluckedWaiting[j] = -1;
				}
*/				//if (j == 1)
				{
					//HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_2, DAC_ALIGN_12B_R, (uint16_t)hammerOnWait[j]*10);
				}

				//add LH mute wait of at least 6 ms, maybe 10ms
				if (((didPlucked[j] > 0)) && (!stringSounding[j]) && (!stringTouchRH[j]))// && (!LHmuted))
				{
					if (didPlucked[j] > totalMaximums[j])
					{
						totalMaximums[j] = didPlucked[j];
					}
					//didPlucked[j] = (float)didPlucked[j];// * storedMaxFloats[j];
					if (didPlucked[j] > 65535)
					{
						didPlucked[j] = 65535;
					}
					if (stringPressed[j] == 65535)
					{
						openstrings[j] = 1;
						hammerOnWait[j] = 400;
					}
					else
					{
						openstrings[j] = 0;
					}
					stringStates[j] = didPlucked[j];
					//SPI_PLUCK_TX[(j * 2)] = (didPlucked[j] >> 8);
					//SPI_PLUCK_TX[(j * 2)] = (didPlucked[j] & 0xff);

					//a pluck happened! send a message over SPI to the other ICs
					//TODO: a pluck message

					if (j == 0)
					{
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
						//HAL_DAC_SetValue(&hdac1, 0, DAC_ALIGN_12B_R, didPlucked[j] >> 4);
					}
					//SPI_TX[j*2+(16*spiBuffer)] = (uint8_t) (didPlucked[j] >> 8); //high byte
					//SPI_TX[j*2+1+(16*spiBuffer)] = (uint8_t) (didPlucked[j] & 0xff); //low byte


					//HAL_SPI_Transmit_DMA(&hspi1, SPI_PLUCK_TX, 20);
					/*
					SPI_PLUCK_TX[0] = j;
					SPI_PLUCK_TX[1] = (uint8_t) (didPlucked[j] >> 8); //high byte
					SPI_PLUCK_TX[2] = (uint8_t) (didPlucked[j] & 0xff); //low byte
					SPI_PLUCK_TX[3] = 0;
					*/
					changeHappened = 1;
					stringSounding[j] = 1;
					lastPlucked[j] = stringStates[j];
					//HAL_SPI_Transmit_DMA(&hspi1, SPI_PLUCK_TX, 4);
				}

				//if you touch with right hand that's a mute
				if ((stringTouchRH[j]) && (stringSounding[j]))
				{
					//a note-off happened! send a message over SPI to the other ICs

					if (j == 0)
					{
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
						//HAL_DAC_SetValue(&hdac1, 0, DAC_ALIGN_12B_R, 0);
					}
					//HAL_SPI_Transmit_DMA(&hspi1, SPI_PLUCK_TX, 20);
					stringStates[j] = 0;
					changeHappened = 1;
					pickupMaximums[j] = 0.0f;
					stringSounding[j] = 0;
					if (j == 1)
					{
						//HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0);
					}
				}

				//whenever the Left Hand mute isn't active, reset the hammerOn counter
				if (!LHmuted)
				{
					hammerOnWait[j] = 400;
				}
				//currently testing removal of left hand mute handling from the stm32 -
				//the idea is to instead handle all left hand muting on the PSOC, taking advantage of the more immediate touch and fretting data.

#if 0
				//if you have gotten a Left Hand mute signal and the string is either already sounding or just sounded (looks the same from this perspective)
				// then countdown for hammer ons or pull offs (so that the mute doesn't stop the sound)
				// might make sense instead to always mute the string and do a re-attack
				else if (LHmuted && stringSounding[j])
				{
					if (hammerOnWait[j] > 0)
					{
						hammerOnWait[j]--;
						hammerOnWaiting[j] = 1;
						stringFrozen[j] = 1;
					}
					else
					{
						if (pullOffWait[j] == -1)
						{
							openstrings[j] = 1;
							pullOffWait[j] = 500;
							stringFrozen[j] = 1;
						}
						if (pullOffWait[j] > 0)
						{
							pullOffWait[j]--;
							stringFrozen[j] = 1;
						}

						if (pullOffWait[j] == 0)
						{

							if (j == 1)
							{
								HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
								//HAL_DAC_SetValue(&hdac1, 0, DAC_ALIGN_12B_R, 0);
							}
							//HAL_SPI_Transmit_DMA(&hspi1, SPI_PLUCK_TX, 20);
							stringStates[j] = 0;
							changeHappened = 1;
							pickupMaximums[j] = 0.0f;
							stringSounding[j] = 0;
							pullOffWait[j] = -1;
							hammerOnWait[j] = -1;
							hammerOnWaiting[j] = 0;
							stringFrozen[j] = 0;
							if (j == 1)
							{
								//HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0);
							}
						}
					}
				}
#endif
				#if SDRECORD
				if (SDReady)
				{
					writeToSD(SDWriteIndex, tempInt, j, stringSounding[j]);

					if (memoryPointer >= ((LARGE_MEM_SIZE/2) - 3000))
					{
						finishSD = 1;
						HAL_ADC_Stop(&hadc1);
						//HAL_SAI_DMAStop(&hsai_BlockA1);
						//HAL_SAI_DMAStop(&hsai_BlockB1);
					}
				}
				#endif
/*
				if (memoryPointer < ((LARGE_MEM_SIZE / 2) - 10))
				{
					largeMemory[memoryPointer++] = (uint16_t)tempInt;
					largeMemory[memoryPointer++] = (uint16_t)didPlucked[j];
					largeMemory[memoryPointer++] = (uint16_t)(myPluck[j]->ready_for_pluck);
					largeMemory[memoryPointer++] = (uint16_t)(myPluck[j]->midpoint_estimate);
					largeMemory[memoryPointer++] = (uint16_t)didPlucked2[j];
					largeMemory[memoryPointer++] = (uint16_t)armed[j];
					largeMemory[memoryPointer++] = (uint16_t)downCounter[j];
					largeMemory[memoryPointer++] = (uint16_t)((slopeStorage[j] * 4096.0f) + 2048.0f);
					largeMemory[memoryPointer++] = (uint16_t)stringTouchRH[j];
					largeMemory[memoryPointer++] = (uint16_t)stringSounding[j];
				}
				else
				{
					writeSD();

					while(1)
					{
						//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
					}
				}

*/
				stringTouchRHPrev[j] = stringTouchRH[j];
				/*
				if (j == 0)
				{
					if (stringSounding[j])
					{
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
					}
					else
					{
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
					}
				}
				*/
			}
			//itoa(SDWriteIndex, wtext, 4);



		}

	}
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);

	if (changeHappened)
	{
		//HAL_SPI_Transmit_DMA(&hspi1, SPI_PLUCK_TX, 22);
	}
}

void ADC_EM(int offset)
{
#if 0
	for (int i = offset; i < ADC_FRAME_SIZE + offset; i++)
	{
		for (int j = 0; j < NUM_ADC_CHANNELS2; j++)
		{
			int tempInt = ADC_values2[(i*NUM_ADC_CHANNELS2) + j];
			float tempSamp = (((float)tempInt - TWO_TO_15) * INV_TWO_TO_15) * 2.5f;
			tempSamp = tHighpass_tick(&EMHighpass[j], tempSamp);
			float absFloat = fabsf(tempSamp);
			if (absFloat > pickupMaximums[j])
			{
				pickupMaximums[j] = absFloat;
			}

		}
	}
#endif
}
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{

	if (hadc == &hadc1)
	{
		ADC_Frame(ADC_FRAME_SIZE);
	}

}
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
	if (hadc == &hadc1)
	{
		ADC_Frame(0);
	}

}
void HAL_ADC_Error(ADC_HandleTypeDef *hadc)
{

}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	spiBuffer = 1;
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
	for (int j = 0; j < 4; j++)
	{
		stringTouchLH[j] = (SPI_RX[24] >> (j+4)) & 1;
		stringTouchRH[j] = (SPI_RX[24] >> j) & 1;
		int currentnumber = (j*2) + 16;
		stringPressed[j] = (SPI_RX[currentnumber] << 8) + SPI_RX[currentnumber+1];
		//if (stringTouchLH[j] || stringTouchRH[j])
		//{
			//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
		//}

		SPI_TX[j*2+(16*spiBuffer)] = (uint8_t) (stringStates[j] >> 8); //high byte
		SPI_TX[j*2+1+(16*spiBuffer)] = (uint8_t) (stringStates[j] & 0xff); //low byte
		//SPI_TX[j*2+8+(16*spiBuffer)] = (uint8_t) (stringFrozen[j]); //high byte
	}
	//HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
}

void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	spiBuffer = 0;
   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
	for (int j = 0; j < 4; j++)
	{
		stringTouchLH[j] = (SPI_RX[8] >> (j+4)) & 1;
		stringTouchRH[j] = (SPI_RX[8] >> j) & 1;
		stringPressed[j] = (SPI_RX[j*2] << 8) + SPI_RX[(j*2)+1];
		//if (stringTouchLH[j] || stringTouchRH[j])
		//{
			//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
		//}
		SPI_TX[j*2+(16*spiBuffer)] = (uint8_t) (stringStates[j] >> 8); //high byte
		SPI_TX[j*2+1+(16*spiBuffer)] = (uint8_t) (stringStates[j] & 0xff); //low byte
		//SPI_TX[j*2+8+(16*spiBuffer)] = (uint8_t) (stringFrozen[j]); //high byte
	}
	//HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
}

// EXTI Line12 External Interrupt ISR Handler CallBackFun
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == GPIO_PIN_12) // If The INT Source Is EXTI Line12
	{

		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12) == 0) {
			HAL_SPI_Abort(&hspi1);
			__HAL_SPI_CLEAR_OVRFLAG(&hspi1);
		} else {
			for (int i = 0; i < 32; i++) {
				SPI_TX[i] = i;
			}
			for (int i = 0; i < 8; i++) {
				SPI_TX[i] = 0;
			}
			for (int i = 16; i < 24; i++) {
				SPI_TX[i] = 0;
			}
			HAL_SPI_TransmitReceive_DMA(&hspi1, SPI_TX, SPI_RX, 32);
		}
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
