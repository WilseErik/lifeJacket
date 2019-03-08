#ifndef P2PC_PROTOCOL
#define P2PC_PROTOCOL

/*
This file handles the Point to Point (P2P) client-side (C) protocol.
*/

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
 * @brief Initializes the point to point protocol.
 */
void p2pc_protocol_init(void);

/**
 * @brief Starts a gps position broadcast.
 */
void p2pc_protocol_broadcast_gps_position(void);

/**
* @brief Checks if the protocol has been initialized.
* @return True if protocol is active.
*/
bool p2pc_protocol_is_active(void);

#ifdef  __cplusplus
}
#endif

#endif  /* P2PC_PROTOCOL */

