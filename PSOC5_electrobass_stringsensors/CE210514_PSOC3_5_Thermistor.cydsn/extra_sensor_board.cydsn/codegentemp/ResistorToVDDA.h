/*******************************************************************************
* File Name: ResistorToVDDA.h  
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

#if !defined(CY_PINS_ResistorToVDDA_H) /* Pins ResistorToVDDA_H */
#define CY_PINS_ResistorToVDDA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ResistorToVDDA_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ResistorToVDDA__PORT == 15 && ((ResistorToVDDA__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ResistorToVDDA_Write(uint8 value);
void    ResistorToVDDA_SetDriveMode(uint8 mode);
uint8   ResistorToVDDA_ReadDataReg(void);
uint8   ResistorToVDDA_Read(void);
void    ResistorToVDDA_SetInterruptMode(uint16 position, uint16 mode);
uint8   ResistorToVDDA_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ResistorToVDDA_SetDriveMode() function.
     *  @{
     */
        #define ResistorToVDDA_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ResistorToVDDA_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ResistorToVDDA_DM_RES_UP          PIN_DM_RES_UP
        #define ResistorToVDDA_DM_RES_DWN         PIN_DM_RES_DWN
        #define ResistorToVDDA_DM_OD_LO           PIN_DM_OD_LO
        #define ResistorToVDDA_DM_OD_HI           PIN_DM_OD_HI
        #define ResistorToVDDA_DM_STRONG          PIN_DM_STRONG
        #define ResistorToVDDA_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ResistorToVDDA_MASK               ResistorToVDDA__MASK
#define ResistorToVDDA_SHIFT              ResistorToVDDA__SHIFT
#define ResistorToVDDA_WIDTH              1u

/* Interrupt constants */
#if defined(ResistorToVDDA__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ResistorToVDDA_SetInterruptMode() function.
     *  @{
     */
        #define ResistorToVDDA_INTR_NONE      (uint16)(0x0000u)
        #define ResistorToVDDA_INTR_RISING    (uint16)(0x0001u)
        #define ResistorToVDDA_INTR_FALLING   (uint16)(0x0002u)
        #define ResistorToVDDA_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ResistorToVDDA_INTR_MASK      (0x01u) 
#endif /* (ResistorToVDDA__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ResistorToVDDA_PS                     (* (reg8 *) ResistorToVDDA__PS)
/* Data Register */
#define ResistorToVDDA_DR                     (* (reg8 *) ResistorToVDDA__DR)
/* Port Number */
#define ResistorToVDDA_PRT_NUM                (* (reg8 *) ResistorToVDDA__PRT) 
/* Connect to Analog Globals */                                                  
#define ResistorToVDDA_AG                     (* (reg8 *) ResistorToVDDA__AG)                       
/* Analog MUX bux enable */
#define ResistorToVDDA_AMUX                   (* (reg8 *) ResistorToVDDA__AMUX) 
/* Bidirectional Enable */                                                        
#define ResistorToVDDA_BIE                    (* (reg8 *) ResistorToVDDA__BIE)
/* Bit-mask for Aliased Register Access */
#define ResistorToVDDA_BIT_MASK               (* (reg8 *) ResistorToVDDA__BIT_MASK)
/* Bypass Enable */
#define ResistorToVDDA_BYP                    (* (reg8 *) ResistorToVDDA__BYP)
/* Port wide control signals */                                                   
#define ResistorToVDDA_CTL                    (* (reg8 *) ResistorToVDDA__CTL)
/* Drive Modes */
#define ResistorToVDDA_DM0                    (* (reg8 *) ResistorToVDDA__DM0) 
#define ResistorToVDDA_DM1                    (* (reg8 *) ResistorToVDDA__DM1)
#define ResistorToVDDA_DM2                    (* (reg8 *) ResistorToVDDA__DM2) 
/* Input Buffer Disable Override */
#define ResistorToVDDA_INP_DIS                (* (reg8 *) ResistorToVDDA__INP_DIS)
/* LCD Common or Segment Drive */
#define ResistorToVDDA_LCD_COM_SEG            (* (reg8 *) ResistorToVDDA__LCD_COM_SEG)
/* Enable Segment LCD */
#define ResistorToVDDA_LCD_EN                 (* (reg8 *) ResistorToVDDA__LCD_EN)
/* Slew Rate Control */
#define ResistorToVDDA_SLW                    (* (reg8 *) ResistorToVDDA__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ResistorToVDDA_PRTDSI__CAPS_SEL       (* (reg8 *) ResistorToVDDA__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ResistorToVDDA_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ResistorToVDDA__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ResistorToVDDA_PRTDSI__OE_SEL0        (* (reg8 *) ResistorToVDDA__PRTDSI__OE_SEL0) 
#define ResistorToVDDA_PRTDSI__OE_SEL1        (* (reg8 *) ResistorToVDDA__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ResistorToVDDA_PRTDSI__OUT_SEL0       (* (reg8 *) ResistorToVDDA__PRTDSI__OUT_SEL0) 
#define ResistorToVDDA_PRTDSI__OUT_SEL1       (* (reg8 *) ResistorToVDDA__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ResistorToVDDA_PRTDSI__SYNC_OUT       (* (reg8 *) ResistorToVDDA__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ResistorToVDDA__SIO_CFG)
    #define ResistorToVDDA_SIO_HYST_EN        (* (reg8 *) ResistorToVDDA__SIO_HYST_EN)
    #define ResistorToVDDA_SIO_REG_HIFREQ     (* (reg8 *) ResistorToVDDA__SIO_REG_HIFREQ)
    #define ResistorToVDDA_SIO_CFG            (* (reg8 *) ResistorToVDDA__SIO_CFG)
    #define ResistorToVDDA_SIO_DIFF           (* (reg8 *) ResistorToVDDA__SIO_DIFF)
#endif /* (ResistorToVDDA__SIO_CFG) */

/* Interrupt Registers */
#if defined(ResistorToVDDA__INTSTAT)
    #define ResistorToVDDA_INTSTAT            (* (reg8 *) ResistorToVDDA__INTSTAT)
    #define ResistorToVDDA_SNAP               (* (reg8 *) ResistorToVDDA__SNAP)
    
	#define ResistorToVDDA_0_INTTYPE_REG 		(* (reg8 *) ResistorToVDDA__0__INTTYPE)
#endif /* (ResistorToVDDA__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ResistorToVDDA_H */


/* [] END OF FILE */
