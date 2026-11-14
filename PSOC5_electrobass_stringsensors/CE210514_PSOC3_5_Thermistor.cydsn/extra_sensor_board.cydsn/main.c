/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#define RD_BUFFER_SIZE		(8u)
#define WR_BUFFER_SIZE		(2u)

volatile uint8_t myInput[WR_BUFFER_SIZE];
uint8_t muxCtl = 0;
uint32_t stringResult = 0;
uint8_t goingUp[4] = {0,0,0,0};
uint32_t prevStringResults[4] = {0,0,0,0};

int main(void)
{


    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
   uint8 byteCount = 0u;
    uint8 sample_segment[RD_BUFFER_SIZE] = {5,6};
    uint8 sample_segment2[WR_BUFFER_SIZE];
    uint16 sample_full = 0u;

    /* Set up slave read data buffer */
    I2CS_SlaveInitReadBuf((uint8 *) sample_segment, RD_BUFFER_SIZE);
    I2CS_SlaveInitWriteBuf((uint8 *) sample_segment2, WR_BUFFER_SIZE);
    I2CS_Start();
    ADC_1_Start();
    AMux_1_Start();
    AMux_2_Start();
    /* Enable global interrupts - needed for I2C operation */
    CyGlobalIntEnable;

    for(;;)
    {
        while(MUX_En_Read() == 1) //wait while mux enable is high, reading the control pins
        {
            AMux_1_FastSelect(0);
            AMux_2_FastSelect(0);
            muxCtl = MUX_0_Read() + (MUX_1_Read() << 1); //assemble the mux control number
        }
        //when mux control goes low, do the conversion
        AMux_1_FastSelect(muxCtl+1);
        AMux_2_FastSelect(muxCtl+1);
        CyDelayUs(4); 
        ADC_1_StartConvert();
        ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
        stringResult = ADC_1_GetResult32();

        //goin up
        if (stringResult > prevStringResults[muxCtl])
        {
            goingUp[muxCtl] = 1;
        }
        //goin down
        else if (stringResult < prevStringResults[muxCtl])
        {
            goingUp[muxCtl] = 0;
        }
        //stayed the same
        else
        {
            goingUp[muxCtl] = 2;
        }
        
        prevStringResults[muxCtl] = stringResult;
        
        for (int i = 0; i < 4; i++)
        {
            sample_segment[i*2] = prevStringResults[i] & 255;
            sample_segment[(i*2) + 1] = (prevStringResults[i] >> 8) & 255;
        }
      
        /* Check if the slave buffer has been read */
        if(I2CS_SlaveStatus() & I2CS_SSTAT_RD_CMPLT)
        {
            I2CS_SlaveClearReadStatus();
            I2CS_SlaveClearReadBuf();
        }
        while(MUX_En_Read() == 0) //wait while mux enable is low, reading the control pins
        {
            ;
        }
        #if 0
        /* Check if the slave buffer has been written to*/
        if(I2CS_SlaveStatus() & I2CS_SSTAT_WR_CMPLT)
        {
            myInput[0] = sample_segment2[0];
            myInput[1] = sample_segment2[1];
            byteCount = I2CS_SlaveGetWriteBufSize();
            I2CS_SlaveClearWriteStatus();
            I2CS_SlaveClearWriteBuf();
        }
        #endif
    } /* End of forever loop */

}

/* [] END OF FILE */
//