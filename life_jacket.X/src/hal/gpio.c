// =============================================================================
// Include statements
// =============================================================================
#include <xc.h>

#include <stdint.h>
#include <stdbool.h>

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

void gpio_init(void)
{
    LORA_DIO0_DIR       = DIR_IN;
    LORA_DIO1_DIR       = DIR_IN;
    LORA_DIO2_DIR       = DIR_IN;
    LORA_DIO3_DIR       = DIR_IN;
    // DIO4 is input only
    LORA_DIO5_DIR       = DIR_IN;

    LORA_N_CS_DIR       = DIR_OUT;
    LORA_CS_OFF;

    LORA_N_RESET_DIR    = DIR_OUT;
    LORA_RESET_OFF;

    LORA_ANT_SEL1_DIR  = DIR_OUT;
    LORA_ANT_SEL2_DIR  = DIR_OUT;
    LORA_SELECT_ANT_1;

    GPS_TIMEPULSE_DIR   = DIR_IN;
    GPS_ON_OFF_DIR      = DIR_OUT;
    GPS_TXD_DIR         = DIR_OUT;
    GPS_RXD_DIR         = DIR_IN;
    GPS_ANT_SEL1_DIR    = DIR_OUT;
    GPS_ANT_SEL2_DIR    = DIR_OUT;
    GPS_SELECT_ANT_1;

    PCM1770_SCKI_DIR    = DIR_OUT;
    PCM1770_N_CS_DIR    = DIR_OUT;
    PCM1770_CS_OFF;
    PCM1770_N_PD_DIR    = DIR_OUT;
    PCM1770_N_PD_PIN    = 0;
    PCM1770_BCK_DIR     = DIR_OUT;
    PCM1770_DATA_DIR    = DIR_OUT;
    PCM1770_LRCK_DIR    = DIR_OUT;

    AMP_N_SD_DIR        = DIR_OUT;
    AMP_N_SD_PIN        = 0;
    AMP_N_SD_BOOST_DIR  = DIR_OUT;
    AMP_N_SD_BOOST_PIN  = 0;

    ACC_N_CS_DIR        = DIR_OUT;
    ACC_CS_OFF;

    SPI_CLK_DIR         = DIR_OUT;
    SPI_MOSI_DIR        = DIR_OUT;
    SPI_MISO_DIR        = DIR_IN;

    DEBUG_UART_RX_DIR   = DIR_IN;
    DEBUG_UART_TX_DIR   = DIR_OUT;

    // No analog io
    ANSA = 0;
    ANSB = 0;
    ANSC = 0;

    // SPI interface
    SPI_CLK_PPS_REG = GPIO_PPS_OUT_SCK1OUT;
    SPI_MOSI_PPS_REG = GPIO_PPS_OUT_SDO1;
    SPI_MISO_PPS_REG = SPI_MISO_RP_PIN;

    // I2S interface
    PCM1770_BCK_PPS_REG = GPIO_PPS_OUT_SCK2OUT;
    PCM1770_DATA_PPS_REG = GPIO_PPS_OUT_SDO2;
    PCM1770_LRCK_PPS_REG = GPIO_PPS_OUT_SS2OUT;

    // Debug UART
    DEBUG_UART_TX_PPS_REG = GPIO_PPS_OUT_U1TX;
    DEBUG_UART_RX_PPS_REG = DEBUG_UART_RX_RP_PIN;

    // GPS UART
    GPS_TXD_PPS_REG = GPIO_PPS_OUT_U2TX;
    GPS_RXD_PPS_REG = GPS_RXD_RP_PIN;
}

// =============================================================================
// Private function definitions
// =============================================================================



