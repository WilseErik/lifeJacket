#ifndef TERMINAL_H
#define	TERMINAL_H

#ifdef	__cplusplus
extern "C" {
#endif

// =============================================================================
// Include statements
// =============================================================================

#include <stdbool.h>
#include <stdint.h>
    
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
 * @brief Handles any received characters.
 */
void terminal_handle_uart_event(void);

/**
 * @brief Checks if the terminal allows the mcu to enter sleep mode.
 * @return True if sleep is allowed.
 */
bool termnial_allows_sleep(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TERMINAL_H */

