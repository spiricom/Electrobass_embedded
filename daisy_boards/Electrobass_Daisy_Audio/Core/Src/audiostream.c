/*
 * audio.c
 *
 *  Created on: Jul 6, 2022
 *      Author: jeffsnyder
 */
#include "main.h"
#include "leaf.h"
#include "codec.h"
#include "i2c.h"
#include "gpio.h"
#include "spi.h"
#include "parameters.h"
#include "audiostream.h"
#include "arm_math.h"
#include "string1.h"
#include "string2.h"
#include "additive.h"
#include "vocal.h"
#include "synth.h"
#include "string3.h"

//the audio buffers are put in the D2 RAM area because that is a memory location that the DMA has access to.
int32_t audioOutBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2_DMA;
int32_t audioInBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2_DMA;
char small_memory[SMALL_MEM_SIZE];
char medium_memory[MED_MEM_SIZE] __ATTR_RAM_D1;
char large_memory[LARGE_MEM_SIZE] __ATTR_SDRAM;
tMempool mediumPool;
tMempool largePool;
volatile uint32_t newPluck = 0 ;
cStack midiStack;
//float fractionalMidi[128];
HAL_StatusTypeDef transmit_status;
HAL_StatusTypeDef receive_status;
BOOL bufferCleared = TRUE;
int numBuffersToClearOnLoad = 2;
int numBuffersCleared = 0;
float masterVolFromBrain = 0.5f;
float masterVolFromBrainForSynth = 0.25f;
tSimplePoly myPoly;
float mtofTable[MTOF_TABLE_SIZE]__ATTR_RAM_D2;
volatile uint16_t previousStringInputs[12];
float barInMIDI[2] = {0.0f, 0.0f};
float prevBarInMIDI[2] = {0.0f, 0.0f};
float atoDbTable[ATODB_TABLE_SIZE]__ATTR_RAM_D2;
float dbtoATable[DBTOA_TABLE_SIZE]__ATTR_RAM_D2;
uint8_t numStringsThisBoard = NUM_STRINGS_PER_BOARD;

tExpSmooth stringFreqSmoothers[NUM_STRINGS_PER_BOARD];
float freqToSmoothMemoryGlobal[NUM_STRINGS_PER_BOARD];
float prevStringMIDI[NUM_STRINGS_PER_BOARD] ={64.0f};
tExpSmooth volumeSmoother;
tExpSmooth knobSmoothers[20];

float stringMidiPitchesNoBend = 0.0f;
float prevStringMidiPitchesNoBend = 0.0f;

uint8_t lsDecay[NUM_STRINGS_PER_BOARD];

audioFrame_t audioFrameFunction;
//envelope tables
float decayExpBuffer[DECAY_EXP_BUFFER_SIZE];
float decayExpBufferSizeMinusOne;
LEAF leaf;

union breakFloat{
	float f;
	uint8_t b[4];
};


float prevSamp[NUM_STRINGS_PER_BOARD];

tADSRT fenvelopes[NUM_STRINGS_PER_BOARD];


tVZFilter noiseFilt;
tVZFilter noiseFilt2;
volatile int firstString = 0;
float invNumStrings = 1.0f;
tNoise myNoise;
volatile uint16_t stringInputs[NUM_STRINGS];
volatile uint8_t resetStringInputs = 0;
float octave;

float atodbTableScalar;
float atodbTableOffset;
float dbtoaTableScalar;
float dbtoaTableOffset;

float stringMappedPositions[NUM_STRINGS]  = {1.0f, 1.0f, 1.0f, 1.0f};
float stringFrequencies[NUM_STRINGS] ;

float volumePedal  = 0.0f;
float knobScaled[20];
volatile uint8_t knobFrozen[20];
float pedalScaled[10];
volatile float stringMIDIPitches[NUM_STRINGS_PER_BOARD] = {64.0f};

volatile int voice = 0 ;
volatile int prevVoice = 127;
int dualSlider = 0;
int neck = 0;

int currentBarBuffer = 0;
int currentPluckBuffer = 0;

int edit = 0;
int whichTable = 0;
int presetReady = 0;
uint8_t whichStringModelLoaded = NothingLoaded;
float bendRangeMultiplier = 0.002929866324849f; //default to divide by 48


float stringOctave[NUM_STRINGS_PER_BOARD];



volatile float MIDIerror = 0.0f;

uint8_t interrupted = 0;

uint32_t timeFrame = 0;
float frameLoadPercentage = 0.0f;
float frameLoadMultiplier = 1.0f / (10000.0f * AUDIO_FRAME_SIZE);
uint32_t frameLoadOverCount = 0;

volatile uint16_t sampleClippedCountdown = 0;

volatile uint16_t volumePedalInt;
float octaveRatios[4] = {0.5f, 1.0f, 2.0f, 4.0f};

int octaveIndex = 1;
int stringOctaveIndex[4];

float pluckPos = 0.5f;
volatile int switchStrings = 0;
volatile uint8_t octaveAction = 0;

/**********************************************/

float FORCE_INLINE aToDbTableLookup(float in)
{
    in = fastabsf(in);
    float floatIndex = LEAF_clip (0, (in * atodbTableScalar) - atodbTableOffset, ATODB_TABLE_SIZE_MINUS_ONE);
    uint32_t inAmpIndex = (uint32_t) floatIndex;
    uint32_t inAmpIndexPlusOne = inAmpIndex + 1;
    if (inAmpIndexPlusOne > ATODB_TABLE_SIZE_MINUS_ONE)
    {
    	inAmpIndexPlusOne = ATODB_TABLE_SIZE_MINUS_ONE;
    }
    float alpha = floatIndex - (float)inAmpIndex;
    return ((atoDbTable[inAmpIndex] * (1.0f - alpha)) + (atoDbTable[inAmpIndexPlusOne] * alpha));
}

float FORCE_INLINE aToDbTableLookupFast(float in)
{
    in = fastabsf(in);
    uint32_t inAmpIndex = LEAF_clip (0, (in * atodbTableScalar) - atodbTableOffset, ATODB_TABLE_SIZE_MINUS_ONE);
    return atoDbTable[inAmpIndex];
}

float FORCE_INLINE dbToATableLookup(float in)
{
    float floatIndex = LEAF_clip (0, (in * dbtoaTableScalar) - dbtoaTableOffset, DBTOA_TABLE_SIZE_MINUS_ONE);
    uint32_t inDBIndex = (uint32_t) floatIndex;
    uint32_t inDBIndexPlusOne = inDBIndex + 1;
    if (inDBIndexPlusOne > DBTOA_TABLE_SIZE_MINUS_ONE)
    {
    	inDBIndexPlusOne = DBTOA_TABLE_SIZE_MINUS_ONE;
    }
    float alpha = floatIndex - (float)inDBIndex;
    return ((dbtoATable[inDBIndex] * (1.0f - alpha)) + (dbtoATable[inDBIndexPlusOne] * alpha));
}

float FORCE_INLINE dbToATableLookupFast(float in)
{
    uint32_t inDBIndex = LEAF_clip (0, (in * dbtoaTableScalar) - dbtoaTableOffset, DBTOA_TABLE_SIZE_MINUS_ONE);
    return dbtoATable[inDBIndex];
}



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
	LEAF_init(&leaf, SAMPLE_RATE, small_memory, SMALL_MEM_SIZE, &randomNumber);

		tMempool_init (&mediumPool, medium_memory, MED_MEM_SIZE, &leaf);
		tMempool_init (&largePool, large_memory, LARGE_MEM_SIZE, &leaf);

		leaf.clearOnAllocation = 1;
		LEAF_generate_exp(decayExpBuffer, 0.001f, 0.0f, 1.0f, -0.0008f, DECAY_EXP_BUFFER_SIZE); // exponential decay buffer falling from 1 to 0
		decayExpBufferSizeMinusOne = DECAY_EXP_BUFFER_SIZE - 1;

		for (int i = 0; i < 12; i++)
		{
			previousStringInputs[i]	= 0;
		}

		LEAF_generate_atodb(atoDbTable, ATODB_TABLE_SIZE, 0.00001f, 1.0f);
		LEAF_generate_dbtoa(dbtoATable, DBTOA_TABLE_SIZE, -90.0f, 50.0f);

		atodbTableScalar = ATODB_TABLE_SIZE_MINUS_ONE/(1.0f-0.00001f);
		atodbTableOffset = 0.00001f * atodbTableScalar;
		dbtoaTableScalar = DBTOA_TABLE_SIZE_MINUS_ONE/(50.0f+90.0f);
		dbtoaTableOffset = -90.0f * dbtoaTableScalar;

		LEAF_generate_mtof(mtofTable, -163.8375f, 163.8375f,  MTOF_TABLE_SIZE); //mtof table for fast calc



	tSimplePoly_init(&myPoly, 1, &leaf);

	numStringsThisBoard = 1;

	tExpSmooth_init(&volumeSmoother,0.0f, 0.0005f, &leaf);
		for (int i = 0; i < 20; i++)
		{
			tExpSmooth_init(&knobSmoothers[i],0.0f, 0.0005f, &leaf);
		}

		for (int i = 0; i < NUM_STRINGS_PER_BOARD; i++)
		{
			//tExpSmooth_init(&barSlideSmoother[i],0.000f, 0.01f, &leaf);
			//tEnvelopeFollower_init(&barNoiseSmoother[i],0.0001f, 0.9993f, &leaf);
			tExpSmooth_init(&stringFreqSmoothers[i],64.0f, 0.0009f, &leaf);
		}

		audioInitAdditive();
		//audioInitString1();
		audioInitVocal();
		audioInitSynth();
		audioInitString3();


		for (int v = 0; v < NUM_STRINGS_PER_BOARD; v++)
			{


				tADSRT_init(&fenvelopes[v], 0.0f,  50.0f, 0.0f, 200.0f, decayExpBuffer, DECAY_EXP_BUFFER_SIZE, &leaf);


				tVZFilter_init(&noiseFilt, BandpassPeak, 1500.0f, 1.5f, &leaf);
				tVZFilter_init(&noiseFilt2, Lowpass, 800.0f, 0.9f, &leaf);
				//tVZFilter_setFreq(&noiseFilt2, 3332.0f); //based on testing with knob values


				tVZFilter_setFreq(&noiseFilt, faster_mtof(0.9f * 128.0f));
				tVZFilter_setFreq(&noiseFilt2,faster_mtof(0.8f * 128.0f));

				tNoise_init(&myNoise, WhiteNoise, &leaf);

			}
		for (int i = 0; i < AUDIO_BUFFER_SIZE; i++)
		{

				audioOutBuffer[ i] = (int32_t)(0.0f * TWO_TO_23);
		}
		audioFrameFunction = audioFrameWaiting;
		HAL_Delay(1);
}

void audioStart(SAI_HandleTypeDef* hsaiOut, SAI_HandleTypeDef* hsaiIn)
{
	// set up the I2S driver to send audio data to the codec (and retrieve input as well)
	HAL_Delay(1);
	transmit_status = HAL_SAI_Transmit_DMA(hsaiOut, (uint8_t *)&audioOutBuffer[0], AUDIO_BUFFER_SIZE);
	receive_status = HAL_SAI_Receive_DMA(hsaiIn, (uint8_t *)&audioInBuffer[0], AUDIO_BUFFER_SIZE);
	//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
}

uint32_t timeMIDI = 0;
uint32_t timeSPI = 0;

void __ATTR_ITCMRAM updateStateFromSPIMessage(uint8_t offset)
{
	uint32_t tempCountSPI = DWT->CYCCNT;
	int modeBit = SPI_RX[24 + offset];

	octaveAction = (modeBit >> 6) & 1;
	dualSlider = (modeBit >> 5) & 1;

	edit = (modeBit >> 4) & 1;
	voice = SPI_RX[25 + offset];


	//octave = (((int32_t) (modeBit & 15) - 5 ) * 12.0f);
	//if "octave action" is set to 1, then immediately change octave instead of waiting for new note
	if (octaveAction)
	{
		for (int i = 0; i < numStringsThisBoard; i++)
		{
			stringOctave[i] = octave;
		}
	}

	volumePedalInt = ((uint16_t)SPI_RX[26 + offset] << 8) + ((uint16_t)SPI_RX[27 + offset] & 0xff);
	volumePedal = volumePedalInt * 0.0002442002442f;


	tExpSmooth_setDest(&volumeSmoother,volumePedal);
	timeSPI = DWT->CYCCNT - tempCountSPI;
}

void voiceChangeCheck(void)
{
	if (voice != prevVoice)
	{
		if (voice == 63)
		{
			audioFrameFunction = audioFrameWaiting;
			audioSwitchToString1();
			currentActivePreset = voice;
			resetStringInputs = 1;
			diskBusy = 0;
			whichModel = 1;
		}
		else if (voice == 62)
		{
			audioFrameFunction = audioFrameWaiting;
			audioSwitchToString2();
			currentActivePreset = voice;
			resetStringInputs = 1;
			diskBusy = 0;
			whichModel = 2;
		}
		else if (voice == 61)
		{
			audioFrameFunction = audioFrameAdditive;
			audioSwitchToAdditive();
			currentActivePreset = voice;
			diskBusy = 0;
			presetReady = 1;
			resetStringInputs = 1;
			whichModel = 3;
		}
		else if (voice == 60)
		{
			audioFrameFunction = audioFrameVocal;
			audioSwitchToVocal();
			currentActivePreset = voice;
			diskBusy = 0;
			presetReady = 1;
			resetStringInputs = 1;
			whichModel = 4;
		}
		else if (voice == 59)
		{
			audioFrameFunction = audioFrameString3;
			audioSwitchToString3();
			currentActivePreset = voice;
			diskBusy = 0;
			presetReady = 1;
			resetStringInputs = 1;
			whichModel = 5;
		}
		else
		{
			audioFrameFunction = audioFrameWaiting;
			presetWaitingToLoad = 1;
			presetNumberToLoad = voice;
			presetReady = 0;
			if (prevVoice > 58)
			{
				resetStringInputs = 1;
			}
			frameLoadOverCount = 0;
			whichModel = 0;
		}
		for (int i = 0; i < AUDIO_BUFFER_SIZE; i+=2)
		{
			audioOutBuffer[i] = 0;
			audioOutBuffer[i + 1] = 0;
		}
	}

	prevVoice = voice;
}

float noteIn = 64.0f;
float bendIn = 0.0f;

void __ATTR_ITCMRAM sendNoteOn(uint8_t note, uint8_t velocity)
{
	float fvelocity = 0.0f;
	if (velocity > 0)
	{
		tSimplePoly_noteOn(&myPoly, note, velocity);
		fvelocity = (float)velocity;
		fvelocity = ((0.007685533519034f*fvelocity) + 0.0239372430f);
		fvelocity = fvelocity * fvelocity;
		stringInputs[0] = fvelocity*65535.0f;
		noteIn = note;
		stringMidiPitchesNoBend = noteIn;
		stringMIDIPitches[0] = noteIn + bendIn;
	}
	else
	{
		tSimplePoly_noteOff(&myPoly, note);
		noteIn = note;
		stringMidiPitchesNoBend = noteIn;
		stringInputs[0] = 0;
	}
	newPluck = 1;
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

	bendIn = bendInt * bendRangeMultiplier; //by default, divide by (16383 / 96 semitones)
	stringMIDIPitches[0] = noteIn + bendIn;
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

	if ((!diskBusy)&& (presetReady))
	{
		audioFrameFunction(HALF_BUFFER_SIZE);
	}

	voiceChangeCheck();
	uint32_t tempCountClean = DWT->CYCCNT;
	SCB_CleanInvalidateDCache_by_Addr((uint32_t*)(((uint32_t)audioOutBuffer) & ~(uint32_t)0x1F), AUDIO_BUFFER_SIZE+32);
	timeClean = DWT->CYCCNT - tempCountClean;
}

void __ATTR_ITCMRAM HAL_SAI_TxHalfCpltCallback(SAI_HandleTypeDef *hsai)
{
	//SCB_CleanInvalidateDCache_by_Addr((uint32_t*)(((uint32_t)audioOutBuffer) & ~(uint32_t)0x1F), AUDIO_BUFFER_SIZE+32);
	if ((!diskBusy)&& (presetReady))
	{
		audioFrameFunction(0);
	}
	voiceChangeCheck();
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

