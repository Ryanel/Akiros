#pragma once

namespace Kernel {
/// Manages all interrupts
class InterruptManager {
public:
    int interruptsDispatched = 0;
    int interruptsUndispatched = 0;
};

extern InterruptManager interruptManager;
}