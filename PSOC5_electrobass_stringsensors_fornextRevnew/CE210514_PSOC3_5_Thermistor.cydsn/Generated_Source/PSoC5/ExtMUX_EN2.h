/*******************************************************************************
* File Name: ExtMUX_EN2.h  
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

#if !defined(CY_PINS_ExtMUX_EN2_H) /* Pins ExtMUX_EN2_H */
#define CY_PINS_ExtMUX_EN2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ExtMUX_EN2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ExtMUX_EN2__PORT == 15 && ((ExtMUX_EN2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ExtMUX_EN2_Write(uint8 value);
void    ExtMUX_EN2_SetDriveMode(uint8 mode);
uint8   ExtMUX_EN2_ReadDataReg(void);
uint8   ExtMUX_EN2_Read(void);
void    ExtMUX_EN2_SetInterruptMode(uint16 position, uint16 mode);
uint8   ExtMUX_EN2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ExtMUX_EN2_SetDriveMode() function.
     *  @{
     */
        #define ExtMUX_EN2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ExtMUX_EN2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ExtMUX_EN2_DM_RES_UP          PIN_DM_RES_UP
        #define ExtMUX_EN2_DM_RES_DWN         PIN_DM_RES_DWN
        #define ExtMUX_EN2_DM_OD_LO           PIN_DM_OD_LO
        #define ExtMUX_EN2_DM_OD_HI           PIN_DM_OD_HI
        #define ExtMUX_EN2_DM_STRONG          PIN_DM_STRONG
        #define ExtMUX_EN2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ExtMUX_EN2_MASK               ExtMUX_EN2__MASK
#define ExtMUX_EN2_SHIFT              ExtMUX_EN2__SHIFT
#define ExtMUX_EN2_WIDTH              1u

/* Interrupt constants */
#if defined(ExtMUX_EN2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ExtMUX_EN2_SetInterruptMode() function.
     *  @{
     */
        #define ExtMUX_EN2_INTR_NONE      (uint16)(0x0000u)
        #define ExtMUX_EN2_INTR_RISING    (uint16)(0x0001u)
        #define ExtMUX_EN2_INTR_FALLING   (uint16)(0x0002u)
        #define ExtMUX_EN2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ExtMUX_EN2_INTR_MASK      (0x01u) 
#endif /* (ExtMUX_EN2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ExtMUX_EN2_PS                     (* (reg8 *) ExtMUX_EN2__PS)
/* Data Register */
#define ExtMUX_EN2_DR                     (* (reg8 *) ExtMUX_EN2__DR)
/* Port Number */
#define ExtMUX_EN2_PRT_NUM                (* (reg8 *) ExtMUX_EN2__PRT) 
/* Connect to Analog Globals */                                                  
#define ExtMUX_EN2_AG                     (* (reg8 *) ExtMUX_EN2__AG)                       
/* Analog MUX bux enable */
#define ExtMUX_EN2_AMUX                   (* (reg8 *) ExtMUX_EN2__AMUX) 
/* Bidirectional Enable */                                                        
#define ExtMUX_EN2_BIE                    (* (reg8 *) ExtMUX_EN2__BIE)
/* Bit-mask for Aliased Register Access */
#define ExtMUX_EN2_BIT_MASK               (* (reg8 *) ExtMUX_EN2__BIT_MASK)
/* Bypass Enable */
#define ExtMUX_EN2_BYP                    (* (reg8 *) ExtMUX_EN2__BYP)
/* Port wide control signals */                                                   
#define ExtMUX_EN2_CTL                    (* (reg8 *) ExtMUX_EN2__CTL)
/* Drive Modes */
#define ExtMUX_EN2_DM0                    (* (reg8 *) ExtMUX_EN2__DM0) 
#define ExtMUX_EN2_DM1                    (* (reg8 *) ExtMUX_EN2__DM1)
#define ExtMUX_EN2_DM2                    (* (reg8 *) ExtMUX_EN2__DM2) 
/* Input Buffer Disable Override */
#define ExtMUX_EN2_INP_DIS                (* (reg8 *) ExtMUX_EN2__INP_DIS)
/* LCD Common or Segment Drive */
#define ExtMUX_EN2_LCD_COM_SEG            (* (reg8 *) ExtMUX_EN2__LCD_COM_SEG)
/* Enable Segment LCD */
#define ExtMUX_EN2_LCD_EN                 (* (reg8 *) ExtMUX_EN2__LCD_EN)
/* Slew Rate Control */
#define ExtMUX_EN2_SLW                    (* (reg8 *) ExtMUX_EN2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ExtMUX_EN2_PRTDSI__CAPS_SEL       (* (reg8 *) ExtMUX_EN2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ExtMUX_EN2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ExtMUX_EN2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ExtMUX_EN2_PRTDSI__OE_SEL0        (* (reg8 *) ExtMUX_EN2__PRTDSI__OE_SEL0) 
#define ExtMUX_EN2_PRTDSI__OE_SEL1        (* (reg8 *) ExtMUX_EN2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ExtMUX_EN2_PRTDSI__OUT_SEL0       (* (reg8 *) ExtMUX_EN2__PRTDSI__OUT_SEL0) 
#define ExtMUX_EN2_PRTDSI__OUT_SEL1       (* (reg8 *) ExtMUX_EN2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ExtMUX_EN2_PRTDSI__SYNC_OUT       (* (reg8 *) ExtMUX_EN2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ExtMUX_EN2__SIO_CFG)
    #define ExtMUX_EN2_SIO_HYST_EN        (* (reg8 *) ExtMUX_EN2__SIO_HYST_EN)
    #define ExtMUX_EN2_SIO_REG_HIFREQ     (* (reg8 *) ExtMUX_EN2__SIO_REG_HIFREQ)
    #define ExtMUX_EN2_SIO_CFG            (* (reg8 *) ExtMUX_EN2__SIO_CFG)
    #define ExtMUX_EN2_SIO_DIFF           (* (reg8 *) ExtMUX_EN2__SIO_DIFF)
#endif /* (ExtMUX_EN2__SIO_CFG) */

/* Interrupt Registers */
#if defined(ExtMUX_EN2__INTSTAT)
    #define ExtMUX_EN2_INTSTAT            (* (reg8 *) ExtMUX_EN2__INTSTAT)
    #define ExtMUX_EN2_SNAP               (* (reg8 *) ExtMUX_EN2__SNAP)
    
	#define ExtMUX_EN2_0_INTTYPE_REG 		(* (reg8 *) ExtMUX_EN2__0__INTTYPE)
#endif /* (ExtMUX_EN2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ExtMUX_EN2_H */


/* [] END OF FILE */
