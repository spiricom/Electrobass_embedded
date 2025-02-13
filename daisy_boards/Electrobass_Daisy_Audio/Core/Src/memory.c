/*
 * memory.c
 *
 *  Created on: Feb 13, 2025
 *      Author: jeffsnyder
 */

#include "memory.h"
//the audio buffers are put in the D2 RAM area because that is a memory location that the DMA has access to.
int32_t audioOutBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2_DMA;
int32_t audioInBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2_DMA;

uint8_t SPI_TX[SPI_BUFFER_SIZE] __ATTR_RAM_D2_DMA;
uint8_t SPI_RX[SPI_BUFFER_SIZE] __ATTR_RAM_D2_DMA;

char small_memory[SMALL_MEM_SIZE];
char medium_memory[MED_MEM_SIZE] __ATTR_RAM_D1;
char large_memory[LARGE_MEM_SIZE] __ATTR_SDRAM;
tMempool mediumPool;
tMempool largePool;

float mtofTable[MTOF_TABLE_SIZE]__ATTR_RAM_D2;
float atoDbTable[ATODB_TABLE_SIZE]__ATTR_RAM_D2;
float dbtoATable[DBTOA_TABLE_SIZE]__ATTR_RAM_D2;

float decayExpBuffer[DECAY_EXP_BUFFER_SIZE];


volatile uint8_t presetNamesArray[MAX_NUM_PRESETS][14]__ATTR_RAM_D2;
volatile uint8_t macroNamesArray[MAX_NUM_PRESETS][20][10]__ATTR_RAM_D2;

#define SCALE_TABLE_SIZE 2048
float resTable[SCALE_TABLE_SIZE];
float envTimeTable[SCALE_TABLE_SIZE];
float lfoRateTable[SCALE_TABLE_SIZE];
