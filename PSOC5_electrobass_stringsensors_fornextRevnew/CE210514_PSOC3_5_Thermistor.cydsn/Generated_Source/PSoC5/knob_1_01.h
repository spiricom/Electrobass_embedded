/*******************************************************************************
* File Name: knob_1_01.h  
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

#if !defined(CY_PINS_knob_1_01_H) /* Pins knob_1_01_H */
#define CY_PINS_knob_1_01_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "knob_1_01_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 knob_1_01__PORT == 15 && ((knob_1_01__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    knob_1_01_Write(uint8 value);
void    knob_1_01_SetDriveMode(uint8 mode);
uint8   knob_1_01_ReadDataReg(void);
uint8   knob_1_01_Read(void);
void    knob_1_01_SetInterruptMode(uint16 position, uint16 mode);
uint8   knob_1_01_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the knob_1_01_SetDriveMode() function.
     *  @{
     */
        #define knob_1_01_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define knob_1_01_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define knob_1_01_DM_RES_UP          PIN_DM_RES_UP
        #define knob_1_01_DM_RES_DWN         PIN_DM_RES_DWN
        #define knob_1_01_DM_OD_LO           PIN_DM_OD_LO
        #define knob_1_01_DM_OD_HI           PIN_DM_OD_HI
        #define knob_1_01_DM_STRONG          PIN_DM_STRONG
        #define knob_1_01_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define knob_1_01_MASK               knob_1_01__MASK
#define knob_1_01_SHIFT              knob_1_01__SHIFT
#define knob_1_01_WIDTH              1u

/* Interrupt constants */
#if defined(knob_1_01__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in knob_1_01_SetInterruptMode() function.
     *  @{
     */
        #define knob_1_01_INTR_NONE      (uint16)(0x0000u)
        #define knob_1_01_INTR_RISING    (uint16)(0x0001u)
        #define knob_1_01_INTR_FALLING   (uint16)(0x0002u)
        #define knob_1_01_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define knob_1_01_INTR_MASK      (0x01u) 
#endif /* (knob_1_01__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define knob_1_01_PS                     (* (reg8 *) knob_1_01__PS)
/* Data Register */
#define knob_1_01_DR                     (* (reg8 *) knob_1_01__DR)
/* Port Number */
#define knob_1_01_PRT_NUM                (* (reg8 *) knob_1_01__PRT) 
/* Connect to Analog Globals */                                                  
#define knob_1_01_AG                     (* (reg8 *) knob_1_01__AG)                       
/* Analog MUX bux enable */
#define knob_1_01_AMUX                   (* (reg8 *) knob_1_01__AMUX) 
/* Bidirectional Enable */                                                        
#define knob_1_01_BIE                    (* (reg8 *) knob_1_01__BIE)
/* Bit-mask for Aliased Register Access */
#define knob_1_01_BIT_MASK               (* (reg8 *) knob_1_01__BIT_MASK)
/* Bypass Enable */
#define knob_1_01_BYP                    (* (reg8 *) knob_1_01__BYP)
/* Port wide control signals */                                                   
#define knob_1_01_CTL                    (* (reg8 *) knob_1_01__CTL)
/* Drive Modes */
#define knob_1_01_DM0                    (* (reg8 *) knob_1_01__DM0) 
#define knob_1_01_DM1                    (* (reg8 *) knob_1_01__DM1)
#define knob_1_01_DM2                    (* (reg8 *) knob_1_01__DM2) 
/* Input Buffer Disable Override */
#define knob_1_01_INP_DIS                (* (reg8 *) knob_1_01__INP_DIS)
/* LCD Common or Segment Drive */
#define knob_1_01_LCD_COM_SEG            (* (reg8 *) knob_1_01__LCD_COM_SEG)
/* Enable Segment LCD */
#define knob_1_01_LCD_EN                 (* (reg8 *) knob_1_01__LCD_EN)
/* Slew Rate Control */
#define knob_1_01_SLW                    (* (reg8 *) knob_1_01__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define knob_1_01_PRTDSI__CAPS_SEL       (* (reg8 *) knob_1_01__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define knob_1_01_PRTDSI__DBL_SYNC_IN    (* (reg8 *) knob_1_01__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define knob_1_01_PRTDSI__OE_SEL0        (* (reg8 *) knob_1_01__PRTDSI__OE_SEL0) 
#define knob_1_01_PRTDSI__OE_SEL1        (* (reg8 *) knob_1_01__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define knob_1_01_PRTDSI__OUT_SEL0       (* (reg8 *) knob_1_01__PRTDSI__OUT_SEL0) 
#define knob_1_01_PRTDSI__OUT_SEL1       (* (reg8 *) knob_1_01__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define knob_1_01_PRTDSI__SYNC_OUT       (* (reg8 *) knob_1_01__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(knob_1_01__SIO_CFG)
    #define knob_1_01_SIO_HYST_EN        (* (reg8 *) knob_1_01__SIO_HYST_EN)
    #define knob_1_01_SIO_REG_HIFREQ     (* (reg8 *) knob_1_01__SIO_REG_HIFREQ)
    #define knob_1_01_SIO_CFG            (* (reg8 *) knob_1_01__SIO_CFG)
    #define knob_1_01_SIO_DIFF           (* (reg8 *) knob_1_01__SIO_DIFF)
#endif /* (knob_1_01__SIO_CFG) */

/* Interrupt Registers */
#if defined(knob_1_01__INTSTAT)
    #define knob_1_01_INTSTAT            (* (reg8 *) knob_1_01__INTSTAT)
    #define knob_1_01_SNAP               (* (reg8 *) knob_1_01__SNAP)
    
	#define knob_1_01_0_INTTYPE_REG 		(* (reg8 *) knob_1_01__0__INTTYPE)
#endif /* (knob_1_01__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_knob_1_01_H */


/* [] END OF FILE */
