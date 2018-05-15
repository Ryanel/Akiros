#include <panic.hpp>
#include <console/console.hpp>
#include <klog.hpp>

using namespace Kernel;

void panic(const char * msg) {
    kLog.Fatal("panic", msg);
    kHang();
}