#ifndef RFM95W_H
#define RFM95W_H

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

#define RFM95W_RX_BUFFER_SIZE (256)

typedef struct rfm95w_buffer_t
{
    uint8_t data[RFM95W_RX_BUFFER_SIZE];
    uint8_t length;
} rfm95w_buffer_t;

typedef struct rfm95w_ack_parameters_t
{
    bool send_ack;
    bool wait_for_ack;

    bool was_valid_ack;
} rfm95w_ack_parameters_t;


typedef void (*rfmw95w_received_message_callback_t)(
    const uint8_t * data,
    uint8_t length,
    int16_t rssi,
    rfm95w_ack_parameters_t * ack_parameters,
    rfm95w_buffer_t * ack);


// =============================================================================
// Global variable declarations
// =============================================================================
    
// =============================================================================
// Global constatants
// =============================================================================
#define RFM95W_MAX_RETRANSMISSION_COUNT (3)

// =============================================================================
// Public function declarations
// =============================================================================

/**
 @brief Initializes the RFM95W module.
*/
void rfm95w_init(void);

/**
 * @brief Registers a callback for handling received messages.
 * @param callback  - Callback to register.
 */
void rfm95w_register_received_message_callback(
    rfmw95w_received_message_callback_t callback);

/**
 * @brief Checks if the RFM95W is in an idle state.
 * @return True if in idle.
 */
bool rfm95w_is_idle(void);

/**
 * @brief Appends data to the TX FIFO.
 * @param data      - Data to append to the FIFO.
 * @param length    - Number of bytes to append to the FIFO.
 * @param offset    - Number of bytes from tx fifo base address to start
 *                    writing at.
 */
void rfm95w_write_tx_fifo(const uint8_t * data,
                          uint8_t length,
                          uint8_t offset);

/**
 * @brief Clears the TX FIFO.
 */
void rfm95w_clear_tx_fifo(void);

/**
 * @brief Starts a TX session.
 */
void rfm95w_start_tx(uint8_t max_retransmissions, bool wait_for_ack);

/**
 * @brief Starts a RX session which ends at complete packet reception
 *        or after the rx time window has passed.
 */
void rfm95w_start_single_rx(void);

/**
 * @brief Starts a continuous RX session.
 */
void rfm95w_start_continuous_rx(void);

void rfmw_send_cw(void);

#ifdef  __cplusplus
}
#endif

#endif  /* RFM95W_H */

