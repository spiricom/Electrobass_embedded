/*******************************************************************************
* File Name: Vtherm3.h  
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

#if !defined(CY_PINS_Vtherm3_H) /* Pins Vtherm3_H */
#define CY_PINS_Vtherm3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vtherm3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vtherm3__PORT == 15 && ((Vtherm3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Vtherm3_Write(uint8 value);
void    Vtherm3_SetDriveMode(uint8 mode);
uint8   Vtherm3_ReadDataReg(void);
uint8   Vtherm3_Read(void);
void    Vtherm3_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vtherm3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Vtherm3_SetDriveMode() function.
     *  @{
     */
        #define Vtherm3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Vtherm3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Vtherm3_DM_RES_UP          PIN_DM_RES_UP
        #define Vtherm3_DM_RES_DWN         PIN_DM_RES_DWN
        #define Vtherm3_DM_OD_LO           PIN_DM_OD_LO
        #define Vtherm3_DM_OD_HI           PIN_DM_OD_HI
        #define Vtherm3_DM_STRONG          PIN_DM_STRONG
        #define Vtherm3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Vtherm3_MASK               Vtherm3__MASK
#define Vtherm3_SHIFT              Vtherm3__SHIFT
#define Vtherm3_WIDTH              1u

/* Interrupt constants */
#if defined(Vtherm3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vtherm3_SetInterruptMode() function.
     *  @{
     */
        #define Vtherm3_INTR_NONE      (uint16)(0x0000u)
        #define Vtherm3_INTR_RISING    (uint16)(0x0001u)
        #define Vtherm3_INTR_FALLING   (uint16)(0x0002u)
        #define Vtherm3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Vtherm3_INTR_MASK      (0x01u) 
#endif /* (Vtherm3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vtherm3_PS                     (* (reg8 *) Vtherm3__PS)
/* Data Register */
#define Vtherm3_DR                     (* (reg8 *) Vtherm3__DR)
/* Port Number */
#define Vtherm3_PRT_NUM                (* (reg8 *) Vtherm3__PRT) 
/* Connect to Analog Globals */                                                  
#define Vtherm3_AG                     (* (reg8 *) Vtherm3__AG)                       
/* Analog MUX bux enable */
#define Vtherm3_AMUX                   (* (reg8 *) Vtherm3__AMUX) 
/* Bidirectional Enable */                                                        
#define Vtherm3_BIE                    (* (reg8 *) Vtherm3__BIE)
/* Bit-mask for Aliased Register Access */
#define Vtherm3_BIT_MASK               (* (reg8 *) Vtherm3__BIT_MASK)
/* Bypass Enable */
#define Vtherm3_BYP                    (* (reg8 *) Vtherm3__BYP)
/* Port wide control signals */                                                   
#define Vtherm3_CTL                    (* (reg8 *) Vtherm3__CTL)
/* Drive Modes */
#define Vtherm3_DM0                    (* (reg8 *) Vtherm3__DM0) 
#define Vtherm3_DM1                    (* (reg8 *) Vtherm3__DM1)
#define Vtherm3_DM2                    (* (reg8 *) Vtherm3__DM2) 
/* Input Buffer Disable Override */
#define Vtherm3_INP_DIS                (* (reg8 *) Vtherm3__INP_DIS)
/* LCD Common or Segment Drive */
#define Vtherm3_LCD_COM_SEG            (* (reg8 *) Vtherm3__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vtherm3_LCD_EN                 (* (reg8 *) Vtherm3__LCD_EN)
/* Slew Rate Control */
#define Vtherm3_SLW                    (* (reg8 *) Vtherm3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vtherm3_PRTDSI__CAPS_SEL       (* (reg8 *) Vtherm3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vtherm3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vtherm3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vtherm3_PRTDSI__OE_SEL0        (* (reg8 *) Vtherm3__PRTDSI__OE_SEL0) 
#define Vtherm3_PRTDSI__OE_SEL1        (* (reg8 *) Vtherm3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vtherm3_PRTDSI__OUT_SEL0       (* (reg8 *) Vtherm3__PRTDSI__OUT_SEL0) 
#define Vtherm3_PRTDSI__OUT_SEL1       (* (reg8 *) Vtherm3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vtherm3_PRTDSI__SYNC_OUT       (* (reg8 *) Vtherm3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Vtherm3__SIO_CFG)
    #define Vtherm3_SIO_HYST_EN        (* (reg8 *) Vtherm3__SIO_HYST_EN)
    #define Vtherm3_SIO_REG_HIFREQ     (* (reg8 *) Vtherm3__SIO_REG_HIFREQ)
    #define Vtherm3_SIO_CFG            (* (reg8 *) Vtherm3__SIO_CFG)
    #define Vtherm3_SIO_DIFF           (* (reg8 *) Vtherm3__SIO_DIFF)
#endif /* (Vtherm3__SIO_CFG) */

/* Interrupt Registers */
#if defined(Vtherm3__INTSTAT)
    #define Vtherm3_INTSTAT            (* (reg8 *) Vtherm3__INTSTAT)
    #define Vtherm3_SNAP               (* (reg8 *) Vtherm3__SNAP)
    
	#define Vtherm3_0_INTTYPE_REG 		(* (reg8 *) Vtherm3__0__INTTYPE)
#endif /* (Vtherm3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vtherm3_H */


/* [] END OF FILE */
