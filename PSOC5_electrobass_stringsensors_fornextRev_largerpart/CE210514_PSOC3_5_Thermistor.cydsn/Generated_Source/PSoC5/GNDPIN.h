/*******************************************************************************
* File Name: GNDPIN.h  
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

#if !defined(CY_PINS_GNDPIN_H) /* Pins GNDPIN_H */
#define CY_PINS_GNDPIN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "GNDPIN_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 GNDPIN__PORT == 15 && ((GNDPIN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    GNDPIN_Write(uint8 value);
void    GNDPIN_SetDriveMode(uint8 mode);
uint8   GNDPIN_ReadDataReg(void);
uint8   GNDPIN_Read(void);
void    GNDPIN_SetInterruptMode(uint16 position, uint16 mode);
uint8   GNDPIN_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the GNDPIN_SetDriveMode() function.
     *  @{
     */
        #define GNDPIN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define GNDPIN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define GNDPIN_DM_RES_UP          PIN_DM_RES_UP
        #define GNDPIN_DM_RES_DWN         PIN_DM_RES_DWN
        #define GNDPIN_DM_OD_LO           PIN_DM_OD_LO
        #define GNDPIN_DM_OD_HI           PIN_DM_OD_HI
        #define GNDPIN_DM_STRONG          PIN_DM_STRONG
        #define GNDPIN_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define GNDPIN_MASK               GNDPIN__MASK
#define GNDPIN_SHIFT              GNDPIN__SHIFT
#define GNDPIN_WIDTH              1u

/* Interrupt constants */
#if defined(GNDPIN__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in GNDPIN_SetInterruptMode() function.
     *  @{
     */
        #define GNDPIN_INTR_NONE      (uint16)(0x0000u)
        #define GNDPIN_INTR_RISING    (uint16)(0x0001u)
        #define GNDPIN_INTR_FALLING   (uint16)(0x0002u)
        #define GNDPIN_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define GNDPIN_INTR_MASK      (0x01u) 
#endif /* (GNDPIN__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define GNDPIN_PS                     (* (reg8 *) GNDPIN__PS)
/* Data Register */
#define GNDPIN_DR                     (* (reg8 *) GNDPIN__DR)
/* Port Number */
#define GNDPIN_PRT_NUM                (* (reg8 *) GNDPIN__PRT) 
/* Connect to Analog Globals */                                                  
#define GNDPIN_AG                     (* (reg8 *) GNDPIN__AG)                       
/* Analog MUX bux enable */
#define GNDPIN_AMUX                   (* (reg8 *) GNDPIN__AMUX) 
/* Bidirectional Enable */                                                        
#define GNDPIN_BIE                    (* (reg8 *) GNDPIN__BIE)
/* Bit-mask for Aliased Register Access */
#define GNDPIN_BIT_MASK               (* (reg8 *) GNDPIN__BIT_MASK)
/* Bypass Enable */
#define GNDPIN_BYP                    (* (reg8 *) GNDPIN__BYP)
/* Port wide control signals */                                                   
#define GNDPIN_CTL                    (* (reg8 *) GNDPIN__CTL)
/* Drive Modes */
#define GNDPIN_DM0                    (* (reg8 *) GNDPIN__DM0) 
#define GNDPIN_DM1                    (* (reg8 *) GNDPIN__DM1)
#define GNDPIN_DM2                    (* (reg8 *) GNDPIN__DM2) 
/* Input Buffer Disable Override */
#define GNDPIN_INP_DIS                (* (reg8 *) GNDPIN__INP_DIS)
/* LCD Common or Segment Drive */
#define GNDPIN_LCD_COM_SEG            (* (reg8 *) GNDPIN__LCD_COM_SEG)
/* Enable Segment LCD */
#define GNDPIN_LCD_EN                 (* (reg8 *) GNDPIN__LCD_EN)
/* Slew Rate Control */
#define GNDPIN_SLW                    (* (reg8 *) GNDPIN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define GNDPIN_PRTDSI__CAPS_SEL       (* (reg8 *) GNDPIN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define GNDPIN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) GNDPIN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define GNDPIN_PRTDSI__OE_SEL0        (* (reg8 *) GNDPIN__PRTDSI__OE_SEL0) 
#define GNDPIN_PRTDSI__OE_SEL1        (* (reg8 *) GNDPIN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define GNDPIN_PRTDSI__OUT_SEL0       (* (reg8 *) GNDPIN__PRTDSI__OUT_SEL0) 
#define GNDPIN_PRTDSI__OUT_SEL1       (* (reg8 *) GNDPIN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define GNDPIN_PRTDSI__SYNC_OUT       (* (reg8 *) GNDPIN__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(GNDPIN__SIO_CFG)
    #define GNDPIN_SIO_HYST_EN        (* (reg8 *) GNDPIN__SIO_HYST_EN)
    #define GNDPIN_SIO_REG_HIFREQ     (* (reg8 *) GNDPIN__SIO_REG_HIFREQ)
    #define GNDPIN_SIO_CFG            (* (reg8 *) GNDPIN__SIO_CFG)
    #define GNDPIN_SIO_DIFF           (* (reg8 *) GNDPIN__SIO_DIFF)
#endif /* (GNDPIN__SIO_CFG) */

/* Interrupt Registers */
#if defined(GNDPIN__INTSTAT)
    #define GNDPIN_INTSTAT            (* (reg8 *) GNDPIN__INTSTAT)
    #define GNDPIN_SNAP               (* (reg8 *) GNDPIN__SNAP)
    
	#define GNDPIN_0_INTTYPE_REG 		(* (reg8 *) GNDPIN__0__INTTYPE)
#endif /* (GNDPIN__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_GNDPIN_H */


/* [] END OF FILE */
