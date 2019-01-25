#ifndef LORA_IO_H
#define	LORA_IO_H

#ifdef	__cplusplus
extern "C" {
#endif

// =============================================================================
// Include statements
// =============================================================================

#include "stdint.h"
#include "stdbool.h"

// =============================================================================
// Public type definitions
// =============================================================================

//
// Register addresses
//
typedef enum
{
    RFM95W_REG_FIFO                     = 0x00,
    RFM95W_REG_OP_MODE                  = 0x01,
    RFM95W_REG_UNUSED1                  = 0x02,
    RFM95W_REG_UNUSED2                  = 0x03,
    RFM95W_REG_UNUSED3                  = 0x04,
    RFM95W_REG_UNUSED4                  = 0x05,
    RFM95W_REG_FRF_MSB                  = 0x06,
    RFM95W_REG_FRF_MID                  = 0x07,
    RFM95W_REG_FRF_LSB                  = 0x08,
    RFM95W_REG_PA_CONFIG                = 0x09,
    RFM95W_REG_PA_RAMP                  = 0x0A,
    RFM95W_REG_OCP                      = 0x0B,
    RFM95W_REG_LNA                      = 0x0C,
    RFM95W_REG_FIFO_ADDR_PTR            = 0x0D,
    RFM95W_REG_FIFO_TX_BASE_ADDR        = 0x0E,
    RFM95W_REG_FIFO_RX_BASE_ADDR        = 0x0F,
    RFM95W_REG_FIFO_RX_CURRENT_ADDR     = 0x10,
    RFM95W_REG_IRQ_FLAGS_MASK           = 0x11,
    RFM95W_REG_IRQ_FLAGS                = 0x12,
    RFM95W_REG_RX_NBR_BYTES             = 0x13,
    RFM95W_REG_RX_HEADER_CNT_MSB        = 0x14,
    RFM95W_REG_RX_HEADER_CNT_LSB        = 0x15,
    RFM95W_REG_RX_PACKET_CNT_VALUE_MSB  = 0x16,
    RFM95W_REG_RX_PACKET_CNT_VALUE_LSB  = 0x17,
    RFM95W_REG_MODEM_STAT               = 0x18,
    RFM95W_REG_PKT_SNR_VALUE            = 0x19,
    RFM95W_REG_PKT_RSSI_VALUE           = 0x1A,
    RFM95W_REG_RSSI_VALUE               = 0x1B,
    RFM95W_REG_HOP_CHANNEL              = 0x1C,
    RFM95W_REG_MODEM_CONFIG1            = 0x1D,
    RFM95W_REG_MODEM_CONFIG2            = 0x1E,
    RFM95W_REG_SYMB_TIMEOUT_LSB         = 0x1F,
    RFM95W_REG_PREAMBLE_MSB             = 0x20,
    RFM95W_REG_PREAMBLE_LSB             = 0x21,
    RFM95W_REG_PAYLOAD_LENGTH           = 0x22,
    RFM95W_REG_MAX_PAYLOAD_LENGTH       = 0x23,
    RFM95W_REG_HOP_PERIOD               = 0x24,
    RFM95W_REG_FIFO_RX_BYTE_ADDR        = 0x25,
    RFM95W_REG_MODEM_CONFIG3            = 0x26,
    //
    RFM95W_REG_DIO_MAPPING_1            = 0x40,
    RFM95W_REG_DIO_MAPPING_2            = 0x41,
    RFM95W_REG_VERSION                  = 0x42,
    //
    RFM95W_REG_TCXO                     = 0x4B,
    RFM95W_REG_PA_DAC                   = 0x4D,
    RFM95W_REG_FORMER_TEMP              = 0x5B,
    RFM95W_REG_AGC_REF                  = 0x61,
    RFM95W_REG_AGC_THRESH_1             = 0x62,
    RFM95W_REG_AGC_THRESH_2             = 0x63,
    RFM95W_REG_AGC_THRESH_3             = 0x64
} rfm95w_address_t;

//
// Operating mode
//
typedef enum
{
    RFM95W_OP_MODE_SLEEP        = 0x00,
    RFM95W_OP_MODE_STAND_BY     = 0x01,
    RFM95W_OP_MODE_FSTX         = 0x02,
    RFM95W_OP_MODE_FSRX         = 0x04,
    RFM95W_OP_MODE_TX           = 0x03,
    RFM95W_OP_MODE_RX_CONT      = 0x05,
    RFM95W_OP_MODE_RX_SINGLE    = 0x06,
    RFM95W_OP_MODE_CAD          = 0x07
} rfm95w_operating_mode_t;


//
// DIO functions
//
typedef enum
{
    RFM95W_DIO0_FUNC_RX_DONE                = 0x00,
    RFM95W_DIO0_FUNC_TX_DONE                = 0x01,
    RFM95W_DIO0_FUNC_CAD_DONE               = 0x02
} rfm95w_dio0_func_t;

typedef enum
{
    RFM95W_DIO1_FUNC_RX_TIMEOUT             = 0x00,
    RFM95W_DIO1_FUNC_FHSS_CHANGE_CHANNEL    = 0x01,
    RFM95W_DIO1_FUNC_CAD_DETECTED           = 0x02
} rfm95w_dio1_func_t;

typedef enum
{
    RFM95W_DIO2_FUNC_FHSS_CHANGE_CHANNEL_ALT1   = 0x00,
    RFM95W_DIO2_FUNC_FHSS_CHANGE_CHANNEL_ALT2   = 0x01,
    RFM95W_DIO2_FUNC_FHSS_CHANGE_CHANNEL_ALT3   = 0x02
} rfm95w_dio2_func_t;

typedef enum
{
    RFM95W_DIO3_FUNC_CAD_DONE               = 0x00,
    RFM95W_DIO3_FUNC_VALID_HEADER           = 0x01,
    RFM95W_DIO3_FUNC_PAYLOAD_CRC_ERROR      = 0x02
} rfm95w_dio3_func_t;

typedef enum
{
    RFM95W_DIO4_FUNC_CAD_DETECTED           = 0x00,
    RFM95W_DIO4_FUNC_PLL_LOCK_ALT1          = 0x01,
    RFM95W_DIO4_FUNC_PLL_LOCK_ALT2          = 0x02
} rfm95w_dio4_func_t;

typedef enum
{
    RFM95W_DIO5_FUNC_MODE_READY             = 0x00,
    RFM95W_DIO5_FUNC_CLK_OUT_ALT1           = 0x01,
    RFM95W_DIO5_FUNC_CLK_OUT_ALT2           = 0x02
} rfm95w_dio5_func_t;

typedef enum
{
    RFM95W_BW_7K8   = 0x00,
    RFM95W_BW_10K4  = 0x01,
    RFM95W_BW_15K6  = 0x02,
    RFM95W_BW_20K8  = 0x03,
    RFM95W_BW_31K25 = 0x04,
    RFM95W_BW_41K7  = 0x05,
    RFM95W_BW_62K5  = 0x06,
    RFM95W_BW_125K  = 0x07,
    RFM95W_BW_250K  = 0x08,
    RFM95W_BW_500K  = 0x09,
} rfm95w_modem_cfg_bw_t;

typedef enum
{
    RFM95W_CODING_RATE_4_5  = 0x01,
    RFM95W_CODING_RATE_4_6  = 0x02,
    RFM95W_CODING_RATE_4_7  = 0x03,
    RFM95W_CODING_RATE_4_8  = 0x04
} rfm95w_coding_rate_t;

typedef enum
{
    RFM95W_EXPLICIT_HEADER_MODE = 0x00,
    RFM95W_IMPLICIT_HEADER_MODE = 0x01
} rfm95w_implicit_header_mode_on_t;

typedef enum
{
    RFM95W_SPREADING_FACTOR_64_CHIPS    = 6,
    RFM95W_SPREADING_FACTOR_128_CHIPS   = 7,
    RFM95W_SPREADING_FACTOR_256_CHIPS   = 8,
    RFM95W_SPREADING_FACTOR_512_CHIPS   = 9,
    RFM95W_SPREADING_FACTOR_1024_CHIPS  = 10,
    RFM95W_SPREADING_FACTOR_2048_CHIPS  = 11,
    RFM95W_SPREADING_FACTOR_4096_CHIPS  = 12,
} rfm95w_spreading_factor_t;

typedef enum
{
    RFM95W_TX_NORMAL_MODE       = 0x00,
    RFM95W_TX_CONTINUOUS_MODE   = 0x01
} rfm95w_tx_continuous_mode_t;

typedef enum
{
    RFM95W_PAYLOAD_CRC_DISABLE  = 0x00,
    RFM95W_PAYLOAD_CRC_ENABLE   = 0x01
} rfm95w_payload_crc_on_t;

typedef enum
{
    RFM95W_IRQ_FLAG_RX_TIMEOUT_MASK             = 0x80,
    RFM95W_IRQ_FLAG_RX_DONE_MASK                = 0x40,
    RFM95W_IRQ_FLAG_PAYLOAD_CRC_ERROR_MASK      = 0x20,
    RFM95W_IRQ_FLAG_VALID_HEADER_MASK           = 0x10,
    RFM95W_IRQ_FLAG_TX_DONE_MASK                = 0x08,
    RFM95W_IRQ_FLAG_CAD_DONE_MASK               = 0x04,
    RFM95W_IRQ_FLAG_FHSS_CHANGE_CHANNEL_MASK    = 0x02,
    RFM95W_IRQ_FLAG_CAD_DETECTED_MASK           = 0x01
} rfm95w_irq_flag_t;

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
 @brief Writes a value to one register in the RFM95W.
 @param register    - Address to write to.
 @param value       - Value to be written to the register.
*/
void rfm95w_io_write(rfm95w_address_t register, uint8_t value);

/**
 @brief Reads the value from one register in the RFM95W.
 @param register    - Address to read from.
 @return Value in the read register.
*/
uint8_t rfm95w_io_read(rfm95w_address_t register);

/**
 @brief Sets the output function of one of the DIO pins.
 @param dio_number      - DIO pin number.
 @param dio_function    - Which function should be assigned to the DIO pin.
*/
void rfm95w_io_set_dio_function(uint8_t dio_number, uint8_t dio_function);

/**
 @brief Sets the operating mode.
*/
void rfm95w_io_set_operating_mode(rfm95w_operating_mode_t mode);

/**
 * @brief Sets the rx timeout in single RX mode.
 * @param symbols   - Timeout length in number of symbols. Must be in [4, 1023]
 */
void rfm95w_io_set_single_rx_timeout(uint16_t symbols);

/**
 * @brief Clears all IRQs.
 */
void rfm95w_io_clear_all_irqs(void);

#ifdef	__cplusplus
}
#endif

#endif	/* LORA_IO_H */

