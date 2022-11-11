#include "../include/vgastr.h"

#define VGA_BASE_ADDR 0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define vga_make(c, c)

#define va_start(p, count) (p = (va_list)&count + sizeof(char*))
// 这行代码做了两件事情：1、修改p_args; 2、取值
#define va_arg(p, t) (*(t*)((p += sizeof(char*)) - sizeof(char*)))
#define va_end(p) (p = 0)

cursor_t cursor;

KLINE uint16_t make_char(char c, char color){
    return (color << 8) | c;
}

void terminal_clear(){
    uint16_t * video_meme = (uint16_t*) VGA_BASE_ADDR;
    
}