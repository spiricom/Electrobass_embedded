/*******************************************************************************
* File Name: I2C_Pins.h  
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

#if !defined(CY_PINS_I2C_Pins_ALIASES_H) /* Pins I2C_Pins_ALIASES_H */
#define CY_PINS_I2C_Pins_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define I2C_Pins_0			(I2C_Pins__0__PC)
#define I2C_Pins_0_INTR	((uint16)((uint16)0x0001u << I2C_Pins__0__SHIFT))

#define I2C_Pins_1			(I2C_Pins__1__PC)
#define I2C_Pins_1_INTR	((uint16)((uint16)0x0001u << I2C_Pins__1__SHIFT))

#define I2C_Pins_INTR_ALL	 ((uint16)(I2C_Pins_0_INTR| I2C_Pins_1_INTR))
#define I2C_Pins_scl			(I2C_Pins__scl__PC)
#define I2C_Pins_scl_INTR	((uint16)((uint16)0x0001u << I2C_Pins__0__SHIFT))

#define I2C_Pins_sda			(I2C_Pins__sda__PC)
#define I2C_Pins_sda_INTR	((uint16)((uint16)0x0001u << I2C_Pins__1__SHIFT))

#endif /* End Pins I2C_Pins_ALIASES_H */


/* [] END OF FILE */
