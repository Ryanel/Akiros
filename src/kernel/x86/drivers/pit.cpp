#include <x86/drivers/pit.hpp>
#include <x86/interrupts.hpp>
#include <klog.hpp>
using namespace Kernel;
using namespace x86;
using namespace x86::Drivers;

void PIT::Init() {
    interruptDispatch.Register(0, PIT_Handler);
}

extern "C" void PIT_Handler(registers_t * reg) {
    kLog.Debug("pit", "Got tick!");
}