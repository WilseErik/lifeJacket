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
#define EXT_FLASH_PAGE_LENGTH (256)

// =============================================================================
// Public function declarations
// =============================================================================

/**
 @brief Initializes the mx25r6435f chip.
*/
void ext_flash_init(void);

/**
 @brief Reads a number of consecutive bytes from the flash memeory.
 @param destination - Where to store the read data.
 @param address     - Address of first byte to read.
 @param length      - Number of bytes to read. Must be multiple of 4.
*/
void ext_flash_read(void * destination, uint32_t address, uint32_t length);

/**
 @brief Reads one byte from the external flash memory.
 @param address     - Address to read from.
 @return Read byte.
*/
uint8_t ext_flash_read_byte(uint32_t address);

/**
 @brief Reads one word from the external flash memory.
 @param address     - Address to read from.
 @return Read word.
*/
uint16_t ext_flash_read_word(uint32_t address);

/**
 @brief Reads one dword from the external flash memory.
 @param address     - Address to read from.
 @return Read dword.
*/
uint32_t ext_flash_read_dword(uint32_t address);

/**
 @brief Erases all data on the flash memory.
*/
void ext_flash_chip_erase(void);

/**
 @brief Checks if a write is in progress.
*/
bool ext_flash_is_write_in_progress(void);

/**
 @brief Programs a 256 byte data block.
 @param data    - The data to program the flash with.
 @param address - Start address of the page to program.
*/
void ext_flash_program_page(const void * data, uint32_t address);

#ifdef  __cplusplus
}
#endif

#endif  /* EXT_FLASH_H */

