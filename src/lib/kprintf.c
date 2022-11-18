#include "../include/stdarg.h"
#include "../hal/hal_console.h"

static int vsprintf(char * buf, const char * fmt, char * args){
    return 0;
}

int printk(const char * fmt, ...) {
    char buf[1024];
    va_list args;
    int i;

    va_start(args, fmt);

    i = vsprintf(buf, fmt, args);

    va_end(args);

    write_console(fmt);

    return i;
}