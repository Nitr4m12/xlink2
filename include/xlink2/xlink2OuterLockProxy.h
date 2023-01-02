#pragma once

#include "thread/seadMutex.h"
#include "xlink2/xlink2ILockProxy.h"

namespace xlink2 {
template <typename T>
class OuterLockProxy : ILockProxy {};

template <>
class OuterLockProxy<sead::Mutex> : ILockProxy {
    ~OuterLockProxy() override;
public:
    void lock();
    void unlock();
private:
    sead::Mutex* mMutex;
};
}