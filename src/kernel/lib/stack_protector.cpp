#include <stdint.h>
#include <panic.hpp>

const uintptr_t __stack_chk_guard = 0xAB03FF00;
  
extern "C" 
 __attribute__((noreturn)) void __stack_chk_fail(void)
{
 	panic("Stack smashing detected");
 	while(true) {}
}
