/*******************************************************************************
* File Name: AMux_3.c
* Version 1.80
*
*  Description:
*    This file contains all functions required for the analog multiplexer
*    AMux User Module.
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "AMux_3.h"

static uint8 AMux_3_lastChannel = AMux_3_NULL_CHANNEL;


/*******************************************************************************
* Function Name: AMux_3_Start
********************************************************************************
* Summary:
*  Disconnect all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void AMux_3_Start(void) 
{
    uint8 chan;

    for(chan = 0u; chan < AMux_3_CHANNELS ; chan++)
    {
#if (AMux_3_MUXTYPE == AMux_3_MUX_SINGLE)
        AMux_3_Unset(chan);
#else
        AMux_3_CYAMUXSIDE_A_Unset(chan);
        AMux_3_CYAMUXSIDE_B_Unset(chan);
#endif
    }

    AMux_3_lastChannel = AMux_3_NULL_CHANNEL;
}


#if (!AMux_3_ATMOSTONE)
/*******************************************************************************
* Function Name: AMux_3_Select
********************************************************************************
* Summary:
*  This functions first disconnects all channels then connects the given
*  channel.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void AMux_3_Select(uint8 channel) 
{
    AMux_3_DisconnectAll();        /* Disconnect all previous connections */
    AMux_3_Connect(channel);       /* Make the given selection */
    AMux_3_lastChannel = channel;  /* Update last channel */
}
#endif


/*******************************************************************************
* Function Name: AMux_3_FastSelect
********************************************************************************
* Summary:
*  This function first disconnects the last connection made with FastSelect or
*  Select, then connects the given channel. The FastSelect function is similar
*  to the Select function, except it is faster since it only disconnects the
*  last channel selected rather than all channels.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void AMux_3_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( AMux_3_lastChannel != AMux_3_NULL_CHANNEL)
    {
        AMux_3_Disconnect(AMux_3_lastChannel);
    }

    /* Make the new channel connection */
#if (AMux_3_MUXTYPE == AMux_3_MUX_SINGLE)
    AMux_3_Set(channel);
#else
    AMux_3_CYAMUXSIDE_A_Set(channel);
    AMux_3_CYAMUXSIDE_B_Set(channel);
#endif


    AMux_3_lastChannel = channel;   /* Update last channel */
}


#if (AMux_3_MUXTYPE == AMux_3_MUX_DIFF)
#if (!AMux_3_ATMOSTONE)
/*******************************************************************************
* Function Name: AMux_3_Connect
********************************************************************************
* Summary:
*  This function connects the given channel without affecting other connections.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void AMux_3_Connect(uint8 channel) 
{
    AMux_3_CYAMUXSIDE_A_Set(channel);
    AMux_3_CYAMUXSIDE_B_Set(channel);
}
#endif

/*******************************************************************************
* Function Name: AMux_3_Disconnect
********************************************************************************
* Summary:
*  This function disconnects the given channel from the common or output
*  terminal without affecting other connections.
*
* Parameters:
*  channel:  The channel to disconnect from the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void AMux_3_Disconnect(uint8 channel) 
{
    AMux_3_CYAMUXSIDE_A_Unset(channel);
    AMux_3_CYAMUXSIDE_B_Unset(channel);
}
#endif

#if (AMux_3_ATMOSTONE)
/*******************************************************************************
* Function Name: AMux_3_DisconnectAll
********************************************************************************
* Summary:
*  This function disconnects all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void AMux_3_DisconnectAll(void) 
{
    if(AMux_3_lastChannel != AMux_3_NULL_CHANNEL) 
    {
        AMux_3_Disconnect(AMux_3_lastChannel);
        AMux_3_lastChannel = AMux_3_NULL_CHANNEL;
    }
}
#endif

/* [] END OF FILE */
