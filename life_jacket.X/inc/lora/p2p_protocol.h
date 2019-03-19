#ifndef P2P_PROTOCOL_H
#define P2P_PROTOCOL_H

/*
This file handles the Point to Point (P2P) protocol.
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
    P2P_INDEX_DESTINATION   = 4,
    P2P_INDEX_TIME_TO_LIVE  = 8,
    P2P_INDEX_FRAME_NUMBER  = 9,
    P2P_INDEX_PROTOCOL      = 10,
    P2P_INDEX_DATA_TYPE     = 11,
    P2P_INDEX_APPLICATION   = 12,
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
// Global variable declarations
// =============================================================================
    
// =============================================================================
// Global constatants
// =============================================================================

// =============================================================================
// Public function declarations
// =============================================================================

#ifdef  __cplusplus
}
#endif

#endif  /* P2P_PROTOCOL_H */

