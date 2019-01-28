#ifndef NMEA_H
#define NMEA_H

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
 @brief Handles a NMEA output message.
*/
void nmea_handle_message(char * message);

/**
 @brief Resets the on lock event flag.
 */
void nmea_reset_on_lock_event(void);

/**
 @brief Checks if the on lock event flag is set.
 @return On lock event flag.
 */
bool nmea_check_on_lock_event(void);

/**
 * @brief Prints the current status on the debug UART.
 */
void nmea_print_status(void);

#ifdef  __cplusplus
}
#endif

#endif  /* NMEA_H */

