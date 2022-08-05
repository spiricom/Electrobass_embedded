/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "parameters.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
#define __ATTR_RAM_D1	__attribute__ ((section(".sram2_bss"))) __attribute__ ((aligned (32)))
#define __ATTR_RAM_D2	__attribute__ ((section(".sram1_bss"))) __attribute__ ((aligned (32)))
//#define __ATTR_RAM_D3	__attribute__ ((section(".sramd3_bss"))) __attribute__ ((aligned (32)))
#define __ATTR_SDRAM	__attribute__ ((section(".sdram_bss"))) __attribute__ ((aligned (32)))
#define __ATTR_DTCMRAM	__attribute__ ((section(".dtcmram_bss"))) __attribute__ ((aligned (32)))
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */


#define NUM_PARAMS numParams
#define MAX_NUM_MAPPINGS 32
extern param params[NUM_PARAMS];
extern mapping mappings[MAX_NUM_MAPPINGS];
extern volatile uint8_t muteAudio;
extern uint8_t numMappings;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
float randomNumber(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
