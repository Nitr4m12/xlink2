#include <xlink2/xlink2OuterLockProxy.h>

namespace xlink2 {
OuterLockProxy<sead::Mutex>::~OuterLockProxy() = default;
void OuterLockProxy<sead::Mutex>::lock() { mMutex->lock(); }
void OuterLockProxy<sead::Mutex>::unlock() { mMutex->unlock(); }
}