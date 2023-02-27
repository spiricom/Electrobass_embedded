/*******************************************************************************
* File Name: lowMUX.c
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

#include "lowMUX.h"

static uint8 lowMUX_lastChannel = lowMUX_NULL_CHANNEL;


/*******************************************************************************
* Function Name: lowMUX_Start
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
void lowMUX_Start(void) 
{
    uint8 chan;

    for(chan = 0u; chan < lowMUX_CHANNELS ; chan++)
    {
#if (lowMUX_MUXTYPE == lowMUX_MUX_SINGLE)
        lowMUX_Unset(chan);
#else
        lowMUX_CYAMUXSIDE_A_Unset(chan);
        lowMUX_CYAMUXSIDE_B_Unset(chan);
#endif
    }

    lowMUX_lastChannel = lowMUX_NULL_CHANNEL;
}


#if (!lowMUX_ATMOSTONE)
/*******************************************************************************
* Function Name: lowMUX_Select
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
void lowMUX_Select(uint8 channel) 
{
    lowMUX_DisconnectAll();        /* Disconnect all previous connections */
    lowMUX_Connect(channel);       /* Make the given selection */
    lowMUX_lastChannel = channel;  /* Update last channel */
}
#endif


/*******************************************************************************
* Function Name: lowMUX_FastSelect
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
void lowMUX_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( lowMUX_lastChannel != lowMUX_NULL_CHANNEL)
    {
        lowMUX_Disconnect(lowMUX_lastChannel);
    }

    /* Make the new channel connection */
#if (lowMUX_MUXTYPE == lowMUX_MUX_SINGLE)
    lowMUX_Set(channel);
#else
    lowMUX_CYAMUXSIDE_A_Set(channel);
    lowMUX_CYAMUXSIDE_B_Set(channel);
#endif


    lowMUX_lastChannel = channel;   /* Update last channel */
}


#if (lowMUX_MUXTYPE == lowMUX_MUX_DIFF)
#if (!lowMUX_ATMOSTONE)
/*******************************************************************************
* Function Name: lowMUX_Connect
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
void lowMUX_Connect(uint8 channel) 
{
    lowMUX_CYAMUXSIDE_A_Set(channel);
    lowMUX_CYAMUXSIDE_B_Set(channel);
}
#endif

/*******************************************************************************
* Function Name: lowMUX_Disconnect
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
void lowMUX_Disconnect(uint8 channel) 
{
    lowMUX_CYAMUXSIDE_A_Unset(channel);
    lowMUX_CYAMUXSIDE_B_Unset(channel);
}
#endif

#if (lowMUX_ATMOSTONE)
/*******************************************************************************
* Function Name: lowMUX_DisconnectAll
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
void lowMUX_DisconnectAll(void) 
{
    if(lowMUX_lastChannel != lowMUX_NULL_CHANNEL) 
    {
        lowMUX_Disconnect(lowMUX_lastChannel);
        lowMUX_lastChannel = lowMUX_NULL_CHANNEL;
    }
}
#endif

/* [] END OF FILE */
