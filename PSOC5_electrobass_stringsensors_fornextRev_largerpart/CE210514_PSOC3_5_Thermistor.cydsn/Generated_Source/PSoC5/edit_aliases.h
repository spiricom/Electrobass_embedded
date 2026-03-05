/*******************************************************************************
* File Name: edit.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_edit_ALIASES_H) /* Pins edit_ALIASES_H */
#define CY_PINS_edit_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define edit_0			(edit__0__PC)
#define edit_0_INTR	((uint16)((uint16)0x0001u << edit__0__SHIFT))

#define edit_INTR_ALL	 ((uint16)(edit_0_INTR))

#endif /* End Pins edit_ALIASES_H */


/* [] END OF FILE */
