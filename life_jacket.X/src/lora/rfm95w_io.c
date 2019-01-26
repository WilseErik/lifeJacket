// =============================================================================
// Include statements
// =============================================================================

#include "lora/rfm95w_io.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <xc.h>

#include "hal/spi_hal.h"
#include "hal/uart.h"
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
static const uint8_t FREQ_WORD_868_3[] = {0xD9, 0x13, 0x33};
static const uint8_t FREQ_WORD_868_5[] = {0xD9, 0x20, 0x00};
static const uint8_t FREQ_WORD_867_1[] = {0xD8, 0xC6, 0x66};
static const uint8_t FREQ_WORD_867_3[] = {0xD8, 0xD3, 0x33};
static const uint8_t FREQ_WORD_867_5[] = {0xD8, 0xE0, 0x00};
static const uint8_t FREQ_WORD_867_7[] = {0xD8, 0xEC, 0xCC};
static const uint8_t FREQ_WORD_867_9[] = {0xD8, 0xF9, 0x99};

// =============================================================================
// Private variables
// =============================================================================

// =============================================================================
// Private function declarations
// =============================================================================

// =============================================================================
// Public function definitions
// =============================================================================

void rfm95w_io_write(rfm95w_address_t reg, uint8_t value)
{
    uint16_t value_to_write = 0x8000;

    spi_hal_setup_for_device(SPI_DEVICE_RFM95W);

    value_to_write |= (((uint16_t)reg) << 8);
    value_to_write |= (uint16_t)value;

    (void)spi_hal_tranceive16(value_to_write);
}

uint8_t rfm95w_io_read(rfm95w_address_t reg)
{
    uint16_t value_to_write = 0x0000;
    uint16_t read_value;

    spi_hal_setup_for_device(SPI_DEVICE_RFM95W);

    value_to_write |= (((uint16_t)reg) << 8);

    read_value = spi_hal_tranceive16(value_to_write);

    return ((uint8_t)read_value);
}

void rfm95w_io_set_dio_function(uint8_t dio_number, uint8_t dio_function)
{
    uint8_t reg_addr = RFM95W_REG_DIO_MAPPING_1;
    uint8_t bit_shift = 0;
    uint8_t reg_value;

    switch (dio_number)
    {
        case 0:
            reg_addr = RFM95W_REG_DIO_MAPPING_1;
            bit_shift = 6;
            break;

        case 1:
            reg_addr = RFM95W_REG_DIO_MAPPING_1;
            bit_shift = 4;
            break;

        case 2:
            reg_addr = RFM95W_REG_DIO_MAPPING_1;
            bit_shift = 2;
            break;

        case 3:
            reg_addr = RFM95W_REG_DIO_MAPPING_1;
            bit_shift = 0;
            break;

        case 4:
            reg_addr = RFM95W_REG_DIO_MAPPING_2;
            bit_shift = 6;
            break;

        case 5:
            reg_addr = RFM95W_REG_DIO_MAPPING_2;
            bit_shift = 4;
            break;
    }

    reg_value = rfm95w_io_read(reg_addr);
    reg_value &= ~(0x03 << bit_shift);
    reg_value |= (dio_function & 0x03) << bit_shift;

    rfm95w_io_write(reg_addr, reg_value);
}

void rfm95w_io_set_operating_mode(rfm95w_operating_mode_t mode)
{
    uint8_t reg_value;

    reg_value = rfm95w_io_read(RFM95W_REG_OP_MODE);
    reg_value &= 0xF8;
    reg_value |= ((uint8_t)mode) & 0x07;
    rfm95w_io_write(RFM95W_REG_OP_MODE, reg_value);
}

void rfm95w_io_set_single_rx_timeout(uint16_t symbols)
{
    uint8_t modem_config_2;

    if (symbols > 0x03FF)
    {
        symbols = 0x03FF;
    }
    else if (symbols < 4)
    {
        symbols = 4;
    }

    modem_config_2 = rfm95w_io_read(RFM95W_REG_MODEM_CONFIG2);
    modem_config_2 &= 0xFC;
    modem_config_2 |= ((uint8_t)(symbols >> 8)) & 0x03;
    rfm95w_io_write(RFM95W_REG_MODEM_CONFIG2, modem_config_2);

    rfm95w_io_write(RFM95W_REG_SYMB_TIMEOUT_LSB, (uint8_t)symbols);
}

void rfm95w_io_clear_all_irqs(void)
{
    rfm95w_io_write(RFM95W_REG_IRQ_FLAGS, 0xFF);   
}

void rfm95w_io_set_bandwidth(rfm95w_modem_cfg_bw_t bandwidth)
{
    uint8_t modem_config_1;

    modem_config_1 = rfm95w_io_read(RFM95W_REG_MODEM_CONFIG1);

    modem_config_1 &= 0x0F;
    modem_config_1 |= (bandwidth << 4);

    rfm95w_io_write(RFM95W_REG_MODEM_CONFIG1, modem_config_1);

    switch (bandwidth)
    {
        case RFM95W_BW_7K8:
            debug_log_append_line("\tLORA bandwidth set to 7.8 kHz");
            break;

        case RFM95W_BW_10K4:
            debug_log_append_line("\tLORA bandwidth set to 10.4 kHz");
            break;

        case RFM95W_BW_15K6:
            debug_log_append_line("\tLORA bandwidth set to 15.6 kHz");
            break;

        case RFM95W_BW_20K8:
            debug_log_append_line("\tLORA bandwidth set to 20.8 kHz");
            break;

        case RFM95W_BW_31K25:
            debug_log_append_line("\tLORA bandwidth set to 31.25 kHz");
            break;

        case RFM95W_BW_41K7:
            debug_log_append_line("\tLORA bandwidth set to 41.7 kHz");
            break;

        case RFM95W_BW_62K5:
            debug_log_append_line("\tLORA bandwidth set to 62.5 kHz");
            break;

        case RFM95W_BW_125K:
            debug_log_append_line("\tLORA bandwidth set to 125 kHz");
            break;

        case RFM95W_BW_250K:
            debug_log_append_line("\tLORA bandwidth set to 250 kHz");
            break;

        case RFM95W_BW_500K:
            debug_log_append_line("\tLORA bandwidth set to 500 kHz");
            break;

        default:
            debug_log_append_line("\tLORA bandwidth set to invalid value");
            break;
    }
}

void rfm95w_io_set_coding_rate(rfm95w_coding_rate_t coding_rate)
{
    uint8_t modem_config_1;

    modem_config_1 = rfm95w_io_read(RFM95W_REG_MODEM_CONFIG1);

    modem_config_1 &= 0x0E;
    modem_config_1 |= (coding_rate << 1);

    rfm95w_io_write(RFM95W_REG_MODEM_CONFIG1, modem_config_1);

    switch (coding_rate)
    {
    case RFM95W_CODING_RATE_4_5:
        debug_log_append_line("\tLORA coding rate set to 4/5");
        break;

    case RFM95W_CODING_RATE_4_6:
        debug_log_append_line("\tLORA coding rate set to 4/6");
        break;

    case RFM95W_CODING_RATE_4_7:
        debug_log_append_line("\tLORA coding rate set to 4/7");
        break;

    case RFM95W_CODING_RATE_4_8:
        debug_log_append_line("\tLORA coding rate set to 4/8");
        break;

    default:
        debug_log_append_line("\tLORA coding rate set to invalid value");
        break;
    }
}

void rfm95w_io_set_speading_factor(rfm95w_spreading_factor_t spreading_factor)
{
    uint8_t modem_config_2;

    modem_config_2 = rfm95w_io_read(RFM95W_REG_MODEM_CONFIG2);

    modem_config_2 &= 0xF0;
    modem_config_2 |= (spreading_factor << 4);

    rfm95w_io_write(RFM95W_REG_MODEM_CONFIG2, modem_config_2);

    switch (spreading_factor)
    {
    case RFM95W_SPREADING_FACTOR_64_CHIPS:
        debug_log_append_line("\tLORA spreading factor set to 64 chips");
        break;

    case RFM95W_SPREADING_FACTOR_128_CHIPS:
        debug_log_append_line("\tLORA spreading factor set to 128 chips");
        break;

    case RFM95W_SPREADING_FACTOR_256_CHIPS:
        debug_log_append_line("\tLORA spreading factor set to 256 chips");
        break;

    case RFM95W_SPREADING_FACTOR_512_CHIPS:
        debug_log_append_line("\tLORA spreading factor set to 512 chips");
        break;

    case RFM95W_SPREADING_FACTOR_1024_CHIPS:
        debug_log_append_line("\tLORA spreading factor set to 1024 chips");
        break;

    case RFM95W_SPREADING_FACTOR_2048_CHIPS:
        debug_log_append_line("\tLORA spreading factor set to 2048 chips");
        break;

    case RFM95W_SPREADING_FACTOR_4096_CHIPS:
        debug_log_append_line("\tLORA spreading factor set to 4096 chips");
        break;

    default:
        debug_log_append_line("\tLORA spreading factor set to invalid value");
        break;
    }
}

void rfm95w_io_set_frequency(rfm95w_channel_frequency_t frequency)
{
    const uint8_t * freq_word;

    switch (frequency)
    {
    case RFM95W_CHANNEL_FREQUENCY_868_1:
        freq_word = FREQ_WORD_868_1;
        debug_log_append_line("\tLORA frequency set to 868.1 MHz");
        break;

    case RFM95W_CHANNEL_FREQUENCY_868_3:
        freq_word = FREQ_WORD_868_3;
        debug_log_append_line("\tLORA frequency set to 868.3 MHz");
        break;

    case RFM95W_CHANNEL_FREQUENCY_868_5:
        freq_word = FREQ_WORD_868_5;
        debug_log_append_line("\tLORA frequency set to 868.5 MHz");
        break;

    case RFM95W_CHANNEL_FREQUENCY_867_1:
        freq_word = FREQ_WORD_867_1;
        debug_log_append_line("\tLORA frequency set to 867.1 MHz");
        break;

    case RFM95W_CHANNEL_FREQUENCY_867_3:
        freq_word = FREQ_WORD_867_3;
        debug_log_append_line("\tLORA frequency set to 867.3 MHz");
        break;

    case RFM95W_CHANNEL_FREQUENCY_867_5:
        freq_word = FREQ_WORD_867_5;
        debug_log_append_line("\tLORA frequency set to 867.5 MHz");
        break;

    case RFM95W_CHANNEL_FREQUENCY_867_7:
        freq_word = FREQ_WORD_867_7;
        debug_log_append_line("\tLORA frequency set to 867.7 MHz");
        break;

    case RFM95W_CHANNEL_FREQUENCY_867_9:
        freq_word = FREQ_WORD_867_9;
        debug_log_append_line("\tLORA frequency set to 867.9 MHz");
        break;

    default:
        freq_word = FREQ_WORD_868_1;
        debug_log_append_line("\tLORA frequency set to 868.1 MHz");
        break;
    }

    rfm95w_io_write(RFM95W_REG_FRF_MSB, freq_word[0]);
    rfm95w_io_write(RFM95W_REG_FRF_MID, freq_word[1]);
    rfm95w_io_write(RFM95W_REG_FRF_LSB, freq_word[2]);
}
// =============================================================================
// Private function definitions
// =============================================================================


