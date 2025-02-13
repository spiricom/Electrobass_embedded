/*
 * memory.h
 *
 *  Created on: Feb 13, 2025
 *      Author: jeffsnyder
 */


#ifndef SRC_MEMORY_H_
#define SRC_MEMORY_H_

#include "leaf.h"



#define __ATTR_RAM_D1	__attribute__ ((section(".sram1_bss"))) __attribute__ ((aligned (32)))
#define __ATTR_RAM_D2_DMA	__attribute__ ((section(".sram2_dma_bss"))) __attribute__ ((aligned (32)))
#define __ATTR_RAM_D2	__attribute__ ((section(".sram2_bss"))) __attribute__ ((aligned (32)))
#define __ATTR_RAM_D3	__attribute__ ((section(".sram3_bss"))) __attribute__ ((aligned (32)))
#define __ATTR_USER_FLASH	__attribute__ ((section(".userflash"))) __attribute__ ((aligned (32)))
#define __ATTR_SDRAM	__attribute__ ((section(".sdram_bss"))) __attribute__ ((aligned (32)))
#define __ATTR_ITCMRAM	__attribute__ ((section(".itcmram"))) __attribute__ ((aligned (32)))


#define MAX_NUM_PRESETS 64

#define SPI_BUFFER_SIZE 64
#define SPI_FRAME_SIZE 32
#define AUDIO_FRAME_SIZE      64
#define HALF_BUFFER_SIZE      AUDIO_FRAME_SIZE * 2 //number of samples per half of the "double-buffer" (twice the audio frame size because there are interleaved samples for both left and right channels)
#define AUDIO_BUFFER_SIZE     AUDIO_FRAME_SIZE * 4 //number of samples in the whole data structure (four times the audio frame size because of stereo and also double-buffering/ping-ponging)
#define SMALL_MEM_SIZE 60000
#define MED_MEM_SIZE 262144//180000
#define LARGE_MEM_SIZE 31457280//67108864 would be 64 MBytes - size of SDRAM IC, but we are using 2MB each for firmware buffers = 2097152*2 =   4194304, so 67108864-4194304=62914560
#define MTOF_TABLE_SIZE	32768
#define MTOF_TABLE_SIZE_MINUS_ONE 32767
#define MTOF_TABLE_SIZE_DIV_TWO	16384
#define ATODB_TABLE_SIZE 16384
#define DBTOA_TABLE_SIZE 16384
#define ATODB_TABLE_SIZE_MINUS_ONE 16383
#define DBTOA_TABLE_SIZE_MINUS_ONE 16383
#define EXP_BUFFER_SIZE 2048
#define DECAY_EXP_BUFFER_SIZE 4096
#define DECAY_EXP_BUFFER_SIZE_MINUS_ONE 4095

#define SCALE_TABLE_SIZE 2048


extern int32_t audioOutBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2_DMA;
extern int32_t audioInBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2_DMA;
extern uint8_t SPI_RX[SPI_BUFFER_SIZE] __ATTR_RAM_D2_DMA;
extern uint8_t SPI_TX[SPI_BUFFER_SIZE] __ATTR_RAM_D2_DMA;


extern char small_memory[SMALL_MEM_SIZE];
extern char medium_memory[MED_MEM_SIZE] __ATTR_RAM_D1;
extern char large_memory[LARGE_MEM_SIZE] __ATTR_SDRAM;
extern tMempool mediumPool;
extern tMempool largePool;

extern float mtofTable[MTOF_TABLE_SIZE]__ATTR_RAM_D2;
extern float atoDbTable[ATODB_TABLE_SIZE]__ATTR_RAM_D2;
extern float dbtoATable[DBTOA_TABLE_SIZE]__ATTR_RAM_D2;
extern float decayExpBuffer[DECAY_EXP_BUFFER_SIZE];

extern volatile uint8_t presetNamesArray[MAX_NUM_PRESETS][14]__ATTR_RAM_D2;
extern volatile uint8_t macroNamesArray[MAX_NUM_PRESETS][20][10]__ATTR_RAM_D2;

#endif /* SRC_MEMORY_H_ */
