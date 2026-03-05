/*******************************************************************************
* File Name: Vlow1.h  
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

#if !defined(CY_PINS_Vlow1_H) /* Pins Vlow1_H */
#define CY_PINS_Vlow1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vlow1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vlow1__PORT == 15 && ((Vlow1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Vlow1_Write(uint8 value);
void    Vlow1_SetDriveMode(uint8 mode);
uint8   Vlow1_ReadDataReg(void);
uint8   Vlow1_Read(void);
void    Vlow1_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vlow1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Vlow1_SetDriveMode() function.
     *  @{
     */
        #define Vlow1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Vlow1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Vlow1_DM_RES_UP          PIN_DM_RES_UP
        #define Vlow1_DM_RES_DWN         PIN_DM_RES_DWN
        #define Vlow1_DM_OD_LO           PIN_DM_OD_LO
        #define Vlow1_DM_OD_HI           PIN_DM_OD_HI
        #define Vlow1_DM_STRONG          PIN_DM_STRONG
        #define Vlow1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Vlow1_MASK               Vlow1__MASK
#define Vlow1_SHIFT              Vlow1__SHIFT
#define Vlow1_WIDTH              1u

/* Interrupt constants */
#if defined(Vlow1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vlow1_SetInterruptMode() function.
     *  @{
     */
        #define Vlow1_INTR_NONE      (uint16)(0x0000u)
        #define Vlow1_INTR_RISING    (uint16)(0x0001u)
        #define Vlow1_INTR_FALLING   (uint16)(0x0002u)
        #define Vlow1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Vlow1_INTR_MASK      (0x01u) 
#endif /* (Vlow1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vlow1_PS                     (* (reg8 *) Vlow1__PS)
/* Data Register */
#define Vlow1_DR                     (* (reg8 *) Vlow1__DR)
/* Port Number */
#define Vlow1_PRT_NUM                (* (reg8 *) Vlow1__PRT) 
/* Connect to Analog Globals */                                                  
#define Vlow1_AG                     (* (reg8 *) Vlow1__AG)                       
/* Analog MUX bux enable */
#define Vlow1_AMUX                   (* (reg8 *) Vlow1__AMUX) 
/* Bidirectional Enable */                                                        
#define Vlow1_BIE                    (* (reg8 *) Vlow1__BIE)
/* Bit-mask for Aliased Register Access */
#define Vlow1_BIT_MASK               (* (reg8 *) Vlow1__BIT_MASK)
/* Bypass Enable */
#define Vlow1_BYP                    (* (reg8 *) Vlow1__BYP)
/* Port wide control signals */                                                   
#define Vlow1_CTL                    (* (reg8 *) Vlow1__CTL)
/* Drive Modes */
#define Vlow1_DM0                    (* (reg8 *) Vlow1__DM0) 
#define Vlow1_DM1                    (* (reg8 *) Vlow1__DM1)
#define Vlow1_DM2                    (* (reg8 *) Vlow1__DM2) 
/* Input Buffer Disable Override */
#define Vlow1_INP_DIS                (* (reg8 *) Vlow1__INP_DIS)
/* LCD Common or Segment Drive */
#define Vlow1_LCD_COM_SEG            (* (reg8 *) Vlow1__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vlow1_LCD_EN                 (* (reg8 *) Vlow1__LCD_EN)
/* Slew Rate Control */
#define Vlow1_SLW                    (* (reg8 *) Vlow1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vlow1_PRTDSI__CAPS_SEL       (* (reg8 *) Vlow1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vlow1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vlow1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vlow1_PRTDSI__OE_SEL0        (* (reg8 *) Vlow1__PRTDSI__OE_SEL0) 
#define Vlow1_PRTDSI__OE_SEL1        (* (reg8 *) Vlow1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vlow1_PRTDSI__OUT_SEL0       (* (reg8 *) Vlow1__PRTDSI__OUT_SEL0) 
#define Vlow1_PRTDSI__OUT_SEL1       (* (reg8 *) Vlow1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vlow1_PRTDSI__SYNC_OUT       (* (reg8 *) Vlow1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Vlow1__SIO_CFG)
    #define Vlow1_SIO_HYST_EN        (* (reg8 *) Vlow1__SIO_HYST_EN)
    #define Vlow1_SIO_REG_HIFREQ     (* (reg8 *) Vlow1__SIO_REG_HIFREQ)
    #define Vlow1_SIO_CFG            (* (reg8 *) Vlow1__SIO_CFG)
    #define Vlow1_SIO_DIFF           (* (reg8 *) Vlow1__SIO_DIFF)
#endif /* (Vlow1__SIO_CFG) */

/* Interrupt Registers */
#if defined(Vlow1__INTSTAT)
    #define Vlow1_INTSTAT            (* (reg8 *) Vlow1__INTSTAT)
    #define Vlow1_SNAP               (* (reg8 *) Vlow1__SNAP)
    
	#define Vlow1_0_INTTYPE_REG 		(* (reg8 *) Vlow1__0__INTTYPE)
#endif /* (Vlow1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vlow1_H */


/* [] END OF FILE */
