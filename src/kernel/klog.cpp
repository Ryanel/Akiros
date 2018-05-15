#include <klog.hpp>
#include <console/console.hpp>
#include <stdio.h>

using namespace Kernel;

KernelLog Kernel::kLog;

void KernelLog::PrintTag(const char * tag) {
    bool hasTime = false;
    if(hasTime) {
        printf("[%s:%d]: ", tag ,0); // TODO: Implement tick counter. Convert ticks into seconds.
    }
    else {
        printf("[%s]: ", tag);
    }
}

void KernelLog::SetColor(LogLevel level) {
    switch(level) {
        case LOG_DEBUG:
            console.SetColor(0x08);
            break;
        case LOG_INFO:
            console.SetColor(0x0B);
            break;
        case LOG_WARNING:
            console.SetColor(0x0E);
            break;
        case LOG_ERROR:
            console.SetColor(0x0C);
            break;
        case LOG_FATAL:
            console.SetColor(0xF4);
            break;
    }
}

void KernelLog::Log(LogLevel level, const char * tag, const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
    Log(level, tag, fmt, args);
    va_end(args);
}

void KernelLog::Log(LogLevel level, const char * tag, const char * fmt, va_list args) {
    SetColor(level);
    PrintTag(tag);

	vprintf(fmt,args);

    console.Print('\n');
    console.ResetColor();
}

void KernelLog::Debug(const char * tag, const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
    Log(LOG_DEBUG, tag, fmt, args);
    va_end(args);
}

void KernelLog::Info(const char * tag, const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
    Log(LOG_INFO, tag, fmt, args);
    va_end(args);
}

void KernelLog::Warning(const char * tag, const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
    Log(LOG_WARNING, tag, fmt, args);
    va_end(args);
}

void KernelLog::Error(const char * tag, const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
    Log(LOG_ERROR, tag, fmt, args);
    va_end(args);
}

void KernelLog::Fatal(const char * tag, const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
    Log(LOG_FATAL, tag, fmt, args);
    va_end(args);
}
