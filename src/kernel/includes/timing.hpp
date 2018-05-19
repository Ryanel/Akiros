#pragma once

namespace Kernel {
class Timing {
private:
    Timer * currentTimer;
    
    long tickCount = 0;
    long tickResolution = 0;

public:
    long GetUptime();
    void DoTick();

    void SetTimer(Timer * t);
    Timer * GetTimer();
};

extern Timing timing;

}
