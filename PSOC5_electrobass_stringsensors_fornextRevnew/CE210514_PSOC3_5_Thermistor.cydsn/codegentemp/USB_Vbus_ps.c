/*******************************************************************************
* File Name: USB_Vbus_ps.c  
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

#include "USB_Vbus_ps.h"

#if !defined(USB_Vbus_ps_sts_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: USB_Vbus_ps_Read
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
uint8 USB_Vbus_ps_Read(void) 
{ 
    return USB_Vbus_ps_Status;
}


/*******************************************************************************
* Function Name: USB_Vbus_ps_InterruptEnable
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
void USB_Vbus_ps_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    USB_Vbus_ps_Status_Aux_Ctrl |= USB_Vbus_ps_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: USB_Vbus_ps_InterruptDisable
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
void USB_Vbus_ps_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    USB_Vbus_ps_Status_Aux_Ctrl &= (uint8)(~USB_Vbus_ps_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: USB_Vbus_ps_WriteMask
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
void USB_Vbus_ps_WriteMask(uint8 mask) 
{
    #if(USB_Vbus_ps_INPUTS < 8u)
    	mask &= ((uint8)(1u << USB_Vbus_ps_INPUTS) - 1u);
	#endif /* End USB_Vbus_ps_INPUTS < 8u */
    USB_Vbus_ps_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: USB_Vbus_ps_ReadMask
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
uint8 USB_Vbus_ps_ReadMask(void) 
{
    return USB_Vbus_ps_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
