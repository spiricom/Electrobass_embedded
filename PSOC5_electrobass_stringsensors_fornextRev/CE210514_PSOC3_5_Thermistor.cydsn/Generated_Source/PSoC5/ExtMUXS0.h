/*******************************************************************************
* File Name: ExtMUXS0.h  
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

#if !defined(CY_PINS_ExtMUXS0_H) /* Pins ExtMUXS0_H */
#define CY_PINS_ExtMUXS0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ExtMUXS0_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ExtMUXS0__PORT == 15 && ((ExtMUXS0__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ExtMUXS0_Write(uint8 value);
void    ExtMUXS0_SetDriveMode(uint8 mode);
uint8   ExtMUXS0_ReadDataReg(void);
uint8   ExtMUXS0_Read(void);
void    ExtMUXS0_SetInterruptMode(uint16 position, uint16 mode);
uint8   ExtMUXS0_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ExtMUXS0_SetDriveMode() function.
     *  @{
     */
        #define ExtMUXS0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ExtMUXS0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ExtMUXS0_DM_RES_UP          PIN_DM_RES_UP
        #define ExtMUXS0_DM_RES_DWN         PIN_DM_RES_DWN
        #define ExtMUXS0_DM_OD_LO           PIN_DM_OD_LO
        #define ExtMUXS0_DM_OD_HI           PIN_DM_OD_HI
        #define ExtMUXS0_DM_STRONG          PIN_DM_STRONG
        #define ExtMUXS0_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ExtMUXS0_MASK               ExtMUXS0__MASK
#define ExtMUXS0_SHIFT              ExtMUXS0__SHIFT
#define ExtMUXS0_WIDTH              1u

/* Interrupt constants */
#if defined(ExtMUXS0__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ExtMUXS0_SetInterruptMode() function.
     *  @{
     */
        #define ExtMUXS0_INTR_NONE      (uint16)(0x0000u)
        #define ExtMUXS0_INTR_RISING    (uint16)(0x0001u)
        #define ExtMUXS0_INTR_FALLING   (uint16)(0x0002u)
        #define ExtMUXS0_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ExtMUXS0_INTR_MASK      (0x01u) 
#endif /* (ExtMUXS0__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ExtMUXS0_PS                     (* (reg8 *) ExtMUXS0__PS)
/* Data Register */
#define ExtMUXS0_DR                     (* (reg8 *) ExtMUXS0__DR)
/* Port Number */
#define ExtMUXS0_PRT_NUM                (* (reg8 *) ExtMUXS0__PRT) 
/* Connect to Analog Globals */                                                  
#define ExtMUXS0_AG                     (* (reg8 *) ExtMUXS0__AG)                       
/* Analog MUX bux enable */
#define ExtMUXS0_AMUX                   (* (reg8 *) ExtMUXS0__AMUX) 
/* Bidirectional Enable */                                                        
#define ExtMUXS0_BIE                    (* (reg8 *) ExtMUXS0__BIE)
/* Bit-mask for Aliased Register Access */
#define ExtMUXS0_BIT_MASK               (* (reg8 *) ExtMUXS0__BIT_MASK)
/* Bypass Enable */
#define ExtMUXS0_BYP                    (* (reg8 *) ExtMUXS0__BYP)
/* Port wide control signals */                                                   
#define ExtMUXS0_CTL                    (* (reg8 *) ExtMUXS0__CTL)
/* Drive Modes */
#define ExtMUXS0_DM0                    (* (reg8 *) ExtMUXS0__DM0) 
#define ExtMUXS0_DM1                    (* (reg8 *) ExtMUXS0__DM1)
#define ExtMUXS0_DM2                    (* (reg8 *) ExtMUXS0__DM2) 
/* Input Buffer Disable Override */
#define ExtMUXS0_INP_DIS                (* (reg8 *) ExtMUXS0__INP_DIS)
/* LCD Common or Segment Drive */
#define ExtMUXS0_LCD_COM_SEG            (* (reg8 *) ExtMUXS0__LCD_COM_SEG)
/* Enable Segment LCD */
#define ExtMUXS0_LCD_EN                 (* (reg8 *) ExtMUXS0__LCD_EN)
/* Slew Rate Control */
#define ExtMUXS0_SLW                    (* (reg8 *) ExtMUXS0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ExtMUXS0_PRTDSI__CAPS_SEL       (* (reg8 *) ExtMUXS0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ExtMUXS0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ExtMUXS0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ExtMUXS0_PRTDSI__OE_SEL0        (* (reg8 *) ExtMUXS0__PRTDSI__OE_SEL0) 
#define ExtMUXS0_PRTDSI__OE_SEL1        (* (reg8 *) ExtMUXS0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ExtMUXS0_PRTDSI__OUT_SEL0       (* (reg8 *) ExtMUXS0__PRTDSI__OUT_SEL0) 
#define ExtMUXS0_PRTDSI__OUT_SEL1       (* (reg8 *) ExtMUXS0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ExtMUXS0_PRTDSI__SYNC_OUT       (* (reg8 *) ExtMUXS0__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ExtMUXS0__SIO_CFG)
    #define ExtMUXS0_SIO_HYST_EN        (* (reg8 *) ExtMUXS0__SIO_HYST_EN)
    #define ExtMUXS0_SIO_REG_HIFREQ     (* (reg8 *) ExtMUXS0__SIO_REG_HIFREQ)
    #define ExtMUXS0_SIO_CFG            (* (reg8 *) ExtMUXS0__SIO_CFG)
    #define ExtMUXS0_SIO_DIFF           (* (reg8 *) ExtMUXS0__SIO_DIFF)
#endif /* (ExtMUXS0__SIO_CFG) */

/* Interrupt Registers */
#if defined(ExtMUXS0__INTSTAT)
    #define ExtMUXS0_INTSTAT            (* (reg8 *) ExtMUXS0__INTSTAT)
    #define ExtMUXS0_SNAP               (* (reg8 *) ExtMUXS0__SNAP)
    
	#define ExtMUXS0_0_INTTYPE_REG 		(* (reg8 *) ExtMUXS0__0__INTTYPE)
#endif /* (ExtMUXS0__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ExtMUXS0_H */


/* [] END OF FILE */
