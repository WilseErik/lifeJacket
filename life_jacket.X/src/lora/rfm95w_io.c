// =============================================================================
// Include statements
// =============================================================================

#include "lora/rfm95w_io.h"

#include <stdint.h>
#include <stdbool.h>

#include <xc.h>

#include "hal/spi_hal.h"

// =============================================================================
// Private type definitions
// =============================================================================

// =============================================================================
// Global variables
// =============================================================================

// =============================================================================
// Private constants
// =============================================================================

// =============================================================================
// Private variables
// =============================================================================

// =============================================================================
// Private function declarations
// =============================================================================

// =============================================================================
// Public function definitions
// =============================================================================

void rfm95w_io_write_single_reg(rfm95w_address_t reg, uint8_t value)
{
    uint16_t value_to_write = 0x8000;

    spi_hal_setup_for_device(SPI_DEVICE_RFM95W);

    value_to_write |= (((uint16_t)reg) << 8);
    value_to_write |= (uint16_t)value;

    (void)spi_hal_tranceive16(value_to_write);
}

uint8_t rfm95w_io_read_single_reg(rfm95w_address_t reg)
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

    reg_value = rfm95w_io_read_single_reg(reg_addr);
    reg_value &= ~(0x03 << bit_shift);
    reg_value |= (dio_function & 0x03) << bit_shift;

    rfm95w_io_write_single_reg(reg_addr, reg_value);
}

void rfm95w_io_set_operating_mode(rfm95w_operating_mode_t mode)
{
    uint8_t reg_value;

    reg_value = rfm95w_io_read_single_reg(RFM95W_REG_OP_MODE);
    reg_value &= 0xF8;
    reg_value |= ((uint8_t)mode) & 0x07;
    rfm95w_io_write_single_reg(RFM95W_REG_OP_MODE, reg_value);
}

// =============================================================================
// Private function definitions
// =============================================================================


