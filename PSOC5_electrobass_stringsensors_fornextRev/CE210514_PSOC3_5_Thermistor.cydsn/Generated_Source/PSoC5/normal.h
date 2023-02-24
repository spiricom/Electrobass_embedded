/*******************************************************************************
* File Name: normal.h  
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

#if !defined(CY_PINS_normal_H) /* Pins normal_H */
#define CY_PINS_normal_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "normal_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 normal__PORT == 15 && ((normal__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    normal_Write(uint8 value);
void    normal_SetDriveMode(uint8 mode);
uint8   normal_ReadDataReg(void);
uint8   normal_Read(void);
void    normal_SetInterruptMode(uint16 position, uint16 mode);
uint8   normal_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the normal_SetDriveMode() function.
     *  @{
     */
        #define normal_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define normal_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define normal_DM_RES_UP          PIN_DM_RES_UP
        #define normal_DM_RES_DWN         PIN_DM_RES_DWN
        #define normal_DM_OD_LO           PIN_DM_OD_LO
        #define normal_DM_OD_HI           PIN_DM_OD_HI
        #define normal_DM_STRONG          PIN_DM_STRONG
        #define normal_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define normal_MASK               normal__MASK
#define normal_SHIFT              normal__SHIFT
#define normal_WIDTH              1u

/* Interrupt constants */
#if defined(normal__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in normal_SetInterruptMode() function.
     *  @{
     */
        #define normal_INTR_NONE      (uint16)(0x0000u)
        #define normal_INTR_RISING    (uint16)(0x0001u)
        #define normal_INTR_FALLING   (uint16)(0x0002u)
        #define normal_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define normal_INTR_MASK      (0x01u) 
#endif /* (normal__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define normal_PS                     (* (reg8 *) normal__PS)
/* Data Register */
#define normal_DR                     (* (reg8 *) normal__DR)
/* Port Number */
#define normal_PRT_NUM                (* (reg8 *) normal__PRT) 
/* Connect to Analog Globals */                                                  
#define normal_AG                     (* (reg8 *) normal__AG)                       
/* Analog MUX bux enable */
#define normal_AMUX                   (* (reg8 *) normal__AMUX) 
/* Bidirectional Enable */                                                        
#define normal_BIE                    (* (reg8 *) normal__BIE)
/* Bit-mask for Aliased Register Access */
#define normal_BIT_MASK               (* (reg8 *) normal__BIT_MASK)
/* Bypass Enable */
#define normal_BYP                    (* (reg8 *) normal__BYP)
/* Port wide control signals */                                                   
#define normal_CTL                    (* (reg8 *) normal__CTL)
/* Drive Modes */
#define normal_DM0                    (* (reg8 *) normal__DM0) 
#define normal_DM1                    (* (reg8 *) normal__DM1)
#define normal_DM2                    (* (reg8 *) normal__DM2) 
/* Input Buffer Disable Override */
#define normal_INP_DIS                (* (reg8 *) normal__INP_DIS)
/* LCD Common or Segment Drive */
#define normal_LCD_COM_SEG            (* (reg8 *) normal__LCD_COM_SEG)
/* Enable Segment LCD */
#define normal_LCD_EN                 (* (reg8 *) normal__LCD_EN)
/* Slew Rate Control */
#define normal_SLW                    (* (reg8 *) normal__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define normal_PRTDSI__CAPS_SEL       (* (reg8 *) normal__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define normal_PRTDSI__DBL_SYNC_IN    (* (reg8 *) normal__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define normal_PRTDSI__OE_SEL0        (* (reg8 *) normal__PRTDSI__OE_SEL0) 
#define normal_PRTDSI__OE_SEL1        (* (reg8 *) normal__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define normal_PRTDSI__OUT_SEL0       (* (reg8 *) normal__PRTDSI__OUT_SEL0) 
#define normal_PRTDSI__OUT_SEL1       (* (reg8 *) normal__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define normal_PRTDSI__SYNC_OUT       (* (reg8 *) normal__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(normal__SIO_CFG)
    #define normal_SIO_HYST_EN        (* (reg8 *) normal__SIO_HYST_EN)
    #define normal_SIO_REG_HIFREQ     (* (reg8 *) normal__SIO_REG_HIFREQ)
    #define normal_SIO_CFG            (* (reg8 *) normal__SIO_CFG)
    #define normal_SIO_DIFF           (* (reg8 *) normal__SIO_DIFF)
#endif /* (normal__SIO_CFG) */

/* Interrupt Registers */
#if defined(normal__INTSTAT)
    #define normal_INTSTAT            (* (reg8 *) normal__INTSTAT)
    #define normal_SNAP               (* (reg8 *) normal__SNAP)
    
	#define normal_0_INTTYPE_REG 		(* (reg8 *) normal__0__INTTYPE)
#endif /* (normal__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_normal_H */


/* [] END OF FILE */
