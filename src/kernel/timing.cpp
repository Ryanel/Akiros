#include <timer.hpp>
#include <timing.hpp>
#include <klog.hpp>

using namespace Kernel;

Timing Kernel::timing;

long Timing::GetUptime() {
    long seconds = tickCount / (long)tickResolution;
    return seconds;
}

void Timing::DoTick() {
    tickCount++;
    if((tickCount % 1000) == 0) {
        int seconds = tickCount / 1000;
        kLog.Debug("timing", "%d second has passed", seconds);
    }
}

void Timing::SetTimer(Timer * t) {
    currentTimer = t;
    tickResolution = currentTimer->resolution;
}
Timer * Timing::GetTimer() {
    return currentTimer;
}