/*******************************************************************************
* File Name: cv_pedal.h  
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

#if !defined(CY_PINS_cv_pedal_H) /* Pins cv_pedal_H */
#define CY_PINS_cv_pedal_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "cv_pedal_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 cv_pedal__PORT == 15 && ((cv_pedal__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    cv_pedal_Write(uint8 value);
void    cv_pedal_SetDriveMode(uint8 mode);
uint8   cv_pedal_ReadDataReg(void);
uint8   cv_pedal_Read(void);
void    cv_pedal_SetInterruptMode(uint16 position, uint16 mode);
uint8   cv_pedal_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the cv_pedal_SetDriveMode() function.
     *  @{
     */
        #define cv_pedal_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define cv_pedal_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define cv_pedal_DM_RES_UP          PIN_DM_RES_UP
        #define cv_pedal_DM_RES_DWN         PIN_DM_RES_DWN
        #define cv_pedal_DM_OD_LO           PIN_DM_OD_LO
        #define cv_pedal_DM_OD_HI           PIN_DM_OD_HI
        #define cv_pedal_DM_STRONG          PIN_DM_STRONG
        #define cv_pedal_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define cv_pedal_MASK               cv_pedal__MASK
#define cv_pedal_SHIFT              cv_pedal__SHIFT
#define cv_pedal_WIDTH              1u

/* Interrupt constants */
#if defined(cv_pedal__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in cv_pedal_SetInterruptMode() function.
     *  @{
     */
        #define cv_pedal_INTR_NONE      (uint16)(0x0000u)
        #define cv_pedal_INTR_RISING    (uint16)(0x0001u)
        #define cv_pedal_INTR_FALLING   (uint16)(0x0002u)
        #define cv_pedal_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define cv_pedal_INTR_MASK      (0x01u) 
#endif /* (cv_pedal__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define cv_pedal_PS                     (* (reg8 *) cv_pedal__PS)
/* Data Register */
#define cv_pedal_DR                     (* (reg8 *) cv_pedal__DR)
/* Port Number */
#define cv_pedal_PRT_NUM                (* (reg8 *) cv_pedal__PRT) 
/* Connect to Analog Globals */                                                  
#define cv_pedal_AG                     (* (reg8 *) cv_pedal__AG)                       
/* Analog MUX bux enable */
#define cv_pedal_AMUX                   (* (reg8 *) cv_pedal__AMUX) 
/* Bidirectional Enable */                                                        
#define cv_pedal_BIE                    (* (reg8 *) cv_pedal__BIE)
/* Bit-mask for Aliased Register Access */
#define cv_pedal_BIT_MASK               (* (reg8 *) cv_pedal__BIT_MASK)
/* Bypass Enable */
#define cv_pedal_BYP                    (* (reg8 *) cv_pedal__BYP)
/* Port wide control signals */                                                   
#define cv_pedal_CTL                    (* (reg8 *) cv_pedal__CTL)
/* Drive Modes */
#define cv_pedal_DM0                    (* (reg8 *) cv_pedal__DM0) 
#define cv_pedal_DM1                    (* (reg8 *) cv_pedal__DM1)
#define cv_pedal_DM2                    (* (reg8 *) cv_pedal__DM2) 
/* Input Buffer Disable Override */
#define cv_pedal_INP_DIS                (* (reg8 *) cv_pedal__INP_DIS)
/* LCD Common or Segment Drive */
#define cv_pedal_LCD_COM_SEG            (* (reg8 *) cv_pedal__LCD_COM_SEG)
/* Enable Segment LCD */
#define cv_pedal_LCD_EN                 (* (reg8 *) cv_pedal__LCD_EN)
/* Slew Rate Control */
#define cv_pedal_SLW                    (* (reg8 *) cv_pedal__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define cv_pedal_PRTDSI__CAPS_SEL       (* (reg8 *) cv_pedal__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define cv_pedal_PRTDSI__DBL_SYNC_IN    (* (reg8 *) cv_pedal__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define cv_pedal_PRTDSI__OE_SEL0        (* (reg8 *) cv_pedal__PRTDSI__OE_SEL0) 
#define cv_pedal_PRTDSI__OE_SEL1        (* (reg8 *) cv_pedal__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define cv_pedal_PRTDSI__OUT_SEL0       (* (reg8 *) cv_pedal__PRTDSI__OUT_SEL0) 
#define cv_pedal_PRTDSI__OUT_SEL1       (* (reg8 *) cv_pedal__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define cv_pedal_PRTDSI__SYNC_OUT       (* (reg8 *) cv_pedal__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(cv_pedal__SIO_CFG)
    #define cv_pedal_SIO_HYST_EN        (* (reg8 *) cv_pedal__SIO_HYST_EN)
    #define cv_pedal_SIO_REG_HIFREQ     (* (reg8 *) cv_pedal__SIO_REG_HIFREQ)
    #define cv_pedal_SIO_CFG            (* (reg8 *) cv_pedal__SIO_CFG)
    #define cv_pedal_SIO_DIFF           (* (reg8 *) cv_pedal__SIO_DIFF)
#endif /* (cv_pedal__SIO_CFG) */

/* Interrupt Registers */
#if defined(cv_pedal__INTSTAT)
    #define cv_pedal_INTSTAT            (* (reg8 *) cv_pedal__INTSTAT)
    #define cv_pedal_SNAP               (* (reg8 *) cv_pedal__SNAP)
    
	#define cv_pedal_0_INTTYPE_REG 		(* (reg8 *) cv_pedal__0__INTTYPE)
#endif /* (cv_pedal__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_cv_pedal_H */


/* [] END OF FILE */
