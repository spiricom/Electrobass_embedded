/*******************************************************************************
* File Name: inputMUX.c
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

#include "inputMUX.h"

static uint8 inputMUX_lastChannel = inputMUX_NULL_CHANNEL;


/*******************************************************************************
* Function Name: inputMUX_Start
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
void inputMUX_Start(void) 
{
    uint8 chan;

    for(chan = 0u; chan < inputMUX_CHANNELS ; chan++)
    {
#if (inputMUX_MUXTYPE == inputMUX_MUX_SINGLE)
        inputMUX_Unset(chan);
#else
        inputMUX_CYAMUXSIDE_A_Unset(chan);
        inputMUX_CYAMUXSIDE_B_Unset(chan);
#endif
    }

    inputMUX_lastChannel = inputMUX_NULL_CHANNEL;
}


#if (!inputMUX_ATMOSTONE)
/*******************************************************************************
* Function Name: inputMUX_Select
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
void inputMUX_Select(uint8 channel) 
{
    inputMUX_DisconnectAll();        /* Disconnect all previous connections */
    inputMUX_Connect(channel);       /* Make the given selection */
    inputMUX_lastChannel = channel;  /* Update last channel */
}
#endif


/*******************************************************************************
* Function Name: inputMUX_FastSelect
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
void inputMUX_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( inputMUX_lastChannel != inputMUX_NULL_CHANNEL)
    {
        inputMUX_Disconnect(inputMUX_lastChannel);
    }

    /* Make the new channel connection */
#if (inputMUX_MUXTYPE == inputMUX_MUX_SINGLE)
    inputMUX_Set(channel);
#else
    inputMUX_CYAMUXSIDE_A_Set(channel);
    inputMUX_CYAMUXSIDE_B_Set(channel);
#endif


    inputMUX_lastChannel = channel;   /* Update last channel */
}


#if (inputMUX_MUXTYPE == inputMUX_MUX_DIFF)
#if (!inputMUX_ATMOSTONE)
/*******************************************************************************
* Function Name: inputMUX_Connect
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
void inputMUX_Connect(uint8 channel) 
{
    inputMUX_CYAMUXSIDE_A_Set(channel);
    inputMUX_CYAMUXSIDE_B_Set(channel);
}
#endif

/*******************************************************************************
* Function Name: inputMUX_Disconnect
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
void inputMUX_Disconnect(uint8 channel) 
{
    inputMUX_CYAMUXSIDE_A_Unset(channel);
    inputMUX_CYAMUXSIDE_B_Unset(channel);
}
#endif

#if (inputMUX_ATMOSTONE)
/*******************************************************************************
* Function Name: inputMUX_DisconnectAll
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
void inputMUX_DisconnectAll(void) 
{
    if(inputMUX_lastChannel != inputMUX_NULL_CHANNEL) 
    {
        inputMUX_Disconnect(inputMUX_lastChannel);
        inputMUX_lastChannel = inputMUX_NULL_CHANNEL;
    }
}
#endif

/* [] END OF FILE */
