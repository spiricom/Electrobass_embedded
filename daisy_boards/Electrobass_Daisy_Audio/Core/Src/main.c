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

#include "memory.h"
#include "audiostream.h"
#include "leaf.h"
#include "codec.h"

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

void MPU_Config(void);
void SDRAM_init(void);
static int checkForSDCardPreset(uint8_t value);
static void writePresetToSDCard(int fileSize);
void getPresetNamesFromSDCard(void);
void parsePreset(int size, int presetNumber);
void getTuningNamesFromSDCard(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

LEAF leaf;


uint8_t presetReady = 0;


float random_values[256];
uint8_t currentRandom = 0;
uint_fast8_t knobTicked[12];
uint_fast8_t pedalTicked[10];
uint8_t bootloaderFlag[32] __ATTR_USER_FLASH;
uint8_t resetFlag = 0;
uint8_t pedalControlsMaster = 0;
uint8_t diskBusy = 0;
uint8_t buttonPressed = 0;
FILINFO fno;
DIR dir;
const TCHAR path = 0;

uint8_t effectsActive[4] = {0,0,0,0};
#define MAX_NUM_TUNINGS 20
volatile uint8_t writingState = 0;
volatile float 	audioMasterLevel = 1.0f;
FIL fdst;
uint8_t buffer[4096] __ATTR_RAM_D2;
volatile uint16_t bufferPos = 0;
FRESULT res;
volatile uint8_t presetNumberToSave;
volatile uint8_t presetNumberToLoad = 0;
volatile uint8_t tuningNumberToSave;
volatile uint8_t tuningNumberToLoad = 0;
volatile uint8_t currentActivePreset = 0;
volatile uint8_t presetName[14];

uint8_t whichMacroToSendName = 0;
volatile uint8_t whichPresetToSendName = 0;

volatile uint8_t whichTuningToSendName = 0;
volatile uint8_t tuningName[14];
volatile uint32_t presetWaitingToParse = 0;
volatile uint32_t presetWaitingToWrite = 0;
volatile uint32_t presetWaitingToLoad = 0;
volatile uint32_t tuningWaitingToParse = 0;
volatile uint32_t tuningWaitingToWrite = 0;
volatile uint32_t tuningWaitingToLoad = 0;

const char* specialModeNames[5];
const char* specialModeMacroNames[5][20];
float loadedKnobParams[20];
int32_t volatile prevKnobByte[20];
uint8_t whichModel; //0=synth 1=string1 2=string2 3=additive 4=vocal 5=string3
uint8_t sendPresetName = 1;
uint32_t currentPresetSize = 0;
param params[NUM_PARAMS];
mapping mappings[MAX_NUM_MAPPINGS];
uint8_t numMappings = 0;

filterSetter filterSetters[NUM_FILT];
lfoSetter lfoSetters[NUM_LFOS];
effectSetter effectSetters[NUM_EFFECT];
float defaultScaling = 1.0f;


int oscsEnabled[3] = {0,0,0};
float midiKeyDivisor;
float midiKeySubtractor;


uint8_t volatile interruptChecker = 0;

uint8_t volatile foundOne = 0;
uint8_t loadFailed = 0;
uint32_t volatile myTestInt = 0;
uint8_t fxPre = 0;


tExpSmooth knobSmoothers[20];
volatile uint8_t knobFrozen[20];

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	MPU_Config();
  SCB_EnableICache();
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

   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
  uint32_t tempFPURegisterVal = __get_FPSCR();
  tempFPURegisterVal |= (1<<24); // set the FTZ (flush-to-zero) bit in the FPU control register
  __set_FPSCR(tempFPURegisterVal);

  CycleCounterInit();
  cStack_init(&midiStack);


  for (int i = 0; i < 4096; i++)
  {
	  buffer[i] = 0;
  } //put in some values to make the array valid as a preset


  HAL_Delay(10);

  /*

  getPresetNamesFromSDCard();
  diskBusy = 1;
  foundOne  = checkForSDCardPreset(presetNumberToLoad);
*/
  SDRAM_init();
  codec_init(&hi2c2);

  //******** initializing leaf stuff ************//
    LEAF_init(&leaf, SAMPLE_RATE, small_memory, SMALL_MEM_SIZE, &randomNumber);
    tLookupTable_init(&leaf.lfoRateTable, 0.0f, 30.f, 2.f, SCALE_TABLE_SIZE,&leaf);
    tLookupTable_init(&leaf.resTable, 0.01f, 10.f, 0.5f, SCALE_TABLE_SIZE,&leaf);
    tLookupTable_init(&leaf.envTimeTable, 0.0f, 20000.f, 4000.f, SCALE_TABLE_SIZE,&leaf);

  	tMempool_init (&mediumPool, medium_memory, MED_MEM_SIZE, &leaf);
  	tMempool_init (&largePool, large_memory, LARGE_MEM_SIZE, &leaf);

  	leaf.clearOnAllocation = 1;
  	LEAF_generate_exp(decayExpBuffer, 0.001f, 0.0f, 1.0f, -0.0008f, DECAY_EXP_BUFFER_SIZE); // exponential decay buffer falling from 1 to 0


  	LEAF_generate_atodb(atoDbTable, ATODB_TABLE_SIZE, 0.00001f, 1.0f);
  	LEAF_generate_dbtoa(dbtoATable, DBTOA_TABLE_SIZE, -90.0f, 50.0f);
  	LEAF_generate_mtof(mtofTable, -163.8375f, 163.8375f,  MTOF_TABLE_SIZE); //mtof table for fast calc

  	for (int i = 0; i < 20; i++)
	{
		tExpSmooth_init(&knobSmoothers[i],0.0f, 0.0005f, &leaf);
	}


  	//******** initializing leaf stuff ************//

  	audioInit();



  	/*
  if (foundOne == 0)
  {
	  parsePreset((NUM_PARAMS*2)+27+ (8*14), 0); //default preset binary
  }
  else
  {
	  //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
	  parsePreset(presetWaitingToParse, presetNumberToLoad);
  }
  */

  HAL_Delay(10);

  HAL_SPI_TransmitReceive_DMA(&hspi1, SPI_TX, SPI_RX, SPI_BUFFER_SIZE);


  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

  audioStart(&hsai_BlockB1, &hsai_BlockA1);



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (presetWaitingToLoad > 0)
	  {
		  checkForSDCardPreset(presetNumberToLoad);
	  }
	  else if (presetWaitingToWrite > 0)
	  {
		  writePresetToSDCard(presetWaitingToWrite);
	  }
	  else if (presetWaitingToParse > 0)
	  {
		  parsePreset(presetWaitingToParse, presetNumberToLoad);
	  }

	  if (tuningWaitingToLoad > 0)
	  {
		  //checkForSDCardTuning(tuningNumberToLoad);
	  }

	  else if(tuningWaitingToParse > 0)
	  {
		  //parseTuning(tuningWaitingToParse, tuningNumberToLoad);
	  }
	  else if  (tuningWaitingToWrite)
	  {
		  //writeTuningToSDCard(tuningWaitingToWrite);
	  }

	  uint32_t rand;
	  HAL_RNG_GenerateRandomNumber(&hrng, &rand);

	  if (rand > TWO_TO_31)
	  {
		  myTestInt++;
		  //HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
	  }

	  random_values[currentRandom++] = (float)rand * INV_TWO_TO_32 ;
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

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
  PeriphClkInitStruct.PLL2.PLL2N = 10;
  PeriphClkInitStruct.PLL2.PLL2P = 8;
  PeriphClkInitStruct.PLL2.PLL2Q = 2;
  PeriphClkInitStruct.PLL2.PLL2R = 1;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_3;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOMEDIUM;
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
float  __ATTR_ITCMRAM randomNumber(void)
{
	return random_values[currentRandom++];
}

uint8_t BSP_SD_IsDetected(void)
{
  __IO uint8_t status = SD_PRESENT;

  //if (BSP_PlatformIsDetected() == 0x0)
  //{
  //  status = SD_NOT_PRESENT;
  //}

  return status;
}

void getPresetNamesFromSDCard(void)
{
	if(BSP_SD_IsDetected())
	{
		for (int i = 0; i < AUDIO_BUFFER_SIZE; i+=2)
		{
			audioOutBuffer[i] = 0;
			audioOutBuffer[i + 1] = 0;
		}
		diskBusy = 1;

		loadFailed = 0;
		//HAL_Delay(300);

		disk_initialize(0);

	    disk_status(0);

		if(f_mount(&SDFatFS,  SDPath, 1) == FR_OK)
		{

			FRESULT res;
			/* Start to search for preset files */


			//turn the integer value into a 2 digit string
			char charBuf[10];
			char finalString[10];

			for(int i = 0; i < MAX_NUM_PRESETS; i++)
			{
				itoa(i, charBuf, 10);
				int len = ((strlen(charBuf)));
				if (len == 1)
				{
					finalString[2] = charBuf[1];
					finalString[1] = charBuf[0];
					finalString[0] = '0';
					strcat(finalString, "*.ebp");
				}

				else
				{
					strcat(charBuf, "*.ebp");
					strcpy(finalString, charBuf);
				}


				res = f_findfirst(&dir, &fno, SDPath, finalString);
				UINT bytesRead;
				if(res == FR_OK)
				{
					if(f_open(&SDFile, fno.fname, FA_OPEN_ALWAYS | FA_READ) == FR_OK)
					{
						f_read(&SDFile, &buffer, f_size(&SDFile), &bytesRead);
						f_close(&SDFile);
						uint16_t bufferIndex = 0;
						//skip the first 4 bytes if there is a version number stored in the preset
						if (buffer[bufferIndex] == 17)
						{
							bufferIndex = 4;
						}
						//14-byte name
						for (int j = 0; j < 14; j++)
						{
							presetNamesArray[i][j] = buffer[bufferIndex];
							bufferIndex++;
						}
						//9-byte macros
						for (int j = 0; j < 8; j++)
						{
							for (int k = 0; k < 9; k++)
							{
								macroNamesArray[i][j][k] = buffer[bufferIndex];
								bufferIndex++;
							}
						}
						//10-byte macros
						for (int j = 0; j < 4; j++)
						{
							for (int k = 0; k < 10; k++)
							{
								macroNamesArray[i][j+8][k] = buffer[bufferIndex];
								bufferIndex++;
							}
						}
					}
				}
			}

		}

	}
	diskBusy = 0;
	return;
}


static int checkForSDCardPreset(uint8_t numberToLoad)
{
	int found = 0;
	//prevVoice = numberToLoad;
	//voice = numberToLoad;
	//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
	if(BSP_SD_IsDetected())
	{
		for (int i = 0; i < AUDIO_BUFFER_SIZE; i+=2)
		{
			audioOutBuffer[i] = 0;
			audioOutBuffer[i + 1] = 0;
		}
		diskBusy = 1;
		loadFailed = 0;
		//HAL_Delay(300);
		presetWaitingToLoad = 0;
		disk_initialize(0);

	    disk_status(0);

		if(f_mount(&SDFatFS,  SDPath, 1) == FR_OK)
		{

			FRESULT res;
			/* Start to search for preset files */
			char charBuf[10];
			char finalString[10];

			//turn the integer value into a 2 digit string

			itoa(numberToLoad, charBuf, 10);
			int len = ((strlen(charBuf)));
			if (len == 1)
			{
				finalString[2] = charBuf[1];
				finalString[1] = charBuf[0];
				finalString[0] = '0';
				strcat(finalString, "*.ebp");
			}

			else
			{
				strcat(charBuf, "*.ebp");
				strcpy(finalString, charBuf);
			}

			res = f_findfirst(&dir, &fno, SDPath, finalString);
			UINT bytesRead;
			if(res == FR_OK)
			{
				if(f_open(&SDFile, fno.fname, FA_OPEN_ALWAYS | FA_READ) == FR_OK)
				{
					f_read(&SDFile, &buffer, f_size(&SDFile), &bytesRead);
					presetWaitingToParse = bytesRead;
					f_close(&SDFile);
					found = 1;
				}
			}
		}
	}
	if (!found)
	{
		loadFailed = 1;
	}


	diskBusy = 0;
	//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
	return found;
}


static void writePresetToSDCard(int fileSize)
{
	__disable_irq();
	 for (int i = 0; i < AUDIO_BUFFER_SIZE; i++)
	 {
		 audioOutBuffer[i] = 0;
	 }
	if(BSP_SD_IsDetected())
	{
		//if(f_mount(&SDFatFS,  SDPath, 1) == FR_OK)
		{
			//if(res == FR_OK)
			{
				for (int i = 0; i < AUDIO_BUFFER_SIZE; i+=2)
				{
					audioOutBuffer[i] = 0;
					audioOutBuffer[i + 1] = 0;
				}
				diskBusy = 1;
				//make sure the number is not above max user preset space
			    if (presetNumberToSave > 57)
			    {
			        presetNumberToSave = 57;
			    }


			    //first, delete any existing presets that share the same number
			    FRESULT res;
				/* Start to search for preset files */
				char charBufC[10];
				char finalStringC[10];

				//turn the integer value into a 2 digit string

				itoa(presetNumberToSave, charBufC, 10);
				int len = ((strlen(charBufC)));
				if (len == 1)
				{
					finalStringC[2] = charBufC[1];
					finalStringC[1] = charBufC[0];
					finalStringC[0] = '0';
					strcat(finalStringC, "*.ebp");
				}

				else
				{
					strcat(charBufC, "*.ebp");
					strcpy(finalStringC, charBufC);
				}

				uint32_t keepChecking = 1;
				while(keepChecking)
				{
					res = f_findfirst(&dir, &fno, SDPath, finalStringC);

					//delete if found
					if((res == FR_OK) && (fno.fname[0]))
					{
						f_unlink (fno.fname);
					}
					else
					{
						keepChecking = 0;
					}
				}

			    //turn the integer value into a 2 digit string
				char charBuf[22];
				char finalString[22];
				itoa(presetNumberToSave, charBuf, 10);
				len = ((strlen(charBuf)));
				if (len == 1)
				{
					finalString[21] = 0;
					finalString[20] = 'p';
					finalString[19] = 'b';
					finalString[18] = 'e';
					finalString[17] = '.';
					for (int i = 0; i < 14; i++)
					{
						finalString[i+3] = buffer[i+4];
						//replace spaces with underscores for filename
						if (finalString[i+3] == 32)
						{
							finalString[i+3] = '_';
						}
					}
					finalString[2] = '_';
					finalString[1] = charBuf[0];
					finalString[0] = '0';

				}

				else
				{
					finalString[21] = 0;
					finalString[20] = 'p';
					finalString[19] = 'b';
					finalString[18] = 'e';
					finalString[17] = '.';
					for (int i = 0; i < 14; i++)
					{
						finalString[i+3] = buffer[i+4];
						//replace spaces with underscores for filename
						if (finalString[i+3] == 32)
						{
							finalString[i+3] = '_';
						}
					}
					finalString[2] = '_';
					finalString[1] = charBuf[1];
					finalString[0] = charBuf[0];


				}

				if(f_open(&SDFile, finalString, FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
				{
					UINT bytesRead;
					f_write(&SDFile, &buffer, fileSize, &bytesRead);
					f_close(&SDFile);
				}

			}
			//f_mount(0, "", 0); //unmount
		}
	}
	presetWaitingToWrite = 0;
	diskBusy = 0;
	__enable_irq();
}

//excellent resource on sdram configuration in cubemx
//https://community.st.com/s/article/How-to-set-up-the-FMC-peripheral-to-interface-with-the-SDRAM-IS42S16800F-6BLI-from-ISSI
//datasheet for memory used on daisy = https://www.issi.com/WW/pdf/42-45SM-RM-VM32160E.pdf

#define SDRAM_MODEREG_BURST_LENGTH_2 ((1 << 0))
#define SDRAM_MODEREG_BURST_LENGTH_4 ((1 << 1))

#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL ((0 << 3))

#define SDRAM_MODEREG_CAS_LATENCY_2 ((1 << 5))

#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE ((1 << 9))
#define SDRAM_MODEREG_WRITEBURST_MODE_PROG_BURST ((0 << 9))

#define SDRAM_MODEREG_OPERATING_MODE_STANDARD ((0 << 13)|(0 << 14))

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

	        /* Step 4: Insert 100 us delay */
	        HAL_Delay(1);


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
	        Command.AutoRefreshNumber      = 2;
	        Command.ModeRegisterDefinition = 0;

	        /* Send the command */
	        HAL_SDRAM_SendCommand(&hsdram1, &Command, 0x1000);

	        /* Step 7: Program the external memory mode register */
	        tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_4
	                 | SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL | SDRAM_MODEREG_CAS_LATENCY_2
	                 | SDRAM_MODEREG_WRITEBURST_MODE_SINGLE | SDRAM_MODEREG_OPERATING_MODE_STANDARD;
	        // // Used in example, but can't find reference except for "Test Mode"

	        Command.CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;
	        Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
	        Command.AutoRefreshNumber      = 1;
	        Command.ModeRegisterDefinition = tmpmrd;

	        /* Send the command */
	        HAL_SDRAM_SendCommand(&hsdram1, &Command, 0x1000);

	        //HAL_SDRAM_ProgramRefreshRate(hsdram, 0x56A - 20);
	        HAL_SDRAM_ProgramRefreshRate(&hsdram1, 762); // ((64ms / 8192) * 100MHz) - 20
	        //8192 is 2^numberofrows (which is 13 in the case of the sdram)

}

void MPU_Config(void)
{
	MPU_Region_InitTypeDef MPU_InitStruct = {0};

	  /* Disables the MPU */
	  HAL_MPU_Disable();

	  /** Initializes and configures the Region and the memory to be protected
	  */
	  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
	  MPU_InitStruct.BaseAddress = 0x0;
	  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
	  MPU_InitStruct.SubRegionDisable = 0x87;
	  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
	  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
	  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
	  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
	  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

	  HAL_MPU_ConfigRegion(&MPU_InitStruct);

	  /** Initializes and configures the Region and the memory to be protected
	  */
	  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
	  MPU_InitStruct.BaseAddress = 0x024000000;
	  MPU_InitStruct.Size = MPU_REGION_SIZE_256KB;
	  MPU_InitStruct.SubRegionDisable = 0x0;
	  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
	  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
	  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;

	  HAL_MPU_ConfigRegion(&MPU_InitStruct);

	  /** Initializes and configures the Region and the memory to be protected
	  */
	  MPU_InitStruct.Number = MPU_REGION_NUMBER2;
	  MPU_InitStruct.BaseAddress = 0x24040000;
	  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

	  HAL_MPU_ConfigRegion(&MPU_InitStruct);

	  /** Initializes and configures the Region and the memory to be protected
	  */
	  MPU_InitStruct.Number = MPU_REGION_NUMBER3;
	  MPU_InitStruct.BaseAddress = 0x30000000;
	  MPU_InitStruct.Size = MPU_REGION_SIZE_512KB;

	  HAL_MPU_ConfigRegion(&MPU_InitStruct);

	  /** Initializes and configures the Region and the memory to be protected
	  */
	  MPU_InitStruct.Number = MPU_REGION_NUMBER4;
	  MPU_InitStruct.Size = MPU_REGION_SIZE_8KB;
	  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
	  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
	  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

	  HAL_MPU_ConfigRegion(&MPU_InitStruct);

	  /** Initializes and configures the Region and the memory to be protected
	  */
	  MPU_InitStruct.Number = MPU_REGION_NUMBER5;
	  MPU_InitStruct.BaseAddress = 0x38000000;
	  MPU_InitStruct.Size = MPU_REGION_SIZE_64KB;

	  HAL_MPU_ConfigRegion(&MPU_InitStruct);

	  /** Initializes and configures the Region and the memory to be protected
	  */
	  MPU_InitStruct.Number = MPU_REGION_NUMBER6;
	  MPU_InitStruct.BaseAddress = 0x38800000;
	  MPU_InitStruct.Size = MPU_REGION_SIZE_4KB;

	  HAL_MPU_ConfigRegion(&MPU_InitStruct);

	  /** Initializes and configures the Region and the memory to be protected
	  */
	  MPU_InitStruct.Number = MPU_REGION_NUMBER7;
	  MPU_InitStruct.BaseAddress = 0xc0000000;
	  MPU_InitStruct.Size = MPU_REGION_SIZE_64MB;

	  HAL_MPU_ConfigRegion(&MPU_InitStruct);

	  /** Initializes and configures the Region and the memory to be protected
	  */
	  MPU_InitStruct.Number = MPU_REGION_NUMBER8;
	  MPU_InitStruct.BaseAddress = 0x90040000;

	  HAL_MPU_ConfigRegion(&MPU_InitStruct);
	  /* Enables the MPU */
	  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);


}






void __ATTR_ITCMRAM handleSPI (uint8_t offset)
{

	if (SPI_RX[offset] == ReceivingPitches)
	{
		 uint8_t currentByte = offset+1;

		 //HAL_GPIO_WritePin(GPIOG, GPIO_PIN_9, GPIO_PIN_SET);

		 updateStateFromSPIMessage(offset);
		 //HAL_GPIO_WritePin(GPIOG, GPIO_PIN_9, GPIO_PIN_RESET);
		 //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
	}
	else if (SPI_RX[offset] == ReceivingKnobs)
	{
		uint8_t currentByte = offset+1;
		for (int i = 0; i < 8; i++)
		{
			int32_t newByte = SPI_RX[i + currentByte];
			if (prevKnobByte[i] == 256)
			{
				prevKnobByte[i] = newByte;
			}
			else if (knobFrozen[i])
			{
				if ((newByte > (prevKnobByte[i] + 3)) || (newByte < (prevKnobByte[i] - 3)))
				{
					knobFrozen[i] = 0;
					prevKnobByte[i] = newByte;
				}
			}
			else
			{
				tExpSmooth_setDest(&knobSmoothers[i], (SPI_RX[i + currentByte] * 0.003921568627451f)); //scaled 0.0 to 1.0
				prevKnobByte[i] = newByte;
			}

		}

		for (int i = 8; i < 12; i++)
		{
			int32_t newByte = SPI_RX[i + currentByte];
			if (prevKnobByte[i] == 256)
			{
				prevKnobByte[i] = newByte;
			}
			else if (knobFrozen[i])
			{
				if ((newByte > (prevKnobByte[i] + 3)) || (newByte < (prevKnobByte[i] - 3)))
				{
					knobFrozen[i] = 0;
					prevKnobByte[i] = newByte;
				}

			}
			else
			{
				tExpSmooth_setDest(&knobSmoothers[i], (newByte * 0.003921568627451f)); //scaled 0.0 to 1.0
				prevKnobByte[i] = newByte;
			}

		}

		updateStateFromSPIMessage(offset);
		//HAL_GPIO_WritePin(GPIOG, GPIO_PIN_9, GPIO_PIN_RESET);

	}
	if (SPI_RX[offset] == ReceivingMIDI)
	{

		 uint8_t currentByte = offset+1;

		 while ((SPI_RX[currentByte] != 0) && (currentByte < (SPI_FRAME_SIZE + offset - 2)))
		 {
			 cStack_push(&midiStack,SPI_RX[currentByte],SPI_RX[currentByte+1],SPI_RX[currentByte+2]);
			 currentByte = currentByte+3;
		 }
		 //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
	}



}
void __ATTR_ITCMRAM parsePreset(int size, int presetNumber)
{
	//turn off the volume while changing parameters
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
	uint16_t presetVersionNumber = 0;
	currentPresetSize = size;
	 __disable_irq();
	// presetReady = 0;
	 for (int i = 0; i < AUDIO_BUFFER_SIZE; i++)
	 {
		 audioOutBuffer[i] = 0;
	 }
	audioMasterLevel = 0.0f;
	//osc params



	presetWaitingToParse = 0;
	currentActivePreset = presetNumber;
	audioMasterLevel = 1.0f;
	//overSampled = 1;
	//changeOversampling(overSampled);
	__enable_irq();
	presetReady = 1;
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
	diskBusy = 0;

}



/////



void  __ATTR_ITCMRAM HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	SCB_CleanInvalidateDCache_by_Addr((uint32_t *)(((uint32_t )SPI_RX) & ~(uint32_t )0x1F), SPI_BUFFER_SIZE+32);
	if ((SPI_RX[62] == 254) && (SPI_RX[63] == 253))
	{
		handleSPI(SPI_FRAME_SIZE);
	}
	SCB_CleanInvalidateDCache_by_Addr((uint32_t *)(((uint32_t )SPI_RX) & ~(uint32_t )0x1F), SPI_BUFFER_SIZE+32);
}

void __ATTR_ITCMRAM HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
	SCB_CleanInvalidateDCache_by_Addr((uint32_t *)(((uint32_t )SPI_RX) & ~(uint32_t )0x1F), SPI_BUFFER_SIZE+32);
	if ((SPI_RX[30] == 254) && (SPI_RX[31] == 253))
	{
		handleSPI(0);
	}
	SCB_CleanInvalidateDCache_by_Addr((uint32_t *)(((uint32_t )SPI_RX) & ~(uint32_t )0x1F), SPI_BUFFER_SIZE+32);
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
void CycleCounterInit( void )
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

				  HAL_Delay(100);
				  HAL_NVIC_SystemReset();


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
