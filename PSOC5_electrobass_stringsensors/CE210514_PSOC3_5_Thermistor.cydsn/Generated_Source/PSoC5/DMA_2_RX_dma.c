/***************************************************************************
* File Name: DMA_2_RX_dma.c  
* Version 1.70
*
*  Description:
*   Provides an API for the DMAC component. The API includes functions
*   for the DMA controller, DMA channels and Transfer Descriptors.
*
*
*   Note:
*     This module requires the developer to finish or fill in the auto
*     generated funcions and setup the dma channel and TD's.
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#include <CYLIB.H>
#include <CYDMAC.H>
#include <DMA_2_RX_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* DMA_2_RX__DRQ_CTL_REG
* 
* 
* DMA_2_RX__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* DMA_2_RX__NUMBEROF_TDS
* 
* Priority of this channel.
* DMA_2_RX__PRIORITY
* 
* True if DMA_2_RX_TERMIN_SEL is used.
* DMA_2_RX__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* DMA_2_RX__TERMIN_SEL
* 
* 
* True if DMA_2_RX_TERMOUT0_SEL is used.
* DMA_2_RX__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* DMA_2_RX__TERMOUT0_SEL
* 
* 
* True if DMA_2_RX_TERMOUT1_SEL is used.
* DMA_2_RX__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* DMA_2_RX__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of DMA_2_RX dma channel */
uint8 DMA_2_RX_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 DMA_2_RX_DmaInitalize
**********************************************************************
* Summary:
*   Allocates and initialises a channel of the DMAC to be used by the
*   caller.
*
* Parameters:
*   BurstCount.
*       
*       
*   ReqestPerBurst.
*       
*       
*   UpperSrcAddress.
*       
*       
*   UpperDestAddress.
*       
*
* Return:
*   The channel that can be used by the caller for DMA activity.
*   DMA_INVALID_CHANNEL (0xFF) if there are no channels left. 
*
*
*******************************************************************/
uint8 DMA_2_RX_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    DMA_2_RX_DmaHandle = (uint8)DMA_2_RX__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(DMA_2_RX_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)DMA_2_RX__TERMOUT0_SEL,
                                  (uint8)DMA_2_RX__TERMOUT1_SEL,
                                  (uint8)DMA_2_RX__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(DMA_2_RX_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(DMA_2_RX_DmaHandle, (uint8)DMA_2_RX__PRIORITY);
    
    return DMA_2_RX_DmaHandle;
}

/*********************************************************************
* Function Name: void DMA_2_RX_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with DMA_2_RX.
*
*
* Parameters:
*   void.
*
*
*
* Return:
*   void.
*
*******************************************************************/
void DMA_2_RX_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(DMA_2_RX_DmaHandle);
}

