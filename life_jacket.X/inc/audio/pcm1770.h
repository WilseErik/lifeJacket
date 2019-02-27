#ifndef PCM1770_H
#define PCM1770_H

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
 @brief Initializes the PCM1770 chip.
*/
void pcm1770_init(void);

/**
 @brief Shuts down the PCM1770 chip and its I2S bus.
*/
void pcm1770_deinit(void);

/**
 @brief Writes a value to one of the PCM1770 registers.
 @param address     - Register address to write to.
 @param value       - Value to write into the register.
*/
void pcm1770_write_register(uint8_t address, uint8_t value);

/**
 @brief Exits the power down mode.
*/
void pcm1770_power_up(void);

/**
 @brief Enters the power down mode.
*/
void pcm1770_power_down(void);

#ifdef  __cplusplus
}
#endif

#endif  /* PCM1770_H */

