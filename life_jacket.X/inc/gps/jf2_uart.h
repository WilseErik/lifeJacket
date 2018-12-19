#ifndef JF2_UART_H
#define	JF2_UART_H

#ifdef	__cplusplus
extern "C" {
#endif

// =============================================================================
// Include statements
// =============================================================================

#include <xc.h>

#include <stdint.h>
#include <stdbool.h>

// =============================================================================
// Public type definitions
// =============================================================================

// =============================================================================
// Global variable declarations
// =============================================================================

// =============================================================================
// Global constatants
// =============================================================================

// =============================================================================
// Public function declarations
// =============================================================================
/**
 * @brief Initializes the UART module
 * @param void
 * @return void
 */
void jf2_uart_init();

/**
 * @brief Writes a byte over the uart interface.
 * @param data - The data to send.
 * @return void
 */
void jf2_uart_write(uint8_t data);

/**
 * @brief Write a string over the uart interface.
 * @param data - The null terminated data to send.
 * @return void
 */
void jf2_uart_write_string(const char* data);

/**
 * @brief Write a string over the uart interface.
 * @brief nbr_of_bytes - The number of bytes to send.
 * @param data - The null terminated data to send.
 * @return void
 */
void jf2_uart_write_array(uint16_t nbr_of_bytes, const uint8_t* data);

/**
 * @brief Checks if the write buffer is empty.
 * @return True if the write buffer is empty.
 */
bool jf2_uart_is_write_buffer_empty(void);

/**
 * @brief Gets a byte from the receive buffer.
 * @param index - The index of the byte to get.
 * @return The byte in the receive buffer at the specified index.
 */
uint8_t jf2_uart_get(uint16_t index);

/**
 * @brief Gets the size (in number of elements) of the receive buffer.
 * @param void
 * @return The size of the reveive buffer.
 */
uint16_t jf2_uart_get_receive_buffer_size(void);

/**
 * @brief Checks if the receive buffer is empty.
 * @param void
 * @return True if the receive buffer is empty, false otherwise.
 */
bool jf2_uart_is_receive_buffer_empty(void);

/**
 * @brief Clears the receive buffer.
 * @param void
 * @return void
 */
void jf2_uart_clear_receive_buffer(void);

/**
 * @brief Enables the UART receive interrupt.
 * @details This interrupt will affect the transmit and receive buffer.
 */
static inline void jf2_uart_enable_rx_interrupt()
{
    IEC0bits.U1RXIE = 1;
}

/**
 * @brief Disables the UART receive interrupt.
 * @details This interrupt will affect the transmit and receive buffer.
 */
static inline void jf2_uart_disable_rx_interrupt()
{
    IEC0bits.U1RXIE = 0;
}

/**
 * @brief Enables the UART transmit interrupt.
 * @details This interrupt will affect the transmit buffer.
 */
static inline void jf2_uart_enable_tx_interrupt()
{
    IEC0bits.U1TXIE = 1;
}

/**
 * @brief Disables the UART transmit interrupt.
 * @details This interrupt will affect the transmit buffer.
 */
static inline void jf2_uart_disable_tx_interrupt()
{
    IEC0bits.U1TXIE = 0;
}


#ifdef	__cplusplus
}
#endif

#endif	/* JF2_UART_H */

