#include "xlink2/xlink2LockProxy.h"

namespace xlink2 {
template <typename T>
LockProxy<T>::~LockProxy() = default;

template <typename T>
void LockProxy<T>::lock()
{
    mLock.lock();
}

template <typename T>
void LockProxy<T>::unlock()
{
    mLock.unlock();
}

// NON-MATCHING: unknown reason
template <>
LockProxy<sead::SpinLock>::~LockProxy() = default;

}  // namespace xlink2