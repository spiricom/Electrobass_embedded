/*******************************************************************************
* File Name: necksense1.h  
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

#if !defined(CY_PINS_necksense1_H) /* Pins necksense1_H */
#define CY_PINS_necksense1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "necksense1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 necksense1__PORT == 15 && ((necksense1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    necksense1_Write(uint8 value);
void    necksense1_SetDriveMode(uint8 mode);
uint8   necksense1_ReadDataReg(void);
uint8   necksense1_Read(void);
void    necksense1_SetInterruptMode(uint16 position, uint16 mode);
uint8   necksense1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the necksense1_SetDriveMode() function.
     *  @{
     */
        #define necksense1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define necksense1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define necksense1_DM_RES_UP          PIN_DM_RES_UP
        #define necksense1_DM_RES_DWN         PIN_DM_RES_DWN
        #define necksense1_DM_OD_LO           PIN_DM_OD_LO
        #define necksense1_DM_OD_HI           PIN_DM_OD_HI
        #define necksense1_DM_STRONG          PIN_DM_STRONG
        #define necksense1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define necksense1_MASK               necksense1__MASK
#define necksense1_SHIFT              necksense1__SHIFT
#define necksense1_WIDTH              1u

/* Interrupt constants */
#if defined(necksense1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in necksense1_SetInterruptMode() function.
     *  @{
     */
        #define necksense1_INTR_NONE      (uint16)(0x0000u)
        #define necksense1_INTR_RISING    (uint16)(0x0001u)
        #define necksense1_INTR_FALLING   (uint16)(0x0002u)
        #define necksense1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define necksense1_INTR_MASK      (0x01u) 
#endif /* (necksense1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define necksense1_PS                     (* (reg8 *) necksense1__PS)
/* Data Register */
#define necksense1_DR                     (* (reg8 *) necksense1__DR)
/* Port Number */
#define necksense1_PRT_NUM                (* (reg8 *) necksense1__PRT) 
/* Connect to Analog Globals */                                                  
#define necksense1_AG                     (* (reg8 *) necksense1__AG)                       
/* Analog MUX bux enable */
#define necksense1_AMUX                   (* (reg8 *) necksense1__AMUX) 
/* Bidirectional Enable */                                                        
#define necksense1_BIE                    (* (reg8 *) necksense1__BIE)
/* Bit-mask for Aliased Register Access */
#define necksense1_BIT_MASK               (* (reg8 *) necksense1__BIT_MASK)
/* Bypass Enable */
#define necksense1_BYP                    (* (reg8 *) necksense1__BYP)
/* Port wide control signals */                                                   
#define necksense1_CTL                    (* (reg8 *) necksense1__CTL)
/* Drive Modes */
#define necksense1_DM0                    (* (reg8 *) necksense1__DM0) 
#define necksense1_DM1                    (* (reg8 *) necksense1__DM1)
#define necksense1_DM2                    (* (reg8 *) necksense1__DM2) 
/* Input Buffer Disable Override */
#define necksense1_INP_DIS                (* (reg8 *) necksense1__INP_DIS)
/* LCD Common or Segment Drive */
#define necksense1_LCD_COM_SEG            (* (reg8 *) necksense1__LCD_COM_SEG)
/* Enable Segment LCD */
#define necksense1_LCD_EN                 (* (reg8 *) necksense1__LCD_EN)
/* Slew Rate Control */
#define necksense1_SLW                    (* (reg8 *) necksense1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define necksense1_PRTDSI__CAPS_SEL       (* (reg8 *) necksense1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define necksense1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) necksense1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define necksense1_PRTDSI__OE_SEL0        (* (reg8 *) necksense1__PRTDSI__OE_SEL0) 
#define necksense1_PRTDSI__OE_SEL1        (* (reg8 *) necksense1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define necksense1_PRTDSI__OUT_SEL0       (* (reg8 *) necksense1__PRTDSI__OUT_SEL0) 
#define necksense1_PRTDSI__OUT_SEL1       (* (reg8 *) necksense1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define necksense1_PRTDSI__SYNC_OUT       (* (reg8 *) necksense1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(necksense1__SIO_CFG)
    #define necksense1_SIO_HYST_EN        (* (reg8 *) necksense1__SIO_HYST_EN)
    #define necksense1_SIO_REG_HIFREQ     (* (reg8 *) necksense1__SIO_REG_HIFREQ)
    #define necksense1_SIO_CFG            (* (reg8 *) necksense1__SIO_CFG)
    #define necksense1_SIO_DIFF           (* (reg8 *) necksense1__SIO_DIFF)
#endif /* (necksense1__SIO_CFG) */

/* Interrupt Registers */
#if defined(necksense1__INTSTAT)
    #define necksense1_INTSTAT            (* (reg8 *) necksense1__INTSTAT)
    #define necksense1_SNAP               (* (reg8 *) necksense1__SNAP)
    
	#define necksense1_0_INTTYPE_REG 		(* (reg8 *) necksense1__0__INTTYPE)
#endif /* (necksense1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_necksense1_H */


/* [] END OF FILE */
