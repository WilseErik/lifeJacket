// =============================================================================
// Include statements
// =============================================================================

#include "lora\rfm95w.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include <xc.h>

#include "lora/rfm95w_io.h"
#include "uart/debug_log.h"
#include "hal/uart.h"
#include "hal/gpio.h"
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

static const uint8_t RFM95W_REG_INIT_TABLE[][2] =
{
    {RFM95W_REG_PA_CONFIG,          0x4F},  // Output power = 4dBm
    {RFM95W_REG_PA_RAMP,            0x09},  // Default value (40 us)
    {RFM95W_REG_LNA,                0x20},  // Max LNA gain
    {RFM95W_REG_FIFO_ADDR_PTR,      0x00},
    {RFM95W_REG_FIFO_TX_BASE_ADDR,  0x80},
    {RFM95W_REG_FIFO_RX_BASE_ADDR,  0x00},
    {RFM95W_REG_IRQ_FLAGS_MASK,     0x00},
    {RFM95W_REG_IRQ_FLAGS,          0xFF},  // Clear by writing 1's
    {RFM95W_REG_MODEM_CONFIG1,      (RFM95W_BW_125K << 4) |
                                    (RFM95W_CODING_RATE_4_5 << 1) |
                                    RFM95W_EXPLICIT_HEADER_MODE},
    {RFM95W_REG_MODEM_CONFIG2,      (RFM95W_SPREADING_FACTOR_128_CHIPS << 4) |
                                    (RFM95W_TX_NORMAL_MODE << 3) |
                                    (RFM95W_PAYLOAD_CRC_DISABLE << 2) |
                                    (0 << 0)},  // rx time-out msb
    {RFM95W_REG_SYMB_TIMEOUT_LSB,   0x40},
    {RFM95W_REG_PREAMBLE_MSB,       0x00},
    {RFM95W_REG_PREAMBLE_LSB,       0x08},
    {RFM95W_REG_PAYLOAD_LENGTH,     0x01},
    {RFM95W_REG_MAX_PAYLOAD_LENGTH, 0xFF},
    {RFM95W_REG_HOP_PERIOD,         0x00},  // Frequency hopping disabled
    {RFM95W_REG_MODEM_CONFIG3,      0x00},  // Data rate is under 16ms, LNA 
                                            // gain set by LnaGain regsister
};

#define RFM95W_REG_INIT_TABLE_LEN (sizeof(RFM95W_REG_INIT_TABLE) / 2)

static const uint8_t RFM95W_SILICON_VERSION = 0x12;


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
static const uint8_t FREQ_WORD_868_1[] = {0xD9, 0x06, 0x66};

// =============================================================================
// Private variables
// =============================================================================

// =============================================================================
// Private function declarations
// =============================================================================

/**
 @brief Performs a CW transmission.
 */
static void rfmw_send_cw(void);

// =============================================================================
// Public function definitions
// =============================================================================

void rfm95w_init(void)
{
    uint8_t i;

    while (clock_get_msec() <= 10)
    {
        ;   // The user should wait for 10 ms from of the end of the POR cycle
            // before commencing communications over the SPI bus
    }

    LORA_RESET_OFF;

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

    rfm95w_io_write_single_reg(RFM95W_REG_FRF_MSB, FREQ_WORD_868_1[0]);
    rfm95w_io_write_single_reg(RFM95W_REG_FRF_MID, FREQ_WORD_868_1[1]);
    rfm95w_io_write_single_reg(RFM95W_REG_FRF_LSB, FREQ_WORD_868_1[2]);

    for (i = 0; i != RFM95W_REG_INIT_TABLE_LEN; ++i)
    {
        rfm95w_io_write_single_reg(RFM95W_REG_INIT_TABLE[i][0],
                                   RFM95W_REG_INIT_TABLE[i][1]);
    }

    rfm95w_io_set_operating_mode(RFM95W_OP_MODE_STAND_BY);
}

// =============================================================================
// Private function definitions
// =============================================================================

static void rfmw_send_cw(void)
{
    uint8_t modem_config_2;

    modem_config_2 = rfm95w_io_read_single_reg(RFM95W_REG_MODEM_CONFIG2);
    modem_config_2 |= RFM95W_TX_CONTINUOUS_MODE << 3;
    rfm95w_io_write_single_reg(RFM95W_REG_MODEM_CONFIG2, modem_config_2);

    rfm95w_io_set_operating_mode(RFM95W_OP_MODE_TX);
}
