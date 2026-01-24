/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
/*******************************************************************************
* File Name: main.c
*
* Version: 2.40
*
* Description:
*  The project explains the usage of CapSense CSD component. The 2 buttons and
*  linear sliders are used as sensing elements. LED displays buttons active
*  state and slider position is shown on LCD.
*
********************************************************************************
* Copyright 2012-2014, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <project.h>

void CapSense_DisplayState(void);

uint8_t fiveValuePos = 1;
uint8_t oldFiveValuePos = 1;

uint16 curPos = 0;
uint16_t oldPos = 1;
/* Buffer and packet size */
#define BUFFER_SIZE         (0x04)
    
    
/* The EZI2C slave buffer for Write and Read */
uint8 ezI2cBuffer[BUFFER_SIZE]; 
/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*  Main function performs following functions:
*   1. Enable global interrupts.
*   2. Initialize CapSense CSD and Start the sensor scanning loop.
*   3. Process scanning results and display it on LCD/LED.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
int main()
{
    /* Enable global interrupts */
    CyGlobalIntEnable;
    
   
    CapSense_Start();
    /* Set up a buffer and start the EZI2C slave (SCB mode) */
    EZI2C_EzI2CSetBuffer1(BUFFER_SIZE, 1, ezI2cBuffer);
    EZI2C_Start();

    /* Initialize baselines */
    CapSense_InitializeAllBaselines();

 while(1u)
    {
        /* Check whether the scanning of all enabled widgets is completed. */
        if(0u == CapSense_IsBusy())
        {
            /* Update all baselines */
            CapSense_UpdateEnabledBaselines();

            /* Start scanning all enabled sensors */
            CapSense_ScanEnabledWidgets();
        }

        /* Display CapSense state using LED/LCD */
        CapSense_DisplayState();
        
                /* The Write is complete: parse the packet */
        //if (0 != (EZI2C_EzI2CGetActivity() & EZI2C_EZI2C_STATUS_READ1))
        //{      
              ezI2cBuffer[1] = fiveValuePos;
            ezI2cBuffer[2] = CapSense_SensorSignal[CapSense_SENSOR_BUTTON0__BTN];
            ezI2cBuffer[3] = CapSense_SensorSignal[CapSense_SENSOR_BUTTON1__BTN];
        //}
    }
}

/*******************************************************************************
* Function Name: CapSense_DisplayState
********************************************************************************
* Summary:
*  Function performs following functions:
*   Display Buttons' state using LEDs and Slider state using LCD bargraph
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CapSense_DisplayState(void)
{


    /* Find Slider Position */
    curPos = CapSense_GetCentroidPos(CapSense_LINEARSLIDER0__LS);

    /* Reset position */
    if(curPos == 0xFFFFu)
    {
        //Pin_1_Write(0);
        //Pin_2_Write(0);
        //Pin_3_Write(0);
        //Pin_4_Write(0);
        //Pin_5_Write(0);
        //curPos = oldPos;
        fiveValuePos = oldFiveValuePos;
        //return;
    }
    else
    {
        fiveValuePos = 4 - (curPos / 51);
        if (fiveValuePos > 4)
        {
            fiveValuePos = 4;
        }
        oldFiveValuePos = fiveValuePos;
    }

    /* Move bargraph */
    if (curPos != oldPos)
    {
        oldPos = curPos;
        /* Display Slider bargraph */
        if (fiveValuePos == 0)
        {
            Pin_1_Write(0);
            Pin_2_Write(0);
            Pin_3_Write(0);
            Pin_4_Write(0);
            Pin_5_Write(1);
        }
        else if (fiveValuePos == 1)
        {
            Pin_1_Write(0);
            Pin_2_Write(0);
            Pin_3_Write(0);
            Pin_4_Write(1);
            Pin_5_Write(0);
        }
        else if (fiveValuePos == 2)
        {
            Pin_1_Write(0);
            Pin_2_Write(0);
            Pin_3_Write(1);
            Pin_4_Write(0);
            Pin_5_Write(0);
        }
        else if (fiveValuePos == 3)
        {
            Pin_1_Write(0);
            Pin_2_Write(1);
            Pin_3_Write(0);
            Pin_4_Write(0);
            Pin_5_Write(0);
        }
        else if (fiveValuePos == 4)
        {
            Pin_1_Write(1);
            Pin_2_Write(0);
            Pin_3_Write(0);
            Pin_4_Write(0);
            Pin_5_Write(0);
        }
    }
}
/* [] END OF FILE */
