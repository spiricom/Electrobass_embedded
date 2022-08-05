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


//function pointers
shapeTick_t shapeTick[NUM_OSC];
filterTick_t filterTick[NUM_FILT];


//oscillators
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

//oscillator outputs
float outSamples[2][NUM_OSC];
//source vals
float sourceValues[NUM_SOURCES];

float freqMult[NUM_OSC];

//filters
tDiodeFilter diodeFilters[NUM_FILT];
tVZFilter VZfilterPeak[NUM_FILT];
tVZFilter VZfilterLS[NUM_FILT];
tVZFilter VZfilterHS[NUM_FILT];
tVZFilter VZfilterBR[NUM_FILT];
tSVF lowpass[NUM_FILT];
tSVF highpass[NUM_FILT];
tSVF bandpass[NUM_FILT];
tLadderFilter Ladderfilter[NUM_FILT];

float midiCutoff[NUM_FILT];
float filterGain[NUM_FILT];

//envelopes
tADSRT envs[NUM_ENV];
float expBuffer[EXP_BUFFER_SIZE];
float expBufferSizeMinusOne;
float decayExpBuffer[DECAY_EXP_BUFFER_SIZE];
float decayExpBufferSizeMinusOne;


//master
float amplitude = 0.0f;

float sample = 0.0f;
tSimplePoly poly;
float bend;
tNoise noise;


uint8_t voiceSounding = 0;

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

    // exponential decay buffer falling from 1 to
    LEAF_generate_exp(decayExpBuffer, 0.001f, 0.0f, 1.0f, -0.0008f, DECAY_EXP_BUFFER_SIZE);

    expBufferSizeMinusOne = EXP_BUFFER_SIZE - 1;
    decayExpBufferSizeMinusOne = DECAY_EXP_BUFFER_SIZE - 1;

    for (int i = 0; i < NUM_ENV; i++)
    {
        tADSRT_init(&envs[i], 0.1f,10.f,0.5f,1.0f,decayExpBuffer, DECAY_EXP_BUFFER_SIZE, &leaf);
        tADSRT_setLeakFactor(&envs[i], ((1.0f - 0.1f) * 0.00005f) + 0.99995f);
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

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
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
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);

}

float oscOuts[2][NUM_OSC];

void oscillator_tick(float note, float freq)
{
    //if (loadingTables || !enabled) return;
	for (int osc = 0; osc < NUM_OSC; osc++)
	{
		param* oscParams = &params[OSC_PARAMS_OFFSET + osc * OscParamsNum];

		float fine = oscParams[OscFine].realVal;
		float freqOffset= oscParams[OscFreq].realVal;
		float shape = oscParams[OscShape].realVal;
		float amp = oscParams[OscAmp].realVal;
		float filterSend = oscParams[OscFilterSend].realVal;

		float finalFreq = mtof(note + (fine*0.01f)) + freqOffset * freqMult[osc];

		float sample = 0.0f;

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



float filter_tick(float* samples, float note)
{
	float cutoff[2];
	uint8_t enabledFilt[2] = {0,0};
	for (int f = 0; f < NUM_FILT; f++)
	{
		param* filtParams = &params[FILTER_PARAMS_OFFSET + f * FilterParamsNum];
		float keyFollow = filtParams[FilterKeyFollow].realVal;
		float enabled = filtParams[FilterEnabled].realVal;
		enabledFilt[f] = (enabled > 0.5f);
		if (!enabledFilt[f]) continue;


		if (isnan(note))
		{
			note = 0.0f; //is this necessary?
		}

		cutoff[f] = midiCutoff[f] + (note * keyFollow);
		cutoff[f] = LEAF_clip(0.1f, fabsf(faster_mtof(cutoff[f])), 19000.0f);
	}

	float  sp = params[FilterSeriesParallelMix].realVal;

	if (enabledFilt[0])
	{
		filterTick[0](&samples[0], 0, cutoff[0]);
	}
	float sendToFilter2 = samples[0] * (1.0f - sp);
	samples[1] += sendToFilter2;
	//compute what gets sent to the second filter
	if (enabledFilt[1])
	{
		filterTick[1](&samples[1], 1, cutoff[1]);
	}
	return samples[1] + (samples[0] * sp);
}


void lowpassTick(float* sample, int v, float cutoff)
{
	tSVF_setFreq(&lowpass[v], cutoff);
	*sample = tSVF_tick(&lowpass[v], *sample);
    *sample *= filterGain[v];
}

void highpassTick(float* sample, int v, float cutoff)
{
	tSVF_setFreq(&highpass[v], cutoff);
	*sample = tSVF_tick(&highpass[v], *sample);
    *sample *= filterGain[v];
}

void bandpassTick(float* sample, int v, float cutoff)
{
	tSVF_setFreq(&bandpass[v], cutoff);
	*sample = tSVF_tick(&bandpass[v], *sample);
    *sample *= filterGain[v];
}

void diodeLowpassTick(float* sample, int v, float cutoff)
{
	tDiodeFilter_setFreq(&diodeFilters[v], cutoff);
	*sample = tDiodeFilter_tick(&diodeFilters[v], *sample);
    *sample *= filterGain[v];
}

void VZpeakTick(float* sample, int v, float cutoff)
{
	tVZFilter_setFreq(&VZfilterPeak[v], cutoff);
	*sample = tVZFilter_tickEfficient(&VZfilterPeak[v], *sample);
}

void VZlowshelfTick(float* sample, int v, float cutoff)
{
	tVZFilter_setFreq(&VZfilterLS[v], cutoff);
	*sample = tVZFilter_tickEfficient(&VZfilterLS[v], *sample);
}
void VZhighshelfTick(float* sample, int v, float cutoff)
{
	tVZFilter_setFreq(&VZfilterHS[v], cutoff);
	*sample = tVZFilter_tickEfficient(&VZfilterHS[v], *sample);
}
void VZbandrejectTick(float* sample, int v, float cutoff)
{
	tVZFilter_setFreq(&VZfilterBR[v], cutoff);
	*sample = tVZFilter_tickEfficient(&VZfilterBR[v], *sample);
    *sample *= filterGain[v];
}

void LadderLowpassTick(float* sample, int v, float cutoff)
{
	tLadderFilter_setFreq(&Ladderfilter[v], cutoff);
	*sample = tLadderFilter_tick(&Ladderfilter[v], *sample);
    *sample *= filterGain[v];
}




void setFreqMult(float harm_pitch, int osc)
{
	if (params[OSC_PARAMS_OFFSET + osc * OscParamsNum + OscisStepped].realVal > 0.5f) ///check for value of 1 since this is a float
	{
		harm_pitch = roundf(harm_pitch);
	}
	if (params[OSC_PARAMS_OFFSET + osc * OscParamsNum + OscisHarmonic].realVal > 0.5f)
	{
		harm_pitch >= 0 ? freqMult[osc] = (harm_pitch + 1) : (1.0f / fabsf((harm_pitch - 1)));
	}
	else
	{
		freqMult[osc] = powf(1.059463094359295f, harm_pitch);
	}
}

void filterSetCutoff(float cutoff, int v)
{
	midiCutoff[v] = cutoff;
}


void lowpassSetQ(float q, int v)
{
    tSVF_setQ(&lowpass[v], q);
}

void highpassSetQ(float q, int v)
{
    tSVF_setQ(&highpass[v], q);
}

void bandpassSetQ(float q, int v)
{
    tSVF_setQ(&bandpass[v], q);
}

void diodeLowpassSetQ(float q, int v)
{
	tDiodeFilter_setQ(&diodeFilters[v], q);
}

void VZpeakSetQ(float bw, int v)
{
	tVZFilter_setBandwidth(&VZfilterPeak[v], bw);
}

void VZlowshelfSetQ(float bw, int v)
{
	 tVZFilter_setBandwidth(&VZfilterLS[v], bw);
}

void VZhighshelfSetQ(float bw, int v)
{
	 tVZFilter_setBandwidth(&VZfilterHS[v], bw);
}

void VZbandrejectSetQ(float bw, int v)
{
	tVZFilter_setBandwidth(&VZfilterBR[v], bw);
}

void LadderLowpassSetQ(float q, int v)
{
	tLadderFilter_setQ(&Ladderfilter[v], q);
}

void lowpassSetGain(float gain, int v)
{
    filterGain[v] = fasterdbtoa((gain * 24.0f) - 12.0f);
}

void highpassSetGain(float gain, int v)
{
	filterGain[v] = fasterdbtoa((gain * 24.0f) - 12.0f);
}

void bandpassSetGain(float gain, int v)
{
	filterGain[v] = fasterdbtoa((gain * 24.0f) - 12.0f);
}

void diodeLowpassSetGain(float gain, int v)
{
	filterGain[v] = fasterdbtoa((gain * 24.0f) - 12.0f);
}

void VZpeakSetGain(float gain, int v)
{
	 tVZFilter_setGain(&VZfilterPeak[v], fasterdbtoa((gain * 50.f) - 25.f));
}

void VZlowshelfSetGain(float gain, int v)
{
	tVZFilter_setGain(&VZfilterLS[v], fasterdbtoa((gain * 50.f) - 25.f));
}

void VZhighshelfSetGain(float gain, int v)
{
	tVZFilter_setGain(&VZfilterLS[v], fasterdbtoa((gain * 50.f) - 25.f));
}

void VZbandrejectSetGain(float gain, int v)
{
	filterGain[v] = fasterdbtoa((gain * 24.0f) - 12.0f);
}

void LadderLowpassSetGain(float gain, int v)
{
	filterGain[v] = fasterdbtoa((gain * 24.0f) - 12.0f);
}


void envelope_tick(void)
{
	for (int v = 0; v < NUM_ENV; v++)
	{
		float value = tADSRT_tickNoInterp(&envs[v]);
		sourceValues[ENV_SOURCE_OFFSET + v] = value;
	}

	if (poly->voices[0][0] == -2)
	{
	    if (envs[0]->whichStage == env_idle)
	    {
	          tSimplePoly_deactivateVoice(&poly, 0);  //remove this since we're monophonic - should check if that will break anything
	          voiceSounding = false;
	    }
	}

}


void setEnvelopeAttack(float a, int v)
{
	tADSRT_setAttack(&envs[v], a);
}

void setEnvelopeDecay(float d, int v)
{
	tADSRT_setDecay(&envs[v], d);
}

void setEnvelopeSustain(float s, int v)
{
	tADSRT_setSustain(&envs[v], s);
}

void setEnvelopeRelease(float r, int v)
{
	tADSRT_setRelease(&envs[v], r);
}

void setEnvelopeLeak(float leak, int v)
{
	tADSRT_setLeakFactor(&envs[v], 0.99995f + 0.00005f*(1.f-leak));
}

void setAmp(float amp, int v)
{
	amplitude = amp;
}


void tickMappings(void)
{
	for (int i = 0; i < numMappings; i++)
	{
		float value = 0.0f;
		for (int j = 0; j < mappings[i].numHooks; j++)
		{
			float sum = *mappings[i].sourceValPtr[j] * mappings[i].amount[j]; // *mappings[i].scalarSourceValPtr[j]
			value += sum;
		}
		//sources are now summed - let's add the initial value
		value += mappings[i].dest.zeroToOneVal;

		//now scale the value with the correct scaling function
		mappings[i].dest.realVal = mappings[i].dest.scaleFunc(value);

		//and pop that value where it belongs by setting the actual parameter
		mappings[i].dest.setParam(mappings[i].dest.realVal, mappings[i].dest.objectNumber);
	}
}

float audioTickL(float audioIn)
{

	sample = 0.0f;

	if (!muteAudio)
	{

		//run mapping ticks
		tickMappings();

		float note = bend + (float)tSimplePoly_getPitch(&poly, 0);

		float freq = mtof(note);


		envelope_tick();


		oscillator_tick(note, freq);

		float filterSamps[2] = {0.0f, 0.0f};
		for (int i = 0; i < NUM_OSC; i++)
		{
			filterSamps[0] += oscOuts[0][i];
			filterSamps[1] += oscOuts[1][i];
		}

		sample = filter_tick(&filterSamps[0], note);

		sample *= amplitude;

	}
	return sample;
}



void sendNoteOn(uint8_t note, uint8_t velocity)
{
	if (velocity > 0)
	{
		tSimplePoly_noteOn(&poly, note, velocity);
		for (int v = 0; v < NUM_ENV; v++)
		{
			param* envParams = &params[ENVELOPE_PARAMS_OFFSET + v * EnvelopeParamsNum];
			float useVelocity = envParams[EnvelopeVelocity].realVal;
			if (useVelocity == 0) velocity = 127.f;
			float fvelocity = (float)velocity;
			fvelocity = ((0.007685533519034f*fvelocity) + 0.0239372430f);
			fvelocity = fvelocity * fvelocity;
		    tADSRT_on(&envs[v], fvelocity);
		    voiceSounding = 1;
		}
	}
	else
	{
		tSimplePoly_noteOff(&poly, note);
		for (int v = 0; v < NUM_ENV; v++)
		{
			tADSRT_off(&envs[v]);
		}
	}
}


void sendCtrl(uint8_t ctrl, uint8_t value)
{
	//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);

	sourceValues[CTRL_SOURCE_OFFSET + (ctrl - CTRL_MIDI_START)] = (float)value * INV_TWO_TO_7;
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



