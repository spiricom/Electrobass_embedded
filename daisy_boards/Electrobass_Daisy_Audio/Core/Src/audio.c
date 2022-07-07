/*
 * audio.c
 *
 *  Created on: Jul 6, 2022
 *      Author: jeffsnyder
 */
#include "main.h"
#include "audio.h"
#include "leaf.h"


//the audio buffers are put in the D2 RAM area because that is a memory location that the DMA has access to.
int32_t audioOutBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2;
int32_t audioInBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2;



HAL_StatusTypeDef transmit_status;
HAL_StatusTypeDef receive_status;

float sample = 0.0f;

tCycle mySine;


//MEMPOOLS
#define SMALL_MEM_SIZE 5000
char smallMemory[SMALL_MEM_SIZE];

#define MEDIUM_MEM_SIZE 500000
char mediumMemory[MEDIUM_MEM_SIZE] __ATTR_RAM_D1;

//#define LARGE_MEM_SIZE 33554432 //32 MBytes - size of SDRAM IC
//char largeMemory[LARGE_MEM_SIZE] __ATTR_SDRAM;

LEAF leaf;

tMempool smallPool;
tMempool largePool;

void audio_init(SAI_HandleTypeDef* hsaiOut, SAI_HandleTypeDef* hsaiIn)
{
	LEAF_init(&leaf, SAMPLE_RATE, mediumMemory, MEDIUM_MEM_SIZE, &randomNumber);
	tMempool_init (&smallPool, smallMemory, SMALL_MEM_SIZE, &leaf);
	//tMempool_init (&largePool, largeMemory, LARGE_MEM_SIZE, &leaf);
	tCycle_initToPool(&mySine, &smallPool);
	tCycle_setFreq(&mySine, 440.0f);
	HAL_Delay(10);
	for (int i = 0; i < AUDIO_BUFFER_SIZE; i++)
	{
		audioOutBuffer[i] = 0;
	}
	HAL_Delay(1);
	// set up the I2S driver to send audio data to the codec (and retrieve input as well)
	transmit_status = HAL_SAI_Transmit_DMA(hsaiOut, (uint8_t *)&audioOutBuffer[0], AUDIO_BUFFER_SIZE);
	receive_status = HAL_SAI_Receive_DMA(hsaiIn, (uint8_t *)&audioInBuffer[0], AUDIO_BUFFER_SIZE);
}


void audioFrame(uint16_t buffer_offset)
{
	int i;
	int32_t current_sample = 0;

	for (i = 0; i < (HALF_BUFFER_SIZE); i++)
	{
		if ((i & 1) == 0)
		{
			current_sample = (int32_t)(audioTickL((float) (audioInBuffer[buffer_offset + i] * INV_TWO_TO_23)) * TWO_TO_23);
		}
		else
		{
			//current_sample = (int32_t)(audioTickL((float) (audioInBuffer[buffer_offset + i] * INV_TWO_TO_23)) * TWO_TO_23);
		}

		audioOutBuffer[buffer_offset + i] = current_sample;
	}

}


float audioTickL(float audioIn)
{

	sample = 0.0f;

		//tCycle_setFreq(&mySine, (tRamp_tick(&adc[i]) * 500.0f) + 100.0f); // use knob to set frequency between 100 and 600 Hz
	sample += tCycle_tick(&mySine); // tick the oscillator
	//sample *= 0.33f; // drop the gain because we've got three full volume sine waves summing here

	return sample;
}


void HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hsai)
{
	audioFrame(HALF_BUFFER_SIZE);
}

void HAL_SAI_RxHalfCpltCallback(SAI_HandleTypeDef *hsai)
{
	audioFrame(0);
}