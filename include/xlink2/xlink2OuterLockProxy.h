#pragma once

#include <thread/seadMutex.h>

#include "xlink2/xlink2ILockProxy.h"

namespace xlink2 {
template <typename T>
class OuterLockProxy : public ILockProxy {
public:
    ~OuterLockProxy() override = default;
    void lock() override;
    void unlock() override;

private:
    T* mLock;
};

static_assert(sizeof(OuterLockProxy<sead::Mutex>) == 0x10,
              "Incorrect size of 'xlink2::OuterLockProxy<sead::Mutex>'");
}  // namespace xlink2