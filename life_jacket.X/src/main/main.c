// =============================================================================
// Include statements
// =============================================================================

#include <xc.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "status.h"
#include "build_number.h"

#include "hal/gpio.h"
#include "hal/flash.h"
#include "hal/clock.h"
#include "hal/uart.h"

#include "acc/accelerometer.h"

#include "lora/rfm95w.h"
#include "lora/lora_tx_queue.h"
#include "lora/p2pc_protocol.h"
#include "lora/p2ps_protocol.h"

#include "audio/ext_flash.h"
#include "audio/pcm1770.h"

#include "uart/terminal.h"
#include "uart/debug_log.h"

#include "gps/jf2_io.h"
#include "gps/jf2_uart.h"
#include "gps/nmea_queue.h"
#include "gps/nmea.h"
#include "gps/gps.h"

#include "audio/audio.h"

// =============================================================================
// Private type definitions
// =============================================================================

// =============================================================================
// Global variables
// =============================================================================

// =============================================================================
// Private constants
// =============================================================================

// =============================================================================
// Private variables
// =============================================================================

// =============================================================================
// Private function declarations
// =============================================================================

static void init(void);

static void print_start_message(uint16_t reset_reason);

// =============================================================================
// Public function definitions
// =============================================================================

int main(int argc, char** argv)
{
    nmea_queue_t nmea_rx_queue;

    init();

    nmea_rx_queue = nmea_queue_get_rx_queue();

    while (1)
    {
        ClrWdt();

        if (status_check(STATUS_UART_RECEIVE_FLAG))
        {
            terminal_handle_uart_event();
            status_clear(STATUS_UART_RECEIVE_FLAG);
        }

        if (status_check(STATUS_GPS_ON_EVENT))
        {
            status_clear(STATUS_GPS_ON_EVENT);
            debug_log_append_line("Sending GPS on pulse");
            jf2_io_send_on_pulse();
        }

        if (nmea_queue_size(nmea_rx_queue))
        {
            nmea_handle_message(nmea_queue_peek(nmea_rx_queue));
            nmea_queue_pop(nmea_rx_queue);
        }

        if (!lora_tx_queue_is_empty() && rfm95w_is_idle())
        {
            lora_tx_queue_transmit_and_pop();
        }

        if (status_check(STATUS_GPS_BROADCAST_EVENT))
        {
            status_clear(STATUS_GPS_BROADCAST_EVENT);
            g_clock_gps_broadcast_timeout_sec = GPS_BROADCAST_INTERVAL_SEC;
            p2pc_protocol_broadcast_gps_position();
            debug_log_append_line("GPS broadcast added to tx queue.");
        }

        gps_poll();

        if (status_check(STATUS_AUDIO_BUFFER_UPDATE_EVENT))
        {
            status_clear(STATUS_AUDIO_BUFFER_UPDATE_EVENT);
            audio_handle_buffer_update();
        }

        if (rfm95w_is_idle() &&
            gps_allows_sleep_mode() &&
            termnial_allows_sleep())
        {
            Sleep();
        }
    }

    return (EXIT_SUCCESS);
}


// =============================================================================
// Private function definitions
// =============================================================================

static void init(void)
{
    uint16_t reset_reason;

    CLKDIVbits.RCDIV = 0;
    reset_reason = RCON;

    gpio_init();
    clock_start_msec_timer();

    uart_init();
    print_start_message(reset_reason);

    flash_init();

    while (!uart_is_write_buffer_empty()){;}
    rfm95w_init();
    while (!uart_is_write_buffer_empty()){;}
    accelerometer_init();
    while (!uart_is_write_buffer_empty()){;}
    ext_flash_init();

    gps_init();

    lora_tx_queue_init();

    if (flash_read_byte(FLASH_INDEX_LORA_P2PS_NOT_P2PC))
    {
        p2ps_protocol_init();
    }
    else
    {
        p2pc_protocol_init();
    }

    clock_start_rtc();

    if (p2pc_protocol_is_active())
    {
        g_clock_gps_broadcast_timeout_sec = GPS_BROADCAST_INTERVAL_SEC;
    }

    if (p2ps_protocol_is_active())
    {
        rfm95w_start_continuous_rx();
    }
}

static void print_start_message(uint16_t reset_reason)
{
    uart_write_string("\r\n\r\n");
    uart_write_string("Life jacket tracker V1.0.0\r\n");
    uart_write_string("Build number: ");
    uart_write_string(BUILD_NUMBER_STRING);
    uart_write_string("\r\nLast compiled ");
    uart_write_string(__DATE__);
    uart_write_string(", ");
    uart_write_string(__TIME__);
    uart_write_string("\r\nReset reason was:");

    if (reset_reason & _RCON_TRAPR_MASK)
    {
        RCONbits.TRAPR = 0;
        uart_write_string("\r\n\tTrap reset");
    }

    if (reset_reason & _RCON_IOPUWR_MASK)
    {
        RCONbits.IOPUWR = 0;
        uart_write_string("\r\n\tIllegal op. code");
    }

    if (reset_reason & _RCON_EXTR_MASK)
    {
        RCONbits.EXTR = 0;
        uart_write_string("\r\n\tExternal reset");
    }

    if (reset_reason & _RCON_SWR_MASK)
    {
        RCONbits.SWR = 0;
        uart_write_string("\r\n\tSoftware reset");
    }

    if (reset_reason & _RCON_WDTO_MASK)
    {
        uint8_t wdt_reset_count;

        wdt_reset_count = flash_read_byte(FLASH_INDEX_WDT_RESETS) + 1;
        flash_init_write_buffer();
        flash_write_byte_to_buffer(FLASH_INDEX_WDT_RESETS, wdt_reset_count);
        flash_write_buffer_to_flash();

        RCONbits.WDTO = 0;
        sprintf(g_uart_string_buffer,
                "\r\n\tWatchdog timeout reset #%u",
                wdt_reset_count);
        uart_write_string(g_uart_string_buffer);


    }

    if (reset_reason & _RCON_BOR_MASK)
    {
        RCONbits.BOR = 0;
        uart_write_string("\r\n\tBrown out reset");
    }

    if (reset_reason & _RCON_POR_MASK)
    {
        RCONbits.POR = 0;
        uart_write_string("\r\n\tPower on reset");
    }

    uart_write_string("\r\nType 'help' for help.\r\n");
}