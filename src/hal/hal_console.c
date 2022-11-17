#include "hal_console.h"

typedef struct cursor{
    uint32_t x;
    uint32_t y;
}cursor_t;

static cursor_t cursor;
static uint16_t * const vga_str_addr = (uint16_t *)VGA_RAM_SADR;
static uint16_t * const vga_end_addr = (uint16_t *)VGA_RAM_EADR;
void clear_console()
{
    cursor.x=cursor.y=0;

    uint16_t * ptr = vga_str_addr;
    while (ptr < vga_end_addr)
    {
        *ptr++ = 0x0720;
    }
}

void init_console(){
    clear_console();
}