#pragma once

#include "xlink2/xlink2ILockProxy.h"

namespace xlink2 {
class LockProxy : ILockProxy {
public:
    void lock();
    void unlock();

private:
};
}  // namespace xlink2