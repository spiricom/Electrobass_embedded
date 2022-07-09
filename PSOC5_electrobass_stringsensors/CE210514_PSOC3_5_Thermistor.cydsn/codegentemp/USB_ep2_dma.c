/***************************************************************************
* File Name: USB_ep2_dma.c  
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
#include <USB_ep2_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* USB_ep2__DRQ_CTL_REG
* 
* 
* USB_ep2__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* USB_ep2__NUMBEROF_TDS
* 
* Priority of this channel.
* USB_ep2__PRIORITY
* 
* True if USB_ep2_TERMIN_SEL is used.
* USB_ep2__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* USB_ep2__TERMIN_SEL
* 
* 
* True if USB_ep2_TERMOUT0_SEL is used.
* USB_ep2__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* USB_ep2__TERMOUT0_SEL
* 
* 
* True if USB_ep2_TERMOUT1_SEL is used.
* USB_ep2__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* USB_ep2__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of USB_ep2 dma channel */
uint8 USB_ep2_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 USB_ep2_DmaInitalize
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
uint8 USB_ep2_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    USB_ep2_DmaHandle = (uint8)USB_ep2__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(USB_ep2_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)USB_ep2__TERMOUT0_SEL,
                                  (uint8)USB_ep2__TERMOUT1_SEL,
                                  (uint8)USB_ep2__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(USB_ep2_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(USB_ep2_DmaHandle, (uint8)USB_ep2__PRIORITY);
    
    return USB_ep2_DmaHandle;
}

/*********************************************************************
* Function Name: void USB_ep2_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with USB_ep2.
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
void USB_ep2_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(USB_ep2_DmaHandle);
}

