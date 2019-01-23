#ifndef GPIO_H
#define	GPIO_H

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
    
#define DIR_IN 1
#define DIR_OUT 0

//
// LoRa
//
#define LORA_DIO0_PIN               PORTAbits.RA0
#define LORA_DIO0_DIR               TRISAbits.TRISA0
#define LORA_DIO0_CNEN              CNEN1bits.CN2IE

#define LORA_DIO1_PIN               PORTAbits.RA1
#define LORA_DIO1_DIR               TRISAbits.TRISA1
#define LORA_DIO1_CNEN              CNEN1bits.CN3IE

#define LORA_DIO2_PIN               PORTAbits.RA2
#define LORA_DIO2_DIR               TRISAbits.TRISA2
#define LORA_DIO2_CNEN              CNEN2bits.CN30IE

#define LORA_DIO3_PIN               PORTCbits.RC9
#define LORA_DIO3_DIR               TRISCbits.TRISC9
#define LORA_DIO3_CNEN              CNEN2bits.CN19IE

// LORA_DIO4 is input only
#define LORA_DIO4_PIN               PORTAbits.RA4
#define LORA_DIO4_CNEN              CNEN1bits.CN0IE

#define LORA_DIO5_PIN               PORTAbits.RA7
#define LORA_DIO5_DIR               TRISAbits.TRISA7
#define LORA_DIO5_CNEN              CNEN3bits.CN33IE

#define LORA_N_CS_PIN               LATCbits.LATC4
#define LORA_N_CS_DIR               TRISCbits.TRISC4
#define LORA_CS_ON                  do {LORA_N_CS_PIN = 0;} while (0)
#define LORA_CS_OFF                 do {LORA_N_CS_PIN = 1;} while (0)

#define LORA_N_RESET_PIN            LATCbits.LATC8
#define LORA_N_RESET_DIR            TRISCbits.TRISC8
#define LORA_RESET_ON               do {LORA_N_RESET_PIN = 0;} while (0)
#define LORA_RESET_OFF              do {LORA_N_RESET_PIN = 1;} while (0)

#define LORA_ANT_SEL1_PIN          LATBbits.LATB9
#define LORA_ANT_SEL1_DIR          TRISBbits.TRISB9

#define LORA_ANT_SEL2_PIN          LATBbits.LATB10
#define LORA_ANT_SEL2_DIR          TRISBbits.TRISB10

#define LORA_SELECT_ANT_1           do {LORA_ANT_SEL1_PIN = 0;                \
                                        LORA_ANT_SEL2_PIN = 1;} while (0)

#define LORA_SELECT_ANT_2           do {LORA_ANT_SEL2_PIN = 0;                \
                                        LORA_ANT_SEL1_PIN = 1;} while (0)

//
// GPS
//
#define GPS_TIMEPULSE_PIN           PORTAbits.RA8
#define GPS_TIMEPULSE_DIR           TRISAbits.TRISA8

#define GPS_ON_OFF_PIN              LATAbits.LATA10
#define GPS_ON_OFF_DIR              TRISAbits.TRISA10

#define GPS_TXD_PIN                 LATBbits.LATB15
#define GPS_TXD_DIR                 TRISBbits.TRISB15
#define GPS_TXD_PPS_REG             RPOR7bits.RP15R

#define GPS_RXD_PIN                 PORTBbits.RB14
#define GPS_RXD_DIR                 TRISBbits.TRISB14
#define GPS_RXD_PPS_REG             RPINR18bits.U1RXR
#define GPS_RXD_RP_PIN              (14)

#define GPS_ANT_SEL1_PIN            PORTAbits.RA9
#define GPS_ANT_SEL1_DIR            TRISAbits.TRISA9

#define GPS_ANT_SEL2_PIN            PORTCbits.RC7
#define GPS_ANT_SEL2_DIR            TRISCbits.TRISC7

#define GPS_SELECT_ANT_1           do {GPS_ANT_SEL1_PIN = 0;                \
                                       GPS_ANT_SEL2_PIN = 1;} while (0)

#define GPS_SELECT_ANT_2           do {GPS_ANT_SEL2_PIN = 0;                \
                                       GPS_ANT_SEL1_PIN = 1;} while (0)

//
// Audio
//
#define PCM1770_SCKI_PIN            LATAbits.LATA3
#define PCM1770_SCKI_DIR            TRISAbits.TRISA3

#define PCM1770_N_CS_PIN            LATCbits.LATC5
#define PCM1770_N_CS_DIR            TRISCbits.TRISC5
#define PCM1770_CS_ON               do {PCM1770_N_CS_PIN = 0;} while (0)
#define PCM1770_CS_OFF              do {PCM1770_N_CS_PIN = 1;} while (0)

#define PCM1770_N_PD_PIN            LATBbits.LATB8
#define PCM1770_N_PD_DIR            TRISBbits.TRISB8

#define PCM1770_BCK_PIN             LATBbits.LATB11
#define PCM1770_BCK_DIR             TRISBbits.TRISB11
#define PCM1770_BCK_PPS_REG         RPOR5bits.RP11R

#define PCM1770_DATA_PIN            LATBbits.LATB12
#define PCM1770_DATA_DIR            TRISBbits.TRISB12
#define PCM1770_DATA_PPS_REG        RPOR6bits.RP12R

#define PCM1770_LRCK_PIN            LATB13bits.LATB13
#define PCM1770_LRCK_DIR            TRISBbits.TRISB13
#define PCM1770_LRCK_PPS_REG        RPOR6bits.RP13R
                                       
#define AMP_N_SD_PIN                LATBbits.LATB7
#define AMP_N_SD_DIR                TRISBbits.TRISB7

#define AMP_N_SD_BOOST_PIN          LATBbits.LATB6
#define AMP_N_SD_BOOST_DIR          TRISBbits.TRISB6

//
// Accelerometer
//
#define ACC_N_CS_PIN                LATCbits.LATC3
#define ACC_N_CS_DIR                TRISCbits.TRISC3
#define ACC_CS_ON                   do {ACC_N_CS_PIN = 0;} while (0)
#define ACC_CS_OFF                  do {ACC_N_CS_PIN = 1;} while (0)

//
// Flash
//
#define FLASH_N_CS_PIN				LATCbits.LATC6
#define FLASH_N_CS_DIR              TRISCbits.TRISC6
#define FLASH_CS_ON                 do {FLASH_N_CS_PIN = 0;} while (0)
#define FLASH_CS_OFF                do {FLASH_N_CS_PIN = 1;} while (0)

//
// Common SPI bus
//
#define SPI_CLK_PIN                 LATCbits.LATC0
#define SPI_CLK_DIR                 TRISCbits.TRISC0
#define SPI_CLK_PPS_REG             RPOR8bits.RP16R

#define SPI_MOSI_PIN                LATCbits.LATC1
#define SPI_MOSI_DIR                TRISCbits.TRISC1
#define SPI_MOSI_PPS_REG            RPOR8bits.RP17R
#define SPI_MISO_RP_PIN             (18)

#define SPI_MISO_PIN                PORTCbits.PORTC2
#define SPI_MISO_DIR                TRISCbits.TRISC2
#define SPI_MISO_PPS_REG            RPINR20bits.SDI1R


//
// Debug
//
#define DEBUG_UART_RX_PIN           PORTBbits.PORTB2
#define DEBUG_UART_RX_DIR           TRISBbits.TRISB2
#define DEBUG_UART_RX_PPS_REG       RPINR19bits.U2RXR
#define DEBUG_UART_RX_RP_PIN        (2)

#define DEBUG_UART_TX_PIN           LATBbits.LATB3
#define DEBUG_UART_TX_DIR           TRISBbits.TRISB3
#define DEBUG_UART_TX_PPS_REG       RPOR1bits.RP3R


#define NC1_PIN                     LATBbits.LATB4
#define NC1_DIR                     TRISBbits.TRISB4

#define NC2_PIN                     LATBbits.LATB5
#define NC2_DIR                     TRISBbits.TRISB5

typedef enum
{
    GPIO_PPS_OUT_NULL       = 0,
    GPIO_PPS_OUT_C1OUT      = 1,
    GPIO_PPS_OUT_C2OUT      = 2,
    GPIO_PPS_OUT_U1TX       = 3,
    GPIO_PPS_OUT_U1RTS      = 4,
    GPIO_PPS_OUT_U2TX       = 5,
    GPIO_PPS_OUT_U2RTS      = 6,
    GPIO_PPS_OUT_SDO1       = 7,
    GPIO_PPS_OUT_SCK1OUT    = 8,
    GPIO_PPS_OUT_SS1OUT     = 9,
    GPIO_PPS_OUT_SDO2       = 10,
    GPIO_PPS_OUT_SCK2OUT    = 11,
    GPIO_PPS_OUT_SS2OUT     = 12,
    GPIO_PPS_OUT_OC1        = 18,
    GPIO_PPS_OUT_OC2        = 19,
    GPIO_PPS_OUT_OC3        = 20,
    GPIO_PPS_OUT_OC4        = 21,
    GPIO_PPS_OUT_OC5        = 22
} gpio_pps_output_function_t;

typedef enum
{
    GPIO_CN_PIN_LORA_DIO0,
    GPIO_CN_PIN_LORA_DIO1,
    GPIO_CN_PIN_LORA_DIO2,
    GPIO_CN_PIN_LORA_DIO3,
    GPIO_CN_PIN_LORA_DIO4,
    GPIO_CN_PIN_LORA_DIO5,
} gpio_cn_pin_t;

typedef void (*gpio_cn_callback_t)(bool rising);

typedef struct  gpio_cn_pin_info_t
{
    bool                state;
    bool                cn_enabled;
    gpio_cn_callback_t  callback;
} gpio_cn_pin_info_t;

typedef struct gpio_cn_pin_status_t
{
    gpio_cn_pin_info_t lora_dio0;
    gpio_cn_pin_info_t lora_dio1;
    gpio_cn_pin_info_t lora_dio2;
    gpio_cn_pin_info_t lora_dio3;
    gpio_cn_pin_info_t lora_dio4;
    gpio_cn_pin_info_t lora_dio5;
} gpio_cn_pin_status_t;


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
 * @brief Sets up the GPIOs to their default state.
 */
void gpio_init(void);

/**
 * @brief Registers a callback function to be called when the specified pin
 *        triggers a change notification.
 * @details The callback function will run in isr context.
 * @param pin       - Pin to register the callback for.
 * @param callback  - Function to call at a change notification event.
 */
void gpio_register_cn_handler(gpio_cn_pin_t pin, gpio_cn_callback_t callback);

/**
 * @brief Enables/disables a change notification callback to be generated.
 * @param pin       - Pin to enable/disable change notification for.
 * @param enable    - True if change notification should be enabed, false if
 *                    it should be disabled.
 */
void gpio_enable_cn(gpio_cn_pin_t pin, bool enable);

#ifdef	__cplusplus
}
#endif

#endif	/* GPIO_H */

