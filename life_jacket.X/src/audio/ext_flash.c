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
        sprintf((char*)g_uart_string_buffer,
                "External flash - invalid manufacturer id. Was 0x%02X should be 0x%02X",
                manufacturer_id,
                RDID_MANUFACTURER_ID);
        debug_log_append_line((char*)g_uart_string_buffer);
        
        return;
    }

    if (RDID_DEVICE_ID != device_id)
    {
        sprintf((char*)g_uart_string_buffer,
                "External flash - invalid device id. Was 0x%04X should be 0x%04X",
                device_id,
                RDID_DEVICE_ID);
        debug_log_append_line((char*)g_uart_string_buffer);

        return;
    }

    sprintf((char*)g_uart_string_buffer,
            "External flash communication ok");
    debug_log_append_line((char*)g_uart_string_buffer);
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