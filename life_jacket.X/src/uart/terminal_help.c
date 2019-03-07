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
    else if (NULL != strstr(in, "system reset"))
    {
        uart_write_string("\tForces a software reboot.\n\r\t\n\r");
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
    else if (NULL != strstr(in, "lora gps broadcast"))
    {
        uart_write_string("\tStarts a LoRa GPS position broadcast.\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "lora cont rx"))
    {
        uart_write_string("\tStarts continuous rx LoRa mode.\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "gps on off pulse"))
    {
        uart_write_string("\tSends a on/off pulse to the GPS module.\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "ext flash chip erase"))
    {
        uart_write_string("\tErases the whole external flash memory.\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "ext flash write test"))
    {
        uart_write_string("\tWrites test data to the first page (first 256 bytes).\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "ef spb"))
    {
        uart_write_string("\tSets two bytes in the page buffer. Word indexed.\n\r\tParameters: <index in range [0, 127]> <value to set as 4 hex digits>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "ef wp"))
    {
        uart_write_string("\tWrites the page buffer to a page in the external flash memory.\n\r\tParameters: <page address as 6 hex digits>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "test audio session"))
    {
        uart_write_string("\tRuns a audio session test.\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "write audio test data"))
    {
        uart_write_string("\tWrites test audio data to the external flash memory.\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "restart uart"))
    {
        uart_write_string("\tResets the debug UART module.\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "get flash"))
    {
        uart_write_string("\tGets one byte from the flash data memory.\n\r\tParameter: <index in hex format>\n\r\tReturns: <hex value of byte at specified index>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "get ext flash"))
    {
        uart_write_string("\tGets one byte from the external flash memory.\n\r\tParameter: <address in hex>\n\r\tReturns: <read byte in hex format>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "get page ext flash"))
    {
        uart_write_string("\tGets 256 of bytes from the external flash memory.\n\r\tParameters: <start address in hex>\n\r\t\n\r");
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
    else if (NULL != strstr(in, "set lora bw"))
    {
        uart_write_string("\tSets the LoRa channel bandwidth.\n\r\tParameter: <bandwidth setting in range [0, 9]>\n\r\t\n\r\t0 = 7.8kHz\n\r\t1 = 10.4kHz\n\r\t2 = 15.6 kHz\n\r\t3 = 20.8 kHz\n\r\t4 = 31.25 kHz\n\r\t5 = 41.7 kHz\n\r\t6 = 62.5 kHz\n\r\t7 = 125 kHz\n\r\t8 = 250 kHz\n\r\t9 = 500 kHz\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "set lora cr"))
    {
        uart_write_string("\tSets the LoRa coding rate.\n\r\tParameter: <coding rate setting in range[1, 4]>\n\r\t\n\r\t1 = coding rate 4/5\n\r\t2 = coding rate 4/6\n\r\t3 = coding rate 4/7\n\r\t4 = coding rate 4/8\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "set lora sf"))
    {
        uart_write_string("\tSets the LoRa spreading factor.\n\r\tParameter: <spreading factor in range [6, 12]>\n\r\t\n\r\tA spreading factor of 'sf' gives 2^(sf) chips\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "set lora freq"))
    {
        uart_write_string("\tSets the LoRa frequency.\n\r\tParameter: <frequency band in range [1, 8]>\n\r\t\n\r\tBands:\n\r\t1 = 868.1 MHz\n\r\t2 = 868.3 MHz\n\r\t3 = 868.5 MHz\n\r\t4 = 867.1 MHz\n\r\t5 = 867.3 MHz\n\r\t6 = 867.5 MHz\n\r\t7 = 867.7 MHz\n\r\t8 = 867.9 MHz\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "set sleep allowed"))
    {
        uart_write_string("\tEnables/disables sleep mode.\n\r\tParamter: <'on' or 'off'>\n\r\t\n\r");
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
        uart_write_string("ef spb\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("ef wp\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("ext flash chip erase\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("ext flash write test\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("flush flash buffer\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("get ext flash\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("get flash\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("get gps status\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("get orientation\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("get page ext flash\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("gps on off pulse\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("hello\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("init flash bufffer\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("lora cont rx\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("lora cw\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("lora gps broadcast\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("restart uart\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set flash\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set gps echo\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set lora bw\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set lora cr\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set lora freq\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set lora sf\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set sleep allowed\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("system reset\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("test audio session\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("write audio test data\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("\n\r");
    }
}
