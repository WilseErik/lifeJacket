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

#include "hal/uart.h"
#include "hal/gpio.h"
#include "hal/clock.h"
#include "status.h"

// =============================================================================
// Private type definitions
// =============================================================================

// =============================================================================
// Global variables
// =============================================================================

char g_uart_string_buffer[UART_STRING_BUFFER_SIZE];

// =============================================================================
// Private constants
// =============================================================================
#define BUFFER_SIZE     ((uint16_t)256)
#define BACKSPACE_CHAR  (0x08)

static const uint32_t UART_BAUD = 38400;
static const uint32_t PERIPHERAL_FREQ = CLOCK_HAL_PCBCLOCK_FREQ;

static const uint8_t COMMAND_TERMINATION_CHAR = '\n';

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

void uart_init()
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

        status_set(STATUS_UART_RECEIVE_FLAG, 0);

        //
        // IO ports
        //
        DEBUG_UART_TX_DIR = DIR_OUT;
        DEBUG_UART_RX_DIR = DIR_IN;

        //
        // UART module
        //
        U2MODE = 0x0000;
        U2STA = 0x0000;

        U2BRG = (PERIPHERAL_FREQ / UART_BAUD) / 16 - 1;

        U2MODEbits.PDSEL = 0; // 8 bit data, no parity
        U2MODEbits.STSEL = 0; // 1 Stop bit

        // Interrupt is generated when any character is transfered to the
        // Transmit Shift Register and the hw transmit buffer is empty.
        U2STAbits.UTXISEL0 = 0;
        U2STAbits.UTXISEL1 = 0;
        IPC7bits.U2TXIP = 2;  // Interrupt priority
        IEC1bits.U2TXIE = 1;  // TX interrupt enable

        // Interrupt is generated each time a data word is transfered from
        // the U1RSR to the receive buffer. There may be one or more characters
        // in the receive buffer.
        U2STAbits.URXISEL = 0;
        IPC7bits.U2RXIP = 2;  // Interrupt priority
        IEC1bits.U2RXIE = 1;  // RX interrupt enable

        U2MODEbits.UARTEN = 1;
        U2STAbits.UTXEN = 1;

        for (wait_cnt = 0; wait_cnt != PERIPHERAL_FREQ / UART_BAUD; ++wait_cnt)
        {
            ;
        }

        uart_initialized = true;
    }
}

void uart_deinit()
{
    if (true == uart_initialized)
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

        status_set(STATUS_UART_RECEIVE_FLAG, 0);

        // Interrupt is generated when any character is transfered to the
        // Transmit Shift Register and the hw transmit buffer is empty.
        U2STAbits.UTXISEL0 = 0;
        U2STAbits.UTXISEL1 = 0;
        IPC7bits.U2TXIP = 2;  // Interrupt priority
        IEC1bits.U2TXIE = 0;  // TX interrupt enable

        // Interrupt is generated each time a data word is transfered from
        // the U1RSR to the receive buffer. There may be one or more characters
        // in the receive buffer.
        U2STAbits.URXISEL = 0;
        IPC7bits.U2RXIP = 2;  // Interrupt priority
        IEC1bits.U2RXIE = 0;  // RX interrupt enable

        U2MODEbits.UARTEN = 0;

        uart_initialized = false;
    }
}

void uart_write(uint8_t data)
{
    if ((0 == tx_buff_size) && (0 == U2STAbits.UTXBF))
    {
        // hw transmit buffer not full but tx buffer is.
        U2TXREG = data;
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

void uart_write_string(const char* data)
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

void uart_write_array(uint16_t nbr_of_bytes, const uint8_t* data)
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

bool uart_is_write_buffer_empty(void)
{
    return tx_buff_size == 0;
}

uint8_t uart_get(uint16_t index)
{
    uint16_t i;
    uint8_t data;

    uart_disable_rx_interrupt();

    i = rx_buff_first + index;

    if (i >= BUFFER_SIZE)
    {
        i -= BUFFER_SIZE;
    }

    data = rx_buff[i];

    uart_enable_rx_interrupt();

    return data;
}

uint16_t uart_get_receive_buffer_size(void)
{
    return rx_buff_size;
}

bool uart_is_receive_buffer_empty(void)
{
    return (0 == rx_buff_size);
}

void uart_clear_receive_buffer(void)
{
    uart_disable_rx_interrupt();

    rx_buff_size = 0;
    rx_buff_first = 0;
    rx_buff_last = 0;

    uart_enable_rx_interrupt();
}


// =============================================================================
// Private function definitions
// =============================================================================

void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void)
{
    while ((0 == U2STAbits.UTXBF) && (0 != tx_buff_size))
    {
        // TX fifo not full and there are more things to send
        U2TXREG = tx_buff[tx_buff_first];

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

    IFS1bits.U2TXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void)
{
    uint8_t received;

    uart_disable_tx_interrupt();

    if (U2STAbits.OERR)
    {
        U2STAbits.OERR = 0;
    }

    while (U2STAbits.URXDA)
    {
        received = U2RXREG;

        if (COMMAND_TERMINATION_CHAR == received)
        {
            status_set(STATUS_UART_RECEIVE_FLAG, true);
        }

        if (BACKSPACE_CHAR != received)
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
        }
        else
        {
            if (1 < rx_buff_size)
            {

                if (0 != rx_buff_last)
                {
                    --rx_buff_last;
                }
                else
                {
                    rx_buff_last = BUFFER_SIZE - 1;
                }
            }

            if (0 != rx_buff_size)
            {
                --rx_buff_size;
            }
        }


        uart_write(received);
    }

    uart_enable_tx_interrupt();

    IFS1bits.U2RXIF = 0;
}

static void start_tx(void)
{
    uart_disable_tx_interrupt();
    uart_disable_rx_interrupt();

    while ((0 != tx_buff_size) && (0 == U2STAbits.UTXBF))
    {
        U2TXREG = tx_buff[tx_buff_first];

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

    uart_enable_tx_interrupt();
    uart_enable_rx_interrupt();
}

