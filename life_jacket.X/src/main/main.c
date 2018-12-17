// =============================================================================
// Include statements
// =============================================================================

#include <xc.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "hal/gpio.h"
#include "hal/flash.h"
#include "acc/accelerometer.h"
#include "lora/rfm95w.h"
#include "audio/ext_flash.h"
#include "audio/pcm1770.h"
#include "hal/clock.h"
#include "hal/uart.h"

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
    init();


    while (1)
    {
        ClrWdt();
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

    uart_init();
    print_start_message(reset_reason);

    flash_init();

    clock_start_msec_timer();

    rfm95w_init();
    accelerometer_init();
    ext_flash_init();
    pcm1770_init();
}

static void print_start_message(uint16_t reset_reason)
{
    uart_write_string("\r\n\r\n");
    uart_write_string("Life jacket tracker V1.0.0\r\n");
    uart_write_string("Last compiled ");
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
        RCONbits.WDTO = 0;
        uart_write_string("\r\n\tWatchdog timeout reset");
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