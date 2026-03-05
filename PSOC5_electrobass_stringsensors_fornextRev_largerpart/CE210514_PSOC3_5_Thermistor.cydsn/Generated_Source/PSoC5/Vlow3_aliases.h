/*******************************************************************************
* File Name: Vlow3.h  
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

#if !defined(CY_PINS_Vlow3_ALIASES_H) /* Pins Vlow3_ALIASES_H */
#define CY_PINS_Vlow3_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Vlow3_0			(Vlow3__0__PC)
#define Vlow3_0_INTR	((uint16)((uint16)0x0001u << Vlow3__0__SHIFT))

#define Vlow3_INTR_ALL	 ((uint16)(Vlow3_0_INTR))

#endif /* End Pins Vlow3_ALIASES_H */


/* [] END OF FILE */
