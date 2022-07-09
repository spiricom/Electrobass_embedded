/*******************************************************************************
* File Name: knob_2_36.h  
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

#if !defined(CY_PINS_knob_2_36_H) /* Pins knob_2_36_H */
#define CY_PINS_knob_2_36_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "knob_2_36_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 knob_2_36__PORT == 15 && ((knob_2_36__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    knob_2_36_Write(uint8 value);
void    knob_2_36_SetDriveMode(uint8 mode);
uint8   knob_2_36_ReadDataReg(void);
uint8   knob_2_36_Read(void);
void    knob_2_36_SetInterruptMode(uint16 position, uint16 mode);
uint8   knob_2_36_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the knob_2_36_SetDriveMode() function.
     *  @{
     */
        #define knob_2_36_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define knob_2_36_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define knob_2_36_DM_RES_UP          PIN_DM_RES_UP
        #define knob_2_36_DM_RES_DWN         PIN_DM_RES_DWN
        #define knob_2_36_DM_OD_LO           PIN_DM_OD_LO
        #define knob_2_36_DM_OD_HI           PIN_DM_OD_HI
        #define knob_2_36_DM_STRONG          PIN_DM_STRONG
        #define knob_2_36_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define knob_2_36_MASK               knob_2_36__MASK
#define knob_2_36_SHIFT              knob_2_36__SHIFT
#define knob_2_36_WIDTH              1u

/* Interrupt constants */
#if defined(knob_2_36__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in knob_2_36_SetInterruptMode() function.
     *  @{
     */
        #define knob_2_36_INTR_NONE      (uint16)(0x0000u)
        #define knob_2_36_INTR_RISING    (uint16)(0x0001u)
        #define knob_2_36_INTR_FALLING   (uint16)(0x0002u)
        #define knob_2_36_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define knob_2_36_INTR_MASK      (0x01u) 
#endif /* (knob_2_36__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define knob_2_36_PS                     (* (reg8 *) knob_2_36__PS)
/* Data Register */
#define knob_2_36_DR                     (* (reg8 *) knob_2_36__DR)
/* Port Number */
#define knob_2_36_PRT_NUM                (* (reg8 *) knob_2_36__PRT) 
/* Connect to Analog Globals */                                                  
#define knob_2_36_AG                     (* (reg8 *) knob_2_36__AG)                       
/* Analog MUX bux enable */
#define knob_2_36_AMUX                   (* (reg8 *) knob_2_36__AMUX) 
/* Bidirectional Enable */                                                        
#define knob_2_36_BIE                    (* (reg8 *) knob_2_36__BIE)
/* Bit-mask for Aliased Register Access */
#define knob_2_36_BIT_MASK               (* (reg8 *) knob_2_36__BIT_MASK)
/* Bypass Enable */
#define knob_2_36_BYP                    (* (reg8 *) knob_2_36__BYP)
/* Port wide control signals */                                                   
#define knob_2_36_CTL                    (* (reg8 *) knob_2_36__CTL)
/* Drive Modes */
#define knob_2_36_DM0                    (* (reg8 *) knob_2_36__DM0) 
#define knob_2_36_DM1                    (* (reg8 *) knob_2_36__DM1)
#define knob_2_36_DM2                    (* (reg8 *) knob_2_36__DM2) 
/* Input Buffer Disable Override */
#define knob_2_36_INP_DIS                (* (reg8 *) knob_2_36__INP_DIS)
/* LCD Common or Segment Drive */
#define knob_2_36_LCD_COM_SEG            (* (reg8 *) knob_2_36__LCD_COM_SEG)
/* Enable Segment LCD */
#define knob_2_36_LCD_EN                 (* (reg8 *) knob_2_36__LCD_EN)
/* Slew Rate Control */
#define knob_2_36_SLW                    (* (reg8 *) knob_2_36__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define knob_2_36_PRTDSI__CAPS_SEL       (* (reg8 *) knob_2_36__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define knob_2_36_PRTDSI__DBL_SYNC_IN    (* (reg8 *) knob_2_36__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define knob_2_36_PRTDSI__OE_SEL0        (* (reg8 *) knob_2_36__PRTDSI__OE_SEL0) 
#define knob_2_36_PRTDSI__OE_SEL1        (* (reg8 *) knob_2_36__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define knob_2_36_PRTDSI__OUT_SEL0       (* (reg8 *) knob_2_36__PRTDSI__OUT_SEL0) 
#define knob_2_36_PRTDSI__OUT_SEL1       (* (reg8 *) knob_2_36__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define knob_2_36_PRTDSI__SYNC_OUT       (* (reg8 *) knob_2_36__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(knob_2_36__SIO_CFG)
    #define knob_2_36_SIO_HYST_EN        (* (reg8 *) knob_2_36__SIO_HYST_EN)
    #define knob_2_36_SIO_REG_HIFREQ     (* (reg8 *) knob_2_36__SIO_REG_HIFREQ)
    #define knob_2_36_SIO_CFG            (* (reg8 *) knob_2_36__SIO_CFG)
    #define knob_2_36_SIO_DIFF           (* (reg8 *) knob_2_36__SIO_DIFF)
#endif /* (knob_2_36__SIO_CFG) */

/* Interrupt Registers */
#if defined(knob_2_36__INTSTAT)
    #define knob_2_36_INTSTAT            (* (reg8 *) knob_2_36__INTSTAT)
    #define knob_2_36_SNAP               (* (reg8 *) knob_2_36__SNAP)
    
	#define knob_2_36_0_INTTYPE_REG 		(* (reg8 *) knob_2_36__0__INTTYPE)
#endif /* (knob_2_36__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_knob_2_36_H */


/* [] END OF FILE */
