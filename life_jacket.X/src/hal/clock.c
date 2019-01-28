// =============================================================================
// Include statements
// =============================================================================

#include "hal/clock.h"

#include <stdint.h>
#include <stdbool.h>

#include <xc.h>

#include "status.h"

#include "uart/debug_log.h"

// =============================================================================
// Private type definitions
// =============================================================================

// =============================================================================
// Global variables
// =============================================================================

volatile uint16_t g_clock_gps_on_event_timeout;
volatile uint16_t g_clock_gps_off_timeout;
volatile uint16_t g_clock_gps_hot_start_timeout_sec;

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

typedef enum
{
    CLOCK_RTCC_POINTER_YEAR             = 0x3,
    CLOCK_RTCC_POINTER_MONTH_DAY        = 0x2,
    CLOCK_RTCC_POINTER_WEEKDAY_HOUR     = 0x1,
    CLOCK_RTCC_POINTER_MINUTES_SECONDS  = 0x0,
} clock_rtcc_pointer_t;

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

void clock_start_rtc(void)
{
    __builtin_write_RTCWEN();

    RTCPWCbits.RTCLK = 0x01;    // RTCLK = internal LPRC osc

    ALCFGRPTbits.ALRMEN = 0;    // Alarm disable
    ALCFGRPTbits.AMASK = 0x01;  // Alarm every second
    ALCFGRPTbits.ARPT = 255;    // Alarm repeat count
    ALCFGRPTbits.CHIME = 1;     // Repeat alarm indefinitely

    RCFGCALbits.RTCPTR = CLOCK_RTCC_POINTER_YEAR;
    RTCVAL = 0x0000;    // Year = 2000
    RTCVAL = 0x0101;    // Month = 1, day = 1
    RTCVAL = 0x0000;    // Sunday, hour = 0
    RTCVAL = 0x0000;    // Minute = 0, seconds = 0

    ALCFGRPTbits.ALRMPTR = CLOCK_RTCC_POINTER_MONTH_DAY;
    ALRMVAL = 0x0101;   // Month = 1, day = 1
    ALRMVAL = 0x0000;   // Sunday, hour = 0
    ALRMVAL = 0x0002;   // Minute 0, seconds = 2

    IFS3bits.RTCIF = 0;
    IEC3bits.RTCIE = 1;

    ALCFGRPTbits.ALRMEN = 1;    // Alarm enable
    RCFGCALbits.RTCEN = 1;      // RTCC module enable
}

// =============================================================================
// Private function definitions
// =============================================================================


void __attribute__((interrupt, no_auto_psv)) _RTCCInterrupt(void)
{
    IFS3bits.RTCIF = 0;

    if (g_clock_gps_hot_start_timeout_sec)
    {
        --g_clock_gps_hot_start_timeout_sec;

        if (!g_clock_gps_hot_start_timeout_sec)
        {
            status_set(STATUS_GPS_HOTSTART_EVENT, true);
        }
    }
}

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

    if (g_clock_gps_off_timeout)
    {
        --g_clock_gps_off_timeout;
    }

    ++current_time;
}