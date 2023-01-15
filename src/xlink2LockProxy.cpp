#include "xlink2/xlink2LockProxy.h"

namespace xlink2 {
LockProxy<sead::SpinLock>::~LockProxy() = default;
void LockProxy<sead::SpinLock>::lock() { mSpinLock.lock(); }
void LockProxy<sead::SpinLock>::unlock() { mSpinLock.unlock(); }
}