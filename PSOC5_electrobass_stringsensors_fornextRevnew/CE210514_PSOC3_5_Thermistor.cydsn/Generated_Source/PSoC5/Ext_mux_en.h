/*******************************************************************************
* File Name: Ext_mux_en.h  
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

#if !defined(CY_PINS_Ext_mux_en_H) /* Pins Ext_mux_en_H */
#define CY_PINS_Ext_mux_en_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Ext_mux_en_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Ext_mux_en__PORT == 15 && ((Ext_mux_en__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Ext_mux_en_Write(uint8 value);
void    Ext_mux_en_SetDriveMode(uint8 mode);
uint8   Ext_mux_en_ReadDataReg(void);
uint8   Ext_mux_en_Read(void);
void    Ext_mux_en_SetInterruptMode(uint16 position, uint16 mode);
uint8   Ext_mux_en_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Ext_mux_en_SetDriveMode() function.
     *  @{
     */
        #define Ext_mux_en_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Ext_mux_en_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Ext_mux_en_DM_RES_UP          PIN_DM_RES_UP
        #define Ext_mux_en_DM_RES_DWN         PIN_DM_RES_DWN
        #define Ext_mux_en_DM_OD_LO           PIN_DM_OD_LO
        #define Ext_mux_en_DM_OD_HI           PIN_DM_OD_HI
        #define Ext_mux_en_DM_STRONG          PIN_DM_STRONG
        #define Ext_mux_en_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Ext_mux_en_MASK               Ext_mux_en__MASK
#define Ext_mux_en_SHIFT              Ext_mux_en__SHIFT
#define Ext_mux_en_WIDTH              1u

/* Interrupt constants */
#if defined(Ext_mux_en__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Ext_mux_en_SetInterruptMode() function.
     *  @{
     */
        #define Ext_mux_en_INTR_NONE      (uint16)(0x0000u)
        #define Ext_mux_en_INTR_RISING    (uint16)(0x0001u)
        #define Ext_mux_en_INTR_FALLING   (uint16)(0x0002u)
        #define Ext_mux_en_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Ext_mux_en_INTR_MASK      (0x01u) 
#endif /* (Ext_mux_en__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Ext_mux_en_PS                     (* (reg8 *) Ext_mux_en__PS)
/* Data Register */
#define Ext_mux_en_DR                     (* (reg8 *) Ext_mux_en__DR)
/* Port Number */
#define Ext_mux_en_PRT_NUM                (* (reg8 *) Ext_mux_en__PRT) 
/* Connect to Analog Globals */                                                  
#define Ext_mux_en_AG                     (* (reg8 *) Ext_mux_en__AG)                       
/* Analog MUX bux enable */
#define Ext_mux_en_AMUX                   (* (reg8 *) Ext_mux_en__AMUX) 
/* Bidirectional Enable */                                                        
#define Ext_mux_en_BIE                    (* (reg8 *) Ext_mux_en__BIE)
/* Bit-mask for Aliased Register Access */
#define Ext_mux_en_BIT_MASK               (* (reg8 *) Ext_mux_en__BIT_MASK)
/* Bypass Enable */
#define Ext_mux_en_BYP                    (* (reg8 *) Ext_mux_en__BYP)
/* Port wide control signals */                                                   
#define Ext_mux_en_CTL                    (* (reg8 *) Ext_mux_en__CTL)
/* Drive Modes */
#define Ext_mux_en_DM0                    (* (reg8 *) Ext_mux_en__DM0) 
#define Ext_mux_en_DM1                    (* (reg8 *) Ext_mux_en__DM1)
#define Ext_mux_en_DM2                    (* (reg8 *) Ext_mux_en__DM2) 
/* Input Buffer Disable Override */
#define Ext_mux_en_INP_DIS                (* (reg8 *) Ext_mux_en__INP_DIS)
/* LCD Common or Segment Drive */
#define Ext_mux_en_LCD_COM_SEG            (* (reg8 *) Ext_mux_en__LCD_COM_SEG)
/* Enable Segment LCD */
#define Ext_mux_en_LCD_EN                 (* (reg8 *) Ext_mux_en__LCD_EN)
/* Slew Rate Control */
#define Ext_mux_en_SLW                    (* (reg8 *) Ext_mux_en__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Ext_mux_en_PRTDSI__CAPS_SEL       (* (reg8 *) Ext_mux_en__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Ext_mux_en_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Ext_mux_en__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Ext_mux_en_PRTDSI__OE_SEL0        (* (reg8 *) Ext_mux_en__PRTDSI__OE_SEL0) 
#define Ext_mux_en_PRTDSI__OE_SEL1        (* (reg8 *) Ext_mux_en__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Ext_mux_en_PRTDSI__OUT_SEL0       (* (reg8 *) Ext_mux_en__PRTDSI__OUT_SEL0) 
#define Ext_mux_en_PRTDSI__OUT_SEL1       (* (reg8 *) Ext_mux_en__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Ext_mux_en_PRTDSI__SYNC_OUT       (* (reg8 *) Ext_mux_en__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Ext_mux_en__SIO_CFG)
    #define Ext_mux_en_SIO_HYST_EN        (* (reg8 *) Ext_mux_en__SIO_HYST_EN)
    #define Ext_mux_en_SIO_REG_HIFREQ     (* (reg8 *) Ext_mux_en__SIO_REG_HIFREQ)
    #define Ext_mux_en_SIO_CFG            (* (reg8 *) Ext_mux_en__SIO_CFG)
    #define Ext_mux_en_SIO_DIFF           (* (reg8 *) Ext_mux_en__SIO_DIFF)
#endif /* (Ext_mux_en__SIO_CFG) */

/* Interrupt Registers */
#if defined(Ext_mux_en__INTSTAT)
    #define Ext_mux_en_INTSTAT            (* (reg8 *) Ext_mux_en__INTSTAT)
    #define Ext_mux_en_SNAP               (* (reg8 *) Ext_mux_en__SNAP)
    
	#define Ext_mux_en_0_INTTYPE_REG 		(* (reg8 *) Ext_mux_en__0__INTTYPE)
#endif /* (Ext_mux_en__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Ext_mux_en_H */


/* [] END OF FILE */
