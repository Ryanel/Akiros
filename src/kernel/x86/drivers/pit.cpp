#include <x86/ports.hpp>
#include <x86/idt.hpp>
#include <x86/drivers/pit.hpp>
#include <x86/interrupts.hpp>
#include <klog.hpp>
#include <kernel.hpp>
#include <timer.hpp>
#include <timing.hpp>

using namespace Kernel;
using namespace x86;
using namespace x86::Drivers;

void PIT::Init() {
    resolution = 1000;
    
    uint32_t divisor = 1193180 / resolution;
    outb(0x43, 0x36);
    uint8_t l = (uint8_t)(divisor & 0xFF);
	uint8_t h = (uint8_t)((divisor>>8) & 0xFF);
	outb(0x40, l);
    outb(0x40, h);

    interruptDispatch.Register(IRQ0, PIT_Handler);
    
    kLog.Log(LOG_DEBUG, "pit", "PIT started");
}

extern "C" void PIT_Handler(registers_t * reg) {
    UNUSED(reg);
    timing.DoTick();
}
