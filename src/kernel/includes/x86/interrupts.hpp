#pragma once

#include <stdint.h>
#include <x86/registers.hpp>

namespace x86 {
typedef void (*interrupt_handler_t)(registers_t *); 

class InterruptDispatch {
private:
	interrupt_handler_t interruptHandlerTable[256];
public:
	bool Dispatch(registers_t * regs);
	void Register (uint8_t n, interrupt_handler_t h);
	void Unregister (uint8_t n);
};

void EnableInterrupts(bool on);

extern InterruptDispatch intDispatch;
}
