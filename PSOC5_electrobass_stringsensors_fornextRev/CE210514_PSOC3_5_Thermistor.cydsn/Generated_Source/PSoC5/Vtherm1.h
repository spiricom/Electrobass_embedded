/*******************************************************************************
* File Name: Vtherm1.h  
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

#if !defined(CY_PINS_Vtherm1_H) /* Pins Vtherm1_H */
#define CY_PINS_Vtherm1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vtherm1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vtherm1__PORT == 15 && ((Vtherm1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Vtherm1_Write(uint8 value);
void    Vtherm1_SetDriveMode(uint8 mode);
uint8   Vtherm1_ReadDataReg(void);
uint8   Vtherm1_Read(void);
void    Vtherm1_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vtherm1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Vtherm1_SetDriveMode() function.
     *  @{
     */
        #define Vtherm1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Vtherm1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Vtherm1_DM_RES_UP          PIN_DM_RES_UP
        #define Vtherm1_DM_RES_DWN         PIN_DM_RES_DWN
        #define Vtherm1_DM_OD_LO           PIN_DM_OD_LO
        #define Vtherm1_DM_OD_HI           PIN_DM_OD_HI
        #define Vtherm1_DM_STRONG          PIN_DM_STRONG
        #define Vtherm1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Vtherm1_MASK               Vtherm1__MASK
#define Vtherm1_SHIFT              Vtherm1__SHIFT
#define Vtherm1_WIDTH              1u

/* Interrupt constants */
#if defined(Vtherm1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vtherm1_SetInterruptMode() function.
     *  @{
     */
        #define Vtherm1_INTR_NONE      (uint16)(0x0000u)
        #define Vtherm1_INTR_RISING    (uint16)(0x0001u)
        #define Vtherm1_INTR_FALLING   (uint16)(0x0002u)
        #define Vtherm1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Vtherm1_INTR_MASK      (0x01u) 
#endif /* (Vtherm1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vtherm1_PS                     (* (reg8 *) Vtherm1__PS)
/* Data Register */
#define Vtherm1_DR                     (* (reg8 *) Vtherm1__DR)
/* Port Number */
#define Vtherm1_PRT_NUM                (* (reg8 *) Vtherm1__PRT) 
/* Connect to Analog Globals */                                                  
#define Vtherm1_AG                     (* (reg8 *) Vtherm1__AG)                       
/* Analog MUX bux enable */
#define Vtherm1_AMUX                   (* (reg8 *) Vtherm1__AMUX) 
/* Bidirectional Enable */                                                        
#define Vtherm1_BIE                    (* (reg8 *) Vtherm1__BIE)
/* Bit-mask for Aliased Register Access */
#define Vtherm1_BIT_MASK               (* (reg8 *) Vtherm1__BIT_MASK)
/* Bypass Enable */
#define Vtherm1_BYP                    (* (reg8 *) Vtherm1__BYP)
/* Port wide control signals */                                                   
#define Vtherm1_CTL                    (* (reg8 *) Vtherm1__CTL)
/* Drive Modes */
#define Vtherm1_DM0                    (* (reg8 *) Vtherm1__DM0) 
#define Vtherm1_DM1                    (* (reg8 *) Vtherm1__DM1)
#define Vtherm1_DM2                    (* (reg8 *) Vtherm1__DM2) 
/* Input Buffer Disable Override */
#define Vtherm1_INP_DIS                (* (reg8 *) Vtherm1__INP_DIS)
/* LCD Common or Segment Drive */
#define Vtherm1_LCD_COM_SEG            (* (reg8 *) Vtherm1__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vtherm1_LCD_EN                 (* (reg8 *) Vtherm1__LCD_EN)
/* Slew Rate Control */
#define Vtherm1_SLW                    (* (reg8 *) Vtherm1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vtherm1_PRTDSI__CAPS_SEL       (* (reg8 *) Vtherm1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vtherm1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vtherm1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vtherm1_PRTDSI__OE_SEL0        (* (reg8 *) Vtherm1__PRTDSI__OE_SEL0) 
#define Vtherm1_PRTDSI__OE_SEL1        (* (reg8 *) Vtherm1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vtherm1_PRTDSI__OUT_SEL0       (* (reg8 *) Vtherm1__PRTDSI__OUT_SEL0) 
#define Vtherm1_PRTDSI__OUT_SEL1       (* (reg8 *) Vtherm1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vtherm1_PRTDSI__SYNC_OUT       (* (reg8 *) Vtherm1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Vtherm1__SIO_CFG)
    #define Vtherm1_SIO_HYST_EN        (* (reg8 *) Vtherm1__SIO_HYST_EN)
    #define Vtherm1_SIO_REG_HIFREQ     (* (reg8 *) Vtherm1__SIO_REG_HIFREQ)
    #define Vtherm1_SIO_CFG            (* (reg8 *) Vtherm1__SIO_CFG)
    #define Vtherm1_SIO_DIFF           (* (reg8 *) Vtherm1__SIO_DIFF)
#endif /* (Vtherm1__SIO_CFG) */

/* Interrupt Registers */
#if defined(Vtherm1__INTSTAT)
    #define Vtherm1_INTSTAT            (* (reg8 *) Vtherm1__INTSTAT)
    #define Vtherm1_SNAP               (* (reg8 *) Vtherm1__SNAP)
    
	#define Vtherm1_0_INTTYPE_REG 		(* (reg8 *) Vtherm1__0__INTTYPE)
#endif /* (Vtherm1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vtherm1_H */


/* [] END OF FILE */
