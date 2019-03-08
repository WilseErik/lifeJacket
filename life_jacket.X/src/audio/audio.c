// =============================================================================
// Include statements
// =============================================================================
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include <xc.h>

#include "hal/gpio.h"
#include "audio/audio.h"
#include "audio/dma.h"
#include "audio/pcm1770.h"
#include "audio/ext_flash.h"
#include "status.h"

#include "hal/uart.h"
#include "uart/debug_log.h"

// =============================================================================
// Private type definitions
// =============================================================================

typedef struct audio_flash_header_t
{
    uint16_t number_of_tracks;
} audio_flash_header_t;

typedef struct audio_track_header_t
{
    uint32_t start_address;
    uint32_t number_of_samples;
} audio_track_header_t;

#define AUDIO_TRACK_HEADER_SIZE (8)

typedef struct audio_track_t
{
    uint32_t number_of_samples;
    uint32_t samples_played;
    uint32_t start_address;
    uint32_t next_address;
} audio_track_t;

typedef enum
{
    AUDIO_FLASH_ADDRESS_NUMBER_OF_TRACKS    = 0,
    AUDIO_FLASH_ADDRESS_TRACK_HEADERS_START = 2
} audio_flash_address_t;

// =============================================================================
// Global variables
// =============================================================================

// =============================================================================
// Private constants
// =============================================================================

// =============================================================================
// Private variables
// =============================================================================

static int16_t audio_buffer[AUDIO_BUFFER_LENGTH + AUDIO_BUFFER_LENGTH];
static bool is_using_buffer_a;
static int16_t * buffer_a;
static int16_t * buffer_b;
static int16_t * buffer_a_end;
static int16_t * buffer_b_end;

static audio_track_t track;
static bool playback_session_active = false;;

// =============================================================================
// Private function declarations
// =============================================================================

static int16_t * audio_get_back_buffer(void);
static void audio_load_test_data(void);

static uint16_t audio_get_number_of_tracks(void);
static void get_track_header(audio_track_header_t * header,
                             uint16_t track_number);

// =============================================================================
// Public function definitions
// =============================================================================

void audio_init(void)
{
    buffer_a = &audio_buffer[0];
    buffer_b = &audio_buffer[AUDIO_BUFFER_LENGTH];

    buffer_a_end = &audio_buffer[AUDIO_BUFFER_LENGTH];
    buffer_b_end = &audio_buffer[AUDIO_BUFFER_LENGTH + AUDIO_BUFFER_LENGTH];

    playback_session_active = false;
}

void audio_start_playback_session(uint16_t track_number)
{
    audio_track_header_t track_header;

    audio_init();

    if (track_number >= audio_get_number_of_tracks())
    {
        debug_log_append_line("Tried to play non-existent track.");
        return;
    }

    get_track_header(&track_header, track_number);
    
    track.start_address = track_header.start_address;
    track.number_of_samples = track_header.number_of_samples;

    track.samples_played = 0;
    track.next_address = track.start_address;

    ext_flash_read((uint16_t*)audio_get_front_buffer(),
                   track.next_address,
                   AUDIO_BUFFER_SIZE);

    track.next_address += AUDIO_BUFFER_SIZE;
    track.samples_played += AUDIO_BUFFER_LENGTH;

    ext_flash_read(audio_get_back_buffer(),
                   track.next_address,
                   AUDIO_BUFFER_SIZE);

    track.next_address += AUDIO_BUFFER_SIZE;
    track.samples_played += AUDIO_BUFFER_LENGTH;

    pcm1770_init();
    dma_i2s_ch_init();

    AMP_N_SD_PIN = 1;
    AMP_N_SD_BOOST_PIN = 1;

    playback_session_active = true;

    sprintf(g_uart_string_buffer,
            "Playback of track %u started",
            track_number);
    debug_log_append_line(g_uart_string_buffer);
}

void audio_handle_buffer_update(void)
{
    if (track.samples_played < track.number_of_samples)
    {
        ext_flash_read(audio_get_back_buffer(),
                   track.next_address,
                   AUDIO_BUFFER_SIZE);

        track.next_address += AUDIO_BUFFER_SIZE;
        track.samples_played += AUDIO_BUFFER_LENGTH;
    }
    else
    {
        pcm1770_deinit();
        dma_i2s_ch_deinit();

        AMP_N_SD_PIN = 0;
        AMP_N_SD_BOOST_PIN = 0;

        playback_session_active = false;

        debug_log_append_line("Audio playback finished.");
    }
}

bool audio_is_playback_in_progress(void)
{
    return playback_session_active;
}

const int16_t * audio_get_front_buffer(void)
{
    const int16_t * current_buffer = audio_buffer;

    if (!is_using_buffer_a)
    {
        current_buffer += AUDIO_BUFFER_LENGTH;
    }

    return current_buffer;
}

void audio_switch_buffer(void)
{
    is_using_buffer_a = !is_using_buffer_a;

    status_set(STATUS_AUDIO_BUFFER_UPDATE_EVENT, true);
}

void audio_get_sample_pointer_limits(int16_t ** min, int16_t ** max)
{
    *min = buffer_a;
    *max = buffer_b_end;
}

// =============================================================================
// Private function definitions
// =============================================================================

static int16_t * audio_get_back_buffer(void)
{
    int16_t * current_buffer = audio_buffer;

    if (is_using_buffer_a)
    {
        current_buffer += AUDIO_BUFFER_LENGTH;
    }

    return current_buffer;
}

static void audio_load_test_data(void)
{
    uint16_t i;
    uint16_t k;
    uint16_t index;

    for (i = 0; i != 8; ++i)
    {
        for (k = 0; k != 32; ++k)
        {
            index = i * 64 + k;
            buffer_a[index] = k * 4;
            buffer_b[index] = k * 4;
        }

        for (k = 0; k != 32; ++k)
        {
            index = i * 64 + 32 + k;
            buffer_a[index] = (32 - k) * 4;
            buffer_b[index] = (32 - k) * 4;
        }
    }
    
    ext_flash_chip_erase();

    ext_flash_program_page(&buffer_a[128 * 0], 256 * 0);
    ext_flash_program_page(&buffer_a[128 * 1], 256 * 1);
    ext_flash_program_page(&buffer_a[128 * 2], 256 * 2);
    ext_flash_program_page(&buffer_a[128 * 3], 256 * 3);

    ext_flash_program_page(&buffer_b[128 * 0], 256 * 4);
    ext_flash_program_page(&buffer_b[128 * 1], 256 * 5);
    ext_flash_program_page(&buffer_b[128 * 2], 256 * 6);
    ext_flash_program_page(&buffer_b[128 * 3], 256 * 7);

    for (i = 0; i != 8; ++i)
    {
        for (k = 0; k != 32; ++k)
        {
            index = i * 64 + k;
            buffer_a[index] = 0;
            buffer_b[index] = 0;
        }

        for (k = 0; k != 32; ++k)
        {
            index = i * 64 + 32 + k;
            buffer_a[index] = 0;
            buffer_b[index] = 0;
        }
    }

    ext_flash_read(buffer_a, 0, 1024);
    ext_flash_read(buffer_b, 1024, 1024);

    sprintf(g_uart_string_buffer,
            "Buffer A:\r\n");
    uart_write_string(g_uart_string_buffer);

    for (k = 0; k != 64; ++k)
    {
        sprintf(g_uart_string_buffer,
                "%04X %04X %04X %04X %04X %04X %04X %04X\r\n",
                buffer_a[8 * k + 0],
                buffer_a[8 * k + 1],
                buffer_a[8 * k + 2],
                buffer_a[8 * k + 3],
                buffer_a[8 * k + 4],
                buffer_a[8 * k + 5],
                buffer_a[8 * k + 6],
                buffer_a[8 * k + 7]);
        uart_write_string(g_uart_string_buffer);

        while (!uart_is_write_buffer_empty()){;}
    }

    sprintf(g_uart_string_buffer,
            "\r\n\r\nBuffer B:\r\n");
    uart_write_string(g_uart_string_buffer);

    for (k = 0; k != 64; ++k)
    {
        sprintf(g_uart_string_buffer,
                "%04X %04X %04X %04X %04X %04X %04X %04X\r\n",
                buffer_b[8 * k + 0],
                buffer_b[8 * k + 1],
                buffer_b[8 * k + 2],
                buffer_b[8 * k + 3],
                buffer_b[8 * k + 4],
                buffer_b[8 * k + 5],
                buffer_b[8 * k + 6],
                buffer_b[8 * k + 7]);
        uart_write_string(g_uart_string_buffer);

        while (!uart_is_write_buffer_empty()){;}
    }

    track.number_of_samples = 1024;
    track.samples_played = 0;
    track.start_address = 0;
    track.next_address = 0;
}

static uint16_t audio_get_number_of_tracks(void)
{
    return ext_flash_read_word(AUDIO_FLASH_ADDRESS_NUMBER_OF_TRACKS);
}

static void get_track_header(audio_track_header_t * header,
                             uint16_t track_number)
{
    uint32_t header_address = AUDIO_FLASH_ADDRESS_TRACK_HEADERS_START +
                              (AUDIO_TRACK_HEADER_SIZE * track_number);

    header->start_address = ext_flash_read_dword(header_address);
    header->number_of_samples = ext_flash_read_dword(header_address + 4);
}