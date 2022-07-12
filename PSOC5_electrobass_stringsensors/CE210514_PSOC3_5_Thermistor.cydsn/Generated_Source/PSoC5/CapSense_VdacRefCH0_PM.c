/*******************************************************************************
* File Name: CapSense_VdacRefCH0_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
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

#include "CapSense_VdacRefCH0.h"

static CapSense_VdacRefCH0_backupStruct CapSense_VdacRefCH0_backup;


/*******************************************************************************
* Function Name: CapSense_VdacRefCH0_SaveConfig
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
void CapSense_VdacRefCH0_SaveConfig(void) 
{
    if (!((CapSense_VdacRefCH0_CR1 & CapSense_VdacRefCH0_SRC_MASK) == CapSense_VdacRefCH0_SRC_UDB))
    {
        CapSense_VdacRefCH0_backup.data_value = CapSense_VdacRefCH0_Data;
    }
}


/*******************************************************************************
* Function Name: CapSense_VdacRefCH0_RestoreConfig
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
void CapSense_VdacRefCH0_RestoreConfig(void) 
{
    if (!((CapSense_VdacRefCH0_CR1 & CapSense_VdacRefCH0_SRC_MASK) == CapSense_VdacRefCH0_SRC_UDB))
    {
        if((CapSense_VdacRefCH0_Strobe & CapSense_VdacRefCH0_STRB_MASK) == CapSense_VdacRefCH0_STRB_EN)
        {
            CapSense_VdacRefCH0_Strobe &= (uint8)(~CapSense_VdacRefCH0_STRB_MASK);
            CapSense_VdacRefCH0_Data = CapSense_VdacRefCH0_backup.data_value;
            CapSense_VdacRefCH0_Strobe |= CapSense_VdacRefCH0_STRB_EN;
        }
        else
        {
            CapSense_VdacRefCH0_Data = CapSense_VdacRefCH0_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: CapSense_VdacRefCH0_Sleep
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
*  CapSense_VdacRefCH0_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void CapSense_VdacRefCH0_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(CapSense_VdacRefCH0_ACT_PWR_EN == (CapSense_VdacRefCH0_PWRMGR & CapSense_VdacRefCH0_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        CapSense_VdacRefCH0_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        CapSense_VdacRefCH0_backup.enableState = 0u;
    }
    
    CapSense_VdacRefCH0_Stop();
    CapSense_VdacRefCH0_SaveConfig();
}


/*******************************************************************************
* Function Name: CapSense_VdacRefCH0_Wakeup
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
*  CapSense_VdacRefCH0_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CapSense_VdacRefCH0_Wakeup(void) 
{
    CapSense_VdacRefCH0_RestoreConfig();
    
    if(CapSense_VdacRefCH0_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        CapSense_VdacRefCH0_Enable();

        /* Restore the data register */
        CapSense_VdacRefCH0_SetValue(CapSense_VdacRefCH0_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
