#pragma once

#include "thread/seadSpinLock.h"
#include "xlink2/xlink2ILockProxy.h"

namespace xlink2 {
template <typename T>
class LockProxy : ILockProxy {};

template <>
class LockProxy<sead::SpinLock> : ILockProxy {
public:
    ~LockProxy() override;
    void lock();
    void unlock();

private:
    sead::SpinLock mSpinLock;
};
}  // namespace xlink2