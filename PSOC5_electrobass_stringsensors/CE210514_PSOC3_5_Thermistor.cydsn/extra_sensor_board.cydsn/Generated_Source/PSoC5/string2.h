/*******************************************************************************
* File Name: string2.h  
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

#if !defined(CY_PINS_string2_H) /* Pins string2_H */
#define CY_PINS_string2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "string2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 string2__PORT == 15 && ((string2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    string2_Write(uint8 value);
void    string2_SetDriveMode(uint8 mode);
uint8   string2_ReadDataReg(void);
uint8   string2_Read(void);
void    string2_SetInterruptMode(uint16 position, uint16 mode);
uint8   string2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the string2_SetDriveMode() function.
     *  @{
     */
        #define string2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define string2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define string2_DM_RES_UP          PIN_DM_RES_UP
        #define string2_DM_RES_DWN         PIN_DM_RES_DWN
        #define string2_DM_OD_LO           PIN_DM_OD_LO
        #define string2_DM_OD_HI           PIN_DM_OD_HI
        #define string2_DM_STRONG          PIN_DM_STRONG
        #define string2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define string2_MASK               string2__MASK
#define string2_SHIFT              string2__SHIFT
#define string2_WIDTH              1u

/* Interrupt constants */
#if defined(string2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in string2_SetInterruptMode() function.
     *  @{
     */
        #define string2_INTR_NONE      (uint16)(0x0000u)
        #define string2_INTR_RISING    (uint16)(0x0001u)
        #define string2_INTR_FALLING   (uint16)(0x0002u)
        #define string2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define string2_INTR_MASK      (0x01u) 
#endif /* (string2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define string2_PS                     (* (reg8 *) string2__PS)
/* Data Register */
#define string2_DR                     (* (reg8 *) string2__DR)
/* Port Number */
#define string2_PRT_NUM                (* (reg8 *) string2__PRT) 
/* Connect to Analog Globals */                                                  
#define string2_AG                     (* (reg8 *) string2__AG)                       
/* Analog MUX bux enable */
#define string2_AMUX                   (* (reg8 *) string2__AMUX) 
/* Bidirectional Enable */                                                        
#define string2_BIE                    (* (reg8 *) string2__BIE)
/* Bit-mask for Aliased Register Access */
#define string2_BIT_MASK               (* (reg8 *) string2__BIT_MASK)
/* Bypass Enable */
#define string2_BYP                    (* (reg8 *) string2__BYP)
/* Port wide control signals */                                                   
#define string2_CTL                    (* (reg8 *) string2__CTL)
/* Drive Modes */
#define string2_DM0                    (* (reg8 *) string2__DM0) 
#define string2_DM1                    (* (reg8 *) string2__DM1)
#define string2_DM2                    (* (reg8 *) string2__DM2) 
/* Input Buffer Disable Override */
#define string2_INP_DIS                (* (reg8 *) string2__INP_DIS)
/* LCD Common or Segment Drive */
#define string2_LCD_COM_SEG            (* (reg8 *) string2__LCD_COM_SEG)
/* Enable Segment LCD */
#define string2_LCD_EN                 (* (reg8 *) string2__LCD_EN)
/* Slew Rate Control */
#define string2_SLW                    (* (reg8 *) string2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define string2_PRTDSI__CAPS_SEL       (* (reg8 *) string2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define string2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) string2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define string2_PRTDSI__OE_SEL0        (* (reg8 *) string2__PRTDSI__OE_SEL0) 
#define string2_PRTDSI__OE_SEL1        (* (reg8 *) string2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define string2_PRTDSI__OUT_SEL0       (* (reg8 *) string2__PRTDSI__OUT_SEL0) 
#define string2_PRTDSI__OUT_SEL1       (* (reg8 *) string2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define string2_PRTDSI__SYNC_OUT       (* (reg8 *) string2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(string2__SIO_CFG)
    #define string2_SIO_HYST_EN        (* (reg8 *) string2__SIO_HYST_EN)
    #define string2_SIO_REG_HIFREQ     (* (reg8 *) string2__SIO_REG_HIFREQ)
    #define string2_SIO_CFG            (* (reg8 *) string2__SIO_CFG)
    #define string2_SIO_DIFF           (* (reg8 *) string2__SIO_DIFF)
#endif /* (string2__SIO_CFG) */

/* Interrupt Registers */
#if defined(string2__INTSTAT)
    #define string2_INTSTAT            (* (reg8 *) string2__INTSTAT)
    #define string2_SNAP               (* (reg8 *) string2__SNAP)
    
	#define string2_0_INTTYPE_REG 		(* (reg8 *) string2__0__INTTYPE)
#endif /* (string2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_string2_H */


/* [] END OF FILE */
