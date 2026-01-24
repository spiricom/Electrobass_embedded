/*******************************************************************************
* File Name: up.h  
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

#if !defined(CY_PINS_up_H) /* Pins up_H */
#define CY_PINS_up_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "up_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 up__PORT == 15 && ((up__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    up_Write(uint8 value);
void    up_SetDriveMode(uint8 mode);
uint8   up_ReadDataReg(void);
uint8   up_Read(void);
void    up_SetInterruptMode(uint16 position, uint16 mode);
uint8   up_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the up_SetDriveMode() function.
     *  @{
     */
        #define up_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define up_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define up_DM_RES_UP          PIN_DM_RES_UP
        #define up_DM_RES_DWN         PIN_DM_RES_DWN
        #define up_DM_OD_LO           PIN_DM_OD_LO
        #define up_DM_OD_HI           PIN_DM_OD_HI
        #define up_DM_STRONG          PIN_DM_STRONG
        #define up_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define up_MASK               up__MASK
#define up_SHIFT              up__SHIFT
#define up_WIDTH              1u

/* Interrupt constants */
#if defined(up__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in up_SetInterruptMode() function.
     *  @{
     */
        #define up_INTR_NONE      (uint16)(0x0000u)
        #define up_INTR_RISING    (uint16)(0x0001u)
        #define up_INTR_FALLING   (uint16)(0x0002u)
        #define up_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define up_INTR_MASK      (0x01u) 
#endif /* (up__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define up_PS                     (* (reg8 *) up__PS)
/* Data Register */
#define up_DR                     (* (reg8 *) up__DR)
/* Port Number */
#define up_PRT_NUM                (* (reg8 *) up__PRT) 
/* Connect to Analog Globals */                                                  
#define up_AG                     (* (reg8 *) up__AG)                       
/* Analog MUX bux enable */
#define up_AMUX                   (* (reg8 *) up__AMUX) 
/* Bidirectional Enable */                                                        
#define up_BIE                    (* (reg8 *) up__BIE)
/* Bit-mask for Aliased Register Access */
#define up_BIT_MASK               (* (reg8 *) up__BIT_MASK)
/* Bypass Enable */
#define up_BYP                    (* (reg8 *) up__BYP)
/* Port wide control signals */                                                   
#define up_CTL                    (* (reg8 *) up__CTL)
/* Drive Modes */
#define up_DM0                    (* (reg8 *) up__DM0) 
#define up_DM1                    (* (reg8 *) up__DM1)
#define up_DM2                    (* (reg8 *) up__DM2) 
/* Input Buffer Disable Override */
#define up_INP_DIS                (* (reg8 *) up__INP_DIS)
/* LCD Common or Segment Drive */
#define up_LCD_COM_SEG            (* (reg8 *) up__LCD_COM_SEG)
/* Enable Segment LCD */
#define up_LCD_EN                 (* (reg8 *) up__LCD_EN)
/* Slew Rate Control */
#define up_SLW                    (* (reg8 *) up__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define up_PRTDSI__CAPS_SEL       (* (reg8 *) up__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define up_PRTDSI__DBL_SYNC_IN    (* (reg8 *) up__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define up_PRTDSI__OE_SEL0        (* (reg8 *) up__PRTDSI__OE_SEL0) 
#define up_PRTDSI__OE_SEL1        (* (reg8 *) up__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define up_PRTDSI__OUT_SEL0       (* (reg8 *) up__PRTDSI__OUT_SEL0) 
#define up_PRTDSI__OUT_SEL1       (* (reg8 *) up__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define up_PRTDSI__SYNC_OUT       (* (reg8 *) up__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(up__SIO_CFG)
    #define up_SIO_HYST_EN        (* (reg8 *) up__SIO_HYST_EN)
    #define up_SIO_REG_HIFREQ     (* (reg8 *) up__SIO_REG_HIFREQ)
    #define up_SIO_CFG            (* (reg8 *) up__SIO_CFG)
    #define up_SIO_DIFF           (* (reg8 *) up__SIO_DIFF)
#endif /* (up__SIO_CFG) */

/* Interrupt Registers */
#if defined(up__INTSTAT)
    #define up_INTSTAT            (* (reg8 *) up__INTSTAT)
    #define up_SNAP               (* (reg8 *) up__SNAP)
    
	#define up_0_INTTYPE_REG 		(* (reg8 *) up__0__INTTYPE)
#endif /* (up__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_up_H */


/* [] END OF FILE */
