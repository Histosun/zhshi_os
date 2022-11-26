#include "../include/stdarg.h"
#include "../hal/x86_64/halconsole.h"

void number(char** const p_str, int num){
    char temp[36];
    if(num<0){
        *((*p_str)++)='-';
        num = -num;
    }

    char * str = temp;
    do{
        *str++ = "0123456789"[num%10];
    }while(num/=10);

    while(str>temp){
        *((*p_str)++)=*--str;
    }
}

static int vsprintf(char * buf, const char * fmt, va_list args){
    char *str;
    for (str=buf ; *fmt ; ++fmt) {
        if(*fmt != '%'){
            *str = *fmt;
            ++str;
            continue;
        }

        ++fmt;
        switch (*fmt) {
            case 'd':
                number(&str, va_arg(args, int));
                break;
        }
    }
    *str = 0;
    return str - buf;
}

int printk(const char * fmt, ...) {
    char buf[1024];
    va_list args;
    int i;

    va_start(args, fmt);

    i = vsprintf(buf, fmt, args);

    va_end(args);

    write_console(buf);

    return i;
}