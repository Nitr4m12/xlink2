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
}  // namespace xlink2