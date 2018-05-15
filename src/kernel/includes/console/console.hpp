#ifndef KERNEL_CONSOLE_H
#define KERNEL_CONSOLE_H

#include <console/console_base.hpp>

namespace Kernel {

/// The text console. Can print characters to the screen
class TextConsole {
protected:
    /// The terminal implementation to use
    TextConsoleBase * base;
public:
    /// The default color
    char defaultColor = 0x0F;

public:
    /// Print a character to the console.
    void Print(char c);
    /// Print a string to the console.
    void Print(const char * s);
    /// Print a string, plus a newline, to the console
    void PrintLine(const char * s);
    /// Clears the console, and resets X and Y to 0.
    void Clear();
    /// Sets the current color
    void SetColor(char colorCode);
    /// Resets the color to the default
    void ResetColor();
    /// Sets the current output base
    void SetBase(TextConsoleBase* base);
};
/// The kernel's console
extern TextConsole console;
}
#endif
