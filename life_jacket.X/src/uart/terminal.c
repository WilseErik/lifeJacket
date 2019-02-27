// =============================================================================
// Include statements
// =============================================================================
#include "uart\terminal.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "hal/uart.h"
#include "uart/debug_log.h"
#include "uart/terminal_help.h"
#include "hal/gpio.h"
#include "hal/flash.h"
#include "gps/jf2_uart.h"
#include "gps/jf2_io.h"
#include "gps/nmea.h"
#include "acc/accelerometer.h"
#include "lora/rfm95w.h"
#include "lora/rfm95w_io.h"
#include "lora/p2pc_protocol.h"
#include "audio/ext_flash.h"
#include "audio/audio.h"

// =============================================================================
// Private type definitions
// =============================================================================

// =============================================================================
// Global variables
// =============================================================================

// =============================================================================
// Private constants
// =============================================================================

#define HEX_BYTE_STR_LEN  (2 + 1)
#define HEX_WORD_STR_LEN  (4 + 1)
#define HEX_DWORD_STR_LEN (8 + 1)

static const char NEWLINE[]         = "\r\n";

static const char CMD_TYPE_HELP[]   = "help";
static const char CMD_TYPE_SET[]    = "set ";
static const char CMD_TYPE_GET[]    = "get ";

static const char SYNTAX_ERROR[]    = "[Syntax error]";
static const char ARGUMENT_ERROR[]  = "[Invalid argument]";

#define CMD_BUFFER_SIZE 257

//
// Commands
//

/*§
 Say hi!
 */
static const char CMD_HELLO[]       = "hello";

/*§
 Forces a software reboot.
 */
static const char CMD_SYSTEM_RESET[] = "system reset";

/*§
 Initiates the flash write buffer with the contents of theflash data memory.
 */
static const char CMD_INIT_WRITE_BUFFER[] = "init flash bufffer";

/*§
 Writes one byte to the flash buffer.
 Paramters: <index in hex format> <one byte value in hex format>
 */
static const char CMD_BUFFERED_WRITE[] = "buffered write";

/*§
 Write the contents of the flash buffer to the flash memory.
 */
static const char CMD_FLUSH_BUFFER[]    = "flush flash buffer";

/*§
 Starts a LORA CW transmission.
 */
static const char CMD_LORA_CW[]         = "lora cw";

/*§
 Starts a LoRa GPS position broadcast.
 */
static const char CMD_LORA_GPS_BROADCAST[] = "lora gps broadcast";

/*§
 Starts continuous rx LoRa mode.
 */
static const char CMD_LORA_CONTIUOUS_RX[] = "lora cont rx";

/*§
 Sends a on/off pulse to the GPS module.
 */
static const char CMD_GPS_ON_OFF_PULSE[] = "gps on off pulse";

/*§
 Erases the whole external flash memory.
 */
static const char CMD_EXT_FLASH_CHIP_ERASE[] = "ext flash chip erase";

/*§
 Writes test data to the first page (first 256 bytes).
*/
static const char CMD_EXT_FLASH_WRITE_TEST[] = "ext flash write test";

/*§
 Runs a audio session test.
*/
static const char CMD_TEST_AUDIO_SESSION[] = "test audio session";

/*§
 Writes test audio data to the external flash memory.
*/
static const char CMD_WRITE_AUDIO_TEST_DATA[] = "write audio test data";

/*§
 Gets one byte from the flash data memory.
 Parameter: <index in hex format>
 Returns: <hex value of byte at specified index>
 */
static const char GET_FLASH[]       = "get flash";

/*§
 Gets one byte from the external flash memory.
 Parameter: <address in hex>
 Returns: <read byte in hex format>
 */
static const char GET_EXT_FLASH[]   = "get ext flash";

/*§
 Gets 256 of bytes from the external flash memory.
 Parameters: <start address in hex>
*/
static const char GET_PAGE_EXT_FLASH[] = "get page ext flash";

/*§
 Gets the status of the GPS.
 */
static const char GET_GPS_STATUS[]  = "get gps status";

/*§
 Gets the x, y, z values from the accelerometer.
 */
static const char GET_ORIENTATION[] = "get orientation";

/*§
 Sets one byte in the flash data memory.
 Paramter: <index in hex format> <one byte value in hex format>
 */
static const char SET_FLASH[]       = "set flash";

/*§
 Enabled/disables received GPS messages from being echoed onto the debug UART.
 Paramter: <'on' or 'off'>
 */
static const char SET_GPS_ECHO[]    = "set gps echo";

/*§
 Sets the LoRa channel bandwidth.
 Parameter: <bandwidth setting in range [0, 9]>

 0 = 7.8kHz
 1 = 10.4kHz
 2 = 15.6 kHz
 3 = 20.8 kHz
 4 = 31.25 kHz
 5 = 41.7 kHz
 6 = 62.5 kHz
 7 = 125 kHz
 8 = 250 kHz
 9 = 500 kHz
*/
static const char SET_LORA_BANDWIDTH[] = "set lora bw";

/*§
 Sets the LoRa coding rate.
 Parameter: <coding rate setting in range[1, 4]>

 1 = coding rate 4/5
 2 = coding rate 4/6
 3 = coding rate 4/7
 4 = coding rate 4/8
 */
static const char SET_LORA_CODING_RATE[] = "set lora cr";

/*§
 Sets the LoRa spreading factor.
 Parameter: <spreading factor in range [6, 12]>

 A spreading factor of 'sf' gives 2^(sf) chips 
 */
static const char SET_LORA_SPREADING_FACTOR[] = "set lora sf";

/*§
 Sets the LoRa frequency.
 Parameter: <frequency band in range [1, 8]>

 Bands:
 1 = 868.1 MHz
 2 = 868.3 MHz
 3 = 868.5 MHz
 4 = 867.1 MHz
 5 = 867.3 MHz
 6 = 867.5 MHz
 7 = 867.7 MHz
 8 = 867.9 MHz
 */
static const char SET_LORA_FREQUENCY[] = "set lora freq";

/*§
 Enables/disables sleep mode.
 Paramter: <'on' or 'off'>
*/
static const char SET_SLEEP_ALLOWED[] = "set sleep allowed";

// =============================================================================
// Private variables
// =============================================================================

static char cmd_buffer[CMD_BUFFER_SIZE] = {0};
static bool arg_error = false;
static bool is_sleep_allowed = true;

// =============================================================================
// Private function declarations
// =============================================================================

/**
 * @brief Copies the uart rx buffer to the cmd_buffer.
 */
static void copy_to_cmd_buffer(void);

/**
 * @brief Parses and executes the command in the command buffer.
 */
static void execute_command(void);

//
// Command help functions
//
static void cmd_hello(void);
static void cmd_system_reset(void);
static void cmd_init_flash_buffer(void);
static void cmd_buffered_write(void);
static void cmd_flush_buffer(void);
static void cmd_lora_cw(void);
static void cmd_lora_gps_broadcast(void);
static void cmd_lora_contiuous_rx(void);
static void cmd_gps_on_off_pulse(void);
static void cmd_ext_flash_chip_erase(void);
static void cmd_ext_flash_write_test(void);
static void cmd_test_audio_session(void);
static void cmd_write_audio_test_data(void);

static void get_flash(void);
static void get_ext_flash(void);
static void get_page_ext_flash(void);
static void get_gps_status(void);
static void get_orientation(void);

static void set_flash(void);
static void set_gps_echo(void);
static void set_lora_bandwidth(void);
static void set_lora_coding_rate(void);
static void set_lora_spreading_factor(void);
static void set_lora_frequency_band(void);
static void set_sleep_allowed(void);

// =============================================================================
// Public function definitions
// =============================================================================

void terminal_handle_uart_event(void)
{
    copy_to_cmd_buffer();
    execute_command();
}

bool termnial_allows_sleep(void)
{
    return is_sleep_allowed;
}

// =============================================================================
// Private function definitions
// =============================================================================

static void copy_to_cmd_buffer(void)
{
    uint16_t nbr_of_bytes;
    uint16_t current_index = 0;

    nbr_of_bytes = uart_get_receive_buffer_size();

    for (current_index = 0; current_index != nbr_of_bytes; ++current_index)
    {
        cmd_buffer[current_index] = (char)uart_get(current_index);
    }

    cmd_buffer[current_index] = NULL;

    uart_clear_receive_buffer();
}

static void execute_command(void)
{
    bool syntax_error = false;
    arg_error = false;

    if (NULL != strstr(cmd_buffer, CMD_TYPE_HELP))
    {
        terminal_help(cmd_buffer);
    }
    //
    // GET
    //
    else if (NULL != strstr(cmd_buffer, CMD_TYPE_GET))
    {
        if (NULL != strstr(cmd_buffer, GET_FLASH))
        {
            get_flash();
        }
        else if (NULL != strstr(cmd_buffer, GET_EXT_FLASH))
        {
            get_ext_flash();
        }
        else if (NULL != strstr(cmd_buffer, GET_PAGE_EXT_FLASH))
        {
            get_page_ext_flash();
        }
        else if (NULL != strstr(cmd_buffer, GET_GPS_STATUS))
        {
            get_gps_status();
        }
        else if (NULL != strstr(cmd_buffer, GET_ORIENTATION))
        {
            get_orientation();
        }
        else
        {
            syntax_error = true;
        }
    }
    //
    // SET
    //
    else if (NULL != strstr(cmd_buffer, CMD_TYPE_SET))
    {
        if (NULL != strstr(cmd_buffer, SET_FLASH))
        {
            set_flash();
        }
        else if (NULL != strstr(cmd_buffer, SET_GPS_ECHO))
        {
            set_gps_echo();
        }
        else if (NULL != strstr(cmd_buffer, SET_LORA_BANDWIDTH))
        {
            set_lora_bandwidth();
        }
        else if (NULL != strstr(cmd_buffer, SET_LORA_CODING_RATE))
        {
            set_lora_coding_rate();
        }
        else if (NULL != strstr(cmd_buffer, SET_LORA_SPREADING_FACTOR))
        {
            set_lora_spreading_factor();
        }
        else if (NULL != strstr(cmd_buffer, SET_LORA_FREQUENCY))
        {
            set_lora_frequency_band();
        }
        else if (NULL != strstr(cmd_buffer, SET_SLEEP_ALLOWED))
        {
            set_sleep_allowed();
        }
        else
        {
            syntax_error = true;
        }
    }
    //
    // CMD
    //
    else
    {
        if (NULL != strstr(cmd_buffer, CMD_HELLO))
        {
            cmd_hello();
        }
        else if (NULL != strstr(cmd_buffer, CMD_SYSTEM_RESET))
        {
            cmd_system_reset();
        }
        else if (NULL != strstr(cmd_buffer, CMD_INIT_WRITE_BUFFER))
        {
            cmd_init_flash_buffer();
        }
        else if (NULL != strstr(cmd_buffer, CMD_BUFFERED_WRITE))
        {
            cmd_buffered_write();
        }
        else if (NULL != strstr(cmd_buffer, CMD_FLUSH_BUFFER))
        {
            cmd_flush_buffer();
        }
        else if (NULL != strstr(cmd_buffer, CMD_LORA_CW))
        {
            cmd_lora_cw();
        }
        else if (NULL != strstr(cmd_buffer, CMD_LORA_GPS_BROADCAST))
        {
            cmd_lora_gps_broadcast();
        }
        else if (NULL != strstr(cmd_buffer, CMD_LORA_CONTIUOUS_RX))
        {
            cmd_lora_contiuous_rx();
        }
        else if (NULL != strstr(cmd_buffer, CMD_GPS_ON_OFF_PULSE))
        {
            cmd_gps_on_off_pulse();
        }
        else if (NULL != strstr(cmd_buffer, CMD_EXT_FLASH_CHIP_ERASE))
        {
            cmd_ext_flash_chip_erase();
        }
        else if (NULL != strstr(cmd_buffer, CMD_EXT_FLASH_WRITE_TEST))
        {
            cmd_ext_flash_write_test();
        }
        else if (NULL != strstr(cmd_buffer, CMD_TEST_AUDIO_SESSION))
        {
            cmd_test_audio_session();
        }
        else if (NULL != strstr(cmd_buffer, CMD_WRITE_AUDIO_TEST_DATA))
        {
            cmd_write_audio_test_data();
        }
        else
        {
            syntax_error = true;
        }
    }

    if (syntax_error)
    {
        uart_write_string(SYNTAX_ERROR);
        uart_write_string(NEWLINE);
    }
    else if (arg_error)
    {
        uart_write_string(ARGUMENT_ERROR);
        uart_write_string(NEWLINE);
    }
    else
    {
        uart_write_string("ok");
        uart_write_string(NEWLINE);
    }
}

static void cmd_hello(void)
{
    uart_write_string("Hello!");
    uart_write_string(NEWLINE);
}

static void cmd_system_reset(void)
{
    __asm__ volatile ("reset");
}

static void cmd_init_flash_buffer(void)
{
    flash_init_write_buffer();
}

static void cmd_buffered_write(void)
{
    uint8_t * p;
    char address_arg[HEX_WORD_STR_LEN] = {0};
    char value_arg[HEX_BYTE_STR_LEN] = {0};

    p = (uint8_t*)strstr(cmd_buffer, SET_FLASH);
    p += strlen(SET_FLASH);
    p += 1;     // +1 for space

    if (!isxdigit(*p))
    {
        arg_error = true;
    }
    else
    {
        uint8_t i = 0;
        uint16_t address;
        uint8_t value;

        //
        // Parse address argument
        //
        while ((i != HEX_WORD_STR_LEN) && isxdigit(*p))
        {
            address_arg[i++] = *(p++);
        }

        address_arg[i] = NULL;
        arg_error = arg_error || (i == 0);
        address = (uint16_t)strtol(address_arg, NULL, 16);

        //
        // Parse value argument
        //
        p += 1; // +1 for space
        i = 0;

        while ((i != HEX_BYTE_STR_LEN) && isxdigit(*p))
        {
            value_arg[i++] = *(p++);
        }

        value_arg[i] = NULL;
        arg_error = arg_error || (i == 0);
        value = (uint8_t)strtol(value_arg, NULL, 16);

        //
        // Perform flash write
        //
        if (!arg_error && (address < FLASH_MEM_SIZE))
        {
            flash_write_byte_to_buffer((flash_index_t)address, value);
        }
        else
        {
            arg_error = true;
        }
    }
}

static void cmd_flush_buffer(void)
{
    flash_write_buffer_to_flash();
}

static void cmd_lora_cw(void)
{
    rfm95w_init();
    rfmw_send_cw();
}

static void cmd_lora_gps_broadcast(void)
{
    p2pc_protocol_broadcast_gps_position();
}

static void cmd_lora_contiuous_rx(void)
{
    rfm95w_start_continuous_rx();
}

static void cmd_gps_on_off_pulse(void)
{
    jf2_io_send_on_pulse();
}

static void cmd_ext_flash_chip_erase(void)
{
    ext_flash_chip_erase();
}

static void cmd_ext_flash_write_test(void)
{
    uint8_t test_data[EXT_FLASH_PAGE_LENGTH];
    uint16_t i;

    for (i = 0; i != EXT_FLASH_PAGE_LENGTH; ++i)
    {
        test_data[i] = i;
    }

    ext_flash_program_page(test_data, 0);

    for (i = 0; i != EXT_FLASH_PAGE_LENGTH; ++i)
    {
        test_data[i] = (uint8_t)(i << 1);
    }

    ext_flash_program_page(test_data, 256);
}

static void cmd_test_audio_session(void)
{
    audio_start_playback_session(0);
}

static void cmd_write_audio_test_data(void)
{
    uint16_t i;
    uint16_t k;
    uint16_t index;
    uint16_t page[128];
    
    ext_flash_chip_erase();

    for (i = 0; i != 128; ++i)
    {
        page[i] = 0x0000;
    }

    page[0] = 1;    // number of tracks

    // Track header for track 0:
    page[1 + 0] = 0;        // start address 256
    page[1 + 1] = 256;
    page[1 + 2] = 0x0004;   // 4c400 samples (610*512)
    page[1 + 3] = 0xc400;

    ext_flash_program_page(page, 0);

    for (i = 0; i != 2; ++i)
    {
        for (k = 0; k != 32; ++k)
        {
            index = i * 64 + k;
            page[index] = k * 4;
        }

        for (k = 0; k != 32; ++k)
        {
            index = i * 64 + 32 + k;
            page[index] = (32 - k) * 4;
        }
    }

    for (i = 0; i != 610; ++i)
    {
        uint16_t page_number = (2 + i);
        uint32_t address = ((uint32_t)page_number) << 8;

        page[0] = i;
        ext_flash_program_page(page, address);        
    }

    debug_log_append_line("Audio test data written!");
}

static void get_flash(void)
{
    uint8_t * p;
    char address_arg[HEX_WORD_STR_LEN] = {0};

    p = (uint8_t*)strstr(cmd_buffer, GET_FLASH);
    p += strlen(GET_FLASH);
    p += 1;     // +1 for space

    if (!isxdigit(*p))
    {
        arg_error = true;
    }
    else
    {
        uint8_t i = 0;
        uint16_t address;

        //
        // Parse address argument
        //
        while ((i != HEX_WORD_STR_LEN) && isxdigit(*p))
        {
            address_arg[i++] = *(p++);
        }

        address_arg[i] = NULL;
        address = (uint16_t)strtol(address_arg, NULL, 16);

        //
        // Perform flash read
        //
        if (address < FLASH_MEM_SIZE)
        {
            uint8_t value;
            char ans[32];
            
            value = flash_read_byte((flash_index_t)address);
            sprintf(ans, "%02X%s", value, NEWLINE);
            uart_write_string(ans);
        }
        else
        {
            arg_error = true;
        }
    }
}

static void get_ext_flash(void)
{
    uint8_t * p;
    char address_arg[HEX_DWORD_STR_LEN] = {0};

    p = (uint8_t*)strstr(cmd_buffer, GET_EXT_FLASH);
    p += strlen(GET_EXT_FLASH);
    p += 1;     // +1 for space

    if (!isxdigit(*p))
    {
        arg_error = true;
    }
    else
    {
        uint8_t i = 0;
        uint32_t address;

        //
        // Parse address argument
        //
        while ((i != HEX_DWORD_STR_LEN) && isxdigit(*p))
        {
            address_arg[i++] = *(p++);
        }

        address_arg[i] = NULL;
        address = (uint32_t)strtol(address_arg, NULL, 16);

        //
        // Perform flash read
        //
        if (address < 0x01000000)
        {
            uint8_t value;
            char ans[32];
            
            value = ext_flash_read_byte(address);
            sprintf(ans, "%02X%s", value, NEWLINE);
            uart_write_string(ans);
        }
        else
        {
            arg_error = true;
        }
    }
}

static void get_page_ext_flash(void)
{
    uint8_t * p;
    char address_arg[HEX_DWORD_STR_LEN] = {0};

    p = (uint8_t*)strstr(cmd_buffer, GET_PAGE_EXT_FLASH);
    p += strlen(GET_PAGE_EXT_FLASH);
    p += 1;     // +1 for space

    if (!isxdigit(*p))
    {
        arg_error = true;
    }
    else
    {
        uint8_t i = 0;
        uint32_t address;
        uint16_t page[128];

        //
        // Parse address argument
        //
        while ((i != HEX_DWORD_STR_LEN) && isxdigit(*p))
        {
            address_arg[i++] = *(p++);
        }

        address_arg[i] = NULL;
        arg_error = arg_error || (i == 0);
        address = (uint32_t)strtol(address_arg, NULL, 16);

        //
        // Perform flash read
        //
        if (!arg_error && (address < 0x01000000))
        {
            uint16_t k = 0;

            ext_flash_read(&page[0], address, 256);

            sprintf(g_uart_string_buffer,
                    "\r\n");
            uart_write_string(g_uart_string_buffer);

            for (k = 0; k != 16; ++k)
            {
                sprintf(g_uart_string_buffer,
                        "%04X %04X %04X %04X %04X %04X %04X %04X\r\n",
                        page[8 * k + 0],
                        page[8 * k + 1],
                        page[8 * k + 2],
                        page[8 * k + 3],
                        page[8 * k + 4],
                        page[8 * k + 5],
                        page[8 * k + 6],
                        page[8 * k + 7]);
                uart_write_string(g_uart_string_buffer);

                while (!uart_is_write_buffer_empty()){;}
            }
        }
        else
        {
            arg_error = true;
        }
    }
}

static void get_gps_status(void)
{
    nmea_print_status();
}

static void get_orientation(void)
{
    accelerometer_output_t xyz;
    char s[32] = {0};

    accelerometer_get_orientation(&xyz);

    sprintf(s, "\tx: %u", xyz.x);
    uart_write_string(s);
    sprintf(s, "\r\n\ty: %u", xyz.y);
    uart_write_string(s);
    sprintf(s, "\r\n\tz: %u\r\n", xyz.z);
    uart_write_string(s);
}

static void set_flash(void)
{
    uint8_t * p;
    char address_arg[HEX_WORD_STR_LEN] = {0};
    char value_arg[HEX_BYTE_STR_LEN] = {0};

    p = (uint8_t*)strstr(cmd_buffer, SET_FLASH);
    p += strlen(SET_FLASH);
    p += 1;     // +1 for space

    if (!isxdigit(*p))
    {
        arg_error = true;
    }
    else
    {
        uint8_t i = 0;
        uint16_t address;
        uint8_t value;

        //
        // Parse address argument
        //
        while ((i != HEX_WORD_STR_LEN) && isxdigit(*p))
        {
            address_arg[i++] = *(p++);
        }

        address_arg[i] = NULL;
        arg_error = arg_error || (i == 0);
        address = (uint16_t)strtol(address_arg, NULL, 16);

        //
        // Parse value argument
        //
        p += 1; // +1 for space
        i = 0;
        
        while ((i != HEX_BYTE_STR_LEN) && isxdigit(*p))
        {
            value_arg[i++] = *(p++);
        }

        value_arg[i] = NULL;
        arg_error = arg_error || (i == 0);
        value = (uint8_t)strtol(value_arg, NULL, 16);
        
        //
        // Perform flash write
        //
        if (!arg_error && (address < FLASH_MEM_SIZE))
        {
            flash_init_write_buffer();
            flash_write_byte_to_buffer((flash_index_t)address, value);
            flash_write_buffer_to_flash();
        }
        else
        {
            arg_error = true;
        }
    }
}

static void set_gps_echo(void)
{
    uint8_t * p;

    p = (uint8_t*)strstr(cmd_buffer, SET_GPS_ECHO);
    p += strlen(SET_GPS_ECHO);
    p += 1;     // +1 for space

    if (('o' == *p) && ('n' == *(p + 1)))
    {
        jf2_uart_enable_debug_uart_echo(true);
    } else if (('o' == *p) && ('f' == *(p + 1)) && ('f' == *(p + 2)))
    {
        jf2_uart_enable_debug_uart_echo(false);
    }
    else
    {
        arg_error = true;
    }
}

static void set_lora_bandwidth(void)
{
    uint8_t * p;
    char bandwidth_arg[2] = {0};

    p = (uint8_t*)strstr(cmd_buffer, SET_LORA_BANDWIDTH);
    p += strlen(SET_LORA_BANDWIDTH);
    p += 1;     // +1 for space

    if (!isdigit(*p))
    {
        arg_error = true;
    }
    else
    {
        uint8_t bandwidth;
        bandwidth_arg[0] = *p;

        bandwidth = (uint8_t)strtol(bandwidth_arg, NULL, 10);

        if ((bandwidth >= RFM95W_BW_7K8) && (bandwidth <= RFM95W_BW_500K))
        {
            rfm95w_io_set_bandwidth((rfm95w_modem_cfg_bw_t)bandwidth);
        }
        else
        {
            arg_error = true;
        }
    }
}

static void set_lora_coding_rate(void)
{
    uint8_t * p;
    char coding_rate_arg[2] = {0};

    p = (uint8_t*)strstr(cmd_buffer, SET_LORA_CODING_RATE);
    p += strlen(SET_LORA_CODING_RATE);
    p += 1;     // +1 for space

    if (!isdigit(*p))
    {
        arg_error = true;
    }
    else
    {
        uint8_t coding_rate;
        coding_rate_arg[0] = *p;

        coding_rate = (uint8_t)strtol(coding_rate_arg, NULL, 10);

        if ((coding_rate >= RFM95W_CODING_RATE_4_5) &&
            (coding_rate <= RFM95W_CODING_RATE_4_8))
        {
            rfm95w_io_set_coding_rate((rfm95w_coding_rate_t)coding_rate);
        }
        else
        {
            arg_error = true;
        }
    }
}

static void set_lora_spreading_factor(void)
{
    uint8_t * p;
    char spreading_factor_arg[3] = {0};

    p = (uint8_t*)strstr(cmd_buffer, SET_LORA_SPREADING_FACTOR);
    p += strlen(SET_LORA_SPREADING_FACTOR);
    p += 1;     // +1 for space

    if (!isdigit(*p))
    {
        arg_error = true;
    }
    else
    {
        uint8_t spreading_factor;
        spreading_factor_arg[0] = *p;
        ++p;

        if (isdigit(*p))
        {
            spreading_factor_arg[1] = *p;
        }

        spreading_factor = (uint8_t)strtol(spreading_factor_arg, NULL, 10);

        if ((spreading_factor >= RFM95W_SPREADING_FACTOR_64_CHIPS) &&
            (spreading_factor <= RFM95W_SPREADING_FACTOR_4096_CHIPS))
        {
            rfm95w_io_set_speading_factor((rfm95w_spreading_factor_t)spreading_factor);
        }
        else
        {
            arg_error = true;
        }
    }
}

static void set_lora_frequency_band(void)
{
    uint8_t * p;
    char frequency_arg[2] = {0};

    p = (uint8_t*)strstr(cmd_buffer, SET_LORA_FREQUENCY);
    p += strlen(SET_LORA_FREQUENCY);
    p += 1;     // +1 for space

    if (!isdigit(*p))
    {
        arg_error = true;
    }
    else
    {
        uint8_t frequency;
        frequency_arg[0] = *p;

        frequency = (uint8_t)strtol(frequency_arg, NULL, 10);

        if ((frequency >= RFM95W_CHANNEL_FREQUENCY_868_1) &&
            (frequency <= RFM95W_CHANNEL_FREQUENCY_867_9))
        {
            rfm95w_io_set_frequency((rfm95w_channel_frequency_t)frequency);
        }
        else
        {
            arg_error = true;
        }
    }
}

static void set_sleep_allowed(void)
{
    uint8_t * p;

    p = (uint8_t*)strstr(cmd_buffer, SET_SLEEP_ALLOWED);
    p += strlen(SET_SLEEP_ALLOWED);
    p += 1;     // +1 for space

    if (('o' == *p) && ('n' == *(p + 1)))
    {
        is_sleep_allowed = true;
    }
    else if (('o' == *p) && ('f' == *(p + 1)) && ('f' == *(p + 2)))
    {
        is_sleep_allowed = false;
    }
    else
    {
        arg_error = true;
    }
}
