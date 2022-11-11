#include "../include/string.h"


char* strcpy(char* const dest, const char* src){
    char* ptr = dest;
    while((*ptr=*src)){
        ++src;
        ++ptr;
    }
    return dest;
}

char* strcat(char* const dest, const char* src){
    char* ptr = dest;
    while((*ptr=*src)){
        ++src;
        ++ptr;
    }
    
    return dest;
}

size_t strlen(const char* str){
    size_t len = 0;
    while(str[len]){
        ++len;
    }
    return len;
}

int strcmp(const char* lhs, const char* rhs){
    int pos=0;
    while(lhs[pos] && lhs[pos]==rhs[pos]){
        ++pos;
    }
    if(lhs[pos]>rhs[pos])
        return 1;
    if(lhs[pos]<rhs[pos])
        return -1;
    return 0;
}

char* strchr(const char* str, int ch){
    while(*str){
        if(*str==ch)
            return (char*)str;
        ++str;
    }
    return NULL;
}

char* strrchr(const char* str, int ch){
    char* last=NULL;
    while(*str){
        if(*str==ch)
            last=(char*)str;
        ++str;
    }
    return last;
}

