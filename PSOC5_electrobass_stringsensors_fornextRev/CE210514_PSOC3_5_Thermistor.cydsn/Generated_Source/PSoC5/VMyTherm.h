/*******************************************************************************
* File Name: VMyTherm.h  
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

#if !defined(CY_PINS_VMyTherm_H) /* Pins VMyTherm_H */
#define CY_PINS_VMyTherm_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VMyTherm_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 VMyTherm__PORT == 15 && ((VMyTherm__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    VMyTherm_Write(uint8 value);
void    VMyTherm_SetDriveMode(uint8 mode);
uint8   VMyTherm_ReadDataReg(void);
uint8   VMyTherm_Read(void);
void    VMyTherm_SetInterruptMode(uint16 position, uint16 mode);
uint8   VMyTherm_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the VMyTherm_SetDriveMode() function.
     *  @{
     */
        #define VMyTherm_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define VMyTherm_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define VMyTherm_DM_RES_UP          PIN_DM_RES_UP
        #define VMyTherm_DM_RES_DWN         PIN_DM_RES_DWN
        #define VMyTherm_DM_OD_LO           PIN_DM_OD_LO
        #define VMyTherm_DM_OD_HI           PIN_DM_OD_HI
        #define VMyTherm_DM_STRONG          PIN_DM_STRONG
        #define VMyTherm_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define VMyTherm_MASK               VMyTherm__MASK
#define VMyTherm_SHIFT              VMyTherm__SHIFT
#define VMyTherm_WIDTH              1u

/* Interrupt constants */
#if defined(VMyTherm__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VMyTherm_SetInterruptMode() function.
     *  @{
     */
        #define VMyTherm_INTR_NONE      (uint16)(0x0000u)
        #define VMyTherm_INTR_RISING    (uint16)(0x0001u)
        #define VMyTherm_INTR_FALLING   (uint16)(0x0002u)
        #define VMyTherm_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define VMyTherm_INTR_MASK      (0x01u) 
#endif /* (VMyTherm__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VMyTherm_PS                     (* (reg8 *) VMyTherm__PS)
/* Data Register */
#define VMyTherm_DR                     (* (reg8 *) VMyTherm__DR)
/* Port Number */
#define VMyTherm_PRT_NUM                (* (reg8 *) VMyTherm__PRT) 
/* Connect to Analog Globals */                                                  
#define VMyTherm_AG                     (* (reg8 *) VMyTherm__AG)                       
/* Analog MUX bux enable */
#define VMyTherm_AMUX                   (* (reg8 *) VMyTherm__AMUX) 
/* Bidirectional Enable */                                                        
#define VMyTherm_BIE                    (* (reg8 *) VMyTherm__BIE)
/* Bit-mask for Aliased Register Access */
#define VMyTherm_BIT_MASK               (* (reg8 *) VMyTherm__BIT_MASK)
/* Bypass Enable */
#define VMyTherm_BYP                    (* (reg8 *) VMyTherm__BYP)
/* Port wide control signals */                                                   
#define VMyTherm_CTL                    (* (reg8 *) VMyTherm__CTL)
/* Drive Modes */
#define VMyTherm_DM0                    (* (reg8 *) VMyTherm__DM0) 
#define VMyTherm_DM1                    (* (reg8 *) VMyTherm__DM1)
#define VMyTherm_DM2                    (* (reg8 *) VMyTherm__DM2) 
/* Input Buffer Disable Override */
#define VMyTherm_INP_DIS                (* (reg8 *) VMyTherm__INP_DIS)
/* LCD Common or Segment Drive */
#define VMyTherm_LCD_COM_SEG            (* (reg8 *) VMyTherm__LCD_COM_SEG)
/* Enable Segment LCD */
#define VMyTherm_LCD_EN                 (* (reg8 *) VMyTherm__LCD_EN)
/* Slew Rate Control */
#define VMyTherm_SLW                    (* (reg8 *) VMyTherm__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VMyTherm_PRTDSI__CAPS_SEL       (* (reg8 *) VMyTherm__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VMyTherm_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VMyTherm__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VMyTherm_PRTDSI__OE_SEL0        (* (reg8 *) VMyTherm__PRTDSI__OE_SEL0) 
#define VMyTherm_PRTDSI__OE_SEL1        (* (reg8 *) VMyTherm__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VMyTherm_PRTDSI__OUT_SEL0       (* (reg8 *) VMyTherm__PRTDSI__OUT_SEL0) 
#define VMyTherm_PRTDSI__OUT_SEL1       (* (reg8 *) VMyTherm__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VMyTherm_PRTDSI__SYNC_OUT       (* (reg8 *) VMyTherm__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(VMyTherm__SIO_CFG)
    #define VMyTherm_SIO_HYST_EN        (* (reg8 *) VMyTherm__SIO_HYST_EN)
    #define VMyTherm_SIO_REG_HIFREQ     (* (reg8 *) VMyTherm__SIO_REG_HIFREQ)
    #define VMyTherm_SIO_CFG            (* (reg8 *) VMyTherm__SIO_CFG)
    #define VMyTherm_SIO_DIFF           (* (reg8 *) VMyTherm__SIO_DIFF)
#endif /* (VMyTherm__SIO_CFG) */

/* Interrupt Registers */
#if defined(VMyTherm__INTSTAT)
    #define VMyTherm_INTSTAT            (* (reg8 *) VMyTherm__INTSTAT)
    #define VMyTherm_SNAP               (* (reg8 *) VMyTherm__SNAP)
    
	#define VMyTherm_0_INTTYPE_REG 		(* (reg8 *) VMyTherm__0__INTTYPE)
#endif /* (VMyTherm__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_VMyTherm_H */


/* [] END OF FILE */
