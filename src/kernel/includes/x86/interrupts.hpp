#pragma once

#include <stdint.h>
#include <x86/registers.hpp>

namespace x86 {
typedef void (*interrupt_handler_t)(registers_t *); 

/// Dispatches interrupts on the x86 architecture
class InterruptDispatch {
private:
	interrupt_handler_t interruptHandlerTable[256];
public:
	/// Dispatches an interrupt to the appropreate handlers
	bool Dispatch(registers_t * regs);
	/// Register a handler
	void Register (uint8_t n, interrupt_handler_t h);
	/// Unregister a handler
	void Unregister (uint8_t n);
};

/// Enable interrupts
void EnableInterrupts(bool on);

extern InterruptDispatch interruptDispatch;
}
