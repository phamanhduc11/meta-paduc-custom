#include <stdio.h>
#include <stdarg.h>

void myprint(const char *str, ...) {
    va_list va;
    va_start(va, str);
    printf(str, va);
    va_end(va);
}