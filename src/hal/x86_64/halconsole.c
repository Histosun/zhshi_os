#include "halconsole.h"
#define vga_start_addr (uint16_t *)VGA_RAM_SADR
#define vga_end_addr (uint16_t *)VGA_RAM_EADR

typedef struct cursor{
    uint32_t x;
    uint32_t y;
}cursor_t;

__attribute__((section(".data"))) cursor_t cursor;

void clear_console()
{
    cursor.x = cursor.y = 0;

    uint16_t * ptr = vga_start_addr;
    while (ptr < vga_end_addr) {
        *ptr++ = 0x0720;
    }
}

void init_console(){
    clear_console();
}

void write_console(const char * buff){
    char * pos = (char *) (vga_start_addr + cursor.x + cursor.y * 80);
    while(*buff){
        *pos = *buff++;
        pos += 2;
    }
    uint32_t offset = (uint16_t *)pos - vga_start_addr;
    cursor.x = offset % 80;
    cursor.y = offset / 80;
}

void write_number(const uint64_t number){
    char * pos = (char *) (vga_start_addr);
    char buf[16];
    uint64_t num = number;
    for(int i = 0; i < 16; ++i) {
        buf[i] = "0123456789abcdef"[num % 16];
        num/=16;
    }
    for(int i = 0; i < 16; ++i) {
        pos[i*2] = buf[15 - i];
    }
}

void write_cusor(){
    write_number(&cursor);
}