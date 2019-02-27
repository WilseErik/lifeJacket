// =============================================================================
// Include statements
// =============================================================================

#include "audio/ext_flash.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include <xc.h>

#include "hal/gpio.h"
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
static const uint8_t  RDID_MANUFACTURER_ID = 0xC2;
static const uint16_t RDID_DEVICE_ID = 0x2817;

// =============================================================================
// Private variables
// =============================================================================

// =============================================================================
// Private function declarations
// =============================================================================

static void ext_flash_read_id(uint8_t * manufacturer_id, uint16_t * device_id);

static void ext_flash_write_enable(void);

static uint8_t ext_flash_read_status_register(void);

// =============================================================================
// Public function definitions
// =============================================================================

void ext_flash_init(void)
{
    uint8_t manufacturer_id;
    uint16_t device_id;

    ext_flash_read_id(&manufacturer_id, &device_id);

    if (RDID_MANUFACTURER_ID != manufacturer_id)
    {
        sprintf(g_uart_string_buffer,
                "External flash - invalid manufacturer id. Was 0x%02X should be 0x%02X",
                manufacturer_id,
                RDID_MANUFACTURER_ID);
        debug_log_append_line(g_uart_string_buffer);
        
        return;
    }

    if (RDID_DEVICE_ID != device_id)
    {
        sprintf(g_uart_string_buffer,
                "External flash - invalid device id. Was 0x%04X should be 0x%04X",
                device_id,
                RDID_DEVICE_ID);
        debug_log_append_line(g_uart_string_buffer);

        return;
    }

    sprintf(g_uart_string_buffer,
            "External flash communication ok");
    debug_log_append_line(g_uart_string_buffer);
}

void ext_flash_read(void * destination, uint32_t address, uint32_t length)
{
    spi_hal_setup_for_device(SPI_DEVICE_EXT_FLASH);

    FLASH_CS_ON;

    (void)spi_hal_tranceive8((uint8_t)EXT_FLASH_CMD_READ);

    (void)spi_hal_tranceive8((uint8_t)(address >> 16));
    (void)spi_hal_tranceive8((uint8_t)(address >>  8));
    (void)spi_hal_tranceive8((uint8_t)(address >>  0));

    spi_hal_read16_block(destination, length);

    FLASH_CS_OFF;
}

uint8_t ext_flash_read_byte(uint32_t address)
{
    uint8_t read_byte;

    spi_hal_setup_for_device(SPI_DEVICE_EXT_FLASH);

    FLASH_CS_ON;

    (void)spi_hal_tranceive8((uint8_t)EXT_FLASH_CMD_READ);

    (void)spi_hal_tranceive8((uint8_t)(address >> 16));
    (void)spi_hal_tranceive8((uint8_t)(address >>  8));
    (void)spi_hal_tranceive8((uint8_t)(address >>  0));

    read_byte = spi_hal_tranceive8(0);

    FLASH_CS_OFF;

    return read_byte;
}

uint16_t ext_flash_read_word(uint32_t address)
{
    uint16_t read_word;

    spi_hal_setup_for_device(SPI_DEVICE_EXT_FLASH);

    FLASH_CS_ON;

    (void)spi_hal_tranceive8((uint8_t)EXT_FLASH_CMD_READ);

    (void)spi_hal_tranceive8((uint8_t)(address >> 16));
    (void)spi_hal_tranceive8((uint8_t)(address >>  8));
    (void)spi_hal_tranceive8((uint8_t)(address >>  0));

    read_word = ((uint16_t)spi_hal_tranceive8(0)) << 8;
    read_word |= ((uint16_t)spi_hal_tranceive8(0)) << 0;
    
    FLASH_CS_OFF;

    return read_word;
}

uint32_t ext_flash_read_dword(uint32_t address)
{
    uint32_t read_dword;

    spi_hal_setup_for_device(SPI_DEVICE_EXT_FLASH);

    FLASH_CS_ON;

    (void)spi_hal_tranceive8((uint8_t)EXT_FLASH_CMD_READ);

    (void)spi_hal_tranceive8((uint8_t)(address >> 16));
    (void)spi_hal_tranceive8((uint8_t)(address >>  8));
    (void)spi_hal_tranceive8((uint8_t)(address >>  0));

    read_dword  = ((uint32_t)spi_hal_tranceive8(0)) << 24;
    read_dword |= ((uint32_t)spi_hal_tranceive8(0)) << 16;
    read_dword |= ((uint32_t)spi_hal_tranceive8(0)) <<  8;
    read_dword |= ((uint32_t)spi_hal_tranceive8(0)) <<  0;
    
    FLASH_CS_OFF;

    return read_dword;
}

void ext_flash_chip_erase(void)
{
    ext_flash_write_enable();

    FLASH_CS_ON;

    (void)spi_hal_tranceive8((uint8_t)EXT_FLASH_CMD_CHIP_ERASE);

    FLASH_CS_OFF;

    debug_log_append_line("Chip erase started!");

    while (ext_flash_is_write_in_progress())
    {
        ClrWdt();
    }

    debug_log_append_line("Chip erase done!");
}

bool ext_flash_is_write_in_progress(void)
{
    return ((ext_flash_read_status_register() & 0x01) != 0);
}

void ext_flash_program_page(const void * data, uint32_t address)
{
    uint16_t i;
    const uint16_t * data_pointer = data;

    spi_hal_setup_for_device(SPI_DEVICE_EXT_FLASH);

    while (ext_flash_is_write_in_progress())
    {
        ;
    }

    ext_flash_write_enable();

    FLASH_CS_ON;

    (void)spi_hal_tranceive8((uint8_t)EXT_FLASH_CMD_PAGE_PROGRAM);

    (void)spi_hal_tranceive8((uint8_t)(address >> 16));
    (void)spi_hal_tranceive8((uint8_t)(address >>  8));
    (void)spi_hal_tranceive8((uint8_t)(address >>  0));

    for (i = 0; i != EXT_FLASH_PAGE_LENGTH / 2; ++i)
    {
        (void)spi_hal_tranceive8(data_pointer[i] >> 8);
        (void)spi_hal_tranceive8(data_pointer[i] >> 0);
    }

    FLASH_CS_OFF;

    while (ext_flash_is_write_in_progress())
    {
        ;
    }
}

// =============================================================================
// Private function definitions
// =============================================================================

static void ext_flash_read_id(uint8_t * manufacturer_id, uint16_t * device_id)
{
    spi_hal_setup_for_device(SPI_DEVICE_EXT_FLASH);

    FLASH_CS_ON;

    (void)spi_hal_tranceive8((uint8_t)EXT_FLASH_CMD_READ_ID);

    *manufacturer_id = spi_hal_tranceive8(0);
    *device_id = ((uint16_t)spi_hal_tranceive8(0)) << 8;
    *device_id |= spi_hal_tranceive8(0);

    FLASH_CS_OFF;
}

static void ext_flash_write_enable(void)
{
    spi_hal_setup_for_device(SPI_DEVICE_EXT_FLASH);

    FLASH_CS_ON;

    (void)spi_hal_tranceive8((uint8_t)EXT_FLASH_CMD_WRITE_ENABLE);

    FLASH_CS_OFF;
}

static uint8_t ext_flash_read_status_register(void)
{
    uint8_t status_register = 0x0000;

    spi_hal_setup_for_device(SPI_DEVICE_EXT_FLASH);

    FLASH_CS_ON;

    (void)spi_hal_tranceive8((uint8_t)EXT_FLASH_CMD_READ_STATUS);

    status_register = spi_hal_tranceive8(0);

    FLASH_CS_OFF;

    return status_register;
}