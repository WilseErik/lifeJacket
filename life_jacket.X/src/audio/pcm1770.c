// =============================================================================
// Include statements
// =============================================================================

#include "audio/pcm1770.h"

#include <stdint.h>
#include <stdbool.h>

#include <xc.h>

#include "hal/gpio.h"
#include "hal/spi_hal.h"
#include "hal/clock.h"

// =============================================================================
// Private type definitions
// =============================================================================

// =============================================================================
// Global variables
// =============================================================================

// =============================================================================
// Private constants
// =============================================================================

#define PCM1770_HIGHEST_REGISTER_ADDR (4)

#define I2S_BITS_PER_FRAME (32)
#define I2S_TARGET_SAMPLING_FREQ (31250ull)
#define I2S_TARGET_FREQ (I2S_TARGET_SAMPLING_FREQ * I2S_BITS_PER_FRAME)
static uint16_t I2S_BRG = 
    CLOCK_HAL_PCBCLOCK_FREQ / (2 * I2S_TARGET_FREQ) - 1;

// =============================================================================
// Private variables
// =============================================================================
static uint8_t shadow_registers[PCM1770_HIGHEST_REGISTER_ADDR + 1];

// =============================================================================
// Private function declarations
// =============================================================================

static void pcm1770_i2s_init(void);
static void pcm1770_i2s_deinit(void);

// =============================================================================
// Public function definitions
// =============================================================================

void pcm1770_init(void)
{
    PCM1770_N_PD_PIN = 1;

    shadow_registers[1] = 0x3F;
    shadow_registers[2] = 0x3F;
    shadow_registers[3] = 0x80;
    shadow_registers[4] = 0x00;

    pcm1770_write_register(1, shadow_registers[1]);
    pcm1770_write_register(2, shadow_registers[2]);
    pcm1770_write_register(3, shadow_registers[3]);
    pcm1770_write_register(4, shadow_registers[4]);

    pcm1770_i2s_init();
}

void pcm1770_deinit(void)
{
    PCM1770_N_PD_PIN = 0;

    pcm1770_i2s_deinit();
}

void pcm1770_write_register(uint8_t address, uint8_t value)
{
    uint16_t value_to_write = (((uint16_t)address) << 8) & 0x8000;
    value_to_write |= value;

    spi_hal_setup_for_device(SPI_DEVICE_PCM1770);
    spi_hal_tranceive16(value_to_write);

    shadow_registers[address] = value;
}

void pcm1770_power_up(void)
{
    pcm1770_write_register(4, shadow_registers[4] | 0x01);
}

void pcm1770_power_down(void)
{
    pcm1770_write_register(4, shadow_registers[4] & 0xFE);
}

// =============================================================================
// Private function definitions
// =============================================================================

static void pcm1770_i2s_init(void)
{
    //
    // Set up the I2S module for 16 bit, right-justified data.
    //
    SPI2IMSKL = 0;              // No interrupts
    SPI2IMSKH = 0;              // No interrupts

    SPI2CON1Lbits.SPIEN = 0;    // Turn of and reset the module

    SPI2CON1L = 0;
    SPI2CON1H = 0;

    SPI2STATL = 0;              // Clear any errors

    SPI2IMSKLbits.SPITBEN = 1;  // SPIx transmit buffer empty generates an interrupt event
    SPI2IMSKLbits.SPIRBFEN = 1;

    SPI2CON1Hbits.AUDMOD = 0;    // I2S mode
    SPI2CON1Hbits.AUDEN = 1;
    SPI2CON1Hbits.AUDMONO = 1;   // Audio data is mono
    SPI2CON1Hbits.IGNTUR = 1;    // Ignore tx underrun

    SPI2BRGL = I2S_BRG;
    SPI2STATLbits.SPIROV = 0;

    SPI2CON1Lbits.MSTEN = 1;    // Master mode
    SPI2CON1Lbits.CKP = 1;
    SPI2CON1Lbits.MODE32 = 0;
    SPI2CON1Lbits.MODE16 = 0;
    SPI2CON1Lbits.ENHBUF = 0;   // Not enhanched buffer mode
    SPI2CON1Lbits.DISSDI = 1;   // Do not use the MISO pin

    SPI2CON1Lbits.SPIEN = 1;
}

static void pcm1770_i2s_deinit(void)
{
    //
    // Set up the I2S module for 16 bit, right-justified data.
    //
    SPI2IMSKL = 0;              // No interrupts
    SPI2IMSKH = 0;              // No interrupts

    SPI2CON1Lbits.SPIEN = 0;    // Turn of and reset the module

    SPI2CON1L = 0;
    SPI2CON1H = 0;

    SPI2STATL = 0;              // Clear any errors
}