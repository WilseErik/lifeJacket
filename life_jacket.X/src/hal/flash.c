/*
 * This file allows the use of a part of the instruction memory to be used
 * as non volatile data memory.
 *
 * In this implemententation only the 16 LSB of each instruction (24 bits) will
 * be used for data storage. This of course consumes more memory, but speeds
 * up flash address calculation wich in turn improves read speeds significantly.
 *
 * One instruction in the flash memory:
 *
 *    -------------------------------------------------------------
 *   |        Used as data memory             |       Unused       |
 *    -------------------------------------------------------------
 *             BIT0    -    BIT15                  BIT16 -  BIT23
 *
 *
 * References:
 * Document number: DS30009715C, PIC24F Flash Program Memory
 * Document number: DS39715A, Section 4. Program Memory
 * Document number: DS39747D, PIC24FJ128GA010 Family Data Sheet
 * Document number: DS51284F, MPLAB C30 C COMPILER USER?S GUIDE
 * 
 */




// =============================================================================
// Include statements
// =============================================================================
#include "hal/flash.h"

#include <stdbool.h>
#include <stdint.h>

#include <xc.h>

// =============================================================================
// Private type definitions
// =============================================================================

// =============================================================================
// Global variables
// =============================================================================

// =============================================================================
// Private constants
// =============================================================================

#define INSTRUCTIONS_PER_ROW            64
#define ROWS_PER_ERASE_BLOCK            8
#define INSTRUCTIONS_PER_ERASE_BLOCK    512
#define WORDS_PER_ERASE_BLOCK           (INSTRUCTIONS_PER_ERASE_BLOCK * 2)

// =============================================================================
// Private variables
// =============================================================================

static volatile uint8_t buffer[FLASH_MEM_SIZE];

const uint16_t flash_data[WORDS_PER_ERASE_BLOCK] __attribute__((space(prog),aligned(WORDS_PER_ERASE_BLOCK))) =
{
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x0000
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x0008
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x0010
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x0018
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x0020
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x0028
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x0030
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x0038
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x0040
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x0048
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x0050
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x0058
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x0060
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x0068
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x0070
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x0078
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x0080
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x0088
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x0090
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x0098
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x00A0
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x00A8
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x00B0
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x00B8
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x00C0
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x00C8
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x00D0
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x00D8
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x00E0
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x00E8
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    // 0x00F0
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000     // 0x00F8
};

// =============================================================================
// Private function declarations
// =============================================================================


/**
 * @brief Erases the address page used for data.
 */
static void erase_flash_data(void);

// =============================================================================
// Public function definitions
// =============================================================================

void flash_init(void)
{
    ;
}

uint8_t flash_read_byte(flash_index_t index)
{
    uint16_t data;
    uint8_t ret_val;
    data = flash_read_word(index & ~0x0001);

    if (index & 0x0001)
    {
        ret_val = (uint8_t)data;
    }
    else
    {
        ret_val = (uint8_t)(data >> 8);
    }

    return ret_val;
}

uint16_t flash_read_word(flash_index_t index)
{
    uint16_t addr_offset;
    uint16_t read_word;
    uint16_t index_offset = (uint16_t)index & 0xFFFE;
    bool odd_addr = (0 != ((uint16_t)index & 0x0001));

    TBLPAG = __builtin_tblpage(flash_data);
    addr_offset = __builtin_tbloffset(flash_data) + index_offset;
    asm("tblrdl.w [%1], %0" : "=r"(read_word) : "r"(addr_offset));

    if (odd_addr)
    {
        uint16_t high_word;

        index_offset += 1;
        TBLPAG = __builtin_tblpage(flash_data);
        addr_offset = __builtin_tbloffset(flash_data) + index_offset;
        asm("tblrdl.w [%1], %0" : "=r"(high_word) : "r"(addr_offset));

        read_word = (read_word << 8) | (0x00FF & (high_word >> 8));
    }

    return read_word;
}

uint32_t flash_read_dword(flash_index_t index)
{
    uint32_t dword = 0x00000000;

    dword |= ((uint32_t)flash_read_word(index) << 16) & (uint32_t)0xFFFF0000;
    dword |=  (uint32_t)flash_read_word(index + 2)    & (uint32_t)0x0000FFFF;

    return dword;
}

void flash_init_write_buffer(void)
{
    uint16_t i;

    for (i = 0; i != FLASH_MEM_SIZE; i += 2)
    {
        uint16_t d = flash_read_word(i);
        buffer[i] = d >> 8;
        buffer[i + 1] = d;
    }
}

void flash_write_byte_to_buffer(flash_index_t index, uint8_t data)
{
    buffer[index] = data;
}

void flash_write_word_to_buffer(flash_index_t index, uint16_t data)
{
    buffer[index]     = (uint8_t)((data >> 8) & 0xFF);
    buffer[index + 1] = (uint8_t)( data       & 0xFF);
}

void flash_write_dword_to_buffer(flash_index_t index, uint32_t data)
{
    buffer[index]     = (uint8_t)((data >> 24) & 0xFF);
    buffer[index + 1] = (uint8_t)((data >> 16) & 0xFF);
    buffer[index + 2] = (uint8_t)((data >> 8 ) & 0xFF);
    buffer[index + 3] = (uint8_t)( data        & 0xFF);
}

/*
 * From DS39715A-page 4-17:
 *

The user can program one row of program Flash memory at a time. To do this, it is necessary to
erase the 8-row erase block containing the desired row. The general process is:
1. Read eight rows of program memory (512 instructions) and store in data RAM.
2. Update the program data in RAM with the desired new data.
3. Erase the block:
a) Set the NVMOP bits (NVMCOM<3:0>) to ?0010? to configure for block erase. Set the
ERASE (NVMCOM<6>) and WREN (NVMCOM<14>) bits.
b) Write the starting address of the block to be erased into the TBLPAG and W registers.
c) Write 55h to NVMKEY.
d) Write AAh to NVMKEY.
e) Set the WR bit (NVMCOM<15>). The erase cycle begins and the CPU stalls for the
duration of the erase cycle. When the erase is done, the WR bit is cleared automatically.
4. Write the first 64 instructions from data RAM into the program memory buffers (see Section 4.5
?Program Memory Writes?).
5. Write the program block to Flash memory:
a) Set the NVMOP bits to ?0001? to configure for row programming. Clear the ERASE
bit and set the WREN bit.
b) Write 55h to NVMKEY.
c) Write AAh to NVMKEY.
d) Set the WR bit. The programming cycle begins and the CPU stalls for the duration of the
write cycle. When the write to Flash memory is done, the WR bit is cleared automatically.
6. Repeat steps 4 and 5, using the next available 64 instructions from the block in data RAM
by incrementing the value in TBLPAG, until all 512 instructions are written back to Flash
memory.
For protection against accidental operations, the write initiate sequence for NVMKEY must be
used to allow any erase or program operation to proceed. After the programming command has
been executed, the user must wait for the programming time until programming is complete. The
two instructions following the start of the programming sequence should be NOPs, as shown in
Section 4.6.4.2 ?NVMKEY Register?.

 */
void flash_write_buffer_to_flash(void)
{
    uint16_t row;
    uint16_t instr;
    uint16_t offset;
    uint16_t buffer_index;

    erase_flash_data();

    // Memory row program operation (ERASE = 0) or no operation (ERASE = 1)
    NVMCONbits.NVMOP = 1;
    NVMCONbits.ERASE = 0;
    NVMCONbits.WREN = 1;

    TBLPAG = __builtin_tblpage(flash_data);
    offset = __builtin_tbloffset(flash_data);
    buffer_index = 0;

    for (row = 0; row != ROWS_PER_ERASE_BLOCK; ++row)
    {
        uint16_t row_offset = row * (uint16_t)INSTRUCTIONS_PER_ROW * 2;
        
        for (instr = 0; instr != INSTRUCTIONS_PER_ROW; ++instr)
        {
            uint16_t low_word;
            uint8_t dummy_data = 0x00;
            uint16_t addr = offset + (instr * 2) + row_offset;

            low_word  = (uint16_t)buffer[buffer_index++] << 8;
            low_word |= (uint16_t)buffer[buffer_index++];

            __builtin_tblwtl(addr, low_word);
            __builtin_tblwth(addr, dummy_data);
        }
        __builtin_disi(5);
        __builtin_write_NVM();

        while (NVMCONbits.WR)
        {
            ;
        }
    }  
}

// =============================================================================
// Private function definitions
// =============================================================================

/**
 * Reference: DS30009715C-page 16
 */
static void erase_flash_data(void)
{
    uint16_t addr_offset;

    NVMCONbits.NVMOP = 0x2;     // Erase block

    // Perform the erase operation specified by NVMOP3:NVMOP0 on the next WR command
    NVMCONbits.ERASE = 1;

    // Enable Flash program/erase operations
    NVMCONbits.WREN = 1;

    // Set up the address
    TBLPAG = __builtin_tblpage(flash_data);
    addr_offset = __builtin_tbloffset(flash_data);
    __builtin_tblwtl(addr_offset, 0); // Dummy TBLWT to load address

    // Start sequence accoding to doc: DS39715A-page 4-16
    __builtin_disi(5);
    __builtin_write_NVM();  

    while (NVMCONbits.WR)
    {
        ;
    }
}
