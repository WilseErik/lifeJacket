// =============================================================================
// Include statements
// =============================================================================

#include "lora\p2pc_protocol.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <xc.h>

#include "lora/rfm95w.h"
#include "uart/debug_log.h"
#include "hal/uart.h"
#include "lora/lora_tx_queue.h"

// =============================================================================
// Private type definitions
// =============================================================================

typedef enum
{
    P2P_DATA_TYPE_ACK           = 0x01,
    P2P_DATA_TYPE_GPS_POSITION  = 0x02
} p2p_data_type_t;

typedef struct p2p_frame_header_t
{
    uint32_t source_address;
    uint32_t destination_address;
    uint8_t frame_number;
    uint8_t time_to_live;
    uint8_t protocol;
    p2p_data_type_t data_type;
} p2p_frame_header_t;

typedef enum
{
    P2P_INDEX_SOURCE        = 0,
    P2P_INDEX_DESTINATION   = 5,
    P2P_INDEX_FRAME_NUMBER  = 9,
    P2P_INDEX_TIME_TO_LIVE  = 10,
    P2P_INDEX_PROTOCOL      = 11,
    P2P_INDEX_DATA_TYPE     = 12,
    P2P_INDEX_APPLICATION   = 13,
} p2p_message_index_t;

// =============================================================================
// Global variables
// =============================================================================

// =============================================================================
// Private constants
// =============================================================================

// =============================================================================
// Private variables
// =============================================================================

static uint8_t frame_number;

// =============================================================================
// Private function declarations
// =============================================================================

static void p2pc_handle_received_message(const uint8_t * data, uint8_t length);

static void p2pc_write_header(uint8_t * data,
                              const p2p_frame_header_t * header);

// =============================================================================
// Public function definitions
// =============================================================================

void p2pc_protocol_init(void)
{
    rfm95w_register_received_message_callback(p2pc_handle_received_message);

    frame_number = 0;
}

void p2pc_protocol_broadcast_gps_position(void)
{
    uint8_t message[32];
    p2p_frame_header_t header;
    lora_tx_queue_element_t queue_element;
    uint8_t i;

    header.source_address = 0xA1A2A3A4;
    header.destination_address = 0xFFFFFFFF;
    header.frame_number = frame_number++;
    header.time_to_live = 15;
    header.protocol = 1;
    header.data_type = P2P_DATA_TYPE_GPS_POSITION;

    p2pc_write_header(message, &header);

    //
    // Fill in GPS data here
    //


    queue_element.data = message;
    queue_element.length = sizeof(p2p_frame_header_t);
    lora_tx_queue_append(&queue_element);
}

// =============================================================================
// Private function definitions
// =============================================================================

static void p2pc_handle_received_message(const uint8_t * data, uint8_t length)
{
    uint8_t i;
    char * p = g_uart_string_buffer;

    sprintf(g_uart_string_buffer, "Received: ");
    p += strlen(g_uart_string_buffer);

    for (i = 0; i != length; ++i)
    {
        sprintf(p, "%02X ", data[i]);
        p += 3;
    }

    debug_log_append_line(g_uart_string_buffer);
}

static void p2pc_write_header(uint8_t * data, const p2p_frame_header_t * header)
{
    data[0] = (uint8_t)(header->source_address >> 24);
    data[1] = (uint8_t)(header->source_address >> 16);
    data[2] = (uint8_t)(header->source_address >>  8);
    data[3] = (uint8_t)(header->source_address >>  0);

    data[4] = (uint8_t)(header->destination_address >> 24);
    data[5] = (uint8_t)(header->destination_address >> 16);
    data[6] = (uint8_t)(header->destination_address >>  8);
    data[7] = (uint8_t)(header->destination_address >>  0);

    data[8] = header->frame_number;
    data[9] = header->time_to_live;
    data[10] = header->protocol;
    data[11] = header->data_type;
}