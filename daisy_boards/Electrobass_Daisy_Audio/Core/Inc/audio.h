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

void audio_init(SAI_HandleTypeDef* hsaiOut, SAI_HandleTypeDef* hsaiIn);
void audioFrame(uint16_t buffer_offset);
float audioTickL(float audioIn);
float audioTickR(float audioIn);

void DMA1_TransferCpltCallback(DMA_HandleTypeDef *hdma);
void DMA1_HalfTransferCpltCallback(DMA_HandleTypeDef *hdma);

extern void sendNoteOn(uint8_t note, uint8_t velocity);
extern void sendCtrl(uint8_t value, uint8_t ctrl);
extern void sendPitchBend(uint8_t value, uint8_t ctrl);

/****************** Audio Params **********************/
extern float oscAmp[3];

extern float filtCutoff[2];
extern float follow[2];

#endif /* INC_AUDIO_H_ */
