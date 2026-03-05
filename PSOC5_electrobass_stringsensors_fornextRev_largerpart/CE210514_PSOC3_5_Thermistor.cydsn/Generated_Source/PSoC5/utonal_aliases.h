/*******************************************************************************
* File Name: utonal.h  
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

#if !defined(CY_PINS_utonal_ALIASES_H) /* Pins utonal_ALIASES_H */
#define CY_PINS_utonal_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define utonal_0			(utonal__0__PC)
#define utonal_0_INTR	((uint16)((uint16)0x0001u << utonal__0__SHIFT))

#define utonal_INTR_ALL	 ((uint16)(utonal_0_INTR))

#endif /* End Pins utonal_ALIASES_H */


/* [] END OF FILE */
