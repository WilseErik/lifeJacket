// =============================================================================
// Include statements
// =============================================================================

#include "acc/accelerometer.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <xc.h>

#include "hal/gpio.h"
#include "acc/lis2hh12_io.h"
#include "uart/debug_log.h"

// =============================================================================
// Private type definitions
// =============================================================================


// =============================================================================
// Global variables
// =============================================================================


// =============================================================================
// Private constants
// =============================================================================
static const uint8_t WHO_AM_I_REG_VALUE = 0x41;

static const uint8_t LIS2HH12_REG_INIT_TABLE[][2] =
{
    {LIS2HH12_REG_ACT_THS,      0x00},
    {LIS2HH12_REG_ACT_DUR,      0x00},
    {LIS2HH12_REG_CTRL1,        0x17},
    {LIS2HH12_REG_CTRL2,        0x00},
    {LIS2HH12_REG_CTRL3,        0x00},
    {LIS2HH12_REG_CTRL4,        0x04},
    {LIS2HH12_REG_CTRL5,        0x00},
    {LIS2HH12_REG_CTRL6,        0x00},
    {LIS2HH12_REG_CTRL7,        0x00},
    {LIS2HH12_REG_FIFO_CTRL,    0x00},
    {LIS2HH12_REG_IG_CFG1,      0x00},
    {LIS2HH12_REG_IG_THS_X1,    0x00},
    {LIS2HH12_REG_IG_THS_Y1,    0x00},
    {LIS2HH12_REG_IG_THS_Z1,    0x00},
    {LIS2HH12_REG_IG_DUR1,      0x00},
    {LIS2HH12_REG_CFG2,         0x00},
    {LIS2HH12_REG_THS2,         0x00},
    {LIS2HH12_REG_DUR2,         0x00},
    {LIS2HH12_REG_XL_REFERENCE, 0x00},
    {LIS2HH12_REG_XH_REFERENCE, 0x00},
    {LIS2HH12_REG_YL_REFERENCE, 0x00},
    {LIS2HH12_REG_YH_REFERENCE, 0x00},
    {LIS2HH12_REG_ZL_REFERENCE, 0x00},
    {LIS2HH12_REG_ZH_REFERENCE, 0x00},
};

#define INIT_TABLE_ENTRY_COUNT (sizeof(LIS2HH12_REG_INIT_TABLE) / 2)

// =============================================================================
// Private variables
// =============================================================================


// =============================================================================
// Private function declarations
// =============================================================================


// =============================================================================
// Public function definitions
// =============================================================================

void accelerometer_init(void)
{
    uint8_t i;

    if (WHO_AM_I_REG_VALUE == lis2hh12_read_register(LIS2HH12_REG_WHO_AM_I))
    {
        debug_log_append_line("LIS2HH12 communication ok");
    }
    else
    {
        debug_log_append_line("LIS2HH12 communication failiure");
        return;
    }

    for (i = 0; i != INIT_TABLE_ENTRY_COUNT; ++i)
    {
        lis2hh12_write_register(LIS2HH12_REG_INIT_TABLE[i][0],
                                LIS2HH12_REG_INIT_TABLE[i][1]);
    }
}

void accelerometer_get_orientation(accelerometer_output_t * out)
{
    memset(out, 0, sizeof(accelerometer_output_t));

    out->x |= ((uint16_t)lis2hh12_read_register(LIS2HH12_REG_OUT_X_H)) << 8;
    out->x |= ((uint16_t)lis2hh12_read_register(LIS2HH12_REG_OUT_X_L));

    out->y |= ((uint16_t)lis2hh12_read_register(LIS2HH12_REG_OUT_Y_H)) << 8;
    out->y |= ((uint16_t)lis2hh12_read_register(LIS2HH12_REG_OUT_Y_L));

    out->z |= ((uint16_t)lis2hh12_read_register(LIS2HH12_REG_OUT_Z_H)) << 8;
    out->z |= ((uint16_t)lis2hh12_read_register(LIS2HH12_REG_OUT_Z_L));
}

// =============================================================================
// Private function definitions
// =============================================================================
