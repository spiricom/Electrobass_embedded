/*******************************************************************************
* File Name: string3.h  
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

#if !defined(CY_PINS_string3_H) /* Pins string3_H */
#define CY_PINS_string3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "string3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 string3__PORT == 15 && ((string3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    string3_Write(uint8 value);
void    string3_SetDriveMode(uint8 mode);
uint8   string3_ReadDataReg(void);
uint8   string3_Read(void);
void    string3_SetInterruptMode(uint16 position, uint16 mode);
uint8   string3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the string3_SetDriveMode() function.
     *  @{
     */
        #define string3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define string3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define string3_DM_RES_UP          PIN_DM_RES_UP
        #define string3_DM_RES_DWN         PIN_DM_RES_DWN
        #define string3_DM_OD_LO           PIN_DM_OD_LO
        #define string3_DM_OD_HI           PIN_DM_OD_HI
        #define string3_DM_STRONG          PIN_DM_STRONG
        #define string3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define string3_MASK               string3__MASK
#define string3_SHIFT              string3__SHIFT
#define string3_WIDTH              1u

/* Interrupt constants */
#if defined(string3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in string3_SetInterruptMode() function.
     *  @{
     */
        #define string3_INTR_NONE      (uint16)(0x0000u)
        #define string3_INTR_RISING    (uint16)(0x0001u)
        #define string3_INTR_FALLING   (uint16)(0x0002u)
        #define string3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define string3_INTR_MASK      (0x01u) 
#endif /* (string3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define string3_PS                     (* (reg8 *) string3__PS)
/* Data Register */
#define string3_DR                     (* (reg8 *) string3__DR)
/* Port Number */
#define string3_PRT_NUM                (* (reg8 *) string3__PRT) 
/* Connect to Analog Globals */                                                  
#define string3_AG                     (* (reg8 *) string3__AG)                       
/* Analog MUX bux enable */
#define string3_AMUX                   (* (reg8 *) string3__AMUX) 
/* Bidirectional Enable */                                                        
#define string3_BIE                    (* (reg8 *) string3__BIE)
/* Bit-mask for Aliased Register Access */
#define string3_BIT_MASK               (* (reg8 *) string3__BIT_MASK)
/* Bypass Enable */
#define string3_BYP                    (* (reg8 *) string3__BYP)
/* Port wide control signals */                                                   
#define string3_CTL                    (* (reg8 *) string3__CTL)
/* Drive Modes */
#define string3_DM0                    (* (reg8 *) string3__DM0) 
#define string3_DM1                    (* (reg8 *) string3__DM1)
#define string3_DM2                    (* (reg8 *) string3__DM2) 
/* Input Buffer Disable Override */
#define string3_INP_DIS                (* (reg8 *) string3__INP_DIS)
/* LCD Common or Segment Drive */
#define string3_LCD_COM_SEG            (* (reg8 *) string3__LCD_COM_SEG)
/* Enable Segment LCD */
#define string3_LCD_EN                 (* (reg8 *) string3__LCD_EN)
/* Slew Rate Control */
#define string3_SLW                    (* (reg8 *) string3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define string3_PRTDSI__CAPS_SEL       (* (reg8 *) string3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define string3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) string3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define string3_PRTDSI__OE_SEL0        (* (reg8 *) string3__PRTDSI__OE_SEL0) 
#define string3_PRTDSI__OE_SEL1        (* (reg8 *) string3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define string3_PRTDSI__OUT_SEL0       (* (reg8 *) string3__PRTDSI__OUT_SEL0) 
#define string3_PRTDSI__OUT_SEL1       (* (reg8 *) string3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define string3_PRTDSI__SYNC_OUT       (* (reg8 *) string3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(string3__SIO_CFG)
    #define string3_SIO_HYST_EN        (* (reg8 *) string3__SIO_HYST_EN)
    #define string3_SIO_REG_HIFREQ     (* (reg8 *) string3__SIO_REG_HIFREQ)
    #define string3_SIO_CFG            (* (reg8 *) string3__SIO_CFG)
    #define string3_SIO_DIFF           (* (reg8 *) string3__SIO_DIFF)
#endif /* (string3__SIO_CFG) */

/* Interrupt Registers */
#if defined(string3__INTSTAT)
    #define string3_INTSTAT            (* (reg8 *) string3__INTSTAT)
    #define string3_SNAP               (* (reg8 *) string3__SNAP)
    
	#define string3_0_INTTYPE_REG 		(* (reg8 *) string3__0__INTTYPE)
#endif /* (string3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_string3_H */


/* [] END OF FILE */
