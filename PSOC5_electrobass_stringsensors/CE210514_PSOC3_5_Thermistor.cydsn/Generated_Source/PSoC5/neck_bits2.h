/*******************************************************************************
* File Name: neck_bits2.h  
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

#if !defined(CY_PINS_neck_bits2_H) /* Pins neck_bits2_H */
#define CY_PINS_neck_bits2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "neck_bits2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 neck_bits2__PORT == 15 && ((neck_bits2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    neck_bits2_Write(uint8 value);
void    neck_bits2_SetDriveMode(uint8 mode);
uint8   neck_bits2_ReadDataReg(void);
uint8   neck_bits2_Read(void);
void    neck_bits2_SetInterruptMode(uint16 position, uint16 mode);
uint8   neck_bits2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the neck_bits2_SetDriveMode() function.
     *  @{
     */
        #define neck_bits2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define neck_bits2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define neck_bits2_DM_RES_UP          PIN_DM_RES_UP
        #define neck_bits2_DM_RES_DWN         PIN_DM_RES_DWN
        #define neck_bits2_DM_OD_LO           PIN_DM_OD_LO
        #define neck_bits2_DM_OD_HI           PIN_DM_OD_HI
        #define neck_bits2_DM_STRONG          PIN_DM_STRONG
        #define neck_bits2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define neck_bits2_MASK               neck_bits2__MASK
#define neck_bits2_SHIFT              neck_bits2__SHIFT
#define neck_bits2_WIDTH              1u

/* Interrupt constants */
#if defined(neck_bits2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in neck_bits2_SetInterruptMode() function.
     *  @{
     */
        #define neck_bits2_INTR_NONE      (uint16)(0x0000u)
        #define neck_bits2_INTR_RISING    (uint16)(0x0001u)
        #define neck_bits2_INTR_FALLING   (uint16)(0x0002u)
        #define neck_bits2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define neck_bits2_INTR_MASK      (0x01u) 
#endif /* (neck_bits2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define neck_bits2_PS                     (* (reg8 *) neck_bits2__PS)
/* Data Register */
#define neck_bits2_DR                     (* (reg8 *) neck_bits2__DR)
/* Port Number */
#define neck_bits2_PRT_NUM                (* (reg8 *) neck_bits2__PRT) 
/* Connect to Analog Globals */                                                  
#define neck_bits2_AG                     (* (reg8 *) neck_bits2__AG)                       
/* Analog MUX bux enable */
#define neck_bits2_AMUX                   (* (reg8 *) neck_bits2__AMUX) 
/* Bidirectional Enable */                                                        
#define neck_bits2_BIE                    (* (reg8 *) neck_bits2__BIE)
/* Bit-mask for Aliased Register Access */
#define neck_bits2_BIT_MASK               (* (reg8 *) neck_bits2__BIT_MASK)
/* Bypass Enable */
#define neck_bits2_BYP                    (* (reg8 *) neck_bits2__BYP)
/* Port wide control signals */                                                   
#define neck_bits2_CTL                    (* (reg8 *) neck_bits2__CTL)
/* Drive Modes */
#define neck_bits2_DM0                    (* (reg8 *) neck_bits2__DM0) 
#define neck_bits2_DM1                    (* (reg8 *) neck_bits2__DM1)
#define neck_bits2_DM2                    (* (reg8 *) neck_bits2__DM2) 
/* Input Buffer Disable Override */
#define neck_bits2_INP_DIS                (* (reg8 *) neck_bits2__INP_DIS)
/* LCD Common or Segment Drive */
#define neck_bits2_LCD_COM_SEG            (* (reg8 *) neck_bits2__LCD_COM_SEG)
/* Enable Segment LCD */
#define neck_bits2_LCD_EN                 (* (reg8 *) neck_bits2__LCD_EN)
/* Slew Rate Control */
#define neck_bits2_SLW                    (* (reg8 *) neck_bits2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define neck_bits2_PRTDSI__CAPS_SEL       (* (reg8 *) neck_bits2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define neck_bits2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) neck_bits2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define neck_bits2_PRTDSI__OE_SEL0        (* (reg8 *) neck_bits2__PRTDSI__OE_SEL0) 
#define neck_bits2_PRTDSI__OE_SEL1        (* (reg8 *) neck_bits2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define neck_bits2_PRTDSI__OUT_SEL0       (* (reg8 *) neck_bits2__PRTDSI__OUT_SEL0) 
#define neck_bits2_PRTDSI__OUT_SEL1       (* (reg8 *) neck_bits2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define neck_bits2_PRTDSI__SYNC_OUT       (* (reg8 *) neck_bits2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(neck_bits2__SIO_CFG)
    #define neck_bits2_SIO_HYST_EN        (* (reg8 *) neck_bits2__SIO_HYST_EN)
    #define neck_bits2_SIO_REG_HIFREQ     (* (reg8 *) neck_bits2__SIO_REG_HIFREQ)
    #define neck_bits2_SIO_CFG            (* (reg8 *) neck_bits2__SIO_CFG)
    #define neck_bits2_SIO_DIFF           (* (reg8 *) neck_bits2__SIO_DIFF)
#endif /* (neck_bits2__SIO_CFG) */

/* Interrupt Registers */
#if defined(neck_bits2__INTSTAT)
    #define neck_bits2_INTSTAT            (* (reg8 *) neck_bits2__INTSTAT)
    #define neck_bits2_SNAP               (* (reg8 *) neck_bits2__SNAP)
    
	#define neck_bits2_0_INTTYPE_REG 		(* (reg8 *) neck_bits2__0__INTTYPE)
#endif /* (neck_bits2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_neck_bits2_H */


/* [] END OF FILE */
