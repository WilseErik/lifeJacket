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
        uart_write_string("set lora bw\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set lora cr\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set lora freq\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set lora sf\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("system reset\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("\n\r");
    }
}
