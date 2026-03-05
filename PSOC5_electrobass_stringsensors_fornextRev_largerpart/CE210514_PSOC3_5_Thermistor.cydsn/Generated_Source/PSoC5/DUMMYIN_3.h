/*******************************************************************************
* File Name: DUMMYIN_3.h  
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

#if !defined(CY_PINS_DUMMYIN_3_H) /* Pins DUMMYIN_3_H */
#define CY_PINS_DUMMYIN_3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DUMMYIN_3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DUMMYIN_3__PORT == 15 && ((DUMMYIN_3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DUMMYIN_3_Write(uint8 value);
void    DUMMYIN_3_SetDriveMode(uint8 mode);
uint8   DUMMYIN_3_ReadDataReg(void);
uint8   DUMMYIN_3_Read(void);
void    DUMMYIN_3_SetInterruptMode(uint16 position, uint16 mode);
uint8   DUMMYIN_3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DUMMYIN_3_SetDriveMode() function.
     *  @{
     */
        #define DUMMYIN_3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DUMMYIN_3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DUMMYIN_3_DM_RES_UP          PIN_DM_RES_UP
        #define DUMMYIN_3_DM_RES_DWN         PIN_DM_RES_DWN
        #define DUMMYIN_3_DM_OD_LO           PIN_DM_OD_LO
        #define DUMMYIN_3_DM_OD_HI           PIN_DM_OD_HI
        #define DUMMYIN_3_DM_STRONG          PIN_DM_STRONG
        #define DUMMYIN_3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DUMMYIN_3_MASK               DUMMYIN_3__MASK
#define DUMMYIN_3_SHIFT              DUMMYIN_3__SHIFT
#define DUMMYIN_3_WIDTH              1u

/* Interrupt constants */
#if defined(DUMMYIN_3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DUMMYIN_3_SetInterruptMode() function.
     *  @{
     */
        #define DUMMYIN_3_INTR_NONE      (uint16)(0x0000u)
        #define DUMMYIN_3_INTR_RISING    (uint16)(0x0001u)
        #define DUMMYIN_3_INTR_FALLING   (uint16)(0x0002u)
        #define DUMMYIN_3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DUMMYIN_3_INTR_MASK      (0x01u) 
#endif /* (DUMMYIN_3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DUMMYIN_3_PS                     (* (reg8 *) DUMMYIN_3__PS)
/* Data Register */
#define DUMMYIN_3_DR                     (* (reg8 *) DUMMYIN_3__DR)
/* Port Number */
#define DUMMYIN_3_PRT_NUM                (* (reg8 *) DUMMYIN_3__PRT) 
/* Connect to Analog Globals */                                                  
#define DUMMYIN_3_AG                     (* (reg8 *) DUMMYIN_3__AG)                       
/* Analog MUX bux enable */
#define DUMMYIN_3_AMUX                   (* (reg8 *) DUMMYIN_3__AMUX) 
/* Bidirectional Enable */                                                        
#define DUMMYIN_3_BIE                    (* (reg8 *) DUMMYIN_3__BIE)
/* Bit-mask for Aliased Register Access */
#define DUMMYIN_3_BIT_MASK               (* (reg8 *) DUMMYIN_3__BIT_MASK)
/* Bypass Enable */
#define DUMMYIN_3_BYP                    (* (reg8 *) DUMMYIN_3__BYP)
/* Port wide control signals */                                                   
#define DUMMYIN_3_CTL                    (* (reg8 *) DUMMYIN_3__CTL)
/* Drive Modes */
#define DUMMYIN_3_DM0                    (* (reg8 *) DUMMYIN_3__DM0) 
#define DUMMYIN_3_DM1                    (* (reg8 *) DUMMYIN_3__DM1)
#define DUMMYIN_3_DM2                    (* (reg8 *) DUMMYIN_3__DM2) 
/* Input Buffer Disable Override */
#define DUMMYIN_3_INP_DIS                (* (reg8 *) DUMMYIN_3__INP_DIS)
/* LCD Common or Segment Drive */
#define DUMMYIN_3_LCD_COM_SEG            (* (reg8 *) DUMMYIN_3__LCD_COM_SEG)
/* Enable Segment LCD */
#define DUMMYIN_3_LCD_EN                 (* (reg8 *) DUMMYIN_3__LCD_EN)
/* Slew Rate Control */
#define DUMMYIN_3_SLW                    (* (reg8 *) DUMMYIN_3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DUMMYIN_3_PRTDSI__CAPS_SEL       (* (reg8 *) DUMMYIN_3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DUMMYIN_3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DUMMYIN_3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DUMMYIN_3_PRTDSI__OE_SEL0        (* (reg8 *) DUMMYIN_3__PRTDSI__OE_SEL0) 
#define DUMMYIN_3_PRTDSI__OE_SEL1        (* (reg8 *) DUMMYIN_3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DUMMYIN_3_PRTDSI__OUT_SEL0       (* (reg8 *) DUMMYIN_3__PRTDSI__OUT_SEL0) 
#define DUMMYIN_3_PRTDSI__OUT_SEL1       (* (reg8 *) DUMMYIN_3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DUMMYIN_3_PRTDSI__SYNC_OUT       (* (reg8 *) DUMMYIN_3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DUMMYIN_3__SIO_CFG)
    #define DUMMYIN_3_SIO_HYST_EN        (* (reg8 *) DUMMYIN_3__SIO_HYST_EN)
    #define DUMMYIN_3_SIO_REG_HIFREQ     (* (reg8 *) DUMMYIN_3__SIO_REG_HIFREQ)
    #define DUMMYIN_3_SIO_CFG            (* (reg8 *) DUMMYIN_3__SIO_CFG)
    #define DUMMYIN_3_SIO_DIFF           (* (reg8 *) DUMMYIN_3__SIO_DIFF)
#endif /* (DUMMYIN_3__SIO_CFG) */

/* Interrupt Registers */
#if defined(DUMMYIN_3__INTSTAT)
    #define DUMMYIN_3_INTSTAT            (* (reg8 *) DUMMYIN_3__INTSTAT)
    #define DUMMYIN_3_SNAP               (* (reg8 *) DUMMYIN_3__SNAP)
    
	#define DUMMYIN_3_0_INTTYPE_REG 		(* (reg8 *) DUMMYIN_3__0__INTTYPE)
#endif /* (DUMMYIN_3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DUMMYIN_3_H */


/* [] END OF FILE */
