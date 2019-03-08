/* 
 * File:   dma.h
 * Author: Erik
 *
 * This file forms a hardware abstraction layer for the DMA module
 * which is uesd in order to move data between perhipherials and memory without
 * involving the CPU.
 */

#ifndef DMA_H
#define	DMA_H

#ifdef	__cplusplus
//extern "C" {
#endif


// =============================================================================
// Include statements
// =============================================================================

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
 * @brief Initializes the DMA channel used for loading the I2S module.
 * @param void
 * @return void
 */
void dma_i2s_ch_init(void);

/**
 * @brief Deinitializes the DMA channel used for loading the I2S module.
 */
void dma_i2s_ch_deinit(void);

#ifdef	__cplusplus
}
#endif

#endif	/* DMA_H */

