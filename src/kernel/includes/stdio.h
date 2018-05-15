#ifndef LIB_STDIO_H
#define LIB_STDIO_H
#include <stdarg.h>
int vsprintf(char *buf, const char *fmt, va_list args);
int sprintf(char *buf, const char *fmt, ...);
int vprintf(const char *fmt, va_list args);
int printf(const char *fmt, ...);
#endif
