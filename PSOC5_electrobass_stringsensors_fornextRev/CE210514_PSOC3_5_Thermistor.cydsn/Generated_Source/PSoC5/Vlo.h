/*******************************************************************************
* File Name: Vlo.h  
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

#if !defined(CY_PINS_Vlo_H) /* Pins Vlo_H */
#define CY_PINS_Vlo_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vlo_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vlo__PORT == 15 && ((Vlo__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Vlo_Write(uint8 value);
void    Vlo_SetDriveMode(uint8 mode);
uint8   Vlo_ReadDataReg(void);
uint8   Vlo_Read(void);
void    Vlo_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vlo_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Vlo_SetDriveMode() function.
     *  @{
     */
        #define Vlo_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Vlo_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Vlo_DM_RES_UP          PIN_DM_RES_UP
        #define Vlo_DM_RES_DWN         PIN_DM_RES_DWN
        #define Vlo_DM_OD_LO           PIN_DM_OD_LO
        #define Vlo_DM_OD_HI           PIN_DM_OD_HI
        #define Vlo_DM_STRONG          PIN_DM_STRONG
        #define Vlo_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Vlo_MASK               Vlo__MASK
#define Vlo_SHIFT              Vlo__SHIFT
#define Vlo_WIDTH              1u

/* Interrupt constants */
#if defined(Vlo__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vlo_SetInterruptMode() function.
     *  @{
     */
        #define Vlo_INTR_NONE      (uint16)(0x0000u)
        #define Vlo_INTR_RISING    (uint16)(0x0001u)
        #define Vlo_INTR_FALLING   (uint16)(0x0002u)
        #define Vlo_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Vlo_INTR_MASK      (0x01u) 
#endif /* (Vlo__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vlo_PS                     (* (reg8 *) Vlo__PS)
/* Data Register */
#define Vlo_DR                     (* (reg8 *) Vlo__DR)
/* Port Number */
#define Vlo_PRT_NUM                (* (reg8 *) Vlo__PRT) 
/* Connect to Analog Globals */                                                  
#define Vlo_AG                     (* (reg8 *) Vlo__AG)                       
/* Analog MUX bux enable */
#define Vlo_AMUX                   (* (reg8 *) Vlo__AMUX) 
/* Bidirectional Enable */                                                        
#define Vlo_BIE                    (* (reg8 *) Vlo__BIE)
/* Bit-mask for Aliased Register Access */
#define Vlo_BIT_MASK               (* (reg8 *) Vlo__BIT_MASK)
/* Bypass Enable */
#define Vlo_BYP                    (* (reg8 *) Vlo__BYP)
/* Port wide control signals */                                                   
#define Vlo_CTL                    (* (reg8 *) Vlo__CTL)
/* Drive Modes */
#define Vlo_DM0                    (* (reg8 *) Vlo__DM0) 
#define Vlo_DM1                    (* (reg8 *) Vlo__DM1)
#define Vlo_DM2                    (* (reg8 *) Vlo__DM2) 
/* Input Buffer Disable Override */
#define Vlo_INP_DIS                (* (reg8 *) Vlo__INP_DIS)
/* LCD Common or Segment Drive */
#define Vlo_LCD_COM_SEG            (* (reg8 *) Vlo__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vlo_LCD_EN                 (* (reg8 *) Vlo__LCD_EN)
/* Slew Rate Control */
#define Vlo_SLW                    (* (reg8 *) Vlo__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vlo_PRTDSI__CAPS_SEL       (* (reg8 *) Vlo__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vlo_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vlo__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vlo_PRTDSI__OE_SEL0        (* (reg8 *) Vlo__PRTDSI__OE_SEL0) 
#define Vlo_PRTDSI__OE_SEL1        (* (reg8 *) Vlo__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vlo_PRTDSI__OUT_SEL0       (* (reg8 *) Vlo__PRTDSI__OUT_SEL0) 
#define Vlo_PRTDSI__OUT_SEL1       (* (reg8 *) Vlo__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vlo_PRTDSI__SYNC_OUT       (* (reg8 *) Vlo__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Vlo__SIO_CFG)
    #define Vlo_SIO_HYST_EN        (* (reg8 *) Vlo__SIO_HYST_EN)
    #define Vlo_SIO_REG_HIFREQ     (* (reg8 *) Vlo__SIO_REG_HIFREQ)
    #define Vlo_SIO_CFG            (* (reg8 *) Vlo__SIO_CFG)
    #define Vlo_SIO_DIFF           (* (reg8 *) Vlo__SIO_DIFF)
#endif /* (Vlo__SIO_CFG) */

/* Interrupt Registers */
#if defined(Vlo__INTSTAT)
    #define Vlo_INTSTAT            (* (reg8 *) Vlo__INTSTAT)
    #define Vlo_SNAP               (* (reg8 *) Vlo__SNAP)
    
	#define Vlo_0_INTTYPE_REG 		(* (reg8 *) Vlo__0__INTTYPE)
#endif /* (Vlo__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vlo_H */


/* [] END OF FILE */
