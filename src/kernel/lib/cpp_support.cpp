#include <panic.hpp>

// Catch errors if a pure virtual function is not called
extern "C" void __cxa_pure_virtual()
{
    panic("Pure virtual function error!");
}
