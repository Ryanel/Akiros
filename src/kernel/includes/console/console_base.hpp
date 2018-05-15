#pragma once

namespace Kernel {
/// A implementation used by the TextConsole
class TextConsoleBase {
protected:
    /// The current X position of the tty
    int x;
    /// The current Y position of the tty
    int y;
public:
    /// Print a character to the terminal. Must be able to interpret ASCII control codes.
    virtual void Print(char c) = 0;
    /// Clears the terminal, and resets X and Y to 0.
    virtual void Clear() = 0;
    /// Sets the current color
    virtual void SetColor(char colorCode) = 0;
    /// Get the width of the terminal
    virtual int GetWidth() = 0;
    /// Get the height of the terminal
    virtual int GetHeight() = 0;
    /// Get the current X of the terminal
    int GetX() {return x;}
    /// Get the current Y of the terminal
    int GetY() {return y;}
};
}
