/*******************************************************************************
* File Name: otonal.h  
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

#if !defined(CY_PINS_otonal_ALIASES_H) /* Pins otonal_ALIASES_H */
#define CY_PINS_otonal_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define otonal_0			(otonal__0__PC)
#define otonal_0_INTR	((uint16)((uint16)0x0001u << otonal__0__SHIFT))

#define otonal_INTR_ALL	 ((uint16)(otonal_0_INTR))

#endif /* End Pins otonal_ALIASES_H */


/* [] END OF FILE */
