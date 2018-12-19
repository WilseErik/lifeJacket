// =============================================================================
// Include statements
// =============================================================================

#include <xc.h>

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "gps/nmea_queue.h"

// =============================================================================
// Private type definitions
// =============================================================================

#define NMEA_QUEUE_SIZE (5)

struct nmea_queue_struct_t
{
    char messages[NMEA_QUEUE_SIZE][NMEA_MAX_MESSAGE_LENGTH];
    uint16_t message_lengths[NMEA_QUEUE_SIZE];
    uint16_t first;
    uint16_t last;
    uint16_t size;
};

// =============================================================================
// Global variables
// =============================================================================

// =============================================================================
// Private constants
// =============================================================================

// =============================================================================
// Private variables
// =============================================================================

/*
    FIFO queue, append at the "last" index.
*/
static struct nmea_queue_struct_t rx_queue;
static struct nmea_queue_struct_t tx_queue;

// =============================================================================
// Private function declarations
// =============================================================================

// =============================================================================
// Public function definitions
// =============================================================================

void nmea_queue_init(nmea_queue_t queue)
{
    memset((void*)queue, 0, sizeof(struct nmea_queue_struct_t));
}

nmea_queue_t nmea_queue_get_rx_queue(void)
{
    return &rx_queue;
}

nmea_queue_t nmea_queue_get_tx_queue(void)
{
    return &tx_queue;
}

void nmea_queue_append(nmea_queue_t queue,
                       char * message,
                       uint16_t length)
{
    if (NMEA_QUEUE_SIZE == queue->size)
    {
        return; // queue is full, throw this message away
    }

    if (length > NMEA_MAX_MESSAGE_LENGTH)
    {
        return; // message is to long, throw this message away
    }

    if (queue->size)
    {
        queue->last += 1;
    }

    if (NMEA_QUEUE_SIZE == queue->last)
    {
        queue->last = 0;
    }

    memcpy(queue->messages[queue->last], message, length);
    queue->message_lengths[queue->last] = length;

    queue->size += 1;
}

uint16_t nmea_queue_size(nmea_queue_t queue)
{
    return queue->size;
}

char * nmea_queue_peek(nmea_queue_t queue)
{
    return queue->messages[queue->first];
}

uint16_t nmea_queue_peek_length(nmea_queue_t queue)
{
    return queue->message_lengths[queue->first];
}

void nmea_queue_pop(nmea_queue_t queue)
{
    if (!queue->size)
    {
        return; // Queue is already empty
    }

    if (1 != queue->size)
    {
        queue->first += 1;
    }

    queue->size -= 1;
}

// =============================================================================
// Private function definitions
// =============================================================================
