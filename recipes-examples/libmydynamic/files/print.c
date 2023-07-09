#include <stdio.h>
#include <stdarg.h>

void myprint_dynamic(const char *str, ...) {
    va_list va;
    va_start(va, str);
    printf(str, va);
    va_end(va);
}