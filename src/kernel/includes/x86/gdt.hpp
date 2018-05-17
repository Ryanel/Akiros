#pragma once

#include <stddef.h>
#include <stdint.h>

namespace x86 {
/// Manages the x86 GDT
class GDT {
public:
    /// An entry in the GDT
    struct gdt_entry
    {
        unsigned short limit_low;
        unsigned short base_low;
        unsigned char base_middle;
        unsigned char access;
        unsigned char granularity;
        unsigned char base_high;
    } __attribute__((packed));

    /// Pointer to the GDT
    struct gdt_ptr
    {
        unsigned short limit;
        unsigned int base;
    } __attribute__((packed));

private:
    /// The number of entries in the GDT
    const static int numEntries = 7;
    /// The actual GDT. Actually will contain the entries
    struct gdt_entry 	gdt[numEntries];
    /// Sets the GDT entry in gdt.
    void SetGate(signed int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);    
public:
    /// Sets up the GDT.
    void Setup();
};
/// Sets the GDT. Do not call from anything other then GDT!
extern "C" void gdt_flush(uintptr_t gdt_pointer);

}
