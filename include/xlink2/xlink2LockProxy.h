#pragma once

#include "xlink2/xlink2.h"

namespace xlink2 {
class ILockProxy {
    ~ILockProxy();
};

class LockProxy : ILockProxy {
public:
    void lock();
    void unlock();

private:
};

class OuterLockProxy : ILockProxy {
public:
    void lock();
    void unlock();
private:
};
}  // namespace xlink2