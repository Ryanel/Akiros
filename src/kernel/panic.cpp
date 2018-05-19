#include <panic.hpp>
#include <console/console.hpp>
#include <klog.hpp>

using namespace Kernel;

[[ noreturn ]] void panic(const char * msg) {
    kLog.Fatal("panic", msg);
    while(true) {
        kHang();
    }
}