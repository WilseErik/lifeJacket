#ifndef DEBUG_LOG_H
#define DEBUG_LOG_H

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
 @brief Prints one line to the debug interface.
 @param line    - Line to print.
*/
void debug_log_append_line(const char * line);

/**
 @brief Enables/Disables the debug log.
 @param enable  - True to enable, false to disable.
*/
void debug_log_enable(bool enable);

#ifdef  __cplusplus
}
#endif

#endif  /* DEBUG_LOG_H */

