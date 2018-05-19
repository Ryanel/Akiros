#include <x86/interrupts.hpp>
#include <x86/registers.hpp>
#include <interrupts.hpp>
#include <klog.hpp>
#include <panic.hpp>

using namespace x86;
using namespace Kernel;

InterruptDispatch x86::interruptDispatch;

bool InterruptDispatch::Dispatch(registers_t * regs) {
    int interruptNumber = regs->int_no;
    if(interruptHandlerTable[interruptNumber] == nullptr) {
        interruptManager.interruptsUndispatched++;
        return false;
    }

    interruptHandlerTable[interruptNumber](regs);
    interruptManager.interruptsDispatched++;
    return true;
}

void InterruptDispatch::Register (uint8_t n, interrupt_handler_t h) {
    if(interruptHandlerTable[n] != nullptr) {
        kLog.Warning("int dispatch", "Interrupt %d reassigned from 0x%X to 0x%X.", (uintptr_t)n, (uintptr_t)interruptHandlerTable[n], (uintptr_t)h);
    }
    interruptHandlerTable[n] = h;
}

void InterruptDispatch::Unregister (uint8_t n) {
    interruptHandlerTable[n] = nullptr;
}
