/*******************************************************************************
* File Name: neck_scale3.h  
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

#if !defined(CY_PINS_neck_scale3_H) /* Pins neck_scale3_H */
#define CY_PINS_neck_scale3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "neck_scale3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 neck_scale3__PORT == 15 && ((neck_scale3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    neck_scale3_Write(uint8 value);
void    neck_scale3_SetDriveMode(uint8 mode);
uint8   neck_scale3_ReadDataReg(void);
uint8   neck_scale3_Read(void);
void    neck_scale3_SetInterruptMode(uint16 position, uint16 mode);
uint8   neck_scale3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the neck_scale3_SetDriveMode() function.
     *  @{
     */
        #define neck_scale3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define neck_scale3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define neck_scale3_DM_RES_UP          PIN_DM_RES_UP
        #define neck_scale3_DM_RES_DWN         PIN_DM_RES_DWN
        #define neck_scale3_DM_OD_LO           PIN_DM_OD_LO
        #define neck_scale3_DM_OD_HI           PIN_DM_OD_HI
        #define neck_scale3_DM_STRONG          PIN_DM_STRONG
        #define neck_scale3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define neck_scale3_MASK               neck_scale3__MASK
#define neck_scale3_SHIFT              neck_scale3__SHIFT
#define neck_scale3_WIDTH              1u

/* Interrupt constants */
#if defined(neck_scale3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in neck_scale3_SetInterruptMode() function.
     *  @{
     */
        #define neck_scale3_INTR_NONE      (uint16)(0x0000u)
        #define neck_scale3_INTR_RISING    (uint16)(0x0001u)
        #define neck_scale3_INTR_FALLING   (uint16)(0x0002u)
        #define neck_scale3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define neck_scale3_INTR_MASK      (0x01u) 
#endif /* (neck_scale3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define neck_scale3_PS                     (* (reg8 *) neck_scale3__PS)
/* Data Register */
#define neck_scale3_DR                     (* (reg8 *) neck_scale3__DR)
/* Port Number */
#define neck_scale3_PRT_NUM                (* (reg8 *) neck_scale3__PRT) 
/* Connect to Analog Globals */                                                  
#define neck_scale3_AG                     (* (reg8 *) neck_scale3__AG)                       
/* Analog MUX bux enable */
#define neck_scale3_AMUX                   (* (reg8 *) neck_scale3__AMUX) 
/* Bidirectional Enable */                                                        
#define neck_scale3_BIE                    (* (reg8 *) neck_scale3__BIE)
/* Bit-mask for Aliased Register Access */
#define neck_scale3_BIT_MASK               (* (reg8 *) neck_scale3__BIT_MASK)
/* Bypass Enable */
#define neck_scale3_BYP                    (* (reg8 *) neck_scale3__BYP)
/* Port wide control signals */                                                   
#define neck_scale3_CTL                    (* (reg8 *) neck_scale3__CTL)
/* Drive Modes */
#define neck_scale3_DM0                    (* (reg8 *) neck_scale3__DM0) 
#define neck_scale3_DM1                    (* (reg8 *) neck_scale3__DM1)
#define neck_scale3_DM2                    (* (reg8 *) neck_scale3__DM2) 
/* Input Buffer Disable Override */
#define neck_scale3_INP_DIS                (* (reg8 *) neck_scale3__INP_DIS)
/* LCD Common or Segment Drive */
#define neck_scale3_LCD_COM_SEG            (* (reg8 *) neck_scale3__LCD_COM_SEG)
/* Enable Segment LCD */
#define neck_scale3_LCD_EN                 (* (reg8 *) neck_scale3__LCD_EN)
/* Slew Rate Control */
#define neck_scale3_SLW                    (* (reg8 *) neck_scale3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define neck_scale3_PRTDSI__CAPS_SEL       (* (reg8 *) neck_scale3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define neck_scale3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) neck_scale3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define neck_scale3_PRTDSI__OE_SEL0        (* (reg8 *) neck_scale3__PRTDSI__OE_SEL0) 
#define neck_scale3_PRTDSI__OE_SEL1        (* (reg8 *) neck_scale3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define neck_scale3_PRTDSI__OUT_SEL0       (* (reg8 *) neck_scale3__PRTDSI__OUT_SEL0) 
#define neck_scale3_PRTDSI__OUT_SEL1       (* (reg8 *) neck_scale3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define neck_scale3_PRTDSI__SYNC_OUT       (* (reg8 *) neck_scale3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(neck_scale3__SIO_CFG)
    #define neck_scale3_SIO_HYST_EN        (* (reg8 *) neck_scale3__SIO_HYST_EN)
    #define neck_scale3_SIO_REG_HIFREQ     (* (reg8 *) neck_scale3__SIO_REG_HIFREQ)
    #define neck_scale3_SIO_CFG            (* (reg8 *) neck_scale3__SIO_CFG)
    #define neck_scale3_SIO_DIFF           (* (reg8 *) neck_scale3__SIO_DIFF)
#endif /* (neck_scale3__SIO_CFG) */

/* Interrupt Registers */
#if defined(neck_scale3__INTSTAT)
    #define neck_scale3_INTSTAT            (* (reg8 *) neck_scale3__INTSTAT)
    #define neck_scale3_SNAP               (* (reg8 *) neck_scale3__SNAP)
    
	#define neck_scale3_0_INTTYPE_REG 		(* (reg8 *) neck_scale3__0__INTTYPE)
#endif /* (neck_scale3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_neck_scale3_H */


/* [] END OF FILE */
