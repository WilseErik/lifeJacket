// =============================================================================
// Include statements
// =============================================================================

#include "hal/clock.h"

#include <stdint.h>
#include <stdbool.h>

#include <xc.h>

#include "status.h"

// =============================================================================
// Private type definitions
// =============================================================================

// =============================================================================
// Global variables
// =============================================================================

volatile uint16_t g_clock_gps_on_event_timeout;

// =============================================================================
// Private constants
// =============================================================================

//
// HW constants
//

static uint32_t TIMER_CLOCK_FREQ_HZ = CLOCK_HAL_PCBCLOCK_FREQ;
static uint32_t MSEC_TIMER_FREQ_HZ = 1000;


#define TCKPS_ONE_TO_ONE_PRESCALE                       0
#define TCKPS_ONE_TO_EIGHT_PRESCALE                     1
#define TCKPS_ONE_TO_SIXTYFOUR_PRESCALE                 2
#define TCKPS_ONE_TO_TWOHUNDRED_AND_FIFTYSIX_PRESCALE   3

#define TCS_INTERNAL_CLOCK                              0

// =============================================================================
// Private variables
// =============================================================================

static volatile uint32_t current_time = 0;

// =============================================================================
// Private function declarations
// =============================================================================

// =============================================================================
// Public function definitions
// =============================================================================

void clock_start_msec_timer(void)
{
    uint32_t counts;

    T1CON = 0x0000;
    T1CONbits.TON = 1;

    counts = TIMER_CLOCK_FREQ_HZ / MSEC_TIMER_FREQ_HZ;

    if ((counts / 1) < UINT16_MAX)
    {
        T1CONbits.TCKPS = TCKPS_ONE_TO_ONE_PRESCALE;
        PR1 = counts / 1;
    }
    else if ((counts / 8) < UINT16_MAX)
    {
        T1CONbits.TCKPS = TCKPS_ONE_TO_EIGHT_PRESCALE;
        PR1 = counts / 8;
    }
    else if ((counts / 64) < UINT16_MAX)
    {
        T1CONbits.TCKPS = TCKPS_ONE_TO_SIXTYFOUR_PRESCALE;
        PR1 = counts / 64;
    }
    else
    {
        T1CONbits.TCKPS = TCKPS_ONE_TO_TWOHUNDRED_AND_FIFTYSIX_PRESCALE;
        PR1 = counts / 256;
    }

    T1CONbits.TCS = TCS_INTERNAL_CLOCK;

    IEC0bits.T1IE = 1;  // Enable interrupt generation of timer 1
    IPC0bits.T1IP = 4;  // Set isr priority
}

uint32_t clock_get_msec(void)
{
    volatile uint32_t t1;
    volatile uint32_t t2;

    // Avoid incorrect readings of current_time due to preemption by T1 isr.
    do
    {
        t1 = current_time;
        t2 = current_time;
    }
    while (t1 != t2);

    return t1;
}

// =============================================================================
// Private function definitions
// =============================================================================

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0;

    if (g_clock_gps_on_event_timeout)
    {
        --g_clock_gps_on_event_timeout;

        if (!g_clock_gps_on_event_timeout)
        {
            status_set(STATUS_GPS_ON_EVENT, true);
        }
    }

    ++current_time;
}