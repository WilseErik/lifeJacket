#ifndef NMEA_QUEUE_H
#define NMEA_QUEUE_H

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

typedef struct nmea_queue_struct_t * nmea_queue_t;

// =============================================================================
// Global variable declarations
// =============================================================================
    
// =============================================================================
// Global constatants
// =============================================================================

#define NMEA_MAX_MESSAGE_LENGTH (85)

// =============================================================================
// Public function declarations
// =============================================================================

/**
 @brief Initializes the NMEA queue.
*/
void nmea_queue_init(nmea_queue_t queue);

/**
 @brief Gets the NMEA RX queue.
 @return RX queue.
*/
nmea_queue_t nmea_queue_get_rx_queue(void);

/**
 @brief Gets the NMEA TX queue.
 @return TX queue.
*/
nmea_queue_t nmea_queue_get_tx_queue(void);

/**
 @brief Appends a NMEA message to the queue.
 @param queue       - Queue to append to
 @param message     - Message to append to the queue
 @param length      - Number of characters in message
*/
void nmea_queue_append(nmea_queue_t queue, char * message, uint16_t length);

/**
 @brief Gets the number of elements in the queue.
 @param queue       - Queue to get the size of
 @return Number of elements in the RX queue.
*/
uint16_t nmea_queue_size(nmea_queue_t queue);

/**
 @breif Gets the first message in the queue.
 @param queue       - Queue to peek in
 @return First message in the queue.
*/
char * nmea_queue_peek(nmea_queue_t queue);

/**
 @brief Gets the length of the first message in the queue.
 @param queue       - Queue to peek in
 @return Length of the first message in the RX queue.
*/
uint16_t nmea_queue_peek_length(nmea_queue_t queue);

/**
 @brief Removes the first element from the queue.
 @param queue       - Queue to pop
*/
void nmea_queue_pop(nmea_queue_t queue);

#ifdef  __cplusplus
}
#endif

#endif  /* NMEA_QUEUE_H */

