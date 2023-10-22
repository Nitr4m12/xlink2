#include "xlink2/xlink2LockProxy.h"

namespace xlink2 {
template <typename T>
LockProxy<T>::~LockProxy() = default;

template <typename T>
void LockProxy<T>::lock() {
    mLock.lock();
}

template <typename T>
void LockProxy<T>::unlock() {
    mLock.unlock();
}


LockProxy<sead::SpinLock>::~LockProxy() = default;

void LockProxy<sead::SpinLock>::lock() {
    mLock.lock();
};

void LockProxy<sead::SpinLock>::unlock() {
    mLock.unlock();
};

}  // namespace xlink2