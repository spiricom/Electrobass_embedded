/*******************************************************************************
* File Name: normal_LED.h  
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

#if !defined(CY_PINS_normal_LED_H) /* Pins normal_LED_H */
#define CY_PINS_normal_LED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "normal_LED_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 normal_LED__PORT == 15 && ((normal_LED__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    normal_LED_Write(uint8 value);
void    normal_LED_SetDriveMode(uint8 mode);
uint8   normal_LED_ReadDataReg(void);
uint8   normal_LED_Read(void);
void    normal_LED_SetInterruptMode(uint16 position, uint16 mode);
uint8   normal_LED_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the normal_LED_SetDriveMode() function.
     *  @{
     */
        #define normal_LED_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define normal_LED_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define normal_LED_DM_RES_UP          PIN_DM_RES_UP
        #define normal_LED_DM_RES_DWN         PIN_DM_RES_DWN
        #define normal_LED_DM_OD_LO           PIN_DM_OD_LO
        #define normal_LED_DM_OD_HI           PIN_DM_OD_HI
        #define normal_LED_DM_STRONG          PIN_DM_STRONG
        #define normal_LED_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define normal_LED_MASK               normal_LED__MASK
#define normal_LED_SHIFT              normal_LED__SHIFT
#define normal_LED_WIDTH              1u

/* Interrupt constants */
#if defined(normal_LED__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in normal_LED_SetInterruptMode() function.
     *  @{
     */
        #define normal_LED_INTR_NONE      (uint16)(0x0000u)
        #define normal_LED_INTR_RISING    (uint16)(0x0001u)
        #define normal_LED_INTR_FALLING   (uint16)(0x0002u)
        #define normal_LED_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define normal_LED_INTR_MASK      (0x01u) 
#endif /* (normal_LED__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define normal_LED_PS                     (* (reg8 *) normal_LED__PS)
/* Data Register */
#define normal_LED_DR                     (* (reg8 *) normal_LED__DR)
/* Port Number */
#define normal_LED_PRT_NUM                (* (reg8 *) normal_LED__PRT) 
/* Connect to Analog Globals */                                                  
#define normal_LED_AG                     (* (reg8 *) normal_LED__AG)                       
/* Analog MUX bux enable */
#define normal_LED_AMUX                   (* (reg8 *) normal_LED__AMUX) 
/* Bidirectional Enable */                                                        
#define normal_LED_BIE                    (* (reg8 *) normal_LED__BIE)
/* Bit-mask for Aliased Register Access */
#define normal_LED_BIT_MASK               (* (reg8 *) normal_LED__BIT_MASK)
/* Bypass Enable */
#define normal_LED_BYP                    (* (reg8 *) normal_LED__BYP)
/* Port wide control signals */                                                   
#define normal_LED_CTL                    (* (reg8 *) normal_LED__CTL)
/* Drive Modes */
#define normal_LED_DM0                    (* (reg8 *) normal_LED__DM0) 
#define normal_LED_DM1                    (* (reg8 *) normal_LED__DM1)
#define normal_LED_DM2                    (* (reg8 *) normal_LED__DM2) 
/* Input Buffer Disable Override */
#define normal_LED_INP_DIS                (* (reg8 *) normal_LED__INP_DIS)
/* LCD Common or Segment Drive */
#define normal_LED_LCD_COM_SEG            (* (reg8 *) normal_LED__LCD_COM_SEG)
/* Enable Segment LCD */
#define normal_LED_LCD_EN                 (* (reg8 *) normal_LED__LCD_EN)
/* Slew Rate Control */
#define normal_LED_SLW                    (* (reg8 *) normal_LED__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define normal_LED_PRTDSI__CAPS_SEL       (* (reg8 *) normal_LED__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define normal_LED_PRTDSI__DBL_SYNC_IN    (* (reg8 *) normal_LED__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define normal_LED_PRTDSI__OE_SEL0        (* (reg8 *) normal_LED__PRTDSI__OE_SEL0) 
#define normal_LED_PRTDSI__OE_SEL1        (* (reg8 *) normal_LED__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define normal_LED_PRTDSI__OUT_SEL0       (* (reg8 *) normal_LED__PRTDSI__OUT_SEL0) 
#define normal_LED_PRTDSI__OUT_SEL1       (* (reg8 *) normal_LED__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define normal_LED_PRTDSI__SYNC_OUT       (* (reg8 *) normal_LED__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(normal_LED__SIO_CFG)
    #define normal_LED_SIO_HYST_EN        (* (reg8 *) normal_LED__SIO_HYST_EN)
    #define normal_LED_SIO_REG_HIFREQ     (* (reg8 *) normal_LED__SIO_REG_HIFREQ)
    #define normal_LED_SIO_CFG            (* (reg8 *) normal_LED__SIO_CFG)
    #define normal_LED_SIO_DIFF           (* (reg8 *) normal_LED__SIO_DIFF)
#endif /* (normal_LED__SIO_CFG) */

/* Interrupt Registers */
#if defined(normal_LED__INTSTAT)
    #define normal_LED_INTSTAT            (* (reg8 *) normal_LED__INTSTAT)
    #define normal_LED_SNAP               (* (reg8 *) normal_LED__SNAP)
    
	#define normal_LED_0_INTTYPE_REG 		(* (reg8 *) normal_LED__0__INTTYPE)
#endif /* (normal_LED__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_normal_LED_H */


/* [] END OF FILE */
