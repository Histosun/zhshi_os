void _strwirite(char* str) {
    // Video memory start address
    char * p_strdst = (char*) 0xb8000;
    while(*str){
        *p_strdst = *str++;
        p_strdst += 2;
    }
}

void printf(char* fmt, ...){
    _strwirite(fmt);
}