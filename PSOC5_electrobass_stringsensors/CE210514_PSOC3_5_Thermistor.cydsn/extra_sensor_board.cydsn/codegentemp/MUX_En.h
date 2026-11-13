/*******************************************************************************
* File Name: MUX_En.h  
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

#if !defined(CY_PINS_MUX_En_H) /* Pins MUX_En_H */
#define CY_PINS_MUX_En_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MUX_En_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MUX_En__PORT == 15 && ((MUX_En__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MUX_En_Write(uint8 value);
void    MUX_En_SetDriveMode(uint8 mode);
uint8   MUX_En_ReadDataReg(void);
uint8   MUX_En_Read(void);
void    MUX_En_SetInterruptMode(uint16 position, uint16 mode);
uint8   MUX_En_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MUX_En_SetDriveMode() function.
     *  @{
     */
        #define MUX_En_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MUX_En_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MUX_En_DM_RES_UP          PIN_DM_RES_UP
        #define MUX_En_DM_RES_DWN         PIN_DM_RES_DWN
        #define MUX_En_DM_OD_LO           PIN_DM_OD_LO
        #define MUX_En_DM_OD_HI           PIN_DM_OD_HI
        #define MUX_En_DM_STRONG          PIN_DM_STRONG
        #define MUX_En_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MUX_En_MASK               MUX_En__MASK
#define MUX_En_SHIFT              MUX_En__SHIFT
#define MUX_En_WIDTH              1u

/* Interrupt constants */
#if defined(MUX_En__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MUX_En_SetInterruptMode() function.
     *  @{
     */
        #define MUX_En_INTR_NONE      (uint16)(0x0000u)
        #define MUX_En_INTR_RISING    (uint16)(0x0001u)
        #define MUX_En_INTR_FALLING   (uint16)(0x0002u)
        #define MUX_En_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MUX_En_INTR_MASK      (0x01u) 
#endif /* (MUX_En__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MUX_En_PS                     (* (reg8 *) MUX_En__PS)
/* Data Register */
#define MUX_En_DR                     (* (reg8 *) MUX_En__DR)
/* Port Number */
#define MUX_En_PRT_NUM                (* (reg8 *) MUX_En__PRT) 
/* Connect to Analog Globals */                                                  
#define MUX_En_AG                     (* (reg8 *) MUX_En__AG)                       
/* Analog MUX bux enable */
#define MUX_En_AMUX                   (* (reg8 *) MUX_En__AMUX) 
/* Bidirectional Enable */                                                        
#define MUX_En_BIE                    (* (reg8 *) MUX_En__BIE)
/* Bit-mask for Aliased Register Access */
#define MUX_En_BIT_MASK               (* (reg8 *) MUX_En__BIT_MASK)
/* Bypass Enable */
#define MUX_En_BYP                    (* (reg8 *) MUX_En__BYP)
/* Port wide control signals */                                                   
#define MUX_En_CTL                    (* (reg8 *) MUX_En__CTL)
/* Drive Modes */
#define MUX_En_DM0                    (* (reg8 *) MUX_En__DM0) 
#define MUX_En_DM1                    (* (reg8 *) MUX_En__DM1)
#define MUX_En_DM2                    (* (reg8 *) MUX_En__DM2) 
/* Input Buffer Disable Override */
#define MUX_En_INP_DIS                (* (reg8 *) MUX_En__INP_DIS)
/* LCD Common or Segment Drive */
#define MUX_En_LCD_COM_SEG            (* (reg8 *) MUX_En__LCD_COM_SEG)
/* Enable Segment LCD */
#define MUX_En_LCD_EN                 (* (reg8 *) MUX_En__LCD_EN)
/* Slew Rate Control */
#define MUX_En_SLW                    (* (reg8 *) MUX_En__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MUX_En_PRTDSI__CAPS_SEL       (* (reg8 *) MUX_En__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MUX_En_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MUX_En__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MUX_En_PRTDSI__OE_SEL0        (* (reg8 *) MUX_En__PRTDSI__OE_SEL0) 
#define MUX_En_PRTDSI__OE_SEL1        (* (reg8 *) MUX_En__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MUX_En_PRTDSI__OUT_SEL0       (* (reg8 *) MUX_En__PRTDSI__OUT_SEL0) 
#define MUX_En_PRTDSI__OUT_SEL1       (* (reg8 *) MUX_En__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MUX_En_PRTDSI__SYNC_OUT       (* (reg8 *) MUX_En__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MUX_En__SIO_CFG)
    #define MUX_En_SIO_HYST_EN        (* (reg8 *) MUX_En__SIO_HYST_EN)
    #define MUX_En_SIO_REG_HIFREQ     (* (reg8 *) MUX_En__SIO_REG_HIFREQ)
    #define MUX_En_SIO_CFG            (* (reg8 *) MUX_En__SIO_CFG)
    #define MUX_En_SIO_DIFF           (* (reg8 *) MUX_En__SIO_DIFF)
#endif /* (MUX_En__SIO_CFG) */

/* Interrupt Registers */
#if defined(MUX_En__INTSTAT)
    #define MUX_En_INTSTAT            (* (reg8 *) MUX_En__INTSTAT)
    #define MUX_En_SNAP               (* (reg8 *) MUX_En__SNAP)
    
	#define MUX_En_0_INTTYPE_REG 		(* (reg8 *) MUX_En__0__INTTYPE)
#endif /* (MUX_En__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MUX_En_H */


/* [] END OF FILE */
