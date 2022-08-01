/*
 * audio.c
 *
 *  Created on: Jul 6, 2022
 *      Author: jeffsnyder
 */
#include "main.h"
#include "leaf.h"
#include "parameters.h"
#include "audio.h"

//the audio buffers are put in the D2 RAM area because that is a memory location that the DMA has access to.
int32_t audioOutBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2;
int32_t audioInBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2;


HAL_StatusTypeDef transmit_status;
HAL_StatusTypeDef receive_status;



shapeTick_t shapeTick[NUM_OSC];
filterTick_t filterTick[NUM_FILT];

tMBSaw saw[NUM_OSC];
tMBPulse pulse[NUM_OSC];
tCycle sine[NUM_OSC];
tMBTriangle tri[NUM_OSC];

// Using seperate objects for pairs to easily maintain phase relation
tMBSaw sawPaired[NUM_OSC];
tMBPulse pulsePaired[NUM_OSC];
tCycle sinePaired[NUM_OSC];
tMBTriangle triPaired[NUM_OSC];

tWaveOscS wave[NUM_OSC];

float outSamples[2][NUM_OSC];

float sourceValues[NUM_SOURCES];


tDiodeFilter diodeFilters[NUM_FILT];
tVZFilter VZfilterPeak[NUM_FILT];
tVZFilter VZfilterLS[NUM_FILT];
tVZFilter VZfilterHS[NUM_FILT];
tVZFilter VZfilterBR[NUM_FILT];
tSVF lowpass[NUM_FILT];
tSVF highpass[NUM_FILT];
tSVF bandpass[NUM_FILT];
tLadderFilter Ladderfilter[NUM_FILT];



float sample = 0.0f;
tSimplePoly poly;
float bend;
tNoise noise;

//MEMPOOLS
//#define SMALL_MEM_SIZE 50000
//char smallMemory[SMALL_MEM_SIZE] __ATTR_DTCMRAM;

#define MEDIUM_MEM_SIZE 100000
char mediumMemory[MEDIUM_MEM_SIZE] __ATTR_RAM_D1;

//#define LARGE_MEM_SIZE 33554432 //32 MBytes - size of SDRAM IC
//char largeMemory[LARGE_MEM_SIZE] __ATTR_SDRAM;

LEAF leaf;

tMempool smallPool;
tMempool largePool;


void audio_init(SAI_HandleTypeDef* hsaiOut, SAI_HandleTypeDef* hsaiIn)
{
	LEAF_init(&leaf, SAMPLE_RATE, mediumMemory, MEDIUM_MEM_SIZE, &randomNumber);
	//tMempool_init (&smallPool, smallMemory, SMALL_MEM_SIZE, &leaf);
	//tMempool_init (&largePool, largeMemory, LARGE_MEM_SIZE, &leaf);
	for(int i = 0; i < NUM_OSC; i++)
	{
		tMBSaw_init(&saw[i], &leaf);
		tMBPulse_init(&pulse[i], &leaf);
		tCycle_init(&sine[i], &leaf);
		tMBTriangle_init(&tri[i], &leaf);

		// Using seperate objects for pairs to easily maintain phase relation
		tMBSaw_init(&sawPaired[i], &leaf);
		tMBPulse_init(&pulsePaired[i], &leaf);
		tCycle_init(&sinePaired[i], &leaf);
		tMBTriangle_init(&triPaired[i], &leaf);
	}

	for (int i = 0; i < NUM_FILT; i++)
	{
		tSVF_init(&lowpass[i], SVFTypeLowpass, 2000.f, 0.7f, &leaf);
		tSVF_init(&highpass[i], SVFTypeHighpass, 2000.f, 0.7f, &leaf);
		tSVF_init(&bandpass[i], SVFTypeBandpass, 2000.f, 0.7f, &leaf);
		tDiodeFilter_init(&diodeFilters[i], 2000.f, 1.0f, &leaf);
		tVZFilter_init(&VZfilterPeak[i], Bell, 2000.f, 1.0f, &leaf);
		tVZFilter_init(&VZfilterLS[i], Lowshelf, 2000.f, 1.0f, &leaf);
		tVZFilter_init(&VZfilterHS[i], Highshelf, 2000.f, 1.0f, &leaf);
		tVZFilter_init(&VZfilterBR[i], BandReject, 2000.f, 1.0f, &leaf);
		tLadderFilter_init(&Ladderfilter[i], 2000.f, 1.0f, &leaf);
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

float oscOuts[2][NUM_OSC];

void oscillator_tick(float note, float freq)
{
    //if (loadingTables || !enabled) return;
	for (int osc = 0; osc < NUM_OSC; osc++)
	{
		param* oscParams = &params[OSC_PARAMS_OFFSET + osc * OscParamsNum];


		float harm_pitch = oscParams[OscPitch].realVal;
		float fine = oscParams[OscFine].realVal;
		float freqOffset= oscParams[OscFreq].realVal;
		float shape = oscParams[OscShape].realVal;
		float amp = oscParams[OscAmp].realVal;
		float filterSend = oscParams[OscFilterSend].realVal;

		amp = amp < 0.f ? 0.f : amp;
		if (oscParams[OscisStepped].realVal > 0.5f) ///check for value of 1 since this is a float
		{
			harm_pitch = round(harm_pitch);
		}
		if (oscParams[OscisHarmonic].realVal > 0.5f)
		{
			note = harm_pitch >= 0 ? ftom(freq * (harm_pitch + 1)) : ftom(freq / abs((harm_pitch - 1)));
			harm_pitch = 0.0f;
		}

		float finalFreq = mtof(LEAF_clip(0.0f, note + harm_pitch + fine*0.01f, 127.0f)) + freqOffset;

		float sample = 0.0f;

		shape = LEAF_clip(0.f, shape, 1.f);
		shapeTick[osc](&sample, osc, finalFreq, shape);

		sample *= amp;

		float normSample = (sample + 1.f) * 0.5f;
		sourceValues[OSC_SOURCE_OFFSET + osc] = normSample; // the define of zero may be wasteful


		sample *= INV_NUM_OSCS;

		oscOuts[0][osc] = sample * filterSend * oscParams[OscEnabled].realVal;
		oscOuts[1][osc] = sample * (1.f-filterSend) * oscParams[OscEnabled].realVal;
	}

}


void sawSquareTick(float* sample, int v, float freq, float shape)
{
    tMBSaw_setFreq(&sawPaired[v], freq);
    tMBPulse_setFreq(&pulsePaired[v], freq);
    *sample += tMBSaw_tick(&sawPaired[v]) * (1.0f - shape) * 2.f;
    *sample += tMBPulse_tick(&pulsePaired[v]) * shape * 2.f;
}

void sineTriTick(float* sample, int v, float freq, float shape)
{
    tCycle_setFreq(&sinePaired[v], freq);
    tMBTriangle_setFreq(&triPaired[v], freq);
    *sample += tCycle_tick(&sinePaired[v]) * (1.0f - shape);
    *sample += tMBTriangle_tick(&triPaired[v]) * shape * 2.f;;
}

void sawTick(float* sample, int v, float freq, float shape)
{
    tMBSaw_setFreq(&saw[v], freq);
    *sample += tMBSaw_tick(&saw[v]) * 2.f;;
}

void pulseTick(float* sample, int v, float freq, float shape)
{
    tMBPulse_setFreq(&pulse[v], freq);
    tMBPulse_setWidth(&pulse[v], shape);
    *sample += tMBPulse_tick(&pulse[v]) * 2.f;;
}

void sineTick(float* sample, int v, float freq, float shape)
{
    tCycle_setFreq(&sine[v], freq);
    *sample += tCycle_tick(&sine[v]);
}

void triTick(float* sample, int v, float freq, float shape)
{
    tMBTriangle_setFreq(&tri[v], freq);
    tMBTriangle_setWidth(&tri[v], shape);
    *sample += tMBTriangle_tick(&tri[v]) * 2.f;;
}

void userTick(float* sample, int v, float freq, float shape)
{
    tWaveOscS_setFreq(&wave[v], freq);
    tWaveOscS_setIndex(&wave[v], shape);
    *sample += tWaveOscS_tick(&wave[v]);
}



void filter_tick(float* samples, float note, float freq)
{
	for (int f = 0; f < NUM_FILT; f++)
	{
		param* filtParams = &params[FILTER_PARAMS_OFFSET + f * FilterParamsNum];
		float midiCutoff = filtParams[FilterCutoff].realVal;
		float keyFollow = filtParams[FilterKeyFollow].realVal;
		float q= filtParams[FilterResonance].realVal;
		float gain = filtParams[FilterGain].realVal;
		float enabled = filtParams[FilterEnabled].realVal;



		if (!enabled) continue;

		LEAF_clip(0.f, keyFollow, 1.f);

		if (isnan(note))
		{
			note = 0.0f;
		}

		float cutoff = midiCutoff + (note * keyFollow);
		cutoff = LEAF_clip(0.1f, fabsf(mtof(cutoff)), 19000.0f);

		q = q < 0.1f ? 0.1f : q;

		filterTick[f](&samples[f], f, cutoff, q, keyFollow, gain);

	}
}


void lowpassTick(float* sample, int v, float cutoff, float q, float morph, float gain)
{
    tSVF_setFreqAndQ(&lowpass[v], cutoff, q);
    *sample = tSVF_tick(&lowpass[v], *sample);
    *sample *= dbtoa((gain * 24.0f) - 12.0f);
}

void highpassTick(float* sample, int v, float cutoff, float q, float morph, float gain)
{
    tSVF_setFreqAndQ(&highpass[v], cutoff, q);
    *sample = tSVF_tick(&highpass[v], *sample);
    *sample *= fasterdbtoa((gain * 24.0f) - 12.0f);
}

void bandpassTick(float* sample, int v, float cutoff, float q, float morph, float gain)
{
    tSVF_setFreqAndQ(&bandpass[v], cutoff, q);
    *sample = tSVF_tick(&bandpass[v], *sample);
    *sample *= fasterdbtoa((gain * 24.0f) - 12.0f);
}

void diodeLowpassTick(float* sample, int v, float cutoff, float q, float morph, float gain)
{
    tDiodeFilter_setFreq(&diodeFilters[v], cutoff);
    tDiodeFilter_setQ(&diodeFilters[v], q);
    *sample = tDiodeFilter_tick(&diodeFilters[v], *sample);
    *sample *= fasterdbtoa((gain * 24.0f) - 12.0f);
}

void VZpeakTick(float* sample, int v, float cutoff, float q, float morph, float gain)
{
    tVZFilter_setFrequencyAndBandwidthAndGain(&VZfilterPeak[v], cutoff, q, dbtoa((gain * 50.f) - 25.f));
    *sample = tVZFilter_tickEfficient(&VZfilterPeak[v], *sample);
}

void VZlowshelfTick(float* sample, int v, float cutoff, float q, float morph, float gain)
{
    tVZFilter_setFrequencyAndResonanceAndGain(&VZfilterLS[v], cutoff, q, fasterdbtoa((gain * 50.f) - 25.0f));
    *sample = tVZFilter_tickEfficient(&VZfilterLS[v], *sample);
}
void VZhighshelfTick(float* sample, int v, float cutoff, float q, float morph, float gain)
{
    tVZFilter_setFrequencyAndResonanceAndGain(&VZfilterHS[v], cutoff, q, fasterdbtoa((gain * 50.0f) - 25.0f));
    *sample = tVZFilter_tickEfficient(&VZfilterHS[v], *sample);
}
void VZbandrejectTick(float* sample, int v, float cutoff, float q, float morph, float gain)
{
    tVZFilter_setFrequencyAndResonanceAndGain(&VZfilterBR[v], cutoff, q, 1);
    *sample = tVZFilter_tickEfficient(&VZfilterBR[v], *sample);
    *sample *= fasterdbtoa(gain);
}

void LadderLowpassTick(float* sample, int v, float cutoff, float q, float morph, float gain)
{
    tLadderFilter_setFreq(&Ladderfilter[v], cutoff);
    tLadderFilter_setQ(&Ladderfilter[v], q);
    *sample = tLadderFilter_tick(&Ladderfilter[v], *sample);
    *sample *= fasterdbtoa(gain);
}



float audioTickL(float audioIn)
{

	sample = 0.0f;

	if (!muteAudio)
	{

		float note = bend + (float)tSimplePoly_getPitch(&poly, 0);

		float freq = mtof(note);

		oscillator_tick(note, freq);

		float filterSamps[2] = {0.0f, 0.0f};
		for (int i = 0; i < NUM_OSC; i++)
		{
			filterSamps[0] += oscOuts[0][i];
			filterSamps[1] += oscOuts[1][i];
		}

		filter_tick(&filterSamps[0], note, freq);



		for (int i = 0; i < NUM_FILT; i++)
		{
			sample += filterSamps[i];
		}

		uint8_t vel = tSimplePoly_getVelocity(&poly, 0);
		float velocity = (float)vel;
		velocity = ((0.007685533519034f*velocity) + 0.0239372430f);
		velocity = velocity * velocity;
		sample *= velocity;

	}
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

}
void sendCtrl(uint8_t value, uint8_t ctrl)
{
	//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
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



