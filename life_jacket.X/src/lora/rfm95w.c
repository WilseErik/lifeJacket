// =============================================================================
// Include statements
// =============================================================================

#include "lora\rfm95w.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <xc.h>

#include "lora/rfm95w_io.h"
#include "uart/debug_log.h"
#include "hal/uart.h"
#include "hal/gpio.h"
#include "hal/clock.h"

// =============================================================================
// Private type definitions
// =============================================================================

typedef enum
{
    RFM95W_RADIO_STATE_IDLE,
    RFM95W_RADIO_STATE_TX,
    RFM95W_RADIO_STATE_RX_SINGLE
} rfm95w_radio_state_t;

#define RFM95W_RX_BUFFER_SIZE (256)

typedef struct rfm95w_buffer_t
{
    uint8_t data[RFM95W_RX_BUFFER_SIZE];
    uint8_t length;
} rfm95w_buffer_t;

// =============================================================================
// Global variables
// =============================================================================

// =============================================================================
// Private constants
// =============================================================================

static const uint8_t RFM95W_REG_INIT_TABLE[][2] =
{
    {RFM95W_REG_PA_CONFIG,          0x4F},  // Output power = 4dBm
    {RFM95W_REG_PA_RAMP,            0x09},  // Default value (40 us)
    {RFM95W_REG_LNA,                0x20},  // Max LNA gain
    {RFM95W_REG_FIFO_ADDR_PTR,      0x00},
    {RFM95W_REG_FIFO_TX_BASE_ADDR,  0x80},
    {RFM95W_REG_FIFO_RX_BASE_ADDR,  0x00},
    {RFM95W_REG_IRQ_FLAGS_MASK,     0x00},
    {RFM95W_REG_IRQ_FLAGS,          0xFF},  // Clear by writing 1's
    {RFM95W_REG_MODEM_CONFIG1,      (RFM95W_BW_125K << 4) |
                                    (RFM95W_CODING_RATE_4_5 << 1) |
                                    RFM95W_EXPLICIT_HEADER_MODE},
    {RFM95W_REG_MODEM_CONFIG2,      (RFM95W_SPREADING_FACTOR_128_CHIPS << 4) |
                                    (RFM95W_TX_NORMAL_MODE << 3) |
                                    (RFM95W_PAYLOAD_CRC_DISABLE << 2) |
                                    (0 << 0)},  // rx time-out msb
    {RFM95W_REG_SYMB_TIMEOUT_LSB,   0x40},
    {RFM95W_REG_PREAMBLE_MSB,       0x00},
    {RFM95W_REG_PREAMBLE_LSB,       0x08},
    {RFM95W_REG_PAYLOAD_LENGTH,     0x01},
    {RFM95W_REG_MAX_PAYLOAD_LENGTH, 0xFF},
    {RFM95W_REG_HOP_PERIOD,         0x00},  // Frequency hopping disabled
    {RFM95W_REG_MODEM_CONFIG3,      0x00},  // Data rate is under 16ms, LNA 
                                            // gain set by LnaGain regsister
};

#define RFM95W_REG_INIT_TABLE_LEN (sizeof(RFM95W_REG_INIT_TABLE) / 2)

static const uint8_t RFM95W_SILICON_VERSION = 0x12;


/*
 Allowed frequencies:
    868.1 - SF7BW125 to SF12BW125
    868.3 - SF7BW125 to SF12BW125 and SF7BW250
    868.5 - SF7BW125 to SF12BW125
    867.1 - SF7BW125 to SF12BW125
    867.3 - SF7BW125 to SF12BW125
    867.5 - SF7BW125 to SF12BW125
    867.7 - SF7BW125 to SF12BW125
    867.9 - SF7BW125 to SF12BW125
    868.8 - FSK

 Max output power: 14 dBm
*/
static const uint8_t FREQ_WORD_868_1[] = {0xD9, 0x06, 0x66};

static const uint16_t SINGLE_RX_TIMEOUT_SYMBOLS = 1023; // must be in [4, 1023]

static const uint8_t RFM95W_MAX_RETRANSMISSION_COUNT = 3;

// =============================================================================
// Private variables
// =============================================================================

static rfmw95w_received_message_callback_t received_message_callback;

static volatile uint8_t tx_fifo_size = 0;

static volatile rfm95w_radio_state_t radio_state = RFM95W_RADIO_STATE_IDLE;
static volatile uint8_t rfm95w_retransmission_count;

static volatile rfm95w_buffer_t rx_buffer;
static volatile rfm95w_buffer_t tx_buffer;

// =============================================================================
// Private function declarations
// =============================================================================

//
// Event handlers
//

/**
 * @brief Handles the TX done event.
 */
static void handle_tx_done(void);

/**
 * @brief Handles the RX done event.
 */
static void handle_rx_done(void);

/**
 * @brief Handles the RX timeout event.
 */
static void handle_rx_timeout(void);

//
//
//

/**
 * @brief Reads the contents of the RX fifo into RAM.
 */
static void rfm95w_read_fifo(void);

/**
 * @brief Ends a RX session.
 */
static void rfm95w_end_rx(void);

/**
 * @brief Starts a retransmission.
 */
static void rfm95w_start_retransmission(void);

/**
 * @brief Fills up the TX fifo for a retransmission.
 */
static void rfm95w_refill_tx_fifo(void);

/**
 * @brief Configures DIO0 to generate an interrupt when the message has been
 *        transitted.
 */
static void rfm95w_setup_dio0_for_tx_done(void);

/**
 * @brief Configures DIO0 to generate an interrupt when a message has been
 *        received.
 */
static void rfm95w_setup_dio0_for_rx_done(void);

/**
 * @brief Configures DIO1 ti generate an interrupt when a fixed time
 *        RX session times out.
 */
static void rfm95w_setup_dio1_for_rx_timeout(void);

//
// DIO interrupts
//

/**
 * @brief Callback for the DIO0 change notification callback.
 */
static void rfmw_dio0_callback(bool rising);

/**
 * @brief Callback for the DIO1 change notification callback.
 */
static void rfmw_dio1_callback(bool rising);

// =============================================================================
// Public function definitions
// =============================================================================

void rfm95w_init(void)
{
    uint8_t i;

    radio_state = RFM95W_RADIO_STATE_IDLE;
    rx_buffer.length = 0;
    received_message_callback = NULL;
    rfm95w_retransmission_count = 0;
    memset((void*)&rx_buffer, sizeof(rfm95w_buffer_t), 0);
    memset((void*)&tx_buffer, sizeof(rfm95w_buffer_t), 0);

    while (clock_get_msec() <= 10)
    {
        ;   // The user should wait for 10 ms from of the end of the POR cycle
            // before commencing communications over the SPI bus
    }

    LORA_RESET_OFF;

    if (RFM95W_SILICON_VERSION == rfm95w_io_read(RFM95W_REG_VERSION))
    {
        debug_log_append_line("RFM95W communication ok");
    }
    else
    {
        debug_log_append_line("RFM95W communication failiure");
        return;
    }

    rfm95w_io_set_operating_mode(RFM95W_OP_MODE_SLEEP);

    // LORA mode, high frequency mode
    rfm95w_io_write(RFM95W_REG_OP_MODE, 0x80);

    rfm95w_io_write(RFM95W_REG_FRF_MSB, FREQ_WORD_868_1[0]);
    rfm95w_io_write(RFM95W_REG_FRF_MID, FREQ_WORD_868_1[1]);
    rfm95w_io_write(RFM95W_REG_FRF_LSB, FREQ_WORD_868_1[2]);

    for (i = 0; i != RFM95W_REG_INIT_TABLE_LEN; ++i)
    {
        rfm95w_io_write(RFM95W_REG_INIT_TABLE[i][0],
                                   RFM95W_REG_INIT_TABLE[i][1]);
    }

    rfm95w_io_set_operating_mode(RFM95W_OP_MODE_STAND_BY);
}

void rfm95w_register_received_message_callback(
    rfmw95w_received_message_callback_t callback)
{
    received_message_callback = callback;
}

bool rfm95w_is_idle(void)
{
    return (RFM95W_RADIO_STATE_IDLE == radio_state);
}

void rfm95w_write_tx_fifo(const uint8_t * data,
                          uint8_t length,
                          uint8_t offset)
{
    uint8_t tx_fifo_base;
    uint8_t i;

    tx_fifo_base = rfm95w_io_read(RFM95W_REG_FIFO_TX_BASE_ADDR);
    rfm95w_io_write(RFM95W_REG_FIFO_ADDR_PTR, tx_fifo_base + offset);

    for (i = 0; i != length; ++i)
    {
        rfm95w_io_write(RFM95W_REG_FIFO, *data);
        tx_buffer.data[offset + i] = *data;

        ++data;
    }

    if (offset + length > tx_fifo_size)
    {
        tx_fifo_size = offset + length;

        rfm95w_io_write(RFM95W_REG_PAYLOAD_LENGTH, tx_fifo_size);
        tx_buffer.length = tx_fifo_size;
    }
}

void rfm95w_clear_tx_fifo(void)
{
    tx_fifo_size = 0;
    rfm95w_io_write(RFM95W_REG_PAYLOAD_LENGTH, 1);
}

void rfm95w_start_tx(void)
{
    rfm95w_io_clear_all_irqs();
    rfm95w_setup_dio0_for_tx_done();

    radio_state = RFM95W_RADIO_STATE_TX;
    rfm95w_retransmission_count = 0;

    rfm95w_io_set_operating_mode(RFM95W_OP_MODE_TX);
}

void rfm95w_start_single_rx(void)
{
    uint8_t rx_base_addr;

    rx_base_addr = rfm95w_io_read(RFM95W_REG_FIFO_RX_BASE_ADDR);
    rfm95w_io_write(RFM95W_REG_FIFO_ADDR_PTR, rx_base_addr);

    rfm95w_io_set_single_rx_timeout(SINGLE_RX_TIMEOUT_SYMBOLS);

    rfm95w_io_clear_all_irqs();
    rfm95w_setup_dio0_for_rx_done();
    rfm95w_setup_dio1_for_rx_timeout();

    radio_state = RFM95W_RADIO_STATE_RX_SINGLE;

    rfm95w_io_set_operating_mode(RFM95W_OP_MODE_RX_SINGLE);
}

void rfmw_send_cw(void)
{
    uint8_t modem_config_2;

    modem_config_2 = rfm95w_io_read(RFM95W_REG_MODEM_CONFIG2);
    modem_config_2 |= RFM95W_TX_CONTINUOUS_MODE << 3;
    rfm95w_io_write(RFM95W_REG_MODEM_CONFIG2, modem_config_2);

    rfm95w_io_set_operating_mode(RFM95W_OP_MODE_TX);
}

// =============================================================================
// Private function definitions
// =============================================================================

static void handle_tx_done(void)
{
    rfm95w_start_single_rx();
}

static void handle_rx_done(void)
{
    uint8_t reg_irq_flags;

    reg_irq_flags = rfm95w_io_read(RFM95W_REG_IRQ_FLAGS);

    if (reg_irq_flags & RFM95W_IRQ_FLAG_PAYLOAD_CRC_ERROR_MASK)
    {
        rfm95w_io_clear_all_irqs();

        handle_rx_timeout();
    }
    else
    {
        rfm95w_io_clear_all_irqs();

        rfm95w_read_fifo();

        if (NULL != received_message_callback)
        {
            received_message_callback((uint8_t*)rx_buffer.data,
                                      rx_buffer.length);
        }
    }
}

static void handle_rx_timeout(void)
{
    if (++rfm95w_retransmission_count < RFM95W_MAX_RETRANSMISSION_COUNT)
    {
        rfm95w_start_retransmission();
    }
    else
    {
        rfm95w_end_rx();
    }
}

static void rfm95w_read_fifo(void)
{
    uint8_t length;
    uint8_t i;

    length = rfm95w_io_read(RFM95W_REG_RX_NBR_BYTES);
    rfm95w_io_write(RFM95W_REG_FIFO_ADDR_PTR, RFM95W_REG_FIFO_RX_CURRENT_ADDR);

    for (i = 0; i != length; ++i)
    {
        rx_buffer.data[i] = rfm95w_io_read(RFM95W_REG_FIFO);
    }

    rx_buffer.length = length;
}

static void rfm95w_end_rx(void)
{
    gpio_enable_cn(GPIO_CN_PIN_LORA_DIO0, false);
    gpio_enable_cn(GPIO_CN_PIN_LORA_DIO1, false);

    rfm95w_io_set_operating_mode(RFM95W_OP_MODE_STAND_BY);
    radio_state = RFM95W_RADIO_STATE_IDLE;
}

static void rfm95w_start_retransmission(void)
{
    gpio_enable_cn(GPIO_CN_PIN_LORA_DIO0, false);
    gpio_enable_cn(GPIO_CN_PIN_LORA_DIO1, false);

    rfm95w_io_set_operating_mode(RFM95W_OP_MODE_STAND_BY);

    rfm95w_io_clear_all_irqs();
    rfm95w_setup_dio0_for_tx_done();

    radio_state = RFM95W_RADIO_STATE_TX;
    rfm95w_retransmission_count = 0;

    rfm95w_refill_tx_fifo();

    rfm95w_io_set_operating_mode(RFM95W_OP_MODE_TX);
}

static void rfm95w_refill_tx_fifo(void)
{
    uint8_t tx_fifo_base;
    uint8_t i;

    tx_fifo_base = rfm95w_io_read(RFM95W_REG_FIFO_TX_BASE_ADDR);
    rfm95w_io_write(RFM95W_REG_FIFO_ADDR_PTR, tx_fifo_base);

    for (i = 0; i != tx_buffer.length; ++i)
    {
        rfm95w_io_write(RFM95W_REG_FIFO, tx_buffer.data[i]);
    }

    rfm95w_io_write(RFM95W_REG_PAYLOAD_LENGTH, tx_buffer.length);
}

static void rfm95w_setup_dio0_for_tx_done(void)
{
    uint8_t reg_irq_masks;

    reg_irq_masks = rfm95w_io_read(RFM95W_REG_IRQ_FLAGS_MASK);
    reg_irq_masks &= ~RFM95W_IRQ_FLAG_TX_DONE_MASK;
    rfm95w_io_write(RFM95W_REG_IRQ_FLAGS_MASK, reg_irq_masks);

    rfm95w_io_write(RFM95W_REG_IRQ_FLAGS, RFM95W_IRQ_FLAG_TX_DONE_MASK);   // clear irq

    rfm95w_io_set_dio_function(0, RFM95W_DIO0_FUNC_TX_DONE);
    gpio_register_cn_handler(GPIO_CN_PIN_LORA_DIO0, rfmw_dio0_callback);
    gpio_enable_cn(GPIO_CN_PIN_LORA_DIO0, true);
}

static void rfm95w_setup_dio0_for_rx_done(void)
{
    uint8_t reg_irq_masks;

    reg_irq_masks = rfm95w_io_read(RFM95W_REG_IRQ_FLAGS_MASK);
    reg_irq_masks &= ~RFM95W_IRQ_FLAG_RX_DONE_MASK;
    rfm95w_io_write(RFM95W_REG_IRQ_FLAGS_MASK, reg_irq_masks);

    rfm95w_io_write(RFM95W_REG_IRQ_FLAGS, RFM95W_IRQ_FLAG_RX_DONE_MASK);   // clear irq

    rfm95w_io_set_dio_function(0, RFM95W_DIO0_FUNC_RX_DONE);
    gpio_register_cn_handler(GPIO_CN_PIN_LORA_DIO0, rfmw_dio0_callback);
    gpio_enable_cn(GPIO_CN_PIN_LORA_DIO0, true);
}

static void rfm95w_setup_dio1_for_rx_timeout(void)
{
    uint8_t reg_irq_masks;

    reg_irq_masks = rfm95w_io_read(RFM95W_REG_IRQ_FLAGS_MASK);
    reg_irq_masks &= ~RFM95W_IRQ_FLAG_RX_TIMEOUT_MASK;
    rfm95w_io_write(RFM95W_REG_IRQ_FLAGS_MASK, reg_irq_masks);

    rfm95w_io_write(RFM95W_REG_IRQ_FLAGS, RFM95W_IRQ_FLAG_RX_TIMEOUT_MASK);   // clear irq

    rfm95w_io_set_dio_function(1, RFM95W_DIO1_FUNC_RX_TIMEOUT);
    gpio_register_cn_handler(GPIO_CN_PIN_LORA_DIO1, rfmw_dio1_callback);
    gpio_enable_cn(GPIO_CN_PIN_LORA_DIO1, true);
}

static void rfmw_dio0_callback(bool rising)
{
    if (rising)
    {
        if (RFM95W_RADIO_STATE_TX == radio_state)
        {
            handle_tx_done();
        }
        else if (RFM95W_RADIO_STATE_RX_SINGLE == radio_state)
        {
            handle_rx_done();
        }
    }
    else
    {
        ;
    }
}

static void rfmw_dio1_callback(bool rising)
{
    if (rising)
    {
        if (RFM95W_RADIO_STATE_RX_SINGLE == radio_state)
        {
            handle_rx_timeout();
        }
    }
    else
    {
        ;
    }
}