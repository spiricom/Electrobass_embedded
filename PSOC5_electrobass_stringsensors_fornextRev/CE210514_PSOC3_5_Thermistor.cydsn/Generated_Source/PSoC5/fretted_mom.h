/*******************************************************************************
* File Name: fretted_mom.h  
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

#if !defined(CY_PINS_fretted_mom_H) /* Pins fretted_mom_H */
#define CY_PINS_fretted_mom_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "fretted_mom_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 fretted_mom__PORT == 15 && ((fretted_mom__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    fretted_mom_Write(uint8 value);
void    fretted_mom_SetDriveMode(uint8 mode);
uint8   fretted_mom_ReadDataReg(void);
uint8   fretted_mom_Read(void);
void    fretted_mom_SetInterruptMode(uint16 position, uint16 mode);
uint8   fretted_mom_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the fretted_mom_SetDriveMode() function.
     *  @{
     */
        #define fretted_mom_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define fretted_mom_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define fretted_mom_DM_RES_UP          PIN_DM_RES_UP
        #define fretted_mom_DM_RES_DWN         PIN_DM_RES_DWN
        #define fretted_mom_DM_OD_LO           PIN_DM_OD_LO
        #define fretted_mom_DM_OD_HI           PIN_DM_OD_HI
        #define fretted_mom_DM_STRONG          PIN_DM_STRONG
        #define fretted_mom_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define fretted_mom_MASK               fretted_mom__MASK
#define fretted_mom_SHIFT              fretted_mom__SHIFT
#define fretted_mom_WIDTH              1u

/* Interrupt constants */
#if defined(fretted_mom__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in fretted_mom_SetInterruptMode() function.
     *  @{
     */
        #define fretted_mom_INTR_NONE      (uint16)(0x0000u)
        #define fretted_mom_INTR_RISING    (uint16)(0x0001u)
        #define fretted_mom_INTR_FALLING   (uint16)(0x0002u)
        #define fretted_mom_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define fretted_mom_INTR_MASK      (0x01u) 
#endif /* (fretted_mom__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define fretted_mom_PS                     (* (reg8 *) fretted_mom__PS)
/* Data Register */
#define fretted_mom_DR                     (* (reg8 *) fretted_mom__DR)
/* Port Number */
#define fretted_mom_PRT_NUM                (* (reg8 *) fretted_mom__PRT) 
/* Connect to Analog Globals */                                                  
#define fretted_mom_AG                     (* (reg8 *) fretted_mom__AG)                       
/* Analog MUX bux enable */
#define fretted_mom_AMUX                   (* (reg8 *) fretted_mom__AMUX) 
/* Bidirectional Enable */                                                        
#define fretted_mom_BIE                    (* (reg8 *) fretted_mom__BIE)
/* Bit-mask for Aliased Register Access */
#define fretted_mom_BIT_MASK               (* (reg8 *) fretted_mom__BIT_MASK)
/* Bypass Enable */
#define fretted_mom_BYP                    (* (reg8 *) fretted_mom__BYP)
/* Port wide control signals */                                                   
#define fretted_mom_CTL                    (* (reg8 *) fretted_mom__CTL)
/* Drive Modes */
#define fretted_mom_DM0                    (* (reg8 *) fretted_mom__DM0) 
#define fretted_mom_DM1                    (* (reg8 *) fretted_mom__DM1)
#define fretted_mom_DM2                    (* (reg8 *) fretted_mom__DM2) 
/* Input Buffer Disable Override */
#define fretted_mom_INP_DIS                (* (reg8 *) fretted_mom__INP_DIS)
/* LCD Common or Segment Drive */
#define fretted_mom_LCD_COM_SEG            (* (reg8 *) fretted_mom__LCD_COM_SEG)
/* Enable Segment LCD */
#define fretted_mom_LCD_EN                 (* (reg8 *) fretted_mom__LCD_EN)
/* Slew Rate Control */
#define fretted_mom_SLW                    (* (reg8 *) fretted_mom__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define fretted_mom_PRTDSI__CAPS_SEL       (* (reg8 *) fretted_mom__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define fretted_mom_PRTDSI__DBL_SYNC_IN    (* (reg8 *) fretted_mom__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define fretted_mom_PRTDSI__OE_SEL0        (* (reg8 *) fretted_mom__PRTDSI__OE_SEL0) 
#define fretted_mom_PRTDSI__OE_SEL1        (* (reg8 *) fretted_mom__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define fretted_mom_PRTDSI__OUT_SEL0       (* (reg8 *) fretted_mom__PRTDSI__OUT_SEL0) 
#define fretted_mom_PRTDSI__OUT_SEL1       (* (reg8 *) fretted_mom__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define fretted_mom_PRTDSI__SYNC_OUT       (* (reg8 *) fretted_mom__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(fretted_mom__SIO_CFG)
    #define fretted_mom_SIO_HYST_EN        (* (reg8 *) fretted_mom__SIO_HYST_EN)
    #define fretted_mom_SIO_REG_HIFREQ     (* (reg8 *) fretted_mom__SIO_REG_HIFREQ)
    #define fretted_mom_SIO_CFG            (* (reg8 *) fretted_mom__SIO_CFG)
    #define fretted_mom_SIO_DIFF           (* (reg8 *) fretted_mom__SIO_DIFF)
#endif /* (fretted_mom__SIO_CFG) */

/* Interrupt Registers */
#if defined(fretted_mom__INTSTAT)
    #define fretted_mom_INTSTAT            (* (reg8 *) fretted_mom__INTSTAT)
    #define fretted_mom_SNAP               (* (reg8 *) fretted_mom__SNAP)
    
	#define fretted_mom_0_INTTYPE_REG 		(* (reg8 *) fretted_mom__0__INTTYPE)
#endif /* (fretted_mom__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_fretted_mom_H */


/* [] END OF FILE */
