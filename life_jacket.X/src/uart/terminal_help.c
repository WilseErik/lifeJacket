/*
This file is an auto generated file.
Do not modify its contents manually!
*/
#include <string.h>
#include <stddef.h>
#include "hal/uart.h"
void terminal_help(char* in)
{
    if (NULL != strstr(in, "hello"))
    {
        uart_write_string("\tSay hi!\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "init flash bufffer"))
    {
        uart_write_string("\tInitiates the flash write buffer with the contents of theflash data memory.\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "buffered write"))
    {
        uart_write_string("\tWrites one byte to the flash buffer.\n\r\tParamters: <index in hex format> <one byte value in hex format>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "flush flash buffer"))
    {
        uart_write_string("\tWrite the contents of the flash buffer to the flash memory.\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "lora cw"))
    {
        uart_write_string("\tStarts a LORA CW transmission.\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "get flash"))
    {
        uart_write_string("\tGets one byte from the flash data memory.\n\r\tParameter: <index in hex format>\n\r\tReturns: <hex value of byte at specified index>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "get gps status"))
    {
        uart_write_string("\tGets the status of the GPS.\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "get orientation"))
    {
        uart_write_string("\tGets the x, y, z values from the accelerometer.\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "set flash"))
    {
        uart_write_string("\tSets one byte in the flash data memory.\n\r\tParamter: <index in hex format> <one byte value in hex format>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "set gps echo"))
    {
        uart_write_string("\tEnabled/disables received GPS messages from being echoed onto the debug UART.\n\r\tParamter: <'on' or 'off'>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else
    {
        uart_write_string("\tType \"help <command>\" for more info\n\r");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("\tAvailible commands:\n\r");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("\t------------------------------------\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("buffered write\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("flush flash buffer\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("get flash\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("get gps status\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("get orientation\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("hello\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("init flash bufffer\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("lora cw\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set flash\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set gps echo\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("\n\r");
    }
}
