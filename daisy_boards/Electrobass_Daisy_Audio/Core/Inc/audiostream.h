/**
  ******************************************************************************
  * @file    Audio_playback_and_record/inc/waveplayer.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Header for waveplayer.c module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AUDIOSTREAM_H
#define __AUDIOSTREAM_H

/* Includes ------------------------------------------------------------------*/
#include "parameters.h"
#include "leaf.h"
#include "main.h"
#include "memory.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  BUFFER_OFFSET_NONE = 0,
  BUFFER_OFFSET_HALF,
  BUFFER_OFFSET_FULL,
}BUFFER_StateTypeDef;


//#define SAMPLERATE96K
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



typedef enum BOOL {
	FALSE = 0,
	TRUE
} BOOL;



void audioInit(void);
void audioStart(SAI_HandleTypeDef* hsaiOut, SAI_HandleTypeDef* hsaiIn);

void initFunctionPointers(void);

typedef struct cStack {
    uint8_t buffer[64][3];
    int8_t writeCnt;
    int8_t readCnt;
    int8_t size;
} cStack;

void cStack_init(cStack* stack);
int cStack_size(cStack* stack);
void cStack_push(cStack* stack, uint8_t val, uint8_t val1, uint8_t val2);
void cStack_pop(cStack* stack, uint8_t* output);

extern cStack midiStack;
extern float fractionalMidi[128];

void audioFrame(uint16_t buffer_offset);
void DMA1_TransferCpltCallback(DMA_HandleTypeDef *hdma);
void DMA1_HalfTransferCpltCallback(DMA_HandleTypeDef *hdma);
void updateStateFromSPIMessage(uint8_t currentByte);

float mtofTableLookup(float tempMIDI);

float dbToATableLookup(float in);

void  audioFrameWaiting(uint16_t buffer_offset);


typedef struct _instrumentState {
	float MIDINote;
	float amplitude;
	float controls[4];
};

#endif /* INC_AUDIOSTREAM_H_ */
