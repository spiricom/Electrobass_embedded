/*******************************************************************************
* File Name: highMUX.c
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

#include "highMUX.h"

static uint8 highMUX_lastChannel = highMUX_NULL_CHANNEL;


/*******************************************************************************
* Function Name: highMUX_Start
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
void highMUX_Start(void) 
{
    uint8 chan;

    for(chan = 0u; chan < highMUX_CHANNELS ; chan++)
    {
#if (highMUX_MUXTYPE == highMUX_MUX_SINGLE)
        highMUX_Unset(chan);
#else
        highMUX_CYAMUXSIDE_A_Unset(chan);
        highMUX_CYAMUXSIDE_B_Unset(chan);
#endif
    }

    highMUX_lastChannel = highMUX_NULL_CHANNEL;
}


#if (!highMUX_ATMOSTONE)
/*******************************************************************************
* Function Name: highMUX_Select
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
void highMUX_Select(uint8 channel) 
{
    highMUX_DisconnectAll();        /* Disconnect all previous connections */
    highMUX_Connect(channel);       /* Make the given selection */
    highMUX_lastChannel = channel;  /* Update last channel */
}
#endif


/*******************************************************************************
* Function Name: highMUX_FastSelect
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
void highMUX_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( highMUX_lastChannel != highMUX_NULL_CHANNEL)
    {
        highMUX_Disconnect(highMUX_lastChannel);
    }

    /* Make the new channel connection */
#if (highMUX_MUXTYPE == highMUX_MUX_SINGLE)
    highMUX_Set(channel);
#else
    highMUX_CYAMUXSIDE_A_Set(channel);
    highMUX_CYAMUXSIDE_B_Set(channel);
#endif


    highMUX_lastChannel = channel;   /* Update last channel */
}


#if (highMUX_MUXTYPE == highMUX_MUX_DIFF)
#if (!highMUX_ATMOSTONE)
/*******************************************************************************
* Function Name: highMUX_Connect
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
void highMUX_Connect(uint8 channel) 
{
    highMUX_CYAMUXSIDE_A_Set(channel);
    highMUX_CYAMUXSIDE_B_Set(channel);
}
#endif

/*******************************************************************************
* Function Name: highMUX_Disconnect
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
void highMUX_Disconnect(uint8 channel) 
{
    highMUX_CYAMUXSIDE_A_Unset(channel);
    highMUX_CYAMUXSIDE_B_Unset(channel);
}
#endif

#if (highMUX_ATMOSTONE)
/*******************************************************************************
* Function Name: highMUX_DisconnectAll
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
void highMUX_DisconnectAll(void) 
{
    if(highMUX_lastChannel != highMUX_NULL_CHANNEL) 
    {
        highMUX_Disconnect(highMUX_lastChannel);
        highMUX_lastChannel = highMUX_NULL_CHANNEL;
    }
}
#endif

/* [] END OF FILE */
