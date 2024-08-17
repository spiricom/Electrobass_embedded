/*******************************************************************************
* File Name: necksense4.h  
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

#if !defined(CY_PINS_necksense4_H) /* Pins necksense4_H */
#define CY_PINS_necksense4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "necksense4_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 necksense4__PORT == 15 && ((necksense4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    necksense4_Write(uint8 value);
void    necksense4_SetDriveMode(uint8 mode);
uint8   necksense4_ReadDataReg(void);
uint8   necksense4_Read(void);
void    necksense4_SetInterruptMode(uint16 position, uint16 mode);
uint8   necksense4_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the necksense4_SetDriveMode() function.
     *  @{
     */
        #define necksense4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define necksense4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define necksense4_DM_RES_UP          PIN_DM_RES_UP
        #define necksense4_DM_RES_DWN         PIN_DM_RES_DWN
        #define necksense4_DM_OD_LO           PIN_DM_OD_LO
        #define necksense4_DM_OD_HI           PIN_DM_OD_HI
        #define necksense4_DM_STRONG          PIN_DM_STRONG
        #define necksense4_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define necksense4_MASK               necksense4__MASK
#define necksense4_SHIFT              necksense4__SHIFT
#define necksense4_WIDTH              1u

/* Interrupt constants */
#if defined(necksense4__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in necksense4_SetInterruptMode() function.
     *  @{
     */
        #define necksense4_INTR_NONE      (uint16)(0x0000u)
        #define necksense4_INTR_RISING    (uint16)(0x0001u)
        #define necksense4_INTR_FALLING   (uint16)(0x0002u)
        #define necksense4_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define necksense4_INTR_MASK      (0x01u) 
#endif /* (necksense4__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define necksense4_PS                     (* (reg8 *) necksense4__PS)
/* Data Register */
#define necksense4_DR                     (* (reg8 *) necksense4__DR)
/* Port Number */
#define necksense4_PRT_NUM                (* (reg8 *) necksense4__PRT) 
/* Connect to Analog Globals */                                                  
#define necksense4_AG                     (* (reg8 *) necksense4__AG)                       
/* Analog MUX bux enable */
#define necksense4_AMUX                   (* (reg8 *) necksense4__AMUX) 
/* Bidirectional Enable */                                                        
#define necksense4_BIE                    (* (reg8 *) necksense4__BIE)
/* Bit-mask for Aliased Register Access */
#define necksense4_BIT_MASK               (* (reg8 *) necksense4__BIT_MASK)
/* Bypass Enable */
#define necksense4_BYP                    (* (reg8 *) necksense4__BYP)
/* Port wide control signals */                                                   
#define necksense4_CTL                    (* (reg8 *) necksense4__CTL)
/* Drive Modes */
#define necksense4_DM0                    (* (reg8 *) necksense4__DM0) 
#define necksense4_DM1                    (* (reg8 *) necksense4__DM1)
#define necksense4_DM2                    (* (reg8 *) necksense4__DM2) 
/* Input Buffer Disable Override */
#define necksense4_INP_DIS                (* (reg8 *) necksense4__INP_DIS)
/* LCD Common or Segment Drive */
#define necksense4_LCD_COM_SEG            (* (reg8 *) necksense4__LCD_COM_SEG)
/* Enable Segment LCD */
#define necksense4_LCD_EN                 (* (reg8 *) necksense4__LCD_EN)
/* Slew Rate Control */
#define necksense4_SLW                    (* (reg8 *) necksense4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define necksense4_PRTDSI__CAPS_SEL       (* (reg8 *) necksense4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define necksense4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) necksense4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define necksense4_PRTDSI__OE_SEL0        (* (reg8 *) necksense4__PRTDSI__OE_SEL0) 
#define necksense4_PRTDSI__OE_SEL1        (* (reg8 *) necksense4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define necksense4_PRTDSI__OUT_SEL0       (* (reg8 *) necksense4__PRTDSI__OUT_SEL0) 
#define necksense4_PRTDSI__OUT_SEL1       (* (reg8 *) necksense4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define necksense4_PRTDSI__SYNC_OUT       (* (reg8 *) necksense4__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(necksense4__SIO_CFG)
    #define necksense4_SIO_HYST_EN        (* (reg8 *) necksense4__SIO_HYST_EN)
    #define necksense4_SIO_REG_HIFREQ     (* (reg8 *) necksense4__SIO_REG_HIFREQ)
    #define necksense4_SIO_CFG            (* (reg8 *) necksense4__SIO_CFG)
    #define necksense4_SIO_DIFF           (* (reg8 *) necksense4__SIO_DIFF)
#endif /* (necksense4__SIO_CFG) */

/* Interrupt Registers */
#if defined(necksense4__INTSTAT)
    #define necksense4_INTSTAT            (* (reg8 *) necksense4__INTSTAT)
    #define necksense4_SNAP               (* (reg8 *) necksense4__SNAP)
    
	#define necksense4_0_INTTYPE_REG 		(* (reg8 *) necksense4__0__INTTYPE)
#endif /* (necksense4__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_necksense4_H */


/* [] END OF FILE */
