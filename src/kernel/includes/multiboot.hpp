#pragma once
#include <stdint.h>

/// All functions related to Multiboot
class Multiboot {
public:
    /// Verifies if the kernel was booted correctly, or halts
    static void Verify(uint32_t magic);
};
