#pragma once

namespace xlink2 {
class ILockProxy {
public:
    virtual ~ILockProxy();
    virtual void lock() = 0;
    virtual void unlock() = 0;
};
}  // namespace xlink2