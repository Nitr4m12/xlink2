#pragma once

namespace xlink2 {
class ILockProxy {
public:
    virtual ~ILockProxy();
    virtual void lock();
    virtual void unlock();
};
}  // namespace xlink2