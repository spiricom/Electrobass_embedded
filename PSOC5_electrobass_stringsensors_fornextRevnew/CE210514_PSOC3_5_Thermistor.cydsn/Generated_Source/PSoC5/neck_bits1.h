/*******************************************************************************
* File Name: neck_bits1.h  
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

#if !defined(CY_PINS_neck_bits1_H) /* Pins neck_bits1_H */
#define CY_PINS_neck_bits1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "neck_bits1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 neck_bits1__PORT == 15 && ((neck_bits1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    neck_bits1_Write(uint8 value);
void    neck_bits1_SetDriveMode(uint8 mode);
uint8   neck_bits1_ReadDataReg(void);
uint8   neck_bits1_Read(void);
void    neck_bits1_SetInterruptMode(uint16 position, uint16 mode);
uint8   neck_bits1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the neck_bits1_SetDriveMode() function.
     *  @{
     */
        #define neck_bits1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define neck_bits1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define neck_bits1_DM_RES_UP          PIN_DM_RES_UP
        #define neck_bits1_DM_RES_DWN         PIN_DM_RES_DWN
        #define neck_bits1_DM_OD_LO           PIN_DM_OD_LO
        #define neck_bits1_DM_OD_HI           PIN_DM_OD_HI
        #define neck_bits1_DM_STRONG          PIN_DM_STRONG
        #define neck_bits1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define neck_bits1_MASK               neck_bits1__MASK
#define neck_bits1_SHIFT              neck_bits1__SHIFT
#define neck_bits1_WIDTH              1u

/* Interrupt constants */
#if defined(neck_bits1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in neck_bits1_SetInterruptMode() function.
     *  @{
     */
        #define neck_bits1_INTR_NONE      (uint16)(0x0000u)
        #define neck_bits1_INTR_RISING    (uint16)(0x0001u)
        #define neck_bits1_INTR_FALLING   (uint16)(0x0002u)
        #define neck_bits1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define neck_bits1_INTR_MASK      (0x01u) 
#endif /* (neck_bits1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define neck_bits1_PS                     (* (reg8 *) neck_bits1__PS)
/* Data Register */
#define neck_bits1_DR                     (* (reg8 *) neck_bits1__DR)
/* Port Number */
#define neck_bits1_PRT_NUM                (* (reg8 *) neck_bits1__PRT) 
/* Connect to Analog Globals */                                                  
#define neck_bits1_AG                     (* (reg8 *) neck_bits1__AG)                       
/* Analog MUX bux enable */
#define neck_bits1_AMUX                   (* (reg8 *) neck_bits1__AMUX) 
/* Bidirectional Enable */                                                        
#define neck_bits1_BIE                    (* (reg8 *) neck_bits1__BIE)
/* Bit-mask for Aliased Register Access */
#define neck_bits1_BIT_MASK               (* (reg8 *) neck_bits1__BIT_MASK)
/* Bypass Enable */
#define neck_bits1_BYP                    (* (reg8 *) neck_bits1__BYP)
/* Port wide control signals */                                                   
#define neck_bits1_CTL                    (* (reg8 *) neck_bits1__CTL)
/* Drive Modes */
#define neck_bits1_DM0                    (* (reg8 *) neck_bits1__DM0) 
#define neck_bits1_DM1                    (* (reg8 *) neck_bits1__DM1)
#define neck_bits1_DM2                    (* (reg8 *) neck_bits1__DM2) 
/* Input Buffer Disable Override */
#define neck_bits1_INP_DIS                (* (reg8 *) neck_bits1__INP_DIS)
/* LCD Common or Segment Drive */
#define neck_bits1_LCD_COM_SEG            (* (reg8 *) neck_bits1__LCD_COM_SEG)
/* Enable Segment LCD */
#define neck_bits1_LCD_EN                 (* (reg8 *) neck_bits1__LCD_EN)
/* Slew Rate Control */
#define neck_bits1_SLW                    (* (reg8 *) neck_bits1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define neck_bits1_PRTDSI__CAPS_SEL       (* (reg8 *) neck_bits1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define neck_bits1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) neck_bits1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define neck_bits1_PRTDSI__OE_SEL0        (* (reg8 *) neck_bits1__PRTDSI__OE_SEL0) 
#define neck_bits1_PRTDSI__OE_SEL1        (* (reg8 *) neck_bits1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define neck_bits1_PRTDSI__OUT_SEL0       (* (reg8 *) neck_bits1__PRTDSI__OUT_SEL0) 
#define neck_bits1_PRTDSI__OUT_SEL1       (* (reg8 *) neck_bits1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define neck_bits1_PRTDSI__SYNC_OUT       (* (reg8 *) neck_bits1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(neck_bits1__SIO_CFG)
    #define neck_bits1_SIO_HYST_EN        (* (reg8 *) neck_bits1__SIO_HYST_EN)
    #define neck_bits1_SIO_REG_HIFREQ     (* (reg8 *) neck_bits1__SIO_REG_HIFREQ)
    #define neck_bits1_SIO_CFG            (* (reg8 *) neck_bits1__SIO_CFG)
    #define neck_bits1_SIO_DIFF           (* (reg8 *) neck_bits1__SIO_DIFF)
#endif /* (neck_bits1__SIO_CFG) */

/* Interrupt Registers */
#if defined(neck_bits1__INTSTAT)
    #define neck_bits1_INTSTAT            (* (reg8 *) neck_bits1__INTSTAT)
    #define neck_bits1_SNAP               (* (reg8 *) neck_bits1__SNAP)
    
	#define neck_bits1_0_INTTYPE_REG 		(* (reg8 *) neck_bits1__0__INTTYPE)
#endif /* (neck_bits1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_neck_bits1_H */


/* [] END OF FILE */
