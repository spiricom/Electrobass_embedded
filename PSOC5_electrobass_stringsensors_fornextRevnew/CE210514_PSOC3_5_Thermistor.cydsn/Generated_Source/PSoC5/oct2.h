/*******************************************************************************
* File Name: oct2.h  
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

#if !defined(CY_PINS_oct2_H) /* Pins oct2_H */
#define CY_PINS_oct2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "oct2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 oct2__PORT == 15 && ((oct2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    oct2_Write(uint8 value);
void    oct2_SetDriveMode(uint8 mode);
uint8   oct2_ReadDataReg(void);
uint8   oct2_Read(void);
void    oct2_SetInterruptMode(uint16 position, uint16 mode);
uint8   oct2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the oct2_SetDriveMode() function.
     *  @{
     */
        #define oct2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define oct2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define oct2_DM_RES_UP          PIN_DM_RES_UP
        #define oct2_DM_RES_DWN         PIN_DM_RES_DWN
        #define oct2_DM_OD_LO           PIN_DM_OD_LO
        #define oct2_DM_OD_HI           PIN_DM_OD_HI
        #define oct2_DM_STRONG          PIN_DM_STRONG
        #define oct2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define oct2_MASK               oct2__MASK
#define oct2_SHIFT              oct2__SHIFT
#define oct2_WIDTH              1u

/* Interrupt constants */
#if defined(oct2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in oct2_SetInterruptMode() function.
     *  @{
     */
        #define oct2_INTR_NONE      (uint16)(0x0000u)
        #define oct2_INTR_RISING    (uint16)(0x0001u)
        #define oct2_INTR_FALLING   (uint16)(0x0002u)
        #define oct2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define oct2_INTR_MASK      (0x01u) 
#endif /* (oct2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define oct2_PS                     (* (reg8 *) oct2__PS)
/* Data Register */
#define oct2_DR                     (* (reg8 *) oct2__DR)
/* Port Number */
#define oct2_PRT_NUM                (* (reg8 *) oct2__PRT) 
/* Connect to Analog Globals */                                                  
#define oct2_AG                     (* (reg8 *) oct2__AG)                       
/* Analog MUX bux enable */
#define oct2_AMUX                   (* (reg8 *) oct2__AMUX) 
/* Bidirectional Enable */                                                        
#define oct2_BIE                    (* (reg8 *) oct2__BIE)
/* Bit-mask for Aliased Register Access */
#define oct2_BIT_MASK               (* (reg8 *) oct2__BIT_MASK)
/* Bypass Enable */
#define oct2_BYP                    (* (reg8 *) oct2__BYP)
/* Port wide control signals */                                                   
#define oct2_CTL                    (* (reg8 *) oct2__CTL)
/* Drive Modes */
#define oct2_DM0                    (* (reg8 *) oct2__DM0) 
#define oct2_DM1                    (* (reg8 *) oct2__DM1)
#define oct2_DM2                    (* (reg8 *) oct2__DM2) 
/* Input Buffer Disable Override */
#define oct2_INP_DIS                (* (reg8 *) oct2__INP_DIS)
/* LCD Common or Segment Drive */
#define oct2_LCD_COM_SEG            (* (reg8 *) oct2__LCD_COM_SEG)
/* Enable Segment LCD */
#define oct2_LCD_EN                 (* (reg8 *) oct2__LCD_EN)
/* Slew Rate Control */
#define oct2_SLW                    (* (reg8 *) oct2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define oct2_PRTDSI__CAPS_SEL       (* (reg8 *) oct2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define oct2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) oct2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define oct2_PRTDSI__OE_SEL0        (* (reg8 *) oct2__PRTDSI__OE_SEL0) 
#define oct2_PRTDSI__OE_SEL1        (* (reg8 *) oct2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define oct2_PRTDSI__OUT_SEL0       (* (reg8 *) oct2__PRTDSI__OUT_SEL0) 
#define oct2_PRTDSI__OUT_SEL1       (* (reg8 *) oct2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define oct2_PRTDSI__SYNC_OUT       (* (reg8 *) oct2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(oct2__SIO_CFG)
    #define oct2_SIO_HYST_EN        (* (reg8 *) oct2__SIO_HYST_EN)
    #define oct2_SIO_REG_HIFREQ     (* (reg8 *) oct2__SIO_REG_HIFREQ)
    #define oct2_SIO_CFG            (* (reg8 *) oct2__SIO_CFG)
    #define oct2_SIO_DIFF           (* (reg8 *) oct2__SIO_DIFF)
#endif /* (oct2__SIO_CFG) */

/* Interrupt Registers */
#if defined(oct2__INTSTAT)
    #define oct2_INTSTAT            (* (reg8 *) oct2__INTSTAT)
    #define oct2_SNAP               (* (reg8 *) oct2__SNAP)
    
	#define oct2_0_INTTYPE_REG 		(* (reg8 *) oct2__0__INTTYPE)
#endif /* (oct2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_oct2_H */


/* [] END OF FILE */
