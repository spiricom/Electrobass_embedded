/*******************************************************************************
* File Name: oct6.h  
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

#if !defined(CY_PINS_oct6_H) /* Pins oct6_H */
#define CY_PINS_oct6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "oct6_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 oct6__PORT == 15 && ((oct6__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    oct6_Write(uint8 value);
void    oct6_SetDriveMode(uint8 mode);
uint8   oct6_ReadDataReg(void);
uint8   oct6_Read(void);
void    oct6_SetInterruptMode(uint16 position, uint16 mode);
uint8   oct6_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the oct6_SetDriveMode() function.
     *  @{
     */
        #define oct6_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define oct6_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define oct6_DM_RES_UP          PIN_DM_RES_UP
        #define oct6_DM_RES_DWN         PIN_DM_RES_DWN
        #define oct6_DM_OD_LO           PIN_DM_OD_LO
        #define oct6_DM_OD_HI           PIN_DM_OD_HI
        #define oct6_DM_STRONG          PIN_DM_STRONG
        #define oct6_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define oct6_MASK               oct6__MASK
#define oct6_SHIFT              oct6__SHIFT
#define oct6_WIDTH              1u

/* Interrupt constants */
#if defined(oct6__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in oct6_SetInterruptMode() function.
     *  @{
     */
        #define oct6_INTR_NONE      (uint16)(0x0000u)
        #define oct6_INTR_RISING    (uint16)(0x0001u)
        #define oct6_INTR_FALLING   (uint16)(0x0002u)
        #define oct6_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define oct6_INTR_MASK      (0x01u) 
#endif /* (oct6__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define oct6_PS                     (* (reg8 *) oct6__PS)
/* Data Register */
#define oct6_DR                     (* (reg8 *) oct6__DR)
/* Port Number */
#define oct6_PRT_NUM                (* (reg8 *) oct6__PRT) 
/* Connect to Analog Globals */                                                  
#define oct6_AG                     (* (reg8 *) oct6__AG)                       
/* Analog MUX bux enable */
#define oct6_AMUX                   (* (reg8 *) oct6__AMUX) 
/* Bidirectional Enable */                                                        
#define oct6_BIE                    (* (reg8 *) oct6__BIE)
/* Bit-mask for Aliased Register Access */
#define oct6_BIT_MASK               (* (reg8 *) oct6__BIT_MASK)
/* Bypass Enable */
#define oct6_BYP                    (* (reg8 *) oct6__BYP)
/* Port wide control signals */                                                   
#define oct6_CTL                    (* (reg8 *) oct6__CTL)
/* Drive Modes */
#define oct6_DM0                    (* (reg8 *) oct6__DM0) 
#define oct6_DM1                    (* (reg8 *) oct6__DM1)
#define oct6_DM2                    (* (reg8 *) oct6__DM2) 
/* Input Buffer Disable Override */
#define oct6_INP_DIS                (* (reg8 *) oct6__INP_DIS)
/* LCD Common or Segment Drive */
#define oct6_LCD_COM_SEG            (* (reg8 *) oct6__LCD_COM_SEG)
/* Enable Segment LCD */
#define oct6_LCD_EN                 (* (reg8 *) oct6__LCD_EN)
/* Slew Rate Control */
#define oct6_SLW                    (* (reg8 *) oct6__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define oct6_PRTDSI__CAPS_SEL       (* (reg8 *) oct6__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define oct6_PRTDSI__DBL_SYNC_IN    (* (reg8 *) oct6__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define oct6_PRTDSI__OE_SEL0        (* (reg8 *) oct6__PRTDSI__OE_SEL0) 
#define oct6_PRTDSI__OE_SEL1        (* (reg8 *) oct6__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define oct6_PRTDSI__OUT_SEL0       (* (reg8 *) oct6__PRTDSI__OUT_SEL0) 
#define oct6_PRTDSI__OUT_SEL1       (* (reg8 *) oct6__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define oct6_PRTDSI__SYNC_OUT       (* (reg8 *) oct6__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(oct6__SIO_CFG)
    #define oct6_SIO_HYST_EN        (* (reg8 *) oct6__SIO_HYST_EN)
    #define oct6_SIO_REG_HIFREQ     (* (reg8 *) oct6__SIO_REG_HIFREQ)
    #define oct6_SIO_CFG            (* (reg8 *) oct6__SIO_CFG)
    #define oct6_SIO_DIFF           (* (reg8 *) oct6__SIO_DIFF)
#endif /* (oct6__SIO_CFG) */

/* Interrupt Registers */
#if defined(oct6__INTSTAT)
    #define oct6_INTSTAT            (* (reg8 *) oct6__INTSTAT)
    #define oct6_SNAP               (* (reg8 *) oct6__SNAP)
    
	#define oct6_0_INTTYPE_REG 		(* (reg8 *) oct6__0__INTTYPE)
#endif /* (oct6__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_oct6_H */


/* [] END OF FILE */
