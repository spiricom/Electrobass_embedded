/*******************************************************************************
* File Name: necksense3.h  
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

#if !defined(CY_PINS_necksense3_H) /* Pins necksense3_H */
#define CY_PINS_necksense3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "necksense3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 necksense3__PORT == 15 && ((necksense3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    necksense3_Write(uint8 value);
void    necksense3_SetDriveMode(uint8 mode);
uint8   necksense3_ReadDataReg(void);
uint8   necksense3_Read(void);
void    necksense3_SetInterruptMode(uint16 position, uint16 mode);
uint8   necksense3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the necksense3_SetDriveMode() function.
     *  @{
     */
        #define necksense3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define necksense3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define necksense3_DM_RES_UP          PIN_DM_RES_UP
        #define necksense3_DM_RES_DWN         PIN_DM_RES_DWN
        #define necksense3_DM_OD_LO           PIN_DM_OD_LO
        #define necksense3_DM_OD_HI           PIN_DM_OD_HI
        #define necksense3_DM_STRONG          PIN_DM_STRONG
        #define necksense3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define necksense3_MASK               necksense3__MASK
#define necksense3_SHIFT              necksense3__SHIFT
#define necksense3_WIDTH              1u

/* Interrupt constants */
#if defined(necksense3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in necksense3_SetInterruptMode() function.
     *  @{
     */
        #define necksense3_INTR_NONE      (uint16)(0x0000u)
        #define necksense3_INTR_RISING    (uint16)(0x0001u)
        #define necksense3_INTR_FALLING   (uint16)(0x0002u)
        #define necksense3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define necksense3_INTR_MASK      (0x01u) 
#endif /* (necksense3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define necksense3_PS                     (* (reg8 *) necksense3__PS)
/* Data Register */
#define necksense3_DR                     (* (reg8 *) necksense3__DR)
/* Port Number */
#define necksense3_PRT_NUM                (* (reg8 *) necksense3__PRT) 
/* Connect to Analog Globals */                                                  
#define necksense3_AG                     (* (reg8 *) necksense3__AG)                       
/* Analog MUX bux enable */
#define necksense3_AMUX                   (* (reg8 *) necksense3__AMUX) 
/* Bidirectional Enable */                                                        
#define necksense3_BIE                    (* (reg8 *) necksense3__BIE)
/* Bit-mask for Aliased Register Access */
#define necksense3_BIT_MASK               (* (reg8 *) necksense3__BIT_MASK)
/* Bypass Enable */
#define necksense3_BYP                    (* (reg8 *) necksense3__BYP)
/* Port wide control signals */                                                   
#define necksense3_CTL                    (* (reg8 *) necksense3__CTL)
/* Drive Modes */
#define necksense3_DM0                    (* (reg8 *) necksense3__DM0) 
#define necksense3_DM1                    (* (reg8 *) necksense3__DM1)
#define necksense3_DM2                    (* (reg8 *) necksense3__DM2) 
/* Input Buffer Disable Override */
#define necksense3_INP_DIS                (* (reg8 *) necksense3__INP_DIS)
/* LCD Common or Segment Drive */
#define necksense3_LCD_COM_SEG            (* (reg8 *) necksense3__LCD_COM_SEG)
/* Enable Segment LCD */
#define necksense3_LCD_EN                 (* (reg8 *) necksense3__LCD_EN)
/* Slew Rate Control */
#define necksense3_SLW                    (* (reg8 *) necksense3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define necksense3_PRTDSI__CAPS_SEL       (* (reg8 *) necksense3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define necksense3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) necksense3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define necksense3_PRTDSI__OE_SEL0        (* (reg8 *) necksense3__PRTDSI__OE_SEL0) 
#define necksense3_PRTDSI__OE_SEL1        (* (reg8 *) necksense3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define necksense3_PRTDSI__OUT_SEL0       (* (reg8 *) necksense3__PRTDSI__OUT_SEL0) 
#define necksense3_PRTDSI__OUT_SEL1       (* (reg8 *) necksense3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define necksense3_PRTDSI__SYNC_OUT       (* (reg8 *) necksense3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(necksense3__SIO_CFG)
    #define necksense3_SIO_HYST_EN        (* (reg8 *) necksense3__SIO_HYST_EN)
    #define necksense3_SIO_REG_HIFREQ     (* (reg8 *) necksense3__SIO_REG_HIFREQ)
    #define necksense3_SIO_CFG            (* (reg8 *) necksense3__SIO_CFG)
    #define necksense3_SIO_DIFF           (* (reg8 *) necksense3__SIO_DIFF)
#endif /* (necksense3__SIO_CFG) */

/* Interrupt Registers */
#if defined(necksense3__INTSTAT)
    #define necksense3_INTSTAT            (* (reg8 *) necksense3__INTSTAT)
    #define necksense3_SNAP               (* (reg8 *) necksense3__SNAP)
    
	#define necksense3_0_INTTYPE_REG 		(* (reg8 *) necksense3__0__INTTYPE)
#endif /* (necksense3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_necksense3_H */


/* [] END OF FILE */
