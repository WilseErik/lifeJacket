#ifndef GPS_H
#define GPS_H

#ifdef  __cplusplus
extern "C" {
#endif

// =============================================================================
// Include statements
// =============================================================================

#include <stdint.h>
#include <stdbool.h>

#include "gps/nmea.h"

// =============================================================================
// Public type definitions
// =============================================================================

// =============================================================================
// Global variable declarations
// =============================================================================
    
// =============================================================================
// Global constatants
// =============================================================================

#define GPS_BROADCAST_INTERVAL_SEC (30)

// =============================================================================
// Public function declarations
// =============================================================================

/**
 * @brief Initializes the GPS receiver.
 */
void gps_init(void);

/**
 * @brief Should be polled from the main loop.
 */
void gps_poll(void);

/**
 * @brief Checks if the GPS receiver allows the MCU to enter sleep mode.
 * @return True if the MCU can enter sleep.
 */
bool gps_allows_sleep_mode(void);

/**
 @Brief Gets the current GPS coordinates.
 @return Pointer to a GPS coordinates structure.
*/
const nmea_coordinates_info_t * gps_get_coordinates(void);

#ifdef  __cplusplus
}
#endif

#endif  /* GPS_H */

