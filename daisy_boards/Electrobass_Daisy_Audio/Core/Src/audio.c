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

cStack midiStack;

HAL_StatusTypeDef transmit_status;
HAL_StatusTypeDef receive_status;

volatile uint32_t cycleCount[10];

//function pointers
shapeTick_t shapeTick[NUM_OSC];
filterTick_t filterTick[NUM_FILT];
lfoShapeTick_t lfoShapeTick[NUM_LFOS];
arm_fir_decimate_instance_f32 osD;
arm_fir_interpolate_instance_f32 osI;

//oscillators
tMBSaw saw[NUM_OSC];
tMBPulse pulse[NUM_OSC];
tCycle sine[NUM_OSC];
tMBTriangle tri[NUM_OSC];

// Using seperate objects for pairs to easily maintain phase relation
tMBSawPulse sawPaired[NUM_OSC];
tMBPulse pulsePaired[NUM_OSC];
tCycle sinePaired[NUM_OSC];
tMBTriangle triPaired[NUM_OSC];

tWaveOscS wave[NUM_OSC];


tIntPhasor lfoSaw[NUM_LFOS];
tSquareLFO lfoPulse[NUM_LFOS];
tCycle lfoSine[NUM_LFOS];
tTriLFO lfoTri[NUM_LFOS];
tSawSquareLFO lfoSawSquare[NUM_LFOS];
tSineTriLFO lfoSineTri[NUM_LFOS];

//oscillator outputs
float outSamples[2][NUM_OSC];


//source vals
float sourceValues[NUM_SOURCES];

tExpSmooth mapSmoothers[MAX_NUM_MAPPINGS];

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


//master
float amplitude = 0.0f;
float finalMaster = 1.0f;

float sample = 0.0f;
tSimplePoly myPoly;
float bend;
float transpose = 0.0f;
tNoise noise;

#define OVERSAMPLE 2
tOversampler os;
float oversamplerArray[OVERSAMPLE];

float upState1[128];
float downState1[128];

uint8_t voiceSounding = 0;

//MEMPOOLS
#define SMALL_MEM_SIZE 65000
char smallMemory[SMALL_MEM_SIZE];

//#define MEDIUM_MEM_SIZE 100000
//char mediumMemory[MEDIUM_MEM_SIZE] __ATTR_RAM_D1;

//#define LARGE_MEM_SIZE 33554432 //32 MBytes - size of SDRAM IC
//char largeMemory[LARGE_MEM_SIZE] __ATTR_SDRAM;

LEAF leaf;

tMempool smallPool;
tMempool largePool;

int MBoffset = 0;

void audio_init(void)
{
	LEAF_init(&leaf, SAMPLE_RATE, smallMemory, SMALL_MEM_SIZE, &randomNumber);
	//tMempool_init (&smallPool, smallMemory, SMALL_MEM_SIZE, &leaf);
	//tMempool_init (&largePool, largeMemory, LARGE_MEM_SIZE, &leaf);
	for(int i = 0; i < NUM_OSC; i++)
	{
		tMBSaw_init(&saw[i], &leaf);
		tMBSaw_setBufferOffset(&saw[i], MBoffset);
		MBoffset = (MBoffset + AUDIO_FRAME_SIZE) % FILLEN;

		tMBPulse_init(&pulse[i], &leaf);
		tMBPulse_setBufferOffset(&pulse[i], MBoffset);
		MBoffset = (MBoffset + AUDIO_FRAME_SIZE) % FILLEN;

		tCycle_init(&sine[i], &leaf);

		tMBTriangle_init(&tri[i], &leaf);
		tMBTriangle_setBufferOffset(&tri[i], MBoffset);
		MBoffset = (MBoffset + AUDIO_FRAME_SIZE) % FILLEN;

		// Using seperate objects for pairs to easily maintain phase relation
		tMBSawPulse_init(&sawPaired[i], &leaf);
		tMBSawPulse_setBufferOffset(&sawPaired[i], MBoffset);
		MBoffset = (MBoffset + AUDIO_FRAME_SIZE) % FILLEN;

		//tMBPulse_init(&pulsePaired[i], &leaf);
		//tMBPulse_setBufferOffset(&pulsePaired[i], MBoffset);
		//MBoffset = (MBoffset + AUDIO_FRAME_SIZE) % FILLEN;

		tCycle_init(&sinePaired[i], &leaf);

		tMBTriangle_init(&triPaired[i], &leaf);
		tMBTriangle_setBufferOffset(&triPaired[i], MBoffset);
		MBoffset = (MBoffset + AUDIO_FRAME_SIZE) % FILLEN;
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

	for (int i = 0; i < NUM_LFOS; i++)
	{
		tIntPhasor_init(&lfoSaw[i], &leaf);
		tSquareLFO_init(&lfoPulse[i], &leaf);
		tCycle_init(&lfoSine[i], &leaf);
		tTriLFO_init(&lfoTri[i], &leaf);

		tSineTriLFO_init(&lfoSineTri[i], &leaf);
		tSawSquareLFO_init(&lfoSawSquare[i], &leaf);
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

    for (int i = 0; i < MAX_NUM_MAPPINGS; i++)
    {
    	tExpSmooth_init(&mapSmoothers[i], 0.0f, 0.02f, &leaf);
    }

	tSimplePoly_init(&myPoly, 1, &leaf);
	tNoise_init(&noise, WhiteNoise, &leaf);

	tOversampler_init(&os, OVERSAMPLE, 0, &leaf);

    int idx = (int)(log2f(OVERSAMPLE))-1;
    int numTaps = __leaf_tablesize_firNumTaps[idx];

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
}

const int syncMap[3] = {2, 0, 1};
uint32_t timeMIDI = 0;

void audioFrame(uint16_t buffer_offset)
{
	volatile uint32_t tmpCnt = 0;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);

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
	tmpCnt = DWT->CYCCNT - tmpCnt;
	timeMIDI = tmpCnt;

	int32_t current_sample = 0;

	for (int i = 0; i < (HALF_BUFFER_SIZE); i++)
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
uint32_t timeOsc = 0;

void oscillator_tick(float note)
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
		int sync = roundf(oscParams[OscisSync].realVal);
		float finalFreq = (mtof(note + (fine*0.01f)) * freqMult[osc]) + freqOffset ;
		finalFreq = LEAF_clip(-19000.0f, finalFreq, 19000.0f);
		float sample = 0.0f;

		shapeTick[osc](&sample, osc, finalFreq, shape, sync);

		sample *= amp;

		sourceValues[OSC_SOURCE_OFFSET + osc] = sample; // the define of zero may be wasteful

		sample *= INV_NUM_OSCS;

		oscOuts[0][osc] = sample * filterSend * oscParams[OscEnabled].realVal;
		oscOuts[1][osc] = sample * (1.f-filterSend) * oscParams[OscEnabled].realVal;
	}
	uint32_t tempCount2 = DWT->CYCCNT;

	timeOsc = tempCount2-tempCount1;
}


void sawSquareTick(float* sample, int v, float freq, float shape, int sync)
{
    tMBSawPulse_setFreq(&sawPaired[v], freq);
    tMBSawPulse_setShape(&sawPaired[v], shape);
    if (sync)
    {
    	tMBSawPulse_sync(&sawPaired[v], sourceValues[syncMap[OSC_SOURCE_OFFSET + v]]);

    }
    *sample += tMBSawPulse_tick(&sawPaired[v]) * 2.f;
}

void sineTriTick(float* sample, int v, float freq, float shape, int sync)
{
    tCycle_setFreq(&sinePaired[v], freq);
    tMBTriangle_setFreq(&triPaired[v], freq);
    if (sync)
    {
    	tMBTriangle_sync(&triPaired[v], sourceValues[syncMap[OSC_SOURCE_OFFSET + v]]);
    }
    *sample += tCycle_tick(&sinePaired[v]) * (1.0f - shape);
    *sample += tMBTriangle_tick(&triPaired[v]) * shape * 2.f;;
}

void sawTick(float* sample, int v, float freq, float shape, int sync)
{
    tMBSaw_setFreq(&saw[v], freq);
    if (sync)
	{
		tMBSaw_sync(&saw[v], sourceValues[syncMap[OSC_SOURCE_OFFSET + v]]);
	}
    *sample += tMBSaw_tick(&saw[v]) * 2.f;;
}

void pulseTick(float* sample, int v, float freq, float shape, int sync)
{
    tMBPulse_setFreq(&pulse[v], freq);
    tMBPulse_setWidth(&pulse[v], shape);
    if (sync)
	{
		tMBPulse_sync(&pulse[v], sourceValues[syncMap[OSC_SOURCE_OFFSET + v]]);
	}
    *sample += tMBPulse_tick(&pulse[v]) * 2.f;;
}

void sineTick(float* sample, int v, float freq, float shape, int sync)
{
    tCycle_setFreq(&sine[v], freq);
    *sample += tCycle_tick(&sine[v]);
}

void triTick(float* sample, int v, float freq, float shape, int sync)
{
    tMBTriangle_setFreq(&tri[v], freq);
    tMBTriangle_setWidth(&tri[v], shape);
    if (sync)
	{
		tMBTriangle_sync(&tri[v], sourceValues[syncMap[OSC_SOURCE_OFFSET + v]]);
	}
    *sample += tMBTriangle_tick(&tri[v]) * 2.0f;;
}

void userTick(float* sample, int v, float freq, float shape, int sync)
{
    //tWaveOscS_setFreq(&wave[v], freq);
    //tWaveOscS_setIndex(&wave[v], shape);
    //*sample += tWaveOscS_tick(&wave[v]);
}

uint32_t timeFilt = 0;

float filter_tick(float* samples, float note)
{
	interruptChecker = 0;
	uint32_t tempCount1 = DWT->CYCCNT;
	float cutoff[2];
	uint8_t enabledFilt[2] = {0,0};
	for (int f = 0; f < NUM_FILT; f++)
	{
		param* filtParams = &params[FILTER_PARAMS_OFFSET + f * FilterParamsNum];
		float MIDIcutoff = filtParams[FilterCutoff].realVal;
		float keyFollow = filtParams[FilterKeyFollow].realVal;
		float enabled = filtParams[FilterEnabled].realVal;
		enabledFilt[f] = (enabled > 0.5f);
		if (!enabledFilt[f]) continue;


		if (isnan(note))
		{
			note = 0.0f; //is this necessary?
		}

		cutoff[f] = MIDIcutoff + (note * keyFollow);
		cutoff[f] = LEAF_clip(0.0f, (cutoff[f]-16.0f) * 35.929824561403509f, 4095.0f);
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
	uint32_t tempCount2 = DWT->CYCCNT;

	timeFilt = tempCount2-tempCount1;
	return samples[1] + (samples[0] * sp);
}


void lowpassTick(float* sample, int v, float cutoff)
{
	tSVF_setFreqFast(&lowpass[v], cutoff);
	*sample = tSVF_tick(&lowpass[v], *sample);
    *sample *= filterGain[v];
}

void highpassTick(float* sample, int v, float cutoff)
{
	tSVF_setFreqFast(&highpass[v], cutoff);
	*sample = tSVF_tick(&highpass[v], *sample);
    *sample *= filterGain[v];
}

void bandpassTick(float* sample, int v, float cutoff)
{
	tSVF_setFreqFast(&bandpass[v], cutoff);
	*sample = tSVF_tick(&bandpass[v], *sample);
    *sample *= filterGain[v];
}

void diodeLowpassTick(float* sample, int v, float cutoff)
{
	tDiodeFilter_setFreqFast(&diodeFilters[v], cutoff);
	*sample = tDiodeFilter_tick(&diodeFilters[v], *sample);
    *sample *= filterGain[v];
}

void VZpeakTick(float* sample, int v, float cutoff)
{
	tVZFilter_setFreqFast(&VZfilterPeak[v], cutoff);
	*sample = tVZFilter_tickEfficient(&VZfilterPeak[v], *sample);
}

void VZlowshelfTick(float* sample, int v, float cutoff)
{
	tVZFilter_setFreqFast(&VZfilterLS[v], cutoff);
	*sample = tVZFilter_tickEfficient(&VZfilterLS[v], *sample);
}
void VZhighshelfTick(float* sample, int v, float cutoff)
{
	tVZFilter_setFreqFast(&VZfilterHS[v], cutoff);
	*sample = tVZFilter_tickEfficient(&VZfilterHS[v], *sample);
}
void VZbandrejectTick(float* sample, int v, float cutoff)
{
	tVZFilter_setFreqFast(&VZfilterBR[v], cutoff);
	*sample = tVZFilter_tickEfficient(&VZfilterBR[v], *sample);
    *sample *= filterGain[v];
}

void LadderLowpassTick(float* sample, int v, float cutoff)
{
	tLadderFilter_setFreqFast(&Ladderfilter[v], cutoff);
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
		if (harm_pitch >= 0)
		{
			freqMult[osc] = (harm_pitch + 1);
		}
		else
		{
			freqMult[osc] = (1.0f / fabsf((harm_pitch - 1)));
		}
	}
	else
	{
		freqMult[osc] = powf(1.059463094359295f, harm_pitch);
	}
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

uint32_t timeEnv = 0;
void envelope_tick(void)
{
	interruptChecker = 0;
	uint32_t tempCount1 = DWT->CYCCNT;
	for (int v = 0; v < NUM_ENV; v++)
	{
		float value = tADSRT_tick(&envs[v]); //used to be noInterp but wanted to check if this sounds better and isn't too slow
		sourceValues[ENV_SOURCE_OFFSET + v] = value;
	}
	uint32_t tempCount2 = DWT->CYCCNT;
	timeEnv = tempCount2-tempCount1;
}

uint32_t timeLFO = 0;
void lfo_tick(void)
{
	interruptChecker = 0;
	uint32_t tempCount1 = DWT->CYCCNT;
	for (int i = 0; i < NUM_LFOS; i++)
	{
		float sample = 0.0f;
		lfoShapeTick[i](&sample,i);
		sourceValues[LFO_SOURCE_OFFSET + i] = sample;
	}
	uint32_t tempCount2 = DWT->CYCCNT;
	timeLFO = tempCount2-tempCount1;
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

void setMaster(float amp, int v)
{
	finalMaster = amp;
}

void setTranspose(float in, int v)
{
	transpose = in;
}

void setPitchBendRangeUp(float in, int v)
{
	bendRangeMultiplier = 1.0f / (16383.0f / (in * 2.0f));
}

void setPitchBendRangeDown(float in, int v)
{
	//bendRangeDown = in; //ignored for now
}

uint32_t timeMap = 0;
void tickMappings(void)
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
	uint32_t tempCount2 = DWT->CYCCNT;
	timeMap = tempCount2-tempCount1;

}
uint32_t timeTick = 0;


float audioTickL(float audioIn)
{
	uint32_t tempCount5 = DWT->CYCCNT;
	sample = 0.0f;

		//run mapping ticks
		tickMappings();

		float note = bend + transpose + (float)tSimplePoly_getPitch(&myPoly, 0);



		envelope_tick();
		lfo_tick();
		oscillator_tick(note);

		float filterSamps[2] = {0.0f, 0.0f};
		for (int i = 0; i < NUM_OSC; i++)
		{
			filterSamps[0] += oscOuts[0][i];
			filterSamps[1] += oscOuts[1][i];
		}
		//sample = filterSamps[0];
		sample = filter_tick(&filterSamps[0], note);

		sample *= amplitude;

		uint32_t tempCount1 = DWT->CYCCNT;

		//oversample for non-linear effects (distortion, etc)
        //tOversampler_upsample(&os, sample, oversamplerArray);
/*
		arm_fir_interpolate_f32(
		  &osI,
		  &sample,
		  (float*)&oversamplerArray,
		  1);
		  */
/*
        for (int i = 0; i < fx.size(); i++) {
            fx[i]->oversample_tick(oversamplerArray, v);
        }
*/
        //hard clip before downsampling to get a little more antialiasing from clipped signal.
        //for (int i = 0; i < (OVERSAMPLE); i++)
        //{
        //    oversamplerArray[i] = LEAF_clip(-1.0f, oversamplerArray[i], 1.0f);
        //}
		sample = LEAF_clip(-1.0f, sample, 1.0f);
        //downsample to get back to normal sample rate
        //sample = tOversampler_downsample(&os, oversamplerArray);
/*
        arm_fir_decimate_f32(
          &osD,
		  (float*)&oversamplerArray,
          &sample,
          OVERSAMPLE);
*/
    	uint32_t tempCount2 = DWT->CYCCNT;

    	cycleCount[5] = tempCount2-tempCount1;

		sample *= finalMaster;

		uint32_t tempCount6 = DWT->CYCCNT;
		timeTick = tempCount6-tempCount5;
	return sample * audioMasterLevel;
}



void sendNoteOn(uint8_t note, uint8_t velocity)
{
	if (velocity > 0)
	{
		tSimplePoly_noteOn(&myPoly, note, velocity);
		float fvelocity = (float)velocity;
		fvelocity = ((0.007685533519034f*fvelocity) + 0.0239372430f);
		fvelocity = fvelocity * fvelocity;
		for (int v = 0; v < NUM_ENV; v++)
		{
			param* envParams = &params[ENVELOPE_PARAMS_OFFSET + v * EnvelopeParamsNum];
			float useVelocity = envParams[EnvelopeVelocity].realVal;
			float envVel = fvelocity;
			if (useVelocity == 0) envVel = 1.f;
		    tADSRT_on(&envs[v], envVel);
		    voiceSounding = 1;
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


void sendCtrl(uint8_t ctrl, uint8_t value)
{
	//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);

	sourceValues[CTRL_SOURCE_OFFSET + (ctrl - CTRL_MIDI_START)] = (float)value * INV_TWO_TO_7;
}


void sendPitchBend(uint8_t value, uint8_t ctrl)
{
	int bendInt = value + (ctrl << 7);
	bendInt = bendInt - 8192;
	bend = bendInt * bendRangeMultiplier; //by default, divide by (16383 / 48 semitones)

}







void HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hsai)
{
	if (!diskBusy)
	audioFrame(HALF_BUFFER_SIZE);
}

void HAL_SAI_RxHalfCpltCallback(SAI_HandleTypeDef *hsai)
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



void cStack_init(cStack* stack)
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
void cStack_push(cStack* stack, uint8_t val, uint8_t val1, uint8_t val2)
{
    stack->buffer[stack->writeCnt][0] = val;
    stack->buffer[stack->writeCnt][1] = val1;
    stack->buffer[stack->writeCnt][2] = val2;
    stack->writeCnt = (stack->writeCnt + 1 ) & 63;
}

void cStack_pop(cStack* stack, uint8_t* output)
{
    output[0] = stack->buffer[stack->readCnt][0];
    output[1] = stack->buffer[stack->readCnt][1];
    output[2] = stack->buffer[stack->readCnt][2];
    stack->readCnt = (stack->readCnt + 1) & 63;

}



