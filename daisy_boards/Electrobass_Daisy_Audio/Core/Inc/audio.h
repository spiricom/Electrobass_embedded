/*
 * audio.h
 *
 *  Created on: Jul 6, 2022
 *      Author: jeffsnyder
 */

#ifndef INC_AUDIO_H_
#define INC_AUDIO_H_


#include "leaf.h"
#include "main.h"


#define AUDIO_FRAME_SIZE      32
#define HALF_BUFFER_SIZE      AUDIO_FRAME_SIZE * 2 //number of samples per half of the "double-buffer" (twice the audio frame size because there are interleaved samples for both left and right channels)
#define AUDIO_BUFFER_SIZE     AUDIO_FRAME_SIZE * 4 //number of samples in the whole data structure (four times the audio frame size because of stereo and also double-buffering/ping-ponging)

#ifdef SAMPLERATE96K
#define SAMPLE_RATE 96000.f
#else
#define SAMPLE_RATE 48000.f
#endif


#define INV_SAMPLE_RATE 1.f/SAMPLE_RATE
#define SAMPLE_RATE_MS (SAMPLE_RATE / 1000.f)
#define INV_SR_MS 1.f/SAMPLE_RATE_MS
#define SAMPLE_RATE_DIV_PARAMS SAMPLE_RATE / 3
#define SAMPLE_RATE_DIV_PARAMS_MS (SAMPLE_RATE_DIV_PARAMS / 1000.f)
#define INV_SR_DIV_PARAMS_MS 1.f/SAMPLE_RATE_DIV_PARAMS_MS


typedef enum
{
  BUFFER_OFFSET_NONE = 0,
  BUFFER_OFFSET_HALF,
  BUFFER_OFFSET_FULL,
}BUFFER_StateTypeDef;


extern int32_t audioOutBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2;
void audio_init(void);
void audio_start(SAI_HandleTypeDef* hsaiOut, SAI_HandleTypeDef* hsaiIn);
void audioFrame(uint16_t buffer_offset);
float audioTickL(float audioIn);
float audioTickR(float audioIn);

void DMA1_TransferCpltCallback(DMA_HandleTypeDef *hdma);
void DMA1_HalfTransferCpltCallback(DMA_HandleTypeDef *hdma);

extern void storeNoteOn(uint8_t note, uint8_t velocity);
extern void storeCtrl(uint8_t value, uint8_t ctrl);
extern void storePitchBend(uint8_t value, uint8_t ctrl);

void sendNoteOn(uint8_t note, uint8_t velocity);
void sendCtrl(uint8_t value, uint8_t ctrl);
void sendPitchBend(uint8_t value, uint8_t ctrl);
/****************** Audio Params **********************/

#define NUM_OSC 3
#define INV_NUM_OSCS 0.333333333f
#define NUM_FILT 2
#define NUM_ENV 4
#define NUM_SOURCES 33
#define EXP_BUFFER_SIZE 2048
#define DECAY_EXP_BUFFER_SIZE 4096
#define OSC_SOURCE_OFFSET 0
#define CTRL_SOURCE_OFFSET 20
#define ENV_SOURCE_OFFSET 25


#define CTRL_MIDI_START 17


void setTranspose(float in, int v);
void setPitchBendRangeUp(float in, int v);
void setPitchBendRangeDown(float in, int v);
void setNoiseAmp(float in, int v);

void oscillator_tick(float note);

typedef void (*shapeTick_t)(float*, int, float, float);

void sawSquareTick(float* sample, int v, float freq, float shape);
void sineTriTick(float* sample, int v, float freq, float shape);
void sawTick(float* sample, int v, float freq, float shape);
void pulseTick(float* sample, int v, float freq, float shape);
void sineTick(float* sample, int v, float freq, float shape);
void triTick(float* sample, int v, float freq, float shape);
void userTick(float* sample, int v, float freq, float shape);

extern shapeTick_t shapeTick[NUM_OSC];


float filter_tick(float* samples, float note);

typedef void (*filterTick_t)(float*, int, float);
void setFreqMult(float harm_pitch, int osc);
void lowpassTick(float* sample, int v, float cutoff);
void highpassTick(float* sample, int v, float cutoff);
void bandpassTick(float* sample, int v, float cutoff);
void diodeLowpassTick(float* sample, int v, float cutoff);
void LadderLowpassTick(float* sample, int v, float cutoff);
void VZlowshelfTick(float* sample, int v, float cutoff);
void VZhighshelfTick(float* sample, int v, float cutoff);
void VZpeakTick(float* sample, int v, float cutoff);
void VZbandrejectTick(float* sample, int v, float cutoff);

void filterSetCutoff(float cutoff, int v);
void filterSetKeyfollow(float keyfollow, int v);
void lowpassSetQ(float q, int v);
void highpassSetQ(float q, int v);
void bandpassSetQ(float q, int v);
void diodeLowpassSetQ(float q, int v);
void VZpeakSetQ(float bw, int v);
void VZlowshelfSetQ(float bw, int v);
void VZhighshelfSetQ(float bw, int v);
void VZbandrejectSetQ(float bw, int v);
void LadderLowpassSetQ(float q, int v);
void lowpassSetGain(float gain, int v);
void highpassSetGain(float gain, int v);
void bandpassSetGain(float gain, int v);
void diodeLowpassSetGain(float gain, int v);
void VZpeakSetGain(float gain, int v);
void VZlowshelfSetGain(float gain, int v);
void VZhighshelfSetGain(float gain, int v);
void VZbandrejectSetGain(float gain, int v);
void LadderLowpassSetGain(float gain, int v);
extern filterTick_t filterTick[NUM_FILT];

//envelope functions
void setEnvelopeAttack(float a, int v);
void setEnvelopeDecay(float d, int v);
void setEnvelopeSustain(float s, int v);
void setEnvelopeRelease(float r, int v);
void setEnvelopeLeak(float leak, int v);

//master functions
void setAmp(float amp, int v);
void setMaster(float amp, int v);



extern float sourceValues[NUM_SOURCES];

#endif /* INC_AUDIO_H_ */
