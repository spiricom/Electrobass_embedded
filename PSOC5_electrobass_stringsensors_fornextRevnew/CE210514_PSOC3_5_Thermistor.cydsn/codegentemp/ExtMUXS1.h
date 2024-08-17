/*******************************************************************************
* File Name: ExtMUXS1.h  
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

#if !defined(CY_PINS_ExtMUXS1_H) /* Pins ExtMUXS1_H */
#define CY_PINS_ExtMUXS1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ExtMUXS1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ExtMUXS1__PORT == 15 && ((ExtMUXS1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ExtMUXS1_Write(uint8 value);
void    ExtMUXS1_SetDriveMode(uint8 mode);
uint8   ExtMUXS1_ReadDataReg(void);
uint8   ExtMUXS1_Read(void);
void    ExtMUXS1_SetInterruptMode(uint16 position, uint16 mode);
uint8   ExtMUXS1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ExtMUXS1_SetDriveMode() function.
     *  @{
     */
        #define ExtMUXS1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ExtMUXS1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ExtMUXS1_DM_RES_UP          PIN_DM_RES_UP
        #define ExtMUXS1_DM_RES_DWN         PIN_DM_RES_DWN
        #define ExtMUXS1_DM_OD_LO           PIN_DM_OD_LO
        #define ExtMUXS1_DM_OD_HI           PIN_DM_OD_HI
        #define ExtMUXS1_DM_STRONG          PIN_DM_STRONG
        #define ExtMUXS1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ExtMUXS1_MASK               ExtMUXS1__MASK
#define ExtMUXS1_SHIFT              ExtMUXS1__SHIFT
#define ExtMUXS1_WIDTH              1u

/* Interrupt constants */
#if defined(ExtMUXS1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ExtMUXS1_SetInterruptMode() function.
     *  @{
     */
        #define ExtMUXS1_INTR_NONE      (uint16)(0x0000u)
        #define ExtMUXS1_INTR_RISING    (uint16)(0x0001u)
        #define ExtMUXS1_INTR_FALLING   (uint16)(0x0002u)
        #define ExtMUXS1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ExtMUXS1_INTR_MASK      (0x01u) 
#endif /* (ExtMUXS1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ExtMUXS1_PS                     (* (reg8 *) ExtMUXS1__PS)
/* Data Register */
#define ExtMUXS1_DR                     (* (reg8 *) ExtMUXS1__DR)
/* Port Number */
#define ExtMUXS1_PRT_NUM                (* (reg8 *) ExtMUXS1__PRT) 
/* Connect to Analog Globals */                                                  
#define ExtMUXS1_AG                     (* (reg8 *) ExtMUXS1__AG)                       
/* Analog MUX bux enable */
#define ExtMUXS1_AMUX                   (* (reg8 *) ExtMUXS1__AMUX) 
/* Bidirectional Enable */                                                        
#define ExtMUXS1_BIE                    (* (reg8 *) ExtMUXS1__BIE)
/* Bit-mask for Aliased Register Access */
#define ExtMUXS1_BIT_MASK               (* (reg8 *) ExtMUXS1__BIT_MASK)
/* Bypass Enable */
#define ExtMUXS1_BYP                    (* (reg8 *) ExtMUXS1__BYP)
/* Port wide control signals */                                                   
#define ExtMUXS1_CTL                    (* (reg8 *) ExtMUXS1__CTL)
/* Drive Modes */
#define ExtMUXS1_DM0                    (* (reg8 *) ExtMUXS1__DM0) 
#define ExtMUXS1_DM1                    (* (reg8 *) ExtMUXS1__DM1)
#define ExtMUXS1_DM2                    (* (reg8 *) ExtMUXS1__DM2) 
/* Input Buffer Disable Override */
#define ExtMUXS1_INP_DIS                (* (reg8 *) ExtMUXS1__INP_DIS)
/* LCD Common or Segment Drive */
#define ExtMUXS1_LCD_COM_SEG            (* (reg8 *) ExtMUXS1__LCD_COM_SEG)
/* Enable Segment LCD */
#define ExtMUXS1_LCD_EN                 (* (reg8 *) ExtMUXS1__LCD_EN)
/* Slew Rate Control */
#define ExtMUXS1_SLW                    (* (reg8 *) ExtMUXS1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ExtMUXS1_PRTDSI__CAPS_SEL       (* (reg8 *) ExtMUXS1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ExtMUXS1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ExtMUXS1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ExtMUXS1_PRTDSI__OE_SEL0        (* (reg8 *) ExtMUXS1__PRTDSI__OE_SEL0) 
#define ExtMUXS1_PRTDSI__OE_SEL1        (* (reg8 *) ExtMUXS1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ExtMUXS1_PRTDSI__OUT_SEL0       (* (reg8 *) ExtMUXS1__PRTDSI__OUT_SEL0) 
#define ExtMUXS1_PRTDSI__OUT_SEL1       (* (reg8 *) ExtMUXS1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ExtMUXS1_PRTDSI__SYNC_OUT       (* (reg8 *) ExtMUXS1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ExtMUXS1__SIO_CFG)
    #define ExtMUXS1_SIO_HYST_EN        (* (reg8 *) ExtMUXS1__SIO_HYST_EN)
    #define ExtMUXS1_SIO_REG_HIFREQ     (* (reg8 *) ExtMUXS1__SIO_REG_HIFREQ)
    #define ExtMUXS1_SIO_CFG            (* (reg8 *) ExtMUXS1__SIO_CFG)
    #define ExtMUXS1_SIO_DIFF           (* (reg8 *) ExtMUXS1__SIO_DIFF)
#endif /* (ExtMUXS1__SIO_CFG) */

/* Interrupt Registers */
#if defined(ExtMUXS1__INTSTAT)
    #define ExtMUXS1_INTSTAT            (* (reg8 *) ExtMUXS1__INTSTAT)
    #define ExtMUXS1_SNAP               (* (reg8 *) ExtMUXS1__SNAP)
    
	#define ExtMUXS1_0_INTTYPE_REG 		(* (reg8 *) ExtMUXS1__0__INTTYPE)
#endif /* (ExtMUXS1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ExtMUXS1_H */


/* [] END OF FILE */
