/******************************************************************************
* File Name: removeOffsetNoise.h
*  Version 2.0
*
*  This file contains the defines and function prototypes for the functions in 
* removeOffsetNoise.c flie
*
* Note:
*
********************************************************************************
* Copyright (2015), Cypress Semiconductor Corporation. All Rights Reserved.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress)
* and is protected by and subject to worldwide patent protection (United
* States and foreign), United States copyright laws and international treaty
* provisions. Cypress hereby grants to licensee a personal, non-exclusive,
* non-transferable license to copy, use, modify, create derivative works of,
* and compile the Cypress Source Code and derivative works for the sole
* purpose of creating custom software in support of licensee product to be
* used only in conjunction with a Cypress integrated circuit as specified in
* the applicable agreement. Any reproduction, modification, translation,
* compilation, or representation of this software except as specified above 
* is prohibited without the express written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH 
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the 
* materials described herein. Cypress does not assume any liability arising out 
* of the application or use of any product or circuit described herein. Cypress 
* does not authorize its products for use as critical components in life-support 
* systems where a malfunction or failure may reasonably be expected to result in 
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of 
* such use and in doing so indemnifies Cypress against all charges. 
*
* Use of this Software may be limited by and subject to the applicable Cypress
* software license agreement. 
*******************************************************************************/
#if !defined(removeOffsetNoise_H)
#define removeOffsetNoise_H

#include "device.h"

/* Filter coefficient for RTD sensor */
#define RTD_FILTER_COEFF_SHIFT          0
#define MAX_FILTER_COEFF_SHIFT			8

/* Number of sensors(readings) that require filtering */
#define NUM_SENSORS						2

/* Number of each sensor */
#define REF_RES							1
#define THERMISTOR						0

/* Filter Feedforward. It is set equal to 100 ADC counts. It has been scaled by 256 to account for MAXIMUM_FITER_COEFF  */
#define FILTER_FEEDFORWARD 				50 * 256

/* Function prototype for IIR filter */
int32 FilterSignal(int32 ADCSample, uint8 sensor);

/* Function to measure voltage across RTD sensor at zero current */
int32 GetOffset(void);

#endif

//[] END OF FILE
