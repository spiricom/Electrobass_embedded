/*******************************************************************************
* File Name: CapSense_IdacCH1.c
* Version 2.0
*
* Description:
*  This file provides the power management source code to API for the
*  IDAC8.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include "CapSense_IdacCH1.h"

static CapSense_IdacCH1_backupStruct CapSense_IdacCH1_backup;


/*******************************************************************************
* Function Name: CapSense_IdacCH1_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void CapSense_IdacCH1_SaveConfig(void) 
{
    if (!((CapSense_IdacCH1_CR1 & CapSense_IdacCH1_SRC_MASK) == CapSense_IdacCH1_SRC_UDB))
    {
        CapSense_IdacCH1_backup.data_value = CapSense_IdacCH1_Data;
    }
}


/*******************************************************************************
* Function Name: CapSense_IdacCH1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void CapSense_IdacCH1_RestoreConfig(void) 
{
    if (!((CapSense_IdacCH1_CR1 & CapSense_IdacCH1_SRC_MASK) == CapSense_IdacCH1_SRC_UDB))
    {
        if((CapSense_IdacCH1_Strobe & CapSense_IdacCH1_STRB_MASK) == CapSense_IdacCH1_STRB_EN)
        {
            CapSense_IdacCH1_Strobe &= (uint8)(~CapSense_IdacCH1_STRB_MASK);
            CapSense_IdacCH1_Data = CapSense_IdacCH1_backup.data_value;
            CapSense_IdacCH1_Strobe |= CapSense_IdacCH1_STRB_EN;
        }
        else
        {
            CapSense_IdacCH1_Data = CapSense_IdacCH1_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: CapSense_IdacCH1_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
* Global variables:
*  CapSense_IdacCH1_backup.enableState: Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void CapSense_IdacCH1_Sleep(void) 
{
    if(CapSense_IdacCH1_ACT_PWR_EN == (CapSense_IdacCH1_PWRMGR & CapSense_IdacCH1_ACT_PWR_EN))
    {
        /* IDAC8 is enabled */
        CapSense_IdacCH1_backup.enableState = 1u;
    }
    else
    {
        /* IDAC8 is disabled */
        CapSense_IdacCH1_backup.enableState = 0u;
    }

    CapSense_IdacCH1_Stop();
    CapSense_IdacCH1_SaveConfig();
}


/*******************************************************************************
* Function Name: CapSense_IdacCH1_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  CapSense_IdacCH1_backup.enableState: Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CapSense_IdacCH1_Wakeup(void) 
{
    CapSense_IdacCH1_RestoreConfig();
    
    if(CapSense_IdacCH1_backup.enableState == 1u)
    {
        /* Enable IDAC8's operation */
        CapSense_IdacCH1_Enable();
        
        /* Set the data register */
        CapSense_IdacCH1_SetValue(CapSense_IdacCH1_Data);
    } /* Do nothing if IDAC8 was disabled before */    
}


/* [] END OF FILE */
