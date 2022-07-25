/*
 * audio.c
 *
 *  Created on: Jul 6, 2022
 *      Author: jeffsnyder
 */
#include "main.h"
#include "audio.h"
#include "leaf.h"
#include "parameters.h"


//the audio buffers are put in the D2 RAM area because that is a memory location that the DMA has access to.
int32_t audioOutBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2;
int32_t audioInBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2;




HAL_StatusTypeDef transmit_status;
HAL_StatusTypeDef receive_status;

float sample = 0.0f;
float oscAmp[3];
tMBSaw myOsc[3];

tSVF lowpass[2];
float filtCutoff[2];
float follow[2];

tSimplePoly poly;
float bend;
tNoise noise;

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

//float envelopeReleaseBuffer[65535] __ATTR_RAM_D2;

void audio_init(SAI_HandleTypeDef* hsaiOut, SAI_HandleTypeDef* hsaiIn)
{
	LEAF_init(&leaf, SAMPLE_RATE, mediumMemory, MEDIUM_MEM_SIZE, &randomNumber);
	tMempool_init (&smallPool, smallMemory, SMALL_MEM_SIZE, &leaf);
	//tMempool_init (&largePool, largeMemory, LARGE_MEM_SIZE, &leaf);
	for(int i = 0; i < 3; i++)
	{
		tMBSaw_initToPool(&myOsc[i], &smallPool);
		tMBSaw_setFreq(&myOsc[i], 440.0f);
	}

	for (int i = 0; i < 2; i++)
	{
        tSVF_initToPool(&lowpass[i], SVFTypeLowpass, 2000.f, 0.7f, &smallPool);
	}



	tSimplePoly_init(&poly, 1, &leaf);
	tNoise_init(&noise, WhiteNoise, &leaf);


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

/*

void oscillator_tick(float output[], float note)
{
    //if (loadingTables || !enabled) return;
	for (int osc = 0; osc < 3; osc++)
	{
		param* oscParams = &params[OSC_PARAMS_OFFSET + osc * OscParamsNum];
		if(!oscParams[OscEnabled].zeroToOneVal) continue;
			//if (!processor.voiceIsSounding[v]) continue;

			float harm_pitch = oscParams[OscPitch].realVal;
			float fine = oscParams[OscFine].realVal;
			float freq = oscParams[OscFreq].realVal;
			float shape = oscParams[OscShape].realVal;
			float amp = oscParams[OscAmp].realVal;

			amp = amp < 0.f ? 0.f : amp;
			if (oscParams[OscIsStepped] > 0.5f) ///check for value of 1 since this is a float
			{
				harm_pitch = round(harm_pitch);
			}
			if (oscParams[OscIsHarmonic] > 0.5f)
			{
				note = harm_pitch >= 0 ? ftom(processor.tuner.mtof(note) * (harm_pitch + 1)) : ftom(processor.tuner.mtof(note) / abs((harm_pitch - 1)));
				harm_pitch = 0;
			}

			float finalFreq = processor.tuner.mtof(LEAF_clip(0, note + harm_pitch + fine*0.01f, 127)) + freq;

			float sample = 0.0f;

			shape = LEAF_clip(0.f, shape, 1.f);
			(this->*shapeTick)(sample, v, finalFreq, shape);

			sample *= amp;

			float normSample = (sample + 1.f) * 0.5f;
			sourceValues[0][v] = normSample;
			for (int i = 1; i < processor.numInvParameterSkews; ++i)
			{
				float invSkew = processor.quickInvParameterSkews[i];
				sourceValues[i][v] = powf(normSample, invSkew);
			}

			sample *= INV_NUM_OSCS;

			float f = filterSend->tickNoHooks();

			output[0][v] += sample*f * *afpEnabled;
			output[1][v] += sample*(1.f-f) * *afpEnabled ;
		}
	}

}

*/
uint16_t fullVel = 0;

float audioTickL(float audioIn)
{

	sample = 0.0f;

	float note = bend + (float)tSimplePoly_getPitch(&poly, 0);
	float cutoff[2];
	cutoff[0] = fabsf(mtof(LEAF_clip(0.0f, (params[Filter1Cutoff].zeroToOneVal * 127.0f) + note * params[Filter1KeyFollow].zeroToOneVal, 127.0f)));
	cutoff[1] = fabsf(mtof(LEAF_clip(0.0f, (params[Filter2Cutoff].zeroToOneVal * 127.0f) + note * params[Filter2KeyFollow].zeroToOneVal, 127.0f)));
	float freq = mtof(note);

	tMBSaw_setFreq(&myOsc[0], freq);
	tMBSaw_setFreq(&myOsc[1], 2.f * freq);
	tMBSaw_setFreq(&myOsc[2], 3.f * freq);


	sample += params[Osc1Amp].zeroToOneVal * tMBSaw_tick(&myOsc[0]);
	sample += params[Osc2Amp].zeroToOneVal * tMBSaw_tick(&myOsc[1]);
	sample += params[Osc3Amp].zeroToOneVal * tMBSaw_tick(&myOsc[2]);


	for (int i = 0; i < 2; i++)
	{
		tSVF_setFreqAndQ(&lowpass[i], cutoff[i], 1.0f);
		sample = tSVF_tick(&lowpass[i], sample);
	}

	uint8_t vel = tSimplePoly_getVelocity(&poly, 0);
	float velocity = (float)vel;
    velocity = ((0.007685533519034f*velocity) + 0.0239372430f);
    velocity = velocity * velocity;
    sample *= velocity;

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

	float velocity2 = (float)velocity;
    velocity2 = ((0.007685533519034f*velocity2) + 0.0239372430f);
    velocity2 = velocity2 * velocity2;
    fullVel = velocity2 * 65535.0f;
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



