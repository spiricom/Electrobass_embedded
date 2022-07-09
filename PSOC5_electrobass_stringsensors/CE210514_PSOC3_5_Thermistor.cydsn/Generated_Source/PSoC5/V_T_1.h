/*******************************************************************************
* File Name: V_T_1.h  
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

#if !defined(CY_PINS_V_T_1_H) /* Pins V_T_1_H */
#define CY_PINS_V_T_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "V_T_1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 V_T_1__PORT == 15 && ((V_T_1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    V_T_1_Write(uint8 value);
void    V_T_1_SetDriveMode(uint8 mode);
uint8   V_T_1_ReadDataReg(void);
uint8   V_T_1_Read(void);
void    V_T_1_SetInterruptMode(uint16 position, uint16 mode);
uint8   V_T_1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the V_T_1_SetDriveMode() function.
     *  @{
     */
        #define V_T_1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define V_T_1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define V_T_1_DM_RES_UP          PIN_DM_RES_UP
        #define V_T_1_DM_RES_DWN         PIN_DM_RES_DWN
        #define V_T_1_DM_OD_LO           PIN_DM_OD_LO
        #define V_T_1_DM_OD_HI           PIN_DM_OD_HI
        #define V_T_1_DM_STRONG          PIN_DM_STRONG
        #define V_T_1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define V_T_1_MASK               V_T_1__MASK
#define V_T_1_SHIFT              V_T_1__SHIFT
#define V_T_1_WIDTH              1u

/* Interrupt constants */
#if defined(V_T_1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in V_T_1_SetInterruptMode() function.
     *  @{
     */
        #define V_T_1_INTR_NONE      (uint16)(0x0000u)
        #define V_T_1_INTR_RISING    (uint16)(0x0001u)
        #define V_T_1_INTR_FALLING   (uint16)(0x0002u)
        #define V_T_1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define V_T_1_INTR_MASK      (0x01u) 
#endif /* (V_T_1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define V_T_1_PS                     (* (reg8 *) V_T_1__PS)
/* Data Register */
#define V_T_1_DR                     (* (reg8 *) V_T_1__DR)
/* Port Number */
#define V_T_1_PRT_NUM                (* (reg8 *) V_T_1__PRT) 
/* Connect to Analog Globals */                                                  
#define V_T_1_AG                     (* (reg8 *) V_T_1__AG)                       
/* Analog MUX bux enable */
#define V_T_1_AMUX                   (* (reg8 *) V_T_1__AMUX) 
/* Bidirectional Enable */                                                        
#define V_T_1_BIE                    (* (reg8 *) V_T_1__BIE)
/* Bit-mask for Aliased Register Access */
#define V_T_1_BIT_MASK               (* (reg8 *) V_T_1__BIT_MASK)
/* Bypass Enable */
#define V_T_1_BYP                    (* (reg8 *) V_T_1__BYP)
/* Port wide control signals */                                                   
#define V_T_1_CTL                    (* (reg8 *) V_T_1__CTL)
/* Drive Modes */
#define V_T_1_DM0                    (* (reg8 *) V_T_1__DM0) 
#define V_T_1_DM1                    (* (reg8 *) V_T_1__DM1)
#define V_T_1_DM2                    (* (reg8 *) V_T_1__DM2) 
/* Input Buffer Disable Override */
#define V_T_1_INP_DIS                (* (reg8 *) V_T_1__INP_DIS)
/* LCD Common or Segment Drive */
#define V_T_1_LCD_COM_SEG            (* (reg8 *) V_T_1__LCD_COM_SEG)
/* Enable Segment LCD */
#define V_T_1_LCD_EN                 (* (reg8 *) V_T_1__LCD_EN)
/* Slew Rate Control */
#define V_T_1_SLW                    (* (reg8 *) V_T_1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define V_T_1_PRTDSI__CAPS_SEL       (* (reg8 *) V_T_1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define V_T_1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) V_T_1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define V_T_1_PRTDSI__OE_SEL0        (* (reg8 *) V_T_1__PRTDSI__OE_SEL0) 
#define V_T_1_PRTDSI__OE_SEL1        (* (reg8 *) V_T_1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define V_T_1_PRTDSI__OUT_SEL0       (* (reg8 *) V_T_1__PRTDSI__OUT_SEL0) 
#define V_T_1_PRTDSI__OUT_SEL1       (* (reg8 *) V_T_1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define V_T_1_PRTDSI__SYNC_OUT       (* (reg8 *) V_T_1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(V_T_1__SIO_CFG)
    #define V_T_1_SIO_HYST_EN        (* (reg8 *) V_T_1__SIO_HYST_EN)
    #define V_T_1_SIO_REG_HIFREQ     (* (reg8 *) V_T_1__SIO_REG_HIFREQ)
    #define V_T_1_SIO_CFG            (* (reg8 *) V_T_1__SIO_CFG)
    #define V_T_1_SIO_DIFF           (* (reg8 *) V_T_1__SIO_DIFF)
#endif /* (V_T_1__SIO_CFG) */

/* Interrupt Registers */
#if defined(V_T_1__INTSTAT)
    #define V_T_1_INTSTAT            (* (reg8 *) V_T_1__INTSTAT)
    #define V_T_1_SNAP               (* (reg8 *) V_T_1__SNAP)
    
	#define V_T_1_0_INTTYPE_REG 		(* (reg8 *) V_T_1__0__INTTYPE)
#endif /* (V_T_1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_V_T_1_H */


/* [] END OF FILE */
