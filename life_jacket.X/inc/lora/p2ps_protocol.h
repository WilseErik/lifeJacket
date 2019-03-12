#ifndef P2PS_PROTOCOL_H
#define P2PS_PROTOCOL_H

/*
This file handles the Point to Point (P2P) server-side (S) protocol.
*/

#ifdef  __cplusplus
extern "C" {
#endif

// =============================================================================
// Include statements
// =============================================================================
    
#include <stdint.h>
#include <stdbool.h>

#include "lora/p2p_protocol.h"

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
void p2ps_protocol_init(void);

/**
* @brief Checks if the protocol has been initialized.
* @return True if protocol is active.
*/
bool p2ps_protocol_is_active(void);

#ifdef  __cplusplus
}
#endif

#endif  /* P2PS_PROTOCOL_H */

