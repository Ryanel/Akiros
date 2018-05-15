#include <x86/x86.hpp>

void x86::EnableInterrupts() {
    __asm__("sti");
}

void x86::DisableInterrupts() {
    __asm__("sti");
}
