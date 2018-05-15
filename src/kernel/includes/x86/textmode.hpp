#pragma once
#include <stdint.h>
#include <console/console_base.hpp>

namespace x86 {
/// A implementation used by the TextConsole
class TextMode : public Kernel::TextConsoleBase {
private:
    /// Width of the screeen
    const int width = 80;
    /// Height of the screen
    const int height = 25;

    /// The current color to output to the screen
    char currentAttribute = 0x0F;

    /// The base IO address of the screen
    #if ARCH_64Bit
    const uintptr_t baseAddr = 0x000B8000;
    #else
    const uintptr_t baseAddr = 0xC00B8000;
    #endif

    /// Pointer to screen memory
    uint8_t * buffer = (uint8_t*)baseAddr;
    /// Pointer to screen memory
    uint16_t * buffer16 = (uint16_t*)baseAddr;
    
    /// Writes a character to the screen at x, y
    void PutChar(char c, char attribute, int x, int y);
    /// Updates the hardware cursor
    void UpdateHardwareCursor();
    /// Sets the cursor. If y > 25, scroll
    void SetCursor(int x, int y);
    /// Scrolls the screen
    void Scroll();
    /// Write a newline
    void NewLine();
    /// Write a backspace
    void Backspace();
    /// Do a carriage return.
    void CarriageReturn();

public:
    /// Print a character to the terminal. Must be able to interpret ASCII control codes.
    virtual void Print(char c);
    /// Clears the terminal, and resets X and Y to 0.
    virtual void Clear();
    /// Sets the current color
    virtual void SetColor(char colorCode);
    /// Get the width of the terminal
    virtual int GetWidth();
    /// Get the height of the terminal
    virtual int GetHeight();
    /// Get the current X of the terminal
    int GetX() {return x;}
    /// Get the current Y of the terminal
    int GetY() {return y;}
};

/// The base
extern TextMode textModeBase;
}
