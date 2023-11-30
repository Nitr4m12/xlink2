#pragma once

#include <thread/seadSpinLock.h>

#include "xlink2/xlink2ILockProxy.h"

namespace xlink2 {
template <typename T>
class LockProxy : private ILockProxy {
public:
    ~LockProxy() override;
    void lock() override;
    void unlock() override;

private:
    T mLock;
};

static_assert(sizeof(LockProxy<sead::SpinLock>) == 0x18,
              "Incorrect size of 'xlink2::LockProxy<sead::SpinLock>'");

}  // namespace xlink2