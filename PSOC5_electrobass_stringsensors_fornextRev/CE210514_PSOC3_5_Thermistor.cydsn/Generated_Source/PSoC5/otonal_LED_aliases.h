/*******************************************************************************
* File Name: otonal_LED.h  
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

#if !defined(CY_PINS_otonal_LED_ALIASES_H) /* Pins otonal_LED_ALIASES_H */
#define CY_PINS_otonal_LED_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define otonal_LED_0			(otonal_LED__0__PC)
#define otonal_LED_0_INTR	((uint16)((uint16)0x0001u << otonal_LED__0__SHIFT))

#define otonal_LED_INTR_ALL	 ((uint16)(otonal_LED_0_INTR))

#endif /* End Pins otonal_LED_ALIASES_H */


/* [] END OF FILE */
