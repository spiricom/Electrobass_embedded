/*******************************************************************************
* File Name: alt_fretted.h  
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

#if !defined(CY_PINS_alt_fretted_H) /* Pins alt_fretted_H */
#define CY_PINS_alt_fretted_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "alt_fretted_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 alt_fretted__PORT == 15 && ((alt_fretted__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    alt_fretted_Write(uint8 value);
void    alt_fretted_SetDriveMode(uint8 mode);
uint8   alt_fretted_ReadDataReg(void);
uint8   alt_fretted_Read(void);
void    alt_fretted_SetInterruptMode(uint16 position, uint16 mode);
uint8   alt_fretted_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the alt_fretted_SetDriveMode() function.
     *  @{
     */
        #define alt_fretted_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define alt_fretted_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define alt_fretted_DM_RES_UP          PIN_DM_RES_UP
        #define alt_fretted_DM_RES_DWN         PIN_DM_RES_DWN
        #define alt_fretted_DM_OD_LO           PIN_DM_OD_LO
        #define alt_fretted_DM_OD_HI           PIN_DM_OD_HI
        #define alt_fretted_DM_STRONG          PIN_DM_STRONG
        #define alt_fretted_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define alt_fretted_MASK               alt_fretted__MASK
#define alt_fretted_SHIFT              alt_fretted__SHIFT
#define alt_fretted_WIDTH              1u

/* Interrupt constants */
#if defined(alt_fretted__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in alt_fretted_SetInterruptMode() function.
     *  @{
     */
        #define alt_fretted_INTR_NONE      (uint16)(0x0000u)
        #define alt_fretted_INTR_RISING    (uint16)(0x0001u)
        #define alt_fretted_INTR_FALLING   (uint16)(0x0002u)
        #define alt_fretted_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define alt_fretted_INTR_MASK      (0x01u) 
#endif /* (alt_fretted__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define alt_fretted_PS                     (* (reg8 *) alt_fretted__PS)
/* Data Register */
#define alt_fretted_DR                     (* (reg8 *) alt_fretted__DR)
/* Port Number */
#define alt_fretted_PRT_NUM                (* (reg8 *) alt_fretted__PRT) 
/* Connect to Analog Globals */                                                  
#define alt_fretted_AG                     (* (reg8 *) alt_fretted__AG)                       
/* Analog MUX bux enable */
#define alt_fretted_AMUX                   (* (reg8 *) alt_fretted__AMUX) 
/* Bidirectional Enable */                                                        
#define alt_fretted_BIE                    (* (reg8 *) alt_fretted__BIE)
/* Bit-mask for Aliased Register Access */
#define alt_fretted_BIT_MASK               (* (reg8 *) alt_fretted__BIT_MASK)
/* Bypass Enable */
#define alt_fretted_BYP                    (* (reg8 *) alt_fretted__BYP)
/* Port wide control signals */                                                   
#define alt_fretted_CTL                    (* (reg8 *) alt_fretted__CTL)
/* Drive Modes */
#define alt_fretted_DM0                    (* (reg8 *) alt_fretted__DM0) 
#define alt_fretted_DM1                    (* (reg8 *) alt_fretted__DM1)
#define alt_fretted_DM2                    (* (reg8 *) alt_fretted__DM2) 
/* Input Buffer Disable Override */
#define alt_fretted_INP_DIS                (* (reg8 *) alt_fretted__INP_DIS)
/* LCD Common or Segment Drive */
#define alt_fretted_LCD_COM_SEG            (* (reg8 *) alt_fretted__LCD_COM_SEG)
/* Enable Segment LCD */
#define alt_fretted_LCD_EN                 (* (reg8 *) alt_fretted__LCD_EN)
/* Slew Rate Control */
#define alt_fretted_SLW                    (* (reg8 *) alt_fretted__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define alt_fretted_PRTDSI__CAPS_SEL       (* (reg8 *) alt_fretted__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define alt_fretted_PRTDSI__DBL_SYNC_IN    (* (reg8 *) alt_fretted__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define alt_fretted_PRTDSI__OE_SEL0        (* (reg8 *) alt_fretted__PRTDSI__OE_SEL0) 
#define alt_fretted_PRTDSI__OE_SEL1        (* (reg8 *) alt_fretted__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define alt_fretted_PRTDSI__OUT_SEL0       (* (reg8 *) alt_fretted__PRTDSI__OUT_SEL0) 
#define alt_fretted_PRTDSI__OUT_SEL1       (* (reg8 *) alt_fretted__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define alt_fretted_PRTDSI__SYNC_OUT       (* (reg8 *) alt_fretted__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(alt_fretted__SIO_CFG)
    #define alt_fretted_SIO_HYST_EN        (* (reg8 *) alt_fretted__SIO_HYST_EN)
    #define alt_fretted_SIO_REG_HIFREQ     (* (reg8 *) alt_fretted__SIO_REG_HIFREQ)
    #define alt_fretted_SIO_CFG            (* (reg8 *) alt_fretted__SIO_CFG)
    #define alt_fretted_SIO_DIFF           (* (reg8 *) alt_fretted__SIO_DIFF)
#endif /* (alt_fretted__SIO_CFG) */

/* Interrupt Registers */
#if defined(alt_fretted__INTSTAT)
    #define alt_fretted_INTSTAT            (* (reg8 *) alt_fretted__INTSTAT)
    #define alt_fretted_SNAP               (* (reg8 *) alt_fretted__SNAP)
    
	#define alt_fretted_0_INTTYPE_REG 		(* (reg8 *) alt_fretted__0__INTTYPE)
#endif /* (alt_fretted__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_alt_fretted_H */


/* [] END OF FILE */
