/*******************************************************************************
* File Name: SPIM_2_PM.c
* Version 2.50
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPIM_2_PVT.h"

static SPIM_2_BACKUP_STRUCT SPIM_2_backup =
{
    SPIM_2_DISABLED,
    SPIM_2_BITCTR_INIT,
};


/*******************************************************************************
* Function Name: SPIM_2_SaveConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SPIM_2_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPIM_2_RestoreConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SPIM_2_RestoreConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPIM_2_Sleep
********************************************************************************
*
* Summary:
*  Prepare SPIM Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPIM_2_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPIM_2_Sleep(void) 
{
    /* Save components enable state */
    SPIM_2_backup.enableState = ((uint8) SPIM_2_IS_ENABLED);

    SPIM_2_Stop();
}


/*******************************************************************************
* Function Name: SPIM_2_Wakeup
********************************************************************************
*
* Summary:
*  Prepare SPIM Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPIM_2_backup - used when non-retention registers are restored.
*  SPIM_2_txBufferWrite - modified every function call - resets to
*  zero.
*  SPIM_2_txBufferRead - modified every function call - resets to
*  zero.
*  SPIM_2_rxBufferWrite - modified every function call - resets to
*  zero.
*  SPIM_2_rxBufferRead - modified every function call - resets to
*  zero.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPIM_2_Wakeup(void) 
{
    #if(SPIM_2_RX_SOFTWARE_BUF_ENABLED)
        SPIM_2_rxBufferFull  = 0u;
        SPIM_2_rxBufferRead  = 0u;
        SPIM_2_rxBufferWrite = 0u;
    #endif /* (SPIM_2_RX_SOFTWARE_BUF_ENABLED) */

    #if(SPIM_2_TX_SOFTWARE_BUF_ENABLED)
        SPIM_2_txBufferFull  = 0u;
        SPIM_2_txBufferRead  = 0u;
        SPIM_2_txBufferWrite = 0u;
    #endif /* (SPIM_2_TX_SOFTWARE_BUF_ENABLED) */

    /* Clear any data from the RX and TX FIFO */
    SPIM_2_ClearFIFO();

    /* Restore components block enable state */
    if(0u != SPIM_2_backup.enableState)
    {
        SPIM_2_Enable();
    }
}


/* [] END OF FILE */
