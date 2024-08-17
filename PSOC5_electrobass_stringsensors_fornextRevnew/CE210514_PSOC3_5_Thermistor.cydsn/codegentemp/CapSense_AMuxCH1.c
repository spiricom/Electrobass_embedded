/*******************************************************************************
* File Name: CapSense_AMuxCH1.c
* Version 3.50
*
*  Description:
*    This file contains all functions required for the analog multiplexer
*    CapSense_CSD_AMux User Module.
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "CapSense_AMuxCH1.h"

uint8 CapSense_AMuxCH1_initVar = 0u;
uint8 CapSense_AMuxCH1_lastChannel = CapSense_AMuxCH1_NULL_CHANNEL;


/*******************************************************************************
* Function Name: CapSense_AMuxCH1_Start
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
void CapSense_AMuxCH1_Start(void)
{
    CapSense_AMuxCH1_DisconnectAll();
    CapSense_AMuxCH1_initVar = 1u;
}


/*******************************************************************************
* Function Name: CapSense_AMuxCH1_Init
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
void CapSense_AMuxCH1_Init(void)
{
    CapSense_AMuxCH1_DisconnectAll();
}


/*******************************************************************************
* Function Name: CapSense_AMuxCH1_Stop
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
void CapSense_AMuxCH1_Stop(void)
{
    CapSense_AMuxCH1_DisconnectAll();
}


/*******************************************************************************
* Function Name: CapSense_AMuxCH1_Select
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
void CapSense_AMuxCH1_Select(uint8 channel) CYREENTRANT
{
    CapSense_AMuxCH1_DisconnectAll();        /* Disconnect all previous connections */
    CapSense_AMuxCH1_Connect(channel);       /* Make the given selection */
    CapSense_AMuxCH1_lastChannel = channel;  /* Update last channel */
}


/*******************************************************************************
* Function Name: CapSense_AMuxCH1_FastSelect
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
void CapSense_AMuxCH1_FastSelect(uint8 channel) CYREENTRANT
{
    /* Disconnect the last valid channel */
    if( CapSense_AMuxCH1_lastChannel != CapSense_AMuxCH1_NULL_CHANNEL)   /* Update last channel */
    {
        CapSense_AMuxCH1_Disconnect(CapSense_AMuxCH1_lastChannel);
    }

    /* Make the new channel connection */
    CapSense_AMuxCH1_Connect(channel);
    CapSense_AMuxCH1_lastChannel = channel;   /* Update last channel */
}


#if(CapSense_AMuxCH1_MUXTYPE == CapSense_AMuxCH1_MUX_DIFF)
    /*******************************************************************************
    * Function Name: CapSense_AMuxCH1_Connect
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
    void CapSense_AMuxCH1_Connect(uint8 channel) CYREENTRANT
    {
        CapSense_AMuxCH1_CYAMUXSIDE_A_Set(channel);
        CapSense_AMuxCH1_CYAMUXSIDE_B_Set(channel);
    }
    
    
    /*******************************************************************************
    * Function Name: CapSense_AMuxCH1_Disconnect
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
    void CapSense_AMuxCH1_Disconnect(uint8 channel) CYREENTRANT
    {
        CapSense_AMuxCH1_CYAMUXSIDE_A_Unset(channel);
        CapSense_AMuxCH1_CYAMUXSIDE_B_Unset(channel);
    }
    
#endif  /* End (CapSense_AMuxCH1_MUXTYPE == CapSense_AMuxCH1_MUX_DIFF) */


/*******************************************************************************
* Function Name: CapSense_AMuxCH1_DisconnectAll
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
void CapSense_AMuxCH1_DisconnectAll(void) CYREENTRANT
{
    uint8 chan;

    #if(CapSense_AMuxCH1_MUXTYPE == CapSense_AMuxCH1_MUX_SINGLE)
        for(chan = 0; chan < CapSense_AMuxCH1_CHANNELS ; chan++)
        {
            CapSense_AMuxCH1_Unset(chan);
        }
    #else
        for(chan = 0; chan < CapSense_AMuxCH1_CHANNELS ; chan++)
        {
            CapSense_AMuxCH1_CYAMUXSIDE_A_Unset(chan);
            CapSense_AMuxCH1_CYAMUXSIDE_B_Unset(chan);
        }
    #endif  /* End (CapSense_AMuxCH1_MUXTYPE == CapSense_AMuxCH1_MUX_SINGLE) */
}


/* [] END OF FILE */
