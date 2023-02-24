/*******************************************************************************
* File Name: CapSense_CompCH1.c
* Version 2.0
*
* Description:
*  This file provides the power management source code APIs for the
*  Comparator.
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

#include "CapSense_CompCH1.h"

static CapSense_CompCH1_backupStruct CapSense_CompCH1_backup;


/*******************************************************************************
* Function Name: CapSense_CompCH1_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
*******************************************************************************/
void CapSense_CompCH1_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: CapSense_CompCH1_RestoreConfig
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
********************************************************************************/
void CapSense_CompCH1_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: CapSense_CompCH1_Sleep
********************************************************************************
*
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
*  CapSense_CompCH1_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void CapSense_CompCH1_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(CapSense_CompCH1_ACT_PWR_EN == (CapSense_CompCH1_PWRMGR & CapSense_CompCH1_ACT_PWR_EN))
    {
        /* Comp is enabled */
        CapSense_CompCH1_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        CapSense_CompCH1_backup.enableState = 0u;
    }    
    
    CapSense_CompCH1_Stop();
    CapSense_CompCH1_SaveConfig();
}


/*******************************************************************************
* Function Name: CapSense_CompCH1_Wakeup
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
*  CapSense_CompCH1_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CapSense_CompCH1_Wakeup(void) 
{
    CapSense_CompCH1_RestoreConfig();
    
    if(CapSense_CompCH1_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        CapSense_CompCH1_Enable();

    } /* Do nothing if Comp was disabled before */ 
}


/* [] END OF FILE */
