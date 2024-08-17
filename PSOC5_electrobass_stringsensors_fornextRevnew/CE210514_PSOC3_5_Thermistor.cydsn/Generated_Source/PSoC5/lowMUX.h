/*******************************************************************************
* File Name: lowMUX.h
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

#if !defined(CY_AMUX_lowMUX_H)
#define CY_AMUX_lowMUX_H

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

void lowMUX_Start(void) ;
#define lowMUX_Init() lowMUX_Start()
void lowMUX_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void lowMUX_Stop(void); */
/* void lowMUX_Select(uint8 channel); */
/* void lowMUX_Connect(uint8 channel); */
/* void lowMUX_Disconnect(uint8 channel); */
/* void lowMUX_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define lowMUX_CHANNELS  3u
#define lowMUX_MUXTYPE   1
#define lowMUX_ATMOSTONE 1

/***************************************
*             API Constants
***************************************/

#define lowMUX_NULL_CHANNEL 0xFFu
#define lowMUX_MUX_SINGLE   1
#define lowMUX_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if lowMUX_MUXTYPE == lowMUX_MUX_SINGLE
# if !lowMUX_ATMOSTONE
#  define lowMUX_Connect(channel) lowMUX_Set(channel)
# endif
# define lowMUX_Disconnect(channel) lowMUX_Unset(channel)
#else
# if !lowMUX_ATMOSTONE
void lowMUX_Connect(uint8 channel) ;
# endif
void lowMUX_Disconnect(uint8 channel) ;
#endif

#if lowMUX_ATMOSTONE
# define lowMUX_Stop() lowMUX_DisconnectAll()
# define lowMUX_Select(channel) lowMUX_FastSelect(channel)
void lowMUX_DisconnectAll(void) ;
#else
# define lowMUX_Stop() lowMUX_Start()
void lowMUX_Select(uint8 channel) ;
# define lowMUX_DisconnectAll() lowMUX_Start()
#endif

#endif /* CY_AMUX_lowMUX_H */


/* [] END OF FILE */
