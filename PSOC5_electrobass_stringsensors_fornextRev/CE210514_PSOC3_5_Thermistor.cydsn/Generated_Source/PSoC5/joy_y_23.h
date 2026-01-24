/*******************************************************************************
* File Name: joy_y_23.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_joy_y_23_H) /* Pins joy_y_23_H */
#define CY_PINS_joy_y_23_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "joy_y_23_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 joy_y_23__PORT == 15 && ((joy_y_23__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    joy_y_23_Write(uint8 value);
void    joy_y_23_SetDriveMode(uint8 mode);
uint8   joy_y_23_ReadDataReg(void);
uint8   joy_y_23_Read(void);
void    joy_y_23_SetInterruptMode(uint16 position, uint16 mode);
uint8   joy_y_23_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the joy_y_23_SetDriveMode() function.
     *  @{
     */
        #define joy_y_23_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define joy_y_23_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define joy_y_23_DM_RES_UP          PIN_DM_RES_UP
        #define joy_y_23_DM_RES_DWN         PIN_DM_RES_DWN
        #define joy_y_23_DM_OD_LO           PIN_DM_OD_LO
        #define joy_y_23_DM_OD_HI           PIN_DM_OD_HI
        #define joy_y_23_DM_STRONG          PIN_DM_STRONG
        #define joy_y_23_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define joy_y_23_MASK               joy_y_23__MASK
#define joy_y_23_SHIFT              joy_y_23__SHIFT
#define joy_y_23_WIDTH              1u

/* Interrupt constants */
#if defined(joy_y_23__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in joy_y_23_SetInterruptMode() function.
     *  @{
     */
        #define joy_y_23_INTR_NONE      (uint16)(0x0000u)
        #define joy_y_23_INTR_RISING    (uint16)(0x0001u)
        #define joy_y_23_INTR_FALLING   (uint16)(0x0002u)
        #define joy_y_23_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define joy_y_23_INTR_MASK      (0x01u) 
#endif /* (joy_y_23__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define joy_y_23_PS                     (* (reg8 *) joy_y_23__PS)
/* Data Register */
#define joy_y_23_DR                     (* (reg8 *) joy_y_23__DR)
/* Port Number */
#define joy_y_23_PRT_NUM                (* (reg8 *) joy_y_23__PRT) 
/* Connect to Analog Globals */                                                  
#define joy_y_23_AG                     (* (reg8 *) joy_y_23__AG)                       
/* Analog MUX bux enable */
#define joy_y_23_AMUX                   (* (reg8 *) joy_y_23__AMUX) 
/* Bidirectional Enable */                                                        
#define joy_y_23_BIE                    (* (reg8 *) joy_y_23__BIE)
/* Bit-mask for Aliased Register Access */
#define joy_y_23_BIT_MASK               (* (reg8 *) joy_y_23__BIT_MASK)
/* Bypass Enable */
#define joy_y_23_BYP                    (* (reg8 *) joy_y_23__BYP)
/* Port wide control signals */                                                   
#define joy_y_23_CTL                    (* (reg8 *) joy_y_23__CTL)
/* Drive Modes */
#define joy_y_23_DM0                    (* (reg8 *) joy_y_23__DM0) 
#define joy_y_23_DM1                    (* (reg8 *) joy_y_23__DM1)
#define joy_y_23_DM2                    (* (reg8 *) joy_y_23__DM2) 
/* Input Buffer Disable Override */
#define joy_y_23_INP_DIS                (* (reg8 *) joy_y_23__INP_DIS)
/* LCD Common or Segment Drive */
#define joy_y_23_LCD_COM_SEG            (* (reg8 *) joy_y_23__LCD_COM_SEG)
/* Enable Segment LCD */
#define joy_y_23_LCD_EN                 (* (reg8 *) joy_y_23__LCD_EN)
/* Slew Rate Control */
#define joy_y_23_SLW                    (* (reg8 *) joy_y_23__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define joy_y_23_PRTDSI__CAPS_SEL       (* (reg8 *) joy_y_23__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define joy_y_23_PRTDSI__DBL_SYNC_IN    (* (reg8 *) joy_y_23__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define joy_y_23_PRTDSI__OE_SEL0        (* (reg8 *) joy_y_23__PRTDSI__OE_SEL0) 
#define joy_y_23_PRTDSI__OE_SEL1        (* (reg8 *) joy_y_23__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define joy_y_23_PRTDSI__OUT_SEL0       (* (reg8 *) joy_y_23__PRTDSI__OUT_SEL0) 
#define joy_y_23_PRTDSI__OUT_SEL1       (* (reg8 *) joy_y_23__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define joy_y_23_PRTDSI__SYNC_OUT       (* (reg8 *) joy_y_23__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(joy_y_23__SIO_CFG)
    #define joy_y_23_SIO_HYST_EN        (* (reg8 *) joy_y_23__SIO_HYST_EN)
    #define joy_y_23_SIO_REG_HIFREQ     (* (reg8 *) joy_y_23__SIO_REG_HIFREQ)
    #define joy_y_23_SIO_CFG            (* (reg8 *) joy_y_23__SIO_CFG)
    #define joy_y_23_SIO_DIFF           (* (reg8 *) joy_y_23__SIO_DIFF)
#endif /* (joy_y_23__SIO_CFG) */

/* Interrupt Registers */
#if defined(joy_y_23__INTSTAT)
    #define joy_y_23_INTSTAT            (* (reg8 *) joy_y_23__INTSTAT)
    #define joy_y_23_SNAP               (* (reg8 *) joy_y_23__SNAP)
    
	#define joy_y_23_0_INTTYPE_REG 		(* (reg8 *) joy_y_23__0__INTTYPE)
#endif /* (joy_y_23__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_joy_y_23_H */


/* [] END OF FILE */
