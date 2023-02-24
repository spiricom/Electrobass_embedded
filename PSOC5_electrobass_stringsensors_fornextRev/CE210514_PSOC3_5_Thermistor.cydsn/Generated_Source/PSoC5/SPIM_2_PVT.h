/*******************************************************************************
* File Name: .h
* Version 2.50
*
* Description:
*  This private header file contains internal definitions for the SPIM
*  component. Do not use these definitions directly in your application.
*
* Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIM_PVT_SPIM_2_H)
#define CY_SPIM_PVT_SPIM_2_H

#include "SPIM_2.h"


/**********************************
*   Functions with external linkage
**********************************/


/**********************************
*   Variables with external linkage
**********************************/

extern volatile uint8 SPIM_2_swStatusTx;
extern volatile uint8 SPIM_2_swStatusRx;

#if(SPIM_2_TX_SOFTWARE_BUF_ENABLED)
    extern volatile uint8 SPIM_2_txBuffer[SPIM_2_TX_BUFFER_SIZE];
    extern volatile uint8 SPIM_2_txBufferRead;
    extern volatile uint8 SPIM_2_txBufferWrite;
    extern volatile uint8 SPIM_2_txBufferFull;
#endif /* (SPIM_2_TX_SOFTWARE_BUF_ENABLED) */

#if(SPIM_2_RX_SOFTWARE_BUF_ENABLED)
    extern volatile uint8 SPIM_2_rxBuffer[SPIM_2_RX_BUFFER_SIZE];
    extern volatile uint8 SPIM_2_rxBufferRead;
    extern volatile uint8 SPIM_2_rxBufferWrite;
    extern volatile uint8 SPIM_2_rxBufferFull;
#endif /* (SPIM_2_RX_SOFTWARE_BUF_ENABLED) */

#endif /* CY_SPIM_PVT_SPIM_2_H */


/* [] END OF FILE */
