#include <stdint.h>
#include <console/console.hpp>

Kernel::TextConsole Kernel::console;

void Kernel::TextConsole::Print(char c) {
    base->Print(c);
}
void Kernel::TextConsole::Print(const char * s) {
    uint32_t index = 0;
    while(s[index] != 0) {
        Print(s[index]);
        index++;
    }
}
void Kernel::TextConsole::PrintLine(const char * s) {
    Print(s);
    Print('\n');
}
void Kernel::TextConsole::Clear() {
    base->Clear();
    ResetColor();
}

void Kernel::TextConsole::ResetColor() {
    SetColor(defaultColor);
}

void Kernel::TextConsole::SetColor(char color) {
    base->SetColor(color);
}

void Kernel::TextConsole::SetBase(TextConsoleBase * b) {
    base = b;
    Clear();
}
