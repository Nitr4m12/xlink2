#pragma once

#include "thread/seadSpinLock.h"
#include "xlink2/xlink2ILockProxy.h"

namespace xlink2 {
template <typename T>
class LockProxy : ILockProxy {
    ~LockProxy() override;
    void lock();
    void unlock();

private:
    T mLock;
};

template <>
class LockProxy<sead::SpinLock> : ILockProxy {
public:
    ~LockProxy() override;
    void lock();
    void unlock();

private:
    sead::SpinLock mLock;
};
}  // namespace xlink2