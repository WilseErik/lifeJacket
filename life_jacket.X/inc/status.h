#ifndef STATUS_H
#define	STATUS_H

#ifdef	__cplusplus
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
    // Error flag
    STATUS_CRITICAL_ERROR_FLAG,

    // Event flags
    STATUS_UART_RECEIVE_FLAG,
    STATUS_GPS_ON_EVENT,
    STATUS_GPS_BROADCAST_EVENT,
    STATUS_GPS_HOTSTART_EVENT,

    // Status runtime values
    STATUS_BYTE_LAST
} status_byte_index_t;

typedef enum
{
    CRIT_ERR_NO_ERROR = 0,
} critical_error_t;

typedef uint8_t status_item_t;
    
// =============================================================================
// Global variable declarations
// =============================================================================

extern volatile status_item_t status_bytes[STATUS_BYTE_LAST];

// =============================================================================
// Global constatants
// =============================================================================

#define STATUS_PERIPHERAL_FREQ 16000000

// =============================================================================
// Public function declarations
// =============================================================================

/**
 * @brief Inititalizes the status variables.
 */
void status_init(void);

/**
 * @brief Checks the value of one status item.
 * @param index - index of the item to check.
 * @return status item to check.
 */
static inline status_item_t status_check(status_byte_index_t index)
{
    return status_bytes[index];
}

/**
 * @brief Sets the value of one status item.
 * @param index - index of the item to set the value of.
 * @param val - new value to assign the chosen status item.
 */
static inline void status_set(status_byte_index_t index, status_item_t val)
{
    status_bytes[index] = val;
}

/**
 * @brief Sets the value of one status item to 0.
 * @param index - index of the item to set the value of.
 */
static inline void status_clear(status_byte_index_t index)
{
    status_bytes[index] = 0;
}

#ifdef	__cplusplus
}
#endif

#endif	/* STATUS_H */

