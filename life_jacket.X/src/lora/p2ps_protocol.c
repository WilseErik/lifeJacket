// =============================================================================
// Include statements
// =============================================================================

#include "lora\p2ps_protocol.h"

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

typedef enum
{
    P2P_GPS_INDEX_LATITUDE_DEG          = 0,
    P2P_GPS_INDEX_LONGITUDE_DEG         = 2,
    P2P_GPS_INDEX_LATITUDE_MINUTES      = 4,
    P2P_GPS_INDEX_LONGITUDE_MINUTES     = 8,
    P2P_GPS_INDEX_TOF_HOURS             = 12,
    P2P_GPS_INDEX_TOF_MINUTES           = 13,
    P2P_GPS_INDEX_TOD_SECONDS           = 14
} p2p_gps_message_index_t;

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

static uint8_t frame_number;
static uint32_t my_address;
static bool initialized = false;

// =============================================================================
// Private function declarations
// =============================================================================

static void p2ps_handle_received_message(const uint8_t * data,
                                         uint8_t length,
                                         int16_t rssi);

static void p2ps_parse_header(p2p_frame_header_t * header,
                              const uint8_t * data);

static void p2ps_parse_gps_coordinates(nmea_coordinates_info_t * coordinates,
                                       const uint8_t * data);

static void p2ps_print_coordinates(
    const nmea_coordinates_info_t * coordinates);

// =============================================================================
// Public function definitions
// =============================================================================

void p2ps_protocol_init(void)
{
    rfm95w_register_received_message_callback(p2ps_handle_received_message);

    frame_number = 0;
    my_address = flash_read_dword(FLASH_INDEX_LORA_ADDRESS_MSB);

    initialized = true;
    debug_log_append_line("LORA P2PS initialized");
}

bool p2ps_protocol_is_active(void)
{
    return initialized;
}

// =============================================================================
// Private function definitions
// =============================================================================

static void p2ps_handle_received_message(const uint8_t * data,
                                         uint8_t length,
                                         int16_t rssi)
{
    uint8_t i;
    p2p_frame_header_t header;
    char * p = g_uart_string_buffer;

    sprintf(g_uart_string_buffer, "Received: ");
    p += strlen(g_uart_string_buffer);

    for (i = 0; i != length; ++i)
    {
        sprintf(p, "%02X ", data[i]);
        p += 3;
    }

    sprintf(p, "RSSI = %d", rssi);

    debug_log_append_line(g_uart_string_buffer);

    p2ps_parse_header(&header, data);

    if (true)//(P2P_BROADCAST_ADDRESS == header.destination_address) ||
        //(my_address == header.destination_address))
    {
        nmea_coordinates_info_t coordinates;

        p2ps_parse_gps_coordinates(&coordinates,
                                   &data[P2P_INDEX_APPLICATION]);

        p2ps_print_coordinates(&coordinates);
    }
}

static void p2ps_parse_header(p2p_frame_header_t * header,
                              const uint8_t * data)
{
    header->source_address  = 0;
    header->source_address |= ((uint32_t)data[P2P_INDEX_SOURCE + 0]) << 24;
    header->source_address |= ((uint32_t)data[P2P_INDEX_SOURCE + 1]) << 16;
    header->source_address |= ((uint32_t)data[P2P_INDEX_SOURCE + 2]) <<  8;
    header->source_address |= ((uint32_t)data[P2P_INDEX_SOURCE + 3]) <<  0;

    header->destination_address  = 0;
    header->destination_address |= ((uint32_t)data[P2P_INDEX_DESTINATION + 0]) << 24;
    header->destination_address |= ((uint32_t)data[P2P_INDEX_DESTINATION + 1]) << 16;
    header->destination_address |= ((uint32_t)data[P2P_INDEX_DESTINATION + 2]) <<  8;
    header->destination_address |= ((uint32_t)data[P2P_INDEX_DESTINATION + 3]) <<  0;

    header->frame_number = data[P2P_INDEX_FRAME_NUMBER];
    header->time_to_live = data[P2P_INDEX_TIME_TO_LIVE];
    header->protocol = data[P2P_INDEX_PROTOCOL];
    header->data_type = data[P2P_INDEX_DATA_TYPE];
}

static void p2ps_parse_gps_coordinates(nmea_coordinates_info_t * coordinates,
                                       const uint8_t * data)
{
    uint8_t * minutes_pointer;

    coordinates->latitude_north = (0 != (data[P2P_GPS_INDEX_LATITUDE_DEG + 0] & 0x80));

    coordinates->latitude_deg = (uint16_t)(data[P2P_GPS_INDEX_LATITUDE_DEG + 0] & 0x7F) << 8;
    coordinates->latitude_deg |= (uint16_t)(data[P2P_GPS_INDEX_LATITUDE_DEG + 1]);

    coordinates->longitude_east = (0 != (data[P2P_GPS_INDEX_LONGITUDE_DEG + 0] & 0x80));

    coordinates->longitude_deg = (uint16_t)(data[P2P_GPS_INDEX_LONGITUDE_DEG + 0] & 0x7F) << 8;
    coordinates->longitude_deg |= (uint16_t)(data[P2P_GPS_INDEX_LONGITUDE_DEG + 1]);

    minutes_pointer = (uint8_t*)&(coordinates->latitude_minutes);

    *(minutes_pointer + 0) = data[P2P_GPS_INDEX_LATITUDE_MINUTES + 0];
    *(minutes_pointer + 1) = data[P2P_GPS_INDEX_LATITUDE_MINUTES + 1];
    *(minutes_pointer + 2) = data[P2P_GPS_INDEX_LATITUDE_MINUTES + 2];
    *(minutes_pointer + 3) = data[P2P_GPS_INDEX_LATITUDE_MINUTES + 3];

    minutes_pointer = (uint8_t*)&(coordinates->longitude_minutes);

    *(minutes_pointer + 0) = data[P2P_GPS_INDEX_LONGITUDE_MINUTES + 0];
    *(minutes_pointer + 1) = data[P2P_GPS_INDEX_LONGITUDE_MINUTES + 1];
    *(minutes_pointer + 2) = data[P2P_GPS_INDEX_LONGITUDE_MINUTES + 2];
    *(minutes_pointer + 3) = data[P2P_GPS_INDEX_LONGITUDE_MINUTES + 3];

    coordinates->time_of_fix_hours = data[P2P_GPS_INDEX_TOF_HOURS];
    coordinates->time_of_fix_minutes = data[P2P_GPS_INDEX_TOF_MINUTES];
    coordinates->time_of_fix_seconds = data[P2P_GPS_INDEX_TOD_SECONDS];
}

static void p2ps_print_coordinates(
    const nmea_coordinates_info_t * coordinates)
{
    char ns = 'N';
    char ew = 'E';

    if (coordinates->latitude_north)
    {
        ns = 'N';
    }
    else
    {
        ns = 'S';
    }

    if (coordinates->longitude_east)
    {
        ew = 'E';
    }
    else
    {
        ew = 'W';
    }


    sprintf(g_uart_string_buffer,
            "GPS COORDINTATE: %u%c %.4f' %c, %u%c %.4f' %c %02u:%02u:%02u\r\n",
            coordinates->latitude_deg,
            176,
            (double)coordinates->latitude_minutes,
            ns,
            coordinates->longitude_deg,
            176,
            (double)coordinates->longitude_minutes,
            ew,
            coordinates->time_of_fix_hours,
            coordinates->time_of_fix_minutes,
            coordinates->time_of_fix_seconds
            );

    uart_write_string(g_uart_string_buffer);
}

