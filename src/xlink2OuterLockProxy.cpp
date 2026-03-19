#include <xlink2/xlink2OuterLockProxy.h>

namespace xlink2 {
template <typename T>
void OuterLockProxy<T>::lock()
{
    mLock->lock();
}

template <typename T>
void OuterLockProxy<T>::unlock()
{
    mLock->unlock();
}

// These are necessary for OuterLockProxy<sead::Mutex>
// to be picked up by the compiler as a separate class
// and be detected by check
template <>
void OuterLockProxy<sead::Mutex>::lock() {
    mLock->lock();
};

template <>
void OuterLockProxy<sead::Mutex>::unlock() {
    mLock->unlock();
};
}  // namespace xlink2