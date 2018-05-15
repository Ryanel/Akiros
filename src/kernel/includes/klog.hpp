#pragma once
#include <stdarg.h>

namespace Kernel {

/// A log priority
enum LogLevel {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL
};

/// The kernel's log
class KernelLog {
private:
    /// Prints a tag to the screen
    void PrintTag(const char * tag);
    /// Sets the screen's color based on the log level
    void SetColor(LogLevel level);
public:
    /// Logs the formatted string to the screen, using the tag and loglevel
    void Log(LogLevel level, const char * tag, const char * fmt, ...);
    /// Logs the formatted string to the screen, using the tag and loglevel, using args for the formatted string
    void Log(LogLevel level, const char * tag, const char * fmt, va_list args);

    /// Logs a string to the console
    void Debug(const char * tag, const char * fmt, ...);
    /// Logs a string to the console
    void Info(const char * tag, const char * fmt, ...);
    /// Logs a string to the console
    void Warning(const char * tag, const char * fmt, ...);
    /// Logs a string to the console
    void Error(const char * tag, const char * fmt, ...);
    /// Logs a string to the console
    void Fatal(const char * tag, const char * fmt, ...);
};

/// The kernel's global log
extern KernelLog kLog;

};