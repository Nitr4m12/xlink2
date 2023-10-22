#pragma once

#include "thread/seadMutex.h"
#include "xlink2/xlink2ILockProxy.h"

namespace xlink2 {
template <typename T>
class OuterLockProxy : ILockProxy {};

template <>
class OuterLockProxy<sead::Mutex> : ILockProxy {
public:
    ~OuterLockProxy() override;
    void lock() override;
    void unlock() override;

private:
    sead::Mutex mMutex;
};
}  // namespace xlink2