/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "dac.h"
#include "dma.h"
#include "fatfs.h"
#include "i2c.h"
#include "quadspi.h"
#include "rng.h"
#include "sai.h"
#include "sdmmc.h"
#include "spi.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "leaf.h"
#include "codec.h"
#include "audio.h"
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
void PeriphCommonClock_Config(void);
/* USER CODE BEGIN PFP */
void MPU_Conf(void);
static void FS_FileOperations(void);
void parse_preset(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t SPI_TX[32] __ATTR_RAM_D2;
uint8_t SPI_RX[32] __ATTR_RAM_D2;

#define MAX_WAV_FILES 8
FILINFO fno __ATTR_RAM_D1;
DIR dir __ATTR_RAM_D1;
const TCHAR path = 0;
uint32_t waves[MAX_WAV_FILES][4];
uint32_t numWaves = 0;
uint32_t OutOfSpace = 0;
uint32_t tooBigForScratch = 0;
uint32_t memoryPointer = 0;
uint8_t counter = 0;

volatile uint8_t writingPreset = 0;
volatile uint8_t muteAudio = 0;
FIL fdst;
volatile uint8_t buffer[4096];
volatile uint16_t bufferPos = 0;
FRESULT res;


param params[NUM_PARAMS];

float resTable[2048];
float envTimeTable[2048];
float lfoRateTable[2048];

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
  //SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  __enable_irq();
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
  MX_DAC1_Init();
  MX_FMC_Init();
  MX_I2C2_Init();
  MX_QUADSPI_Init();
  MX_SAI1_Init();
  MX_SDMMC1_SD_Init();
  MX_SPI1_Init();
  MX_I2C1_Init();
  MX_RNG_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */



  uint32_t tempFPURegisterVal = __get_FPSCR();
  tempFPURegisterVal |= (1<<24); // set the FTZ (flush-to-zero) bit in the FPU control register
  __set_FPSCR(tempFPURegisterVal);


  while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == 0)
   {
 	  ;
   }


  for (int i = 0; i < 4096; i++)
  {
	  buffer[i] = 0;
  }
  LEAF_generate_table_skew_non_sym(&resTable, 0.01f, 10.0f, 0.5f, 2048);
  LEAF_generate_table_skew_non_sym(&envTimeTable, 0.0f, 20000.0f, 4000.0f, 2048);
  LEAF_generate_table_skew_non_sym(&lfoRateTable, 0.0f, 30.0f, 2.0f, 2048);

  parse_preset();

  codec_init(&hi2c2);

  audio_init(&hsai_BlockB1, &hsai_BlockA1);

  for (int i = 0; i < 32; i++)
  {
	  SPI_TX[i] = counter++;
  }




  HAL_SPI_TransmitReceive_DMA(&hspi1, SPI_TX, SPI_RX, 32);



  HAL_Delay(10);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
/*
	 if(BSP_SD_IsDetected())
	 {

		 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
	     FS_FileOperations();

	 }
	 else
	 {
		 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
	 }

*/
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /*
	  while(1)
	  {
		  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
		  HAL_Delay(100);
	  }
	  */
	  //HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
	  //HAL_Delay(200);
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
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_FMC|RCC_PERIPHCLK_SDMMC
                              |RCC_PERIPHCLK_SAI1;
  PeriphClkInitStruct.PLL2.PLL2M = 1;
  PeriphClkInitStruct.PLL2.PLL2N = 12;
  PeriphClkInitStruct.PLL2.PLL2P = 8;
  PeriphClkInitStruct.PLL2.PLL2Q = 2;
  PeriphClkInitStruct.PLL2.PLL2R = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_3;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 4096;
  PeriphClkInitStruct.PLL3.PLL3M = 1;
  PeriphClkInitStruct.PLL3.PLL3N = 12;
  PeriphClkInitStruct.PLL3.PLL3P = 4;
  PeriphClkInitStruct.PLL3.PLL3Q = 8;
  PeriphClkInitStruct.PLL3.PLL3R = 16;
  PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_3;
  PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOWIDE;
  PeriphClkInitStruct.PLL3.PLL3FRACN = 2360;
  PeriphClkInitStruct.FmcClockSelection = RCC_FMCCLKSOURCE_PLL2;
  PeriphClkInitStruct.SdmmcClockSelection = RCC_SDMMCCLKSOURCE_PLL2;
  PeriphClkInitStruct.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLL3;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
float randomNumber(void) {

	uint32_t rand;
	HAL_RNG_GenerateRandomNumber(&hrng, &rand);
	float num = (float)rand * INV_TWO_TO_32;
	return num;
}


static void FS_FileOperations(void)
{
	HAL_Delay(300);
	disk_initialize(0);

    disk_status(0);
    //if (statusH != RES_OK)
    //{
      //ShowDiskStatus(status);
    //}


	if(f_mount(&SDFatFS,  SDPath, 1) == FR_OK)
	{

		FRESULT res;

		uint32_t fileIndex = 0;

		/* Start to search for wave files */

		res = f_findfirst(&dir, &fno, SDPath, "*.wav");

		/* Repeat while an item is found */
		while (fno.fname[0])
		{
		  if(res == FR_OK)
		  {
			if((fileIndex < MAX_WAV_FILES) && (OutOfSpace == 0))
			{
				if(f_open(&SDFile, fno.fname, FA_OPEN_ALWAYS | FA_READ) == FR_OK)
				{

					waves[fileIndex][0] = (uint32_t)memoryPointer;

					//if (readWave(&SDFile) == 1)
					{

						//waves[fileIndex][1] = header.channels;
						//waves[fileIndex][2] = header.sample_rate;
						//uint32_t LengthInFloats = (uint32_t)memoryPointer - waves[fileIndex][0];
						//waves[fileIndex][3] = LengthInFloats;
						fileIndex++;
						numWaves++;
					}


					f_close(&SDFile);

					/* Search for next item */


					res = f_findnext(&dir, &fno);
				}
			}
			else
			{
				break;
			}

		  }
		  else
		  {
			break;
		  }
		}
		f_closedir(&dir);

	}
	f_mount(0, "", 0); //unmount
}

#define SDRAM_MODEREG_BURST_LENGTH_2 ((1 << 0))
#define SDRAM_MODEREG_BURST_LENGTH_4 ((1 << 1))

#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL ((0 << 3))

#define SDRAM_MODEREG_CAS_LATENCY_3 ((1 << 4) | (1 << 5))

#define SDRAM_MODEREG_OPERATING_MODE_STANDARD ()

#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE ((1 << 9))
#define SDRAM_MODEREG_WRITEBURST_MODE_PROG_BURST ((0 << 9))

void SDRAM_init()
{
	    	FMC_SDRAM_CommandTypeDef Command;

	        __IO uint32_t tmpmrd = 0;
	        /* Step 3:  Configure a clock configuration enable command */
	        Command.CommandMode            = FMC_SDRAM_CMD_CLK_ENABLE;
	        Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
	        Command.AutoRefreshNumber      = 1;
	        Command.ModeRegisterDefinition = 0;

	        /* Send the command */
	        HAL_SDRAM_SendCommand(&hsdram1, &Command, 0x1000);

	        /* Step 4: Insert 100 ms delay */
	        HAL_Delay(100);


	        /* Step 5: Configure a PALL (precharge all) command */
	        Command.CommandMode            = FMC_SDRAM_CMD_PALL;
	        Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
	        Command.AutoRefreshNumber      = 1;
	        Command.ModeRegisterDefinition = 0;

	        /* Send the command */
	        HAL_SDRAM_SendCommand(&hsdram1, &Command, 0x1000);

	        /* Step 6 : Configure a Auto-Refresh command */
	        Command.CommandMode            = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	        Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
	        Command.AutoRefreshNumber      = 4;
	        Command.ModeRegisterDefinition = 0;

	        /* Send the command */
	        HAL_SDRAM_SendCommand(&hsdram1, &Command, 0x1000);

	        /* Step 7: Program the external memory mode register */
	        tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_4
	                 | SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL | SDRAM_MODEREG_CAS_LATENCY_3
	                 | SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
	        //SDRAM_MODEREG_OPERATING_MODE_STANDARD | // Used in example, but can't find reference except for "Test Mode"

	        Command.CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;
	        Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
	        Command.AutoRefreshNumber      = 1;
	        Command.ModeRegisterDefinition = tmpmrd;

	        /* Send the command */
	        HAL_SDRAM_SendCommand(&hsdram1, &Command, 0x1000);

	        //HAL_SDRAM_ProgramRefreshRate(hsdram, 0x56A - 20);
	        HAL_SDRAM_ProgramRefreshRate(&hsdram1, 0x81A - 20);

}

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

	 	  //D2 Domain�SRAM1
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



void handleSPI(uint8_t offset)
{
	// if the first number is a 1 then it's a midi note/ctrl/bend message
	if (SPI_RX[offset] == 1)
	{
		//got a change!
		 HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);

		 uint8_t currentByte = offset+1;

		 while (SPI_RX[currentByte] != 0)
		 {
			 if (SPI_RX[currentByte] == 0x90)
			 {
				 sendNoteOn(SPI_RX[currentByte+1], SPI_RX[currentByte+2]);
			 }
			 else if (SPI_RX[currentByte] == 0xb0)
			 {
				 sendCtrl(SPI_RX[currentByte+1], SPI_RX[currentByte+2]);
			 }
			 else if (SPI_RX[currentByte] == 0xe0)
			 {
				 sendPitchBend(SPI_RX[currentByte+1], SPI_RX[currentByte+2]);
			 }
			 currentByte = currentByte+3;
		 }
		 //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
	}
	// if the first number is a 2 then it's a preset write
	else if (SPI_RX[offset] == 2)
	{
		//got a new preset to write to memory
		 //HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);

		 //if you aren't already writing a preset to memory, start the process
		 if (!writingPreset)
		 {
			 writingPreset = 1; // set the flag to let the mcu know that a preset write is in progress
			 muteAudio = 1;
			 //write the raw data as a preset number on the SD card
			 bufferPos = 0;
			 /*
			 if(f_mount(&SDFatFS,  SDPath, 1) == FR_OK)
			 {
				 res = f_open(&fdst, "P1.txt", FA_CREATE_ALWAYS | FA_WRITE);
			 }
			 */
		 }

		 uint8_t currentByte = offset+2;

		 for (int i = 0; i < 14; i++)
		 {
			 buffer[bufferPos++] = SPI_RX[currentByte + i];
			 //f_putc(SPI_RX[currentByte + i], &fdst);

		 }
		 //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);



		 /*
		 while (SPI_RX[currentByte] != 0)
		 {
			 if (SPI_RX[currentByte] == 0x90)
			 {
				 sendNoteOn(SPI_RX[currentByte+1], SPI_RX[currentByte+2]);
			 }
			 else if (SPI_RX[currentByte] == 0xb0)
			 {
				 sendCtrl(SPI_RX[currentByte+1], SPI_RX[currentByte+2]);
			 }
			 else if (SPI_RX[currentByte] == 0xe0)
			 {
				 sendPitchBend(SPI_RX[currentByte+1], SPI_RX[currentByte+2]);
			 }
			 currentByte = currentByte+3;
		 }
		 */
	}

	else if (SPI_RX[offset] == 3)
		{
			//end writing preset to the SD card and close the file
			 //HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);

			 writingPreset = 0;

			 uint8_t currentByte = offset+1;

			 //write the raw data as a preset number on the SD card


			 //res = f_close(&fdst);
			 //f_mount(0, "", 0); //unmount

			 	/*
			 while (SPI_RX[currentByte] != 0)
			 {
				 if (SPI_RX[currentByte] == 0x90)
				 {
					 sendNoteOn(SPI_RX[currentByte+1], SPI_RX[currentByte+2]);
				 }
				 else if (SPI_RX[currentByte] == 0xb0)
				 {
					 sendCtrl(SPI_RX[currentByte+1], SPI_RX[currentByte+2]);
				 }
				 else if (SPI_RX[currentByte] == 0xe0)
				 {
					 sendPitchBend(SPI_RX[currentByte+1], SPI_RX[currentByte+2]);
				 }
				 currentByte = currentByte+3;
			 }
			 */

			 /* Parse into Audio Params */
			 parse_preset();

			 //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
		}
}

float scaleDefault(float input)
{
	return input;
}

float scaleTwo(float input)
{
	return (input * 2.0f);
}

float scaleOscPitch(float input)
{
	return (input * 48.0f) - 24.0f;
}

float scaleOscFine(float input)
{
	return (input * 200.0f) - 100.0f;
}

float scaleOscFreq(float input)
{
	return (input * 4000.0f) - 2000.0f;
}

float scaleTranspose(float input)
{
	return (input * 96.0f) - 48.0f;
}

float scalePitchBend(float input)
{
	return (input * 24.0f);
}

float scaleFilterCutoff(float input)
{
	return (input * 127.0f);
}

float scaleFilterResonance(float input)
{
	//lookup table for filter res

	//scale to lookup range
	input *= 2047.0f;
	int inputInt = (int)input;
	float inputFloat = (float)inputInt - input;
	int nextPos = LEAF_clip(0, inputInt + 1, 2047);
	return (resTable[inputInt] * (1.0f - inputFloat)) + (resTable[nextPos] * inputFloat);
	//return
}

float scaleEnvTimes(float input)
{
	//lookup table for env times

	//scale to lookup range
	input *= 2047.0f;
	int inputInt = (int)input;
	float inputFloat = (float)inputInt - input;
	int nextPos = LEAF_clip(0, inputInt + 1, 2047);
	return (envTimeTable[inputInt] * (1.0f - inputFloat)) + (envTimeTable[nextPos] * inputFloat);

	//return
}

float scaleLFORates(float input)
{
	//lookup table for LFO rates

	//scale to lookup range
	input *= 2047.0f;
	int inputInt = (int)input;
	float inputFloat = (float)inputInt - input;
	int nextPos = LEAF_clip(0, inputInt + 1, 2047);
	return (lfoRateTable[inputInt] * (1.0f - inputFloat)) + (lfoRateTable[nextPos] * inputFloat);
	//return
}


void parse_preset()
{

	//osc params
	for (int i = 0; i < NUM_PARAMS; i++)
	{
		params[i].zeroToOneVal = INV_TWO_TO_15 * ((buffer[i*2] << 8) + buffer[(i*2)+1]);
		//need to map all of the params to their scaled parameters and set them to the realVals
		params[i].scaleFunc = &scaleDefault;
	}


	//params[i].realVal = params[i].zeroToOneVal;
	params[Master].scaleFunc = &scaleTwo;
	params[Transpose].scaleFunc = &scaleTranspose;
	params[PitchBendRangeUp].scaleFunc = &scalePitchBend;
	params[PitchBendRangeDown].scaleFunc = &scalePitchBend;
	params[NoiseAmp].scaleFunc = &scaleTwo;
	params[Osc1Pitch].scaleFunc = &scaleOscPitch;
	params[Osc1Fine].scaleFunc = &scaleOscFine;
	params[Osc1Freq].scaleFunc = &scaleOscFreq;
	params[Osc1Amp].scaleFunc = &scaleTwo;
	params[Osc2Pitch].scaleFunc = &scaleOscPitch;
	params[Osc2Fine].scaleFunc = &scaleOscFine;
	params[Osc2Freq].scaleFunc = &scaleOscFreq;
	params[Osc2Amp].scaleFunc = &scaleTwo;
	params[Osc3Pitch].scaleFunc = &scaleOscPitch;
	params[Osc3Fine].scaleFunc = &scaleOscFine;
	params[Osc3Freq].scaleFunc = &scaleOscFreq;
	params[Osc3Amp].scaleFunc = &scaleTwo;
	params[Filter1Cutoff].scaleFunc = &scaleFilterCutoff;
	params[Filter1Resonance].scaleFunc = &scaleFilterResonance;
	params[Filter2Cutoff].scaleFunc = &scaleFilterCutoff;
	params[Filter2Resonance].scaleFunc = &scaleFilterResonance;
	params[Envelope1Attack].scaleFunc = &scaleEnvTimes;
	params[Envelope1Decay].scaleFunc = &scaleEnvTimes;
	params[Envelope1Release].scaleFunc = &scaleEnvTimes;
	params[Envelope2Attack].scaleFunc = &scaleEnvTimes;
	params[Envelope2Decay].scaleFunc = &scaleEnvTimes;
	params[Envelope2Release].scaleFunc = &scaleEnvTimes;
	params[Envelope3Attack].scaleFunc = &scaleEnvTimes;
	params[Envelope3Decay].scaleFunc = &scaleEnvTimes;
	params[Envelope3Release].scaleFunc = &scaleEnvTimes;
	params[Envelope4Attack].scaleFunc = &scaleEnvTimes;
	params[Envelope4Decay].scaleFunc = &scaleEnvTimes;
	params[Envelope4Release].scaleFunc = &scaleEnvTimes;
	params[LFO1Rate].scaleFunc = &scaleLFORates;
	params[LFO2Rate].scaleFunc = &scaleLFORates;
	params[LFO3Rate].scaleFunc = &scaleLFORates;
	params[LFO4Rate].scaleFunc = &scaleLFORates;
	params[OutputAmp].scaleFunc = &scaleTwo;

	for (int i = 0; i < NUM_PARAMS; i++)
	{
		params[i].realVal = params[i].scaleFunc(params[i].zeroToOneVal);
	}

	int osc1shape = roundf(params[Osc1ShapeSet].realVal * NUM_OSC_SHAPES);
	switch (osc1shape){
				  case 0:
					  shapeTick[0] = &sawSquareTick;
					  break;
				  case 1:
					  shapeTick[0] = &sineTriTick;
					  break;
				  case 2:
					  shapeTick[0] = &sawTick;
					  break;
				  case 3:
					  shapeTick[0] = &pulseTick;
					  break;
				  case 4:
					  shapeTick[0] = &sineTick;
					  break;
				  case 5:
					  shapeTick[0] = &triTick;
					  break;
				  case 6:
					  shapeTick[0] = &userTick;
					  break;
				  default:
					  break;
	}
	int osc2shape = roundf(params[Osc2ShapeSet].realVal * NUM_OSC_SHAPES);
	switch (osc2shape){
				  case 0:
					  shapeTick[1] = &sawSquareTick;
					  break;
				  case 1:
					  shapeTick[1] = &sineTriTick;
					  break;
				  case 2:
					  shapeTick[1] = &sawTick;
					  break;
				  case 3:
					  shapeTick[1] = &pulseTick;
					  break;
				  case 4:
					  shapeTick[1] = &sineTick;
					  break;
				  case 5:
					  shapeTick[1] = &triTick;
					  break;
				  case 6:
					  shapeTick[1] = &userTick;
					  break;
				  default:
					  break;
	}
	int osc3shape = roundf(params[Osc3ShapeSet].realVal * NUM_OSC_SHAPES);
	switch (osc3shape){
				  case 0:
					  shapeTick[2] = &sawSquareTick;
					  break;
				  case 1:
					  shapeTick[2] = &sineTriTick;
					  break;
				  case 2:
					  shapeTick[2] = &sawTick;
					  break;
				  case 3:
					  shapeTick[2] = &pulseTick;
					  break;
				  case 4:
					  shapeTick[2] = &sineTick;
					  break;
				  case 5:
					  shapeTick[2] = &triTick;
					  break;
				  case 6:
					  shapeTick[2] = &userTick;
					  break;
				  default:
					  break;
	}

	int filter1Type = roundf(params[Filter1Type].realVal * NUM_FILTER_TYPES);
	switch (filter1Type){
				  case 0:
					  filterTick[0] = &lowpassTick;
					  break;
				  case 1:
					  filterTick[0] = &highpassTick;
					  break;
				  case 2:
					  filterTick[0] = &bandpassTick;
					  break;
				  case 3:
					  filterTick[0] = &diodeLowpassTick;
					  break;
				  case 4:
					  filterTick[0] = &VZpeakTick;
					  break;
				  case 5:
					  filterTick[0] = &VZlowshelfTick;
					  break;
				  case 6:
					  filterTick[0] = &VZhighshelfTick;
					  break;
				  case 7:
					  filterTick[0] = &VZbandrejectTick;
					  break;
				  case 8:
					  filterTick[0] = &LadderLowpassTick;
					  break;
				  default:
					  break;
	}

	int filter2Type = roundf(params[Filter2Type].realVal * NUM_FILTER_TYPES);
	switch (filter2Type){
				  case 0:
					  filterTick[1] = &lowpassTick;
					  break;
				  case 1:
					  filterTick[1] = &highpassTick;
					  break;
				  case 2:
					  filterTick[1] = &bandpassTick;
					  break;
				  case 3:
					  filterTick[1] = &diodeLowpassTick;
					  break;
				  case 4:
					  filterTick[1] = &VZpeakTick;
					  break;
				  case 5:
					  filterTick[1] = &VZlowshelfTick;
					  break;
				  case 6:
					  filterTick[1] = &VZhighshelfTick;
					  break;
				  case 7:
					  filterTick[1] = &VZbandrejectTick;
					  break;
				  case 8:
					  filterTick[1] = &LadderLowpassTick;
					  break;
				  default:
					  break;
	}
	muteAudio = 0;
}



void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	handleSPI(16);
}

void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
	handleSPI(0);
}



// EXTI Line12 External Interrupt ISR Handler CallBackFun
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_12) // If The INT Source Is EXTI Line12
    {


    	  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == 0)
    	  {
    		  HAL_SPI_Abort(&hspi1);
    		  __HAL_SPI_CLEAR_OVRFLAG(&hspi1);
    	  }
    	  else
    	  {
    		  for (int i = 0; i < 32; i++)
			  {
				  SPI_TX[i] = i;
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
