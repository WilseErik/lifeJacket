// =============================================================================
// Include statements
// =============================================================================

#include "lora\lora_tx_queue.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <xc.h>

#include "lora/rfm95w.h"

// =============================================================================
// Private type definitions
// =============================================================================

#define LORA_TX_QUEUE_MAX_MESSAGE_LENGTH (128)

typedef struct lora_tx_element_t
{
    uint8_t data[LORA_TX_QUEUE_MAX_MESSAGE_LENGTH];
    uint8_t length;
} lora_tx_element_t;

#define LORA_TX_QUEUE_LENGTH (4)

typedef struct lora_tx_queue_t
{
    lora_tx_element_t elements[LORA_TX_QUEUE_LENGTH];
    uint8_t first;      // new elements are added to index "first"
    uint8_t last;       // index of oldest element
    uint8_t size;       // number of elements in the queue
} lora_tx_queue_t;

// =============================================================================
// Global variables
// =============================================================================

// =============================================================================
// Private constants
// =============================================================================

// =============================================================================
// Private variables
// =============================================================================

static lora_tx_queue_t lora_tx_queue;

// =============================================================================
// Private function declarations
// =============================================================================

static void lora_tx_queue_increment_first(void);
static void lora_tx_queue_increment_last(void);

// =============================================================================
// Public function definitions
// =============================================================================

void lora_tx_queue_init(void)
{
    memset(&lora_tx_queue, sizeof(lora_tx_queue_t), 0);
}

bool lora_tx_queue_is_empty(void)
{
    return (0 == lora_tx_queue.size);
}

void lora_tx_queue_append(const lora_tx_queue_element_t * element)
{
    lora_tx_element_t * first_element;

    if (LORA_TX_QUEUE_LENGTH == lora_tx_queue.size)
    {
        return;
    }

    first_element = &lora_tx_queue.elements[lora_tx_queue.first];

    memcpy(first_element->data,
           element->data,
           element->length);
    first_element->length = element->length;

    lora_tx_queue_increment_first();

    lora_tx_queue.size += 1;
}

void lora_tx_queue_peek(lora_tx_queue_element_t * element)
{
    element->data = &(lora_tx_queue.elements[lora_tx_queue.last].data[0]);
    element->length = lora_tx_queue.elements[lora_tx_queue.last].length;
}

void lora_tx_queue_transmit_and_pop(void)
{
    lora_tx_queue_element_t element;

    if  (0 == lora_tx_queue.size)
    {
        return;
    }

    lora_tx_queue_peek(&element);

    rfm95w_clear_tx_fifo();
    rfm95w_write_tx_fifo(element.data,
                         element.length,
                         0);

    rfm95w_start_tx();

    if (1 != lora_tx_queue.size)
    {
        lora_tx_queue_increment_last();
    }

    lora_tx_queue.size -= 1;
}


// =============================================================================
// Private function definitions
// =============================================================================

static void lora_tx_queue_increment_first(void)
{
    lora_tx_queue.first += 1;

    if (LORA_TX_QUEUE_LENGTH == lora_tx_queue.first)
    {
        lora_tx_queue.first = 0;
    }
}

static void lora_tx_queue_increment_last(void)
{
    lora_tx_queue.last += 1;

    if (LORA_TX_QUEUE_LENGTH == lora_tx_queue.last)
    {
        lora_tx_queue.last = 0;
    }
}

