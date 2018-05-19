#pragma once
#include <stdint.h>
#include <stddef.h>

// Define some utility macros
#define UNUSED(x) (void)(x)

/// All classes that are used by the kernel
namespace Kernel {
/// The main component of the kernel. Assumes basics are operating
void kMain();
}
