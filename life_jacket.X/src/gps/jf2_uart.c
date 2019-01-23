/*
 * This file handes the UART module.
 *
 * References:
 * - PIC24FJ64GA006 datasheet, document number DS39747D, page 139
 */

// =============================================================================
// Include statements
// =============================================================================

#include <xc.h>

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "gps/jf2_uart.h"
#include "gps/nmea_queue.h"
#include "hal/gpio.h"
#include "hal/clock.h"
#include "status.h"

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
#define BUFFER_SIZE     ((uint16_t)256)
#define BACKSPACE_CHAR  (0x08)

static const uint32_t UART_BAUD = 9600;
static const uint32_t PERIPHERAL_FREQ = CLOCK_HAL_PCBCLOCK_FREQ;

static const uint8_t COMMAND_START_CHAR = '$';
static const uint8_t COMMAND_TERMINATION_CHAR = '\r';

// =============================================================================
// Private variables
// =============================================================================
static bool uart_initialized = false;

static volatile uint8_t rx_buff[BUFFER_SIZE];
static volatile uint8_t tx_buff[BUFFER_SIZE];

static volatile uint16_t rx_buff_first = 0;
static volatile uint16_t rx_buff_last = 0;
static volatile uint16_t tx_buff_first = 0;
static volatile uint16_t tx_buff_last = 0;

static volatile uint16_t rx_buff_size = 0;
static volatile uint16_t tx_buff_size = 0;

static volatile bool receiving_message = false;
static char rx_message[NMEA_MAX_MESSAGE_LENGTH];

static volatile bool debug_echo_enabled = false;
// =============================================================================
// Private function declarations
// =============================================================================

/**
 * @brief Starts transmission of the tx buffer.
 * @param void
 * @return void
 */
static void start_tx(void);

// =============================================================================
// Public function definitions
// =============================================================================

void jf2_uart_init()
{
    volatile int16_t wait_cnt = 0;

    if (false == uart_initialized)
    {
        //
        // Variables
        //
        rx_buff_first = 0;
        rx_buff_last = 0;
        tx_buff_first = 0;
        tx_buff_last = 0;

        rx_buff_size = 0;
        tx_buff_size = 0;

        //
        // IO ports
        //
        GPS_TXD_DIR = DIR_OUT;
        GPS_RXD_DIR = DIR_IN;

        //
        // UART module
        //
        U1MODE = 0x0000;
        U1STA = 0x0000;

        U1BRG = (PERIPHERAL_FREQ / UART_BAUD) / 16 - 1;

        U1MODEbits.PDSEL = 0;  // 8 bit data, no parity
        U1MODEbits.STSEL = 0;  // 1 Stop bit
        U1MODEbits.URXINV = 1; // Idle state low

        // Interrupt is generated when any character is transfered to the
        // Transmit Shift Register and the hw transmit buffer is empty.
        U1STAbits.UTXISEL0 = 0;
        U1STAbits.UTXISEL1 = 0;
        IPC3bits.U1TXIP = 2;  // Interrupt priority
        IEC0bits.U1TXIE = 1;  // TX interrupt enable

        // Interrupt is generated each time a data word is transfered from
        // the U1RSR to the receive buffer. There may be one or more characters
        // in the receive buffer.
        U1STAbits.URXISEL = 0;
        IPC2bits.U1RXIP = 2;  // Interrupt priority
        IEC0bits.U1RXIE = 1;  // RX interrupt enable

        U1MODEbits.UARTEN = 1;
        U1STAbits.UTXEN = 1;

        for (wait_cnt = 0; wait_cnt != PERIPHERAL_FREQ / UART_BAUD; ++wait_cnt)
        {
            ;
        }

        debug_echo_enabled = false;
        uart_initialized = true;
    }
}

void jf2_uart_write(uint8_t data)
{
    if ((0 == tx_buff_size) && (0 == U1STAbits.UTXBF))
    {
        // hw transmit buffer not full but tx buffer is.
        U1TXREG = data;
    }
    else if (tx_buff_size < BUFFER_SIZE)
    {
        if (0 != tx_buff_size)
        {
            ++tx_buff_last;

            if (tx_buff_last >= BUFFER_SIZE)
            {
                tx_buff_last = 0;
            }
        }

        tx_buff[tx_buff_last] = data;

        ++tx_buff_size;
    }
}

void jf2_uart_write_string(const char* data)
{
    const uint8_t* p = (const uint8_t*)data;

    // Update the tx buffer.
    while (*p && (tx_buff_size < BUFFER_SIZE))
    {
        if (0 != tx_buff_size)
        {
            ++tx_buff_last;

            if (tx_buff_last >= BUFFER_SIZE)
            {
                tx_buff_last = 0;
            }
        }

        tx_buff[tx_buff_last] = *(p++);

        ++tx_buff_size;
    }

    start_tx();
}

void jf2_uart_write_array(uint16_t nbr_of_bytes, const uint8_t* data)
{
    uint16_t i;

    // Update the tx buffer.
    for (i = 0; i != nbr_of_bytes; ++i)
    {
        if (tx_buff_size < BUFFER_SIZE)
        {
            if (0 != tx_buff_size)
            {
                ++tx_buff_last;

                if (tx_buff_last >= BUFFER_SIZE)
                {
                    tx_buff_last = 0;
                }
            }

            tx_buff[tx_buff_last] = *(data++);

            if (tx_buff_size < BUFFER_SIZE)
            {
                ++tx_buff_size;
            }
        }
    }

    start_tx();
}

bool jf2_uart_is_write_buffer_empty(void)
{
    return tx_buff_size == 0;
}

uint8_t jf2_uart_get(uint16_t index)
{
    uint16_t i;
    uint8_t data;

    jf2_uart_disable_rx_interrupt();

    i = rx_buff_first + index;

    if (i >= BUFFER_SIZE)
    {
        i -= BUFFER_SIZE;
    }

    data = rx_buff[i];

    jf2_uart_enable_rx_interrupt();

    return data;
}

uint16_t jf_uart_get_receive_buffer_size(void)
{
    return rx_buff_size;
}

bool jf2_uart_is_receive_buffer_empty(void)
{
    return (0 == rx_buff_size);
}

void jf2_uart_clear_receive_buffer(void)
{
    jf2_uart_disable_rx_interrupt();

    rx_buff_size = 0;
    rx_buff_first = 0;
    rx_buff_last = 0;

    jf2_uart_enable_rx_interrupt();
}

void jf2_uart_enable_debug_uart_echo(bool enable)
{
    debug_echo_enabled = enable;
}


// =============================================================================
// Private function definitions
// =============================================================================

void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void)
{
    while ((0 == U1STAbits.UTXBF) && (0 != tx_buff_size))
    {
        // TX fifo not full and there are more things to send
        U1TXREG = tx_buff[tx_buff_first];

        if (1 != tx_buff_size)
        {
            ++tx_buff_first;
        }

        if (tx_buff_first >= BUFFER_SIZE)
        {
            tx_buff_first = 0;
        }

        --tx_buff_size;
    }

    IFS0bits.U1TXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    uint8_t received;

    jf2_uart_disable_tx_interrupt();

    if (U1STAbits.OERR)
    {
        U1STAbits.OERR = 0;
    }

    while (U1STAbits.URXDA)
    {
        received = U1RXREG;

        if (debug_echo_enabled)
        {
            uart_write(received);
        }

        if (!receiving_message &&
            (COMMAND_START_CHAR == received))
        {
            receiving_message = true;
        }

        if (receiving_message)
        {
            if (0 != rx_buff_size)
            {
                ++rx_buff_last;

                if (rx_buff_last >= BUFFER_SIZE)
                {
                    rx_buff_last = 0;
                }
            }

            rx_buff[rx_buff_last] = received;

            ++rx_buff_size;
            
            if (COMMAND_TERMINATION_CHAR == received)
            {
                uint16_t current_index = 0;

                for (current_index = 0; current_index != rx_buff_size; ++current_index)
                {
                    rx_message[current_index] = (char)jf2_uart_get(current_index);
                }

                rx_message[current_index] = NULL;

                nmea_queue_append(nmea_queue_get_rx_queue(),
                                  rx_message,
                                  rx_buff_size);

                receiving_message = false;
                jf2_uart_clear_receive_buffer();
            }
            else if (rx_buff_size > NMEA_MAX_MESSAGE_LENGTH)
            {
                receiving_message = false;
                jf2_uart_clear_receive_buffer();
            }
        }
    }

    jf2_uart_enable_tx_interrupt();

    IFS0bits.U1RXIF = 0;
}

static void start_tx(void)
{
    jf2_uart_disable_tx_interrupt();
    jf2_uart_disable_rx_interrupt();

    while ((0 != tx_buff_size) && (0 == U1STAbits.UTXBF))
    {
        U1TXREG = tx_buff[tx_buff_first];

        if (1 != tx_buff_size)
        {
            ++tx_buff_first;
        }

        if (tx_buff_first >= BUFFER_SIZE)
        {
            tx_buff_first = 0;
        }

        --tx_buff_size;
    }

    jf2_uart_enable_tx_interrupt();
    jf2_uart_enable_rx_interrupt();
}

