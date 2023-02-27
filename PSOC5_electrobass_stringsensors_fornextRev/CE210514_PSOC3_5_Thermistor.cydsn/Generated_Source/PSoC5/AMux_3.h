/*******************************************************************************
* File Name: AMux_3.h
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

#if !defined(CY_AMUX_AMux_3_H)
#define CY_AMUX_AMux_3_H

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

void AMux_3_Start(void) ;
#define AMux_3_Init() AMux_3_Start()
void AMux_3_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void AMux_3_Stop(void); */
/* void AMux_3_Select(uint8 channel); */
/* void AMux_3_Connect(uint8 channel); */
/* void AMux_3_Disconnect(uint8 channel); */
/* void AMux_3_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define AMux_3_CHANNELS  3u
#define AMux_3_MUXTYPE   1
#define AMux_3_ATMOSTONE 1

/***************************************
*             API Constants
***************************************/

#define AMux_3_NULL_CHANNEL 0xFFu
#define AMux_3_MUX_SINGLE   1
#define AMux_3_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if AMux_3_MUXTYPE == AMux_3_MUX_SINGLE
# if !AMux_3_ATMOSTONE
#  define AMux_3_Connect(channel) AMux_3_Set(channel)
# endif
# define AMux_3_Disconnect(channel) AMux_3_Unset(channel)
#else
# if !AMux_3_ATMOSTONE
void AMux_3_Connect(uint8 channel) ;
# endif
void AMux_3_Disconnect(uint8 channel) ;
#endif

#if AMux_3_ATMOSTONE
# define AMux_3_Stop() AMux_3_DisconnectAll()
# define AMux_3_Select(channel) AMux_3_FastSelect(channel)
void AMux_3_DisconnectAll(void) ;
#else
# define AMux_3_Stop() AMux_3_Start()
void AMux_3_Select(uint8 channel) ;
# define AMux_3_DisconnectAll() AMux_3_Start()
#endif

#endif /* CY_AMUX_AMux_3_H */


/* [] END OF FILE */
