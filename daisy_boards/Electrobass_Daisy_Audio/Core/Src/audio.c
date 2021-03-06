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

tMBSaw myOsc;
tSimplePoly poly;
float bend;


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
	tMBSaw_initToPool(&myOsc, &smallPool);
	tMBSaw_setFreq(&myOsc, 440.0f);
	tSimplePoly_init(&poly, 1, &leaf);
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


	tMBSaw_setFreq(&myOsc, mtof(bend + (float)tSimplePoly_getPitch(&poly, 0)));
	uint8_t vel = tSimplePoly_getVelocity(&poly, 0);
	sample += tMBSaw_tick(&myOsc); // tick the oscillator
	//sample *= ((float)vel) / 127.0f;
	float velocity = (float)vel;
    velocity = ((0.007685533519034f*velocity) + 0.0239372430f);
    velocity = velocity * velocity;
    sample *= velocity;
	//sample *= ((float)vel) / 127.0f;;
	//sample *= 0.33f; // drop the gain because we've got three full volume sine waves summing here

	return sample;
}



void sendNoteOn(uint8_t note, uint8_t velocity)
{
	if (velocity > 0)
	{
		tSimplePoly_noteOn(&poly, note, velocity);
	}
	else
	{
		tSimplePoly_noteOff(&poly, note);
	}
}
void sendCtrl(uint8_t value, uint8_t ctrl)
{
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
}
void sendPitchBend(uint8_t value, uint8_t ctrl)
{
	int bendInt = value + (ctrl << 7);
	bendInt = bendInt - 8192;
	bend = bendInt * 0.002929866324849f; //divide by (16383 / 48 semitones)

}


void HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hsai)
{
	audioFrame(HALF_BUFFER_SIZE);
}

void HAL_SAI_RxHalfCpltCallback(SAI_HandleTypeDef *hsai)
{
	audioFrame(0);
}



