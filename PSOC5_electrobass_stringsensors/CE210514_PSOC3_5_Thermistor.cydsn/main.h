#include <device.h>
#include <stdio.h>
#include <math.h>

#define MAX_NUM_PRESETS 20
#define MAX_NUM_TUNINGS 20

extern volatile uint8_t I2Cbuff1[256];
uint8 I2C_MasterWriteBlocking(uint8 i2CAddr, uint16 nbytes, uint8_t mode);
extern int currentPresetSelection;
extern int currentTuningSelection;
extern uint8_t presetNamesArray[MAX_NUM_PRESETS][14];