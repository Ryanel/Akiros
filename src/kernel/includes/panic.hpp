#pragma once

/// Causes the kernel to halt with error msg.
void panic(const char * msg);

/// Immediately hangs the kernel
extern "C" void kHang();
