/*******************************************************************************
* File Name: GNDPIN.h  
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

#if !defined(CY_PINS_GNDPIN_ALIASES_H) /* Pins GNDPIN_ALIASES_H */
#define CY_PINS_GNDPIN_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define GNDPIN_0			(GNDPIN__0__PC)
#define GNDPIN_0_INTR	((uint16)((uint16)0x0001u << GNDPIN__0__SHIFT))

#define GNDPIN_INTR_ALL	 ((uint16)(GNDPIN_0_INTR))

#endif /* End Pins GNDPIN_ALIASES_H */


/* [] END OF FILE */
