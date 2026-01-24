/*******************************************************************************
* File Name: edit.h  
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

#if !defined(CY_PINS_edit_H) /* Pins edit_H */
#define CY_PINS_edit_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "edit_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 edit__PORT == 15 && ((edit__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    edit_Write(uint8 value);
void    edit_SetDriveMode(uint8 mode);
uint8   edit_ReadDataReg(void);
uint8   edit_Read(void);
void    edit_SetInterruptMode(uint16 position, uint16 mode);
uint8   edit_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the edit_SetDriveMode() function.
     *  @{
     */
        #define edit_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define edit_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define edit_DM_RES_UP          PIN_DM_RES_UP
        #define edit_DM_RES_DWN         PIN_DM_RES_DWN
        #define edit_DM_OD_LO           PIN_DM_OD_LO
        #define edit_DM_OD_HI           PIN_DM_OD_HI
        #define edit_DM_STRONG          PIN_DM_STRONG
        #define edit_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define edit_MASK               edit__MASK
#define edit_SHIFT              edit__SHIFT
#define edit_WIDTH              1u

/* Interrupt constants */
#if defined(edit__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in edit_SetInterruptMode() function.
     *  @{
     */
        #define edit_INTR_NONE      (uint16)(0x0000u)
        #define edit_INTR_RISING    (uint16)(0x0001u)
        #define edit_INTR_FALLING   (uint16)(0x0002u)
        #define edit_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define edit_INTR_MASK      (0x01u) 
#endif /* (edit__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define edit_PS                     (* (reg8 *) edit__PS)
/* Data Register */
#define edit_DR                     (* (reg8 *) edit__DR)
/* Port Number */
#define edit_PRT_NUM                (* (reg8 *) edit__PRT) 
/* Connect to Analog Globals */                                                  
#define edit_AG                     (* (reg8 *) edit__AG)                       
/* Analog MUX bux enable */
#define edit_AMUX                   (* (reg8 *) edit__AMUX) 
/* Bidirectional Enable */                                                        
#define edit_BIE                    (* (reg8 *) edit__BIE)
/* Bit-mask for Aliased Register Access */
#define edit_BIT_MASK               (* (reg8 *) edit__BIT_MASK)
/* Bypass Enable */
#define edit_BYP                    (* (reg8 *) edit__BYP)
/* Port wide control signals */                                                   
#define edit_CTL                    (* (reg8 *) edit__CTL)
/* Drive Modes */
#define edit_DM0                    (* (reg8 *) edit__DM0) 
#define edit_DM1                    (* (reg8 *) edit__DM1)
#define edit_DM2                    (* (reg8 *) edit__DM2) 
/* Input Buffer Disable Override */
#define edit_INP_DIS                (* (reg8 *) edit__INP_DIS)
/* LCD Common or Segment Drive */
#define edit_LCD_COM_SEG            (* (reg8 *) edit__LCD_COM_SEG)
/* Enable Segment LCD */
#define edit_LCD_EN                 (* (reg8 *) edit__LCD_EN)
/* Slew Rate Control */
#define edit_SLW                    (* (reg8 *) edit__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define edit_PRTDSI__CAPS_SEL       (* (reg8 *) edit__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define edit_PRTDSI__DBL_SYNC_IN    (* (reg8 *) edit__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define edit_PRTDSI__OE_SEL0        (* (reg8 *) edit__PRTDSI__OE_SEL0) 
#define edit_PRTDSI__OE_SEL1        (* (reg8 *) edit__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define edit_PRTDSI__OUT_SEL0       (* (reg8 *) edit__PRTDSI__OUT_SEL0) 
#define edit_PRTDSI__OUT_SEL1       (* (reg8 *) edit__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define edit_PRTDSI__SYNC_OUT       (* (reg8 *) edit__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(edit__SIO_CFG)
    #define edit_SIO_HYST_EN        (* (reg8 *) edit__SIO_HYST_EN)
    #define edit_SIO_REG_HIFREQ     (* (reg8 *) edit__SIO_REG_HIFREQ)
    #define edit_SIO_CFG            (* (reg8 *) edit__SIO_CFG)
    #define edit_SIO_DIFF           (* (reg8 *) edit__SIO_DIFF)
#endif /* (edit__SIO_CFG) */

/* Interrupt Registers */
#if defined(edit__INTSTAT)
    #define edit_INTSTAT            (* (reg8 *) edit__INTSTAT)
    #define edit_SNAP               (* (reg8 *) edit__SNAP)
    
	#define edit_0_INTTYPE_REG 		(* (reg8 *) edit__0__INTTYPE)
#endif /* (edit__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_edit_H */


/* [] END OF FILE */
