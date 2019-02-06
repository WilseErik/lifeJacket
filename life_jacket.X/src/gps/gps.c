// =============================================================================
// Include statements
// =============================================================================

#include <xc.h>

#include "gps/gps.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "gps/nmea.h"
#include "gps/nmea_queue.h"
#include "gps/jf2_io.h"
#include "gps/jf2_uart.h"
#include "status.h"
#include "hal/clock.h"

// =============================================================================
// Private type definitions
// =============================================================================

typedef enum
{
    GPS_STATE_COLD_START_PRE_FIX,
    GPS_STATE_COLD_START_POST_FIX,
    GPS_STATE_HOT_START_PRE_FIX,
    GPS_STATE_HOT_START_POST_FIX,
    GPS_STATE_IDLE
} gps_state_t;

// =============================================================================
// Global variables
// =============================================================================

// =============================================================================
// Private constants
// =============================================================================

static const uint16_t GPS_COLD_START_OFF_TIMEOUT_MS = 5000;
static const uint16_t GPS_HOT_START_OFF_TIMEOUT_MS = 1000;
static const uint16_t GPS_HOT_START_INTERVAL_SEC = 60;

// =============================================================================
// Private variables
// =============================================================================

// =============================================================================
// Private function declarations
// =============================================================================

static gps_state_t gps_state;

static nmea_coordinates_info_t coordinates;
static bool coordinates_set = false;

// =============================================================================
// Public function definitions
// =============================================================================

void gps_init(void)
{
    gps_state = GPS_STATE_COLD_START_PRE_FIX;

    nmea_reset_on_lock_event();
    jf2_uart_init();
    nmea_queue_init(nmea_queue_get_rx_queue());
    nmea_queue_init(nmea_queue_get_tx_queue());
    g_clock_gps_on_event_timeout = JF2_IO_RTC_STARTUP_TIME_MS;
}

void gps_poll(void)
{
    if (GPS_STATE_COLD_START_PRE_FIX == gps_state)
    {
        if (nmea_check_on_lock_event())
        {
            g_clock_gps_off_timeout = GPS_COLD_START_OFF_TIMEOUT_MS;
            gps_state = GPS_STATE_COLD_START_POST_FIX;
        }
    }
    if (GPS_STATE_COLD_START_POST_FIX == gps_state)
    {
        if (0 == g_clock_gps_off_timeout)
        {
            jf2_io_send_on_pulse();
            g_clock_gps_hot_start_timeout_sec = GPS_HOT_START_INTERVAL_SEC;
            gps_state = GPS_STATE_IDLE;
        }
    }
    else if (GPS_STATE_HOT_START_PRE_FIX == gps_state)
    {
        if (nmea_check_on_lock_event())
        {
            g_clock_gps_off_timeout = GPS_HOT_START_OFF_TIMEOUT_MS;
            gps_state = GPS_STATE_HOT_START_POST_FIX;
        }
    }
    else if (GPS_STATE_HOT_START_POST_FIX == gps_state)
    {
        if (0 == g_clock_gps_off_timeout)
        {
            nmea_get_coordinates(&coordinates);
            coordinates_set = true;
            jf2_io_send_on_pulse();
            g_clock_gps_hot_start_timeout_sec = GPS_HOT_START_INTERVAL_SEC;
            gps_state = GPS_STATE_IDLE;
        }
    }
    else if (GPS_STATE_IDLE == gps_state)
    {
        if (status_check(STATUS_GPS_HOTSTART_EVENT))
        {
            status_clear(STATUS_GPS_HOTSTART_EVENT);
            nmea_reset_on_lock_event();
            jf2_io_send_on_pulse();
            gps_state = GPS_STATE_HOT_START_PRE_FIX;
        }
    }
}

bool gps_allows_sleep_mode(void)
{
    return (GPS_STATE_IDLE == gps_state);
}

const nmea_coordinates_info_t * gps_get_coordinates(void)
{
    if (coordinates_set)
    {
        return &coordinates;
    }
    else
    {
        return NULL;       
    }
}

// =============================================================================
// Private function definitions
// =============================================================================


