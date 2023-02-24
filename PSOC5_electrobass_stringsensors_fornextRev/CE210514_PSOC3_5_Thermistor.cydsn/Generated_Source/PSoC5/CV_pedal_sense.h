/*******************************************************************************
* File Name: CV_pedal_sense.h  
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

#if !defined(CY_PINS_CV_pedal_sense_H) /* Pins CV_pedal_sense_H */
#define CY_PINS_CV_pedal_sense_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CV_pedal_sense_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CV_pedal_sense__PORT == 15 && ((CV_pedal_sense__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    CV_pedal_sense_Write(uint8 value);
void    CV_pedal_sense_SetDriveMode(uint8 mode);
uint8   CV_pedal_sense_ReadDataReg(void);
uint8   CV_pedal_sense_Read(void);
void    CV_pedal_sense_SetInterruptMode(uint16 position, uint16 mode);
uint8   CV_pedal_sense_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the CV_pedal_sense_SetDriveMode() function.
     *  @{
     */
        #define CV_pedal_sense_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define CV_pedal_sense_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define CV_pedal_sense_DM_RES_UP          PIN_DM_RES_UP
        #define CV_pedal_sense_DM_RES_DWN         PIN_DM_RES_DWN
        #define CV_pedal_sense_DM_OD_LO           PIN_DM_OD_LO
        #define CV_pedal_sense_DM_OD_HI           PIN_DM_OD_HI
        #define CV_pedal_sense_DM_STRONG          PIN_DM_STRONG
        #define CV_pedal_sense_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define CV_pedal_sense_MASK               CV_pedal_sense__MASK
#define CV_pedal_sense_SHIFT              CV_pedal_sense__SHIFT
#define CV_pedal_sense_WIDTH              1u

/* Interrupt constants */
#if defined(CV_pedal_sense__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CV_pedal_sense_SetInterruptMode() function.
     *  @{
     */
        #define CV_pedal_sense_INTR_NONE      (uint16)(0x0000u)
        #define CV_pedal_sense_INTR_RISING    (uint16)(0x0001u)
        #define CV_pedal_sense_INTR_FALLING   (uint16)(0x0002u)
        #define CV_pedal_sense_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define CV_pedal_sense_INTR_MASK      (0x01u) 
#endif /* (CV_pedal_sense__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CV_pedal_sense_PS                     (* (reg8 *) CV_pedal_sense__PS)
/* Data Register */
#define CV_pedal_sense_DR                     (* (reg8 *) CV_pedal_sense__DR)
/* Port Number */
#define CV_pedal_sense_PRT_NUM                (* (reg8 *) CV_pedal_sense__PRT) 
/* Connect to Analog Globals */                                                  
#define CV_pedal_sense_AG                     (* (reg8 *) CV_pedal_sense__AG)                       
/* Analog MUX bux enable */
#define CV_pedal_sense_AMUX                   (* (reg8 *) CV_pedal_sense__AMUX) 
/* Bidirectional Enable */                                                        
#define CV_pedal_sense_BIE                    (* (reg8 *) CV_pedal_sense__BIE)
/* Bit-mask for Aliased Register Access */
#define CV_pedal_sense_BIT_MASK               (* (reg8 *) CV_pedal_sense__BIT_MASK)
/* Bypass Enable */
#define CV_pedal_sense_BYP                    (* (reg8 *) CV_pedal_sense__BYP)
/* Port wide control signals */                                                   
#define CV_pedal_sense_CTL                    (* (reg8 *) CV_pedal_sense__CTL)
/* Drive Modes */
#define CV_pedal_sense_DM0                    (* (reg8 *) CV_pedal_sense__DM0) 
#define CV_pedal_sense_DM1                    (* (reg8 *) CV_pedal_sense__DM1)
#define CV_pedal_sense_DM2                    (* (reg8 *) CV_pedal_sense__DM2) 
/* Input Buffer Disable Override */
#define CV_pedal_sense_INP_DIS                (* (reg8 *) CV_pedal_sense__INP_DIS)
/* LCD Common or Segment Drive */
#define CV_pedal_sense_LCD_COM_SEG            (* (reg8 *) CV_pedal_sense__LCD_COM_SEG)
/* Enable Segment LCD */
#define CV_pedal_sense_LCD_EN                 (* (reg8 *) CV_pedal_sense__LCD_EN)
/* Slew Rate Control */
#define CV_pedal_sense_SLW                    (* (reg8 *) CV_pedal_sense__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CV_pedal_sense_PRTDSI__CAPS_SEL       (* (reg8 *) CV_pedal_sense__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CV_pedal_sense_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CV_pedal_sense__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CV_pedal_sense_PRTDSI__OE_SEL0        (* (reg8 *) CV_pedal_sense__PRTDSI__OE_SEL0) 
#define CV_pedal_sense_PRTDSI__OE_SEL1        (* (reg8 *) CV_pedal_sense__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CV_pedal_sense_PRTDSI__OUT_SEL0       (* (reg8 *) CV_pedal_sense__PRTDSI__OUT_SEL0) 
#define CV_pedal_sense_PRTDSI__OUT_SEL1       (* (reg8 *) CV_pedal_sense__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CV_pedal_sense_PRTDSI__SYNC_OUT       (* (reg8 *) CV_pedal_sense__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(CV_pedal_sense__SIO_CFG)
    #define CV_pedal_sense_SIO_HYST_EN        (* (reg8 *) CV_pedal_sense__SIO_HYST_EN)
    #define CV_pedal_sense_SIO_REG_HIFREQ     (* (reg8 *) CV_pedal_sense__SIO_REG_HIFREQ)
    #define CV_pedal_sense_SIO_CFG            (* (reg8 *) CV_pedal_sense__SIO_CFG)
    #define CV_pedal_sense_SIO_DIFF           (* (reg8 *) CV_pedal_sense__SIO_DIFF)
#endif /* (CV_pedal_sense__SIO_CFG) */

/* Interrupt Registers */
#if defined(CV_pedal_sense__INTSTAT)
    #define CV_pedal_sense_INTSTAT            (* (reg8 *) CV_pedal_sense__INTSTAT)
    #define CV_pedal_sense_SNAP               (* (reg8 *) CV_pedal_sense__SNAP)
    
	#define CV_pedal_sense_0_INTTYPE_REG 		(* (reg8 *) CV_pedal_sense__0__INTTYPE)
#endif /* (CV_pedal_sense__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CV_pedal_sense_H */


/* [] END OF FILE */
