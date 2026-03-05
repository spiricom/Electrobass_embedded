/*******************************************************************************
* File Name: Vlow3.h  
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

#if !defined(CY_PINS_Vlow3_H) /* Pins Vlow3_H */
#define CY_PINS_Vlow3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vlow3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vlow3__PORT == 15 && ((Vlow3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Vlow3_Write(uint8 value);
void    Vlow3_SetDriveMode(uint8 mode);
uint8   Vlow3_ReadDataReg(void);
uint8   Vlow3_Read(void);
void    Vlow3_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vlow3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Vlow3_SetDriveMode() function.
     *  @{
     */
        #define Vlow3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Vlow3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Vlow3_DM_RES_UP          PIN_DM_RES_UP
        #define Vlow3_DM_RES_DWN         PIN_DM_RES_DWN
        #define Vlow3_DM_OD_LO           PIN_DM_OD_LO
        #define Vlow3_DM_OD_HI           PIN_DM_OD_HI
        #define Vlow3_DM_STRONG          PIN_DM_STRONG
        #define Vlow3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Vlow3_MASK               Vlow3__MASK
#define Vlow3_SHIFT              Vlow3__SHIFT
#define Vlow3_WIDTH              1u

/* Interrupt constants */
#if defined(Vlow3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vlow3_SetInterruptMode() function.
     *  @{
     */
        #define Vlow3_INTR_NONE      (uint16)(0x0000u)
        #define Vlow3_INTR_RISING    (uint16)(0x0001u)
        #define Vlow3_INTR_FALLING   (uint16)(0x0002u)
        #define Vlow3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Vlow3_INTR_MASK      (0x01u) 
#endif /* (Vlow3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vlow3_PS                     (* (reg8 *) Vlow3__PS)
/* Data Register */
#define Vlow3_DR                     (* (reg8 *) Vlow3__DR)
/* Port Number */
#define Vlow3_PRT_NUM                (* (reg8 *) Vlow3__PRT) 
/* Connect to Analog Globals */                                                  
#define Vlow3_AG                     (* (reg8 *) Vlow3__AG)                       
/* Analog MUX bux enable */
#define Vlow3_AMUX                   (* (reg8 *) Vlow3__AMUX) 
/* Bidirectional Enable */                                                        
#define Vlow3_BIE                    (* (reg8 *) Vlow3__BIE)
/* Bit-mask for Aliased Register Access */
#define Vlow3_BIT_MASK               (* (reg8 *) Vlow3__BIT_MASK)
/* Bypass Enable */
#define Vlow3_BYP                    (* (reg8 *) Vlow3__BYP)
/* Port wide control signals */                                                   
#define Vlow3_CTL                    (* (reg8 *) Vlow3__CTL)
/* Drive Modes */
#define Vlow3_DM0                    (* (reg8 *) Vlow3__DM0) 
#define Vlow3_DM1                    (* (reg8 *) Vlow3__DM1)
#define Vlow3_DM2                    (* (reg8 *) Vlow3__DM2) 
/* Input Buffer Disable Override */
#define Vlow3_INP_DIS                (* (reg8 *) Vlow3__INP_DIS)
/* LCD Common or Segment Drive */
#define Vlow3_LCD_COM_SEG            (* (reg8 *) Vlow3__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vlow3_LCD_EN                 (* (reg8 *) Vlow3__LCD_EN)
/* Slew Rate Control */
#define Vlow3_SLW                    (* (reg8 *) Vlow3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vlow3_PRTDSI__CAPS_SEL       (* (reg8 *) Vlow3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vlow3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vlow3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vlow3_PRTDSI__OE_SEL0        (* (reg8 *) Vlow3__PRTDSI__OE_SEL0) 
#define Vlow3_PRTDSI__OE_SEL1        (* (reg8 *) Vlow3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vlow3_PRTDSI__OUT_SEL0       (* (reg8 *) Vlow3__PRTDSI__OUT_SEL0) 
#define Vlow3_PRTDSI__OUT_SEL1       (* (reg8 *) Vlow3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vlow3_PRTDSI__SYNC_OUT       (* (reg8 *) Vlow3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Vlow3__SIO_CFG)
    #define Vlow3_SIO_HYST_EN        (* (reg8 *) Vlow3__SIO_HYST_EN)
    #define Vlow3_SIO_REG_HIFREQ     (* (reg8 *) Vlow3__SIO_REG_HIFREQ)
    #define Vlow3_SIO_CFG            (* (reg8 *) Vlow3__SIO_CFG)
    #define Vlow3_SIO_DIFF           (* (reg8 *) Vlow3__SIO_DIFF)
#endif /* (Vlow3__SIO_CFG) */

/* Interrupt Registers */
#if defined(Vlow3__INTSTAT)
    #define Vlow3_INTSTAT            (* (reg8 *) Vlow3__INTSTAT)
    #define Vlow3_SNAP               (* (reg8 *) Vlow3__SNAP)
    
	#define Vlow3_0_INTTYPE_REG 		(* (reg8 *) Vlow3__0__INTTYPE)
#endif /* (Vlow3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vlow3_H */


/* [] END OF FILE */
