/*****************************************************************************
* File Name: main.c
*
* Version: 3.0
*
* Description:
*   
* 
* Note:
* 	The main project includes the ADC and other components required for the
*   temperature measurement. The Thermistor component is a complete firmware component
*   as decribed in the component datahseet and application note
******************************************************************************
* Copyright (C) 2015, Cypress Semiconductor Corporation.
******************************************************************************
* This software is prese by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*****************************************************************************/
#include <device.h>
#include <main.h>
#include <stdio.h>
#include "math.h"
#include "oled.h"

//#define MAPLE1 1
#define GREEN3 1


#define EEPROM_CALIBRATION_OFFSET 0
#define CALIBRATION_SIZE_IN_BYTES NUM_FRETS * NUM_STRINGS * 2 //for each fret on each string, store 2 bytes to add up to a 16-bit word


volatile uint8 usbActivityCounter = 0u;
 uint8 midiMsg[4];
volatile uint8_t currentVBUS = 0;
volatile uint8_t prevVBUS = 0;
volatile uint8_t USB_active = 0;
volatile uint8_t USB_check_flag = 0;

uint16_t midiSent = 0;
uint16_t midiOverflow = 0;

uint scanPart = 0;
uint channel = 0;
#define TUNING_ARRAY_SIZE 272
uint8_t tuningArray[TUNING_ARRAY_SIZE];
uint currentOutPointer = 0;
uint outChanged = 0;

void checkUSB_Vbus(void);
void sendMIDIAllNotesOff(void);
void sendMIDIPitchBend(int val, int channel);
void firstCheckUSB_Vbus(void);
void restartSystemCheck(void);
void sendMIDINoteOn(int MIDInoteNum, int velocity, int channel);
void sendMIDIControlChange(int CCnum, int CCval, int channel);
void sendMIDIControlChangeComputer(int CCnum, int CCval, int channel);
CY_ISR_PROTO(SleepIsr_function);
void noteEvent(int string);
void I2C_reset(void);
void CCEvent(int bar);
void scanButtons(void);
void sendCurrentPresetNumber(void);
void sendCurrentTuningNumber(void);
uint8 I2C_MasterReadBlocking(uint8 i2CAddr, uint16 nbytes, uint8_t mode);

uint8_t setPresetOrSetTuning = 0;

union breakFloat {
 float f;
 uint8_t b[4];  
 uint32_t u32;
};

volatile uint8_t I2Cbuff1[256];
uint8_t stringCapSensorsOnOff[1];
uint8_t stringCapSensorsRaw[16];
uint8_t thresholdArray[8] = {30, 30, 30, 30, 30, 30, 30, 30};
#if MAPLE1
uint32_t fretMeasurements[4][2] = {
    {68958,19847},
    {67974,20532},
    {68984,20665},
    {85647,24651}
};
#elif defined GREEN3
 uint32_t fretMeasurements[4][4] = {
    {75540,22551, 10000, 10000},
    {64813,19391, 10000, 10000},
    {63616,19052, 10000, 10000},
    {71986,21251, 10000, 10000}
};
#else
uint16_t fretMeasurements[4][2] = {
    {57984,17489},
    {53292,15779},
    {52933,15582},
    {57784,16450}
};
    #endif
//1st fret, 5th fret, 9th fret, 15 fret
float fretRatios[4] = {0.94387439674627617953623675390268f,0.749153457f, 0.594603498f, 0.420448248f}; 

uint8_t sysexBuffer[2048];
uint32_t sysexPointer = 0;
uint8_t receivingSysex = 0;
uint8_t parsingSysex = 0;
volatile uint8_t presetArray[1024];
uint8_t presetNumberToWrite = 0;
uint8_t tuningNumberToWrite = 0;

uint8_t sendMessageEnd = 0;
enum presetArraySectionState
{
    presetName = 0,
    macroNames = 1,
    initialVals = 2,
    mapCountNext = 3,
    mapping = 4,
    presetEnd = 5,
};
uint8_t presetArraySection = presetName;

uint16_t messageArraySendCount = 0;
uint16_t messageArraySize = 0;

uint8_t sysexMessageInProgress = 0;

int32_t linearPotValue32Bit[4];
uint8_t counter = 0;
int32_t temper;
int previousButtons[11];
int octave = 1;
void scanLinearResistor();
int stringPlucks[4];
int stringPlucksPrev[4];


int calibration_mode = 0;
int max_calibration = 16;

#define KNOB_FIR_SIZE 8
#define KNOB_FIR_SIZE_MASK 7
#define KNOB_FIR_SIZE_BITSHIFT 3
uint32_t knobsFIR[5][KNOB_FIR_SIZE];

#define NAME_LENGTH_IN_BYTES 14

#define LINEAR_FIR_SIZE 2
#define LINEAR_FIR_SIZE_MASK 1
#define LINEAR_FIR_SIZE_BITSHIFT 1

float hysteresisStates[4];
float hysteresisLowThresh = 0.4f;
float hysteresisHighThresh = 0.6f;

void DmaTxConfiguration(void);
void DmaRxConfiguration(void);

/* DMA Configuration for DMA_TX */
#define DMA_TX_BYTES_PER_BURST      (1u)
#define DMA_TX_REQUEST_PER_BURST    (1u)
#define DMA_TX_SRC_BASE             (CYDEV_SRAM_BASE)
#define DMA_TX_DST_BASE             (CYDEV_PERIPH_BASE)

/* DMA Configuration for DMA_RX */
#define DMA_RX_BYTES_PER_BURST      (1u)
#define DMA_RX_REQUEST_PER_BURST    (1u)
#define DMA_RX_SRC_BASE             (CYDEV_PERIPH_BASE)
#define DMA_RX_DST_BASE             (CYDEV_SRAM_BASE)

#define BUFFER_SIZE                 (16u)
#define BUFFER_2_SIZE               (16u)
#define STORE_TD_CFG_ONCMPLT        (1u)

/* Variable declarations for DMA_TX*/
volatile uint8 txChannel;
volatile uint8 txTD;
volatile uint8 txBuffer[BUFFER_SIZE];

volatile uint8 rxChannel;
volatile uint8 rxTD;
volatile uint8 rxBuffer[BUFFER_SIZE];

/* Variable declarations for DMA_2*/
volatile uint8 tx2Channel;
volatile uint8 tx2TD;
volatile uint8 tx2Buffer[BUFFER_2_SIZE];

volatile uint8 rx2Channel;
volatile uint8 rx2TD;
volatile uint8 rx2Buffer[BUFFER_2_SIZE];

volatile uint8 tx2BufferTemp[BUFFER_2_SIZE];

    static uint8 CYCODE eepromArray[]={ 0, 0 };
                                            
    uint8 array[] ={ 0, 0 };
                                
    /*Return status for EEPROM and UART*/ 
cy_en_em_eeprom_status_t eepromReturnValue;


/* EEPROM storage in work flash, this is defined in Em_EEPROM.c*/
#if defined (__ICCARM__)
#pragma data_alignment = CY_FLASH_SIZEOF_ROW
const uint8_t Em_EEPROM_em_EepromStorage[Em_EEPROM_PHYSICAL_SIZE] = {0u};
#else
const uint8_t Em_EEPROM_em_EepromStorage[Em_EEPROM_PHYSICAL_SIZE]
__ALIGNED(CY_FLASH_SIZEOF_ROW) = {0u};
#endif /* defined (__ICCARM__) */

    uint8 eeprom_cnt;
    cystatus status;
    volatile const uint8 * ptr;
volatile int barCount = 0;

void handleNotes(int note, int velocity, int string);

int stringStates[4][2] = {{0,0},{0,0},{0,0},{0,0}};

CY_ISR(button_press_ISR) {     /* No need to clear any interrupt source; interrupt component should be      * configured for RISING_EDGE mode.      */     /* Read the debouncer status reg just to clear it, no need to check its      * contents in this application.      */  
 //FiltReg_Read(); 
    //
}

#define INV_440 0.0022727272727273f

float   LEAF_clip(float min, float val, float max)
{
    float tempmin = min;
    float tempmax = max;
    if (min > max)
    {
        tempmin = max;
        tempmax = min;
    }
    if (val < tempmin)
    {
        return tempmin;
    }
    else if (val > tempmax)
    {
        return tempmax;
    }
    else
    {
        return val;
    }
}
float mtof(float f)
{
    if (f <= -1500.0f) return(0);
    else if (f > 1499.0f) return(mtof(1499.0f));
    else return (8.17579891564f * expf(0.0577622650f * f));
}

float ftom(float f)
{
    return (f > 0 ? 17.3123405046f * logf(.12231220585f * f) : -1500.0f);
}

// alpha, [0.0, 1.0]
float LEAF_interpolation_linear (float A, float B, float alpha)
{
    float omAlpha = 1.0f - alpha;
    
    // First 1/2 of interpolation
    float out = A * omAlpha;
    
    out += B * alpha;
    
    return out;
}
void USB_service(void);

//volatile int whichLinearSensor = 0;

float map(float value, float istart, float istop, float ostart, float ostop)
{
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}
uint8 I2C_MasterWriteBlocking(uint8 i2CAddr, uint16 nbytes, uint8_t mode);
void parseSysex(void);
//Main

volatile int testVar = 0;
int lastNotes[4] = {0,0,0,0};
int frettedState = 1;
int polyMode = 0;

int pitchBendsPerString[4];
int openStringCount[4] = {0,0,0,0};
int loudestString = 0;
int64_t timeSinceLastAttack = 0;
float previousHysteresisStates[4] = {0.0f, 0.0f, 0.0f, 0.0f};
float openStringFreqs[4] = {41.203f, 55.0f, 73.416f, 97.999f};
float openStringMIDI[4] = {28.0f, 33.0f, 38.0f, 43.0f};
float invStringMappedPositions[4] = {0,0,0,0};
float stringMIDI[4] = {0,0,0,0};
float stringMIDIRounded[4] = {0,0,0,0};
float stringMIDIPrev[4] = {0,0,0,0};
float linearHysteresis = 0.6f;
float hp_y[4];
float hp_x[4]; 
float hp_R;


int currentPresetSelection = 0;
int highestPresetNumber = MAX_NUM_PRESETS - 1;

uint8_t presetNamesArray[MAX_NUM_PRESETS][14];
uint8_t presetNumberToLoad = 0;


int currentTuningSelection = 0;
int highestTuningNumber = MAX_NUM_TUNINGS - 1;

uint8_t tuningNamesArray[MAX_NUM_TUNINGS][14];
uint8_t tuningNumberToLoad = 0;



int previousPitchBendsSent = 0;
int previousPitchBendsSentPoly[4] = {0};
uint32_t knobs[5];
int buttons;

int firPointer = 0;
uint8_t knobs7bit[5] = {0,0,0,0,0};
uint16_t knobs7bitPrev[5] = {0,0,0,0,0};
uint16_t knobs7bitPrevLS[5] = {0,0,0,0,0};
uint16_t knobs7bitHysteresis = 25;

uint8_t linFirPointer[4] = {0,0,0,0};
uint32_t linearFIR[4][LINEAR_FIR_SIZE];
uint32_t linearSmoothed[4] = {0,0,0,0};
uint32_t linearSmoothedPrev[4] = {0,0,0,0};         
uint32_t LHMuteCounter[4] = {0,0,0,0};
uint8_t LHMute[4] = {0,0,0,0};
uint8_t pitchFreeze[4] = {0,0,0,0};
int32_t pitchBendHistory[4][32];
uint16_t pitchBendHistoryPointer[4] = {0,0,0,0};

volatile int skippedNotes[32][5];
volatile int skipPointer = 0;

uint8_t bufCount = 0;
volatile uint8_t sendingMessage = 0;

uint32_t currentFloat = 0;
uint32_t mapCount = 0;

uint16_t valsCount = 0;
uint16_t mapCountExpectation = 0;
uint16_t numMappings = 0;
volatile uint8_t parseThatMF = 0;
volatile float valCheck = 0.0f;
volatile float testVal = 0.0f;
int buttonCounters[6] = {0,0,0,0,0};
int buttonStates[6] = {0,0,0,0,0};
int frettedStateLatched = 0;
int fretboard_fretless = 1;
uint8_t I2Cbuff2[4];
uint32_t SPI_errors = 0;

float filtx[4][2] = {{0.0f, 0.0f},{0.0f, 0.0f},{0.0f, 0.0f},{0.0f, 0.0f}};
float filty[4][2] = {{0.0f, 0.0f},{0.0f, 0.0f},{0.0f, 0.0f},{0.0f, 0.0f}};

uint8_t customOnMask = 0;
uint8_t simpleThreshold = 1;
uint8_t myThresh[8];

volatile uint8_t capMax[8];
volatile uint8_t capMin[8] = {255, 255, 255, 255, 255, 255, 255, 255};
volatile uint8_t capThresh[8];
volatile uint32_t timeSinceAttack = 0;
/*
CY_ISR(SleepIsr_function)
{
    if (USB_active)
    {
        //check USB activity
        if( USB_CheckActivity() != 0u ) 
        {
            usbActivityCounter = 0u;
        } 
        else 
        {
            usbActivityCounter++;
        }

    }
    //Clear pending interrupt
    SleepTimer_GetStatus();
}
*/
CY_ISR(Vbus_function)
{
    //plug or unplug event
    //check if eeprom has a flag saying you just restarted. If so, don't restart again
    //otherwise, restart
    my_Vbus_ISR_ClearPending();
    vBusPin_ClearInterrupt();
    restartSystemCheck();

}

void restartSystemCheck()
{
    eepromReturnValue = Em_EEPROM_Read(0u, eepromArray, 2u);
    //only do the restart check if there is a USB cable plugged in (to avoid restarting while trying to debug without a usb cable plugged in)
    if (USB_VBusPresent() == 1)
    {
        if (*(volatile uint8 *) &eepromArray[0] == 1u)
        {
            //a flag says we just restarted
            //write a zero so it knows next time that it's OK to restart
            array[0] = 0;
            Em_EEPROM_Write(0u,array,2u);     
            USB_check_flag = 1;
        }
        else
        {
           //otherwise, we need to restart
           array[0] = 1;
           Em_EEPROM_Write(0u,array,2u);  
            USB_Stop();
            I2C_1_Stop();
            CySoftwareReset();
        }
    }
}
volatile uint8_t framesSinceControlSend = 0;
volatile uint8_t controlToSend = 0;

int main(void)
{

	CYGlobalIntEnable; 
    while (SPI_ready_Read() == 0)
    {
        ;
    }
    
    EEPROM_Start();
    
    eepromReturnValue = Em_EEPROM_Init((uint32_t)Em_EEPROM_em_EepromStorage);
    if(eepromReturnValue != CY_EM_EEPROM_SUCCESS)
    {
       // HandleError();
    }
    USB_SetPowerStatus(USB_DEVICE_STATUS_SELF_POWERED);
    my_Vbus_ISR_StartEx(Vbus_function);
    
    if (!USB_VBusPresent())
    {
       restartSystemCheck();
    }
    
    
    IDAC8_1_Start();
	ADC_1_Start();
	AMux_1_Start();
    DmaTxConfiguration();
    DmaRxConfiguration();
    ADC_SAR_Seq_1_Start();
    ADC_SAR_Seq_1_StartConvert();
    SPIM_1_Start();
    SPIM_2_Start();
    I2C_1_Start();
    
    CyDelay(100);
    SPIM_2_ClearTxBuffer();
    for (int i = 0; i < (MAX_NUM_PRESETS + MAX_NUM_TUNINGS); i++)
    {
        SPIM_2_ClearRxBuffer();
        CyDmaChEnable(rx2Channel, STORE_TD_CFG_ONCMPLT);
        CyDmaChEnable(tx2Channel, STORE_TD_CFG_ONCMPLT);
        //make sure previous SPI2 transmission has completed before transferring the remaining midi data
        while (0u == ((SPIM_2_ReadTxStatus() & SPIM_2_STS_SPI_DONE) || (SPIM_2_ReadTxStatus() & SPIM_2_STS_SPI_IDLE )))
        {
            ;
        }    
        if (rx2Buffer[0] == 253) // message that means audio IC is sending preset names)
        {
            uint8_t whichPresetToName = rx2Buffer[1];
            if (whichPresetToName < MAX_NUM_PRESETS)
            {
                for (int i = 0; i < 14; i++)
                {
                    presetNamesArray[whichPresetToName][i] = rx2Buffer[i+2];
                }
            }
        }
        if (rx2Buffer[0] == 254) // message that means audio IC is sending preset names)
        {
            uint8_t whichTuningToName = rx2Buffer[1];
            if (whichTuningToName < MAX_NUM_TUNINGS)
            {
                for (int i = 0; i < 14; i++)
                {
                    tuningNamesArray[whichTuningToName][i] = rx2Buffer[i+2];
                }
            }
        }
    }

    //I2Cbuff1[0] = 1<<6;
    //status = I2C_MasterWriteBlocking(0x70, 1, I2C_1_MODE_COMPLETE_XFER);
    OLED_init();
    //OLEDwriteInt(0, 5, 0,FirstLine);
    //OLED_draw();
    
    
    //get the fretboard calibration data from EEPROM (unique to each Electrobass)
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int high = EEPROM_ReadByte(i*8 + j*2);
            int low = EEPROM_ReadByte(i*8 + j*2 + 1);
            fretMeasurements[i][j] = (high << 8) + low;
        }
    }
    //add other stored values
    // preset number

    currentPresetSelection = EEPROM_ReadByte(32);
    // tuning number
    currentTuningSelection = EEPROM_ReadByte(33);
    // fretted or not
    frettedState =  EEPROM_ReadByte(34);
    frettedStateLatched = frettedState;
    // open strings
    int tempByte = 35;
    
    union breakFloat theFullVal;
        
    for (int i = 0; i < 4; i++)
    {
        theFullVal.u32 = 0;
        theFullVal.u32 |= (EEPROM_ReadByte(tempByte++) << 24);
        theFullVal.u32 |= (EEPROM_ReadByte(tempByte++) << 16);
        theFullVal.u32 |= (EEPROM_ReadByte(tempByte++) << 8);
        theFullVal.u32 |= (EEPROM_ReadByte(tempByte++));
        openStringMIDI[i] = theFullVal.f;
        openStringFreqs[i] = mtof(openStringMIDI[i]);
    }
    
    //load preset
    tx2Buffer[0] = 4; //for the audio chip this message is a 4 
    tx2Buffer[1] = presetNumberToLoad;

    SPIM_2_ClearRxBuffer();
    CyDmaChEnable(rx2Channel, STORE_TD_CFG_ONCMPLT);
    CyDmaChEnable(tx2Channel, STORE_TD_CFG_ONCMPLT);
    OLED_writePreset();
    //prepare to load a tuning next round
    tuningNumberToLoad = currentTuningSelection;
    sendingMessage = 4;
    
    
    ExtMUX_EN_Write(1);
    CyDelayUs(500);
    CapSense_Start();     
    
    hp_R = 1.0f - (3.14159265358979f * 2.0f * 2.0f / 200.0f);

    tuningNamesArray[0][0] = 'E';
    tuningNamesArray[0][1] = 'T';
   CyDelay(10);
    CapSense_InitializeAllBaselines() ;
            while(CapSense_IsBusy() != 0)  
        {
            ;//wait until scan is complete
        }  
    CapSense_ScanEnabledWidgets(); 
            while(CapSense_IsBusy() != 0)  
        {
            ;//wait until scan is complete
        }  
    CapSense_ScanEnabledWidgets(); 
            while(CapSense_IsBusy() != 0)  
        {
            ;//wait until scan is complete
        }  
    CapSense_ScanEnabledWidgets(); 
            while(CapSense_IsBusy() != 0)  
        {
            ;//wait until scan is complete
        }  
    CapSense_ScanEnabledWidgets(); 
            while(CapSense_IsBusy() != 0)  
        {
            ;//wait until scan is complete
        }  
    for (int i = 0; i < 8; i++)
    {
        //myThresh[i] = CapSense_sensorRaw[i] + 80;
        myThresh[i] = 60;
    }
    //SPI_ready_Write(1);
    CyDelay(10);
    /*
    while(1)
    {
        CapSense_ScanSensor(0);
        CyDelay(1);
    }
    */
    //tSimplePoly_init(&myPoly);
	for(;;)
    {


        //turn on the multiplexer channels that set up the resistive sensors
        //#if 0
        ExtMUX_EN_Write(0);
        CyDelayUs(5);
        scanLinearResistor();

        //now disconnect resistive sensors so that they don't interfere with CapSense
       // #endif
        ExtMUX_EN_Write(1);
        CyDelayUs(5);
        
        scanButtons();
        I2C_MasterReadBlocking(0x8u, 4 ,I2C_1_MODE_COMPLETE_XFER);
        //CapSense_ClearSensors();
        //CapSense_UpdateEnabledBaselines();
        CapSense_ScanEnabledWidgets();  
        currentOutPointer = 1;
        //CapSense_ScanSensor(0); 
        //CapSense_CheckIsAnyWidgetActive();
        
        while (CapSense_IsBusy())
        {
            ;
        }
        //CyDelay(1);

        if (simpleThreshold)
        {
            customOnMask = 0;
            
            for (int i = 0; i < 8; i++)
            {
                customOnMask += ((CapSense_sensorRaw[i] > myThresh[i]) << i);
                
                //if (CapSense_sensorRaw[i] > capMax[i])
                {
                //    capMax[i] = CapSense_sensorRaw[i];
                }
                //if (CapSense_sensorRaw[i] < capMin[i])
                {
                //    capMin[i] = CapSense_sensorRaw[i];
                }
                //capThresh[i] = ((capMax[i] - capMin[i]) / 3) + capMin[i];
                //sendMIDIControlChange(i + 64, CapSense_sensorRaw[i] >> 1, 1);
            }
        }
        else
        {
            customOnMask = CapSense_sensorOnMask[0];
        }
        //sendMIDIControlChange(0 + 64, CapSense_sensorRaw[0] >> 1, 1);
        //sendMIDIControlChange(4 + 64, CapSense_sensorRaw[4] >> 1, 1);
        
        if (parseThatMF)
        {
            parseSysex();
        }
        
        for (int whichLinearSensor = 0; whichLinearSensor < 4; whichLinearSensor++)
        {
            float pitchBendVal = 8192.0;
            
             //handle string plucks/noteoffs

            if (((customOnMask >> (whichLinearSensor + 4)) & 1) &&  (linearPotValue32Bit[whichLinearSensor] == 65535))
            {
                LHMute[whichLinearSensor] = 1; 
                if ((LHMuteCounter[whichLinearSensor] < 127) && (stringStates[whichLinearSensor][0] >= 0))
                {
                    LHMuteCounter[whichLinearSensor]++;
                    //sendMIDIControlChangeComputer(116+i, LHMuteCounter[i],6);
                }

            }
            else
            {
                LHMute[whichLinearSensor] = 0;
                LHMuteCounter[whichLinearSensor] = 0;
            }

            //left hand mute just began
            //freeze pitch bend at value from 12 sends ago (to avoid dip before mute due to sensor losing contact)
            if ((LHMute[whichLinearSensor]) && (stringStates[whichLinearSensor][0])>=0)
            {
                pitchFreeze[whichLinearSensor] = 1;
            }
            else
            {
                 pitchFreeze[whichLinearSensor] = 0;             
            }
            blue_LED_Write(pitchFreeze[0]);
            //left hand mute has counted to max time
            //send note off
            if ((LHMuteCounter[whichLinearSensor] > 70) && (stringStates[whichLinearSensor][0] >= 0))
            {
                 handleNotes(lastNotes[whichLinearSensor], 0, whichLinearSensor);
            }


            
            blue_LED_Write(pitchFreeze[0]);
            //if we have read a "not pressed to fretboard" sensor reading
            if (linearPotValue32Bit[whichLinearSensor] == 65535)
            {
                //set string MIDI value to open string value
                stringMIDI[whichLinearSensor] = openStringMIDI[whichLinearSensor];

                //if we've got a pitch freeze active
                if (pitchFreeze[whichLinearSensor])
                {
                    pitchBendHistory[whichLinearSensor][pitchBendHistoryPointer[whichLinearSensor]] = pitchBendHistory[whichLinearSensor][((pitchBendHistoryPointer[whichLinearSensor] + 31) & 31)];
                    pitchBendHistoryPointer[whichLinearSensor] = (pitchBendHistoryPointer[whichLinearSensor] + 1) & 31;
                
                    //pitchBendsPerString[whichLinearSensor] = (int)pitchBendsPerString[whichLinearSensor];
                   //pitchBendsPerString[whichLinearSensor] = pitchBendsPerString[whichLinearSensor];
                }
                else
                {
                    //pitchBendHistory[whichLinearSensor][pitchBendHistoryPointer[whichLinearSensor]] = openStringMIDI[whichLinearSensor];
                    //pitchBendHistoryPointer[whichLinearSensor] =  (pitchBendHistoryPointer[whichLinearSensor] + 1) & 31;
                    
                    pitchBendsPerString[whichLinearSensor] = pitchBendVal;

                }  

            }

            //otherwise, it's pressed to the fretboard
            
            else
            {

                if (pitchFreeze[whichLinearSensor])
                {
                    pitchBendHistory[whichLinearSensor][pitchBendHistoryPointer[whichLinearSensor]] = pitchBendHistory[whichLinearSensor][((pitchBendHistoryPointer[whichLinearSensor] + 31) & 31)];
                    pitchBendHistoryPointer[whichLinearSensor] = (pitchBendHistoryPointer[whichLinearSensor] + 1) & 31;
                }
                else
                {
                    //pitchHistoryPointer gets incremented every time after the history is loaded, so here it should point to the next value, which is the oldest that hasn't been yet overwritten
                    {
                        linearFIR[whichLinearSensor][linFirPointer[whichLinearSensor]] = pitchBendHistory[whichLinearSensor][(((pitchBendHistoryPointer[whichLinearSensor])+31) & 31)];
                    }
                    //else
                    {
                        //linearFIR[whichLinearSensor][linFirPointer[whichLinearSensor]] = linearPotValue32Bit[whichLinearSensor];
                    }
                    linearSmoothed[whichLinearSensor] = 0;
                    for (int j = 0; j < LINEAR_FIR_SIZE; j++)
                    {
                        linearSmoothed[whichLinearSensor] += linearFIR[whichLinearSensor][j];
                    }             
                    linFirPointer[whichLinearSensor] = (linFirPointer[whichLinearSensor] + 1) & LINEAR_FIR_SIZE_MASK;
                    linearSmoothed[whichLinearSensor] = linearSmoothed[whichLinearSensor] >> LINEAR_FIR_SIZE_BITSHIFT;
                    //linearSmoothed[whichLinearSensor] = linearPotValue32Bit[whichLinearSensor];
                    if (calibration_mode > 0)
                    {
                        int whichStringToStore = (calibration_mode - 1) / 4;
                        int whichFretToStore =(calibration_mode - 1) % 4;
                        fretMeasurements[whichStringToStore][whichFretToStore] = linearSmoothed[whichStringToStore];
                    }
                    
                    if (fretboard_fretless)
                    {
        				if (linearSmoothed[whichLinearSensor] == 65535)
        				{
        					invStringMappedPositions[whichLinearSensor] = 1.0f;
        				}
                        else if ((linearSmoothed[whichLinearSensor] > fretMeasurements[whichLinearSensor][1]))
        				{
        					invStringMappedPositions[whichLinearSensor] = 1.0f / (map((float)linearSmoothed[whichLinearSensor], fretMeasurements[whichLinearSensor][0], fretMeasurements[whichLinearSensor][1], fretRatios[0], fretRatios[1]));
        				}
        				else if ((linearSmoothed[whichLinearSensor] <= fretMeasurements[whichLinearSensor][1]) && (linearSmoothed[whichLinearSensor] > fretMeasurements[whichLinearSensor][2]))
        				{
        					invStringMappedPositions[whichLinearSensor] = 1.0f / (map((float)linearSmoothed[whichLinearSensor], fretMeasurements[whichLinearSensor][1], fretMeasurements[whichLinearSensor][2], fretRatios[1], fretRatios[2]));
        				}
        				else
        				{
        					invStringMappedPositions[whichLinearSensor] = 1.0f / map((float)linearSmoothed[whichLinearSensor], fretMeasurements[whichLinearSensor][2], fretMeasurements[whichLinearSensor][3], fretRatios[2], fretRatios[3]);
        				}
                       
                        
                        stringMIDI[whichLinearSensor] = ftom(invStringMappedPositions[whichLinearSensor] * openStringFreqs[whichLinearSensor]);
                    }
                    else
                    {
                        stringMIDI[whichLinearSensor] = openStringMIDI[whichLinearSensor] + roundf(21.0f-((float)linearPotValue32Bit[whichLinearSensor] / 2640.0f));
                    }
                    
                    
                    pitchBendHistory[whichLinearSensor][pitchBendHistoryPointer[whichLinearSensor]] = linearPotValue32Bit[whichLinearSensor];
                    pitchBendHistoryPointer[whichLinearSensor] = (pitchBendHistoryPointer[whichLinearSensor] + 1) & 31;

                    //get vibrato by filtering unfretted signal with a highpass (computed with Max/MSP filtergraph, remember sample rate is very low, like 1Hz)    
                    float oldx = filtx[whichLinearSensor][1];
                    filtx[whichLinearSensor][1] = filtx[whichLinearSensor][0];
                    filtx[whichLinearSensor][0] = stringMIDI[whichLinearSensor];
                    
                    float oldy = filty[whichLinearSensor][1];
                    filty[whichLinearSensor][1] = filty[whichLinearSensor][0];
                    
                    float filtOut = (0.979916f * filtx[whichLinearSensor][0]) + 
                       (-1.959832f * filtx[whichLinearSensor][1]) + ( 0.979916f * oldx) - (-1.959041f * filty[whichLinearSensor][1]) - (0.960623f * oldy);
                    
                    filty[whichLinearSensor][0] = filtOut;
                    


                    if ((stringMIDI[whichLinearSensor] > (stringMIDIPrev[whichLinearSensor] + linearHysteresis)) || ((stringMIDI[whichLinearSensor] < (stringMIDIPrev[whichLinearSensor] - linearHysteresis))))
                    {
                        stringMIDIRounded[whichLinearSensor] = roundf(stringMIDI[whichLinearSensor]);
                        stringMIDIPrev[whichLinearSensor] = stringMIDIRounded[whichLinearSensor];

                        //this removes glitch in filter when fret changes suddenly
                        filtx[whichLinearSensor][0] = stringMIDIRounded[whichLinearSensor];
                        filtx[whichLinearSensor][1] = stringMIDIRounded[whichLinearSensor];
                        filty[whichLinearSensor][0] = 0.0f;
                        filty[whichLinearSensor][1] = 0.0f;

                    }
                    else
                    {
                       stringMIDIRounded[whichLinearSensor] =  stringMIDIPrev[whichLinearSensor];
                    }
                    //if you are in fretted mode, use the rounded value with the vibrato added in 
                    // (need to compute those values even if not using them, in case it switches suddenly
                    if (frettedState)
                    { 
                        stringMIDI[whichLinearSensor] = stringMIDIRounded[whichLinearSensor];// + filtOut;             
                    }
                    pitchBendVal  = ((stringMIDI[whichLinearSensor] - openStringMIDI[whichLinearSensor]) * 170.5f) + 8192.0f;
                    openStringCount[whichLinearSensor] = 0;
                    pitchBendsPerString[whichLinearSensor] = (int)pitchBendVal;
                }
            }
           
        
            //mono
            if (!polyMode)
            {     
                if (stringStates[whichLinearSensor][0] >= 0)
                {

                    if (((int)pitchBendsPerString[whichLinearSensor]) != previousPitchBendsSent)
                    {

                        sendMIDIPitchBend((uint)pitchBendsPerString[whichLinearSensor], 0);
                        previousPitchBendsSent = pitchBendsPerString[whichLinearSensor];
                    }
                }
            }
            else
            {
                if (stringStates[whichLinearSensor][0] >= 0)
                {

                    if (((int)pitchBendsPerString[whichLinearSensor]) != previousPitchBendsSentPoly[whichLinearSensor])
                    {

                        sendMIDIPitchBend((uint)pitchBendsPerString[whichLinearSensor], whichLinearSensor+1);
                        previousPitchBendsSentPoly[whichLinearSensor] = (int)pitchBendsPerString[whichLinearSensor];
                    }
                }
            }
        }
        framesSinceControlSend++;
        //read knobs, joystick, and cv pedal
        if (ADC_SAR_Seq_1_IsEndConversion(ADC_SAR_Seq_1_RETURN_STATUS))
        {
            for (int i = 0; i < 5; i++)
            {
                knobsFIR[i][firPointer] = ADC_SAR_Seq_1_GetResult16(i);
                knobs[i] = 0;
                for (int j = 0; j < KNOB_FIR_SIZE; j++)
                {
                    knobs[i] += knobsFIR[i][j];
                }             
                knobs[i] = knobs[i] >> KNOB_FIR_SIZE_BITSHIFT;
                
                //now squish down to 7 bit with hysteresis
                
                if ((knobs[i] > (knobs7bitPrevLS[i] + knobs7bitHysteresis)) || (knobs[i] < (knobs7bitPrevLS[i] - knobs7bitHysteresis)))
                {
                    knobs7bit[i] = knobs[i] >> 5;
                }
                if (knobs7bit[i] != knobs7bitPrev[i])
                {
                    if (i < 4)
                    {
                        sendMIDIControlChange(9 + i , 127-knobs7bit[i], 0);
                    }
                    if ((i == 4) && (CV_pedal_sense_Read()))
                    {
                        sendMIDIControlChange(9 + i , knobs7bit[i], 0);
                        //sendMIDIControlChange(19 + i+1 , 0, 0);
                    }
                }

                knobs7bitPrev[i] = knobs7bit[i];
                knobs7bitPrevLS[i] = knobs7bit[i] << 5;
            }
            firPointer = (firPointer + 1) & KNOB_FIR_SIZE_MASK;
            if (framesSinceControlSend > 100)
            {
                 if (controlToSend < 4)
                {
                    sendMIDIControlChange(9 + controlToSend , 127-knobs7bit[controlToSend], 0);
                }
                if ((controlToSend == 4) && (CV_pedal_sense_Read()))
                {
                    sendMIDIControlChange(9 + controlToSend , knobs7bit[controlToSend], 0);
                    //sendMIDIControlChange(19 + i+1 , 0, 0);
                }
                framesSinceControlSend = 0;
                controlToSend = (controlToSend + 1) % 5;
            }
        }
        
        //make sure previous SPI1 transmission has completed before checking the received SPI data
        while (0u == ((SPIM_1_ReadTxStatus() & SPIM_1_STS_SPI_DONE) || (SPIM_1_ReadTxStatus() & SPIM_1_STS_SPI_IDLE )))
        {
            ;
        }

        if (timeSinceAttack < 65535)
        {
            timeSinceAttack++;
        }
        for (int i = 0; i < 4; i++)
        {
            stringPlucks[i] = (rxBuffer[i*2] << 8) + rxBuffer[i*2+1];

            //note-on from pluck sensor
            if ((stringPlucks[i] > 0) && (stringPlucksPrev[i] == 0))
            {
                //sendMIDIControlChangeComputer(116+i, stringPlucks[i]/512,7);
                LHMuteCounter[i] = 0;
                pitchFreeze[i] = 0;
                octave = ((int)I2Cbuff2[1]) - 1;
                lastNotes[i] = (int)openStringMIDI[i] + (octave * 12);

                handleNotes(lastNotes[i], stringPlucks[i], i);
            }
            //note-off from pluck sensor (RH Mute)
            else if ((stringPlucks[i] == 0) && (stringPlucksPrev[i] > 0))
            {
                //sendMIDIControlChangeComputer(116+i, stringPlucks[i]/512,7);
                handleNotes(lastNotes[i], 0, i);
                LHMuteCounter[i] = 0;
            }
            

            stringPlucksPrev[i] = stringPlucks[i];
            
        }
        //make sure previous SPI2 transmission has completed before transferring the remaining midi date
        while (0u == ((SPIM_2_ReadTxStatus() & SPIM_2_STS_SPI_DONE) || (SPIM_2_ReadTxStatus() & SPIM_2_STS_SPI_IDLE )))
        {
            ;
        }
        //send midi data to internal synth
        //copy the temp buffer into the send buffer now that we are done filling it and sending the previous one
        if (!sendingMessage)
        {
            for (uint i = 0 ; i < BUFFER_2_SIZE; i++)
            {
                tx2Buffer[i] = tx2BufferTemp[i];
                tx2BufferTemp[i] = 0;
            }
            if (outChanged)
            {
                tx2Buffer[0] = 1;
            }
            else
            {
                tx2Buffer[0] = 0;
            }
            outChanged = 0;
        }
        else if(sendingMessage == 1) //sending preset to audio chip
        {
            if (sendMessageEnd) //send end message
            {
                tx2Buffer[0] = 253;
                tx2Buffer[1] = presetNumberToWrite;
                currentPresetSelection = presetNumberToWrite;
                //display previous preset as loaded
                sendCurrentPresetNumber();
               // OLED_invert(0);
                sendMessageEnd = 0;
                sendingMessage = 0;
                messageArraySendCount = 0;
                
            }
            else //send chunks
            {
                //send the next preset Chunkkkkk
                tx2Buffer[0] = 2;
                tx2Buffer[1] = presetNumberToWrite;
                for (uint i = 2 ; i < BUFFER_2_SIZE; i++)
                {
                    if (messageArraySendCount < messageArraySize)
                    {
                        tx2Buffer[i] = presetArray[messageArraySendCount++];
                    }
                    else
                    {
                        tx2Buffer[i] = 0xee; // preset end ack   - done, next send a message that s
                        sendMessageEnd = 1;
                    }
                }
            }
        } 
        else if (sendingMessage == 2) //sending tuning
        {
            if (sendMessageEnd) //send end message
            {
                tx2Buffer[0] = 253;
                tx2Buffer[1] = tuningNumberToWrite;
                sendMessageEnd = 0;
                sendingMessage = 0;
                messageArraySendCount = 0;
            }
            else //send chunks
            {
                //send the next preset Chunkkkkk
                tx2Buffer[0] = 3;
                tx2Buffer[1] = tuningNumberToWrite;
                for (uint i = 2 ; i < BUFFER_2_SIZE; i++)
                {
                    if (messageArraySendCount < messageArraySize)
                    {
                        tx2Buffer[i] = tuningArray[messageArraySendCount++];
                    }
                    else
                    {
                        tx2Buffer[i] = 0xee; // preset end ack   - done, next send a message that s
                        sendMessageEnd = 1;
                    }
                }
            }
        }
        
        else if (sendingMessage == 3) // 3 means load a preset
        {
            tx2Buffer[0] = 4; //for the audio chip this message is a 4 
            tx2Buffer[1] = presetNumberToLoad;
            sendingMessage = 0;
        }

        else if (sendingMessage == 4) //4  means load a tuning
        {
            tx2Buffer[0] = 5; //for the audio chip this message is a 4 
            tx2Buffer[1] = tuningNumberToLoad;
            sendingMessage = 0;
        }

        
        
        if (currentOutPointer > BUFFER_2_SIZE)
        {
            //LED1_Write(1);
            //overflow
        }
        currentOutPointer = 1;
        if (rx2Buffer[0] == 253) // message that means audio IC is sending preset names)
        {
            uint8_t whichPresetToName = rx2Buffer[1];
            if ((parsingSysex != 1) && (sendingMessage == 0) && (whichPresetToName != currentPresetSelection))
            {
                if (whichPresetToName < MAX_NUM_PRESETS)
                {
                    for (int i = 0; i < 14; i++)
                    {
                        presetNamesArray[whichPresetToName][i] = rx2Buffer[i+2];
                    }
                }
            }
        }
        
        if (rx2Buffer[0] == 254) // message that means audio IC is sending tuning names)
        {
            uint8_t whichTuningToName = rx2Buffer[1];
            if ((parsingSysex != 1) && (sendingMessage == 0) && (whichTuningToName != currentTuningSelection))
            {
                if (whichTuningToName < MAX_NUM_TUNINGS)
                {
                    for (int i = 0; i < 14; i++)
                    {
                        tuningNamesArray[whichTuningToName][i] = rx2Buffer[i+2];
                    }
                }
            }
        }
        
        if (tx2Buffer[0] > 0 )
        {
            SPIM_2_ClearRxBuffer();
            CyDmaChEnable(rx2Channel, STORE_TD_CFG_ONCMPLT);
            CyDmaChEnable(tx2Channel, STORE_TD_CFG_ONCMPLT);
        }
        //check if USB device has just been plugged in
        if (USB_check_flag)
        {
            checkUSB_Vbus();
        }
        
        //only service the USB bus if there is a computer plugged in
        if ((USB_active) && (USB_VBusPresent()))
        {
            if (midiSent > 64)
            {
                midiOverflow++;
            }
            midiSent = 0;
            USB_service();
        }
               
/*
        while(CapSense_IsBusy() != 0)  
        {
            ;//wait until scan is complete
        }  

        CapSense_CheckIsAnyWidgetActive();
   */     
        txBuffer[8] = customOnMask;
        for (int whichLinearSensor = 0; whichLinearSensor < 4; whichLinearSensor++)
        {
            txBuffer[whichLinearSensor*2] = ((uint16_t) linearPotValue32Bit[whichLinearSensor]) >> 8;
            txBuffer[whichLinearSensor*2+1] = linearPotValue32Bit[whichLinearSensor] & 0xff;
        }
        txBuffer[15] = bufCount % 16;
        bufCount++;
        
        if (txBuffer[8] & 1)
        {
            blue_LED_Write(1);
            
        }
        else
        {
            blue_LED_Write(0);
           
        }
        SPIM_1_ClearRxBuffer();

        //send SPI data
        CyDmaChEnable(rxChannel, STORE_TD_CFG_ONCMPLT);
        CyDmaChEnable(txChannel, STORE_TD_CFG_ONCMPLT);

        timeSinceLastAttack++;
     }
}

void checkUSB_Vbus(void)
{
   if (USB_VBusPresent() == 0)
   {
       USB_Stop();
       USB_active = 0; 
   }
   else if (USB_active == 0 )
   {
       USB_Start(0u, USB_5V_OPERATION ); 
        while (0u == USB_GetConfiguration());
        USB_MIDI_EP_Init();
       USB_active = 1;
   }
   USB_check_flag = 0;
}

void USB_service(void)
{
    if(USB_IsConfigurationChanged() != 0u)
    {
        if(USB_GetConfiguration() != 0u)   
        {
           // Sleep_isr_StartEx(SleepIsr_function);
            
            //SleepTimer_Start();
        	
            if ((USB_active) && (USB_VBusPresent()))
            {
                USB_MIDI_EP_Init();
            }
        }
        else
        {
            //SleepTimer_Stop();
        }    
    }        
    
    if(USB_GetConfiguration() != 0u)    
    {

         /* Reinitialize after SET_CONFIGURATION or SET_INTERFACE Requests */
        if(USB_IsConfigurationChanged() != 0x00)
        {
            USB_LoadInEP(USB_midi_in_ep, USB_midiInBuffer,(uint16) USB_midiInPointer);
            //USB_LoadInEP(USB_midi_in_ep, USB_midiInBuffer, 64);
            USB_ReadOutEP(USB_midi_out_ep,USB_midiOutBuffer, 64);
                                             /* configuring the DMAs for the first time only, the data as soon as received
                                             in the EP buffer is Transferred by DMA to the buffer as defined here with no CPU intervention */
            USB_EnableOutEP(USB_midi_out_ep);       /* Note 3.*/
        }
        if ((USB_active) && (USB_VBusPresent()))
        {
            USB_MIDI_IN_Service();
        }



        if ((USB_active) && (USB_VBusPresent()))
        {
            USB_MIDI_OUT_Service();
        }
    }
        
}


#define NUM_MACROS 8
volatile float presetCheck[400];

void parseSysex(void)
{
    parsingSysex = 1;
    
     if (sysexBuffer[0] == 0)
    {
        sysexMessageInProgress = 1; // set a flag that we've started a sysex preset transfer. May take multiple sysex parse calls on the chunks to complete
        currentFloat = 0;
        presetArraySection = presetName;
        presetNumberToWrite = sysexBuffer[1];
        
        union breakFloat theVal;
        uint32_t i = 2;
        uint8_t stoppingPoint = NAME_LENGTH_IN_BYTES+2;
        for (; i < stoppingPoint; i++)
        {
            presetArray[i-2] = sysexBuffer[i] & 127; // pass on the first 14 elements as 8-bit bytes (they are the chars for the name string)
            presetNamesArray[presetNumberToWrite][i-2] = sysexBuffer[i] & 127;
        }
        
        presetArraySection = macroNames;

        
        for (int j = 0; j < NUM_MACROS; j++)
        {
            for (int k = 0; k < NAME_LENGTH_IN_BYTES; k++)
            {
                presetArray[i-2] = sysexBuffer[i] & 127; // pass on the first 14 elements as 8-bit bytes (they are the chars for the name string)
                //don't actually need to store macro names in the Electrobass, since we can't access them right now
                //macroNamesArray[presetNumberToWrite][j][k] = sysexBuffer[i] & 127; // pass on the first 14 elements as 8-bit bytes (they are the chars for the name string)
                i++;
            }
        }
        
        uint16_t valsStart = NAME_LENGTH_IN_BYTES + (NAME_LENGTH_IN_BYTES * NUM_MACROS);
        
        presetArraySection = initialVals;
        
        for (; i < sysexPointer; i = i+5)
        {
            theVal.u32 = 0;
            theVal.u32 |= ((sysexBuffer[i] &15) << 28);
            theVal.u32 |= (sysexBuffer[i+1] << 21);
            theVal.u32 |= (sysexBuffer[i+2] << 14);
            theVal.u32 |= (sysexBuffer[i+3] << 7);
            theVal.u32 |= (sysexBuffer[i+4] & 127);
            testVal = theVal.f;
            if (presetArraySection == initialVals)
            {

                if (currentFloat == 0)
                {
                    valsCount = (uint16_t) theVal.f;
                    presetArray[valsStart + currentFloat++] = valsCount >> 8;
                    presetArray[valsStart + currentFloat++] = valsCount & 0xff;
                }
                else if (currentFloat < ((valsCount+1)*2))
                { 
                    uint16_t intVal = (uint16_t)(theVal.f * 65535.0f);
                    presetArray[valsStart + currentFloat++] = intVal >> 8;
                    presetArray[valsStart + currentFloat++] = intVal & 0xff;
                    presetCheck[currentFloat] = theVal.f;
                }
                else if (currentFloat == ((valsCount+1)*2))
                {
                    valCheck = theVal.f;
                    if ((valCheck < -1.5f) && (valCheck > -2.5f))
                    {
                        presetArray[valsStart + currentFloat++] = 0xef;
                        presetArray[valsStart + currentFloat++] = 0xef;
                        presetArraySection = mapCountNext;
                        mapCount = 0;
                    }
                    else
                    {
                        //error state
                        SPI_errors++;
                        sysexMessageInProgress = 0;
                        sysexPointer = 0;
                        sendingMessage = 0;
                        parseThatMF = 0;
                    }
                }
            }
            else if (presetArraySection == mapCountNext)
            {
                mapCountExpectation = (uint16_t)theVal.f;
                presetArray[valsStart + currentFloat++] = mapCountExpectation >> 8;
                presetArray[valsStart + currentFloat++] = mapCountExpectation & 0xff;
                presetArraySection = mapping;
                numMappings = 0;
            }
            else if (presetArraySection == mapping)
            {
                // this is the order
                // source (int), target (int), scalarSource (arrives as -1.0f if no scalar, send as 255 if no scalar)(int), range (float -1.0 to 1.0)
                if (numMappings < mapCountExpectation)
                {
                    if ((mapCount % 4) == 0)
                    {
                        presetArray[valsStart + currentFloat++] = (uint8_t)theVal.f;
                    }
                    else if  (mapCount % 4 == 1)
                    {
                        presetArray[valsStart + currentFloat++] = (uint8_t)theVal.f;
                    }
                    else if (mapCount % 4 == 2) //check if the scalar source is -1 (if so send 255 instead of a valid source number)
                    {
                        if (theVal.f < 0.0f)
                        {
                             presetArray[valsStart + currentFloat++] = 0xff;
                        }
                        else
                        {
                             presetArray[valsStart + currentFloat++] = (uint8_t)theVal.f;
                        }
                    }
                    else
                    {
                        int16_t intVal = (int16_t)(theVal.f * 32767.0f); //keep it signed to allow negative numbers
                        presetArray[valsStart + currentFloat++] = intVal >> 8;
                        presetArray[valsStart + currentFloat++] = intVal & 0xff;
                        numMappings++;
                    }
                    mapCount++;
                }
                

                else
                {
                    //mapcount ended
                    if ((theVal.f < -2.5f) && (theVal.f > -3.5f))
                    {
                        presetArray[valsStart + currentFloat++] = 0xfe;
                        presetArray[valsStart + currentFloat++] = 0xfe;
                        presetArraySection = presetEnd;
                        sysexMessageInProgress = 0;
                        sendingMessage = 1;
                        messageArraySize = valsStart + currentFloat;
                    }
                    else
                    {
                        //error state
                        SPI_errors++;
                        sysexMessageInProgress = 0;
                        sysexPointer = 0;
                        sendingMessage = 0;
                        parseThatMF = 0;
                    }
                }
            }
            
        }
    }
    
    #if 0
    //0 = it's a preset
    if (sysexBuffer[0] == 0)
    {
        
        
        //if (sysexBuffer[2] == 0)
        {
            sysexMessageInProgress = 1; // set a flag that we've started a sysex preset transfer. May take multiple sysex parse calls on the chunks to complete
            currentFloat = 0;
            presetArraySection = presetName;
        }
        presetNumberToWrite = sysexBuffer[1];
        
        union breakFloat theVal;
        uint32_t i = 2;
        for (; i < 16; i++)
        {
            presetArray[i-2] = sysexBuffer[i] & 127; // pass on the first 14 elements as 8-bit bytes (they are the chars for the name string)
            presetNamesArray[presetNumberToWrite][i-2] = sysexBuffer[i] & 127;
        }
        uint16_t valsStart = 14;
        
        presetArraySection = initialVals;
        for (; i < sysexPointer; i = i+5)
        {
            theVal.u32 = 0;
            theVal.u32 |= ((sysexBuffer[i] &15) << 28);
            theVal.u32 |= (sysexBuffer[i+1] << 21);
            theVal.u32 |= (sysexBuffer[i+2] << 14);
            theVal.u32 |= (sysexBuffer[i+3] << 7);
            theVal.u32 |= (sysexBuffer[i+4] & 127);
            testVal = theVal.f;
            if (presetArraySection == initialVals)
            {

                if (currentFloat == 0)
                {
                    valsCount = (uint16_t) theVal.f;
                    presetArray[valsStart + currentFloat++] = valsCount >> 8;
                    presetArray[valsStart + currentFloat++] = valsCount & 0xff;
                }
                else if (currentFloat < ((valsCount+1)*2))
                { 
                    uint16_t intVal = (uint16_t)(theVal.f * 65535.0f);
                    presetArray[valsStart + currentFloat++] = intVal >> 8;
                    presetArray[valsStart + currentFloat++] = intVal & 0xff;
                }
                else if (currentFloat == ((valsCount+1)*2))
                {
                    valCheck = theVal.f;
                    if ((valCheck < -1.5f) && (valCheck > -2.5f))
                    {
                        presetArray[valsStart + currentFloat++] = 0xef;
                        presetArray[valsStart + currentFloat++] = 0xef;
                        presetArraySection = mapCountNext;
                        mapCount = 0;
                    }
                    else
                    {
                        //error state
                        SPI_errors++;
                        sysexMessageInProgress = 0;
                        sysexPointer = 0;
                        sendingMessage = 0;
                        parseThatMF = 0;
                    }
                }
            }
            else if (presetArraySection == mapCountNext)
            {
                mapCountExpectation = (uint16_t)theVal.f;
                presetArray[valsStart + currentFloat++] = mapCountExpectation >> 8;
                presetArray[valsStart + currentFloat++] = mapCountExpectation & 0xff;
                presetArraySection = mapping;
                numMappings = 0;
            }
            else if (presetArraySection == mapping)
            {
                // this is the order
                // source (int), target (int), scalarSource (arrives as -1.0f if no scalar, send as 255 if no scalar)(int), range (float -1.0 to 1.0)
                if (numMappings < mapCountExpectation)
                {
                    if ((mapCount % 4) == 0)
                    {
                        presetArray[valsStart + currentFloat++] = (uint8_t)theVal.f;
                    }
                    else if  (mapCount % 4 == 1)
                    {
                        presetArray[valsStart + currentFloat++] = (uint8_t)theVal.f;
                    }
                    else if (mapCount % 4 == 2) //check if the scalar source is -1 (if so send 255 instead of a valid source number)
                    {
                        if (theVal.f < 0.0f)
                        {
                             presetArray[valsStart + currentFloat++] = 0xff;
                        }
                        else
                        {
                             presetArray[valsStart + currentFloat++] = (uint8_t)theVal.f;
                        }
                    }
                    else
                    {
                        int16_t intVal = (int16_t)(theVal.f * 32767.0f); //keep it signed to allow negative numbers
                        presetArray[valsStart + currentFloat++] = intVal >> 8;
                        presetArray[valsStart + currentFloat++] = intVal & 0xff;
                        numMappings++;
                    }
                    mapCount++;
                }
                

                else
                {
                    //mapcount ended
                    if ((theVal.f < -2.5f) && (theVal.f > -3.5f))
                    {
                        presetArray[valsStart + currentFloat++] = 0xfe;
                        presetArray[valsStart + currentFloat++] = 0xfe;
                        presetArraySection = presetEnd;
                        sysexMessageInProgress = 0;
                        sendingMessage = 1;
                        messageArraySize = valsStart + currentFloat;
                    }
                    else
                    {
                        //error state
                        SPI_errors++;
                        sysexMessageInProgress = 0;
                        sysexPointer = 0;
                        sendingMessage = 0;
                        parseThatMF = 0;
                    }
                }
            }
            
        }
    }
    #endif
    else if (sysexBuffer[0] == 1) //its a tuning
    {
        
        sysexMessageInProgress = 1; // set a flag that we've started a sysex preset transfer. May take multiple sysex parse calls on the chunks to complete
        currentFloat = 14;
        tuningNumberToWrite = sysexBuffer[1];
        for (int i = 2; i < NAME_LENGTH_IN_BYTES+2; i++)
        {
            tuningNamesArray[tuningNumberToWrite][i-2] = sysexBuffer[i] & 127;
            tuningArray[i-2] = sysexBuffer[i] & 127;
        }
        union breakFloat theVal;
        for (uint32_t i = 16; i < sysexPointer; i = i+5)
        {
            theVal.u32 = 0;
            theVal.u32 |= ((sysexBuffer[i] &15) << 28);
            theVal.u32 |= (sysexBuffer[i+1] << 21);
            theVal.u32 |= (sysexBuffer[i+2] << 14);
            theVal.u32 |= (sysexBuffer[i+3] << 7);
            theVal.u32 |= (sysexBuffer[i+4] & 127);
            testVal = theVal.f;
            uint16_t intVal = (uint16_t)(theVal.f * 512.0f);//(uint16_t)(theVal.f * 65535.0f);
            tuningArray[currentFloat++] = intVal >> 8;
            tuningArray[currentFloat++] = intVal & 0xff;
        }
        
        tuningArray[currentFloat++] = 0xef;
        tuningArray[currentFloat++] = 0xef;
                        
        
        messageArraySize = currentFloat;
                    
        if(messageArraySize != TUNING_ARRAY_SIZE)
        {
            //error state
            SPI_errors++;
            sysexMessageInProgress = 0;
            sysexPointer = 0;
            sendingMessage = 0;
            parseThatMF = 0;
        } else 
        {
            sysexMessageInProgress = 0;
            sendingMessage = 2;
        }
    }
    
    else if (sysexBuffer[0] == 3) //its an open string setting
    {
        
        sysexMessageInProgress = 1; // set a flag that we've started a sysex preset transfer. May take multiple sysex parse calls on the chunks to complete
        currentFloat = 0;
        int openStringNumber = 0;
        union breakFloat theVal;
        int tempByte = 35;
        for (uint32_t i = 2; i < sysexPointer; i = i+5)
        {
            theVal.u32 = 0;
            theVal.u32 |= ((sysexBuffer[i] &15) << 28);
            theVal.u32 |= (sysexBuffer[i+1] << 21);
            theVal.u32 |= (sysexBuffer[i+2] << 14);
            theVal.u32 |= (sysexBuffer[i+3] << 7);
            theVal.u32 |= (sysexBuffer[i+4] & 127);
            testVal = theVal.f;
            
            openStringMIDI[openStringNumber % 4] = testVal;
            openStringFreqs[openStringNumber % 4] = mtof(testVal);
            openStringNumber++;
            
            EEPROM_WriteByte((theVal.u32 >> 24) & 255, tempByte++);
            EEPROM_WriteByte((theVal.u32 >> 16) & 255, tempByte++);
            EEPROM_WriteByte((theVal.u32 >> 8) & 255, tempByte++);
            EEPROM_WriteByte(theVal.u32 & 255, tempByte++);
        }
    }
    parsingSysex = 0;
    sysexPointer = 0;
    parseThatMF = 0;
}



volatile uint8_t tempMIDI[4];
volatile uint8_t firstSysex = 0;
const uint16_t sysexPointerMask = 2047;

//data sent from computer
void USB_callbackLocalMidiEvent(uint8 cable, uint8 *midiMsg) CYREENTRANT
{
    //tempMIDI[0] = midiMsg[0];
    //tempMIDI[1] = midiMsg[1];
    //tempMIDI[2] = midiMsg[2];
    //tempMIDI[3] = midiMsg[3];
    //check that we got here
    if (receivingSysex)
    {
        for (int i = 0; i < 3; i++)
        {
            if (midiMsg[i] < 128)
            {
                sysexBuffer[(sysexPointer++) & sysexPointerMask] = midiMsg[i];
            }
            else
            {
                if (midiMsg[i] == USB_MIDI_EOSEX)
                {
                    receivingSysex = 0;
                    //parseSysex();
                    return;
                 }
            }
        }
    }
    else if (midiMsg[USB_EVENT_BYTE0] == USB_MIDI_SYSEX)
    {
        if (!parsingSysex)
        {

            if (midiMsg[1] == 126) // special message saying that sysex multi-chunk transmission is finished. Parse it!
            {
                parseThatMF = 1;

                //sysexPointer = 0;
            }
            else if (midiMsg[1] == 0 || midiMsg[1] == 1 || midiMsg[1] == 3)
            {
                receivingSysex = 1;
                
                // if this is the first chunk, put in the first and second elements (following chunks need this data stripped until the final message gets sent)
                if (sysexPointer == 0)
                {

                    sysexBuffer[sysexPointer++ & sysexPointerMask] = midiMsg[1];
                    sysexBuffer[sysexPointer++ & sysexPointerMask] = midiMsg[2];
                }
            }
        }
    }
    cable = cable;
}

volatile uint16_t missedNotes = 0;

void sendMIDINoteOn(int MIDInoteNum, int velocity, int channel)
{  
   
    midiMsg[0] = USB_MIDI_NOTE_ON + channel;
    midiMsg[1] = MIDInoteNum;
    midiMsg[2] = velocity;	
    if ((USB_active) && (USB_VBusPresent()))
    {
        USB_PutUsbMidiIn(3u, midiMsg, USB_MIDI_CABLE_00);
    } 
    midiSent += 4;
    if (currentOutPointer < (BUFFER_2_SIZE - 4))
    {
        tx2BufferTemp[currentOutPointer++] = midiMsg[0];
        tx2BufferTemp[currentOutPointer++] = midiMsg[1];
        tx2BufferTemp[currentOutPointer++] = midiMsg[2];
        outChanged = 1;
    }
    else 
    {
        missedNotes++;
    }
    if (velocity > 0)
    {
        //LED1_Write(1);
    }
    else
    {
       // LED1_Write(0);
    }

    
}

void sendMIDIPitchBend(int val, int channel)
{
    midiMsg[0] = USB_MIDI_PITCH_BEND_CHANGE + channel;
    midiMsg[1] = (val & 127); //LSB
    midiMsg[2] = (val >> 7);	//MSB		

    //MIDI1_UART_PutArray(midiMsg, 3);
    
    if ((USB_active) && (USB_VBusPresent()))
    {
        USB_PutUsbMidiIn(3u, midiMsg, USB_MIDI_CABLE_00);
    } 
    midiSent += 4;
    if (currentOutPointer < (BUFFER_2_SIZE - 4))
    {
        tx2BufferTemp[currentOutPointer++] = midiMsg[0];
        tx2BufferTemp[currentOutPointer++] = midiMsg[1];
        tx2BufferTemp[currentOutPointer++] = midiMsg[2];
        outChanged = 1;
    }
    else
    {
        missedNotes++;
    }

}


void sendMIDIControlChange(int CCnum, int CCval, int channel)
{
    midiMsg[0] = USB_MIDI_CONTROL_CHANGE + channel;
    midiMsg[1] = CCnum;
    midiMsg[2] = CCval;			
    //MIDI1_UART_PutArray(midiMsg, 3);
    
    if ((USB_active) && (USB_VBusPresent()))
    {
        USB_PutUsbMidiIn(3u, midiMsg, USB_MIDI_CABLE_00);
    } 
    midiSent += 4;
    if (currentOutPointer < (BUFFER_2_SIZE - 4))
    {
        tx2BufferTemp[currentOutPointer++] = midiMsg[0];
        tx2BufferTemp[currentOutPointer++] = midiMsg[1];
        tx2BufferTemp[currentOutPointer++] = midiMsg[2];
            outChanged = 1;
    }
    else
    {
        missedNotes++;
    }
    
}


void sendMIDIControlChangeComputer(int CCnum, int CCval, int channel)
{
    midiMsg[0] = USB_MIDI_CONTROL_CHANGE + channel;
    midiMsg[1] = CCnum;
    midiMsg[2] = CCval;			
    //MIDI1_UART_PutArray(midiMsg, 3);
    
    if ((USB_active) && (USB_VBusPresent()))
    {
        USB_PutUsbMidiIn(3u, midiMsg, USB_MIDI_CABLE_00);
    } 
    midiSent += 4;
    
}


int32 iVtherm = 0;

volatile int32_t linearSensorZero[3];

volatile float linearSensoriRes;

void scanLinearResistor(void)
{
    int32 iVref = 0;
    int32 iRes = 0;
    int32 offset = 0;
    
     for (int whichLinearSensor = 0; whichLinearSensor < 4; whichLinearSensor++)
     {
        ExtMUXS0_Write(whichLinearSensor & 1);
        ExtMUXS1_Write((whichLinearSensor & 2)>>1);

        scanPart = 0;

        //if (scanPart == 0)
        {
            AMux_1_FastSelect(scanPart);
            CyDelayUs(4); 
            ADC_1_StartConvert();
            ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
            iVtherm = ADC_1_GetResult32();
            
        }
        scanPart = 1;
       // else
        {

            AMux_1_FastSelect(scanPart);
            CyDelayUs(4); 
            ADC_1_StartConvert();
            ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
            iVref = ADC_1_GetResult32();

            iVref =   iVref - offset;
            //to print out sensor values to check in Max/MSP
            #if 0
            if (whichLinearSensor == 0)
            {
                sendMIDIControlChange(103,iVref >> 9, 4);
                sendMIDIControlChange(104,iVref >> 7, 4);
                sendMIDIControlChange(105,iVref & 127, 4);
                
                sendMIDIControlChange(106,iVtherm >> 9, 4);
                sendMIDIControlChange(107,iVtherm >> 7, 4);
                sendMIDIControlChange(108,iVtherm & 127, 4);
            }
            #endif
            if ((iVref > 1000) && (iVtherm < 100))
            {
                iRes = 65535;
            }
            else
            {
                if (fretboard_fretless)
                {
                    iRes = (int32)(((float)iVref / (float)iVtherm) * 20000.0f); //FRETLESS
                }
                else
                {
                    iRes = (int32)(((float)iVref / (float)iVtherm) * 10000.0f); // FRETTED
                }
                //
            }
            
            linearPotValue32Bit[whichLinearSensor] = iRes;
            //sendMIDIControlChangeComputer(116+whichLinearSensor, iRes / 512, 2);
            //whichLinearSensor = (whichLinearSensor + 1) & 3;
        }
        
        scanPart = (scanPart + 1) & 1;
        //scanPart = 0;
    }
}

void DmaTxConfiguration()
{
    /* Init DMA, 1 byte bursts, each burst requires a request */ 
    txChannel = DMA_1_TX_DmaInitialize(DMA_TX_BYTES_PER_BURST, DMA_TX_REQUEST_PER_BURST, 
                                        HI16(DMA_TX_SRC_BASE), HI16(DMA_TX_DST_BASE));

    txTD = CyDmaTdAllocate();

    /* Configure this Td as follows:
    *  - Increment the source address, but not the destination address   
    */
    CyDmaTdSetConfiguration(txTD, BUFFER_SIZE, CY_DMA_DISABLE_TD, TD_INC_SRC_ADR);

    /* From the memory to the SPIM */
    CyDmaTdSetAddress(txTD, LO16((uint32)txBuffer), LO16((uint32) SPIM_1_TXDATA_PTR));
    
    /* Associate the TD with the channel */
    CyDmaChSetInitialTd(txChannel, txTD); 
    
    ////
    
        /* Init DMA, 1 byte bursts, each burst requires a request */ 
    tx2Channel = DMA_2_TX_DmaInitialize(DMA_TX_BYTES_PER_BURST, DMA_TX_REQUEST_PER_BURST, 
                                        HI16(DMA_TX_SRC_BASE), HI16(DMA_TX_DST_BASE));

    tx2TD = CyDmaTdAllocate();

    /* Configure this Td as follows:
    *  - Increment the source address, but not the destination address   
    */
    CyDmaTdSetConfiguration(tx2TD, BUFFER_2_SIZE, CY_DMA_DISABLE_TD, TD_INC_SRC_ADR);

    /* From the memory to the SPIM */
    CyDmaTdSetAddress(tx2TD, LO16((uint32)tx2Buffer), LO16((uint32) SPIM_2_TXDATA_PTR));
    
    /* Associate the TD with the channel */
    CyDmaChSetInitialTd(tx2Channel, tx2TD); 
}    

void DmaRxConfiguration()
{ 
    /* Init DMA, 1 byte bursts, each burst requires a request */ 
    rxChannel = DMA_1_RX_DmaInitialize(DMA_RX_BYTES_PER_BURST, DMA_RX_REQUEST_PER_BURST,
                                     HI16(DMA_RX_SRC_BASE), HI16(DMA_RX_DST_BASE));

    rxTD = CyDmaTdAllocate();
    
    /* Configure this Td as follows:
    *  - Increment the destination address, but not the source address
    */
    CyDmaTdSetConfiguration(rxTD, BUFFER_SIZE, CY_DMA_DISABLE_TD, TD_INC_DST_ADR);

    /* From the SPIM to the memory */
    CyDmaTdSetAddress(rxTD, LO16((uint32)SPIM_1_RXDATA_PTR), LO16((uint32)rxBuffer));

    /* Associate the TD with the channel */
    CyDmaChSetInitialTd(rxChannel, rxTD);
    
    
    
    ///
    
        /* Init DMA, 1 byte bursts, each burst requires a request */ 
    rx2Channel = DMA_2_RX_DmaInitialize(DMA_RX_BYTES_PER_BURST, DMA_RX_REQUEST_PER_BURST,
                                     HI16(DMA_RX_SRC_BASE), HI16(DMA_RX_DST_BASE));

    rx2TD = CyDmaTdAllocate();
    
    /* Configure this Td as follows:
    *  - Increment the destination address, but not the source address
    */
    CyDmaTdSetConfiguration(rx2TD, BUFFER_2_SIZE, CY_DMA_DISABLE_TD, TD_INC_DST_ADR);

    /* From the SPIM to the memory */
    CyDmaTdSetAddress(rx2TD, LO16((uint32)SPIM_2_RXDATA_PTR), LO16((uint32)rx2Buffer));

    /* Associate the TD with the channel */
    CyDmaChSetInitialTd(rx2Channel, rx2TD);
}

uint8 I2C_MasterReadBlocking(uint8 i2CAddr, uint16 nbytes, uint8_t mode)
{
    
    uint8 volatile status;

    status = I2C_1_MasterReadBuf(i2CAddr, (uint8 *)&I2Cbuff2, nbytes,
                                     mode);

    return status;
}

uint8 I2C_MasterWriteBlocking(uint8 i2CAddr, uint16 nbytes, uint8_t mode)
{
    

        uint8 volatile status;

    uint32_t timeout = 50000;
    status = I2C_1_MasterClearStatus();
    if(!(status & I2C_1_MSTAT_ERR_XFER))
    {
        status = I2C_1_MasterWriteBuf(i2CAddr, (uint8 *)&I2Cbuff1, nbytes,
                                     mode);
        if(status == I2C_1_MSTR_NO_ERROR)
        {
            /* wait for write complete and no error */
            do
            {
                status = I2C_1_MasterStatus();
                timeout--;
                if (status == I2C_1_MSTAT_ERR_XFER)
                {
                    //I2C_reset();
                }
                if (timeout == 0)
                {
                    status = I2C_1_MSTAT_ERR_XFER;
                    //I2C_reset();
                }
                /*
                if (status == 0)
                {
                    status = I2C_1_MSTAT_ERR_XFER;
                    I2C_reset();
                }
                */
            } while(((status & (I2C_1_MSTAT_WR_CMPLT | I2C_1_MSTAT_ERR_XFER)) == 0u) && (status != 0u) && (timeout>0));
        }
        else
        {
            /* translate from I2CM_MasterWriteBuf() error output to
            *  I2CM_MasterStatus() error output */
            status = I2C_1_MSTAT_ERR_XFER;
            //I2C_reset();
        } 
    }  

    return status;
}

//velocity comes in as a 16 bit number from 0-65*** 
//not in decibels, raw amplitude value
int counter2 = 1;
void handleNotes(int note, int velocity, int string)
{
    //static int counter = 1;
    //velocity = (counter2 * 6553);
    //counter2 = (counter2 + 1) % 10;
    if (velocity > 0)
    {
        //velocity = (((sqrtf((float)velocity) * 0.00001525878903f) - .0239372430f) * 130.114584436252734f);
        float tempVel = (float)velocity;
        tempVel = tempVel * 0.00001525878903f;
        tempVel = sqrtf(tempVel);
        tempVel = tempVel - 0.0239372430f;
        tempVel = tempVel * 130.114584436252734f;
        velocity = (int)tempVel;
        

        if (velocity > 127)
        {
            velocity = 127;
        }
        
    }
    if (polyMode)
    {
        sendMIDINoteOn(note, velocity, string+1);
        stringStates[string][0] = velocity;
    }
    else
    {
        int loudestSoundingNote = 0;
        if (velocity > 0)
        {
            // find the loudest currently sounding note
            for (int i = 0; i < 4; i++)
            {
                if (stringStates[i][1] > loudestSoundingNote)
                {
                    loudestSoundingNote = stringStates[i][1];
                    loudestString = i;
                }
            }
            //make sure if there is a sounding note that this one is not much lower velocity
            //(would maybe mean this is just sympathetic bridge resonance and shouldn't interrupt the monophonic handling)
            // maybe need more complexity in time since attack? // or maybe do active suppression in the pluck detector board by summing strings with the inverse of the nearby strings
            uint8_t ignore = 0;
            if (velocity < 3) // 25
            {
                ignore = 1;   
            }
            else if ((loudestSoundingNote >=70) && (velocity <= 50))
            {
                if (timeSinceAttack < 20)
                {
                    ignore = 1;
                }
            }
            
            if (!ignore)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (stringStates[i][0] >= 0)
                    {

                        sendMIDINoteOn(stringStates[i][0], 0, 0);
                        stringStates[i][0] = -1;
                        stringStates[i][1] = 0;
                    }
                    openStringCount[i] = 10;
                }
                timeSinceAttack = 0;
                stringStates[string][0] = note;
                stringStates[string][1] = velocity;
                 pitchFreeze[string] = 0;
                sendMIDINoteOn(note, velocity, 0);
                 LHMuteCounter[string] = 0;
                 LHMute[string] = 0;
            }
            else
            {
                skippedNotes[skipPointer][0] = note;
                skippedNotes[skipPointer][1] = velocity;
                skippedNotes[skipPointer][2] = loudestSoundingNote;
                skippedNotes[skipPointer][3] = loudestString;
                skippedNotes[skipPointer][4] = string;
                skipPointer = (skipPointer + 1) & 31;
            }
            #if 0
            else if (timeSinceLastAttack > 500)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (stringStates[i][0] >= 0)
                    {

                        sendMIDINoteOn(stringStates[i][0], 0, 0);
                        stringStates[i][0] = -1;
                    }
                    openStringCount[i] = 10;
                }
                timeSinceLastAttack = 0;
                stringStates[string][0] = note;
                stringStates[string][1] = velocity;
                pitchFreeze[string] = 0;
                sendMIDINoteOn(note, velocity, 0);
            
            }
            #endif
        }
        else
        {
            if (stringStates[string][0] > 0)
            {
                sendMIDINoteOn(stringStates[string][0], 0, 0);
            }
            stringStates[string][0] = -1;
            stringStates[string][1] = 0;
            pitchFreeze[string] = 0;
        }
    }       
}

void scanButtons(void)
{
    int buttonInputs[5];
    
    buttonInputs[0] = !fretted_latching_Read();
    buttonInputs[1] = !up_Read();
    buttonInputs[2] = !down_Read();
    buttonInputs[3] = !enter_Read();
    buttonInputs[4] = !fretted_mom_Read();
    
    for (int i = 0; i < 5; i++)
    {
        if (buttonInputs[i] && (buttonStates[i] == 1)) //subsequent down state
        {
            if (buttonCounters[i] < 100)
            {
                buttonCounters[i]++;
            }
        }
        
        if (buttonStates[i] == 0) //set to zero on first down
        {
             buttonCounters[i] = 0;
        }
        
        buttonStates[i] =  buttonInputs[i] ;
    }
    
    //fretted processing
    if (buttonCounters[0] == 95)
    {
        frettedStateLatched = !frettedStateLatched;
         EEPROM_WriteByte(frettedStateLatched, 34);
        buttonCounters[0] = 97;
    }
    
    //int momentary_fretted = ((int)I2Cbuff2[2] > 0);
    
    //check momentary fretted button
    //if (momentary_fretted)
    {
       // frettedState = !frettedStateLatched;
    }
    //else
    {
        frettedState = frettedStateLatched;
    }
    
    //frettedState = frettedStateLatched;
    //indicate fretted state
    if (frettedState)
    {
        LED_1_Write(1);
    }
    else
    {
        LED_1_Write(0);
    }
    
    
    //up and down processing
    //if up pressed
    //#if 0
    if (buttonCounters[1] == 95)
    {
        
        if (!setPresetOrSetTuning)
        {
            if (currentPresetSelection < highestPresetNumber)
            {
                currentPresetSelection++;
            }
            else
            {
                currentPresetSelection = 0;
            }
            
            sendCurrentPresetNumber();
            presetNumberToLoad = currentPresetSelection;
            sendingMessage = 3;
        }
        else
        {
            if (currentTuningSelection < highestTuningNumber)
            {
                currentTuningSelection++;  
            }
            else
            {
                currentTuningSelection = 0;
            }
            sendCurrentTuningNumber();
            tuningNumberToLoad = currentTuningSelection;
            sendingMessage = 4;
        }
        //OLED_invert(1);
        buttonCounters[1] = 97;
    }
    //if down pressed
    if (buttonCounters[2] == 95)
    {
        if (!setPresetOrSetTuning)
        {
            if (currentPresetSelection > 0)
            {
                currentPresetSelection--;
                
            }
            else
            {
                currentPresetSelection = highestPresetNumber;
            }
            sendCurrentPresetNumber();
            presetNumberToLoad = currentPresetSelection;
            sendingMessage = 3;
        }
        else
        {
            if (currentTuningSelection > 0)
            {
                currentTuningSelection--;
                
            }
            else
            {
                currentTuningSelection = highestTuningNumber;
            }
            sendCurrentTuningNumber();
            tuningNumberToLoad = currentTuningSelection;
            sendingMessage = 4;
        }
        buttonCounters[2] = 97;
    }
    //if enter pressed
    if (buttonCounters[3] == 95)
    {
        if (calibration_mode > 0)
        {
            calibration_mode++;
            
            if (calibration_mode > max_calibration)
            {
                calibration_mode = 0;
                int byteCount = 0;
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        EEPROM_WriteByte(fretMeasurements[i][j] >> 8, byteCount++);
                        EEPROM_WriteByte(fretMeasurements[i][j] & 255, byteCount++);
                    }
                }
                sendCurrentPresetNumber();
            }
            else
            {
                OLED_writeCalibrationScreen(calibration_mode);
            }
        }
        
        else if ((buttonStates[2] == 1) && (buttonStates[0] == 1))
        {
            calibration_mode = 1;
            OLED_writeCalibrationScreen(calibration_mode);
        }

        
        else 
        {
           setPresetOrSetTuning = !setPresetOrSetTuning; 
           if (setPresetOrSetTuning)
            {
                sendCurrentTuningNumber();
            }
            else
            {
                sendCurrentPresetNumber();
            }
        }
        buttonCounters[3] = 97;
    }
    //#endif
    if (buttonCounters[4] == 95)
    {
        //polyMode = !polyMode;
        buttonCounters[4] = 97;
    }        
}

void sendCurrentPresetNumber(void)
{
    OLED_writePreset();
    EEPROM_WriteByte(currentPresetSelection, 32);
}


    
void sendCurrentTuningNumber(void)
{
    OLED_writeTuning();
    EEPROM_WriteByte(currentTuningSelection, 33);
}