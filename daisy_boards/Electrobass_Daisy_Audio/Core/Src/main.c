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
static int checkForSDCardPreset(void);
static void writePresetToSDCard(int fileSize);
void parsePreset(int size);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#define SPI_BUFFER_SIZE 32
#define SPI_FRAME_SIZE 16
uint8_t SPI_TX[SPI_BUFFER_SIZE] __ATTR_RAM_D2;
uint8_t SPI_RX[SPI_BUFFER_SIZE] __ATTR_RAM_D2;

uint8_t volatile bootloaderFlag[32] __ATTR_USER_FLASH;
uint8_t resetFlag = 0;

uint8_t diskBusy = 0;
uint8_t buttonPressed = 0;
FILINFO fno;
DIR dir;
const TCHAR path = 0;


volatile uint8_t writingPreset = 0;
volatile float 	audioMasterLevel = 1.0f;
FIL fdst;
volatile uint8_t buffer[4096];
volatile uint16_t bufferPos = 0;
FRESULT res;

uint32_t presetWaitingToParse = 0;
uint32_t presetWaitingToWrite = 0;


param params[NUM_PARAMS];
mapping mappings[MAX_NUM_MAPPINGS];
uint8_t numMappings = 0;

filterSetter filterSetters[NUM_FILT];
float defaultScaling = 1.0f;

float resTable[2048];
float envTimeTable[2048];
float lfoRateTable[2048];

//uint8_t bootloadFlag __ATTR_RAM_D3;

uint8_t volatile foundOne = 0;


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
  /* Enable write access to Backup domain */
   PWR->CR1 |= PWR_CR1_DBP;
   while((PWR->CR1 & PWR_CR1_DBP) == RESET)
   {
	   ;
   }
   /*Enable BKPRAM clock*/
   __HAL_RCC_BKPRAM_CLK_ENABLE();


  uint32_t tempFPURegisterVal = __get_FPSCR();
  tempFPURegisterVal |= (1<<24); // set the FTZ (flush-to-zero) bit in the FPU control register
  __set_FPSCR(tempFPURegisterVal);

  CycleCounterInit();
  cStack_init(&noteStack);
  cStack_init(&ctrlStack);
  cStack_init(&pBendStack);


  for (int i = 0; i < 4096; i++)
  {
	  buffer[i] = 0;
  }
  LEAF_generate_table_skew_non_sym(&resTable, 0.01f, 10.0f, 0.5f, 2048);
  LEAF_generate_table_skew_non_sym(&envTimeTable, 0.0f, 20000.0f, 4000.0f, 2048);
  LEAF_generate_table_skew_non_sym(&lfoRateTable, 0.0f, 30.0f, 2.0f, 2048);

  foundOne  = checkForSDCardPreset();
  if (foundOne == 0)
  {
	  parsePreset(320); //default preset binary
  }
  else
  {
	  parsePreset(presetWaitingToParse);
  }

  codec_init(&hi2c2);

  audio_init(&hsai_BlockB1, &hsai_BlockA1);
  int counter = 0;
  for (int i = 0; i < SPI_BUFFER_SIZE; i++)
  {
	  SPI_TX[i] = counter++;
  }




  HAL_Delay(10);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);

  HAL_SPI_TransmitReceive_DMA(&hspi1, SPI_TX, SPI_RX, SPI_BUFFER_SIZE);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);









  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (presetWaitingToParse > 0)
	  {
		  parsePreset(presetWaitingToParse);
	  }

	  else if (presetWaitingToWrite > 0)
	  {
		  writePresetToSDCard(presetWaitingToWrite);
	  }

	  if (resetFlag == 1)
	  {
		  HAL_Delay(100);
		  HAL_NVIC_SystemReset();
	  }

	  /*

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


static int checkForSDCardPreset(void)
{
	int found = 0;
	if(BSP_SD_IsDetected())
	{
		diskBusy = 1;
		//HAL_Delay(300);

		disk_initialize(0);

	    disk_status(0);

		if(f_mount(&SDFatFS,  SDPath, 1) == FR_OK)
		{

			FRESULT res;
			/* Start to search for preset files */
			res = f_findfirst(&dir, &fno, SDPath, "1.ebp");
			uint bytesRead;
			if(res == FR_OK)
			{
				if(f_open(&SDFile, fno.fname, FA_OPEN_ALWAYS | FA_READ) == FR_OK)
				{
					f_read(&SDFile, &buffer, f_size(&SDFile), &bytesRead);
					presetWaitingToParse = bytesRead;
					f_close(&SDFile);
					found = 1;
					for (int i = 0; i < 4; i++)
					{
						HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
						HAL_Delay(50);
					}
				}
			}
			//f_closedir(&dir);
			//f_mount(0, "", 0); //unmount
		}

	}
	diskBusy = 0;
	return found;
}


static void writePresetToSDCard(int fileSize)
{
	if(BSP_SD_IsDetected())
	{
		//if(f_mount(&SDFatFS,  SDPath, 1) == FR_OK)
		{
			//if(res == FR_OK)
			{
				diskBusy = 1;
				if(f_open(&SDFile, "1.ebp", FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
				{
					uint bytesRead;
					f_write(&SDFile, &buffer, fileSize, &bytesRead);
					f_close(&SDFile);
				}

			}
			//f_mount(0, "", 0); //unmount
		}
	}
	presetWaitingToWrite = 0;
	diskBusy = 0;
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



	 	  MPU_InitStruct.Enable = MPU_REGION_ENABLE;

	 		  //D2 Domain�SRAM1
	 		  MPU_InitStruct.BaseAddress = 0x38800000;
	 		  // Increased region size to 256k. In Keshikan's code, this was 512 bytes (that's all that application needed).
	 		  // Each audio buffer takes up the frame size * 8 (16 bits makes it *2 and stereo makes it *2 and double buffering makes it *2)
	 		  // So a buffer size for read/write of 4096 would take up 64k = 4096*8 * 2 (read and write).
	 		  // I increased that to 256k so that there would be room for the ADC knob inputs and other peripherals that might require DMA access.
	 		  // we have a total of 256k in SRAM1 (128k, 0x30000000-0x30020000) and SRAM2 (128k, 0x30020000-0x3004000) of D2 domain.
	 		  // There is an SRAM3 in D2 domain as well (32k, 0x30040000-0x3004800) that is currently not mapped by the MPU (memory protection unit) controller.

	 		  MPU_InitStruct.Size = MPU_REGION_SIZE_4KB;

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


	 		  MPU_InitStruct.Number = MPU_REGION_NUMBER2;

	 		  MPU_InitStruct.SubRegionDisable = 0x00;


	 		  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;


	 		  HAL_MPU_ConfigRegion(&MPU_InitStruct);


	  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}



void handleSPI(uint8_t offset)
{
	// if the first number is a 1 then it's a midi note/ctrl/bend message
	if (SPI_RX[offset] == 1)
	{
		//got a change!
		 //HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);

		 uint8_t currentByte = offset+1;

		 while ((SPI_RX[currentByte] != 0) && ((currentByte % 16) < SPI_FRAME_SIZE))
		 {
			 if (SPI_RX[currentByte] == 0x90)
			 {
				 cStack_push(&noteStack, (int8_t)SPI_RX[currentByte+1], (int8_t)SPI_RX[currentByte+2]);
			 }
			 else if (SPI_RX[currentByte] == 0xb0)
			 {
				 cStack_push(&ctrlStack, (int8_t)SPI_RX[currentByte+1], (int8_t)SPI_RX[currentByte+2]);
			 }
			 else if (SPI_RX[currentByte] == 0xe0)
			 {
				 cStack_push(&pBendStack, (int8_t)SPI_RX[currentByte+1], (int8_t)SPI_RX[currentByte+2]);
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
			 audioMasterLevel = 0.0f;
			 //write the raw data as a preset number on the SD card
			 bufferPos = 0;
		 }

		 uint8_t currentByte = offset+2;

		 for (int i = 0; i < 14; i++)
		 {
			 buffer[bufferPos++] = SPI_RX[currentByte + i];

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
		 writingPreset = 0;
		 /* Parse into Audio Params */
		 presetWaitingToParse = bufferPos;
		 presetWaitingToWrite = bufferPos;
	}
}

float scaleDefault(float input)
{
	input = LEAF_clip(0.f, input, 1.f);
	return input;
}

float scaleTwo(float input)
{
	input = LEAF_clip(0.f, input, 1.f);
	return (input * 2.0f);
}

float scaleOscPitch(float input)
{
	input = LEAF_clip(0.f, input, 1.f);
	return (input * 48.0f) - 24.0f;
}

float scaleOscFine(float input)
{
	input = LEAF_clip(0.f, input, 1.f);
	return (input * 200.0f) - 100.0f;
}

float scaleOscFreq(float input)
{
	//input = LEAF_clip(0.f, input, 1.f); //don't clip input because we may want large gain oscillators to go through
	return (input * 4000.0f) - 2000.0f;
}

float scaleTranspose(float input)
{
	input = LEAF_clip(0.f, input, 1.f);
	return (input * 96.0f) - 48.0f;
}

float scalePitchBend(float input)
{
	input = LEAF_clip(0.f, input, 1.f);
	return (input * 24.0f);
}

float scaleFilterCutoff(float input)
{
	input = LEAF_clip(0.f, input, 1.f);
	return (input * 127.0f);
}

float scaleFilterResonance(float input)
{
	//lookup table for filter res
	input = LEAF_clip(0.0f, input, 1.0f);
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
	input = LEAF_clip(0.0f, input, 1.0f);
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
	input = LEAF_clip(0.0f, input, 1.0f);
	//scale to lookup range
	input *= 2047.0f;
	int inputInt = (int)input;
	float inputFloat = (float)inputInt - input;
	int nextPos = LEAF_clip(0, inputInt + 1, 2047);
	return (lfoRateTable[inputInt] * (1.0f - inputFloat)) + (lfoRateTable[nextPos] * inputFloat);
	//return
}
void blankFunction(float a, int b)
{
	;
}


void parsePreset(int size)
{
	//turn off the volume while changing parameters

	audioMasterLevel = 0.0f;
	//osc params
	for (int i = 0; i < NUM_PARAMS; i++)
	{
		params[i].zeroToOneVal = INV_TWO_TO_15 * ((buffer[i*2] << 8) + buffer[(i*2)+1]);
		//need to map all of the params to their scaled parameters and set them to the realVals
		params[i].scaleFunc = &scaleDefault;

		//blank function means that it doesn't actually set a final value, we will read directly from the realVals when we need it
		params[i].setParam = &blankFunction;
	}

	params[Master].scaleFunc = &scaleTwo;
	params[Transpose].scaleFunc = &scaleTranspose;
	params[PitchBendRangeUp].scaleFunc = &scalePitchBend;
	params[PitchBendRangeDown].scaleFunc = &scalePitchBend;
	params[NoiseAmp].scaleFunc = &scaleTwo;
	params[Osc1Pitch].scaleFunc = &scaleOscPitch;
	params[Osc1Fine].scaleFunc = &scaleOscFine;
	params[Osc1Freq].scaleFunc = &scaleOscFreq;
	params[Osc1Amp].scaleFunc = &scaleTwo; // changed to scale from 0-1 instead of 0-2 to avoid FM issues when clipping range CHANGE IN PLUGIN TOO!
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
		params[i].initRealVal = params[i].realVal;
	}

	for (int i = 0; i < NUM_OSC; i++)
	{
		int oscshape = roundf(params[Osc1ShapeSet + (OscParamsNum * i)].realVal * NUM_OSC_SHAPES);
		switch (oscshape){
				  case 0:
					  shapeTick[i] = &sawSquareTick;
					  break;
				  case 1:
					  shapeTick[i] = &sineTriTick;
					  break;
				  case 2:
					  shapeTick[i] = &sawTick;
					  break;
				  case 3:
					  shapeTick[i] = &pulseTick;
					  break;
				  case 4:
					  shapeTick[i] = &sineTick;
					  break;
				  case 5:
					  shapeTick[i] = &triTick;
					  break;
				  case 6:
					  shapeTick[i] = &userTick;
					  break;
				  default:
					  break;
	}


	for (int i = 0; i < NUM_FILT; i++)
	{
		int filterType = roundf(params[Filter1Type + (i * FilterParamsNum)].realVal * NUM_FILTER_TYPES);
		//filterSetters[i].setCutoff = &filterSetCutoff;
		//filterSetters[i].setKeyfollow = &filterSetKeyfollow;
		switch (filterType){
				  case 0:
					  filterTick[i] = &lowpassTick;
					  filterSetters[i].setQ = &lowpassSetQ;
					  filterSetters[i].setGain = &lowpassSetGain;
					  break;
				  case 1:
					  filterTick[i] = &highpassTick;
					  filterSetters[i].setQ = &highpassSetQ;
					  filterSetters[i].setGain = &highpassSetGain;
					  break;
				  case 2:
					  filterTick[i] = &bandpassTick;
					  filterSetters[i].setQ = &bandpassSetQ;
					  filterSetters[i].setGain = &bandpassSetGain;
					  break;
				  case 3:
					  filterTick[i] = &diodeLowpassTick;
					  filterSetters[i].setQ = &diodeLowpassSetQ;
					  filterSetters[i].setGain = &diodeLowpassSetGain;
					  break;
				  case 4:
					  filterTick[i] = &VZpeakTick;
					  filterSetters[i].setQ = &VZpeakSetQ;
					  filterSetters[i].setGain = &VZpeakSetGain;
					  break;
				  case 5:
					  filterTick[i] = &VZlowshelfTick;
					  filterSetters[i].setQ = &VZlowshelfSetQ;
					  filterSetters[i].setGain = &VZlowshelfSetGain;
					  break;
				  case 6:
					  filterTick[i] = &VZhighshelfTick;
					  filterSetters[i].setQ = &VZhighshelfSetQ;
					  filterSetters[i].setGain = &VZhighshelfSetGain;
					  break;
				  case 7:
					  filterTick[i] = &VZbandrejectTick;
					  filterSetters[i].setQ = &VZbandrejectSetQ;
					  filterSetters[i].setGain = &VZbandrejectSetGain;
					  break;
				  case 8:
					  filterTick[i] = &LadderLowpassTick;
					  filterSetters[i].setQ = &LadderLowpassSetQ;
					  filterSetters[i].setGain = &LadderLowpassSetGain;
					  break;
				  default:
					  break;
			}
		}
	}

	params[Master].setParam = &setMaster;
	params[Transpose].setParam = &setTranspose;
	params[PitchBendRangeUp].setParam = &setPitchBendRangeUp;
	params[PitchBendRangeDown].setParam = &setPitchBendRangeDown;
	//params[NoiseAmp].setParam = &setNoiseAmp;
	params[Osc1Pitch].setParam = &setFreqMult;
	params[Osc2Pitch].setParam = &setFreqMult;
	params[Osc3Pitch].setParam = &setFreqMult;
	//params[Filter1Cutoff].setParam = filterSetters[0].setCutoff;
	params[Filter1Resonance].setParam = filterSetters[0].setQ;
	params[Filter1Gain].setParam = filterSetters[0].setGain; //gain is a special case for set params where the scaling function leaves it alone because it's different based on filter type
	//params[Filter1KeyFollow].setParam = filterSetters[0].setKeyfollow;
	//params[Filter2Cutoff].setParam = filterSetters[1].setCutoff;
	params[Filter2Resonance].setParam = filterSetters[1].setQ;
	params[Filter2Gain].setParam = filterSetters[1].setGain;
	//params[Filter2KeyFollow].setParam = filterSetters[1].setKeyfollow;
	params[Envelope1Attack].setParam = &setEnvelopeAttack;
	params[Envelope1Decay].setParam = &setEnvelopeDecay;
	params[Envelope1Sustain].setParam = &setEnvelopeSustain;
	params[Envelope1Release].setParam = &setEnvelopeRelease;
	params[Envelope1Leak].setParam = &setEnvelopeLeak;
	params[Envelope2Attack].setParam = &setEnvelopeAttack;
	params[Envelope2Decay].setParam = &setEnvelopeDecay;
	params[Envelope2Sustain].setParam = &setEnvelopeSustain;
	params[Envelope2Release].setParam = &setEnvelopeRelease;
	params[Envelope2Leak].setParam = &setEnvelopeLeak;
	params[Envelope3Attack].setParam = &setEnvelopeAttack;
	params[Envelope3Decay].setParam = &setEnvelopeDecay;
	params[Envelope3Sustain].setParam = &setEnvelopeSustain;
	params[Envelope3Release].setParam = &setEnvelopeRelease;
	params[Envelope3Leak].setParam = &setEnvelopeLeak;
	params[Envelope4Attack].setParam = &setEnvelopeAttack;
	params[Envelope4Decay].setParam = &setEnvelopeDecay;
	params[Envelope4Sustain].setParam = &setEnvelopeSustain;
	params[Envelope4Release].setParam = &setEnvelopeRelease;
	params[Envelope4Leak].setParam = &setEnvelopeLeak;
	//params[LFO1Rate].setParam = &scaleLFORates;
	//params[LFO2Rate].setParam = &scaleLFORates;
	//params[LFO3Rate].setParam = &scaleLFORates;
	//params[LFO4Rate].setParam = &scaleLFORates;
	params[OutputAmp].setParam = &setAmp;



	for (int i = 0; i < NUM_PARAMS; i++)
	{
		params[i].objectNumber = 0;
		//oscillators
		if ((i >= Osc1) && (i < Osc2))
		{
			params[i].objectNumber = 0;
		}
		else if ((i >= Osc2) && (i < Osc3))
		{
			params[i].objectNumber = 1;
		}
		else if ((i >= Osc3) && (i < Effect1FXType))
		{
			params[i].objectNumber = 2;
		}
		//effects
		//filters
		else if ((i >= Filter1) && (i < Filter2))
		{
			params[i].objectNumber = 0;
		}
		else if ((i >= Filter2) && (i < Envelope1Attack))
		{
			params[i].objectNumber = 1;
		}
		//envelopes
		else if ((i >= Envelope1Attack) && (i < Envelope2Attack))
		{
			params[i].objectNumber = 0;
		}
		else if ((i >= Envelope2Attack) && (i < Envelope3Attack))
		{
			params[i].objectNumber = 1;
		}
		else if ((i >= Envelope3Attack) && (i < Envelope4Attack))
		{
			params[i].objectNumber = 2;
		}
		else if ((i >= Envelope4Attack) && (i < LFO1Rate))
		{
			params[i].objectNumber = 3;
		}
		//lfos
		//other


		params[i].setParam(params[i].realVal, params[i].objectNumber);

	}

	//mappings parsing
	numMappings = 0;

	for (int i = 0; i < MAX_NUM_MAPPINGS; i++)
	{
		mappings[i].destNumber = 255;
		mappings[i].numHooks = 0;
	}
	for (int i = (NUM_PARAMS * 2) + 4; i < size; i+=5)
	{
		if ((buffer[i] != 255) && (buffer[i] != 254))
		{
			uint8_t destNumber = buffer[i+1];
			uint8_t whichMapping = 0;
			uint8_t whichHook = 0;
			uint8_t foundOne = 0;
			//search to see if this destination already has other mappings
			for (int j = 0; j < MAX_NUM_MAPPINGS; j++)
			{
				if (mappings[j].destNumber == destNumber)
				{
					//found one, use this mapping and add another hook to it
					whichMapping = j;
					whichHook = mappings[j].numHooks;
					foundOne = 1;
				}
			}
			if (foundOne == 0)
			{
				//didn't find another mapping with this destination, start a new mapping
				whichMapping = numMappings;

				numMappings++;
				whichHook = 0;
				mappings[whichMapping].destNumber = destNumber;
				mappings[whichMapping].dest = &params[destNumber];

			}

			mappings[whichMapping].sourceValPtr[whichHook] = &sourceValues[buffer[i]];
			int scalar = buffer[i+2];
			if (scalar == 0xff)
			{
				mappings[whichMapping].scalarSourceValPtr[whichHook] = &defaultScaling;
			}
			else
			{
				mappings[whichMapping].scalarSourceValPtr[whichHook] = &sourceValues[buffer[i+2]];
			}
			float amountFloat = ((buffer[i+3] << 8) + buffer[i+4]) * INV_TWO_TO_15;
			mappings[whichMapping].amount[whichHook] = amountFloat;
			mappings[whichMapping].numHooks++;
		}
	}

	//params[i].zeroToOneVal = INV_TWO_TO_15 * ((buffer[i*2] << 8) + buffer[(i*2)+1]);

	audioMasterLevel = 1.0f;
	presetWaitingToParse = 0;
}



/////



void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	handleSPI(16);
}

void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
	handleSPI(0);
}

void FlushECC(void *ptr, int bytes)
{

	uint32_t addr = (uint32_t)ptr;
	/* Check if accessing AXI SRAM => 64-bit words*/
	if(addr >= 0x24000000 && addr < 0x24080000){
		volatile uint64_t temp;
		volatile uint64_t* flush_ptr = (uint64_t*) (addr & 0xFFFFFFF8);
		uint64_t *end_ptr = (uint64_t*) ((addr+bytes) & 0xFFFFFFF8);

		do{
			temp = *flush_ptr;
			*flush_ptr = temp;
			flush_ptr++;
		}while(flush_ptr != end_ptr);
	}
	/* Otherwise 32-bit words */
	else {
		volatile uint32_t temp;
		volatile uint32_t* flush_ptr = (uint32_t*) (addr & 0xFFFFFFFC);
		uint32_t *end_ptr = (uint32_t*) ((addr+bytes) & 0xFFFFFFFC);

		do{
			temp = *flush_ptr;
			*flush_ptr = temp;
			flush_ptr++;
		}while(flush_ptr != end_ptr);
	}
}
// helper function to initialize measuring unit (cycle counter) */
static void CycleCounterInit( void )
{
  /* Enable TRC */
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

  /* Unlock DWT registers */
  if ((*(uint32_t*)0xE0001FB4) & 1)
    *(uint32_t*)0xE0001FB0 = 0xC5ACCE55;

  /* clear the cycle counter */
  DWT->CYCCNT = 0;

  /* start the cycle counter */
  DWT->CTRL = 0x40000001;

}

// EXTI Line12 External Interrupt ISR Handler CallBackFun
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	/*if(GPIO_Pin == GPIO_PIN_12) // If The INT Source Is EXTI Line12
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
    */
    if(GPIO_Pin == GPIO_PIN_3) // If The INT Source Is EXTI Line3
    {
    	  if(HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_3) == 1) //button is pressed, wait
    	  {
    		  buttonPressed = 1;
    		  //bootloadFlag = 231;
    		  //*(__IO uint32_t*)(0x38800000+36) = 12345678;
    		  //SCB_CleanDCache_by_Addr (*(__IO uint32_t*)0x38800000+36, 1); //maybe needs different
    	  }
    	  else //button went up
    	  {
    		  if (buttonPressed == 1)
    		  {
    			  for (int i = 0; i < 32; i++)
    			  {
    				  bootloaderFlag[i] = 231;
    			  }
    			  FlushECC(&bootloaderFlag,  32);

				  buttonPressed = 0;
				  resetFlag = 1;

    		  }
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
