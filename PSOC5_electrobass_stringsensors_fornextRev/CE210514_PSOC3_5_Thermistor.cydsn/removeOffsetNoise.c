/******************************************************************************
* File Name: removeOffsetNoise.c
*  Version 2.0
*
* Description:
*  This file contains the functions that are used to find offset and perform 
*  IIR filter
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
#include "removeOffsetNoise.h"
#include "measurement.h"
#include <device.h>

/*******************************************************************************
*  Function Name: FilterSignal
********************************************************************************
* Summary:
*  This is IIR filter to process the sampled ADC data. For first sample passed 
*  the function simply returns the passed ADC sample. for second sample onwards,
*  Fraction of input signal based upon the filter coefficient, is calculated and 
*  added to the previously stored filtered value.
*
* Parameters:
* (int32)  ADCSample       - ADC sample read for given signal
* (uint8)  Sensor		   - Sensor to be Filtered
*
* Return: 
* (int32)filValueRounded - filtered value passed is updated after applying 
* IIR filter to the ADC sample.
*
* Theory:
* For more information on the IIR filter please refer to Cypress application
* note AN2099.
*
* Side Effects:
* None
*******************************************************************************/
int32 FilterSignal(int32 ADCSample, uint8 sensor)
{
	/* Running filtered value accumulator */
	static int32 filteredValue[NUM_SENSORS] = {0,0};
	
	/* Filtered value rounded-off to 20-bits */
	int32 filValueRounded;
	
	/* Left shift input by MAX_FILTER_COEFF_SHIFT to allow divisions up to MAX_FILTER_COEFF_SHIFT */
	ADCSample <<= MAX_FILTER_COEFF_SHIFT;
	   
	/* Pass the filter input as it is for fast changes in input */
    if ( (ADCSample > (filteredValue[sensor] + FILTER_FEEDFORWARD)) || (ADCSample < (filteredValue[sensor] - FILTER_FEEDFORWARD)) )
    {
        filteredValue[sensor] = ADCSample;
    }
    
    /* If not the first sample then based on filter coefficient, filter the 
     * input signal */
    else
    {
		/* IIR filter */
		filteredValue[sensor] = filteredValue[sensor] + ((ADCSample - filteredValue[sensor]) >> RTD_FILTER_COEFF_SHIFT);			
	}
	
	/* Compensate filter result for  left shift of 8 and round off */
	filValueRounded = (filteredValue[sensor] >> MAX_FILTER_COEFF_SHIFT) + ((filteredValue[sensor] & 0x00000080) >> (MAX_FILTER_COEFF_SHIFT - 1));
	
    return filValueRounded;
}

/*******************************************************************************
*  Function Name: GetOffset
********************************************************************************
* Summary:
* This function shorts the inputs of the ADC together and reads the offset. 
*
* Parameters:
* void:
*
* Return:
* int32: result (offset value).
*
* Theory:
*
* Side Effects:
* None
*******************************************************************************/
int32 GetOffset(void)
{
	int32 result;

  	/*Select the MUX channel and Measure the offset voltage*/	
	//AMux_FastSelect(AMUX_1_CDS);
    //ADC_StartConvert();
	//ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
	//result = ADC_GetResult32();

    return result;
}

/* [] END OF FILE */
