#include <device.h>
#include <stdio.h>
#include <math.h>

#define MAX_NUM_PRESETS 64
#define PRESET_NAME_LENGTH_IN_BYTES 14


#define PRESET_NAME_CLIPPED_LENGTH 12
#define COPEDENT_NAME_CLIPPED_LENGTH 10
#define MACRO_NAME_CLIPPED_LENGTH 9
#define CONTROL_NAME_CLIPPED_LENGTH 10

#define NUM_MACRO_PAGES 2
#define NUM_MACROS 8
#define NUM_CONTROLS 4
#define MACRO_NAME_LENGTH_IN_BYTES 9
#define CONTROL_NAME_LENGTH_IN_BYTES 10

extern uint8_t macroNamesArray[MAX_NUM_PRESETS][NUM_MACROS*NUM_MACRO_PAGES][MACRO_NAME_LENGTH_IN_BYTES];
extern uint8_t controlNamesArray[MAX_NUM_PRESETS][NUM_CONTROLS][CONTROL_NAME_LENGTH_IN_BYTES];

extern uint8_t presetAlreadyDisplayed[MAX_NUM_PRESETS];
extern volatile uint8_t I2Cbuff1[256];
uint8 I2C_MasterWriteBlocking(uint8 i2CAddr, uint16 nbytes, uint8_t mode);
extern int currentPresetSelection;
extern uint8_t presetNamesArray[MAX_NUM_PRESETS][14];