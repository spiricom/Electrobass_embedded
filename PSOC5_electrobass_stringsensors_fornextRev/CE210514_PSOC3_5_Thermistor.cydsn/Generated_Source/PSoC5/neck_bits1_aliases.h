/*******************************************************************************
* File Name: neck_bits1.h  
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

#if !defined(CY_PINS_neck_bits1_ALIASES_H) /* Pins neck_bits1_ALIASES_H */
#define CY_PINS_neck_bits1_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define neck_bits1_0			(neck_bits1__0__PC)
#define neck_bits1_0_INTR	((uint16)((uint16)0x0001u << neck_bits1__0__SHIFT))

#define neck_bits1_INTR_ALL	 ((uint16)(neck_bits1_0_INTR))

#endif /* End Pins neck_bits1_ALIASES_H */


/* [] END OF FILE */
