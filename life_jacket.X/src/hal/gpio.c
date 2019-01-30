// =============================================================================
// Include statements
// =============================================================================
#include <xc.h>

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

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

static volatile gpio_cn_pin_status_t cn_pins;

// =============================================================================
// Private function declarations
// =============================================================================

void gpio_handle_cn_pin_state_update(gpio_cn_pin_info_t * pin, bool new_state);

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
    LORA_RESET_ON;

    LORA_ANT_SEL1_DIR  = DIR_OUT;
    LORA_ANT_SEL2_DIR  = DIR_OUT;
    LORA_SELECT_ANT_1;

    GPS_TIMEPULSE_DIR   = DIR_IN;
    GPS_ON_OFF_PIN      = 0;
    GPS_ON_OFF_DIR      = DIR_OUT;
    GPS_ON_OFF_PIN      = 0;
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

    FLASH_N_CS_DIR      = DIR_OUT;
    FLASH_CS_OFF;

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
    DEBUG_UART_TX_PPS_REG = GPIO_PPS_OUT_U2TX;
    DEBUG_UART_RX_PPS_REG = DEBUG_UART_RX_RP_PIN;

    // GPS UART
    GPS_TXD_PPS_REG = GPIO_PPS_OUT_U1TX;
    GPS_RXD_PPS_REG = GPS_RXD_RP_PIN;

    //
    // Unused pins
    //
    NC1_PULL_DOWN = 1;

    NC2_PIN = 0;
    NC2_DIR = DIR_OUT;
    NC2_PIN = 0;

    PGD1_PULL_DOWN = 1;
    PGC1_PULL_DOWN = 1;

    memset((void*)&cn_pins, sizeof(cn_pins), 0);

    // Enable change notification interrupts
    IEC1bits.CNIE = 1;
}

void gpio_register_cn_handler(gpio_cn_pin_t pin, gpio_cn_callback_t callback)
{
    switch (pin)
    {
    case GPIO_CN_PIN_LORA_DIO0:
        cn_pins.lora_dio0.callback = callback;
        break;

    case GPIO_CN_PIN_LORA_DIO1:
        cn_pins.lora_dio1.callback = callback;
        break;

    case GPIO_CN_PIN_LORA_DIO2:
        cn_pins.lora_dio2.callback = callback;
        break;

    case GPIO_CN_PIN_LORA_DIO3:
        cn_pins.lora_dio3.callback = callback;
        break;

    case GPIO_CN_PIN_LORA_DIO4:
        cn_pins.lora_dio4.callback = callback;
        break;

    case GPIO_CN_PIN_LORA_DIO5:
        cn_pins.lora_dio5.callback = callback;
        break;    
    }
}

void gpio_enable_cn(gpio_cn_pin_t pin, bool enable)
{
    switch (pin)
    {
    case GPIO_CN_PIN_LORA_DIO0:
        cn_pins.lora_dio0.cn_enabled = enable;
        LORA_DIO0_CNEN = enable;
        cn_pins.lora_dio0.state = LORA_DIO0_PIN;
        break;

    case GPIO_CN_PIN_LORA_DIO1:
        cn_pins.lora_dio1.cn_enabled = enable;
        LORA_DIO1_CNEN = enable;
        cn_pins.lora_dio1.state = LORA_DIO1_PIN;
        break;

    case GPIO_CN_PIN_LORA_DIO2:
        cn_pins.lora_dio2.cn_enabled = enable;
        LORA_DIO2_CNEN = enable;
        cn_pins.lora_dio2.state = LORA_DIO2_PIN;
        break;

    case GPIO_CN_PIN_LORA_DIO3:
        cn_pins.lora_dio3.cn_enabled = enable;
        LORA_DIO3_CNEN = enable;
        cn_pins.lora_dio3.state = LORA_DIO3_PIN;
        break;

    case GPIO_CN_PIN_LORA_DIO4:
        cn_pins.lora_dio4.cn_enabled = enable;
        LORA_DIO4_CNEN = enable;
        cn_pins.lora_dio4.state = LORA_DIO4_PIN;
        break;

    case GPIO_CN_PIN_LORA_DIO5:
        cn_pins.lora_dio5.cn_enabled = enable;
        LORA_DIO5_CNEN = enable;
        cn_pins.lora_dio5.state = LORA_DIO5_PIN;
        break;
    }
}

// =============================================================================
// Private function definitions
// =============================================================================

void gpio_handle_cn_pin_state_update(gpio_cn_pin_info_t * pin, bool new_state)
{
    if (pin->cn_enabled &&
        (new_state != pin->state))
    {
        if (NULL != pin->callback)
        {
            pin->callback(new_state);   
        }
    }

    pin->state = new_state;
}

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void)
{
    IFS1bits.CNIF = 0;

    gpio_handle_cn_pin_state_update((gpio_cn_pin_info_t*)&cn_pins.lora_dio0,
                                    LORA_DIO0_PIN);
    gpio_handle_cn_pin_state_update((gpio_cn_pin_info_t*)&cn_pins.lora_dio1,
                                    LORA_DIO1_PIN);
    gpio_handle_cn_pin_state_update((gpio_cn_pin_info_t*)&cn_pins.lora_dio2,
                                    LORA_DIO2_PIN);
    gpio_handle_cn_pin_state_update((gpio_cn_pin_info_t*)&cn_pins.lora_dio3,
                                    LORA_DIO3_PIN);
    gpio_handle_cn_pin_state_update((gpio_cn_pin_info_t*)&cn_pins.lora_dio4,
                                    LORA_DIO4_PIN);
    gpio_handle_cn_pin_state_update((gpio_cn_pin_info_t*)&cn_pins.lora_dio5,
                                    LORA_DIO5_PIN);
}

