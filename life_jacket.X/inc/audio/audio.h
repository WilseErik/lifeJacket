#ifndef AUDIO_H
#define AUDIO_H

#ifdef  __cplusplus
extern "C" {
#endif

// =============================================================================
// Include statements
// =============================================================================
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

#define AUDIO_BUFFER_LENGTH (512)
#define AUDIO_BUFFER_SIZE   (AUDIO_BUFFER_LENGTH * 2)

// =============================================================================
// Public function declarations
// =============================================================================

/**
 @brief Initializes the audio module.
*/
void audio_init(void);

/**
 @brief Starts an audio playback session.
 @param track_number    - Number of the track to play.
*/
void audio_start_playback_session(uint16_t track_number);

/**
 @brief Fills the audio back buffer if there is more data, or ends the
        playback session if the track has finished.
*/
void audio_handle_buffer_update(void);

/**
 @brief Checks if an audio playback is active.
 @return True if an audio track is being played.
 */
bool audio_is_playback_in_progress(void);

/**
 @brief Gets the audio front buffer.
 @return Front buffer.
*/
const int16_t * audio_get_front_buffer(void);

/**
 @brief Swaps the front and back buffers.
*/
void audio_switch_buffer(void);

/**
 @brief Gets the min and max addresses used by the audio buffer.
*/
void audio_get_sample_pointer_limits(int16_t ** min, int16_t ** max);

#ifdef  __cplusplus
}
#endif

#endif  /* AUDIO_H */

