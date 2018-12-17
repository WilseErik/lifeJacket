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
    else if (NULL != strstr(in, "test temp"))
    {
        uart_write_string("\tReads one value from the first MAX6675 ic.\n\r\tReturns: <read value as 16 bits in hex format>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "temp curve eval"))
    {
        uart_write_string("\tEvalues the temperature curve at one point in time.\n\r\tParameters: <seconds in to reflow program>\n\r\tReturns: <target temperature>\n\r\t\n\r");
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
    else if (NULL != strstr(in, "get flash"))
    {
        uart_write_string("\tGets one byte from the flash data memory.\n\r\tParameter: <index in hex format>\n\r\tReturns: <hex value of byte at specified index>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "get K"))
    {
        uart_write_string("\tGets the K constant in the PID regulator.\n\r\tReturns: <K value as a decimal value>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "get Ti"))
    {
        uart_write_string("\tGets the Ti constant in the PID regulator.\n\r\tReturns: <Ti value as a decimal value>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "get Td"))
    {
        uart_write_string("\tGets the Td constant in the PID regulator.\n\r\tReturns: <Td value as a decimal value>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "get Ttr"))
    {
        uart_write_string("\tGets the PID integral tracking time constant.\n\r\tReturns: <PID integral tracking time constant>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "get d max gain"))
    {
        uart_write_string("\tGets the max gain of the PID derivate term.\n\r\tReturns: <Max PID derivate part gain>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "get pid servo factor"))
    {
        uart_write_string("\tGets the servo output scaling factor.\n\r\tReturn: <scaling factor as positive float value>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "get temp filter len"))
    {
        uart_write_string("\tGets the length of the moving average temperature filter.\n\r\tReturn: <lenght of filter>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "get start of soak"))
    {
        uart_write_string("\tGets the timestamp in [s] for when the soak period starts.\n\r\tThis is done for the profile selected by the reflow profile switch.\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "get start of reflow"))
    {
        uart_write_string("\tGets the timestamp in [s] for when the reflow period starts.\n\r\tThis is done for the profile selected by the reflow profile switch.\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "get start of cool"))
    {
        uart_write_string("\tGets the timestamp in [s] for when the cooling period starts.\n\r\tThis is done for the profile selected by the reflow profile switch.\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "set heater"))
    {
        uart_write_string("\tSets the heater on or off.\n\r\tParameter: <'on' or 'off'>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "set servo pos"))
    {
        uart_write_string("\tSets the servo position.\n\r\tParameter: <position as integer in [0, 1200]>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "set flash"))
    {
        uart_write_string("\tSets one byte in the flash data memory.\n\r\tParamter: <index in hex format> <one byte value in hex format>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "set K"))
    {
        uart_write_string("\tSets the K constant in the PID regulator.\n\r\tParameter: <Value in the range [-65535.0, 65535.0]>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "set Ti"))
    {
        uart_write_string("\tSets the Ti constant in the PID regulator.\n\r\tParameter: <Value in the range [-65535.0, 65535.0]>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "set Td"))
    {
        uart_write_string("\tSets the Td constant in the PID regulator.\n\r\tParameter: <Value in the range [-65535.0, 65535.0]>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "set Ttr"))
    {
        uart_write_string("\tSets the integrator tracking time constant in the PID regulator.\n\r\tParameter: <Value in the range [0.0, 65535.0]>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "set d max gain"))
    {
        uart_write_string("\tSets the max gain of the PID derivative term.\n\r\tParameter: <Value in the range [0.0, 65535.0]>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "set pid servo factor"))
    {
        uart_write_string("\tSets how much the servo should extend for negative control values.\n\r\tParamter: <positive float scaling value>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "set temp filter len"))
    {
        uart_write_string("\tSets the length of the moving average temperature filter.\n\r\tReturn: <lenght of filter>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "set heat pwm"))
    {
        uart_write_string("\tActivates the heater PWM and sets the pwm value.\n\r\tParameter: <Duty in range [0, 50]>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "set start of soak"))
    {
        uart_write_string("\tSets the timestamp in [s] for when the soak period starts.\n\r\tThis is done for the profile selected by the reflow profile switch.\n\r\tParameter: <timestamp in seconds>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "set start of reflow"))
    {
        uart_write_string("\tSets the timestamp in [s] for when the reflow period starts.\n\r\tThis is done for the profile selected by the reflow profile switch.\n\r\tParameter: <timestamp in seconds>\n\r\t\n\r");
        while (!uart_is_write_buffer_empty()){;}
    }
    else if (NULL != strstr(in, "set start of cool"))
    {
        uart_write_string("\tSets the timestamp in [s] for when the cool period starts.\n\r\tThis is done for the profile selected by the reflow profile switch.\n\r\tParameter: <timestamp in seconds>\n\r\t\n\r");
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
        uart_write_string("get K\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("get Td\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("get Ti\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("get Ttr\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("get d max gain\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("get flash\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("get pid servo factor\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("get start of cool\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("get start of reflow\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("get start of soak\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("get temp filter len\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("hello\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("init flash bufffer\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set K\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set Td\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set Ti\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set Ttr\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set d max gain\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set flash\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set heat pwm\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set heater\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set pid servo factor\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set servo pos\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set start of cool\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set start of reflow\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set start of soak\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("set temp filter len\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("temp curve eval\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("test temp\n\r\t");
        while (!uart_is_write_buffer_empty()){;}
        uart_write_string("\n\r");
    }
}
