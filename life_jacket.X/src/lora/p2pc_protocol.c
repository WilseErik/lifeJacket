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
#include "gps/gps.h"
#include "hal/flash.h"

// =============================================================================
// Private type definitions
// =============================================================================


// =============================================================================
// Global variables
// =============================================================================

// =============================================================================
// Private constants
// =============================================================================

static const uint32_t P2P_BROADCAST_ADDRESS = 0xFFFFFFFF;

// =============================================================================
// Private variables
// =============================================================================

static volatile uint8_t frame_number;
static volatile uint8_t last_sent_frame_number;
static uint32_t my_address;
static bool initialized = false;

// =============================================================================
// Private function declarations
// =============================================================================

static void p2pc_handle_received_message(const uint8_t * data,
                                         uint8_t length,
                                         int16_t rssi,
                                         uint8_t snr,
                                         rfm95w_ack_parameters_t * ack_parameters,
                                         rfm95w_buffer_t * ack);

static void p2pc_write_header(uint8_t * data,
                              const p2p_frame_header_t * header);

static uint32_t p2pc_parse_radio_code(const uint8_t * data);

static void p2pc_print_received_message(const uint8_t * data,
                                        uint8_t length,
                                        int16_t rssi,
                                        uint8_t snr);

static bool p2pc_handle_ack(const uint8_t * data, uint8_t length);

// =============================================================================
// Public function definitions
// =============================================================================

void p2pc_protocol_init(void)
{
    rfm95w_register_received_message_callback(p2pc_handle_received_message);

    frame_number = 0;
    my_address = flash_read_dword(FLASH_INDEX_LORA_ADDRESS_MSB);

    initialized = true;
    debug_log_append_line("LORA P2PC initialized");
}

void p2pc_protocol_broadcast_gps_position(void)
{
    uint8_t message[32];
    p2p_frame_header_t header;
    lora_tx_queue_element_t queue_element;

    const nmea_coordinates_info_t * coordinates;
    uint8_t * minutes_pointer;

    header.source_address = my_address;
    header.destination_address = P2P_BROADCAST_ADDRESS;
    header.frame_number = frame_number;
    header.time_to_live = 15;
    header.protocol = 1;
    header.data_type = P2P_DATA_TYPE_GPS_POSITION;

    last_sent_frame_number = header.frame_number;
    frame_number += 1;

    p2pc_write_header(message, &header);

    //
    // Fill in GPS data here
    //
    coordinates = gps_get_coordinates();

    if (NULL == coordinates)
    {
        message[P2P_INDEX_APPLICATION + 0] = 0;
        message[P2P_INDEX_APPLICATION + 1] = 0;
        message[P2P_INDEX_APPLICATION + 2] = 0;
        message[P2P_INDEX_APPLICATION + 3] = 0;
        message[P2P_INDEX_APPLICATION + 4] = 0;
        message[P2P_INDEX_APPLICATION + 5] = 0;
        message[P2P_INDEX_APPLICATION + 6] = 0;
        message[P2P_INDEX_APPLICATION + 7] = 0;
        message[P2P_INDEX_APPLICATION + 8] = 0;
        message[P2P_INDEX_APPLICATION + 9] = 0;
        message[P2P_INDEX_APPLICATION + 10] = 0;
        message[P2P_INDEX_APPLICATION + 11] = 0;
        message[P2P_INDEX_APPLICATION + 12] = 0;
        message[P2P_INDEX_APPLICATION + 13] = 0;
        message[P2P_INDEX_APPLICATION + 14] = 0;
    }
    else
    {
        message[P2P_INDEX_APPLICATION + 0] = (uint8_t)(coordinates->latitude_deg >> 8);
        message[P2P_INDEX_APPLICATION + 1] = (uint8_t)coordinates->latitude_deg;

        if (coordinates->latitude_north)
        {
            message[P2P_INDEX_APPLICATION + 0] |= 0x80;
        }

        message[P2P_INDEX_APPLICATION + 2] = (uint8_t)(coordinates->longitude_deg >> 8);
        message[P2P_INDEX_APPLICATION + 3] = (uint8_t)coordinates->longitude_deg;

        if (coordinates->longitude_east)
        {
            message[P2P_INDEX_APPLICATION + 2] |= 0x80;
        }

        minutes_pointer = (uint8_t*)&(coordinates->latitude_minutes);
        message[P2P_INDEX_APPLICATION + 4] = *(minutes_pointer + 0);
        message[P2P_INDEX_APPLICATION + 5] = *(minutes_pointer + 1);
        message[P2P_INDEX_APPLICATION + 6] = *(minutes_pointer + 2);
        message[P2P_INDEX_APPLICATION + 7] = *(minutes_pointer + 3);

        minutes_pointer = (uint8_t*)&(coordinates->longitude_minutes);
        message[P2P_INDEX_APPLICATION + 8] = *(minutes_pointer + 0);
        message[P2P_INDEX_APPLICATION + 9] = *(minutes_pointer + 1);
        message[P2P_INDEX_APPLICATION + 10] = *(minutes_pointer + 2);
        message[P2P_INDEX_APPLICATION + 11] = *(minutes_pointer + 3);

        message[P2P_INDEX_APPLICATION + 12] = coordinates->time_of_fix_hours;
        message[P2P_INDEX_APPLICATION + 13] = coordinates->time_of_fix_minutes;
        message[P2P_INDEX_APPLICATION + 14] = coordinates->time_of_fix_seconds;
    }
    
    queue_element.data = message;
    queue_element.length = P2P_INDEX_APPLICATION + 15;
    lora_tx_queue_append(&queue_element);
}

bool p2pc_protocol_is_active(void)
{
    return initialized;
}

// =============================================================================
// Private function definitions
// =============================================================================

static void p2pc_handle_received_message(
    const uint8_t * data,
    uint8_t length,
    int16_t rssi,
    uint8_t snr,
    rfm95w_ack_parameters_t * ack_parameters,
    rfm95w_buffer_t * ack)
{
    uint32_t src;
    uint32_t dst;

    ack_parameters->send_ack = false;
    ack_parameters->wait_for_ack = false;
    ack_parameters->was_valid_ack = false;

    p2pc_print_received_message(data, length, rssi, snr);

    src = p2pc_parse_radio_code(&data[0]);
    dst = p2pc_parse_radio_code(&data[4]);

    if ((P2P_BROADCAST_ADDRESS == dst) || (dst == my_address))
    {
        uint8_t data_type = data[P2P_INDEX_DATA_TYPE];

        switch (data_type)
        {
            case P2P_DATA_TYPE_ACK:
                ack_parameters->was_valid_ack =
                    p2pc_handle_ack(data, length);
                break;

            default:
                break;
        }
    }
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

    data[8] = header->time_to_live;
    data[9] = header->frame_number;
    data[10] = header->protocol;
    data[11] = header->data_type;
}

static uint32_t p2pc_parse_radio_code(const uint8_t * data)
{
    uint32_t radio_code = 0x00000000;

    radio_code |= ((uint32_t)*data++) << 24;
    radio_code |= ((uint32_t)*data++) << 16;
    radio_code |= ((uint32_t)*data++) <<  8;
    radio_code |= ((uint32_t)*data++) <<  0;

    return radio_code;
}

static void p2pc_print_received_message(const uint8_t * data,
                                        uint8_t length,
                                        int16_t rssi,
                                        uint8_t snr)
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

    sprintf(p, "RSSI = %d SNR = %f dB", rssi, ((double)(int8_t)snr) / 4);

    debug_log_append_line(g_uart_string_buffer);
}

static bool p2pc_handle_ack(const uint8_t * data, uint8_t length)
{
    return data[P2P_INDEX_FRAME_NUMBER] == last_sent_frame_number;
}