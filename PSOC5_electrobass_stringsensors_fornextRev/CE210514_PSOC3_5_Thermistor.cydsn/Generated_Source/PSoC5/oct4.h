/*******************************************************************************
* File Name: oct4.h  
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

#if !defined(CY_PINS_oct4_H) /* Pins oct4_H */
#define CY_PINS_oct4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "oct4_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 oct4__PORT == 15 && ((oct4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    oct4_Write(uint8 value);
void    oct4_SetDriveMode(uint8 mode);
uint8   oct4_ReadDataReg(void);
uint8   oct4_Read(void);
void    oct4_SetInterruptMode(uint16 position, uint16 mode);
uint8   oct4_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the oct4_SetDriveMode() function.
     *  @{
     */
        #define oct4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define oct4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define oct4_DM_RES_UP          PIN_DM_RES_UP
        #define oct4_DM_RES_DWN         PIN_DM_RES_DWN
        #define oct4_DM_OD_LO           PIN_DM_OD_LO
        #define oct4_DM_OD_HI           PIN_DM_OD_HI
        #define oct4_DM_STRONG          PIN_DM_STRONG
        #define oct4_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define oct4_MASK               oct4__MASK
#define oct4_SHIFT              oct4__SHIFT
#define oct4_WIDTH              1u

/* Interrupt constants */
#if defined(oct4__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in oct4_SetInterruptMode() function.
     *  @{
     */
        #define oct4_INTR_NONE      (uint16)(0x0000u)
        #define oct4_INTR_RISING    (uint16)(0x0001u)
        #define oct4_INTR_FALLING   (uint16)(0x0002u)
        #define oct4_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define oct4_INTR_MASK      (0x01u) 
#endif /* (oct4__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define oct4_PS                     (* (reg8 *) oct4__PS)
/* Data Register */
#define oct4_DR                     (* (reg8 *) oct4__DR)
/* Port Number */
#define oct4_PRT_NUM                (* (reg8 *) oct4__PRT) 
/* Connect to Analog Globals */                                                  
#define oct4_AG                     (* (reg8 *) oct4__AG)                       
/* Analog MUX bux enable */
#define oct4_AMUX                   (* (reg8 *) oct4__AMUX) 
/* Bidirectional Enable */                                                        
#define oct4_BIE                    (* (reg8 *) oct4__BIE)
/* Bit-mask for Aliased Register Access */
#define oct4_BIT_MASK               (* (reg8 *) oct4__BIT_MASK)
/* Bypass Enable */
#define oct4_BYP                    (* (reg8 *) oct4__BYP)
/* Port wide control signals */                                                   
#define oct4_CTL                    (* (reg8 *) oct4__CTL)
/* Drive Modes */
#define oct4_DM0                    (* (reg8 *) oct4__DM0) 
#define oct4_DM1                    (* (reg8 *) oct4__DM1)
#define oct4_DM2                    (* (reg8 *) oct4__DM2) 
/* Input Buffer Disable Override */
#define oct4_INP_DIS                (* (reg8 *) oct4__INP_DIS)
/* LCD Common or Segment Drive */
#define oct4_LCD_COM_SEG            (* (reg8 *) oct4__LCD_COM_SEG)
/* Enable Segment LCD */
#define oct4_LCD_EN                 (* (reg8 *) oct4__LCD_EN)
/* Slew Rate Control */
#define oct4_SLW                    (* (reg8 *) oct4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define oct4_PRTDSI__CAPS_SEL       (* (reg8 *) oct4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define oct4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) oct4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define oct4_PRTDSI__OE_SEL0        (* (reg8 *) oct4__PRTDSI__OE_SEL0) 
#define oct4_PRTDSI__OE_SEL1        (* (reg8 *) oct4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define oct4_PRTDSI__OUT_SEL0       (* (reg8 *) oct4__PRTDSI__OUT_SEL0) 
#define oct4_PRTDSI__OUT_SEL1       (* (reg8 *) oct4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define oct4_PRTDSI__SYNC_OUT       (* (reg8 *) oct4__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(oct4__SIO_CFG)
    #define oct4_SIO_HYST_EN        (* (reg8 *) oct4__SIO_HYST_EN)
    #define oct4_SIO_REG_HIFREQ     (* (reg8 *) oct4__SIO_REG_HIFREQ)
    #define oct4_SIO_CFG            (* (reg8 *) oct4__SIO_CFG)
    #define oct4_SIO_DIFF           (* (reg8 *) oct4__SIO_DIFF)
#endif /* (oct4__SIO_CFG) */

/* Interrupt Registers */
#if defined(oct4__INTSTAT)
    #define oct4_INTSTAT            (* (reg8 *) oct4__INTSTAT)
    #define oct4_SNAP               (* (reg8 *) oct4__SNAP)
    
	#define oct4_0_INTTYPE_REG 		(* (reg8 *) oct4__0__INTTYPE)
#endif /* (oct4__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_oct4_H */


/* [] END OF FILE */
