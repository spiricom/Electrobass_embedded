/***************************************************************************
* File Name: USB_ep1_dma.c  
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
#include <USB_ep1_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* USB_ep1__DRQ_CTL_REG
* 
* 
* USB_ep1__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* USB_ep1__NUMBEROF_TDS
* 
* Priority of this channel.
* USB_ep1__PRIORITY
* 
* True if USB_ep1_TERMIN_SEL is used.
* USB_ep1__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* USB_ep1__TERMIN_SEL
* 
* 
* True if USB_ep1_TERMOUT0_SEL is used.
* USB_ep1__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* USB_ep1__TERMOUT0_SEL
* 
* 
* True if USB_ep1_TERMOUT1_SEL is used.
* USB_ep1__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* USB_ep1__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of USB_ep1 dma channel */
uint8 USB_ep1_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 USB_ep1_DmaInitalize
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
uint8 USB_ep1_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    USB_ep1_DmaHandle = (uint8)USB_ep1__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(USB_ep1_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)USB_ep1__TERMOUT0_SEL,
                                  (uint8)USB_ep1__TERMOUT1_SEL,
                                  (uint8)USB_ep1__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(USB_ep1_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(USB_ep1_DmaHandle, (uint8)USB_ep1__PRIORITY);
    
    return USB_ep1_DmaHandle;
}

/*********************************************************************
* Function Name: void USB_ep1_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with USB_ep1.
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
void USB_ep1_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(USB_ep1_DmaHandle);
}

