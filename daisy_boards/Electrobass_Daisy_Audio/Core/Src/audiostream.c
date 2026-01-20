/*
 * audio.c
 *
 *  Created on: Jul 6, 2022
 *      Author: jeffsnyder
 */
#include "main.h"
#include "leaf.h"
#include "memory.h"
#include "codec.h"
#include "i2c.h"
#include "gpio.h"
#include "spi.h"
#include "parameters.h"
#include "audiostream.h"
#include "arm_math.h"
#include "soundengine.h"


cStack midiStack;
//float fractionalMidi[128];
HAL_StatusTypeDef transmit_status;
HAL_StatusTypeDef receive_status;

tSimplePoly myPoly;

uint8_t numStringsThisBoard = NUM_STRINGS_PER_BOARD;

uint32_t audioSuspended = 0;

float frameLoadMultiplier = 1.0f;
float frameLoadPercentage = 0.0f;
union breakFloat{
	float f;
	uint8_t b[4];
};




float FORCE_INLINE mtofTableLookup(float tempMIDI)
{
	float tempIndexF = ((LEAF_clip(-163.0f, tempMIDI, 163.0f) * 100.0f) + 16384.0f);
	int tempIndexI = (int)tempIndexF;
	tempIndexF = tempIndexF -tempIndexI;
	float freqToSmooth1 = mtofTable[tempIndexI & 32767];
	float freqToSmooth2 = mtofTable[(tempIndexI + 1) & 32767];
	return ((freqToSmooth1 * (1.0f - tempIndexF)) + (freqToSmooth2 * tempIndexF));
}


void audioInit(void)
{
	for (int i = 0; i < AUDIO_BUFFER_SIZE; i++)
	{

			audioOutBuffer[ i] = (int32_t)(0.0f * TWO_TO_23);
	}
	//audioFrameFunction = audioFrameWaiting;
	audioChainInit();
	HAL_Delay(1);
}

void audioStart(SAI_HandleTypeDef* hsaiOut, SAI_HandleTypeDef* hsaiIn)
{
	// set up the I2S driver to send audio data to the codec (and retrieve input as well)
	HAL_Delay(1);
	transmit_status = HAL_SAI_Transmit_DMA(hsaiOut, (uint8_t *)&audioOutBuffer[0], AUDIO_BUFFER_SIZE);
	receive_status = HAL_SAI_Receive_DMA(hsaiIn, (uint8_t *)&audioInBuffer[0], AUDIO_BUFFER_SIZE);
	frameLoadMultiplier = 1.0f / (10000.0f * AUDIO_FRAME_SIZE);
	//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
}

uint32_t timeMIDI = 0;
uint32_t timeSPI = 0;

void __ATTR_ITCMRAM updateStateFromSPIMessage(uint8_t offset)
{
	uint32_t tempCountSPI = DWT->CYCCNT;
	int modeBit = SPI_RX[24 + offset];


	timeSPI = DWT->CYCCNT - tempCountSPI;
}



float noteIn = 64.0f;
float bendIn = 0.0f;

void __ATTR_ITCMRAM sendNoteOn(uint8_t note, uint8_t velocity)
{
	float fvelocity = 0.0f;
	if (velocity > 0)
	{
		tSimplePoly_noteOn(myPoly, note, velocity);
		fvelocity = (float)velocity;
		fvelocity = ((0.007685533519034f*fvelocity) + 0.0239372430f);
		fvelocity = fvelocity * fvelocity;
		//stringInputs[0] = fvelocity*65535.0f;
		noteIn = note;
		//stringMidiPitchesNoBend = noteIn;
		//stringMIDIPitches[0] = noteIn + bendIn;
	}
	else
	{
		tSimplePoly_noteOff(myPoly, note);
		noteIn = note;
		//stringMidiPitchesNoBend = noteIn;
		//stringInputs[0] = 0;
	}
	//newPluck = 1;
}


void __ATTR_ITCMRAM sendCtrl(uint8_t ctrl, uint8_t value)
{
	//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
	//set knobs
}


void __ATTR_ITCMRAM sendPitchBend(uint8_t value, uint8_t ctrl)
{
	int bendInt = value + (ctrl << 7);
	bendInt = bendInt - 8192;

	//bendIn = bendInt * bendRangeMultiplier; //by default, divide by (16383 / 96 semitones)
	//stringMIDIPitches[0] = noteIn + bendIn;
}



void __ATTR_ITCMRAM midi_process(void)
{
	volatile uint32_t tmpCnt = 0;

	//take care of MIDI messages that came in
	tmpCnt = DWT->CYCCNT;
	while(midiStack.readCnt != midiStack.writeCnt)
	{
		uint8_t firstByte = midiStack.buffer[midiStack.readCnt][0];
		int8_t readCount = midiStack.readCnt;
		if (firstByte == 0x90)
		{
			sendNoteOn(midiStack.buffer[readCount][1], midiStack.buffer[readCount][2]);
		}
		else if (firstByte == 0xb0)
		{
			sendCtrl(midiStack.buffer[readCount][1], midiStack.buffer[readCount][2]);
		}
		else if (firstByte == 0xe0)
		{
			sendPitchBend(midiStack.buffer[readCount][1], midiStack.buffer[readCount][2]);
		}
		midiStack.readCnt = (midiStack.readCnt + 1) & 63;
	}
	timeMIDI = DWT->CYCCNT - tmpCnt;
}


volatile uint32_t timeClean = 0;

void __ATTR_ITCMRAM HAL_SAI_TxCpltCallback(SAI_HandleTypeDef *hsai)
{

	//SCB_CleanInvalidateDCache_by_Addr((uint32_t*)(((uint32_t)audioOutBuffer) & ~(uint32_t)0x1F), AUDIO_BUFFER_SIZE+32);

	if (!audioSuspended)
	{
		audioFrameFunction(HALF_BUFFER_SIZE);
	}

	//voiceChangeCheck();
	uint32_t tempCountClean = DWT->CYCCNT;
	SCB_CleanInvalidateDCache_by_Addr((uint32_t*)(((uint32_t)audioOutBuffer) & ~(uint32_t)0x1F), AUDIO_BUFFER_SIZE+32);
	timeClean = DWT->CYCCNT - tempCountClean;
}

void __ATTR_ITCMRAM HAL_SAI_TxHalfCpltCallback(SAI_HandleTypeDef *hsai)
{
	//SCB_CleanInvalidateDCache_by_Addr((uint32_t*)(((uint32_t)audioOutBuffer) & ~(uint32_t)0x1F), AUDIO_BUFFER_SIZE+32);
	if (!audioSuspended)
	{
		audioFrameFunction(0);
	}
	//voiceChangeCheck();
	SCB_CleanInvalidateDCache_by_Addr((uint32_t*)(((uint32_t)audioOutBuffer) & ~(uint32_t)0x1F), AUDIO_BUFFER_SIZE+32);
}

void __ATTR_ITCMRAM cStack_init(cStack* stack)
{
    stack->writeCnt = 0;
    stack->readCnt = 0;
    for (int i = 0; i < 64; i++)
    {
        stack->buffer[i][0] = -1;
        stack->buffer[i][1] = -1;
        stack->buffer[i][2] = -1;
    }
}
void __ATTR_ITCMRAM cStack_push(cStack* stack, uint8_t val, uint8_t val1, uint8_t val2)
{
    stack->buffer[stack->writeCnt][0] = val;
    stack->buffer[stack->writeCnt][1] = val1;
    stack->buffer[stack->writeCnt][2] = val2;
    stack->writeCnt = (stack->writeCnt + 1 ) & 63;
}

void __ATTR_ITCMRAM cStack_pop(cStack* stack, uint8_t* output)
{
    output[0] = stack->buffer[stack->readCnt][0];
    output[1] = stack->buffer[stack->readCnt][1];
    output[2] = stack->buffer[stack->readCnt][2];
    stack->readCnt = (stack->readCnt + 1) & 63;
}

uint32_t timeFrame = 0;


void __ATTR_ITCMRAM audioFrameWaiting(uint16_t buffer_offset)
{
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
	uint32_t tempCountFrame = DWT->CYCCNT;
	//mono operation, no need to compute right channel. Also for loop iterating by 2 instead of 1 to avoid if statement.
	for (int i = 0; i < HALF_BUFFER_SIZE; i+=2)
	{
		int iplusbuffer = buffer_offset + i;
		audioOutBuffer[iplusbuffer] = 0;
		audioOutBuffer[iplusbuffer + 1] = 0;
	}
	timeFrame = DWT->CYCCNT - tempCountFrame;
	frameLoadPercentage = (float)timeFrame * frameLoadMultiplier;
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
}

