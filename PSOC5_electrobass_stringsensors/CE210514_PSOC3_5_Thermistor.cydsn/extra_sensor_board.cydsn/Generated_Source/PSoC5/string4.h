/*******************************************************************************
* File Name: string4.h  
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

#if !defined(CY_PINS_string4_H) /* Pins string4_H */
#define CY_PINS_string4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "string4_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 string4__PORT == 15 && ((string4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    string4_Write(uint8 value);
void    string4_SetDriveMode(uint8 mode);
uint8   string4_ReadDataReg(void);
uint8   string4_Read(void);
void    string4_SetInterruptMode(uint16 position, uint16 mode);
uint8   string4_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the string4_SetDriveMode() function.
     *  @{
     */
        #define string4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define string4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define string4_DM_RES_UP          PIN_DM_RES_UP
        #define string4_DM_RES_DWN         PIN_DM_RES_DWN
        #define string4_DM_OD_LO           PIN_DM_OD_LO
        #define string4_DM_OD_HI           PIN_DM_OD_HI
        #define string4_DM_STRONG          PIN_DM_STRONG
        #define string4_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define string4_MASK               string4__MASK
#define string4_SHIFT              string4__SHIFT
#define string4_WIDTH              1u

/* Interrupt constants */
#if defined(string4__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in string4_SetInterruptMode() function.
     *  @{
     */
        #define string4_INTR_NONE      (uint16)(0x0000u)
        #define string4_INTR_RISING    (uint16)(0x0001u)
        #define string4_INTR_FALLING   (uint16)(0x0002u)
        #define string4_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define string4_INTR_MASK      (0x01u) 
#endif /* (string4__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define string4_PS                     (* (reg8 *) string4__PS)
/* Data Register */
#define string4_DR                     (* (reg8 *) string4__DR)
/* Port Number */
#define string4_PRT_NUM                (* (reg8 *) string4__PRT) 
/* Connect to Analog Globals */                                                  
#define string4_AG                     (* (reg8 *) string4__AG)                       
/* Analog MUX bux enable */
#define string4_AMUX                   (* (reg8 *) string4__AMUX) 
/* Bidirectional Enable */                                                        
#define string4_BIE                    (* (reg8 *) string4__BIE)
/* Bit-mask for Aliased Register Access */
#define string4_BIT_MASK               (* (reg8 *) string4__BIT_MASK)
/* Bypass Enable */
#define string4_BYP                    (* (reg8 *) string4__BYP)
/* Port wide control signals */                                                   
#define string4_CTL                    (* (reg8 *) string4__CTL)
/* Drive Modes */
#define string4_DM0                    (* (reg8 *) string4__DM0) 
#define string4_DM1                    (* (reg8 *) string4__DM1)
#define string4_DM2                    (* (reg8 *) string4__DM2) 
/* Input Buffer Disable Override */
#define string4_INP_DIS                (* (reg8 *) string4__INP_DIS)
/* LCD Common or Segment Drive */
#define string4_LCD_COM_SEG            (* (reg8 *) string4__LCD_COM_SEG)
/* Enable Segment LCD */
#define string4_LCD_EN                 (* (reg8 *) string4__LCD_EN)
/* Slew Rate Control */
#define string4_SLW                    (* (reg8 *) string4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define string4_PRTDSI__CAPS_SEL       (* (reg8 *) string4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define string4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) string4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define string4_PRTDSI__OE_SEL0        (* (reg8 *) string4__PRTDSI__OE_SEL0) 
#define string4_PRTDSI__OE_SEL1        (* (reg8 *) string4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define string4_PRTDSI__OUT_SEL0       (* (reg8 *) string4__PRTDSI__OUT_SEL0) 
#define string4_PRTDSI__OUT_SEL1       (* (reg8 *) string4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define string4_PRTDSI__SYNC_OUT       (* (reg8 *) string4__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(string4__SIO_CFG)
    #define string4_SIO_HYST_EN        (* (reg8 *) string4__SIO_HYST_EN)
    #define string4_SIO_REG_HIFREQ     (* (reg8 *) string4__SIO_REG_HIFREQ)
    #define string4_SIO_CFG            (* (reg8 *) string4__SIO_CFG)
    #define string4_SIO_DIFF           (* (reg8 *) string4__SIO_DIFF)
#endif /* (string4__SIO_CFG) */

/* Interrupt Registers */
#if defined(string4__INTSTAT)
    #define string4_INTSTAT            (* (reg8 *) string4__INTSTAT)
    #define string4_SNAP               (* (reg8 *) string4__SNAP)
    
	#define string4_0_INTTYPE_REG 		(* (reg8 *) string4__0__INTTYPE)
#endif /* (string4__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_string4_H */


/* [] END OF FILE */
