#include <stdint.h>
#include <multiboot.hpp>
#include <panic.hpp>
#include <klog.hpp>

const uint32_t MULTIBOOT_MAGIC = 0x2BADB002;

void Multiboot::Verify(uint32_t magic) {
    if(magic != MULTIBOOT_MAGIC) {
        panic("Failed multiboot verification");
    }
    Kernel::kLog.Debug("multiboot", "Booted successfully.");
}
