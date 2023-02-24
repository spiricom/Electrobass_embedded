/*******************************************************************************
* File Name: highMUX.h
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

#if !defined(CY_AMUX_highMUX_H)
#define CY_AMUX_highMUX_H

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

void highMUX_Start(void) ;
#define highMUX_Init() highMUX_Start()
void highMUX_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void highMUX_Stop(void); */
/* void highMUX_Select(uint8 channel); */
/* void highMUX_Connect(uint8 channel); */
/* void highMUX_Disconnect(uint8 channel); */
/* void highMUX_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define highMUX_CHANNELS  2u
#define highMUX_MUXTYPE   1
#define highMUX_ATMOSTONE 1

/***************************************
*             API Constants
***************************************/

#define highMUX_NULL_CHANNEL 0xFFu
#define highMUX_MUX_SINGLE   1
#define highMUX_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if highMUX_MUXTYPE == highMUX_MUX_SINGLE
# if !highMUX_ATMOSTONE
#  define highMUX_Connect(channel) highMUX_Set(channel)
# endif
# define highMUX_Disconnect(channel) highMUX_Unset(channel)
#else
# if !highMUX_ATMOSTONE
void highMUX_Connect(uint8 channel) ;
# endif
void highMUX_Disconnect(uint8 channel) ;
#endif

#if highMUX_ATMOSTONE
# define highMUX_Stop() highMUX_DisconnectAll()
# define highMUX_Select(channel) highMUX_FastSelect(channel)
void highMUX_DisconnectAll(void) ;
#else
# define highMUX_Stop() highMUX_Start()
void highMUX_Select(uint8 channel) ;
# define highMUX_DisconnectAll() highMUX_Start()
#endif

#endif /* CY_AMUX_highMUX_H */


/* [] END OF FILE */
