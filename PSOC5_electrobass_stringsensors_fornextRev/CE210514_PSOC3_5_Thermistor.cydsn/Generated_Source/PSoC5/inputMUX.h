/*******************************************************************************
* File Name: inputMUX.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_inputMUX_H)
#define CY_AMUX_inputMUX_H

#include "cyfitter.h"
#include "cyfitter_cfg.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))    
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif /* ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */


/***************************************
*        Function Prototypes
***************************************/

void inputMUX_Start(void) ;
#define inputMUX_Init() inputMUX_Start()
void inputMUX_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void inputMUX_Stop(void); */
/* void inputMUX_Select(uint8 channel); */
/* void inputMUX_Connect(uint8 channel); */
/* void inputMUX_Disconnect(uint8 channel); */
/* void inputMUX_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define inputMUX_CHANNELS  5u
#define inputMUX_MUXTYPE   2
#define inputMUX_ATMOSTONE 1

/***************************************
*             API Constants
***************************************/

#define inputMUX_NULL_CHANNEL 0xFFu
#define inputMUX_MUX_SINGLE   1
#define inputMUX_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if inputMUX_MUXTYPE == inputMUX_MUX_SINGLE
# if !inputMUX_ATMOSTONE
#  define inputMUX_Connect(channel) inputMUX_Set(channel)
# endif
# define inputMUX_Disconnect(channel) inputMUX_Unset(channel)
#else
# if !inputMUX_ATMOSTONE
void inputMUX_Connect(uint8 channel) ;
# endif
void inputMUX_Disconnect(uint8 channel) ;
#endif

#if inputMUX_ATMOSTONE
# define inputMUX_Stop() inputMUX_DisconnectAll()
# define inputMUX_Select(channel) inputMUX_FastSelect(channel)
void inputMUX_DisconnectAll(void) ;
#else
# define inputMUX_Stop() inputMUX_Start()
void inputMUX_Select(uint8 channel) ;
# define inputMUX_DisconnectAll() inputMUX_Start()
#endif

#endif /* CY_AMUX_inputMUX_H */


/* [] END OF FILE */
