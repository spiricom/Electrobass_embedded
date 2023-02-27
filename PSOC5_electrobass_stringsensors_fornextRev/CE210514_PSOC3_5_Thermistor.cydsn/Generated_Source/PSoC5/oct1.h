/*******************************************************************************
* File Name: oct1.h  
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

#if !defined(CY_PINS_oct1_H) /* Pins oct1_H */
#define CY_PINS_oct1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "oct1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 oct1__PORT == 15 && ((oct1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    oct1_Write(uint8 value);
void    oct1_SetDriveMode(uint8 mode);
uint8   oct1_ReadDataReg(void);
uint8   oct1_Read(void);
void    oct1_SetInterruptMode(uint16 position, uint16 mode);
uint8   oct1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the oct1_SetDriveMode() function.
     *  @{
     */
        #define oct1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define oct1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define oct1_DM_RES_UP          PIN_DM_RES_UP
        #define oct1_DM_RES_DWN         PIN_DM_RES_DWN
        #define oct1_DM_OD_LO           PIN_DM_OD_LO
        #define oct1_DM_OD_HI           PIN_DM_OD_HI
        #define oct1_DM_STRONG          PIN_DM_STRONG
        #define oct1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define oct1_MASK               oct1__MASK
#define oct1_SHIFT              oct1__SHIFT
#define oct1_WIDTH              1u

/* Interrupt constants */
#if defined(oct1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in oct1_SetInterruptMode() function.
     *  @{
     */
        #define oct1_INTR_NONE      (uint16)(0x0000u)
        #define oct1_INTR_RISING    (uint16)(0x0001u)
        #define oct1_INTR_FALLING   (uint16)(0x0002u)
        #define oct1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define oct1_INTR_MASK      (0x01u) 
#endif /* (oct1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define oct1_PS                     (* (reg8 *) oct1__PS)
/* Data Register */
#define oct1_DR                     (* (reg8 *) oct1__DR)
/* Port Number */
#define oct1_PRT_NUM                (* (reg8 *) oct1__PRT) 
/* Connect to Analog Globals */                                                  
#define oct1_AG                     (* (reg8 *) oct1__AG)                       
/* Analog MUX bux enable */
#define oct1_AMUX                   (* (reg8 *) oct1__AMUX) 
/* Bidirectional Enable */                                                        
#define oct1_BIE                    (* (reg8 *) oct1__BIE)
/* Bit-mask for Aliased Register Access */
#define oct1_BIT_MASK               (* (reg8 *) oct1__BIT_MASK)
/* Bypass Enable */
#define oct1_BYP                    (* (reg8 *) oct1__BYP)
/* Port wide control signals */                                                   
#define oct1_CTL                    (* (reg8 *) oct1__CTL)
/* Drive Modes */
#define oct1_DM0                    (* (reg8 *) oct1__DM0) 
#define oct1_DM1                    (* (reg8 *) oct1__DM1)
#define oct1_DM2                    (* (reg8 *) oct1__DM2) 
/* Input Buffer Disable Override */
#define oct1_INP_DIS                (* (reg8 *) oct1__INP_DIS)
/* LCD Common or Segment Drive */
#define oct1_LCD_COM_SEG            (* (reg8 *) oct1__LCD_COM_SEG)
/* Enable Segment LCD */
#define oct1_LCD_EN                 (* (reg8 *) oct1__LCD_EN)
/* Slew Rate Control */
#define oct1_SLW                    (* (reg8 *) oct1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define oct1_PRTDSI__CAPS_SEL       (* (reg8 *) oct1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define oct1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) oct1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define oct1_PRTDSI__OE_SEL0        (* (reg8 *) oct1__PRTDSI__OE_SEL0) 
#define oct1_PRTDSI__OE_SEL1        (* (reg8 *) oct1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define oct1_PRTDSI__OUT_SEL0       (* (reg8 *) oct1__PRTDSI__OUT_SEL0) 
#define oct1_PRTDSI__OUT_SEL1       (* (reg8 *) oct1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define oct1_PRTDSI__SYNC_OUT       (* (reg8 *) oct1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(oct1__SIO_CFG)
    #define oct1_SIO_HYST_EN        (* (reg8 *) oct1__SIO_HYST_EN)
    #define oct1_SIO_REG_HIFREQ     (* (reg8 *) oct1__SIO_REG_HIFREQ)
    #define oct1_SIO_CFG            (* (reg8 *) oct1__SIO_CFG)
    #define oct1_SIO_DIFF           (* (reg8 *) oct1__SIO_DIFF)
#endif /* (oct1__SIO_CFG) */

/* Interrupt Registers */
#if defined(oct1__INTSTAT)
    #define oct1_INTSTAT            (* (reg8 *) oct1__INTSTAT)
    #define oct1_SNAP               (* (reg8 *) oct1__SNAP)
    
	#define oct1_0_INTTYPE_REG 		(* (reg8 *) oct1__0__INTTYPE)
#endif /* (oct1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_oct1_H */


/* [] END OF FILE */
