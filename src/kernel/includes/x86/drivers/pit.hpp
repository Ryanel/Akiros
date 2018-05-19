#pragma once
#include <timer.hpp>
#include <x86/registers.hpp>
namespace x86 {
namespace Drivers {

class PIT : public Kernel::Timer {
public:
    virtual void Init();
};

extern "C" void PIT_Handler(registers_t * reg);

}
}

