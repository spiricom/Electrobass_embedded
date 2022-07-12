/*******************************************************************************
* File Name: Vlo2.h  
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

#if !defined(CY_PINS_Vlo2_H) /* Pins Vlo2_H */
#define CY_PINS_Vlo2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vlo2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vlo2__PORT == 15 && ((Vlo2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Vlo2_Write(uint8 value);
void    Vlo2_SetDriveMode(uint8 mode);
uint8   Vlo2_ReadDataReg(void);
uint8   Vlo2_Read(void);
void    Vlo2_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vlo2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Vlo2_SetDriveMode() function.
     *  @{
     */
        #define Vlo2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Vlo2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Vlo2_DM_RES_UP          PIN_DM_RES_UP
        #define Vlo2_DM_RES_DWN         PIN_DM_RES_DWN
        #define Vlo2_DM_OD_LO           PIN_DM_OD_LO
        #define Vlo2_DM_OD_HI           PIN_DM_OD_HI
        #define Vlo2_DM_STRONG          PIN_DM_STRONG
        #define Vlo2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Vlo2_MASK               Vlo2__MASK
#define Vlo2_SHIFT              Vlo2__SHIFT
#define Vlo2_WIDTH              1u

/* Interrupt constants */
#if defined(Vlo2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vlo2_SetInterruptMode() function.
     *  @{
     */
        #define Vlo2_INTR_NONE      (uint16)(0x0000u)
        #define Vlo2_INTR_RISING    (uint16)(0x0001u)
        #define Vlo2_INTR_FALLING   (uint16)(0x0002u)
        #define Vlo2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Vlo2_INTR_MASK      (0x01u) 
#endif /* (Vlo2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vlo2_PS                     (* (reg8 *) Vlo2__PS)
/* Data Register */
#define Vlo2_DR                     (* (reg8 *) Vlo2__DR)
/* Port Number */
#define Vlo2_PRT_NUM                (* (reg8 *) Vlo2__PRT) 
/* Connect to Analog Globals */                                                  
#define Vlo2_AG                     (* (reg8 *) Vlo2__AG)                       
/* Analog MUX bux enable */
#define Vlo2_AMUX                   (* (reg8 *) Vlo2__AMUX) 
/* Bidirectional Enable */                                                        
#define Vlo2_BIE                    (* (reg8 *) Vlo2__BIE)
/* Bit-mask for Aliased Register Access */
#define Vlo2_BIT_MASK               (* (reg8 *) Vlo2__BIT_MASK)
/* Bypass Enable */
#define Vlo2_BYP                    (* (reg8 *) Vlo2__BYP)
/* Port wide control signals */                                                   
#define Vlo2_CTL                    (* (reg8 *) Vlo2__CTL)
/* Drive Modes */
#define Vlo2_DM0                    (* (reg8 *) Vlo2__DM0) 
#define Vlo2_DM1                    (* (reg8 *) Vlo2__DM1)
#define Vlo2_DM2                    (* (reg8 *) Vlo2__DM2) 
/* Input Buffer Disable Override */
#define Vlo2_INP_DIS                (* (reg8 *) Vlo2__INP_DIS)
/* LCD Common or Segment Drive */
#define Vlo2_LCD_COM_SEG            (* (reg8 *) Vlo2__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vlo2_LCD_EN                 (* (reg8 *) Vlo2__LCD_EN)
/* Slew Rate Control */
#define Vlo2_SLW                    (* (reg8 *) Vlo2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vlo2_PRTDSI__CAPS_SEL       (* (reg8 *) Vlo2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vlo2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vlo2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vlo2_PRTDSI__OE_SEL0        (* (reg8 *) Vlo2__PRTDSI__OE_SEL0) 
#define Vlo2_PRTDSI__OE_SEL1        (* (reg8 *) Vlo2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vlo2_PRTDSI__OUT_SEL0       (* (reg8 *) Vlo2__PRTDSI__OUT_SEL0) 
#define Vlo2_PRTDSI__OUT_SEL1       (* (reg8 *) Vlo2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vlo2_PRTDSI__SYNC_OUT       (* (reg8 *) Vlo2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Vlo2__SIO_CFG)
    #define Vlo2_SIO_HYST_EN        (* (reg8 *) Vlo2__SIO_HYST_EN)
    #define Vlo2_SIO_REG_HIFREQ     (* (reg8 *) Vlo2__SIO_REG_HIFREQ)
    #define Vlo2_SIO_CFG            (* (reg8 *) Vlo2__SIO_CFG)
    #define Vlo2_SIO_DIFF           (* (reg8 *) Vlo2__SIO_DIFF)
#endif /* (Vlo2__SIO_CFG) */

/* Interrupt Registers */
#if defined(Vlo2__INTSTAT)
    #define Vlo2_INTSTAT            (* (reg8 *) Vlo2__INTSTAT)
    #define Vlo2_SNAP               (* (reg8 *) Vlo2__SNAP)
    
	#define Vlo2_0_INTTYPE_REG 		(* (reg8 *) Vlo2__0__INTTYPE)
#endif /* (Vlo2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vlo2_H */


/* [] END OF FILE */
