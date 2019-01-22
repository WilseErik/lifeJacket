// =============================================================================
// Include statements
// =============================================================================

#include <xc.h>

#include <stdint.h>
#include <stdbool.h>

#include "gps/jf2_io.h"
#include "hal/clock.h"
#include "hal/gpio.h"

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


// =============================================================================
// Public function definitions
// =============================================================================

void jf2_io_send_on_pulse(void)
{
    // From: JF2 Hardware User Guide
    // Document number: 1vv0300985 Rev. 5
    //
    // The ON-OFF signal is normally low. When it transitions high, it should
    // stay high for a time equivalent to a minimum of 3 RTC clock cycles.
    // The signal should then transition low and remain low until the next
    // change in power state is desired.
    //
    // RTC = 32.678kHz => 3RTC clock cycles = 0.1ms

    //
    // ON-OFF pulse can not be sent before the RTC startup time has finished.
    // Typ: 300ms, Max: 5000ms
    //

    uint16_t i;

    GPS_ON_OFF_PIN = 1;

    for (i = 0; i != 2; ++i)
    {
        uint32_t start_time = clock_get_msec();

        while (clock_get_msec() == start_time)
        {
            ;
        }
    }

    GPS_ON_OFF_PIN = 0;
}

// =============================================================================
// Private function definitions
// =============================================================================
