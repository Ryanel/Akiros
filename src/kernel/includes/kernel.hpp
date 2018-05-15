#pragma once
#include <stdint.h>
#include <stddef.h>

// Define some utility macros
#define UNUSED(x) (void)(x)

namespace Kernel {
/// The main component of the kernel. Assumes basics are operating
void kMain();
}
