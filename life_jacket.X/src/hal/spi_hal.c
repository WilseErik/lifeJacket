// =============================================================================
// Include statements
// =============================================================================

#include "hal/spi_hal.h"

#include <stdint.h>
#include <stdbool.h>

#include <xc.h>

#include "hal/gpio.h"
#include "hal/clock.h"

#include "uart/debug_log.h"

// =============================================================================
// Private type definitions
// =============================================================================

// =============================================================================
// Global variables
// =============================================================================

// =============================================================================
// Private constants
// =============================================================================

// LIS2HH12 max clock freq is 10Mhz, run at 1 MHz
#define LIS2HH12_TARGET_FREQ (1000000ull)
static uint16_t LIS2HH12_BRG = 
	CLOCK_HAL_PCBCLOCK_FREQ / (2 * LIS2HH12_TARGET_FREQ) - 1;

// RFM95W max clock freq is 10Mhz, run at 1 MHz
#define RFM95W_TARGET_FREQ (1000000ull)
static uint16_t RFM95W_BRG = 
    CLOCK_HAL_PCBCLOCK_FREQ / (2 * RFM95W_TARGET_FREQ) - 1;

// PCM1770 max clock freq is 16Mhz, run at 1 MHz
#define PCM1770_TARGET_FREQ (1000000ull)
static uint16_t PCM1770_BRG = 
    CLOCK_HAL_PCBCLOCK_FREQ / (2 * PCM1770_TARGET_FREQ) - 1;

// MX25R6435F max clock freq is 8Mhz of reads, run at 4 MHz
#define MX25R6435F_TARGET_FREQ (4000000ull)
static uint16_t MX25R6435F_BRG = 
    CLOCK_HAL_PCBCLOCK_FREQ / (2 * MX25R6435F_TARGET_FREQ) - 1;
// =============================================================================
// Private variables
// =============================================================================

static spi_hal_device_t current_device = SPI_DEVICE_NULL;

// =============================================================================
// Private function declarations
// =============================================================================

static void spi_hal_setup_for_lis2hh12(void);
static void spi_hal_setup_for_rfm95w(void);
static void spi_hal_setup_for_pcm1770(void);
static void spi_hal_setup_for_mx25r6435f(void);

static void spi_hal_cs_on(void);
static void spi_hal_cs_off(void);
static void spi_hal_all_cs_off(void);

// =============================================================================
// Public function definitions
// =============================================================================

void spi_hal_setup_for_device(spi_hal_device_t device)
{
    if (current_device != device)
    {
        current_device = device;

        spi_hal_all_cs_off();

        switch (device)
        {
        case SPI_DEVICE_RFM95W:
            spi_hal_setup_for_rfm95w();
            break;

        case SPI_DEVICE_LIS2HH12:
            spi_hal_setup_for_lis2hh12();
            break;

        case SPI_DEVICE_PCM1770:
            spi_hal_setup_for_pcm1770();
            break;

        case SPI_DEVICE_EXT_FLASH:
            spi_hal_setup_for_mx25r6435f();
            break;

        default:
            break;

        }
    }
}

uint16_t spi_hal_tranceive16(uint16_t v)
{
	uint16_t read_value = 0;

	spi_hal_cs_on();

    SPI1BUFH = 0;
	SPI1BUFL = v;

	while (SPI1STATLbits.SPIRBE) {;}

    read_value = SPI1BUFH;
	read_value = SPI1BUFL;

	spi_hal_cs_off();

	return read_value;
}

uint8_t spi_hal_tranceive8(uint8_t v)
{
    uint8_t read_value = 0;

    SPI1BUFH = 0;
    SPI1BUFL = v;

    while (SPI1STATLbits.SPIRBE) {;}

    read_value = SPI1BUFH;
    read_value = SPI1BUFL;

    return read_value;
}

// =============================================================================
// Private function definitions
// =============================================================================

static void spi_hal_setup_for_lis2hh12(void)
{
	SPI1IMSKL = 0; 				// No interrupts
	SPI1IMSKH = 0;				// No interrupts
	
	SPI1CON1Lbits.SPIEN = 0;	// Turn of and reset the module

	SPI1CON1L = 0;
	SPI1CON1H = 0;

	SPI1CON1Lbits.MODE32 = 0;	// 16 bit mode
	SPI1CON1Lbits.MODE16 = 1;	// 16 bit mode
	SPI1CON1Lbits.CKP = 1; 		// Clock idle high
	SPI1CON1Lbits.CKE = 0; 		// Transmit at idle to active clk transition
	SPI1CON1Lbits.MSTEN = 1;	// Master mode
	SPI1CON1Lbits.ENHBUF = 1;	// Use enhanced buffer mode

	SPI1CON2L = 0;				// 16 bit mode
	SPI1STATL = 0; 				// Clear any errors

	SPI1BRGL = LIS2HH12_BRG;

	ACC_CS_OFF;
	SPI1CON1Lbits.SPIEN = 1;
}

static void spi_hal_setup_for_rfm95w(void)
{
    SPI1IMSKL = 0;              // No interrupts
    SPI1IMSKH = 0;              // No interrupts
    
    SPI1CON1Lbits.SPIEN = 0;    // Turn of and reset the module

    SPI1CON1L = 0;
    SPI1CON1H = 0;

    SPI1CON1Lbits.MODE32 = 0;   // 16 bit mode
    SPI1CON1Lbits.MODE16 = 1;   // 16 bit mode
    SPI1CON1Lbits.CKP = 0;      // Clock idle low
    SPI1CON1Lbits.CKE = 1;      // Transmit at active to idle clk transition
    SPI1CON1Lbits.MSTEN = 1;    // Master mode
    SPI1CON1Lbits.ENHBUF = 1;   // Use enhanced buffer mode

    SPI1CON2L = 0;              // 16 bit mode
    SPI1STATL = 0;              // Clear any errors

    SPI1BRGL = RFM95W_BRG;

    LORA_CS_OFF;
    SPI1CON1Lbits.SPIEN = 1;
}

static void spi_hal_setup_for_pcm1770(void)
{
    SPI1IMSKL = 0;              // No interrupts
    SPI1IMSKH = 0;              // No interrupts
    
    SPI1CON1Lbits.SPIEN = 0;    // Turn of and reset the module

    SPI1CON1L = 0;
    SPI1CON1H = 0;

    SPI1CON1Lbits.MODE32 = 0;   // 16 bit mode
    SPI1CON1Lbits.MODE16 = 1;   // 16 bit mode
    SPI1CON1Lbits.CKP = 1;      // Clock idle high
    SPI1CON1Lbits.CKE = 0;      // Transmit at idle to active clk transition
    SPI1CON1Lbits.MSTEN = 1;    // Master mode
    SPI1CON1Lbits.ENHBUF = 1;   // Use enhanced buffer mode

    SPI1CON2L = 0;              // 16 bit mode
    SPI1STATL = 0;              // Clear any errors

    SPI1BRGL = PCM1770_BRG;

    PCM1770_CS_OFF;
    SPI1CON1Lbits.SPIEN = 1;
}

/*
     CS     ‾‾‾‾‾__________


     SCLK   ___‾‾__‾‾__‾‾__
     SI           DD  DD            (MSB first)
     SO    ______<DD><DD><D  

     Data sampled on rising edge
     Clock idle low
*/
static void spi_hal_setup_for_mx25r6435f(void)
{
    SPI1IMSKL = 0;              // No interrupts
    SPI1IMSKH = 0;              // No interrupts
    
    SPI1CON1Lbits.SPIEN = 0;    // Turn of and reset the module

    SPI1CON1L = 0;
    SPI1CON1H = 0;

    SPI1CON1Lbits.MODE32 = 0;   // 8 bit mode
    SPI1CON1Lbits.MODE16 = 0;   // 8 bit mode
    SPI1CON1Lbits.CKP = 0;      // Clock idle low
    SPI1CON1Lbits.CKE = 1;      // Transmit at active to idle clk transition
    SPI1CON1Lbits.MSTEN = 1;    // Master mode
    SPI1CON1Lbits.ENHBUF = 1;   // Use enhanced buffer mode

    SPI1CON2L = 0;              // 16 bit mode
    SPI1STATL = 0;              // Clear any errors

    SPI1BRGL = MX25R6435F_BRG;

    FLASH_CS_OFF;
    SPI1CON1Lbits.SPIEN = 1;
}

static void spi_hal_cs_on(void)
{
	switch (current_device)
	{
	case SPI_DEVICE_NULL:
		break;

    case SPI_DEVICE_RFM95W:
    	LORA_CS_ON;
    	break;

    case SPI_DEVICE_LIS2HH12:
    	ACC_CS_ON;
    	break;

    case SPI_DEVICE_PCM1770:
    	PCM1770_CS_ON;
    	break;

    case SPI_DEVICE_EXT_FLASH:
    	FLASH_CS_ON;
    	break;
    }
}

static void spi_hal_cs_off(void)
{
	switch (current_device)
	{
	case SPI_DEVICE_NULL:
		break;

    case SPI_DEVICE_RFM95W:
    	LORA_CS_OFF;
    	break;

    case SPI_DEVICE_LIS2HH12:
    	ACC_CS_OFF;
    	break;

    case SPI_DEVICE_PCM1770:
    	PCM1770_CS_OFF;
    	break;

    case SPI_DEVICE_EXT_FLASH:
    	FLASH_CS_OFF;
    	break;
    }
}

static void spi_hal_all_cs_off(void)
{
	LORA_CS_OFF;
	ACC_CS_OFF;
	PCM1770_CS_OFF;
	FLASH_CS_OFF;
}
