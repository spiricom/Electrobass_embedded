/*******************************************************************************
* File Name: joy_x.h  
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

#if !defined(CY_PINS_joy_x_H) /* Pins joy_x_H */
#define CY_PINS_joy_x_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "joy_x_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 joy_x__PORT == 15 && ((joy_x__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    joy_x_Write(uint8 value);
void    joy_x_SetDriveMode(uint8 mode);
uint8   joy_x_ReadDataReg(void);
uint8   joy_x_Read(void);
void    joy_x_SetInterruptMode(uint16 position, uint16 mode);
uint8   joy_x_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the joy_x_SetDriveMode() function.
     *  @{
     */
        #define joy_x_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define joy_x_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define joy_x_DM_RES_UP          PIN_DM_RES_UP
        #define joy_x_DM_RES_DWN         PIN_DM_RES_DWN
        #define joy_x_DM_OD_LO           PIN_DM_OD_LO
        #define joy_x_DM_OD_HI           PIN_DM_OD_HI
        #define joy_x_DM_STRONG          PIN_DM_STRONG
        #define joy_x_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define joy_x_MASK               joy_x__MASK
#define joy_x_SHIFT              joy_x__SHIFT
#define joy_x_WIDTH              1u

/* Interrupt constants */
#if defined(joy_x__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in joy_x_SetInterruptMode() function.
     *  @{
     */
        #define joy_x_INTR_NONE      (uint16)(0x0000u)
        #define joy_x_INTR_RISING    (uint16)(0x0001u)
        #define joy_x_INTR_FALLING   (uint16)(0x0002u)
        #define joy_x_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define joy_x_INTR_MASK      (0x01u) 
#endif /* (joy_x__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define joy_x_PS                     (* (reg8 *) joy_x__PS)
/* Data Register */
#define joy_x_DR                     (* (reg8 *) joy_x__DR)
/* Port Number */
#define joy_x_PRT_NUM                (* (reg8 *) joy_x__PRT) 
/* Connect to Analog Globals */                                                  
#define joy_x_AG                     (* (reg8 *) joy_x__AG)                       
/* Analog MUX bux enable */
#define joy_x_AMUX                   (* (reg8 *) joy_x__AMUX) 
/* Bidirectional Enable */                                                        
#define joy_x_BIE                    (* (reg8 *) joy_x__BIE)
/* Bit-mask for Aliased Register Access */
#define joy_x_BIT_MASK               (* (reg8 *) joy_x__BIT_MASK)
/* Bypass Enable */
#define joy_x_BYP                    (* (reg8 *) joy_x__BYP)
/* Port wide control signals */                                                   
#define joy_x_CTL                    (* (reg8 *) joy_x__CTL)
/* Drive Modes */
#define joy_x_DM0                    (* (reg8 *) joy_x__DM0) 
#define joy_x_DM1                    (* (reg8 *) joy_x__DM1)
#define joy_x_DM2                    (* (reg8 *) joy_x__DM2) 
/* Input Buffer Disable Override */
#define joy_x_INP_DIS                (* (reg8 *) joy_x__INP_DIS)
/* LCD Common or Segment Drive */
#define joy_x_LCD_COM_SEG            (* (reg8 *) joy_x__LCD_COM_SEG)
/* Enable Segment LCD */
#define joy_x_LCD_EN                 (* (reg8 *) joy_x__LCD_EN)
/* Slew Rate Control */
#define joy_x_SLW                    (* (reg8 *) joy_x__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define joy_x_PRTDSI__CAPS_SEL       (* (reg8 *) joy_x__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define joy_x_PRTDSI__DBL_SYNC_IN    (* (reg8 *) joy_x__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define joy_x_PRTDSI__OE_SEL0        (* (reg8 *) joy_x__PRTDSI__OE_SEL0) 
#define joy_x_PRTDSI__OE_SEL1        (* (reg8 *) joy_x__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define joy_x_PRTDSI__OUT_SEL0       (* (reg8 *) joy_x__PRTDSI__OUT_SEL0) 
#define joy_x_PRTDSI__OUT_SEL1       (* (reg8 *) joy_x__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define joy_x_PRTDSI__SYNC_OUT       (* (reg8 *) joy_x__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(joy_x__SIO_CFG)
    #define joy_x_SIO_HYST_EN        (* (reg8 *) joy_x__SIO_HYST_EN)
    #define joy_x_SIO_REG_HIFREQ     (* (reg8 *) joy_x__SIO_REG_HIFREQ)
    #define joy_x_SIO_CFG            (* (reg8 *) joy_x__SIO_CFG)
    #define joy_x_SIO_DIFF           (* (reg8 *) joy_x__SIO_DIFF)
#endif /* (joy_x__SIO_CFG) */

/* Interrupt Registers */
#if defined(joy_x__INTSTAT)
    #define joy_x_INTSTAT            (* (reg8 *) joy_x__INTSTAT)
    #define joy_x_SNAP               (* (reg8 *) joy_x__SNAP)
    
	#define joy_x_0_INTTYPE_REG 		(* (reg8 *) joy_x__0__INTTYPE)
#endif /* (joy_x__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_joy_x_H */


/* [] END OF FILE */
