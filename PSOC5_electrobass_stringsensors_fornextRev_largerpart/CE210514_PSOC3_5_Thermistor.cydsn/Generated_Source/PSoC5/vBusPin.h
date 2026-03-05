/*******************************************************************************
* File Name: vBusPin.h  
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

#if !defined(CY_PINS_vBusPin_H) /* Pins vBusPin_H */
#define CY_PINS_vBusPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "vBusPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 vBusPin__PORT == 15 && ((vBusPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    vBusPin_Write(uint8 value);
void    vBusPin_SetDriveMode(uint8 mode);
uint8   vBusPin_ReadDataReg(void);
uint8   vBusPin_Read(void);
void    vBusPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   vBusPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the vBusPin_SetDriveMode() function.
     *  @{
     */
        #define vBusPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define vBusPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define vBusPin_DM_RES_UP          PIN_DM_RES_UP
        #define vBusPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define vBusPin_DM_OD_LO           PIN_DM_OD_LO
        #define vBusPin_DM_OD_HI           PIN_DM_OD_HI
        #define vBusPin_DM_STRONG          PIN_DM_STRONG
        #define vBusPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define vBusPin_MASK               vBusPin__MASK
#define vBusPin_SHIFT              vBusPin__SHIFT
#define vBusPin_WIDTH              1u

/* Interrupt constants */
#if defined(vBusPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in vBusPin_SetInterruptMode() function.
     *  @{
     */
        #define vBusPin_INTR_NONE      (uint16)(0x0000u)
        #define vBusPin_INTR_RISING    (uint16)(0x0001u)
        #define vBusPin_INTR_FALLING   (uint16)(0x0002u)
        #define vBusPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define vBusPin_INTR_MASK      (0x01u) 
#endif /* (vBusPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define vBusPin_PS                     (* (reg8 *) vBusPin__PS)
/* Data Register */
#define vBusPin_DR                     (* (reg8 *) vBusPin__DR)
/* Port Number */
#define vBusPin_PRT_NUM                (* (reg8 *) vBusPin__PRT) 
/* Connect to Analog Globals */                                                  
#define vBusPin_AG                     (* (reg8 *) vBusPin__AG)                       
/* Analog MUX bux enable */
#define vBusPin_AMUX                   (* (reg8 *) vBusPin__AMUX) 
/* Bidirectional Enable */                                                        
#define vBusPin_BIE                    (* (reg8 *) vBusPin__BIE)
/* Bit-mask for Aliased Register Access */
#define vBusPin_BIT_MASK               (* (reg8 *) vBusPin__BIT_MASK)
/* Bypass Enable */
#define vBusPin_BYP                    (* (reg8 *) vBusPin__BYP)
/* Port wide control signals */                                                   
#define vBusPin_CTL                    (* (reg8 *) vBusPin__CTL)
/* Drive Modes */
#define vBusPin_DM0                    (* (reg8 *) vBusPin__DM0) 
#define vBusPin_DM1                    (* (reg8 *) vBusPin__DM1)
#define vBusPin_DM2                    (* (reg8 *) vBusPin__DM2) 
/* Input Buffer Disable Override */
#define vBusPin_INP_DIS                (* (reg8 *) vBusPin__INP_DIS)
/* LCD Common or Segment Drive */
#define vBusPin_LCD_COM_SEG            (* (reg8 *) vBusPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define vBusPin_LCD_EN                 (* (reg8 *) vBusPin__LCD_EN)
/* Slew Rate Control */
#define vBusPin_SLW                    (* (reg8 *) vBusPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define vBusPin_PRTDSI__CAPS_SEL       (* (reg8 *) vBusPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define vBusPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) vBusPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define vBusPin_PRTDSI__OE_SEL0        (* (reg8 *) vBusPin__PRTDSI__OE_SEL0) 
#define vBusPin_PRTDSI__OE_SEL1        (* (reg8 *) vBusPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define vBusPin_PRTDSI__OUT_SEL0       (* (reg8 *) vBusPin__PRTDSI__OUT_SEL0) 
#define vBusPin_PRTDSI__OUT_SEL1       (* (reg8 *) vBusPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define vBusPin_PRTDSI__SYNC_OUT       (* (reg8 *) vBusPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(vBusPin__SIO_CFG)
    #define vBusPin_SIO_HYST_EN        (* (reg8 *) vBusPin__SIO_HYST_EN)
    #define vBusPin_SIO_REG_HIFREQ     (* (reg8 *) vBusPin__SIO_REG_HIFREQ)
    #define vBusPin_SIO_CFG            (* (reg8 *) vBusPin__SIO_CFG)
    #define vBusPin_SIO_DIFF           (* (reg8 *) vBusPin__SIO_DIFF)
#endif /* (vBusPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(vBusPin__INTSTAT)
    #define vBusPin_INTSTAT            (* (reg8 *) vBusPin__INTSTAT)
    #define vBusPin_SNAP               (* (reg8 *) vBusPin__SNAP)
    
	#define vBusPin_0_INTTYPE_REG 		(* (reg8 *) vBusPin__0__INTTYPE)
#endif /* (vBusPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_vBusPin_H */


/* [] END OF FILE */
