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


typedef struct nmea_coordinates_info_t
{
    bool        latitude_north;
    uint16_t    latitude_deg;
    float       latitude_minutes;
    
    bool        longitude_east;
    uint16_t    longitude_deg;
    float       longitude_minutes;
    
    uint8_t     time_of_fix_hours;
    uint8_t     time_of_fix_minutes;
    uint8_t     time_of_fix_seconds;
} nmea_coordinates_info_t;

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
 @brief Gets the most recent current coordinates.
 @param coordinates     - Where to store the coordinates.
*/
void nmea_get_coordinates(nmea_coordinates_info_t * coordinates);

/**
 * @brief Prints the current status on the debug UART.
 */
void nmea_print_status(void);

#ifdef  __cplusplus
}
#endif

#endif  /* NMEA_H */

