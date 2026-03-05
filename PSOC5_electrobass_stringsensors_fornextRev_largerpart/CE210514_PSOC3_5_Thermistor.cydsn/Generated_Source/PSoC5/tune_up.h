/*******************************************************************************
* File Name: tune_up.h  
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

#if !defined(CY_PINS_tune_up_H) /* Pins tune_up_H */
#define CY_PINS_tune_up_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "tune_up_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 tune_up__PORT == 15 && ((tune_up__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    tune_up_Write(uint8 value);
void    tune_up_SetDriveMode(uint8 mode);
uint8   tune_up_ReadDataReg(void);
uint8   tune_up_Read(void);
void    tune_up_SetInterruptMode(uint16 position, uint16 mode);
uint8   tune_up_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the tune_up_SetDriveMode() function.
     *  @{
     */
        #define tune_up_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define tune_up_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define tune_up_DM_RES_UP          PIN_DM_RES_UP
        #define tune_up_DM_RES_DWN         PIN_DM_RES_DWN
        #define tune_up_DM_OD_LO           PIN_DM_OD_LO
        #define tune_up_DM_OD_HI           PIN_DM_OD_HI
        #define tune_up_DM_STRONG          PIN_DM_STRONG
        #define tune_up_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define tune_up_MASK               tune_up__MASK
#define tune_up_SHIFT              tune_up__SHIFT
#define tune_up_WIDTH              1u

/* Interrupt constants */
#if defined(tune_up__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in tune_up_SetInterruptMode() function.
     *  @{
     */
        #define tune_up_INTR_NONE      (uint16)(0x0000u)
        #define tune_up_INTR_RISING    (uint16)(0x0001u)
        #define tune_up_INTR_FALLING   (uint16)(0x0002u)
        #define tune_up_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define tune_up_INTR_MASK      (0x01u) 
#endif /* (tune_up__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define tune_up_PS                     (* (reg8 *) tune_up__PS)
/* Data Register */
#define tune_up_DR                     (* (reg8 *) tune_up__DR)
/* Port Number */
#define tune_up_PRT_NUM                (* (reg8 *) tune_up__PRT) 
/* Connect to Analog Globals */                                                  
#define tune_up_AG                     (* (reg8 *) tune_up__AG)                       
/* Analog MUX bux enable */
#define tune_up_AMUX                   (* (reg8 *) tune_up__AMUX) 
/* Bidirectional Enable */                                                        
#define tune_up_BIE                    (* (reg8 *) tune_up__BIE)
/* Bit-mask for Aliased Register Access */
#define tune_up_BIT_MASK               (* (reg8 *) tune_up__BIT_MASK)
/* Bypass Enable */
#define tune_up_BYP                    (* (reg8 *) tune_up__BYP)
/* Port wide control signals */                                                   
#define tune_up_CTL                    (* (reg8 *) tune_up__CTL)
/* Drive Modes */
#define tune_up_DM0                    (* (reg8 *) tune_up__DM0) 
#define tune_up_DM1                    (* (reg8 *) tune_up__DM1)
#define tune_up_DM2                    (* (reg8 *) tune_up__DM2) 
/* Input Buffer Disable Override */
#define tune_up_INP_DIS                (* (reg8 *) tune_up__INP_DIS)
/* LCD Common or Segment Drive */
#define tune_up_LCD_COM_SEG            (* (reg8 *) tune_up__LCD_COM_SEG)
/* Enable Segment LCD */
#define tune_up_LCD_EN                 (* (reg8 *) tune_up__LCD_EN)
/* Slew Rate Control */
#define tune_up_SLW                    (* (reg8 *) tune_up__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define tune_up_PRTDSI__CAPS_SEL       (* (reg8 *) tune_up__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define tune_up_PRTDSI__DBL_SYNC_IN    (* (reg8 *) tune_up__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define tune_up_PRTDSI__OE_SEL0        (* (reg8 *) tune_up__PRTDSI__OE_SEL0) 
#define tune_up_PRTDSI__OE_SEL1        (* (reg8 *) tune_up__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define tune_up_PRTDSI__OUT_SEL0       (* (reg8 *) tune_up__PRTDSI__OUT_SEL0) 
#define tune_up_PRTDSI__OUT_SEL1       (* (reg8 *) tune_up__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define tune_up_PRTDSI__SYNC_OUT       (* (reg8 *) tune_up__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(tune_up__SIO_CFG)
    #define tune_up_SIO_HYST_EN        (* (reg8 *) tune_up__SIO_HYST_EN)
    #define tune_up_SIO_REG_HIFREQ     (* (reg8 *) tune_up__SIO_REG_HIFREQ)
    #define tune_up_SIO_CFG            (* (reg8 *) tune_up__SIO_CFG)
    #define tune_up_SIO_DIFF           (* (reg8 *) tune_up__SIO_DIFF)
#endif /* (tune_up__SIO_CFG) */

/* Interrupt Registers */
#if defined(tune_up__INTSTAT)
    #define tune_up_INTSTAT            (* (reg8 *) tune_up__INTSTAT)
    #define tune_up_SNAP               (* (reg8 *) tune_up__SNAP)
    
	#define tune_up_0_INTTYPE_REG 		(* (reg8 *) tune_up__0__INTTYPE)
#endif /* (tune_up__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_tune_up_H */


/* [] END OF FILE */
