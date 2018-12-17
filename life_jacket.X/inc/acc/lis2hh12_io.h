#ifndef LIS2HH12_H
#define LIS2HH12_H

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
    LIS2HH12_REG_TEMP_L         = 0x0B,
    LIS2HH12_REG_TEMP_H         = 0x0C,
    LIS2HH12_REG_WHO_AM_I       = 0x0F,
    LIS2HH12_REG_ACT_THS        = 0x1E,
    LIS2HH12_REG_ACT_DUR        = 0x1F,
    LIS2HH12_REG_CTRL1          = 0x20,
    LIS2HH12_REG_CTRL2          = 0x21,
    LIS2HH12_REG_CTRL3          = 0x22,
    LIS2HH12_REG_CTRL4          = 0x23,
    LIS2HH12_REG_CTRL5          = 0x24,
    LIS2HH12_REG_CTRL6          = 0x25,
    LIS2HH12_REG_CTRL7          = 0x26,
    LIS2HH12_REG_STATUS         = 0x27,
    LIS2HH12_REG_OUT_X_L        = 0x28,
    LIS2HH12_REG_OUT_X_H        = 0x29,
    LIS2HH12_REG_OUT_Y_L        = 0x2A,
    LIS2HH12_REG_OUT_Y_H        = 0x2B,
    LIS2HH12_REG_OUT_Z_L        = 0x2C,
    LIS2HH12_REG_OUT_Z_H        = 0x2D,
    LIS2HH12_REG_FIFO_CTRL      = 0x2E,
    LIS2HH12_REG_FIFO_SRC       = 0x2F,
    LIS2HH12_REG_IG_CFG1        = 0x30,
    LIS2HH12_REG_IG_SRC1        = 0x31,
    LIS2HH12_REG_IG_THS_X1      = 0x32,
    LIS2HH12_REG_IG_THS_Y1      = 0x33,
    LIS2HH12_REG_IG_THS_Z1      = 0x34,
    LIS2HH12_REG_IG_DUR1        = 0x35,
    LIS2HH12_REG_CFG2           = 0x36,
    LIS2HH12_REG_SRC2           = 0x37,
    LIS2HH12_REG_THS2           = 0x38,
    LIS2HH12_REG_DUR2           = 0x39,
    LIS2HH12_REG_XL_REFERENCE   = 0x3A,
    LIS2HH12_REG_XH_REFERENCE   = 0x3B,
    LIS2HH12_REG_YL_REFERENCE   = 0x3C,
    LIS2HH12_REG_YH_REFERENCE   = 0x3D,
    LIS2HH12_REG_ZL_REFERENCE   = 0x3E,
    LIS2HH12_REG_ZH_REFERENCE   = 0x3F
} lis2hh12_address_t;

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
 @brief Writes a value to one of the registers.
 @param reg         - Address of the register to write to.
 @param value       - The value which shall be written to the register.
*/
void lis2hh12_write_register(lis2hh12_address_t reg, uint8_t value);

/**
 @brief Reads the contents of one register.
 @param reg         - Address of the register to read from.
 @return The value read from the specified register.
*/
uint8_t lis2hh12_read_register(lis2hh12_address_t reg);

#ifdef  __cplusplus
}
#endif

#endif  /* LIS2HH12_H */

