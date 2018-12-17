#ifndef EXT_FLASH_H
#define EXT_FLASH_H

#ifdef  __cplusplus
extern "C" {
#endif

// =============================================================================
// Include statements
// =============================================================================

#include <stdint.h>
#include <stdbool.h>

// =============================================================================
// Public type definitions
// =============================================================================

typedef enum
{
    EXT_FLASH_CMD_READ                  = 0x03,
    EXT_FLASH_CMD_FAST_READ             = 0x0B,
    EXT_FLASH_CMD_2READ                 = 0xBB,
    EXT_FLASH_CMD_DREAD                 = 0x3B,
    EXT_FLASH_CMD_4READ                 = 0xEB,
    EXT_FLASH_CMD_QREAD                 = 0x6B,
    EXT_FLASH_CMD_PAGE_PROGRAM          = 0x02,
    EXT_FLASH_CMD_QUAD_PAGE_PROGRAM     = 0x38,
    EXT_FLASH_CMD_SECTOR_ERASE          = 0x20,
    EXT_FLASH_CMD_BLOCK_ERASE_32        = 0x52,
    EXT_FLASH_CMD_BLOCK_ERASE_64        = 0xD8,
    EXT_FLASH_CMD_CHIP_ERASE            = 0x60,
    EXT_FLASH_CMD_READ_SFDP             = 0x5A,
    EXT_FLASH_CMD_WRITE_ENABLE          = 0x06,
    EXT_FLASH_CMD_WRITE_DISABLE         = 0x04,
    EXT_FLASH_CMD_READ_STATUS           = 0x05,
    EXT_FLASH_CMD_READ_CONFIG           = 0x15,
    EXT_FLASH_CMD_WRITE_STATUS          = 0x01,
    EXT_FLASH_CMD_SUSPEND               = 0x75,
    EXT_FLASH_CMD_RESUME                = 0x7A,
    EXT_FLASH_CMD_DEEP_POWER_DOWN       = 0xB9,
    EXT_FLASH_CMD_SET_BURST_LENGTH      = 0xC0,
    EXT_FLASH_CMD_READ_ID               = 0x9F,
    EXT_FLASH_CMD_READ_ELECTRONIC_ID    = 0xAB,
    EXT_FLASH_CMD_READ_MANUFACTURER     = 0x90,
    EXT_FLASH_CMD_ENTER_SECURED_OTP     = 0xB1,
    EXT_FLASH_CMD_EXIT_SECURED_OTP      = 0xC1,
    EXT_FLASH_CMD_READ_SECURITY         = 0x2B,
    EXT_FLASH_CMD_WRITE_SECURITY        = 0x2F,
    EXT_FLASH_CMD_NOP                   = 0x00,
    EXT_FLASH_CMD_RESET_ENABLE          = 0x66,
    EXT_FLASH_CMD_RESET_MEMORY          = 0x99
} ext_flash_command_t;

// =============================================================================
// Global variable declarations
// =============================================================================
    
// =============================================================================
// Global constatants
// =============================================================================

// =============================================================================
// Public function declarations
// =============================================================================

/**
 @brief Initializes the mx25r6435f chip.
*/
void ext_flash_init(void);

#ifdef  __cplusplus
}
#endif

#endif  /* EXT_FLASH_H */

