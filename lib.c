#include "lib.h"

void err_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}

void err_println(const char *s) {
    err_printf("%s\n", s);
}
