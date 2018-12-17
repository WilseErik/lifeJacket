// =============================================================================
// Include statements
// =============================================================================

#include "lora\rfm95w.h"

#include <stdint.h>
#include <stdbool.h>

#include <xc.h>

#include "lora/rfm95w_io.h"
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

static const uint8_t RFM95W_REG_INIT_TABLE[][2] =
{
    {RFM95W_REG_PA_CONFIG,      0x4F},
    {RFM95W_REG_PA_RAMP,        0x09},
    {RFM95W_REG_LNA,            0x20},
    {RFM95W_REG_IRQ_FLAGS_MASK, 0x00},
    {RFM95W_REG_IRQ_FLAGS,      0x00},
    {RFM95W_REG_MODULATION_CFG, (RFM95W_BW_125K << 4) | 0x02},

};

static const uint8_t RFM95W_SILICON_VERSION = 0x11;


/*
 Allowed frequencies:
    868.1 - SF7BW125 to SF12BW125
    868.3 - SF7BW125 to SF12BW125 and SF7BW250
    868.5 - SF7BW125 to SF12BW125
    867.1 - SF7BW125 to SF12BW125
    867.3 - SF7BW125 to SF12BW125
    867.5 - SF7BW125 to SF12BW125
    867.7 - SF7BW125 to SF12BW125
    867.9 - SF7BW125 to SF12BW125
    868.8 - FSK

 Max output power: 14 dBm
*/
static const uint8_t FREQ_WORD[] = {0xD9, 0x06, 0x66};

// =============================================================================
// Private variables
// =============================================================================

// =============================================================================
// Private function declarations
// =============================================================================

// =============================================================================
// Public function definitions
// =============================================================================

void rfm95w_init(void)
{
    if (RFM95W_SILICON_VERSION == rfm95w_io_read_single_reg(RFM95W_REG_VERSION))
    {
        debug_log_append_line("RFM95W communication ok");
    }
    else
    {
        debug_log_append_line("RFM95W communication failiure");
        return;
    }

    rfm95w_io_set_operating_mode(RFM95W_OP_MODE_SLEEP);

    // LORA mode, high frequency mode
    rfm95w_io_write_single_reg(RFM95W_REG_OP_MODE, 0x80);

    rfm95w_io_write_single_reg(RFM95W_REG_FRF_MSB, FREQ_WORD[0]);
    rfm95w_io_write_single_reg(RFM95W_REG_FRF_MID, FREQ_WORD[1]);
    rfm95w_io_write_single_reg(RFM95W_REG_FRF_LSB, FREQ_WORD[2]);
}

// =============================================================================
// Private function definitions
// =============================================================================


