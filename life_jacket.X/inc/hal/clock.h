#ifndef CLOCK_HAL_H
#define CLOCK_HAL_H

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

extern volatile uint16_t g_clock_gps_on_event_timeout;
extern volatile uint16_t g_clock_gps_off_timeout;
extern volatile uint16_t g_clock_gps_hot_start_timeout_sec;
extern volatile uint16_t g_clock_gps_broadcast_timeout_sec;

// =============================================================================
// Global constatants
// =============================================================================

#define CLOCK_HAL_PCBCLOCK_FREQ (16000000ull)

// =============================================================================
// Public function declarations
// =============================================================================

/**
 @breif Starts the msec timer.
*/
void clock_start_msec_timer(void);

/**
 @brief Gets the current millisecond timer value. 
*/
uint32_t clock_get_msec(void);

/**
 @brief Starts the RTC timer.
*/
void clock_start_rtc(void);
 
#ifdef  __cplusplus
}
#endif

#endif  /* CLOCK_HAL_H */

