#include <stdint.h>

#include <kernel.hpp>
#include <console/console.hpp>

#include <multiboot.hpp>
#include <klog.hpp>

#include <x86/textmode.hpp>
#include <x86/gdt.hpp>
#include <x86/idt.hpp>
#include <x86/interrupts.hpp>

#include <x86/drivers/pit.hpp>

using namespace Kernel;
using namespace x86;

IDT idt;
x86::Drivers::PIT pit;

/// Configure the kernel
void kConfigureKernel() {
    console.SetBase(&x86::textModeBase);
    kLog.Debug("console", "Console device configiured");
}

/// Initialise the hardware
void kInitHardware() {
    kLog.Info("kernel", "Initialising hardware");

    idt.Setup();
    pit.Init();
    x86::EnableInterrupts(true);

    kLog.Info("kernel", "Initialised hardware");
}

/// Start of execution
extern "C" void kStart(uint32_t mbMagic, void * mbt) { 
    UNUSED(mbMagic);
    UNUSED(mbt);
    
    kConfigureKernel();
    
    Multiboot::Verify(mbMagic);

    kInitHardware();
    
    kMain();
}