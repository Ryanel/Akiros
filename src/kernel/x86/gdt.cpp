#include <x86/gdt.hpp>
#include <klog.hpp>

using namespace x86;
using namespace Kernel;


void GDT::Setup() {
    #ifdef ARCH_64Bit
    return; // Do not setup GDT, it's already setup by the loader.
    #endif

    gdtptr.limit = (sizeof(struct gdt_entry) * numEntries) - 1;
    gdtptr.base = (uint32_t)&gdt;

    SetGate(0, 0, 0, 0, 0);                // Null segment
	SetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
	SetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
	SetGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    SetGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    gdt_flush((uintptr_t)&gdtptr);
	kLog.Log(LOG_DEBUG, "x86", "GDT configured");
}

void GDT::SetGate(signed int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt[num].base_low    = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high   = (base >> 24) & 0xFF;

	gdt[num].limit_low   = (limit & 0xFFFF);

	gdt[num].granularity = (limit >> 16) & 0x0F;
	gdt[num].granularity |= gran & 0xF0;

    gdt[num].access = access;
}