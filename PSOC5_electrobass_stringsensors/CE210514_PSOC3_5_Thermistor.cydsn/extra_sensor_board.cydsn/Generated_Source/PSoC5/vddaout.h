/*******************************************************************************
* File Name: vddaout.h  
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

#if !defined(CY_PINS_vddaout_H) /* Pins vddaout_H */
#define CY_PINS_vddaout_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "vddaout_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 vddaout__PORT == 15 && ((vddaout__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    vddaout_Write(uint8 value);
void    vddaout_SetDriveMode(uint8 mode);
uint8   vddaout_ReadDataReg(void);
uint8   vddaout_Read(void);
void    vddaout_SetInterruptMode(uint16 position, uint16 mode);
uint8   vddaout_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the vddaout_SetDriveMode() function.
     *  @{
     */
        #define vddaout_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define vddaout_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define vddaout_DM_RES_UP          PIN_DM_RES_UP
        #define vddaout_DM_RES_DWN         PIN_DM_RES_DWN
        #define vddaout_DM_OD_LO           PIN_DM_OD_LO
        #define vddaout_DM_OD_HI           PIN_DM_OD_HI
        #define vddaout_DM_STRONG          PIN_DM_STRONG
        #define vddaout_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define vddaout_MASK               vddaout__MASK
#define vddaout_SHIFT              vddaout__SHIFT
#define vddaout_WIDTH              1u

/* Interrupt constants */
#if defined(vddaout__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in vddaout_SetInterruptMode() function.
     *  @{
     */
        #define vddaout_INTR_NONE      (uint16)(0x0000u)
        #define vddaout_INTR_RISING    (uint16)(0x0001u)
        #define vddaout_INTR_FALLING   (uint16)(0x0002u)
        #define vddaout_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define vddaout_INTR_MASK      (0x01u) 
#endif /* (vddaout__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define vddaout_PS                     (* (reg8 *) vddaout__PS)
/* Data Register */
#define vddaout_DR                     (* (reg8 *) vddaout__DR)
/* Port Number */
#define vddaout_PRT_NUM                (* (reg8 *) vddaout__PRT) 
/* Connect to Analog Globals */                                                  
#define vddaout_AG                     (* (reg8 *) vddaout__AG)                       
/* Analog MUX bux enable */
#define vddaout_AMUX                   (* (reg8 *) vddaout__AMUX) 
/* Bidirectional Enable */                                                        
#define vddaout_BIE                    (* (reg8 *) vddaout__BIE)
/* Bit-mask for Aliased Register Access */
#define vddaout_BIT_MASK               (* (reg8 *) vddaout__BIT_MASK)
/* Bypass Enable */
#define vddaout_BYP                    (* (reg8 *) vddaout__BYP)
/* Port wide control signals */                                                   
#define vddaout_CTL                    (* (reg8 *) vddaout__CTL)
/* Drive Modes */
#define vddaout_DM0                    (* (reg8 *) vddaout__DM0) 
#define vddaout_DM1                    (* (reg8 *) vddaout__DM1)
#define vddaout_DM2                    (* (reg8 *) vddaout__DM2) 
/* Input Buffer Disable Override */
#define vddaout_INP_DIS                (* (reg8 *) vddaout__INP_DIS)
/* LCD Common or Segment Drive */
#define vddaout_LCD_COM_SEG            (* (reg8 *) vddaout__LCD_COM_SEG)
/* Enable Segment LCD */
#define vddaout_LCD_EN                 (* (reg8 *) vddaout__LCD_EN)
/* Slew Rate Control */
#define vddaout_SLW                    (* (reg8 *) vddaout__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define vddaout_PRTDSI__CAPS_SEL       (* (reg8 *) vddaout__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define vddaout_PRTDSI__DBL_SYNC_IN    (* (reg8 *) vddaout__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define vddaout_PRTDSI__OE_SEL0        (* (reg8 *) vddaout__PRTDSI__OE_SEL0) 
#define vddaout_PRTDSI__OE_SEL1        (* (reg8 *) vddaout__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define vddaout_PRTDSI__OUT_SEL0       (* (reg8 *) vddaout__PRTDSI__OUT_SEL0) 
#define vddaout_PRTDSI__OUT_SEL1       (* (reg8 *) vddaout__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define vddaout_PRTDSI__SYNC_OUT       (* (reg8 *) vddaout__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(vddaout__SIO_CFG)
    #define vddaout_SIO_HYST_EN        (* (reg8 *) vddaout__SIO_HYST_EN)
    #define vddaout_SIO_REG_HIFREQ     (* (reg8 *) vddaout__SIO_REG_HIFREQ)
    #define vddaout_SIO_CFG            (* (reg8 *) vddaout__SIO_CFG)
    #define vddaout_SIO_DIFF           (* (reg8 *) vddaout__SIO_DIFF)
#endif /* (vddaout__SIO_CFG) */

/* Interrupt Registers */
#if defined(vddaout__INTSTAT)
    #define vddaout_INTSTAT            (* (reg8 *) vddaout__INTSTAT)
    #define vddaout_SNAP               (* (reg8 *) vddaout__SNAP)
    
	#define vddaout_0_INTTYPE_REG 		(* (reg8 *) vddaout__0__INTTYPE)
#endif /* (vddaout__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_vddaout_H */


/* [] END OF FILE */
