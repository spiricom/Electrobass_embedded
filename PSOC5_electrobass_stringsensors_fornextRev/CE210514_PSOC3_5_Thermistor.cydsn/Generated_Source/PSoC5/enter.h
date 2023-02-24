/*******************************************************************************
* File Name: enter.h  
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

#if !defined(CY_PINS_enter_H) /* Pins enter_H */
#define CY_PINS_enter_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "enter_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 enter__PORT == 15 && ((enter__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    enter_Write(uint8 value);
void    enter_SetDriveMode(uint8 mode);
uint8   enter_ReadDataReg(void);
uint8   enter_Read(void);
void    enter_SetInterruptMode(uint16 position, uint16 mode);
uint8   enter_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the enter_SetDriveMode() function.
     *  @{
     */
        #define enter_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define enter_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define enter_DM_RES_UP          PIN_DM_RES_UP
        #define enter_DM_RES_DWN         PIN_DM_RES_DWN
        #define enter_DM_OD_LO           PIN_DM_OD_LO
        #define enter_DM_OD_HI           PIN_DM_OD_HI
        #define enter_DM_STRONG          PIN_DM_STRONG
        #define enter_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define enter_MASK               enter__MASK
#define enter_SHIFT              enter__SHIFT
#define enter_WIDTH              1u

/* Interrupt constants */
#if defined(enter__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in enter_SetInterruptMode() function.
     *  @{
     */
        #define enter_INTR_NONE      (uint16)(0x0000u)
        #define enter_INTR_RISING    (uint16)(0x0001u)
        #define enter_INTR_FALLING   (uint16)(0x0002u)
        #define enter_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define enter_INTR_MASK      (0x01u) 
#endif /* (enter__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define enter_PS                     (* (reg8 *) enter__PS)
/* Data Register */
#define enter_DR                     (* (reg8 *) enter__DR)
/* Port Number */
#define enter_PRT_NUM                (* (reg8 *) enter__PRT) 
/* Connect to Analog Globals */                                                  
#define enter_AG                     (* (reg8 *) enter__AG)                       
/* Analog MUX bux enable */
#define enter_AMUX                   (* (reg8 *) enter__AMUX) 
/* Bidirectional Enable */                                                        
#define enter_BIE                    (* (reg8 *) enter__BIE)
/* Bit-mask for Aliased Register Access */
#define enter_BIT_MASK               (* (reg8 *) enter__BIT_MASK)
/* Bypass Enable */
#define enter_BYP                    (* (reg8 *) enter__BYP)
/* Port wide control signals */                                                   
#define enter_CTL                    (* (reg8 *) enter__CTL)
/* Drive Modes */
#define enter_DM0                    (* (reg8 *) enter__DM0) 
#define enter_DM1                    (* (reg8 *) enter__DM1)
#define enter_DM2                    (* (reg8 *) enter__DM2) 
/* Input Buffer Disable Override */
#define enter_INP_DIS                (* (reg8 *) enter__INP_DIS)
/* LCD Common or Segment Drive */
#define enter_LCD_COM_SEG            (* (reg8 *) enter__LCD_COM_SEG)
/* Enable Segment LCD */
#define enter_LCD_EN                 (* (reg8 *) enter__LCD_EN)
/* Slew Rate Control */
#define enter_SLW                    (* (reg8 *) enter__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define enter_PRTDSI__CAPS_SEL       (* (reg8 *) enter__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define enter_PRTDSI__DBL_SYNC_IN    (* (reg8 *) enter__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define enter_PRTDSI__OE_SEL0        (* (reg8 *) enter__PRTDSI__OE_SEL0) 
#define enter_PRTDSI__OE_SEL1        (* (reg8 *) enter__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define enter_PRTDSI__OUT_SEL0       (* (reg8 *) enter__PRTDSI__OUT_SEL0) 
#define enter_PRTDSI__OUT_SEL1       (* (reg8 *) enter__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define enter_PRTDSI__SYNC_OUT       (* (reg8 *) enter__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(enter__SIO_CFG)
    #define enter_SIO_HYST_EN        (* (reg8 *) enter__SIO_HYST_EN)
    #define enter_SIO_REG_HIFREQ     (* (reg8 *) enter__SIO_REG_HIFREQ)
    #define enter_SIO_CFG            (* (reg8 *) enter__SIO_CFG)
    #define enter_SIO_DIFF           (* (reg8 *) enter__SIO_DIFF)
#endif /* (enter__SIO_CFG) */

/* Interrupt Registers */
#if defined(enter__INTSTAT)
    #define enter_INTSTAT            (* (reg8 *) enter__INTSTAT)
    #define enter_SNAP               (* (reg8 *) enter__SNAP)
    
	#define enter_0_INTTYPE_REG 		(* (reg8 *) enter__0__INTTYPE)
#endif /* (enter__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_enter_H */


/* [] END OF FILE */
