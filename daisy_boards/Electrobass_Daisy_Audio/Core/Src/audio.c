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
#include "arm_math.h"

//the audio buffers are put in the D2 RAM area because that is a memory location that the DMA has access to.
int32_t audioOutBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2;
int32_t audioInBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2;


uint8_t randomValPointer = 0;

cStack midiStack;
float fractionalMidi[128];
HAL_StatusTypeDef transmit_status;
HAL_StatusTypeDef receive_status;

volatile uint32_t cycleCount[10];

//function pointers
shapeTick_t shapeTick[NUM_OSC];
filterTick_t filterTick[NUM_FILT];
lfoShapeTick_t lfoShapeTick[NUM_LFOS];
effectTick_t effectTick[NUM_EFFECT];

//oversamplers
arm_fir_decimate_instance_f32 osD;
arm_fir_interpolate_instance_f32 osI;

//oscillators
tMBSaw saw[NUM_OSC];
tMBPulse pulse[NUM_OSC];
tCycle sine[NUM_OSC];
tMBTriangle tri[NUM_OSC];

// Using seperate objects for pairs to easily maintain phase relation
tMBSawPulse sawPaired[NUM_OSC];
tMBSineTri sinePaired[NUM_OSC];


tWaveOscS wave[NUM_OSC];

//noise
//
float noiseOuts[2];
tVZFilter noiseShelf1, noiseShelf2, noiseBell1;
tNoise noise;
tIntPhasor lfoSaw[NUM_LFOS];
tSquareLFO lfoPulse[NUM_LFOS];
tCycle lfoSine[NUM_LFOS];
tTriLFO lfoTri[NUM_LFOS];
tSawSquareLFO lfoSawSquare[NUM_LFOS];
tSineTriLFO lfoSineTri[NUM_LFOS];

uint8_t lfoOn[NUM_LFOS];


//oscillator outputs
float outSamples[2][NUM_OSC];


//source vals
float sourceValues[NUM_SOURCES];

tExpSmooth mapSmoothers[MAX_NUM_MAPPINGS];
tExpSmooth pitchSmoother[NUM_OSC];
tExpSmooth filterCutoffSmoother[NUM_FILT];


float freqMult[NUM_OSC];
float bendRangeMultiplier = 0.002929866324849f; //default to divide by 48


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

float filterGain[NUM_FILT];

//envelopes
tADSRT envs[NUM_ENV];
float expBuffer[EXP_BUFFER_SIZE];
float expBufferSizeMinusOne;
float decayExpBuffer[DECAY_EXP_BUFFER_SIZE];
float decayExpBufferSizeMinusOne;


//effects
 tHighpass dcBlock1[NUM_EFFECT];
 tHighpass dcBlock2[NUM_EFFECT];
 tVZFilter shelf1[NUM_EFFECT], shelf2[NUM_EFFECT], bell1[NUM_EFFECT];
 tCompressor comp[NUM_EFFECT];
 tCrusher bc[NUM_EFFECT];
 tLockhartWavefolder wf[NUM_EFFECT];
 tLinearDelay delay1[NUM_EFFECT];
 tLinearDelay delay2[NUM_EFFECT];
 tCycle mod1[NUM_EFFECT];
 tCycle mod2[NUM_EFFECT];
 float fxMix[NUM_EFFECT];
 float fxPostGain[NUM_EFFECT];
 tDiodeFilter FXdiodeFilters[NUM_EFFECT];
 tVZFilter FXVZfilterPeak[NUM_EFFECT];
 tVZFilter FXVZfilterLS[NUM_EFFECT];
 tVZFilter FXVZfilterHS[NUM_EFFECT];
 tVZFilter FXVZfilterBR[NUM_EFFECT];
 tSVF FXlowpass[NUM_EFFECT];
 tSVF FXhighpass[NUM_EFFECT];
 tSVF FXbandpass[NUM_EFFECT];
 tLadderFilter FXLadderfilter[NUM_EFFECT];
//master
float amplitude = 0.0f;
float finalMaster = 1.0f;

tSimplePoly myPoly;
float bend;
float transpose = 0.0f;
tNoise noise;

#define OVERSAMPLE 2
float inv_oversample = 1.0f / OVERSAMPLE;

tOversampler os;
float oversamplerArray[OVERSAMPLE];

float upState1[128];
float downState1[128];

tSVF finalLowpass;

uint8_t voiceSounding = 0;

//MEMPOOLS
#define SMALL_MEM_SIZE 35000
char smallMemory[SMALL_MEM_SIZE];

#define MEDIUM_MEM_SIZE 260000
char mediumMemory[MEDIUM_MEM_SIZE] __ATTR_RAM_D1;

//#define LARGE_MEM_SIZE 33554432 //32 MBytes - size of SDRAM IC
//char largeMemory[LARGE_MEM_SIZE] __ATTR_SDRAM;

LEAF leaf;

tMempool mediumPool;
tMempool largePool;

int MBoffset = 0;

void audio_init(void)
{
	LEAF_init(&leaf, SAMPLE_RATE, smallMemory, SMALL_MEM_SIZE, &randomNumber);
	leaf.clearOnAllocation = 1;
	tMempool_init (&mediumPool, mediumMemory, MEDIUM_MEM_SIZE, &leaf);
	//tMempool_init (&largePool, largeMemory, LARGE_MEM_SIZE, &leaf);
	for(int i = 0; i < NUM_OSC; i++)
	{
		tMBSaw_init(&saw[i], &leaf);

		tMBPulse_init(&pulse[i], &leaf);

		tCycle_init(&sine[i], &leaf);

		tMBTriangle_init(&tri[i], &leaf);

		tMBSawPulse_init(&sawPaired[i], &leaf);

		tMBSineTri_init(&sinePaired[i], &leaf);

	    tExpSmooth_init(&pitchSmoother[i], 64.0f, 0.01f, &leaf);
	}

	for (int i = 0; i < NUM_FILT; i++)
	{
		tSVF_init(&lowpass[i], SVFTypeLowpass, 2000.f, 0.7f, &leaf);
		tSVF_init(&highpass[i], SVFTypeHighpass, 2000.f, 0.7f, &leaf);
		tSVF_init(&bandpass[i], SVFTypeBandpass, 2000.f, 0.7f, &leaf);
		tDiodeFilter_init(&diodeFilters[i], 2000.f, 0.5f, &leaf);
		tVZFilter_init(&VZfilterPeak[i], Bell, 2000.f, 1.0f, &leaf);
		tVZFilter_init(&VZfilterLS[i], Lowshelf, 2000.f, 1.0f, &leaf);
		tVZFilter_init(&VZfilterHS[i], Highshelf, 2000.f, 1.0f, &leaf);
		tVZFilter_init(&VZfilterBR[i], BandReject, 2000.f, 1.0f, &leaf);
		tLadderFilter_init(&Ladderfilter[i], 2000.f, 1.0f, &leaf);
	    tExpSmooth_init(&filterCutoffSmoother[i], 64.0f, 0.01f, &leaf);
	}

	for (int i = 0; i < NUM_LFOS; i++)
	{
		tIntPhasor_init(&lfoSaw[i], &leaf);
		tSquareLFO_init(&lfoPulse[i], &leaf);
		tCycle_init(&lfoSine[i], &leaf);
		tTriLFO_init(&lfoTri[i], &leaf);

		tSineTriLFO_init(&lfoSineTri[i], &leaf);
		tSawSquareLFO_init(&lfoSawSquare[i], &leaf);
	}
    //noise
	tVZFilter_init(&noiseShelf1, Lowshelf, 80.0f, 6.0f, &leaf);
	tVZFilter_init(&noiseShelf2, Highshelf, 12000.0f, 6.0f, &leaf);
	tVZFilter_init(&noiseBell1, Bell, 1000.0f, 1.9f, &leaf);
    tNoise_init(&noise, WhiteNoise, &leaf);
    // exponential decay buffer falling from 1 to
    LEAF_generate_exp(decayExpBuffer, 0.001f, 0.0f, 1.0f, -0.0008f, DECAY_EXP_BUFFER_SIZE);

    expBufferSizeMinusOne = EXP_BUFFER_SIZE - 1;
    decayExpBufferSizeMinusOne = DECAY_EXP_BUFFER_SIZE - 1;

    for (int i = 0; i < NUM_ENV; i++)
    {
        tADSRT_init(&envs[i], 0.1f,10.f,0.5f,1.0f,decayExpBuffer, DECAY_EXP_BUFFER_SIZE, &leaf);
        tADSRT_setLeakFactor(&envs[i], ((1.0f - 0.1f) * 0.00005f) + 0.99995f);
    }


    for (int i = 0; i < NUM_EFFECT; i++)
    {
		tCrusher_init(&bc[i],&leaf);
		tHighpass_init(&dcBlock1[i], 5.0f,&leaf);
		tHighpass_init(&dcBlock2[i], 5.0f,&leaf);
		tVZFilter_init(&shelf1[i], Lowshelf, 80.0f, 32.0f,  &leaf);
		tVZFilter_init(&shelf2[i], Highshelf, 12000.0f, 32.0f, &leaf);
		tVZFilter_init(&bell1[i], Bell, 1000.0f, 1.9f, &leaf);
		tVZFilter_setSampleRate(&shelf1[i], SAMPLE_RATE * OVERSAMPLE);
		tVZFilter_setSampleRate(&shelf2[i], SAMPLE_RATE * OVERSAMPLE);
		tVZFilter_setSampleRate(&bell1[i], SAMPLE_RATE * OVERSAMPLE);
		tCompressor_init(&comp[i], &leaf);
		tLinearDelay_initToPool(&delay1[i], 4000.0f, 4096, &mediumPool);
		tLinearDelay_initToPool(&delay2[i], 4000.0f, 4096, &mediumPool);
		tCycle_init(&mod1[i], &leaf);
		tCycle_init(&mod2[i], &leaf);
		tCycle_setFreq(&mod1[i], 0.2f);
		tCycle_setFreq(&mod2[i], 0.22222222222f);

        //filters
        tSVF_init(&FXlowpass[i], SVFTypeLowpass, 2000.f, 0.7f, &leaf);
        tSVF_init(&FXhighpass[i], SVFTypeHighpass, 2000.f, 0.7f, &leaf);
        tSVF_init(&FXbandpass[i], SVFTypeBandpass, 2000.f, 0.7f, &leaf);
        tDiodeFilter_init(&FXdiodeFilters[i], 2000.f, 1.0f, &leaf);
        tVZFilter_init(&FXVZfilterPeak[i], Bell, 2000.f, 1.0f, &leaf);
        tVZFilter_init(&FXVZfilterLS[i], Lowshelf, 2000.f, 1.0f, &leaf);
        tVZFilter_init(&FXVZfilterHS[i], Highshelf, 2000.f, 1.0f, &leaf);
        tVZFilter_init(&FXVZfilterBR[i], BandReject, 2000.f, 1.0f, &leaf);
        tLadderFilter_init(&FXLadderfilter[i], 2000.f, 1.0f, &leaf);
    }

    for (int i = 0; i < MAX_NUM_MAPPINGS; i++)
    {
    	tExpSmooth_init(&mapSmoothers[i], 0.0f, 0.01f, &leaf);
    }



	tSimplePoly_init(&myPoly, 1, &leaf);
	tNoise_init(&noise, WhiteNoise, &leaf);

	tOversampler_init(&os, OVERSAMPLE, 0, &leaf);

	tSVF_init(&finalLowpass, SVFTypeLowpass, 19000.f, 0.3f, &leaf);


    //int idx = (int)(log2f(OVERSAMPLE))-1;
    //int numTaps = __leaf_tablesize_firNumTaps[idx];
/*
	arm_fir_decimate_init_f32(
	        &osD,
			numTaps,
			OVERSAMPLE,
			(float*) &__leaf_table_fir2XLow,
			(float*) &downState1,
	        OVERSAMPLE);

	arm_fir_interpolate_init_f32(
	        &osI,
			OVERSAMPLE,
			numTaps,
			(float*) &__leaf_table_fir2XLow,
			(float*) &upState1,
	        1);
*/
	HAL_Delay(10);
	for (int i = 0; i < AUDIO_BUFFER_SIZE; i++)
	{
		audioOutBuffer[i] = 0;
	}
}

void audio_start(SAI_HandleTypeDef* hsaiOut, SAI_HandleTypeDef* hsaiIn)
{
	// set up the I2S driver to send audio data to the codec (and retrieve input as well)
	HAL_Delay(1);
	transmit_status = HAL_SAI_Transmit_DMA(hsaiOut, (uint8_t *)&audioOutBuffer[0], AUDIO_BUFFER_SIZE);
	receive_status = HAL_SAI_Receive_DMA(hsaiIn, (uint8_t *)&audioInBuffer[0], AUDIO_BUFFER_SIZE);
	//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
}

const int syncMap[3] = {2, 0, 1};
uint32_t timeMIDI = 0;
uint32_t timeFrame = 0;
float frameLoadPercentage = 0.0f;
float frameLoadMultiplier = 1.0f / (10000.0f * AUDIO_FRAME_SIZE);
void __ATTR_ITCMRAM audioFrame(uint16_t buffer_offset)
{
	volatile uint32_t tmpCnt = 0;
	//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
	uint32_t tempCountFrame = DWT->CYCCNT;
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

	int32_t current_sample = 0;

	//mono operation, no need to compute right channel. Also for loop iterating by 2 instead of 1 to avoid if statement.
	for (int i = 0; i < HALF_BUFFER_SIZE; i+=2)
	{
		current_sample = (int32_t)(audioTickL() * TWO_TO_23);
		audioOutBuffer[buffer_offset + i] = current_sample;
		//audioOutBuffer[buffer_offset + i + 1] = current_sample;
	}
	timeFrame = DWT->CYCCNT - tempCountFrame;
	//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
	frameLoadPercentage = (float)timeFrame * frameLoadMultiplier;

}

float oscOuts[2][NUM_OSC];
float oscAmpMult = 1.0f;
float oscAmpMultArray[4] = {0.0f, 1.0f, 0.5f, 0.333333f};
uint32_t timeOsc = 0;

void __ATTR_ITCMRAM oscillator_tick(float note)
{
    //if (loadingTables || !enabled) return;
	interruptChecker = 0;
	uint32_t tempCount1 = DWT->CYCCNT;
	for (int osc = 0; osc < NUM_OSC; osc++)
	{
		param* oscParams = &params[OSC_PARAMS_OFFSET + osc * OscParamsNum];

		float fine = oscParams[OscFine].realVal;
		float freqOffset= oscParams[OscFreq].realVal;
		float shape = oscParams[OscShape].realVal;
		float amp = oscParams[OscAmp].realVal;
		float filterSend = oscParams[OscFilterSend].realVal;
		int sync = oscParams[OscisSync].realVal > 0.5f; // probably faster than previous roundf version but haven't tested
		float freqToSmooth = (note + (fine*0.01f));
		tExpSmooth_setDest(&pitchSmoother[osc], freqToSmooth);
		freqToSmooth = mtof(tExpSmooth_tick(&pitchSmoother[osc]));
		float finalFreq = (freqToSmooth * freqMult[osc]) + freqOffset ;

		float sample = 0.0f;

		shapeTick[osc](&sample, osc, finalFreq, shape, sync);

		sample *= amp;

		//sourceValues[OSC_SOURCE_OFFSET + osc] = sample; // the define of zero may be wasteful
		sourceValues[osc] = sample;

		sample *= oscAmpMult; // divide down gain if more than one oscillator is sounding (computed at preset load)

		oscOuts[0][osc] = sample * (filterSend) * oscParams[OscEnabled].realVal;
		oscOuts[1][osc] = sample * (1.0f - filterSend) * oscParams[OscEnabled].realVal;
	}
	timeOsc = DWT->CYCCNT - tempCount1;
}


void __ATTR_ITCMRAM  sawSquareTick(float* sample, int v, float freq, float shape, int sync)
{
    tMBSawPulse_setFreq(&sawPaired[v], freq);
    tMBSawPulse_setShape(&sawPaired[v], shape);
    if (sync)
    {
    	tMBSawPulse_sync(&sawPaired[v], sourceValues[syncMap[OSC_SOURCE_OFFSET + v]]);

    }
    *sample += tMBSawPulse_tick(&sawPaired[v]) * 2.f;
}

void __ATTR_ITCMRAM  sineTriTick(float* sample, int v, float freq, float shape, int sync)
{
    tMBSineTri_setFreq(&sinePaired[v], freq);
    tMBSineTri_setShape(&sinePaired[v],shape);
    if (sync)
    {
    	tMBSineTri_sync(&sinePaired[v], sourceValues[syncMap[OSC_SOURCE_OFFSET + v]]);
    }
    *sample += tMBSineTri_tick(&sinePaired[v]) * 2.0f;
}

void __ATTR_ITCMRAM  sawTick(float* sample, int v, float freq, float shape, int sync)
{
    tMBSaw_setFreq(&saw[v], freq);
    if (sync)
	{
		tMBSaw_sync(&saw[v], sourceValues[syncMap[OSC_SOURCE_OFFSET + v]]);
	}
    *sample += tMBSaw_tick(&saw[v]) * 2.f;;
}

void __ATTR_ITCMRAM  pulseTick(float* sample, int v, float freq, float shape, int sync)
{
    tMBPulse_setFreq(&pulse[v], freq);
    tMBPulse_setWidth(&pulse[v], shape);
    if (sync)
	{
		tMBPulse_sync(&pulse[v], sourceValues[syncMap[OSC_SOURCE_OFFSET + v]]);
	}
    *sample += tMBPulse_tick(&pulse[v]) * 2.f;;
}

void __ATTR_ITCMRAM  sineTick(float* sample, int v, float freq, float shape, int sync)
{
    tCycle_setFreq(&sine[v], freq);
    *sample += tCycle_tick(&sine[v]);
}

void __ATTR_ITCMRAM  triTick(float* sample, int v, float freq, float shape, int sync)
{
    tMBTriangle_setFreq(&tri[v], freq);
    tMBTriangle_setWidth(&tri[v], shape);
    if (sync)
	{
		tMBTriangle_sync(&tri[v], sourceValues[syncMap[OSC_SOURCE_OFFSET + v]]);
	}
    *sample += tMBTriangle_tick(&tri[v]) * 2.0f;;
}

void __ATTR_ITCMRAM  userTick(float* sample, int v, float freq, float shape, int sync)
{
    //tWaveOscS_setFreq(&wave[v], freq);
    //tWaveOscS_setIndex(&wave[v], shape);
    //*sample += tWaveOscS_tick(&wave[v]);
}

uint32_t timeFilt = 0;

float __ATTR_ITCMRAM filter_tick(float* samples, float note)
{
	interruptChecker = 0;
	uint32_t tempCount1 = DWT->CYCCNT;
	float cutoff[2];
	uint8_t enabledFilt[2] = {0,0};
	for (int f = 0; f < NUM_FILT; f++)
	{
		param* filtParams = &params[FILTER_PARAMS_OFFSET + f * FilterParamsNum];
		float enabled = filtParams[FilterEnabled].realVal;
		enabledFilt[f] = (enabled > 0.5f);
		if (!enabledFilt[f]) continue;

		float MIDIcutoff = filtParams[FilterCutoff].realVal;
		float keyFollow = filtParams[FilterKeyFollow].realVal;
		if (isnan(note))
		{
			note = 0.0f; //is this necessary?
		}

		cutoff[f] = MIDIcutoff + (note * keyFollow);
		cutoff[f] = LEAF_clip(0.0f, (cutoff[f]-16.0f) * 35.929824561403509f, 4095.0f);
		//smoothing may not be necessary
		tExpSmooth_setDest(&filterCutoffSmoother[f], cutoff[f]);
		cutoff[f] = tExpSmooth_tick(&filterCutoffSmoother[f]);
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

	timeFilt = DWT->CYCCNT - tempCount1;
	return samples[1] + (samples[0] * sp);
}


void __ATTR_ITCMRAM  lowpassTick(float* sample, int v, float cutoff)
{
	tSVF_setFreqFast(&lowpass[v], cutoff);
	*sample = tSVF_tick(&lowpass[v], *sample);
    *sample *= filterGain[v];
}

void __ATTR_ITCMRAM  highpassTick(float* sample, int v, float cutoff)
{
	tSVF_setFreqFast(&highpass[v], cutoff);
	*sample = tSVF_tick(&highpass[v], *sample);
    *sample *= filterGain[v];
}

void __ATTR_ITCMRAM  bandpassTick(float* sample, int v, float cutoff)
{
	tSVF_setFreqFast(&bandpass[v], cutoff);
	*sample = tSVF_tick(&bandpass[v], *sample);
    *sample *= filterGain[v];
}

void __ATTR_ITCMRAM  diodeLowpassTick(float* sample, int v, float cutoff)
{
	tDiodeFilter_setFreqFast(&diodeFilters[v], cutoff);
	*sample = tDiodeFilter_tick(&diodeFilters[v], *sample);
    *sample *= filterGain[v];
}

void __ATTR_ITCMRAM  VZpeakTick(float* sample, int v, float cutoff)
{
	tVZFilter_setFreqFast(&VZfilterPeak[v], cutoff);
	*sample = tVZFilter_tickEfficient(&VZfilterPeak[v], *sample);
}

void __ATTR_ITCMRAM  VZlowshelfTick(float* sample, int v, float cutoff)
{
	tVZFilter_setFreqFast(&VZfilterLS[v], cutoff);
	*sample = tVZFilter_tickEfficient(&VZfilterLS[v], *sample);
}
void __ATTR_ITCMRAM  VZhighshelfTick(float* sample, int v, float cutoff)
{
	tVZFilter_setFreqFast(&VZfilterHS[v], cutoff);
	*sample = tVZFilter_tickEfficient(&VZfilterHS[v], *sample);
}
void __ATTR_ITCMRAM  VZbandrejectTick(float* sample, int v, float cutoff)
{
	tVZFilter_setFreqFast(&VZfilterBR[v], cutoff);
	*sample = tVZFilter_tickEfficient(&VZfilterBR[v], *sample);
    *sample *= filterGain[v];
}

void __ATTR_ITCMRAM  LadderLowpassTick(float* sample, int v, float cutoff)
{
	tLadderFilter_setFreqFast(&Ladderfilter[v], cutoff);
	*sample = tLadderFilter_tick(&Ladderfilter[v], *sample);
    *sample *= filterGain[v];
}




void __ATTR_ITCMRAM setFreqMultPitch(float pitch, int osc)
{
	if (params[OSC_PARAMS_OFFSET + osc * OscParamsNum + OscisStepped].realVal > 0.5f) ///check for value of 1 since this is a float
	{
		pitch = roundf(pitch);
	}
	else
	{
		freqMult[osc] = powf(1.059463094359295f, pitch);
	}
}

void __ATTR_ITCMRAM setFreqMultHarm(float harm, int osc)
{
	if (params[OSC_PARAMS_OFFSET + osc * OscParamsNum + OscisStepped].realVal > 0.5f) ///check for value of 1 since this is a float
	{
		harm = roundf(harm);
	}

	if (harm >= 0)
	{
		freqMult[osc] = (harm + 1);
	}
	else
	{
		freqMult[osc] = (1.0f / fabsf((harm - 1)));
	}

}




void __ATTR_ITCMRAM  lowpassSetQ(float q, int v)
{
    tSVF_setQ(&lowpass[v], q);
}

void __ATTR_ITCMRAM  highpassSetQ(float q, int v)
{
    tSVF_setQ(&highpass[v], q);
}

void __ATTR_ITCMRAM  bandpassSetQ(float q, int v)
{
    tSVF_setQ(&bandpass[v], q);
}

void __ATTR_ITCMRAM  diodeLowpassSetQ(float q, int v)
{
	tDiodeFilter_setQ(&diodeFilters[v], q);
}

void __ATTR_ITCMRAM  VZpeakSetQ(float q, int v)
{
	tVZFilter_setResonance(&VZfilterPeak[v], q);
}

void __ATTR_ITCMRAM  VZlowshelfSetQ(float q, int v)
{
	tVZFilter_setResonance(&VZfilterLS[v], q);
}

void __ATTR_ITCMRAM  VZhighshelfSetQ(float q, int v)
{
	tVZFilter_setResonance(&VZfilterHS[v], q);
}

void __ATTR_ITCMRAM  VZbandrejectSetQ(float q, int v)
{
	tVZFilter_setResonance(&VZfilterBR[v], q);
}

void __ATTR_ITCMRAM  LadderLowpassSetQ(float q, int v)
{
	tLadderFilter_setQ(&Ladderfilter[v], q);
}

void __ATTR_ITCMRAM  lowpassSetGain(float gain, int v)
{
    filterGain[v] = fasterdbtoa((gain * 24.0f) - 12.0f);
}

void __ATTR_ITCMRAM  highpassSetGain(float gain, int v)
{
	filterGain[v] = fasterdbtoa((gain * 24.0f) - 12.0f);
}

void __ATTR_ITCMRAM  bandpassSetGain(float gain, int v)
{
	filterGain[v] = fasterdbtoa((gain * 24.0f) - 12.0f);
}

void __ATTR_ITCMRAM  diodeLowpassSetGain(float gain, int v)
{
	filterGain[v] = fasterdbtoa((gain * 24.0f) - 12.0f);
}

void __ATTR_ITCMRAM  VZpeakSetGain(float gain, int v)
{
	 tVZFilter_setGain(&VZfilterPeak[v], fasterdbtoa((gain * 50.f) - 25.f));
}

void __ATTR_ITCMRAM  VZlowshelfSetGain(float gain, int v)
{
	tVZFilter_setGain(&VZfilterLS[v], fasterdbtoa((gain * 50.f) - 25.f));
}

void __ATTR_ITCMRAM  VZhighshelfSetGain(float gain, int v)
{
	tVZFilter_setGain(&VZfilterLS[v], fasterdbtoa((gain * 50.f) - 25.f));
}

void  __ATTR_ITCMRAM VZbandrejectSetGain(float gain, int v)
{
	filterGain[v] = fasterdbtoa((gain * 24.0f) - 12.0f);
}

void  __ATTR_ITCMRAM  LadderLowpassSetGain(float gain, int v)
{
	filterGain[v] = fasterdbtoa((gain * 24.0f) - 12.0f);
}

uint32_t timeEnv = 0;
void __ATTR_ITCMRAM envelope_tick(void)
{
	interruptChecker = 0;
	uint32_t tempCount1 = DWT->CYCCNT;
	for (int v = 0; v < NUM_ENV; v++)
	{
		float value = tADSRT_tick(&envs[v]); //used to be noInterp but wanted to check if this sounds better and isn't too slow
		sourceValues[ENV_SOURCE_OFFSET + v] = value;
	}
	timeEnv = DWT->CYCCNT - tempCount1;
}

uint32_t timeLFO = 0;
void __ATTR_ITCMRAM lfo_tick(void)
{
	interruptChecker = 0;
	uint32_t tempCount1 = DWT->CYCCNT;
	for (int i = 0; i < NUM_LFOS; i++)
	{
		float sample = 0.0f;
		if (lfoOn[i])
		{
			lfoShapeTick[i](&sample,i);
		}
		sourceValues[LFO_SOURCE_OFFSET + i] = sample;
	}
	timeLFO = DWT->CYCCNT - tempCount1;
}


void  __ATTR_ITCMRAM  setEnvelopeAttack(float a, int v)
{
	tADSRT_setAttack(&envs[v], a);
}

void  __ATTR_ITCMRAM  setEnvelopeDecay(float d, int v)
{
	tADSRT_setDecay(&envs[v], d);
}

void  __ATTR_ITCMRAM  setEnvelopeSustain(float s, int v)
{
	tADSRT_setSustain(&envs[v], s);
}

void  __ATTR_ITCMRAM  setEnvelopeRelease(float r, int v)
{
	tADSRT_setRelease(&envs[v], r);
}

void  __ATTR_ITCMRAM  setEnvelopeLeak(float leak, int v)
{
	tADSRT_setLeakFactor(&envs[v], 0.99995f + 0.00005f*(1.f-leak));
}

void  __ATTR_ITCMRAM  setAmp(float amp, int v)
{
	amplitude = amp;
}

void  __ATTR_ITCMRAM  setMaster(float amp, int v)
{
	finalMaster = amp;
}

void  __ATTR_ITCMRAM  setTranspose(float in, int v)
{
	transpose = in;
}

void  __ATTR_ITCMRAM  setPitchBendRange(float in, int v)
{
	bendRangeMultiplier = 1.0f / (16383.0f / (in * 2.0f));
}

void  __ATTR_ITCMRAM  setFinalLowpass(float in, int v)
{
	tSVF_setFreqFast(&finalLowpass, LEAF_clip(0.0f, (in-16.0f) * 35.929824561403509f, 4095.0f));
}

uint32_t timeMap = 0;
void __ATTR_ITCMRAM tickMappings(void)
{
	interruptChecker = 0;
	uint32_t tempCount1 = DWT->CYCCNT;
	for (int i = 0; i < numMappings; i++)
	{
		float unsmoothedValue = 0.0f;
		float smoothedValue = 0.0f;
		for (int j = 0; j < mappings[i].numHooks; j++)
		{
			float sum = *mappings[i].sourceValPtr[j] * mappings[i].amount[j] * *mappings[i].scalarSourceValPtr[j];
			if (mappings[i].sourceSmoothed[j])
			{
				smoothedValue += sum;
			}
			else
			{
				unsmoothedValue += sum;
			}
		}
		//sources are now summed - let's add the initial value
		smoothedValue += mappings[i].dest->zeroToOneVal;

		tExpSmooth_setDest(&mapSmoothers[i], smoothedValue);
		smoothedValue = tExpSmooth_tick(&mapSmoothers[i]);
		float finalVal = unsmoothedValue + smoothedValue;

		//now scale the value with the correct scaling function
		mappings[i].dest->realVal = mappings[i].dest->scaleFunc(finalVal);

		//and pop that value where it belongs by setting the actual parameter
		mappings[i].dest->setParam(mappings[i].dest->realVal, mappings[i].dest->objectNumber);
	}
	timeMap = DWT->CYCCNT - tempCount1;

}
uint32_t timeTick = 0;
uint32_t oversampleCount = 0;

float __ATTR_ITCMRAM audioTickL(void)
{
	uint32_t tempCount5 = DWT->CYCCNT;
	float sample = 0.0f;
	uint8_t fxPre = (params[FXPREPOST_PARAMS_OFFSET].realVal > 0.5f);
	//run mapping ticks
	tickMappings();

	float note = bend + transpose + (float)tSimplePoly_getPitch(&myPoly, 0);

	sourceValues[MIDI_KEY_SOURCE_OFFSET] = (note - midiKeySubtractor) * midiKeyDivisor;

	int tempNoteIntPart = (int)note;
	float tempNoteFloatPart = note - (float)tempNoteIntPart;
				//int tempPitchClassIntPart =tempNoteIntPart % 12;
	float dev1 = (fractionalMidi[tempNoteIntPart] * (1.0f - tempNoteFloatPart));
	float dev2 =  (fractionalMidi [(tempNoteIntPart+1)] * tempNoteFloatPart);
	note = ( dev1  + dev2);

	note = LEAF_clip(1.0f, note, 140.0f);
	envelope_tick();
	lfo_tick();
	oscillator_tick(note);
	noise_tick();
	float filterSamps[2] = {0.0f, 0.0f};
	for (int i = 0; i < NUM_OSC; i++)
	{
		filterSamps[0] += oscOuts[0][i];
		filterSamps[1] += oscOuts[1][i];
	}
	filterSamps[0] += noiseOuts[0];
	filterSamps[1] += noiseOuts[1];
	//sample = filterSamps[0];
	sample = filter_tick(&filterSamps[0], note);
	if (fxPre)
	{
		sample *= amplitude;
	}
	uint32_t tempCount1 = DWT->CYCCNT;

	//oversample for non-linear effects (distortion, etc)
	tOversampler_upsample(&os, sample, oversamplerArray);

	//arm_fir_interpolate_f32(&osI, &sample, (float*)&oversamplerArray, 1);


	for (int i = 0; i < NUM_EFFECT; i++) {

		for (int j = 0; j < OVERSAMPLE; j++)
		{
			float dry = oversamplerArray[j]; //store the dry value to mix later
			oversamplerArray[j] = effectTick[i](oversamplerArray[j], i); //run the effect
			oversamplerArray[j] = ((1.0f - fxMix[i]) * dry) + (fxMix[i] * oversamplerArray[j]); //mix in dry/wet at the "mix" amount
			oversamplerArray[j] *= fxPostGain[i]; //apply postgain
		}
	}

	//hard clip before downsampling to get a little more antialiasing from clipped signal.
	for (int i = 0; i < (OVERSAMPLE); i++)
	{
		oversamplerArray[i] = LEAF_clip(-1.0f, oversamplerArray[i], 1.0f);
	}
	//downsample to get back to normal sample rate
	sample = tOversampler_downsample(&os, oversamplerArray);

	//arm_fir_decimate_f32(&osD, (float*)&oversamplerArray, &sample, OVERSAMPLE);

	uint32_t tempCount2 = DWT->CYCCNT;

	oversampleCount = tempCount2-tempCount1;

	if (!fxPre)
	{
		sample *= amplitude;
	}


	sample = tSVF_tick(&finalLowpass, sample);
	if (isnan(sample))
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
	}
	sample *= finalMaster;
	sample = LEAF_clip(-1.0f, sample, 1.0f);

	uint32_t tempCount6 = DWT->CYCCNT;
	timeTick = tempCount6-tempCount5;
	return sample * audioMasterLevel * 0.95f;
}



void __ATTR_ITCMRAM sendNoteOn(uint8_t note, uint8_t velocity)
{
	float fvelocity = 0.0f;
	if (velocity > 0)
	{
		tSimplePoly_noteOn(&myPoly, note, velocity);
		fvelocity = (float)velocity;
		fvelocity = ((0.007685533519034f*fvelocity) + 0.0239372430f);
		fvelocity = fvelocity * fvelocity;

		//store random number as source
		sourceValues[RANDOM_SOURCE_OFFSET] = random_values[randomValPointer++];
		//store velocity as source
		sourceValues[VELOCITY_SOURCE_OFFSET] = fvelocity;

		for (int v = 0; v < NUM_ENV; v++)
		{
			param* envParams = &params[ENVELOPE_PARAMS_OFFSET + v * EnvelopeParamsNum];
			float useVelocity = envParams[EnvelopeVelocity].realVal;
			float envVel = fvelocity;
			if (useVelocity == 0) envVel = 1.f;
		    tADSRT_on(&envs[v], envVel);
		    voiceSounding = 1;
		}
		for (int v = 0; v < NUM_LFOS; v++)
		{
			param* lfoParams = &params[LFO_PARAMS_OFFSET + v * LFOParamsNum];
			float noteOnSync = lfoParams[LFOSync].realVal;
			if (noteOnSync > 0.5f)
			{
				lfoParams[LFOPhase].setParam(lfoParams[LFOPhase].realVal, v);
			}
		}
	}
	else
	{
		tSimplePoly_noteOff(&myPoly, note);

		for (int v = 0; v < NUM_ENV; v++)
		{
			tADSRT_off(&envs[v]);
		}
	}



}


void __ATTR_ITCMRAM sendCtrl(uint8_t ctrl, uint8_t value)
{
	//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);

	sourceValues[CTRL_SOURCE_OFFSET + (ctrl - CTRL_MIDI_START)] = (float)value * INV_TWO_TO_7;
}


void __ATTR_ITCMRAM sendPitchBend(uint8_t value, uint8_t ctrl)
{
	int bendInt = value + (ctrl << 7);
	bendInt = bendInt - 8192;
	bend = bendInt * bendRangeMultiplier; //by default, divide by (16383 / 96 semitones)

}







void __ATTR_ITCMRAM HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hsai)
{
	if (!diskBusy)
	audioFrame(HALF_BUFFER_SIZE);
}

void __ATTR_ITCMRAM HAL_SAI_RxHalfCpltCallback(SAI_HandleTypeDef *hsai)
{
	if (!diskBusy)
	audioFrame(0);
}





void lfoSawSquareTick(float* sample, int v)
{
	*sample = tSawSquareLFO_tick(&lfoSawSquare[v]);
}

void lfoSineTriTick(float* sample, int v)
{
	*sample = tSineTriLFO_tick(&lfoSineTri[v]);
}

void lfoSineTick(float* sample, int v)
{
    *sample = tCycle_tick(&lfoSine[v]);
}

void lfoTriTick(float* sample, int v)
{
    *sample = tTriLFO_tick(&lfoTri[v]);
}
void lfoSawTick(float* sample, int v)
{
    *sample = (tIntPhasor_tick(&lfoSaw[v]) * 2.0f) - 1.0f;
}

void lfoPulseTick(float* sample, int v)
{
    *sample = tSquareLFO_tick(&lfoPulse[v]);
}

void lfoSawSquareSetRate(float r, int v)
{
	tSawSquareLFO_setFreq(&lfoSawSquare[v],r);
}

void lfoSineTriSetRate(float r, int v)
{
	tSineTriLFO_setFreq(&lfoSineTri[v],r);
}
void lfoSineSetRate(float r, int v)
{
	tCycle_setFreq(&lfoSine[v], r);
}
void lfoTriSetRate(float r, int v)
{
	tTriLFO_setFreq(&lfoTri[v], r);
}
void lfoSawSetRate(float r, int v)
{
	tIntPhasor_setFreq(&lfoSaw[v], r);
}
void lfoPulseSetRate(float r, int v)
{
	 tSquareLFO_setFreq(&lfoPulse[v], r);
}


void lfoSawSquareSetPhase(float p, int v)
{
	tSawSquareLFO_setPhase(&lfoSawSquare[v],p);
}
void lfoSineTriSetPhase(float p, int v)
{
	tSineTriLFO_setPhase(&lfoSineTri[v], p);
}
void lfoSineSetPhase(float p, int v)
{
	tCycle_setPhase(&lfoSine[v],p);
}
void lfoTriSetPhase(float p, int v)
{
	tTriLFO_setPhase(&lfoTri[v],p);
}
void lfoSawSetPhase(float p, int v)
{
	tIntPhasor_setPhase(&lfoSaw[v], p);
}
void lfoPulseSetPhase(float p, int v)
{
	tSquareLFO_setPhase(&lfoPulse[v], p);
}


void lfoSawSquareSetShape(float s, int v)
{
	tSawSquareLFO_setShape(&lfoSawSquare[v],s);
}
void lfoSineTriSetShape(float s, int v)
{
	tSineTriLFO_setShape(&lfoSineTri[v],s);
}
void lfoSineSetShape(float s, int v)
{
	//none
}
void lfoTriSetShape(float s, int v)
{
	//none
}
void lfoSawSetShape(float s, int v)
{
	//none
}
void lfoPulseSetShape(float s, int v)
{
	tSquareLFO_setPulseWidth(&lfoPulse[v], s);
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

float param1[NUM_EFFECT];
float param2[NUM_EFFECT];
float param3[NUM_EFFECT];
float param4[NUM_EFFECT];
float param5[NUM_EFFECT];
float shapeDividerS[NUM_EFFECT];
float shapeDividerH[NUM_EFFECT];
float wfState[NUM_EFFECT] = {0.0f, 0.0f, 0.0f, 0.0f};
float invCurFB[NUM_EFFECT];

void __ATTR_ITCMRAM  clipperGainSet(float value, int v)
{
	param1[v] = fasterdbtoa(value * 24.0f);
}
void __ATTR_ITCMRAM  wavefolderParam1(float value, int v)
{
	param1[v] = fasterdbtoa(value * 12.0f);
}
void __ATTR_ITCMRAM  wavefolderParam3(float value, int v)
{
	//value = (value * 0.99f) + 0.00f; //avoid zero
	invCurFB[v] = (1.0f / (1.0f + value));
	param3[v] = value;
}

void __ATTR_ITCMRAM  tiltParam1(float value, int v)
{
	tVZFilter_setGain(&shelf1[v], fasterdbtoa(-1.0f * ((value * 30.0f) - 15.0f)));
	tVZFilter_setGain(&shelf2[v], fasterdbtoa((value * 30.0f) - 15.0f));
}

void __ATTR_ITCMRAM  tiltParam2(float value, int v)
{
	value = (value * 77.0f) + 42.0f;
	value = LEAF_clip(0.0f, (value-16.0f) * 35.929824561403509f, 4095.0f);
	tVZFilter_setFreqFast(&bell1[v], value);
}
void __ATTR_ITCMRAM  tiltParam3(float value, int v)
{
	tVZFilter_setResonance(&bell1[v], (value +1.0f)*6.0f);//TODO: make this match plugin
}
void __ATTR_ITCMRAM  tiltParam4(float value, int v)
{
	tVZFilter_setGain(&bell1[v], fastdbtoa((value * 34.0f) - 17.0f));
}

void __ATTR_ITCMRAM  compressorParam1(float value, int v)
{
	comp[v]->T = value*-24.0f;
}
void __ATTR_ITCMRAM  compressorParam2(float value, int v)
{
	comp[v]->R = ((value*10.0f)+1.0f);
	comp[v]->invR  = 1.0f / comp[v]->R;
}

void __ATTR_ITCMRAM  compressorParam3(float value, int v)
{
	comp[v]->M = value * 18.0f;
}

void __ATTR_ITCMRAM  compressorParam4(float value, int v)
{
	value = (value +  0.001f);
	comp[v]->tauAttack = fasterexpf(-1.0f/(value * comp[v]->sampleRate));
}

void __ATTR_ITCMRAM  compressorParam5(float value, int v)
{
	value = (value + 0.001f);
	comp[v]->tauRelease = fasterexpf(-1.0f/(value * comp[v]->sampleRate));
}

void __ATTR_ITCMRAM  offsetParam2(float value, int v)
{
	param2[v] = (value * 2.0f) - 1.0f;
}
void __ATTR_ITCMRAM param2Linear(float value, int v)
{
	param2[v] = value;
}
void __ATTR_ITCMRAM param3Linear(float value, int v)
{
	param3[v] = value;
}
void __ATTR_ITCMRAM param3Soft(float value, int v)
{
	param3[v] = (value * .99f) + 0.01f;
	shapeDividerS[v] = 1.0f / (param3[v] - ((param3[v]*param3[v]*param3[v]) * 0.3333333f));
}

void __ATTR_ITCMRAM param3Hard(float value, int v)
{
	param3[v] = ((value * .99f) + 0.01f) * HALF_PI;
	shapeDividerH[v] = 1.0f / arm_sin_f32(param3[v]);
}
void __ATTR_ITCMRAM param4Linear(float value, int v)
{
	param4[v] = value;
}

void __ATTR_ITCMRAM param5Linear(float value, int v)
{
	param5[v] = value;
}
void __ATTR_ITCMRAM param2BC(float value, int v)
{
	tCrusher_setQuality (&bc[v],value);
}
void __ATTR_ITCMRAM param3BC(float value, int v)
{
	value = (value * inv_oversample) + 0.01f;
	tCrusher_setSamplingRatio (&bc[v], value);
}
void __ATTR_ITCMRAM param4BC(float value, int v)
{
	tCrusher_setRound(&bc[v], value);
}
void __ATTR_ITCMRAM param5BC(float value, int v)
{
	tCrusher_setOperation(&bc[v], value);
}



void __ATTR_ITCMRAM fxMixSet(float value, int v)
{
	fxMix[v] = value;
}

void __ATTR_ITCMRAM fxPostGainSet(float value, int v)
{
	fxPostGain[v] = fasterdbtoa((value * 24.0f) - 12.0f);
}


//got the idea from https://ccrma.stanford.edu/~jatin/ComplexNonlinearities/Wavefolder.html  -JS
//much more efficient than the lockhart, and can be further optimized with lookups
float __ATTR_ITCMRAM wavefolderTick(float sample, int v)
{
    sample = sample * param1[v] + ((param2[v] * param1[v]));
    float curFB = param3[v];
    float curFF = param4[v];

    //softclip approx for tanh saturation in original code
    float ffSample = sample;
    if (ffSample <= -1.0f)
    {
    	ffSample = -1.0f;
    } else if (ffSample >= 1.0f)
    {
    	ffSample = 1.0f;
    }
    ffSample = ffSample - ((ffSample * ffSample * ffSample)* 0.3333333f);
    ffSample *= 1.499999f;
    float ff = (curFF * ffSample) + ((1.0f - curFF) * sample);

    //softclip approx for tanh saturation in original code
    float fbSample = wfState[v];
    if (fbSample <= -1.0f)
    {
    	fbSample = -1.0f;
    } else if (fbSample >= 1.0f)
    {
    	fbSample = 1.0f;
    }
    fbSample = fbSample - ((fbSample * fbSample * fbSample)* 0.3333333f);
    fbSample *= 1.499999f;
    float fb = curFB * fbSample;

    wfState[v] = (ff + fb) - param5[v] * arm_sin_f32(TWO_PI * sample); //maybe switch for our own sine lookup (avoid the if statements in the CMSIS code)
    sample = wfState[v] * invCurFB[v];
    sample = tHighpass_tick(&dcBlock1[v], sample);
    return sample;
}

void __ATTR_ITCMRAM chorusParam1(float value, int v)
{
	param1[v] = value * 5780.0f + 10.0f;
}
void __ATTR_ITCMRAM chorusParam2(float value, int v)
{
	param2[v] = value * 0.1f;
}

void __ATTR_ITCMRAM chorusParam3(float value, int v)
{
    tCycle_setFreq(&mod1[v], (value * 0.4f) + 0.01f);
}

void __ATTR_ITCMRAM chorusParam4(float value, int v)
{
    tCycle_setFreq(&mod2[v], (value * 0.4444444f) + 0.011f);
}


float __ATTR_ITCMRAM chorusTick(float sample, int v)
{
	tLinearDelay_setDelay(&delay1[v], param1[v] * .707f * (1.0f + param2[v] * tCycle_tick(&mod1[v])));
    tLinearDelay_setDelay(&delay2[v], param1[v] * .5f * (1.0f - param2[v] * tCycle_tick(&mod2[v])));
    float temp = tLinearDelay_tick(&delay1[v], sample) - sample;
    temp += tLinearDelay_tick(&delay2[v], sample) - sample;
    //temp = tHighpass_tick(&dcBlock1[v], temp);
    return -temp;
}

float __ATTR_ITCMRAM shaperTick(float sample, int v)
{
    sample = sample * param1[v];
    float temp = LEAF_shaper(sample + (param2[v] * param1[v]),param3[v]);
    temp = tHighpass_tick(&dcBlock1[v], temp);
    return temp;
}

float __ATTR_ITCMRAM blankTick(float sample, int v)
{
    return sample;
}

float __ATTR_ITCMRAM tiltFilterTick(float sample, int v)
{
    sample = tVZFilter_tickEfficient(&shelf1[v], sample);
    sample = tVZFilter_tickEfficient(&shelf2[v], sample);
    sample = tVZFilter_tickEfficient(&bell1[v], sample);
    return sample;
}

float __ATTR_ITCMRAM tanhTick(float sample, int v)
{
    float gain = param1[v];
	sample = sample * gain;
    gain = gain * 0.5f;
    //need to do something with shape param
    float temp = tanhf(sample + (param2[v]*gain));
    temp = tHighpass_tick(&dcBlock1[v], temp);
    temp *= param4[v];
    temp = tanhf(temp);
    //temp = tHighpass_tick(&dcBlock2, temp);
    return temp;
}


float __ATTR_ITCMRAM softClipTick(float sample, int v)
{
    sample = sample * param1[v];
    sample = sample + param2[v];
    float shape = param3[v];
    if (sample <= -1.0f)
    {
        sample = -1.0f;
    } else if (sample >= 1.0f)
    {
        sample = 1.0f;
    }
    {
        sample = (shape * sample) - ((shape * (sample * sample * sample))* 0.3333333f);
        sample = sample * shapeDividerS[v];
    }

    sample = tHighpass_tick(&dcBlock1[v], sample);
    return sample;
}


float __ATTR_ITCMRAM hardClipTick(float sample, int v)
{

    sample = sample * param1[v];
    sample = sample + param2[v];
    if (sample <= -1.0f)
    {
        sample = -1.0f;
    } else if (sample >= 1.0f)
    {
        sample = 1.0f;
    }
    {
        sample = arm_sin_f32(  (arm_sin_f32(sample*param3[v]) * shapeDividerH[v]) * param3[v]);
        sample = sample * shapeDividerH[v];
    }

    sample = tHighpass_tick(&dcBlock1[v], sample);
    return sample;
}


float __ATTR_ITCMRAM satTick(float sample, int v)
{;
    sample = sample * param1[v];
    float temp = (sample + (param2[v] * param1[v])) / (1.0f + fabs(sample + param2[v]));
    temp = tHighpass_tick(&dcBlock1[v], temp);
    temp = tHighpass_tick(&dcBlock2[v], temp);
    temp = tanhf(temp);
    return temp;
}



float __ATTR_ITCMRAM bcTick(float sample, int v)
{
    sample = sample * param1[v];
    return tCrusher_tick(&bc[v], sample);
}


float __ATTR_ITCMRAM compressorTick(float sample, int v)
{
    return tCompressor_tick(&comp[v], sample);
}

float __ATTR_ITCMRAM  FXlowpassTick(float sample, int v)
{
	return tSVF_tick(&FXlowpass[v], sample);
}

float __ATTR_ITCMRAM  FXhighpassTick(float sample, int v)
{
	return tSVF_tick(&FXhighpass[v], sample);
}

float __ATTR_ITCMRAM  FXbandpassTick(float sample, int v)
{
	return tSVF_tick(&FXbandpass[v], sample);
}

float __ATTR_ITCMRAM  FXdiodeLowpassTick(float sample, int v)
{
	return tDiodeFilter_tick(&FXdiodeFilters[v], sample);
}

float __ATTR_ITCMRAM  FXVZpeakTick(float sample, int v)
{
	return tVZFilter_tickEfficient(&FXVZfilterPeak[v], sample);
}

float __ATTR_ITCMRAM  FXVZlowshelfTick(float sample, int v)
{
	return tVZFilter_tickEfficient(&FXVZfilterLS[v], sample);
}
float __ATTR_ITCMRAM  FXVZhighshelfTick(float sample, int v)
{
	return tVZFilter_tickEfficient(&FXVZfilterHS[v], sample);
}
float __ATTR_ITCMRAM  FXVZbandrejectTick(float sample, int v)
{
	return  tVZFilter_tickEfficient(&FXVZfilterBR[v], sample);
}

float __ATTR_ITCMRAM  FXLadderLowpassTick(float sample, int v)
{
	return tLadderFilter_tick(&FXLadderfilter[v], sample);
}
//cutoffparams

void FXLowpassParam1(float value, int v)
{
	value = (value * 77.0f) + 42.0f;
	value = LEAF_clip(0.0f, (value-16.0f) * 35.929824561403509f, 4095.0f);
	tSVF_setFreqFast(&FXlowpass[v], value);
}
void FXHighpassParam1(float value, int v)
{
	value = (value * 77.0f) + 42.0f;
	value = LEAF_clip(0.0f, (value-16.0f) * 35.929824561403509f, 4095.0f);
	tSVF_setFreqFast(&FXhighpass[v], value);
}

void FXBandpassParam1(float value, int v)
{
	value = (value * 77.0f) + 42.0f;
	value = LEAF_clip(0.0f, (value-16.0f) * 35.929824561403509f, 4095.0f);
    tSVF_setFreqFast(&FXbandpass[v], value);
}

void FXDiodeParam1(float value, int v)
{
	value = (value * 77.0f) + 42.0f;
	value = LEAF_clip(0.0f, (value-16.0f) * 35.929824561403509f, 4095.0f);
	tDiodeFilter_setFreqFast(&FXdiodeFilters[v], value);
}
void FXPeakParam1(float value, int v)
{
	value = (value * 77.0f) + 42.0f;
	value = LEAF_clip(0.0f, (value-16.0f) * 35.929824561403509f, 4095.0f);
	tVZFilter_setFreqFast(&FXVZfilterPeak[v], value);
}
void FXLowShelfParam1(float value, int v)
{
	value = (value * 77.0f) + 42.0f;
    value = LEAF_clip(0.0f, (value-16.0f) * 35.929824561403509f, 4095.0f);
    tVZFilter_setFreqFast(&FXVZfilterLS[v], value);
}
void FXHighShelfParam1(float value, int v)
{
	value = (value * 77.0f) + 42.0f;
	value = LEAF_clip(0.0f, (value-16.0f) * 35.929824561403509f, 4095.0f);
	tVZFilter_setFreqFast(&FXVZfilterHS[v], value);
}
void FXNotchParam1(float value, int v)
{
	value = (value * 77.0f) + 42.0f;
	value = LEAF_clip(0.0f, (value-16.0f) * 35.929824561403509f, 4095.0f);
	tVZFilter_setFreqFast(&FXVZfilterBR[v], value);
}
void FXLadderParam1(float value, int v)
{
	value = (value * 77.0f) + 42.0f;
	value = LEAF_clip(0.0f, (value-16.0f) * 35.929824561403509f, 4095.0f);
	tLadderFilter_setFreqFast(&FXLadderfilter[v], value);
}

//gain params

void FXPeakParam2(float value, int v)
{
	 tVZFilter_setGain(&FXVZfilterPeak[v], fasterdbtoa((value * 50.f) - 25.f));
}

void FXLowShelfParam2(float value, int v)
{
tVZFilter_setGain(&FXVZfilterLS[v], fasterdbtoa((value * 50.f) - 25.f));
}

void FXHighShelfParam2(float value, int v)
{
	tVZFilter_setGain(&FXVZfilterHS[v], fasterdbtoa((value * 50.f) - 25.f));
}

void FXNotchParam2(float value, int v)
{
	tVZFilter_setGain(&FXVZfilterBR[v], fasterdbtoa((value * 50.f) - 25.f));

}
//resonance params
void FXLowpassParam3(float value, int v)
{
	tSVF_setQ(&FXlowpass[v], value);
}

void FXHighpassParam3(float value, int v)
{
    tSVF_setQ(&FXhighpass[v], value);
}

void FXBandpassParam3(float value, int v)
{
    tSVF_setQ(&FXbandpass[v], value);
}

void FXDiodeParam3(float value, int v)
{
	tDiodeFilter_setQ(&FXdiodeFilters[v], value);
}


void FXPeakParam3(float value, int v)
{
	tVZFilter_setResonance(&FXVZfilterPeak[v], value);
}


void FXLowShelfParam3(float value, int v)
{
	tVZFilter_setResonance(&FXVZfilterLS[v], value);
}


void FXHighShelfParam3(float value, int v)
{
	tVZFilter_setResonance(&FXVZfilterHS[v], value);
}


void FXNotchParam3(float value, int v)
{
	tVZFilter_setResonance(&FXVZfilterBR[v], value);
}


void FXLadderParam3(float value, int v)
{
	tLadderFilter_setQ(&FXLadderfilter[v], value);
}




/////NOISE///

void __ATTR_ITCMRAM noiseSetTilt(float value, int v)
{
	tVZFilter_setGain(&noiseShelf1, fastdbtoa(-1.0f * ((value * 30.0f) - 15.0f)));
	tVZFilter_setGain(&noiseShelf2, fastdbtoa((value * 30.0f) - 15.0f));
}


void __ATTR_ITCMRAM noiseSetGain(float value, int v)
{
	tVZFilter_setGain(&noiseBell1, fastdbtoa((value* 34.0f) - 17.0f));
}

void __ATTR_ITCMRAM noiseSetFreq(float value, int v)
{
	value = (value * 77.0f) + 42.0f;
	value = LEAF_clip(0.0f, (value-16.0f) * 35.929824561403509f, 4095.0f);
	tVZFilter_setFreqFast(&noiseBell1, value);
}

uint32_t timeNoise = 0;
uint32_t timeRandom = 0;


void __ATTR_ITCMRAM noise_tick()
{
	uint32_t tempCount7 = DWT->CYCCNT;
	float enabled = params[Noise].realVal;
	float amp = params[NoiseAmp].realVal;
	float filterSend = params[NoiseFilterSend].realVal;
	amp = amp < 0.f ? 0.f : amp;

	uint32_t tempCount9 = DWT->CYCCNT;
	float sample = random_values[randomValPointer++];
	uint32_t tempCount10 = DWT->CYCCNT;
	timeRandom = tempCount10-tempCount9;

	sample = tVZFilter_tickEfficient(&noiseShelf1, sample);
	sample = tVZFilter_tickEfficient(&noiseShelf2, sample);
	sample = tVZFilter_tickEfficient(&noiseBell1, sample);
	sample = sample * amp;
	float normSample = (sample + 1.f) * 0.5f;
	sourceValues[NOISE_SOURCE_OFFSET] = normSample;
	noiseOuts[0] = sample * filterSend *  enabled;
	noiseOuts[1] = sample * (1.f-filterSend) * enabled ;
	uint32_t tempCount8 = DWT->CYCCNT;
	timeNoise = tempCount8-tempCount7;
}


