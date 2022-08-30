/*
 * codec.c
 *
 *  Created on: Jul 6, 2022
 *      Author: jeffsnyder
 */
#include "main.h"
#include "codec.h"

#define W8731_ADDR_0 0x1A
#define W8731_ADDR_1 0x1B
#define W8731_NUM_REGS 10
#define CODEC_ADDRESS (W8731_ADDR_0 << 1)

enum CodecRegister
{
    CODEC_REG_LEFT_LINE_IN         = 0x00,
    CODEC_REG_RIGHT_LINE_IN        = 0x01,
    CODEC_REG_LEFT_HEADPHONES_OUT  = 0x02,
    CODEC_REG_RIGHT_HEADPHONES_OUT = 0x03,
    CODEC_REG_ANALOGUE_ROUTING     = 0x04,
    CODEC_REG_DIGITAL_ROUTING      = 0x05,
    CODEC_REG_POWER_MANAGEMENT     = 0x06,
    CODEC_REG_DIGITAL_FORMAT       = 0x07,
    CODEC_REG_SAMPLE_RATE          = 0x08,
    CODEC_REG_ACTIVE               = 0x09,
    CODEC_REG_RESET                = 0x0f,
};

enum CodecAnalogSettings
{
    CODEC_ANALOG_MICBOOST  = 0x01,
    CODEC_ANALOG_MUTEMIC   = 0x02,
    CODEC_ANALOG_INSEL     = 0x04,
    CODEC_ANALOG_BYPASS    = 0x08,
    CODEC_ANALOG_DACSEL    = 0x10,
    CODEC_ANALOG_SIDETONE  = 0x20,
    CODEC_ANALOG_SIDEATT_0 = 0x40,
    CODEC_ANALOG_SIDEATT_1 = 0x80,
};

enum CodecSettings
{
    CODEC_INPUT_0_DB        = 0x17,
    CODEC_INPUT_UPDATE_BOTH = 0x40,
    CODEC_HEADPHONES_MUTE   = 0x00,
    CODEC_MIC_BOOST         = 0x1,
    CODEC_MIC_MUTE          = 0x2,
    CODEC_ADC_MIC           = 0x4,
    CODEC_ADC_LINE          = 0x0,
    CODEC_OUTPUT_DAC_ENABLE = 0x10,
    CODEC_OUTPUT_MONITOR    = 0x20,
    CODEC_DEEMPHASIS_NONE   = 0x00,
    CODEC_DEEMPHASIS_32K    = 0x01,
    CODEC_DEEMPHASIS_44K    = 0x02,
    CODEC_DEEMPHASIS_48K    = 0x03,
    CODEC_SOFT_MUTE         = 0x01,
    CODEC_ADC_HPF           = 0x00,

    CODEC_POWER_DOWN_LINE_IN      = 0x01,
    CODEC_POWER_DOWN_MIC          = 0x02,
    CODEC_POWER_DOWN_ADC          = 0x04,
    CODEC_POWER_DOWN_DAC          = 0x08,
    CODEC_POWER_DOWN_LINE_OUT     = 0x10,
    CODEC_POWER_DOWN_OSCILLATOR   = 0x20,
    CODEC_POWER_DOWN_CLOCK_OUTPUT = 0x40,
    CODEC_POWER_DOWN_EVERYTHING   = 0x80,

    CODEC_PROTOCOL_MASK_MSB_FIRST = 0x00,
    CODEC_PROTOCOL_MASK_LSB_FIRST = 0x01,
    CODEC_PROTOCOL_MASK_PHILIPS   = 0x02,
    CODEC_PROTOCOL_MASK_DSP       = 0x03,

    CODEC_FORMAT_MASK_16_BIT = 0x00 << 2,
    CODEC_FORMAT_MASK_20_BIT = 0x01 << 2,
    CODEC_FORMAT_MASK_24_BIT = 0x02 << 2,
    CODEC_FORMAT_MASK_32_BIT = 0x03 << 2,

    CODEC_FORMAT_LR_SWAP      = 0x20,
    CODEC_FORMAT_MASTER       = 0x40,
    CODEC_FORMAT_SLAVE        = 0x00,
    CODEC_FORMAT_INVERT_CLOCK = 0x80,

    CODEC_RATE_48K_48K = 0x00 << 2,
    CODEC_RATE_8K_8K   = 0x03 << 2,
    CODEC_RATE_96K_96K = 0x07 << 2,
    CODEC_RATE_32K_32K = 0x06 << 2,
    CODEC_RATE_44K_44K = 0x08 << 2,
};


void codec_init(I2C_HandleTypeDef* i2c)
{
    int res;
    // Reset
    res = WriteControlRegister(i2c, CODEC_REG_RESET, 0);

    // Set Line Inputs to 0DB
    res = WriteControlRegister(i2c, CODEC_REG_LEFT_LINE_IN, CODEC_INPUT_0_DB);

    res = WriteControlRegister(i2c, CODEC_REG_RIGHT_LINE_IN, CODEC_INPUT_0_DB);

    // Set Headphone To Mute (and disable?)
    res = WriteControlRegister(i2c, CODEC_REG_LEFT_HEADPHONES_OUT,
                               CODEC_HEADPHONES_MUTE);

    res = WriteControlRegister(i2c, CODEC_REG_RIGHT_HEADPHONES_OUT,
                               CODEC_HEADPHONES_MUTE);


    // Analog and Digital Routing
    res = WriteControlRegister(i2c, CODEC_REG_ANALOGUE_ROUTING,
                               CODEC_MIC_MUTE | CODEC_ADC_LINE
                                   | CODEC_OUTPUT_DAC_ENABLE);


    res = WriteControlRegister(i2c, CODEC_REG_DIGITAL_ROUTING,
                               CODEC_DEEMPHASIS_NONE);


    // Configure power management
    uint8_t power_down_reg = CODEC_POWER_DOWN_MIC | CODEC_POWER_DOWN_CLOCK_OUTPUT;

    power_down_reg |= CODEC_POWER_DOWN_OSCILLATOR;
    res = WriteControlRegister(i2c, CODEC_REG_POWER_MANAGEMENT, power_down_reg);


    // Digital Format
    uint8_t format_byte;
    format_byte = (MSB_FIRST_LJ) | (WL_BITS_24);
    format_byte |= CODEC_FORMAT_SLAVE;
    res = WriteControlRegister(i2c, CODEC_REG_DIGITAL_FORMAT, format_byte);


    // samplerate
    // TODO: add support for other samplerates
    res = WriteControlRegister(i2c, CODEC_REG_SAMPLE_RATE, CODEC_RATE_48K_48K);


    res = WriteControlRegister(i2c, CODEC_REG_ACTIVE, 0x00);


    // Enable
    res = WriteControlRegister(i2c, CODEC_REG_ACTIVE, 0x01);

    //to avoid unused variable warning
    res = res;

}

int WriteControlRegister(I2C_HandleTypeDef* i2c, uint8_t address, uint16_t data)
{
    uint8_t byte_1  = ((address << 1) & 0xfe) | ((data >> 8) & 0x01);
    uint8_t byte_2  = data & 0xff;
    uint8_t buff[2] = {byte_1, byte_2};
    HAL_I2C_Master_Transmit(i2c, W8731_ADDR_0<<1, buff,
                                              2, 250);

    HAL_Delay(10);
    return 1;
}
