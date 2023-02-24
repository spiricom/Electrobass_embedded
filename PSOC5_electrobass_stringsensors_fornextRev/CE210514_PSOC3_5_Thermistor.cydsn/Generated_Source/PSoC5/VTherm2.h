/*******************************************************************************
* File Name: VTherm2.h  
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

#if !defined(CY_PINS_VTherm2_H) /* Pins VTherm2_H */
#define CY_PINS_VTherm2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VTherm2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 VTherm2__PORT == 15 && ((VTherm2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    VTherm2_Write(uint8 value);
void    VTherm2_SetDriveMode(uint8 mode);
uint8   VTherm2_ReadDataReg(void);
uint8   VTherm2_Read(void);
void    VTherm2_SetInterruptMode(uint16 position, uint16 mode);
uint8   VTherm2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the VTherm2_SetDriveMode() function.
     *  @{
     */
        #define VTherm2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define VTherm2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define VTherm2_DM_RES_UP          PIN_DM_RES_UP
        #define VTherm2_DM_RES_DWN         PIN_DM_RES_DWN
        #define VTherm2_DM_OD_LO           PIN_DM_OD_LO
        #define VTherm2_DM_OD_HI           PIN_DM_OD_HI
        #define VTherm2_DM_STRONG          PIN_DM_STRONG
        #define VTherm2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define VTherm2_MASK               VTherm2__MASK
#define VTherm2_SHIFT              VTherm2__SHIFT
#define VTherm2_WIDTH              1u

/* Interrupt constants */
#if defined(VTherm2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VTherm2_SetInterruptMode() function.
     *  @{
     */
        #define VTherm2_INTR_NONE      (uint16)(0x0000u)
        #define VTherm2_INTR_RISING    (uint16)(0x0001u)
        #define VTherm2_INTR_FALLING   (uint16)(0x0002u)
        #define VTherm2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define VTherm2_INTR_MASK      (0x01u) 
#endif /* (VTherm2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VTherm2_PS                     (* (reg8 *) VTherm2__PS)
/* Data Register */
#define VTherm2_DR                     (* (reg8 *) VTherm2__DR)
/* Port Number */
#define VTherm2_PRT_NUM                (* (reg8 *) VTherm2__PRT) 
/* Connect to Analog Globals */                                                  
#define VTherm2_AG                     (* (reg8 *) VTherm2__AG)                       
/* Analog MUX bux enable */
#define VTherm2_AMUX                   (* (reg8 *) VTherm2__AMUX) 
/* Bidirectional Enable */                                                        
#define VTherm2_BIE                    (* (reg8 *) VTherm2__BIE)
/* Bit-mask for Aliased Register Access */
#define VTherm2_BIT_MASK               (* (reg8 *) VTherm2__BIT_MASK)
/* Bypass Enable */
#define VTherm2_BYP                    (* (reg8 *) VTherm2__BYP)
/* Port wide control signals */                                                   
#define VTherm2_CTL                    (* (reg8 *) VTherm2__CTL)
/* Drive Modes */
#define VTherm2_DM0                    (* (reg8 *) VTherm2__DM0) 
#define VTherm2_DM1                    (* (reg8 *) VTherm2__DM1)
#define VTherm2_DM2                    (* (reg8 *) VTherm2__DM2) 
/* Input Buffer Disable Override */
#define VTherm2_INP_DIS                (* (reg8 *) VTherm2__INP_DIS)
/* LCD Common or Segment Drive */
#define VTherm2_LCD_COM_SEG            (* (reg8 *) VTherm2__LCD_COM_SEG)
/* Enable Segment LCD */
#define VTherm2_LCD_EN                 (* (reg8 *) VTherm2__LCD_EN)
/* Slew Rate Control */
#define VTherm2_SLW                    (* (reg8 *) VTherm2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VTherm2_PRTDSI__CAPS_SEL       (* (reg8 *) VTherm2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VTherm2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VTherm2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VTherm2_PRTDSI__OE_SEL0        (* (reg8 *) VTherm2__PRTDSI__OE_SEL0) 
#define VTherm2_PRTDSI__OE_SEL1        (* (reg8 *) VTherm2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VTherm2_PRTDSI__OUT_SEL0       (* (reg8 *) VTherm2__PRTDSI__OUT_SEL0) 
#define VTherm2_PRTDSI__OUT_SEL1       (* (reg8 *) VTherm2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VTherm2_PRTDSI__SYNC_OUT       (* (reg8 *) VTherm2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(VTherm2__SIO_CFG)
    #define VTherm2_SIO_HYST_EN        (* (reg8 *) VTherm2__SIO_HYST_EN)
    #define VTherm2_SIO_REG_HIFREQ     (* (reg8 *) VTherm2__SIO_REG_HIFREQ)
    #define VTherm2_SIO_CFG            (* (reg8 *) VTherm2__SIO_CFG)
    #define VTherm2_SIO_DIFF           (* (reg8 *) VTherm2__SIO_DIFF)
#endif /* (VTherm2__SIO_CFG) */

/* Interrupt Registers */
#if defined(VTherm2__INTSTAT)
    #define VTherm2_INTSTAT            (* (reg8 *) VTherm2__INTSTAT)
    #define VTherm2_SNAP               (* (reg8 *) VTherm2__SNAP)
    
	#define VTherm2_0_INTTYPE_REG 		(* (reg8 *) VTherm2__0__INTTYPE)
#endif /* (VTherm2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_VTherm2_H */


/* [] END OF FILE */
