#pragma once

namespace Kernel {
class Timer {
public:
    long resolution;
    virtual void Init() = 0;
};
}