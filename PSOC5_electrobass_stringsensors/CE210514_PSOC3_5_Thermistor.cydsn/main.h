#include <device.h>
#include <stdio.h>
#include <math.h>

extern volatile uint8_t I2Cbuff1[256];
uint8 I2C_MasterWriteBlocking(uint8 i2CAddr, uint16 nbytes, uint8_t mode);
