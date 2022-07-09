/*******************************************************************************
* File Name: pedal.h  
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

#if !defined(CY_PINS_pedal_H) /* Pins pedal_H */
#define CY_PINS_pedal_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pedal_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pedal__PORT == 15 && ((pedal__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pedal_Write(uint8 value);
void    pedal_SetDriveMode(uint8 mode);
uint8   pedal_ReadDataReg(void);
uint8   pedal_Read(void);
void    pedal_SetInterruptMode(uint16 position, uint16 mode);
uint8   pedal_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pedal_SetDriveMode() function.
     *  @{
     */
        #define pedal_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pedal_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pedal_DM_RES_UP          PIN_DM_RES_UP
        #define pedal_DM_RES_DWN         PIN_DM_RES_DWN
        #define pedal_DM_OD_LO           PIN_DM_OD_LO
        #define pedal_DM_OD_HI           PIN_DM_OD_HI
        #define pedal_DM_STRONG          PIN_DM_STRONG
        #define pedal_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pedal_MASK               pedal__MASK
#define pedal_SHIFT              pedal__SHIFT
#define pedal_WIDTH              1u

/* Interrupt constants */
#if defined(pedal__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pedal_SetInterruptMode() function.
     *  @{
     */
        #define pedal_INTR_NONE      (uint16)(0x0000u)
        #define pedal_INTR_RISING    (uint16)(0x0001u)
        #define pedal_INTR_FALLING   (uint16)(0x0002u)
        #define pedal_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pedal_INTR_MASK      (0x01u) 
#endif /* (pedal__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pedal_PS                     (* (reg8 *) pedal__PS)
/* Data Register */
#define pedal_DR                     (* (reg8 *) pedal__DR)
/* Port Number */
#define pedal_PRT_NUM                (* (reg8 *) pedal__PRT) 
/* Connect to Analog Globals */                                                  
#define pedal_AG                     (* (reg8 *) pedal__AG)                       
/* Analog MUX bux enable */
#define pedal_AMUX                   (* (reg8 *) pedal__AMUX) 
/* Bidirectional Enable */                                                        
#define pedal_BIE                    (* (reg8 *) pedal__BIE)
/* Bit-mask for Aliased Register Access */
#define pedal_BIT_MASK               (* (reg8 *) pedal__BIT_MASK)
/* Bypass Enable */
#define pedal_BYP                    (* (reg8 *) pedal__BYP)
/* Port wide control signals */                                                   
#define pedal_CTL                    (* (reg8 *) pedal__CTL)
/* Drive Modes */
#define pedal_DM0                    (* (reg8 *) pedal__DM0) 
#define pedal_DM1                    (* (reg8 *) pedal__DM1)
#define pedal_DM2                    (* (reg8 *) pedal__DM2) 
/* Input Buffer Disable Override */
#define pedal_INP_DIS                (* (reg8 *) pedal__INP_DIS)
/* LCD Common or Segment Drive */
#define pedal_LCD_COM_SEG            (* (reg8 *) pedal__LCD_COM_SEG)
/* Enable Segment LCD */
#define pedal_LCD_EN                 (* (reg8 *) pedal__LCD_EN)
/* Slew Rate Control */
#define pedal_SLW                    (* (reg8 *) pedal__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pedal_PRTDSI__CAPS_SEL       (* (reg8 *) pedal__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pedal_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pedal__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pedal_PRTDSI__OE_SEL0        (* (reg8 *) pedal__PRTDSI__OE_SEL0) 
#define pedal_PRTDSI__OE_SEL1        (* (reg8 *) pedal__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pedal_PRTDSI__OUT_SEL0       (* (reg8 *) pedal__PRTDSI__OUT_SEL0) 
#define pedal_PRTDSI__OUT_SEL1       (* (reg8 *) pedal__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pedal_PRTDSI__SYNC_OUT       (* (reg8 *) pedal__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pedal__SIO_CFG)
    #define pedal_SIO_HYST_EN        (* (reg8 *) pedal__SIO_HYST_EN)
    #define pedal_SIO_REG_HIFREQ     (* (reg8 *) pedal__SIO_REG_HIFREQ)
    #define pedal_SIO_CFG            (* (reg8 *) pedal__SIO_CFG)
    #define pedal_SIO_DIFF           (* (reg8 *) pedal__SIO_DIFF)
#endif /* (pedal__SIO_CFG) */

/* Interrupt Registers */
#if defined(pedal__INTSTAT)
    #define pedal_INTSTAT            (* (reg8 *) pedal__INTSTAT)
    #define pedal_SNAP               (* (reg8 *) pedal__SNAP)
    
	#define pedal_0_INTTYPE_REG 		(* (reg8 *) pedal__0__INTTYPE)
#endif /* (pedal__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pedal_H */


/* [] END OF FILE */
