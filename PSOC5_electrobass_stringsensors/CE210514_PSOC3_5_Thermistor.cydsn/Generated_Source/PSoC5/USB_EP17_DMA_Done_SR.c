/*******************************************************************************
* File Name: USB_EP17_DMA_Done_SR.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware to read the value of a Status 
*  Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "USB_EP17_DMA_Done_SR.h"

#if !defined(USB_EP17_DMA_Done_SR_sts_intr_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: USB_EP17_DMA_Done_SR_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The current value in the Status Register.
*
*******************************************************************************/
uint8 USB_EP17_DMA_Done_SR_Read(void) 
{ 
    return USB_EP17_DMA_Done_SR_Status;
}


/*******************************************************************************
* Function Name: USB_EP17_DMA_Done_SR_InterruptEnable
********************************************************************************
*
* Summary:
*  Enables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void USB_EP17_DMA_Done_SR_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    USB_EP17_DMA_Done_SR_Status_Aux_Ctrl |= USB_EP17_DMA_Done_SR_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: USB_EP17_DMA_Done_SR_InterruptDisable
********************************************************************************
*
* Summary:
*  Disables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void USB_EP17_DMA_Done_SR_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    USB_EP17_DMA_Done_SR_Status_Aux_Ctrl &= (uint8)(~USB_EP17_DMA_Done_SR_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: USB_EP17_DMA_Done_SR_WriteMask
********************************************************************************
*
* Summary:
*  Writes the current mask value assigned to the Status Register.
*
* Parameters:
*  mask:  Value to write into the mask register.
*
* Return:
*  None.
*
*******************************************************************************/
void USB_EP17_DMA_Done_SR_WriteMask(uint8 mask) 
{
    #if(USB_EP17_DMA_Done_SR_INPUTS < 8u)
    	mask &= ((uint8)(1u << USB_EP17_DMA_Done_SR_INPUTS) - 1u);
	#endif /* End USB_EP17_DMA_Done_SR_INPUTS < 8u */
    USB_EP17_DMA_Done_SR_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: USB_EP17_DMA_Done_SR_ReadMask
********************************************************************************
*
* Summary:
*  Reads the current interrupt mask assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the interrupt mask of the Status Register.
*
*******************************************************************************/
uint8 USB_EP17_DMA_Done_SR_ReadMask(void) 
{
    return USB_EP17_DMA_Done_SR_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
