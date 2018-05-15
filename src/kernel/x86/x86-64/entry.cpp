#include <stdint.h>

#include <kernel.hpp>
#include <console/console.hpp>

#include <multiboot.hpp>
#include <x86/textmode.hpp>
#include <klog.hpp>

using namespace Kernel;
using namespace x86;

void kConfigureKernel();
void kInitHardware();

void kConfigureKernel() {
    console.SetBase(&x86::textModeBase);
    kLog.Debug("console", "Console device configiured");
}

void kInitHardware() {
    kLog.Debug("kernel", "Initialising hardware");
}

/// Start of execution
extern "C" void kStart() {
    kConfigureKernel();
    kInitHardware();
    kLog.Info("kernel", "Entering main...");
    kMain();
}
