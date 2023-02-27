/*******************************************************************************
* File Name: utonal.h  
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

#if !defined(CY_PINS_utonal_H) /* Pins utonal_H */
#define CY_PINS_utonal_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "utonal_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 utonal__PORT == 15 && ((utonal__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    utonal_Write(uint8 value);
void    utonal_SetDriveMode(uint8 mode);
uint8   utonal_ReadDataReg(void);
uint8   utonal_Read(void);
void    utonal_SetInterruptMode(uint16 position, uint16 mode);
uint8   utonal_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the utonal_SetDriveMode() function.
     *  @{
     */
        #define utonal_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define utonal_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define utonal_DM_RES_UP          PIN_DM_RES_UP
        #define utonal_DM_RES_DWN         PIN_DM_RES_DWN
        #define utonal_DM_OD_LO           PIN_DM_OD_LO
        #define utonal_DM_OD_HI           PIN_DM_OD_HI
        #define utonal_DM_STRONG          PIN_DM_STRONG
        #define utonal_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define utonal_MASK               utonal__MASK
#define utonal_SHIFT              utonal__SHIFT
#define utonal_WIDTH              1u

/* Interrupt constants */
#if defined(utonal__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in utonal_SetInterruptMode() function.
     *  @{
     */
        #define utonal_INTR_NONE      (uint16)(0x0000u)
        #define utonal_INTR_RISING    (uint16)(0x0001u)
        #define utonal_INTR_FALLING   (uint16)(0x0002u)
        #define utonal_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define utonal_INTR_MASK      (0x01u) 
#endif /* (utonal__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define utonal_PS                     (* (reg8 *) utonal__PS)
/* Data Register */
#define utonal_DR                     (* (reg8 *) utonal__DR)
/* Port Number */
#define utonal_PRT_NUM                (* (reg8 *) utonal__PRT) 
/* Connect to Analog Globals */                                                  
#define utonal_AG                     (* (reg8 *) utonal__AG)                       
/* Analog MUX bux enable */
#define utonal_AMUX                   (* (reg8 *) utonal__AMUX) 
/* Bidirectional Enable */                                                        
#define utonal_BIE                    (* (reg8 *) utonal__BIE)
/* Bit-mask for Aliased Register Access */
#define utonal_BIT_MASK               (* (reg8 *) utonal__BIT_MASK)
/* Bypass Enable */
#define utonal_BYP                    (* (reg8 *) utonal__BYP)
/* Port wide control signals */                                                   
#define utonal_CTL                    (* (reg8 *) utonal__CTL)
/* Drive Modes */
#define utonal_DM0                    (* (reg8 *) utonal__DM0) 
#define utonal_DM1                    (* (reg8 *) utonal__DM1)
#define utonal_DM2                    (* (reg8 *) utonal__DM2) 
/* Input Buffer Disable Override */
#define utonal_INP_DIS                (* (reg8 *) utonal__INP_DIS)
/* LCD Common or Segment Drive */
#define utonal_LCD_COM_SEG            (* (reg8 *) utonal__LCD_COM_SEG)
/* Enable Segment LCD */
#define utonal_LCD_EN                 (* (reg8 *) utonal__LCD_EN)
/* Slew Rate Control */
#define utonal_SLW                    (* (reg8 *) utonal__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define utonal_PRTDSI__CAPS_SEL       (* (reg8 *) utonal__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define utonal_PRTDSI__DBL_SYNC_IN    (* (reg8 *) utonal__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define utonal_PRTDSI__OE_SEL0        (* (reg8 *) utonal__PRTDSI__OE_SEL0) 
#define utonal_PRTDSI__OE_SEL1        (* (reg8 *) utonal__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define utonal_PRTDSI__OUT_SEL0       (* (reg8 *) utonal__PRTDSI__OUT_SEL0) 
#define utonal_PRTDSI__OUT_SEL1       (* (reg8 *) utonal__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define utonal_PRTDSI__SYNC_OUT       (* (reg8 *) utonal__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(utonal__SIO_CFG)
    #define utonal_SIO_HYST_EN        (* (reg8 *) utonal__SIO_HYST_EN)
    #define utonal_SIO_REG_HIFREQ     (* (reg8 *) utonal__SIO_REG_HIFREQ)
    #define utonal_SIO_CFG            (* (reg8 *) utonal__SIO_CFG)
    #define utonal_SIO_DIFF           (* (reg8 *) utonal__SIO_DIFF)
#endif /* (utonal__SIO_CFG) */

/* Interrupt Registers */
#if defined(utonal__INTSTAT)
    #define utonal_INTSTAT            (* (reg8 *) utonal__INTSTAT)
    #define utonal_SNAP               (* (reg8 *) utonal__SNAP)
    
	#define utonal_0_INTTYPE_REG 		(* (reg8 *) utonal__0__INTTYPE)
#endif /* (utonal__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_utonal_H */


/* [] END OF FILE */
