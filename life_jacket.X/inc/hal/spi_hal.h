#ifndef SPI_HAL_H
#define SPI_HAL_H

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
	SPI_DEVICE_NULL,
    SPI_DEVICE_RFM95W,
    SPI_DEVICE_LIS2HH12,
    SPI_DEVICE_PCM1770,
    SPI_DEVICE_EXT_FLASH
} spi_hal_device_t;

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
 @brief Sets up the SPI interface for communication with one external device.
 @param device  - Device to set up the SPI interface for.
*/
void spi_hal_setup_for_device(spi_hal_device_t device);

/**
 @brief Performs one 16bit spi session.
 @details This is a blocking operation, and takes control over the CS pin.
 @param v   - Value to transmit.
 @return Received value.
*/
uint16_t spi_hal_tranceive16(uint16_t v);

/**
 @brief Performs one 8bit spi session.
 @details This is a blocking operation, and does no take control over the CS pin.
 @param v   - Value to transmit.
 @return Received value.
*/
uint8_t spi_hal_tranceive8(uint8_t v);
 
#ifdef  __cplusplus
}
#endif

#endif  /* SPI_HAL_H */

