/*******************************************************************************
* File Name: bowed_plucked.h  
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

#if !defined(CY_PINS_bowed_plucked_H) /* Pins bowed_plucked_H */
#define CY_PINS_bowed_plucked_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "bowed_plucked_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 bowed_plucked__PORT == 15 && ((bowed_plucked__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    bowed_plucked_Write(uint8 value);
void    bowed_plucked_SetDriveMode(uint8 mode);
uint8   bowed_plucked_ReadDataReg(void);
uint8   bowed_plucked_Read(void);
void    bowed_plucked_SetInterruptMode(uint16 position, uint16 mode);
uint8   bowed_plucked_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the bowed_plucked_SetDriveMode() function.
     *  @{
     */
        #define bowed_plucked_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define bowed_plucked_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define bowed_plucked_DM_RES_UP          PIN_DM_RES_UP
        #define bowed_plucked_DM_RES_DWN         PIN_DM_RES_DWN
        #define bowed_plucked_DM_OD_LO           PIN_DM_OD_LO
        #define bowed_plucked_DM_OD_HI           PIN_DM_OD_HI
        #define bowed_plucked_DM_STRONG          PIN_DM_STRONG
        #define bowed_plucked_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define bowed_plucked_MASK               bowed_plucked__MASK
#define bowed_plucked_SHIFT              bowed_plucked__SHIFT
#define bowed_plucked_WIDTH              1u

/* Interrupt constants */
#if defined(bowed_plucked__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in bowed_plucked_SetInterruptMode() function.
     *  @{
     */
        #define bowed_plucked_INTR_NONE      (uint16)(0x0000u)
        #define bowed_plucked_INTR_RISING    (uint16)(0x0001u)
        #define bowed_plucked_INTR_FALLING   (uint16)(0x0002u)
        #define bowed_plucked_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define bowed_plucked_INTR_MASK      (0x01u) 
#endif /* (bowed_plucked__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define bowed_plucked_PS                     (* (reg8 *) bowed_plucked__PS)
/* Data Register */
#define bowed_plucked_DR                     (* (reg8 *) bowed_plucked__DR)
/* Port Number */
#define bowed_plucked_PRT_NUM                (* (reg8 *) bowed_plucked__PRT) 
/* Connect to Analog Globals */                                                  
#define bowed_plucked_AG                     (* (reg8 *) bowed_plucked__AG)                       
/* Analog MUX bux enable */
#define bowed_plucked_AMUX                   (* (reg8 *) bowed_plucked__AMUX) 
/* Bidirectional Enable */                                                        
#define bowed_plucked_BIE                    (* (reg8 *) bowed_plucked__BIE)
/* Bit-mask for Aliased Register Access */
#define bowed_plucked_BIT_MASK               (* (reg8 *) bowed_plucked__BIT_MASK)
/* Bypass Enable */
#define bowed_plucked_BYP                    (* (reg8 *) bowed_plucked__BYP)
/* Port wide control signals */                                                   
#define bowed_plucked_CTL                    (* (reg8 *) bowed_plucked__CTL)
/* Drive Modes */
#define bowed_plucked_DM0                    (* (reg8 *) bowed_plucked__DM0) 
#define bowed_plucked_DM1                    (* (reg8 *) bowed_plucked__DM1)
#define bowed_plucked_DM2                    (* (reg8 *) bowed_plucked__DM2) 
/* Input Buffer Disable Override */
#define bowed_plucked_INP_DIS                (* (reg8 *) bowed_plucked__INP_DIS)
/* LCD Common or Segment Drive */
#define bowed_plucked_LCD_COM_SEG            (* (reg8 *) bowed_plucked__LCD_COM_SEG)
/* Enable Segment LCD */
#define bowed_plucked_LCD_EN                 (* (reg8 *) bowed_plucked__LCD_EN)
/* Slew Rate Control */
#define bowed_plucked_SLW                    (* (reg8 *) bowed_plucked__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define bowed_plucked_PRTDSI__CAPS_SEL       (* (reg8 *) bowed_plucked__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define bowed_plucked_PRTDSI__DBL_SYNC_IN    (* (reg8 *) bowed_plucked__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define bowed_plucked_PRTDSI__OE_SEL0        (* (reg8 *) bowed_plucked__PRTDSI__OE_SEL0) 
#define bowed_plucked_PRTDSI__OE_SEL1        (* (reg8 *) bowed_plucked__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define bowed_plucked_PRTDSI__OUT_SEL0       (* (reg8 *) bowed_plucked__PRTDSI__OUT_SEL0) 
#define bowed_plucked_PRTDSI__OUT_SEL1       (* (reg8 *) bowed_plucked__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define bowed_plucked_PRTDSI__SYNC_OUT       (* (reg8 *) bowed_plucked__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(bowed_plucked__SIO_CFG)
    #define bowed_plucked_SIO_HYST_EN        (* (reg8 *) bowed_plucked__SIO_HYST_EN)
    #define bowed_plucked_SIO_REG_HIFREQ     (* (reg8 *) bowed_plucked__SIO_REG_HIFREQ)
    #define bowed_plucked_SIO_CFG            (* (reg8 *) bowed_plucked__SIO_CFG)
    #define bowed_plucked_SIO_DIFF           (* (reg8 *) bowed_plucked__SIO_DIFF)
#endif /* (bowed_plucked__SIO_CFG) */

/* Interrupt Registers */
#if defined(bowed_plucked__INTSTAT)
    #define bowed_plucked_INTSTAT            (* (reg8 *) bowed_plucked__INTSTAT)
    #define bowed_plucked_SNAP               (* (reg8 *) bowed_plucked__SNAP)
    
	#define bowed_plucked_0_INTTYPE_REG 		(* (reg8 *) bowed_plucked__0__INTTYPE)
#endif /* (bowed_plucked__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_bowed_plucked_H */


/* [] END OF FILE */
