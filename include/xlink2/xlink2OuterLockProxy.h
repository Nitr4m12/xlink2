#pragma once

#include "thread/seadMutex.h"
#include "xlink2/xlink2ILockProxy.h"

namespace xlink2 {
template <typename T>
class OuterLockProxy : ILockProxy {};

template <>
class OuterLockProxy<sead::Mutex> : ILockProxy {
    ~OuterLockProxy() override = default;

public:
    void lock() { mMutex->lock(); };
    void unlock() { mMutex->unlock(); };

private:
    sead::Mutex* mMutex;
};
}  // namespace xlink2