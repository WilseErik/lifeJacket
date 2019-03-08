/*
 * This file forms a hardware abstraction layer for the DMA module
 * which is uesd in order to move data between perhipherials and memory without
 * involving the CPU.
 *
 * References:
 *  - PIC24FJ128GA202 datasheet, document number DS30010038C
 *  - dsPIC33/PIC24 Family Reference Manual, Direct Memory Access controller,
 *    document number   DS39742A
 */


// =============================================================================
// Include statements
// =============================================================================
#include <stdint.h>
#include <stdbool.h>

#include <xc.h>

#include "audio/dma.h"
#include "audio/audio.h"

// =============================================================================
// Private type definitions
// =============================================================================

// =============================================================================
// Global variables
// =============================================================================
volatile int16_t g_audio_tx_buff = 0;

// =============================================================================
// Private constants
// =============================================================================

//
// Reference: DS30010038C-page 74
//            TABLE 5-1: DMA CHANNEL TRIGGER SOURCES
//
typedef enum
{
    DMA_TRIGGER_NULL                = 0x00,
    DMA_TRIGGER_SPI3_GENERAL_EV     = 0x01,
    DMA_TRIGGER_I2C1_SLAVE_EV       = 0x02,
    DMA_TRIGGER_UART4_TRANSMIT_EV   = 0x03,
    DMA_TRIGGER_UART4_RECEIVE_EV    = 0x04,
    DMA_TRIGGER_UART4_ERROR         = 0x05,
    DMA_TRIGGER_UART3_TRANSMIT_EV   = 0x06,
    DMA_TRIGGER_UART3_RECEIVE_EV    = 0x07,
    DMA_TRIGGER_UART3_ERROR         = 0x08,
    DMA_TRIGGER_CTMU_EV             = 0x09,
    DMA_TRIGGER_HLVD                = 0x0A,
    DMA_TRIGGER_CRC_DONE            = 0x0B,
    DMA_TRIGGER_UART2_ERROR         = 0x0C,
    DMA_TRIGGER_UART1_ERROR         = 0x0D,
    DMA_TRIGGER_RTCC                = 0x0E,
    DMA_TRIGGER_DMA_CH5             = 0x0F,
    DMA_TRIGGER_EXT_INT_4           = 0x10,
    DMA_TRIGGER_EXT_INT_3           = 0x11,
    DMA_TRIGGER_SPI2_RECEIVE_EV     = 0x12,
    DMA_TRIGGER_I2C2_MSTR_EV        = 0x13,
    DMA_TRIGGER_DMA_CH4             = 0x14,
    DMA_TRIGGER_EPMP                = 0x15,
    DMA_TRIGGER_SPI1_RECEIVE_EV     = 0x16,
    DMA_TRIGGER_OUTPUT_COMPARE_6    = 0x17,
    DMA_TRIGGER_OUTPUT_COMPARE_5    = 0x18,
    DMA_TRIGGER_INPUT_CAPTURE_6     = 0x19,
    DMA_TRIGGER_INPUT_CAPTURE_5     = 0x1A,
    DMA_TRIGGER_INPUT_CAPTURE_4     = 0x1B,
    DMA_TRIGGER_INPUT_CAPTURE_3     = 0x1C,
    DMA_TRIGGER_DMA_CH3             = 0x1D,
    DMA_TRIGGER_SPI2_TRANSMIT_EV    = 0x1E,
    DMA_TRIGGER_SPI2_GENERAL_EV     = 0x1F,
    //
    // ... 
    //
    DMA_TRIGGER_CRYPTOGRAPHIC_DONE  = 0x3F
} dma_channel_trigger_source_t;

// =============================================================================
// Private variables
// =============================================================================

// =============================================================================
// Private function declarations
// =============================================================================

/**
 * @brief Initializes the DMA module.
 * @param void
 * @return void
 */
void dma_init(void);

// =============================================================================
// Public function definitions
// =============================================================================

void dma_i2s_ch_init(void)
{
    dma_init();

    DMACH0bits.CHEN = 0;    // Disable channel 0

    DMASRC0 = (uint16_t)audio_get_front_buffer();
    DMADST0 = (uint16_t)&SPI2BUFL;

    DMACNT0 = AUDIO_BUFFER_LENGTH;    // n transfers before an interrupt is 
                                    //      generated (mono not LR)
    DMACH0bits.SIZE = 0;    // 16 bit transfer
    DMACH0bits.TRMODE = 0;  // One-shot mode
    DMACH0bits.SAMODE = 1;  // DMASRC is incremented based on SIZE bit after a transfer completion
    DMACH0bits.DAMODE = 0;  // DMADST unchanged after a transfer completion
    DMACH0bits.RELOAD = 0;  // DMASRC, DMADST and DMACNT are not reloaded on the start of the next operation
    
    DMACH0bits.CHEN = 1;

    DMAINT0bits.CHSEL = DMA_TRIGGER_SPI2_TRANSMIT_EV;

    IFS0bits.DMA0IF = 0;
    IPC1bits.DMA0IP = 6;
    IEC0bits.DMA0IE = 1;

    SPI2BUFL = 0;           // Start the first transfer
}

void dma_i2s_ch_deinit(void)
{
    IEC0bits.DMA0IE = 0;
    DMACH0bits.CHEN = 0;
}

// =============================================================================
// Private function definitions
// =============================================================================

void dma_init(void)
{
    int16_t * min_limit;
    int16_t * max_limit;

    audio_get_sample_pointer_limits(&min_limit, &max_limit);

    DMACONbits.DMAEN = 1;   // Enable the DMA
    DMACONbits.PRSSEL = 0;  // Fixed priority scheme

    DMAL = (uint16_t)min_limit - 4;
    DMAH = (uint16_t)max_limit + 4;
}

void __attribute((interrupt, no_auto_psv)) _DMA0Interrupt()
{
    DMACH0bits.CHEN = 1;
    
    DMAINT0 &= 0xFF00;      // Clear the interrupt flags

    audio_switch_buffer();

    DMASRC0 = (uint16_t)audio_get_front_buffer();
    DMADST0 = (uint16_t)&SPI2BUFL;
    DMACNT0 = AUDIO_BUFFER_LENGTH;

    IFS2bits.SPI2TXIF = 0;  // Clear the trigger source
    IFS0bits.DMA0IF = 0;
}

