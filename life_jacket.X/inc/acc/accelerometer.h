#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

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

typedef struct accelerometer_output_t
{
    uint16_t x;
    uint16_t y;
    uint16_t z;
} accelerometer_output_t;

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
 @brief Initialize the accelerometer.
*/
void accelerometer_init(void);

void accelerometer_get_orientation(accelerometer_output_t * out);


#ifdef  __cplusplus
}
#endif

#endif  /* ACCELEROMETER_H */

