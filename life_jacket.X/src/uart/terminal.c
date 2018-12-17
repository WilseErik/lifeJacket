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
#include "uart/terminal_help.h"
#include "hal/gpio.h"
#include "hal/flash.h"
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
 Gets one byte from the flash data memory.
 Parameter: <index in hex format>
 Returns: <hex value of byte at specified index>
 */
static const char GET_FLASH[]       = "get flash";

static const char SET_FLASH[]       = "set flash";

// =============================================================================
// Private variables
// =============================================================================

static char cmd_buffer[CMD_BUFFER_SIZE] = {0};
static bool arg_error = false;

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

static void cmd_init_flash_buffer(void);
static void cmd_buffered_write(void);
static void cmd_flush_buffer(void);

static void get_flash(void);
static void set_flash(void);

// =============================================================================
// Public function definitions
// =============================================================================

void terminal_handle_uart_event(void)
{
    copy_to_cmd_buffer();
    execute_command();
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
    else if (NULL != strstr(cmd_buffer, CMD_TYPE_GET))
    {
        if (NULL != strstr(cmd_buffer, GET_FLASH))
        {
            get_flash();
        }
        else
        {
            syntax_error = true;
        }
    }
    else if (NULL != strstr(cmd_buffer, CMD_TYPE_SET))
    {
        if (NULL != strstr(cmd_buffer, SET_FLASH))
        {
            set_flash();
        }
        else
        {
            syntax_error = true;
        }
    }
    else
    {
        if (NULL != strstr(cmd_buffer, CMD_HELLO))
        {
            cmd_hello();
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
}

static void cmd_hello(void)
{
    uart_write_string("Hello!");
    uart_write_string(NEWLINE);
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
