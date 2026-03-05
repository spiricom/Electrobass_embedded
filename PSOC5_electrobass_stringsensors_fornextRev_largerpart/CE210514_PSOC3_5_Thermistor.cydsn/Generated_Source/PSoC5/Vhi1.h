/*******************************************************************************
* File Name: Vhi1.h  
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

#if !defined(CY_PINS_Vhi1_H) /* Pins Vhi1_H */
#define CY_PINS_Vhi1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vhi1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vhi1__PORT == 15 && ((Vhi1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Vhi1_Write(uint8 value);
void    Vhi1_SetDriveMode(uint8 mode);
uint8   Vhi1_ReadDataReg(void);
uint8   Vhi1_Read(void);
void    Vhi1_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vhi1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Vhi1_SetDriveMode() function.
     *  @{
     */
        #define Vhi1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Vhi1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Vhi1_DM_RES_UP          PIN_DM_RES_UP
        #define Vhi1_DM_RES_DWN         PIN_DM_RES_DWN
        #define Vhi1_DM_OD_LO           PIN_DM_OD_LO
        #define Vhi1_DM_OD_HI           PIN_DM_OD_HI
        #define Vhi1_DM_STRONG          PIN_DM_STRONG
        #define Vhi1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Vhi1_MASK               Vhi1__MASK
#define Vhi1_SHIFT              Vhi1__SHIFT
#define Vhi1_WIDTH              1u

/* Interrupt constants */
#if defined(Vhi1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vhi1_SetInterruptMode() function.
     *  @{
     */
        #define Vhi1_INTR_NONE      (uint16)(0x0000u)
        #define Vhi1_INTR_RISING    (uint16)(0x0001u)
        #define Vhi1_INTR_FALLING   (uint16)(0x0002u)
        #define Vhi1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Vhi1_INTR_MASK      (0x01u) 
#endif /* (Vhi1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vhi1_PS                     (* (reg8 *) Vhi1__PS)
/* Data Register */
#define Vhi1_DR                     (* (reg8 *) Vhi1__DR)
/* Port Number */
#define Vhi1_PRT_NUM                (* (reg8 *) Vhi1__PRT) 
/* Connect to Analog Globals */                                                  
#define Vhi1_AG                     (* (reg8 *) Vhi1__AG)                       
/* Analog MUX bux enable */
#define Vhi1_AMUX                   (* (reg8 *) Vhi1__AMUX) 
/* Bidirectional Enable */                                                        
#define Vhi1_BIE                    (* (reg8 *) Vhi1__BIE)
/* Bit-mask for Aliased Register Access */
#define Vhi1_BIT_MASK               (* (reg8 *) Vhi1__BIT_MASK)
/* Bypass Enable */
#define Vhi1_BYP                    (* (reg8 *) Vhi1__BYP)
/* Port wide control signals */                                                   
#define Vhi1_CTL                    (* (reg8 *) Vhi1__CTL)
/* Drive Modes */
#define Vhi1_DM0                    (* (reg8 *) Vhi1__DM0) 
#define Vhi1_DM1                    (* (reg8 *) Vhi1__DM1)
#define Vhi1_DM2                    (* (reg8 *) Vhi1__DM2) 
/* Input Buffer Disable Override */
#define Vhi1_INP_DIS                (* (reg8 *) Vhi1__INP_DIS)
/* LCD Common or Segment Drive */
#define Vhi1_LCD_COM_SEG            (* (reg8 *) Vhi1__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vhi1_LCD_EN                 (* (reg8 *) Vhi1__LCD_EN)
/* Slew Rate Control */
#define Vhi1_SLW                    (* (reg8 *) Vhi1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vhi1_PRTDSI__CAPS_SEL       (* (reg8 *) Vhi1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vhi1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vhi1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vhi1_PRTDSI__OE_SEL0        (* (reg8 *) Vhi1__PRTDSI__OE_SEL0) 
#define Vhi1_PRTDSI__OE_SEL1        (* (reg8 *) Vhi1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vhi1_PRTDSI__OUT_SEL0       (* (reg8 *) Vhi1__PRTDSI__OUT_SEL0) 
#define Vhi1_PRTDSI__OUT_SEL1       (* (reg8 *) Vhi1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vhi1_PRTDSI__SYNC_OUT       (* (reg8 *) Vhi1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Vhi1__SIO_CFG)
    #define Vhi1_SIO_HYST_EN        (* (reg8 *) Vhi1__SIO_HYST_EN)
    #define Vhi1_SIO_REG_HIFREQ     (* (reg8 *) Vhi1__SIO_REG_HIFREQ)
    #define Vhi1_SIO_CFG            (* (reg8 *) Vhi1__SIO_CFG)
    #define Vhi1_SIO_DIFF           (* (reg8 *) Vhi1__SIO_DIFF)
#endif /* (Vhi1__SIO_CFG) */

/* Interrupt Registers */
#if defined(Vhi1__INTSTAT)
    #define Vhi1_INTSTAT            (* (reg8 *) Vhi1__INTSTAT)
    #define Vhi1_SNAP               (* (reg8 *) Vhi1__SNAP)
    
	#define Vhi1_0_INTTYPE_REG 		(* (reg8 *) Vhi1__0__INTTYPE)
#endif /* (Vhi1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vhi1_H */


/* [] END OF FILE */
