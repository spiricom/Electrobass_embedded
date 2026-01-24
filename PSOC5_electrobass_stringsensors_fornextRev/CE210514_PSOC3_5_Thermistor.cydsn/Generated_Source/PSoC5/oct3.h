/*******************************************************************************
* File Name: oct3.h  
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

#if !defined(CY_PINS_oct3_H) /* Pins oct3_H */
#define CY_PINS_oct3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "oct3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 oct3__PORT == 15 && ((oct3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    oct3_Write(uint8 value);
void    oct3_SetDriveMode(uint8 mode);
uint8   oct3_ReadDataReg(void);
uint8   oct3_Read(void);
void    oct3_SetInterruptMode(uint16 position, uint16 mode);
uint8   oct3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the oct3_SetDriveMode() function.
     *  @{
     */
        #define oct3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define oct3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define oct3_DM_RES_UP          PIN_DM_RES_UP
        #define oct3_DM_RES_DWN         PIN_DM_RES_DWN
        #define oct3_DM_OD_LO           PIN_DM_OD_LO
        #define oct3_DM_OD_HI           PIN_DM_OD_HI
        #define oct3_DM_STRONG          PIN_DM_STRONG
        #define oct3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define oct3_MASK               oct3__MASK
#define oct3_SHIFT              oct3__SHIFT
#define oct3_WIDTH              1u

/* Interrupt constants */
#if defined(oct3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in oct3_SetInterruptMode() function.
     *  @{
     */
        #define oct3_INTR_NONE      (uint16)(0x0000u)
        #define oct3_INTR_RISING    (uint16)(0x0001u)
        #define oct3_INTR_FALLING   (uint16)(0x0002u)
        #define oct3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define oct3_INTR_MASK      (0x01u) 
#endif /* (oct3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define oct3_PS                     (* (reg8 *) oct3__PS)
/* Data Register */
#define oct3_DR                     (* (reg8 *) oct3__DR)
/* Port Number */
#define oct3_PRT_NUM                (* (reg8 *) oct3__PRT) 
/* Connect to Analog Globals */                                                  
#define oct3_AG                     (* (reg8 *) oct3__AG)                       
/* Analog MUX bux enable */
#define oct3_AMUX                   (* (reg8 *) oct3__AMUX) 
/* Bidirectional Enable */                                                        
#define oct3_BIE                    (* (reg8 *) oct3__BIE)
/* Bit-mask for Aliased Register Access */
#define oct3_BIT_MASK               (* (reg8 *) oct3__BIT_MASK)
/* Bypass Enable */
#define oct3_BYP                    (* (reg8 *) oct3__BYP)
/* Port wide control signals */                                                   
#define oct3_CTL                    (* (reg8 *) oct3__CTL)
/* Drive Modes */
#define oct3_DM0                    (* (reg8 *) oct3__DM0) 
#define oct3_DM1                    (* (reg8 *) oct3__DM1)
#define oct3_DM2                    (* (reg8 *) oct3__DM2) 
/* Input Buffer Disable Override */
#define oct3_INP_DIS                (* (reg8 *) oct3__INP_DIS)
/* LCD Common or Segment Drive */
#define oct3_LCD_COM_SEG            (* (reg8 *) oct3__LCD_COM_SEG)
/* Enable Segment LCD */
#define oct3_LCD_EN                 (* (reg8 *) oct3__LCD_EN)
/* Slew Rate Control */
#define oct3_SLW                    (* (reg8 *) oct3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define oct3_PRTDSI__CAPS_SEL       (* (reg8 *) oct3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define oct3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) oct3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define oct3_PRTDSI__OE_SEL0        (* (reg8 *) oct3__PRTDSI__OE_SEL0) 
#define oct3_PRTDSI__OE_SEL1        (* (reg8 *) oct3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define oct3_PRTDSI__OUT_SEL0       (* (reg8 *) oct3__PRTDSI__OUT_SEL0) 
#define oct3_PRTDSI__OUT_SEL1       (* (reg8 *) oct3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define oct3_PRTDSI__SYNC_OUT       (* (reg8 *) oct3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(oct3__SIO_CFG)
    #define oct3_SIO_HYST_EN        (* (reg8 *) oct3__SIO_HYST_EN)
    #define oct3_SIO_REG_HIFREQ     (* (reg8 *) oct3__SIO_REG_HIFREQ)
    #define oct3_SIO_CFG            (* (reg8 *) oct3__SIO_CFG)
    #define oct3_SIO_DIFF           (* (reg8 *) oct3__SIO_DIFF)
#endif /* (oct3__SIO_CFG) */

/* Interrupt Registers */
#if defined(oct3__INTSTAT)
    #define oct3_INTSTAT            (* (reg8 *) oct3__INTSTAT)
    #define oct3_SNAP               (* (reg8 *) oct3__SNAP)
    
	#define oct3_0_INTTYPE_REG 		(* (reg8 *) oct3__0__INTTYPE)
#endif /* (oct3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_oct3_H */


/* [] END OF FILE */
