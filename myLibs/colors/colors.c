#include <stdio.h>
#include <stdarg.h>
#include "colors.h"

void cprint(const char *fg, const char *bg, const char *fmt, ...) {
    va_list args;

    printf("%s%s", fg, bg);

    va_start(args, fmt);        // starts reading after the fmt
    vprintf(fmt, args);         // prints like printf with args as the arguments
    va_end(args);               // stop point of the stdarg.

    printf(RESET);
}