/*******************************************************************************
* File Name: Vhi.h  
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

#if !defined(CY_PINS_Vhi_H) /* Pins Vhi_H */
#define CY_PINS_Vhi_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vhi_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vhi__PORT == 15 && ((Vhi__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Vhi_Write(uint8 value);
void    Vhi_SetDriveMode(uint8 mode);
uint8   Vhi_ReadDataReg(void);
uint8   Vhi_Read(void);
void    Vhi_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vhi_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Vhi_SetDriveMode() function.
     *  @{
     */
        #define Vhi_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Vhi_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Vhi_DM_RES_UP          PIN_DM_RES_UP
        #define Vhi_DM_RES_DWN         PIN_DM_RES_DWN
        #define Vhi_DM_OD_LO           PIN_DM_OD_LO
        #define Vhi_DM_OD_HI           PIN_DM_OD_HI
        #define Vhi_DM_STRONG          PIN_DM_STRONG
        #define Vhi_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Vhi_MASK               Vhi__MASK
#define Vhi_SHIFT              Vhi__SHIFT
#define Vhi_WIDTH              1u

/* Interrupt constants */
#if defined(Vhi__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vhi_SetInterruptMode() function.
     *  @{
     */
        #define Vhi_INTR_NONE      (uint16)(0x0000u)
        #define Vhi_INTR_RISING    (uint16)(0x0001u)
        #define Vhi_INTR_FALLING   (uint16)(0x0002u)
        #define Vhi_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Vhi_INTR_MASK      (0x01u) 
#endif /* (Vhi__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vhi_PS                     (* (reg8 *) Vhi__PS)
/* Data Register */
#define Vhi_DR                     (* (reg8 *) Vhi__DR)
/* Port Number */
#define Vhi_PRT_NUM                (* (reg8 *) Vhi__PRT) 
/* Connect to Analog Globals */                                                  
#define Vhi_AG                     (* (reg8 *) Vhi__AG)                       
/* Analog MUX bux enable */
#define Vhi_AMUX                   (* (reg8 *) Vhi__AMUX) 
/* Bidirectional Enable */                                                        
#define Vhi_BIE                    (* (reg8 *) Vhi__BIE)
/* Bit-mask for Aliased Register Access */
#define Vhi_BIT_MASK               (* (reg8 *) Vhi__BIT_MASK)
/* Bypass Enable */
#define Vhi_BYP                    (* (reg8 *) Vhi__BYP)
/* Port wide control signals */                                                   
#define Vhi_CTL                    (* (reg8 *) Vhi__CTL)
/* Drive Modes */
#define Vhi_DM0                    (* (reg8 *) Vhi__DM0) 
#define Vhi_DM1                    (* (reg8 *) Vhi__DM1)
#define Vhi_DM2                    (* (reg8 *) Vhi__DM2) 
/* Input Buffer Disable Override */
#define Vhi_INP_DIS                (* (reg8 *) Vhi__INP_DIS)
/* LCD Common or Segment Drive */
#define Vhi_LCD_COM_SEG            (* (reg8 *) Vhi__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vhi_LCD_EN                 (* (reg8 *) Vhi__LCD_EN)
/* Slew Rate Control */
#define Vhi_SLW                    (* (reg8 *) Vhi__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vhi_PRTDSI__CAPS_SEL       (* (reg8 *) Vhi__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vhi_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vhi__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vhi_PRTDSI__OE_SEL0        (* (reg8 *) Vhi__PRTDSI__OE_SEL0) 
#define Vhi_PRTDSI__OE_SEL1        (* (reg8 *) Vhi__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vhi_PRTDSI__OUT_SEL0       (* (reg8 *) Vhi__PRTDSI__OUT_SEL0) 
#define Vhi_PRTDSI__OUT_SEL1       (* (reg8 *) Vhi__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vhi_PRTDSI__SYNC_OUT       (* (reg8 *) Vhi__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Vhi__SIO_CFG)
    #define Vhi_SIO_HYST_EN        (* (reg8 *) Vhi__SIO_HYST_EN)
    #define Vhi_SIO_REG_HIFREQ     (* (reg8 *) Vhi__SIO_REG_HIFREQ)
    #define Vhi_SIO_CFG            (* (reg8 *) Vhi__SIO_CFG)
    #define Vhi_SIO_DIFF           (* (reg8 *) Vhi__SIO_DIFF)
#endif /* (Vhi__SIO_CFG) */

/* Interrupt Registers */
#if defined(Vhi__INTSTAT)
    #define Vhi_INTSTAT            (* (reg8 *) Vhi__INTSTAT)
    #define Vhi_SNAP               (* (reg8 *) Vhi__SNAP)
    
	#define Vhi_0_INTTYPE_REG 		(* (reg8 *) Vhi__0__INTTYPE)
#endif /* (Vhi__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vhi_H */


/* [] END OF FILE */
