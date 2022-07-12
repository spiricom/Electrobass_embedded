/*******************************************************************************
* File Name: otonal.h  
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

#if !defined(CY_PINS_otonal_H) /* Pins otonal_H */
#define CY_PINS_otonal_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "otonal_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 otonal__PORT == 15 && ((otonal__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    otonal_Write(uint8 value);
void    otonal_SetDriveMode(uint8 mode);
uint8   otonal_ReadDataReg(void);
uint8   otonal_Read(void);
void    otonal_SetInterruptMode(uint16 position, uint16 mode);
uint8   otonal_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the otonal_SetDriveMode() function.
     *  @{
     */
        #define otonal_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define otonal_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define otonal_DM_RES_UP          PIN_DM_RES_UP
        #define otonal_DM_RES_DWN         PIN_DM_RES_DWN
        #define otonal_DM_OD_LO           PIN_DM_OD_LO
        #define otonal_DM_OD_HI           PIN_DM_OD_HI
        #define otonal_DM_STRONG          PIN_DM_STRONG
        #define otonal_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define otonal_MASK               otonal__MASK
#define otonal_SHIFT              otonal__SHIFT
#define otonal_WIDTH              1u

/* Interrupt constants */
#if defined(otonal__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in otonal_SetInterruptMode() function.
     *  @{
     */
        #define otonal_INTR_NONE      (uint16)(0x0000u)
        #define otonal_INTR_RISING    (uint16)(0x0001u)
        #define otonal_INTR_FALLING   (uint16)(0x0002u)
        #define otonal_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define otonal_INTR_MASK      (0x01u) 
#endif /* (otonal__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define otonal_PS                     (* (reg8 *) otonal__PS)
/* Data Register */
#define otonal_DR                     (* (reg8 *) otonal__DR)
/* Port Number */
#define otonal_PRT_NUM                (* (reg8 *) otonal__PRT) 
/* Connect to Analog Globals */                                                  
#define otonal_AG                     (* (reg8 *) otonal__AG)                       
/* Analog MUX bux enable */
#define otonal_AMUX                   (* (reg8 *) otonal__AMUX) 
/* Bidirectional Enable */                                                        
#define otonal_BIE                    (* (reg8 *) otonal__BIE)
/* Bit-mask for Aliased Register Access */
#define otonal_BIT_MASK               (* (reg8 *) otonal__BIT_MASK)
/* Bypass Enable */
#define otonal_BYP                    (* (reg8 *) otonal__BYP)
/* Port wide control signals */                                                   
#define otonal_CTL                    (* (reg8 *) otonal__CTL)
/* Drive Modes */
#define otonal_DM0                    (* (reg8 *) otonal__DM0) 
#define otonal_DM1                    (* (reg8 *) otonal__DM1)
#define otonal_DM2                    (* (reg8 *) otonal__DM2) 
/* Input Buffer Disable Override */
#define otonal_INP_DIS                (* (reg8 *) otonal__INP_DIS)
/* LCD Common or Segment Drive */
#define otonal_LCD_COM_SEG            (* (reg8 *) otonal__LCD_COM_SEG)
/* Enable Segment LCD */
#define otonal_LCD_EN                 (* (reg8 *) otonal__LCD_EN)
/* Slew Rate Control */
#define otonal_SLW                    (* (reg8 *) otonal__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define otonal_PRTDSI__CAPS_SEL       (* (reg8 *) otonal__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define otonal_PRTDSI__DBL_SYNC_IN    (* (reg8 *) otonal__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define otonal_PRTDSI__OE_SEL0        (* (reg8 *) otonal__PRTDSI__OE_SEL0) 
#define otonal_PRTDSI__OE_SEL1        (* (reg8 *) otonal__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define otonal_PRTDSI__OUT_SEL0       (* (reg8 *) otonal__PRTDSI__OUT_SEL0) 
#define otonal_PRTDSI__OUT_SEL1       (* (reg8 *) otonal__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define otonal_PRTDSI__SYNC_OUT       (* (reg8 *) otonal__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(otonal__SIO_CFG)
    #define otonal_SIO_HYST_EN        (* (reg8 *) otonal__SIO_HYST_EN)
    #define otonal_SIO_REG_HIFREQ     (* (reg8 *) otonal__SIO_REG_HIFREQ)
    #define otonal_SIO_CFG            (* (reg8 *) otonal__SIO_CFG)
    #define otonal_SIO_DIFF           (* (reg8 *) otonal__SIO_DIFF)
#endif /* (otonal__SIO_CFG) */

/* Interrupt Registers */
#if defined(otonal__INTSTAT)
    #define otonal_INTSTAT            (* (reg8 *) otonal__INTSTAT)
    #define otonal_SNAP               (* (reg8 *) otonal__SNAP)
    
	#define otonal_0_INTTYPE_REG 		(* (reg8 *) otonal__0__INTTYPE)
#endif /* (otonal__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_otonal_H */


/* [] END OF FILE */
