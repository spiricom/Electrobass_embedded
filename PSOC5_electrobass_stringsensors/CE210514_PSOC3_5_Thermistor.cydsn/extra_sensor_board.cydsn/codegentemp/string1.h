/*******************************************************************************
* File Name: string1.h  
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

#if !defined(CY_PINS_string1_H) /* Pins string1_H */
#define CY_PINS_string1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "string1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 string1__PORT == 15 && ((string1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    string1_Write(uint8 value);
void    string1_SetDriveMode(uint8 mode);
uint8   string1_ReadDataReg(void);
uint8   string1_Read(void);
void    string1_SetInterruptMode(uint16 position, uint16 mode);
uint8   string1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the string1_SetDriveMode() function.
     *  @{
     */
        #define string1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define string1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define string1_DM_RES_UP          PIN_DM_RES_UP
        #define string1_DM_RES_DWN         PIN_DM_RES_DWN
        #define string1_DM_OD_LO           PIN_DM_OD_LO
        #define string1_DM_OD_HI           PIN_DM_OD_HI
        #define string1_DM_STRONG          PIN_DM_STRONG
        #define string1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define string1_MASK               string1__MASK
#define string1_SHIFT              string1__SHIFT
#define string1_WIDTH              1u

/* Interrupt constants */
#if defined(string1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in string1_SetInterruptMode() function.
     *  @{
     */
        #define string1_INTR_NONE      (uint16)(0x0000u)
        #define string1_INTR_RISING    (uint16)(0x0001u)
        #define string1_INTR_FALLING   (uint16)(0x0002u)
        #define string1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define string1_INTR_MASK      (0x01u) 
#endif /* (string1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define string1_PS                     (* (reg8 *) string1__PS)
/* Data Register */
#define string1_DR                     (* (reg8 *) string1__DR)
/* Port Number */
#define string1_PRT_NUM                (* (reg8 *) string1__PRT) 
/* Connect to Analog Globals */                                                  
#define string1_AG                     (* (reg8 *) string1__AG)                       
/* Analog MUX bux enable */
#define string1_AMUX                   (* (reg8 *) string1__AMUX) 
/* Bidirectional Enable */                                                        
#define string1_BIE                    (* (reg8 *) string1__BIE)
/* Bit-mask for Aliased Register Access */
#define string1_BIT_MASK               (* (reg8 *) string1__BIT_MASK)
/* Bypass Enable */
#define string1_BYP                    (* (reg8 *) string1__BYP)
/* Port wide control signals */                                                   
#define string1_CTL                    (* (reg8 *) string1__CTL)
/* Drive Modes */
#define string1_DM0                    (* (reg8 *) string1__DM0) 
#define string1_DM1                    (* (reg8 *) string1__DM1)
#define string1_DM2                    (* (reg8 *) string1__DM2) 
/* Input Buffer Disable Override */
#define string1_INP_DIS                (* (reg8 *) string1__INP_DIS)
/* LCD Common or Segment Drive */
#define string1_LCD_COM_SEG            (* (reg8 *) string1__LCD_COM_SEG)
/* Enable Segment LCD */
#define string1_LCD_EN                 (* (reg8 *) string1__LCD_EN)
/* Slew Rate Control */
#define string1_SLW                    (* (reg8 *) string1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define string1_PRTDSI__CAPS_SEL       (* (reg8 *) string1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define string1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) string1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define string1_PRTDSI__OE_SEL0        (* (reg8 *) string1__PRTDSI__OE_SEL0) 
#define string1_PRTDSI__OE_SEL1        (* (reg8 *) string1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define string1_PRTDSI__OUT_SEL0       (* (reg8 *) string1__PRTDSI__OUT_SEL0) 
#define string1_PRTDSI__OUT_SEL1       (* (reg8 *) string1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define string1_PRTDSI__SYNC_OUT       (* (reg8 *) string1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(string1__SIO_CFG)
    #define string1_SIO_HYST_EN        (* (reg8 *) string1__SIO_HYST_EN)
    #define string1_SIO_REG_HIFREQ     (* (reg8 *) string1__SIO_REG_HIFREQ)
    #define string1_SIO_CFG            (* (reg8 *) string1__SIO_CFG)
    #define string1_SIO_DIFF           (* (reg8 *) string1__SIO_DIFF)
#endif /* (string1__SIO_CFG) */

/* Interrupt Registers */
#if defined(string1__INTSTAT)
    #define string1_INTSTAT            (* (reg8 *) string1__INTSTAT)
    #define string1_SNAP               (* (reg8 *) string1__SNAP)
    
	#define string1_0_INTTYPE_REG 		(* (reg8 *) string1__0__INTTYPE)
#endif /* (string1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_string1_H */


/* [] END OF FILE */
