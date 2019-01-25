#ifndef LORA_TX_QUEUE_H
#define LORA_TX_QUEUE_H

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

typedef struct lora_tx_queue_element_t
{
    const uint8_t * data;
    uint8_t length;
} lora_tx_queue_element_t;

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
 * @brief Initializes the lora tx queue.
 */
void lora_tx_queue_init(void);

/**
 * @brief Checks if the queue is empty.
 * @return True if the queue is empty.
 */
bool lora_tx_queue_is_empty(void);

/**
 * @brief Appends a message to the tx queue.
 * @param element   - Element to append to the queue.
 */
void lora_tx_queue_append(const lora_tx_queue_element_t * element);

/**
 * @brief Peeks at the first element in the queue.
 * @param element   - Returns first element in queue.
 */
void lora_tx_queue_peek(lora_tx_queue_element_t * element);

/**
 * @brief Transmitts the first element and removes it from the queue.
 */
void lora_tx_queue_transmit_and_pop(void);

#ifdef  __cplusplus
}
#endif

#endif  /* LORA_TX_QUEUE_H */

