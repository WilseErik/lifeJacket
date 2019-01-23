// =============================================================================
// Include statements
// =============================================================================

#include <xc.h>

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "gps/nmea.h"
#include "gps/nmea_queue.h"

#include "hal/uart.h"

// =============================================================================
// Private type definitions
// =============================================================================

typedef enum
{
    NMEA_MODE_INDICATOR_AUTONOMOUS          = 'A',
    NMEA_MODE_INDICATOR_DIFFERENTAL         = 'D',
    NMEA_MODE_INDICATOR_ESTIMATED           = 'E',
    NMEA_MODE_INDICATOR_MANUAL              = 'M',
    NMEA_MODE_INDICATOR_SIMULATOR           = 'S',
    NMEA_MODE_INDICATOR_DATA_NOT_VALID      = 'N'
} nmea_mode_indicator_t;

typedef enum
{
    NMEA_GPS_QUALITY_INDICATOR_NO_FIX           = '0',
    NMEA_GPS_QUALITY_INDICATOR_SPS_MODE         = '1',
    NMEA_GPS_QUALITY_INDICATOR_DIFF_SPS_MODE    = '2',
    NMEA_GPS_QUALITY_INDICATOR_PPS_MODE         = '3',
    NMEA_GPS_QUALITY_INDICATOR_RT_KINEMATIC     = '4',
    NMEA_GPS_QUALITY_INDICATOR_FLOAT_RTK        = '5',
    NMEA_GPS_QUALITY_INDICATOR_DEAD_RECKONING   = '6',
    NMEA_GPS_QUALITY_INDICATOR_MANUAL_INPUT     = '7',
    NMEA_GPS_QUALITY_INDICATOR_SIMULATOR        = '8'
} nmea_gps_quality_indicator_t;

typedef enum
{
    NMEA_RMC_FIELD_MNEMONIC                 = 0,
    NMEA_RMC_FIELD_UTC                      = 1,
    NMEA_RMC_FIELD_STATUS                   = 2,
    NMEA_RMC_FIELD_LATITUDE_VAL             = 3,
    NMEA_RMC_FIELD_LATITUDE_NS              = 4,
    NMEA_RMC_FIELD_LONGITUDE_VAL            = 5,
    NMEA_RMC_FIELD_LONGITUDE_EW             = 6,
    NMEA_RMC_FIELD_SPEED_OVER_GROUND        = 7,
    NMEA_RMC_FIELD_COURSE_OVER_GROUND       = 8,
    NMEA_RMC_FIELD_DATE                     = 9,
    NMEA_RMC_FIELD_MAGNETIC_VARIATION_DEG   = 10,
    NMEA_RMC_FIELD_MAGNETIC_VARIATION_EW    = 11,
    NMEA_RMC_FIELD_MODE_INDICATOR           = 12
} nmea_rmc_field_t;

typedef enum
{
    NMEA_GGA_FIELD_MNEMONIC                 = 0,
    NMEA_GGA_FIELD_UTC                      = 1,
    NMEA_GGA_FIELD_LATITUDE_VAL             = 2,
    NMEA_GGA_FIELD_LATITUDE_NS              = 3,
    NMEA_GGA_FIELD_LONGITUDE_VAL            = 4,
    NMEA_GGA_FIELD_LONGITUDE_EW             = 5,
    NMEA_GGA_FIELD_GPS_QUALITY              = 6,
    NMEA_GGA_FIELD_SATELLITE_COUNT          = 7,
    NMEA_GGA_FIELD_HORIZONTAL_PRECISION     = 8,
    NMEA_GGA_FIELD_ALTITUDE                 = 9,
    NMEA_GGA_FIELD_ALTITUDE_METERS          = 10,
    NMEA_GGA_FIELD_GEOIDAL_SEPARATION       = 11,
    NMEA_GGA_FIELD_GEOIDAL_SEPARATION_METERS= 12,
    NMEA_GGA_FIELD_AGE_OF_DIFF_GPS_DATA     = 13,
    NMEA_GGA_FIELD_DIFF_REF_STATION_ID      = 14
} nmea_gga_field_t;

#define LATITUDE_STR_LEN    (11)
#define LONGITUDE_STR_LEN   (11)

typedef struct nmea_position_info_t
{
    char latitude[LATITUDE_STR_LEN];
    char latitude_ns;
    char longitude[LONGITUDE_STR_LEN];
    char longitude_ew;
    char time_of_fix[9];
} nmea_position_info_t;

// =============================================================================
// Global variables
// =============================================================================

// =============================================================================
// Private constants
// =============================================================================

static const char NMEA_START_CHAR = '$';
static const char NMEA_CHECKSUM_CHAR = '*';
static const char NMEA_FIELD_SEPERATOR = ',';

static const char NMEA_STATUS_LOCKED = 'A';
static const char NMEA_STATUS_WARNING = 'V';

#define NMEA_MNEMONIC_CODE_LEN (3)
#define NMEA_UTC_FIELD_LEN (9)

#define NMEA_RMC_FIELD_COUNT (13)
#define NMEA_GGA_FIELD_COUNT (15)

// =============================================================================
// Private variables
// =============================================================================

static bool is_locked = false;
static nmea_position_info_t position_info;

static nmea_mode_indicator_t            mode_indicator;
static nmea_gps_quality_indicator_t     gps_quality_indicator;

// =============================================================================
// Private function declarations
// =============================================================================

/**
 @brief Checks if the checksum of a message is correct.
 @param message     - Message which checksum to check.
 @return True if the checksum was correct.
*/
static bool nmea_is_checksum_ok(char * message);

/**
 @brief Parses a NMEA output message.
 @param message     - Message to parse.
*/
static void nmea_parse_message(char * message);

/**
 @brief Returns a pointer to the start of the next field in a NMEA message.
 @param message     - Start of the current NMEA field.
 @param message_end - End of message.
*/
static char * nmea_next_field(char * message, char * message_end);

/**
 @brief Finds the end of a NMEA message.
 @param message     - Message to find the end of.
*/
static char * nmea_find_end_of_message(char * message);

/**
 @brief Handles a global positioning system fix data message.
 @param message     - Message to handle.
*/
static void nmea_handle_gga_message(char * message);

/**
 @brief Handles a GNSS DOP and active satillites in view message.
 @param message     - Message to handle.
*/
static void nmea_handle_gsa_message(char * message);

/**
 @brief Handles a Recommended minimum specific GNSS data message.
 @param message     - Message to handle.
*/
static void nmea_handle_rmc_message(char * message);

/**
 @brief Handles a GNSS satellites in view message.
 @param message     - Message to handle.
*/
static void nmea_handle_gsv_message(char * message);

// =============================================================================
// Public function definitions
// =============================================================================

void nmea_handle_message(char * message)
{
    if (nmea_is_checksum_ok(message))
    {
        nmea_parse_message(message);
    }
}

void nmea_print_status(void)
{
    uart_write_string("\tMode indicator: ");

    switch (mode_indicator)
    {
    case NMEA_MODE_INDICATOR_AUTONOMOUS:
        uart_write_string("AUTONOMOUS");
        break;

    case NMEA_MODE_INDICATOR_DIFFERENTAL:
        uart_write_string("DIFFERENTAL");
        break;

    case NMEA_MODE_INDICATOR_ESTIMATED:
        uart_write_string("ESTIMATED");
        break;

    case NMEA_MODE_INDICATOR_MANUAL:
        uart_write_string("MANUAL");
        break;

    case NMEA_MODE_INDICATOR_SIMULATOR:
        uart_write_string("SIMULATOR");
        break;

    case NMEA_MODE_INDICATOR_DATA_NOT_VALID:
        uart_write_string("DATA NOT VALID");
        break;
    }

    uart_write_string("\r\n\tQuality indicator: ");

    switch (gps_quality_indicator)
    {
    case NMEA_GPS_QUALITY_INDICATOR_NO_FIX:
        uart_write_string("FIX NOT AVAILABLE OR INVALID");
        break;

    case NMEA_GPS_QUALITY_INDICATOR_SPS_MODE:
        uart_write_string("SPS MODE, FIX VALID");
        break;

    case NMEA_GPS_QUALITY_INDICATOR_DIFF_SPS_MODE:
        uart_write_string("DIFFERENTIAL GPS, SPS MODE, FIX VALID");
        break;

    case NMEA_GPS_QUALITY_INDICATOR_PPS_MODE:
        uart_write_string("GPS PPS MODE, FIX VALID");
        break;

    case NMEA_GPS_QUALITY_INDICATOR_RT_KINEMATIC:
        uart_write_string("REAL TIME KINEMATIC");
        break;

    case NMEA_GPS_QUALITY_INDICATOR_FLOAT_RTK:
        uart_write_string("FLOAT REAL TIME KINEMATIC");
        break;

    case NMEA_GPS_QUALITY_INDICATOR_DEAD_RECKONING:
        uart_write_string("ESTIMATED MODE");
        break;

    case NMEA_GPS_QUALITY_INDICATOR_MANUAL_INPUT:
        uart_write_string("MANUAL INPUT MODE");
        break;

    case NMEA_GPS_QUALITY_INDICATOR_SIMULATOR:
        uart_write_string("SIMULATOR MODE");
        break;
    }

    uart_write_string("\r\n\tLocked: ");

    if (is_locked)
    {
        uart_write_string("true");
    }
    else
    {
        uart_write_string("false");
    }

    uart_write_string("\r\n\tLatitude: ");
    uart_write_string(position_info.latitude);
    uart_write_string(" ");
    uart_write(position_info.latitude_ns);
    uart_write_string("\r\n\tLongitude: ");
    uart_write_string(position_info.longitude);
    uart_write_string(" ");
    uart_write(position_info.longitude_ew);
    uart_write_string("\r\n\tTime of fix (UTC): ");
    uart_write_string(position_info.time_of_fix);
    uart_write_string("\r\n");
}

// =============================================================================
// Private function definitions
// =============================================================================

static bool nmea_is_checksum_ok(char * message)
{
    bool checksum_ok = true;
    char * checksum_str;
    uint8_t checksum;

    if (NMEA_START_CHAR != message[0])
    {
        checksum_ok = false;
    }

    if (checksum_ok)
    {
        checksum_str = memchr(message,
                              NMEA_CHECKSUM_CHAR,
                              NMEA_MAX_MESSAGE_LENGTH - 2);

        checksum_ok = checksum_ok && (NULL != checksum_str);
    }

    if (checksum_ok)
    {
        checksum_ok = checksum_ok && isdigit(checksum_str[1]);
        checksum_ok = checksum_ok && isdigit(checksum_str[2]);
    }

    if (checksum_ok)
    {
        uint8_t calculated_checksum;

        char * m = message + 1;
        calculated_checksum = *m++;

        while (m != checksum_str)
        {
            calculated_checksum ^= *m++;
        }

        checksum = strtol(checksum_str + 1, NULL, 16);

        checksum_ok = (checksum == calculated_checksum);
    }

    return checksum_ok;
}

static void nmea_parse_message(char * message)
{
    char mnemonic_code[NMEA_MNEMONIC_CODE_LEN + 1];

    mnemonic_code[0] = message[3];
    mnemonic_code[1] = message[4];    
    mnemonic_code[2] = message[5];
    mnemonic_code[3] = 0;

    if (0 == strcmp(mnemonic_code, "GGA"))
    {
        nmea_handle_gga_message(message);
    }
    else if (0 == strcmp(mnemonic_code, "GSA"))
    {
        nmea_handle_gsa_message(message);
    }
    else if (0 == strcmp(mnemonic_code, "RMC"))
    {
        nmea_handle_rmc_message(message);
    }
    else if (0 == strcmp(mnemonic_code, "GSV"))
    {
        nmea_handle_gsv_message(message);
    }
}

static char * nmea_next_field(char * message, char * message_end)
{
    char * m;

    m = memchr(message, NMEA_FIELD_SEPERATOR, message_end - message + 1);

    return m + 1;
}

static char * nmea_find_end_of_message(char * message)
{
    return memchr(message, NMEA_CHECKSUM_CHAR, NMEA_MAX_MESSAGE_LENGTH + 3);
}

static void nmea_handle_gga_message(char * message)
{
    char * fields[NMEA_GGA_FIELD_COUNT];
    char * message_end = nmea_find_end_of_message(message);
    uint16_t i;

    fields[0] = message;

    for (i = 1; i != NMEA_GGA_FIELD_COUNT; ++i)
    {
        fields[i] = nmea_next_field(fields[i - 1], message_end);
    }

    gps_quality_indicator = *fields[NMEA_GGA_FIELD_GPS_QUALITY];

    is_locked =
        (NMEA_GPS_QUALITY_INDICATOR_SPS_MODE == gps_quality_indicator) ||
        (NMEA_GPS_QUALITY_INDICATOR_DIFF_SPS_MODE == gps_quality_indicator) ||
        (NMEA_GPS_QUALITY_INDICATOR_PPS_MODE == gps_quality_indicator);

    if (is_locked)
    {
        uint16_t latitude_field_len;
        uint16_t longitude_field_len;

        latitude_field_len = fields[NMEA_GGA_FIELD_LATITUDE_VAL + 1] -
            fields[NMEA_GGA_FIELD_LATITUDE_VAL] - 1;

        memset(position_info.latitude, 0, LATITUDE_STR_LEN);
        memcpy(position_info.latitude,
               fields[NMEA_GGA_FIELD_LATITUDE_VAL],
               latitude_field_len);

        position_info.latitude_ns = *fields[NMEA_GGA_FIELD_LATITUDE_NS];

        longitude_field_len = fields[NMEA_GGA_FIELD_LONGITUDE_VAL + 1] -
            fields[NMEA_GGA_FIELD_LONGITUDE_VAL] - 1;

        memset(position_info.longitude, 0, LONGITUDE_STR_LEN);
        memcpy(position_info.longitude,
               fields[NMEA_GGA_FIELD_LONGITUDE_VAL],
               longitude_field_len);

        position_info.longitude_ew = *fields[NMEA_GGA_FIELD_LONGITUDE_EW];

        memcpy(position_info.time_of_fix,
               fields[NMEA_GGA_FIELD_UTC],
               NMEA_UTC_FIELD_LEN);
    }
}

static void nmea_handle_gsa_message(char * message)
{
    // GNSS DOP and Active Satellites message
    ;
}

static void nmea_handle_rmc_message(char * message)
{
    char * fields[NMEA_RMC_FIELD_COUNT];
    char * message_end = nmea_find_end_of_message(message);
    uint16_t i;

    fields[0] = message;

    for (i = 1; i != NMEA_RMC_FIELD_COUNT; ++i)
    {
        fields[i] = nmea_next_field(fields[i - 1], message_end);
    }

    is_locked = (NMEA_STATUS_LOCKED == *fields[NMEA_RMC_FIELD_STATUS]);

    if (is_locked)
    {
        uint16_t latitude_field_len;
        uint16_t longitude_field_len;

        latitude_field_len = fields[NMEA_RMC_FIELD_LATITUDE_VAL + 1] -
            fields[NMEA_RMC_FIELD_LATITUDE_VAL] - 1;

        memset(position_info.latitude, 0, LATITUDE_STR_LEN);
        memcpy(position_info.latitude,
               fields[NMEA_RMC_FIELD_LATITUDE_VAL],
               latitude_field_len);

        position_info.latitude_ns = *fields[NMEA_RMC_FIELD_LATITUDE_NS];

        longitude_field_len = fields[NMEA_RMC_FIELD_LONGITUDE_VAL + 1] -
            fields[NMEA_RMC_FIELD_LONGITUDE_VAL] - 1;

        memset(position_info.longitude, 0, LONGITUDE_STR_LEN);
        memcpy(position_info.longitude,
               fields[NMEA_RMC_FIELD_LONGITUDE_VAL],
               longitude_field_len);

        position_info.longitude_ew = *fields[NMEA_RMC_FIELD_LONGITUDE_EW];

        memcpy(position_info.time_of_fix,
               fields[NMEA_RMC_FIELD_UTC],
               NMEA_UTC_FIELD_LEN);

        mode_indicator =
            (nmea_mode_indicator_t)*fields[NMEA_RMC_FIELD_MODE_INDICATOR];
    }
}

static void nmea_handle_gsv_message(char * message)
{
    // GNSS Satellites in View message
}

