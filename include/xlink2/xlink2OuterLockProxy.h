#pragma once

#include "xlink2/xlink2ILockProxy.h"

namespace xlink2 {
class OuterLockProxy : ILockProxy {
public:
    void lock();
    void unlock();
private:
};
}