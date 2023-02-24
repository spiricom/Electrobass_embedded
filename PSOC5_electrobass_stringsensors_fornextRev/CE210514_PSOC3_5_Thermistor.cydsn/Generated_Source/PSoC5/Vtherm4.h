/*******************************************************************************
* File Name: Vtherm4.h  
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

#if !defined(CY_PINS_Vtherm4_H) /* Pins Vtherm4_H */
#define CY_PINS_Vtherm4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vtherm4_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vtherm4__PORT == 15 && ((Vtherm4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Vtherm4_Write(uint8 value);
void    Vtherm4_SetDriveMode(uint8 mode);
uint8   Vtherm4_ReadDataReg(void);
uint8   Vtherm4_Read(void);
void    Vtherm4_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vtherm4_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Vtherm4_SetDriveMode() function.
     *  @{
     */
        #define Vtherm4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Vtherm4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Vtherm4_DM_RES_UP          PIN_DM_RES_UP
        #define Vtherm4_DM_RES_DWN         PIN_DM_RES_DWN
        #define Vtherm4_DM_OD_LO           PIN_DM_OD_LO
        #define Vtherm4_DM_OD_HI           PIN_DM_OD_HI
        #define Vtherm4_DM_STRONG          PIN_DM_STRONG
        #define Vtherm4_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Vtherm4_MASK               Vtherm4__MASK
#define Vtherm4_SHIFT              Vtherm4__SHIFT
#define Vtherm4_WIDTH              1u

/* Interrupt constants */
#if defined(Vtherm4__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vtherm4_SetInterruptMode() function.
     *  @{
     */
        #define Vtherm4_INTR_NONE      (uint16)(0x0000u)
        #define Vtherm4_INTR_RISING    (uint16)(0x0001u)
        #define Vtherm4_INTR_FALLING   (uint16)(0x0002u)
        #define Vtherm4_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Vtherm4_INTR_MASK      (0x01u) 
#endif /* (Vtherm4__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vtherm4_PS                     (* (reg8 *) Vtherm4__PS)
/* Data Register */
#define Vtherm4_DR                     (* (reg8 *) Vtherm4__DR)
/* Port Number */
#define Vtherm4_PRT_NUM                (* (reg8 *) Vtherm4__PRT) 
/* Connect to Analog Globals */                                                  
#define Vtherm4_AG                     (* (reg8 *) Vtherm4__AG)                       
/* Analog MUX bux enable */
#define Vtherm4_AMUX                   (* (reg8 *) Vtherm4__AMUX) 
/* Bidirectional Enable */                                                        
#define Vtherm4_BIE                    (* (reg8 *) Vtherm4__BIE)
/* Bit-mask for Aliased Register Access */
#define Vtherm4_BIT_MASK               (* (reg8 *) Vtherm4__BIT_MASK)
/* Bypass Enable */
#define Vtherm4_BYP                    (* (reg8 *) Vtherm4__BYP)
/* Port wide control signals */                                                   
#define Vtherm4_CTL                    (* (reg8 *) Vtherm4__CTL)
/* Drive Modes */
#define Vtherm4_DM0                    (* (reg8 *) Vtherm4__DM0) 
#define Vtherm4_DM1                    (* (reg8 *) Vtherm4__DM1)
#define Vtherm4_DM2                    (* (reg8 *) Vtherm4__DM2) 
/* Input Buffer Disable Override */
#define Vtherm4_INP_DIS                (* (reg8 *) Vtherm4__INP_DIS)
/* LCD Common or Segment Drive */
#define Vtherm4_LCD_COM_SEG            (* (reg8 *) Vtherm4__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vtherm4_LCD_EN                 (* (reg8 *) Vtherm4__LCD_EN)
/* Slew Rate Control */
#define Vtherm4_SLW                    (* (reg8 *) Vtherm4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vtherm4_PRTDSI__CAPS_SEL       (* (reg8 *) Vtherm4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vtherm4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vtherm4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vtherm4_PRTDSI__OE_SEL0        (* (reg8 *) Vtherm4__PRTDSI__OE_SEL0) 
#define Vtherm4_PRTDSI__OE_SEL1        (* (reg8 *) Vtherm4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vtherm4_PRTDSI__OUT_SEL0       (* (reg8 *) Vtherm4__PRTDSI__OUT_SEL0) 
#define Vtherm4_PRTDSI__OUT_SEL1       (* (reg8 *) Vtherm4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vtherm4_PRTDSI__SYNC_OUT       (* (reg8 *) Vtherm4__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Vtherm4__SIO_CFG)
    #define Vtherm4_SIO_HYST_EN        (* (reg8 *) Vtherm4__SIO_HYST_EN)
    #define Vtherm4_SIO_REG_HIFREQ     (* (reg8 *) Vtherm4__SIO_REG_HIFREQ)
    #define Vtherm4_SIO_CFG            (* (reg8 *) Vtherm4__SIO_CFG)
    #define Vtherm4_SIO_DIFF           (* (reg8 *) Vtherm4__SIO_DIFF)
#endif /* (Vtherm4__SIO_CFG) */

/* Interrupt Registers */
#if defined(Vtherm4__INTSTAT)
    #define Vtherm4_INTSTAT            (* (reg8 *) Vtherm4__INTSTAT)
    #define Vtherm4_SNAP               (* (reg8 *) Vtherm4__SNAP)
    
	#define Vtherm4_0_INTTYPE_REG 		(* (reg8 *) Vtherm4__0__INTTYPE)
#endif /* (Vtherm4__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vtherm4_H */


/* [] END OF FILE */
